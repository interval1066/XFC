/*  Xfc-UI: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  widget.cc - GtkWidget C++ wrapper implementation
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

#include "widget.hh"
#include "widgetsignals.hh"
#include "accelgroup.hh"
#include "clipboard.hh"
#include "container.hh"
#include "rc.hh"
#include "settings.hh"
#include "stockid.hh"
#include "style.hh"
#include "private/marshal.hh"
#include "private/widgetclass.hh"
#include "xfc/atk/object.hh"
#include "xfc/gdk/bitmap.hh"
#include "xfc/gdk/color.hh"
#include "xfc/gdk/cursor.hh"
#include "xfc/gdk/display.hh"
#include "xfc/gdk/region.hh"
#include "xfc/gdk/screen.hh"
#include "xfc/gdk/visual.hh"
#include "xfc/gdk/window.hh"
#include "xfc/gdk-pixbuf/pixbuf.hh"
#include "xfc/pango/context.hh"
#include "xfc/pango/font.hh"
#include "xfc/pango/layout.hh"
#include "xfc/glib/value.hh"

using namespace Xfc;

/*  Gtk::Allocation
 */

Gtk::Allocation::Allocation()
{
}

Gtk::Allocation::Allocation(int x, int y, int width, int height)
: Gdk::Rectangle(x, y, width, height)
{
}

Gtk::Allocation::Allocation(const GtkAllocation& allocation)
: Gdk::Rectangle(allocation)
{
}

/*  Gtk::Requisition
 */

Gtk::Requisition::Requisition()
{
	set(0, 0);
}

Gtk::Requisition::Requisition(int width, int height)
{
	set(width, height);
}

Gtk::Requisition::Requisition(const GtkRequisition& requisition)
{
	set(requisition.width, requisition.height);
}

bool
Gtk::Requisition::operator==(const Requisition& other) const
{
	return other.width() == requisition_.width && other.height() == requisition_.height;
}

bool
Gtk::Requisition::operator!=(const Requisition& other) const
{
	return !(*this == other);
}

/*  Gtk::Widget
 */

Gtk::Widget::Widget(GtkWidget *widget, bool owns_reference)
: Object((GtkObject*)widget, owns_reference)
{
}

Gtk::Widget::Widget()
: Object((GtkObject*)WidgetClass::create())
{
}

Gtk::Widget::~Widget()
{
}

void 
Gtk::Widget::set_allocation(const Allocation& allocation)
{
	gtk_widget()->allocation = *allocation.gtk_allocation();
}

void
Gtk::Widget::set_window(const Gdk::Window& window)
{
	g_return_if_fail(!gtk_widget()->window);
	gtk_widget()->window = window.gdk_window();
}

Gtk::Requisition
Gtk::Widget::get_child_requisition() const
{
	GtkRequisition requisition;
	gtk_widget_get_child_requisition(gtk_widget(), &requisition);
	return requisition;
}

void
Gtk::Widget::get_child_requisition(Requisition& requisition) const
{
	gtk_widget_get_child_requisition(gtk_widget(), requisition.gtk_requisition());
}

Gdk::Window*
Gtk::Widget::get_window() const
{
	return is_realized() ? G::Object::wrap<Gdk::Window>(gtk_widget()->window) : 0;
}

String
Gtk::Widget::get_name() const
{
	return gtk_widget_get_name(gtk_widget());
}

Gtk::Widget*
Gtk::Widget::get_parent() const
{
	GtkWidget *parent = gtk_widget_get_parent(gtk_widget());
 	return parent ? G::Object::wrap<Widget>(parent) : 0;
}

Gdk::Window*
Gtk::Widget::get_parent_window() const
{
	GdkWindow *window = gtk_widget_get_parent_window(gtk_widget());
	return window ? G::Object::wrap<Gdk::Window>(window) : 0;
}

Gtk::Widget*
Gtk::Widget::get_toplevel() const
{
	GtkWidget *top_level = gtk_widget_get_toplevel(gtk_widget());
	return top_level ? G::Object::wrap<Widget>(top_level) : 0;
}

Gtk::Widget*
Gtk::Widget::get_ancestor(GType widget_type) const
{
	GtkWidget *ancestor = gtk_widget_get_ancestor(gtk_widget(), widget_type);
	return ancestor ? G::Object::wrap<Widget>(ancestor) : 0;
}

Gdk::Colormap*
Gtk::Widget::get_colormap() const
{
	return G::Object::wrap<Gdk::Colormap>(gtk_widget_get_colormap(gtk_widget()));
}

const Gdk::Visual*
Gtk::Widget::get_visual() const
{
	return G::Object::wrap<Gdk::Visual>(gtk_widget_get_visual(gtk_widget()));
}

Gdk::Screen* 
Gtk::Widget::get_screen() const
{
	return G::Object::wrap<Gdk::Screen>(gtk_widget_get_screen(gtk_widget()));
}

Gdk::Display*
Gtk::Widget::get_display() const
{
	return G::Object::wrap<Gdk::Display>(gtk_widget_get_display(gtk_widget()));
}

Gdk::Window*
Gtk::Widget::get_root_window() const
{
	return G::Object::wrap<Gdk::Window>(gtk_widget_get_root_window(gtk_widget()));
}

Gtk::Settings*
Gtk::Widget::get_settings() const
{
	return G::Object::wrap<Settings>(gtk_widget_get_settings(gtk_widget()));
}

Gtk::Clipboard*
Gtk::Widget::get_clipboard(Gdk::Atom selection) const
{
	return G::Object::wrap<Clipboard>(gtk_widget_get_clipboard(gtk_widget(), selection));
}

Atk::Object*
Gtk::Widget::get_accessible() const
{
	return G::Object::wrap<Atk::Object>(gtk_widget_get_accessible(gtk_widget()));
}

Gdk::Point
Gtk::Widget::get_pointer() const
{
	GdkPoint point;
	gtk_widget_get_pointer(gtk_widget(), &point.x, &point.y);
	return point;
}

bool
Gtk::Widget::is_ancestor(Widget *ancestor) const
{
	return gtk_widget_is_ancestor(gtk_widget(), ancestor->gtk_widget());
}

Gtk::Style*
Gtk::Widget::get_style() const
{
	return G::Object::wrap<Style>(gtk_widget_get_style(gtk_widget()));
}

Gtk::Style*
Gtk::Widget::rc_get_style() const
{
	return G::Object::wrap<Style>(gtk_rc_get_style(gtk_widget()));
}

Gtk::RcStyle*
Gtk::Widget::get_modifier_style() const
{
	return G::Object::wrap<RcStyle>(gtk_widget_get_modifier_style(gtk_widget()));
}

String
Gtk::Widget::get_composite_name() const
{
	char *name = gtk_widget_get_composite_name(gtk_widget());
	String s(name);
	g_free(name);
	return s;
}

Pango::Context*
Gtk::Widget::get_pango_context() const
{
	return G::Object::wrap<Pango::Context>(gtk_widget_get_pango_context(gtk_widget()));
}

const Gtk::Style*
Gtk::Widget::get_default_style()
{
	return G::Object::wrap<Style>(gtk_widget_get_default_style());
}

Gdk::Colormap*
Gtk::Widget::get_default_colormap()
{
	return G::Object::wrap<Gdk::Colormap>(gtk_widget_get_default_colormap());
}

const Gdk::Visual*
Gtk::Widget::get_default_visual()
{
	return G::Object::wrap<Gdk::Visual>(gtk_widget_get_default_visual());
}

void
Gtk::Widget::style_get_property(const char *property_name, G::Value& value)
{
	gtk_widget_style_get_property(gtk_widget(), property_name, value.g_value());
}

void
Gtk::Widget::style_get_property(const String& property_name, G::Value& value)
{
	gtk_widget_style_get_property(gtk_widget(), property_name.c_str(), value.g_value());
}

void 
Gtk::Widget::path(String& path, String& path_reversed) const
{
	unsigned int length;
	char *tmp_path = 0;
	char *tmp_path_reversed = 0;
	gtk_widget_path(gtk_widget(), &length, &tmp_path, &tmp_path_reversed);
	
	if (tmp_path)
	{
		path.assign(tmp_path, length);
		g_free(tmp_path);
	}
	
	if (tmp_path_reversed)
	{
		path_reversed.assign(tmp_path_reversed, length);
		g_free(tmp_path_reversed);
	}
}
	
void 
Gtk::Widget::class_path(String& path, String& path_reversed) const
{
	unsigned int length;
	char *tmp_path = 0;
	char *tmp_path_reversed = 0;
	gtk_widget_class_path(gtk_widget(), &length, &tmp_path, &tmp_path_reversed);
	
	if (tmp_path)
	{
		path.assign(tmp_path, length);
		g_free(tmp_path);
	}
	
	if (tmp_path_reversed)
	{
		path_reversed.assign(tmp_path_reversed, length);
		g_free(tmp_path_reversed);
	}
}
	
void 
Gtk::Widget::show(bool visible)
{
	visible ? show() : hide();
}

void
Gtk::Widget::queue_draw_area(const Gdk::Rectangle& rectangle)
{
	gtk_widget_queue_draw_area(gtk_widget(), rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height());
}

void
Gtk::Widget::size_request(Requisition *requisition)
{
	GtkRequisition tmp;
	gtk_widget_size_request(gtk_widget(), &tmp);
	if (requisition)
		requisition->set(tmp.width, tmp.height);
}

void
Gtk::Widget::size_allocate(const Allocation& allocation)
{
	gtk_widget_size_allocate(gtk_widget(), allocation.gtk_allocation());
}

void
Gtk::Widget::add_accelerator(const char *accel_signal, AccelGroup& accel_group, const AccelKey& accel_key)
{
	gtk_widget_add_accelerator(gtk_widget(), accel_signal, accel_group.gtk_accel_group(), accel_key.key(),
	                           (GdkModifierType)accel_key.mods(), (GtkAccelFlags)accel_key.flags());
}

void
Gtk::Widget::add_accelerator(const String& accel_signal, AccelGroup& accel_group, const AccelKey& accel_key)
{
	add_accelerator(accel_signal.c_str(), accel_group, accel_key);
}

bool
Gtk::Widget::remove_accelerator(AccelGroup& accel_group, const AccelKey& accel_key)
{
	return gtk_widget_remove_accelerator(gtk_widget(), accel_group.gtk_accel_group(), accel_key.key(),
	                                     (GdkModifierType)accel_key.mods());

}

void
Gtk::Widget::set_accel_path(const char *accel_path, AccelGroup& accel_group)
{
	gtk_widget_set_accel_path(gtk_widget(), accel_path, accel_group.gtk_accel_group());
}

void
Gtk::Widget::set_accel_path(const String& accel_path, AccelGroup& accel_group)
{
	set_accel_path(accel_path.c_str(), accel_group);
}

bool
Gtk::Widget::list_accel_closures(std::vector<GClosure*>& closures)
{
	g_return_val_if_fail(closures.empty(), false);
	GList *first = gtk_widget_list_accel_closures(gtk_widget());
	GList *next = first;

	while (next)
	{
		closures.push_back((GClosure*)next->data);
		next = g_list_next(next);
	}

	g_list_free(first);
	return !closures.empty();
}

bool
Gtk::Widget::can_activate_accel(const char *signal_name)
{
	g_return_val_if_fail(signal_name != 0, false);
	GSignalQuery query;
	g_signal_query(g_signal_lookup(signal_name, type()), &query);
	g_return_val_if_fail(query.signal_id != 0, false);
	return gtk_widget_can_activate_accel(gtk_widget(), query.signal_id);
}

bool
Gtk::Widget::can_activate_accel(const String& signal_name)
{
	return can_activate_accel(signal_name.c_str());
}

int
Gtk::Widget::send_expose(const Gdk::EventExpose& event)
{
	return gtk_widget_send_expose(gtk_widget(), event.gdk_event());
}

bool
Gtk::Widget::event(const Gdk::Event& event)
{
	return gtk_widget_event(gtk_widget(), event);
}

bool
Gtk::Widget::set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment)
{
	return gtk_widget_set_scroll_adjustments(gtk_widget(), *hadjustment, *vadjustment);
}

void
Gtk::Widget::reparent(Widget& new_parent)
{
	gtk_widget_reparent(gtk_widget(), new_parent.gtk_widget());
}

bool
Gtk::Widget::intersect(const Gdk::Rectangle& area, Gdk::Rectangle *intersection)
{
	return gtk_widget_intersect(gtk_widget(), area.gdk_rectangle(), *intersection);
}

Gdk::Rectangle
Gtk::Widget::intersect(const Gdk::Rectangle& area)
{
	GdkRectangle rectangle;
	gtk_widget_intersect(gtk_widget(), area.gdk_rectangle(), &rectangle);
	return rectangle;
}
	
Pointer<Gdk::Region>
Gtk::Widget::intersect(Gdk::Region& region)
{
	return new Gdk::Region(gtk_widget_region_intersect(gtk_widget(), region.gdk_region()), false);
}

void
Gtk::Widget::child_notify(const String& child_property)
{
	gtk_widget_child_notify(gtk_widget(), child_property.c_str());
}

void
Gtk::Widget::set_name(const String& name)
{
	gtk_widget_set_name(gtk_widget(), name.c_str());
}

void
Gtk::Widget::set_parent(Widget& parent)
{
	gtk_widget_set_parent(gtk_widget(), parent.gtk_widget());
}

void
Gtk::Widget::set_parent_window(Gdk::Window *parent_window)
{
	gtk_widget_set_parent_window(gtk_widget(), *parent_window);
}

void
Gtk::Widget::set_colormap(Gdk::Colormap& colormap)
{
	if (!is_realized())
		gtk_widget_set_colormap(gtk_widget(), colormap.gdk_colormap());
}

bool
Gtk::Widget::translate_coordinates(Widget &src_widget, int src_x, int src_y, int *dest_x, int *dest_y) const
{
	return gtk_widget_translate_coordinates(src_widget.gtk_widget(), gtk_widget(), src_x, src_y, dest_x, dest_y);
}

void
Gtk::Widget::set_style(Style& style)
{
	gtk_widget_set_style(gtk_widget(), style.gtk_style());
}

void
Gtk::Widget::modify_style(RcStyle& style)
{
	gtk_widget_modify_style(gtk_widget(), style.gtk_rc_style());
}

void
Gtk::Widget::modify_fg(StateType state, const Gdk::Color *color)
{
	gtk_widget_modify_fg(gtk_widget(), (GtkStateType)state, *color);
}

void
Gtk::Widget::modify_bg(StateType state, const Gdk::Color *color)
{
	gtk_widget_modify_bg(gtk_widget(), (GtkStateType)state, *color);
}

void
Gtk::Widget::modify_text(StateType state, const Gdk::Color *color)
{
 	gtk_widget_modify_text(gtk_widget(), (GtkStateType)state, *color);
}

void
Gtk::Widget::modify_base(StateType state, const Gdk::Color *color)
{
	gtk_widget_modify_base(gtk_widget(), (GtkStateType)state, *color);
}

void
Gtk::Widget::modify_font(const Pango::FontDescription *font_desc)
{
	gtk_widget_modify_font(gtk_widget(), *font_desc);
}

Pointer<Pango::Context>
Gtk::Widget::create_pango_context()
{
	return G::Object::wrap_new<Pango::Context>(gtk_widget_create_pango_context(gtk_widget()), true);
}

Pointer<Pango::Layout>
Gtk::Widget::create_pango_layout(const char *text)
{
	return G::Object::wrap_new<Pango::Layout>(gtk_widget_create_pango_layout(gtk_widget(), text), true);
}

Pointer<Pango::Layout>
Gtk::Widget::create_pango_layout(const String& text)
{
	return create_pango_layout(text.c_str());
}

Pointer<Gdk::Pixbuf>
Gtk::Widget::render_icon(const StockId& stock_id, IconSize size, const char *detail)
{
	GdkPixbuf *pixbuf = gtk_widget_render_icon(gtk_widget(), stock_id, (GtkIconSize)size, detail);
	return pixbuf ? G::Object::wrap<Gdk::Pixbuf>(pixbuf, true) : 0;
}

void
Gtk::Widget::set_composite_name(const String& name)
{
	gtk_widget_set_composite_name(gtk_widget(), name.c_str());
}

void
Gtk::Widget::push_colormap(Gdk::Colormap& cmap)
{
	gtk_widget_push_colormap(cmap.gdk_colormap());
}

void
Gtk::Widget::set_default_colormap(Gdk::Colormap *colormap)
{
	gtk_widget_set_default_colormap(*colormap);
}

void
Gtk::Widget::shape_combine_mask(const Gdk::Bitmap& shape_mask, int offset_x, int offset_y)
{
	gtk_widget_shape_combine_mask(gtk_widget(), shape_mask.gdk_bitmap(), offset_x, offset_y);
}

bool
Gtk::Widget::list_mnemonic_labels(std::vector<Widget*>& widgets)
{
	g_return_val_if_fail(widgets.empty(), false);
	GList *first = gtk_widget_list_mnemonic_labels(gtk_widget());
	GList *next = first;

	while (next)
	{
		widgets.push_back(G::Object::wrap<Widget>((GtkWidget*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !widgets.empty();
}
	
void 
Gtk::Widget::add_mnemonic_label(Widget& label)
{
	gtk_widget_add_mnemonic_label(gtk_widget(), label.gtk_widget());
}

void 
Gtk::Widget::remove_mnemonic_label(Widget& label)
{
	gtk_widget_remove_mnemonic_label(gtk_widget(), label.gtk_widget());
}

Gdk::GrabStatus
Gtk::Widget::pointer_grab(Gdk::EventMaskField event_mask, Widget *confine_to, Gdk::Cursor *cursor,
                          bool owner_events, unsigned int time)
{
	GdkWindow *window = confine_to ? confine_to->gtk_widget()->window : 0;
	return (Gdk::GrabStatus)gdk_pointer_grab(gtk_widget()->window, owner_events, (GdkEventMask)event_mask,
	                                         window, *cursor, time);
}

bool
Gtk::Widget::selection_owner_set(Gdk::Atom selection, unsigned int time, const Gdk::Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gtk_widget_get_display(gtk_widget());
	return gtk_selection_owner_set_for_display(tmp_display, gtk_widget(), selection, time);
}

void
Gtk::Widget::selection_add_target(Gdk::Atom selection, const TargetEntry& entry)
{
      gtk_selection_add_target(gtk_widget(), selection, gdk_atom_intern(entry.target(), FALSE), entry.info());
}

void
Gtk::Widget::selection_add_targets(Gdk::Atom selection, const std::vector<TargetEntry>& targets)
{
	g_return_if_fail(!targets.empty());
	int count = targets.size();
	GtkTargetEntry *tmp_targets = new GtkTargetEntry[count];

	int i = 0;
	while (i < count)
	{
		tmp_targets[i] = *(targets[i].gtk_target_entry());
		++i;
	}

	gtk_selection_add_targets(gtk_widget(), selection, tmp_targets, count);
	delete [] tmp_targets;
}

bool
Gtk::Widget::selection_owner_unset(Gdk::Atom selection, unsigned int time, const Gdk::Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return gtk_selection_owner_set_for_display(tmp_display, 0, selection, time);
}

void
Gtk::Widget::drag_get_data(DragContext& context, Gdk::Atom target, unsigned int time)
{
	gtk_drag_get_data(gtk_widget(), context.gdk_drag_context(), target, time);
}

void
Gtk::Widget::drag_dest_set(Gtk::DestDefaultsField flags, const TargetEntry& target, Gdk::DragActionField actions)
{
	gtk_drag_dest_set(gtk_widget(), (GtkDestDefaults)flags, target.gtk_target_entry(), 1, (GdkDragAction)actions);
}

void
Gtk::Widget::drag_dest_set(Gtk::DestDefaultsField flags, const std::vector<TargetEntry>& targets, Gdk::DragActionField actions)
{
	g_return_if_fail (!targets.empty());
	int count = targets.size ();
	GtkTargetEntry *tmp_targets = new GtkTargetEntry[count];

	int i = 0;
	while (i < count)
	{
		tmp_targets[i] = *(targets[i].gtk_target_entry());
		++i;
	}

	gtk_drag_dest_set(gtk_widget(), (GtkDestDefaults)flags, tmp_targets, count, (GdkDragAction)actions);
	delete [] tmp_targets;
}

void
Gtk::Widget::drag_dest_set_proxy(Gdk::Window *proxy_window, Gdk::DragProtocol protocol, bool use_coordinates)
{
	gtk_drag_dest_set_proxy(gtk_widget(), *proxy_window, (GdkDragProtocol)protocol, use_coordinates);
}

Gdk::Atom
Gtk::Widget::drag_dest_find_target(const DragContext& context, const TargetList *target_list)
{
	return gtk_drag_dest_find_target(gtk_widget(), context.gdk_drag_context(), *target_list);
}

Gtk::TargetList*
Gtk::Widget::drag_dest_get_target_list() const
{
	GtkTargetList *target_list = gtk_drag_dest_get_target_list(gtk_widget());
	return target_list ? new TargetList(target_list) : 0;
}

void
Gtk::Widget::drag_dest_set_target_list(TargetList *target_list)
{
	gtk_drag_dest_set_target_list(gtk_widget(), *target_list);
}

Gtk::DragContext*
Gtk::Widget::drag_source_begin(const TargetList& targets, Gdk::DragActionField actions, int button, const Gdk::Event& event)
{
	GdkDragContext *dc = gtk_drag_begin(gtk_widget(), targets.gtk_target_list(), (GdkDragAction)actions, button, event.gdk_event());
	return dc ? G::Object::wrap<DragContext>(dc) : 0;
}

void
Gtk::Widget::drag_source_set(Gdk::ModifierTypeField start_button_mask, const TargetEntry& target, Gdk::DragActionField actions)
{
	gtk_drag_source_set(gtk_widget(), (GdkModifierType)start_button_mask, target.gtk_target_entry(), 1, (GdkDragAction)actions);
}

void
Gtk::Widget::drag_source_set(Gdk::ModifierTypeField start_button_mask, const std::vector<TargetEntry>& targets, Gdk::DragActionField actions)
{
	g_return_if_fail (!targets.empty ());
	int count = targets.size ();
	GtkTargetEntry *tmp_targets = new GtkTargetEntry[count];

	int i = 0;
	while (i < count)
	{
		tmp_targets[i] = *(targets[i].gtk_target_entry());
		++i;
	}

	gtk_drag_source_set(gtk_widget(), (GdkModifierType)start_button_mask, tmp_targets, count, (GdkDragAction)actions);
	delete [] tmp_targets;
}

Gtk::TargetList*
Gtk::Widget::drag_source_get_target_list() const
{
	GtkTargetList *target_list = gtk_drag_source_get_target_list(gtk_widget());
	return target_list ? new TargetList(target_list) : 0;
}

void
Gtk::Widget::drag_source_set_target_list(TargetList *target_list)
{
	gtk_drag_source_set_target_list(gtk_widget(), *target_list);
}

void
Gtk::Widget::drag_source_set_icon(Gdk::Colormap *colormap, Gdk::Pixmap *pixmap, Gdk::Bitmap *mask)
{
	gtk_drag_source_set_icon(gtk_widget(), *colormap, *pixmap, *mask);
}

void
Gtk::Widget::drag_source_set_icon_pixbuf(Gdk::Pixbuf& pixbuf)
{
	gtk_drag_source_set_icon_pixbuf(gtk_widget(), pixbuf.gdk_pixbuf());
}

void
Gtk::Widget::drag_source_set_icon_stock(const StockId& stock_id)
{
	gtk_drag_source_set_icon_stock(gtk_widget(), stock_id);
}

/*  Gtk::WidgetClass
 */

void
Gtk::WidgetClass::init(GtkWidgetClass *g_class)
{
	ObjectClass::init((GtkObjectClass*)g_class);
	g_class->show = &show_proxy;
	g_class->hide = &hide_proxy;
	g_class->map = &map_proxy;
	g_class->unmap = &unmap_proxy;
	g_class->realize = &realize_proxy;
	g_class->unrealize = &unrealize_proxy;
	g_class->size_request = &size_request_proxy;
	g_class->size_allocate = &size_allocate_proxy;
	g_class->state_changed = &state_changed_proxy;
	g_class->parent_set = &parent_set_proxy;
	g_class->hierarchy_changed = &hierarchy_changed_proxy;
	g_class->style_set = &style_set_proxy;
	g_class->direction_changed = &direction_changed_proxy;
	g_class->grab_notify = &grab_notify_proxy;
	g_class->child_notify = &child_notify_proxy;
	g_class->mnemonic_activate = &mnemonic_activate_proxy;
	g_class->grab_focus = &grab_focus_proxy;
	g_class->focus = &focus_proxy;
	g_class->screen_changed = &screen_changed_proxy;
	g_class->can_activate_accel = &can_activate_accel_proxy;
	g_class->selection_get = &selection_get_proxy;
	g_class->selection_received = &selection_received_proxy;
	g_class->drag_begin = &drag_begin_proxy;
	g_class->drag_end = &drag_end_proxy;
	g_class->drag_data_get = &drag_data_get_proxy;
	g_class->drag_data_delete = &drag_data_delete_proxy;
	g_class->drag_leave = &drag_leave_proxy;
	g_class->drag_motion = &drag_motion_proxy;
	g_class->drag_drop = &drag_drop_proxy;
	g_class->drag_data_received = &drag_data_received_proxy;
	g_class->event = &event_proxy;
	g_class->button_press_event = &button_press_event_proxy;
	g_class->button_release_event = &button_release_event_proxy;
	g_class->scroll_event = &scroll_event_proxy;
	g_class->motion_notify_event = &motion_notify_event_proxy;
	g_class->delete_event = &delete_event_proxy;
	g_class->destroy_event = &destroy_event_proxy;
	g_class->expose_event = &expose_event_proxy;
	g_class->key_press_event = &key_press_event_proxy;
	g_class->key_release_event = &key_release_event_proxy;
	g_class->enter_notify_event = &enter_notify_event_proxy;
	g_class->leave_notify_event = &leave_notify_event_proxy;
	g_class->configure_event = &configure_event_proxy;
	g_class->focus_in_event = &focus_in_event_proxy;
	g_class->focus_out_event = &focus_out_event_proxy;
	g_class->map_event = &map_event_proxy;
	g_class->unmap_event = &unmap_event_proxy;
	g_class->property_notify_event = &property_notify_event_proxy;
	g_class->selection_clear_event = &selection_clear_event_proxy;
	g_class->selection_request_event = &selection_request_event_proxy;
	g_class->selection_notify_event = &selection_notify_event_proxy;
	g_class->proximity_in_event = &proximity_in_event_proxy;
	g_class->proximity_out_event = &proximity_out_event_proxy;
	g_class->visibility_notify_event = &visibility_notify_event_proxy;
	g_class->client_event = &client_event_proxy;
	g_class->no_expose_event = &no_expose_event_proxy;
	g_class->window_state_event = &window_state_event_proxy;
}

GtkWidgetClass*
Gtk::WidgetClass::get_parent_class(void *instance)
{
	return static_cast<GtkWidgetClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::WidgetClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_WIDGET, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::WidgetClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::WidgetClass::show_proxy(GtkWidget *widget)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_show();
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->show)
			g_class->show(widget);
	}
}

void
Gtk::WidgetClass::hide_proxy(GtkWidget *widget)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_hide();
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->hide)
			g_class->hide(widget);
	}
}

void
Gtk::WidgetClass::map_proxy(GtkWidget *widget)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_map();
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->map)
			g_class->map(widget);
	}
}

void
Gtk::WidgetClass::unmap_proxy(GtkWidget *widget)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_unmap();
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->unmap)
			g_class->unmap(widget);
	}
}

void
Gtk::WidgetClass::realize_proxy(GtkWidget *widget)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_realize();
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->realize)
			g_class->realize(widget);
	}
}

void
Gtk::WidgetClass::unrealize_proxy(GtkWidget *widget)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_unrealize();
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->unrealize)
			g_class->unrealize(widget);
	}
}

void
Gtk::WidgetClass::size_request_proxy(GtkWidget *widget, GtkRequisition *requisition)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Requisition tmp_requisition;
		static_cast<WidgetSignals*>(ptr)->on_size_request(&tmp_requisition);
		*requisition = *tmp_requisition;
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->size_request)
			g_class->size_request(widget, requisition);
	}
}

void
Gtk::WidgetClass::size_allocate_proxy(GtkWidget *widget, GtkAllocation *allocation)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Allocation tmp_allocation(*allocation);
		static_cast<WidgetSignals*>(ptr)->on_size_allocate(tmp_allocation);
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->size_allocate)
			g_class->size_allocate(widget, allocation);
	}
}

void
Gtk::WidgetClass::state_changed_proxy(GtkWidget *widget, GtkStateType previous_state)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_state_changed((StateType)previous_state);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->state_changed)
			g_class->state_changed(widget, previous_state);
	}
}

void
Gtk::WidgetClass::parent_set_proxy(GtkWidget *widget, GtkWidget *previous_parent)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_parent_set(G::Object::wrap<Widget>(previous_parent));
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->parent_set)
			g_class->parent_set(widget, previous_parent);
	}
}

void
Gtk::WidgetClass::hierarchy_changed_proxy(GtkWidget *widget, GtkWidget *previous_toplevel)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_hierarchy_changed(G::Object::wrap<Widget>(previous_toplevel));
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->hierarchy_changed)
			g_class->hierarchy_changed(widget, previous_toplevel);
	}
}

void
Gtk::WidgetClass::style_set_proxy(GtkWidget *widget, GtkStyle *previous_style)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr && static_cast<Widget*>(G::Object::pointer((GObject*)widget))->is_realized())
		static_cast<WidgetSignals*>(ptr)->on_style_set(G::Object::wrap<Style>(previous_style));
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->style_set)
			g_class->style_set(widget, previous_style);
	}
}

void
Gtk::WidgetClass::direction_changed_proxy(GtkWidget *widget, GtkTextDirection previous_direction)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_direction_changed((TextDirection)previous_direction);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->direction_changed)
			g_class->direction_changed(widget, previous_direction);
	}
}

void
Gtk::WidgetClass::grab_notify_proxy(GtkWidget *widget, gboolean was_grabbed)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_grab_notify(was_grabbed);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->grab_notify)
			g_class->grab_notify(widget, was_grabbed);
	}
}

void
Gtk::WidgetClass::child_notify_proxy(GtkWidget *widget, GParamSpec *pspec)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_child_notify(pspec);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->child_notify)
			g_class->child_notify(widget, pspec);
	}
}

gboolean
Gtk::WidgetClass::mnemonic_activate_proxy(GtkWidget *widget, gboolean group_cycling)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		result = static_cast<WidgetSignals*>(ptr)->on_mnemonic_activate(group_cycling);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->mnemonic_activate)
			result = g_class->mnemonic_activate(widget, group_cycling);
	}
	return result;
}

void
Gtk::WidgetClass::grab_focus_proxy(GtkWidget *widget)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_grab_focus();
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->grab_focus)
			g_class->grab_focus(widget);
	}
}

gboolean
Gtk::WidgetClass::focus_proxy(GtkWidget *widget, GtkDirectionType direction)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		result = static_cast<WidgetSignals*>(ptr)->on_focus((DirectionType)direction);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->focus)
			result = g_class->focus(widget, direction);
	}
	return result;
}

void
Gtk::WidgetClass::screen_changed_proxy(GtkWidget *widget, GdkScreen *previous_screen)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_screen_changed(G::Object::wrap<Gdk::Screen>(previous_screen));
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->screen_changed)
			g_class->screen_changed(widget, previous_screen);
	}
}

gboolean
Gtk::WidgetClass::can_activate_accel_proxy(GtkWidget *widget, guint signal_id)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		result = static_cast<WidgetSignals*>(ptr)->on_can_activate_accel(signal_id);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->can_activate_accel)
			result = g_class->can_activate_accel(widget, signal_id);
	}
	return result;
}

gboolean
Gtk::WidgetClass::event_proxy(GtkWidget	*widget, GdkEvent *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event(event);
		result = static_cast<WidgetSignals*>(ptr)->on_event(tmp_event);
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->event)
			result = g_class->event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::button_press_event_proxy(GtkWidget *widget, GdkEventButton *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_button_press_event(*tmp_event.button());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->button_press_event)
			result = g_class->button_press_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::button_release_event_proxy(GtkWidget *widget, GdkEventButton *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_button_release_event(*tmp_event.button());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->button_release_event)
			result = g_class->button_release_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::scroll_event_proxy(GtkWidget *widget, GdkEventScroll *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_scroll_event(*tmp_event.scroll());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->scroll_event)
			result = g_class->scroll_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::motion_notify_event_proxy(GtkWidget *widget, GdkEventMotion *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_motion_notify_event(*tmp_event.motion());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->motion_notify_event)
			result = g_class->motion_notify_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::delete_event_proxy(GtkWidget *widget, GdkEventAny *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_delete_event(*tmp_event.any());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->delete_event)
			result = g_class->delete_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::destroy_event_proxy(GtkWidget *widget, GdkEventAny *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_destroy_event(*tmp_event.any());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->destroy_event)
			result = g_class->destroy_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::expose_event_proxy(GtkWidget *widget, GdkEventExpose *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_expose_event(*tmp_event.expose());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->expose_event)
			result = g_class->expose_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::key_press_event_proxy(GtkWidget *widget, GdkEventKey *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_key_press_event(*tmp_event.key());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->key_press_event)
			result = g_class->key_press_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::key_release_event_proxy(GtkWidget *widget, GdkEventKey *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_key_release_event(*tmp_event.key());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->key_release_event)
			result = g_class->key_release_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::enter_notify_event_proxy(GtkWidget *widget, GdkEventCrossing *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_enter_notify_event(*tmp_event.crossing());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->enter_notify_event)
			result = g_class->enter_notify_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::leave_notify_event_proxy(GtkWidget *widget, GdkEventCrossing *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_leave_notify_event(*tmp_event.crossing());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->leave_notify_event)
			result = g_class->leave_notify_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::configure_event_proxy(GtkWidget *widget, GdkEventConfigure *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_configure_event(*tmp_event.configure());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->configure_event)
			result = g_class->configure_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::focus_in_event_proxy(GtkWidget *widget, GdkEventFocus *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_focus_in_event(*tmp_event.focus_change());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->focus_in_event)
			result = g_class->focus_in_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::focus_out_event_proxy(GtkWidget *widget, GdkEventFocus *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_focus_out_event(*tmp_event.focus_change());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->focus_out_event)
			result = g_class->focus_out_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::map_event_proxy(GtkWidget	*widget, GdkEventAny *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_map_event(*tmp_event.any());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->map_event)
			result = g_class->map_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::unmap_event_proxy(GtkWidget *widget, GdkEventAny *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_unmap_event(*tmp_event.any());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->unmap_event)
			result = g_class->unmap_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::property_notify_event_proxy(GtkWidget *widget, GdkEventProperty *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_property_notify_event(*tmp_event.property());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->property_notify_event)
			result = g_class->property_notify_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::selection_clear_event_proxy(GtkWidget *widget, GdkEventSelection *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_selection_clear_event(*tmp_event.selection());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->selection_clear_event)
			result = g_class->selection_clear_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::selection_request_event_proxy(GtkWidget *widget, GdkEventSelection *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_selection_request_event(*tmp_event.selection());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->selection_request_event)
			result = g_class->selection_request_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::selection_notify_event_proxy(GtkWidget *widget, GdkEventSelection *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_selection_notify_event(*tmp_event.selection());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->selection_notify_event)
			result = g_class->selection_notify_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::proximity_in_event_proxy(GtkWidget *widget, GdkEventProximity *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_proximity_in_event(*tmp_event.proximity());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->proximity_in_event)
			result = g_class->proximity_in_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::proximity_out_event_proxy(GtkWidget *widget, GdkEventProximity *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_proximity_out_event(*tmp_event.proximity());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->proximity_out_event)
			result = g_class->proximity_out_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::visibility_notify_event_proxy(GtkWidget *widget, GdkEventVisibility *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_visibility_notify_event(*tmp_event.visibility());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->visibility_notify_event)
			result = g_class->visibility_notify_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::client_event_proxy(GtkWidget *widget, GdkEventClient *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_client_event(*tmp_event.client());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->client_event)
			result = g_class->client_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::no_expose_event_proxy(GtkWidget *widget, GdkEventAny *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_no_expose_event(*tmp_event.any());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->no_expose_event)
			result = g_class->no_expose_event(widget, event);
	}
	return result;
}

gboolean
Gtk::WidgetClass::window_state_event_proxy(GtkWidget *widget, GdkEventWindowState *event)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gdk::Event tmp_event((GdkEvent*)event);
		result = static_cast<WidgetSignals*>(ptr)->on_window_state_event(*tmp_event.window_state());
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->window_state_event)
			result = g_class->window_state_event(widget, event);
	}
	return result;
}

void
Gtk::WidgetClass::selection_get_proxy(GtkWidget *widget, GtkSelectionData *selection_data, guint info, guint time)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gtk::SelectionData tmp_selection_data(selection_data);
		static_cast<WidgetSignals*>(ptr)->on_selection_get(tmp_selection_data, info, time);
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->selection_get)
			g_class->selection_get(widget, selection_data, info, time);
	}
}

void
Gtk::WidgetClass::selection_received_proxy(GtkWidget *widget, GtkSelectionData *selection_data, guint time)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gtk::SelectionData tmp_selection_data(selection_data);
		static_cast<WidgetSignals*>(ptr)->on_selection_received(tmp_selection_data, time);
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->selection_received)
			g_class->selection_received(widget, selection_data, time);
	}
}

void
Gtk::WidgetClass::drag_begin_proxy(GtkWidget *widget, GdkDragContext *context)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_drag_begin(*G::Object::wrap<DragContext>(context));
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->drag_begin)
			g_class->drag_begin(widget, context);
	}
}

void
Gtk::WidgetClass::drag_end_proxy(GtkWidget *widget, GdkDragContext *context)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_drag_end(*G::Object::wrap<DragContext>(context));
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->drag_end)
			g_class->drag_end(widget, context);
	}
}

void
Gtk::WidgetClass::drag_data_get_proxy(GtkWidget *widget, GdkDragContext *context, GtkSelectionData *selection_data, guint info, guint time)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gtk::SelectionData tmp_selection_data(selection_data);
		static_cast<WidgetSignals*>(ptr)->on_drag_data_get(*G::Object::wrap<DragContext>(context), tmp_selection_data, info, time);
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->drag_data_get)
			g_class->drag_data_get(widget, context, selection_data, info, time);
	}
}

void
Gtk::WidgetClass::drag_data_delete_proxy(GtkWidget *widget, GdkDragContext *context)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_drag_data_delete(*G::Object::wrap<DragContext>(context));
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->drag_data_delete)
			g_class->drag_data_delete(widget, context);
	}
}

void
Gtk::WidgetClass::drag_leave_proxy(GtkWidget *widget, GdkDragContext *context, guint time)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		static_cast<WidgetSignals*>(ptr)->on_drag_leave(*G::Object::wrap<DragContext>(context), time);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->drag_leave)
			g_class->drag_leave(widget, context, time);
	}
}

gboolean
Gtk::WidgetClass::drag_motion_proxy(GtkWidget *widget, GdkDragContext *context, gint x, gint y, guint time)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		result = static_cast<WidgetSignals*>(ptr)->on_drag_motion(*G::Object::wrap<DragContext>(context),x, y, time);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->drag_motion)
			result = g_class->drag_motion(widget, context, x, y, time);
	}
	return result;
}

gboolean
Gtk::WidgetClass::drag_drop_proxy(GtkWidget *widget, GdkDragContext *context, gint x, gint y, guint time)
{
	gboolean result = FALSE;
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
		result = static_cast<WidgetSignals*>(ptr)->on_drag_drop(*G::Object::wrap<DragContext>(context), x, y, time);
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->drag_drop)
			result = g_class->drag_drop(widget, context, x, y, time);
	}
	return result;
}

void
Gtk::WidgetClass::drag_data_received_proxy(GtkWidget *widget, GdkDragContext *context, gint x, gint y, GtkSelectionData *selection_data, guint info, guint time)
{
	void *ptr = g_object_get_qdata((GObject*)widget, G::ObjectSignals::quark());
	if (ptr)
	{
		Gtk::SelectionData tmp_selection_data(selection_data);
		static_cast<WidgetSignals*>(ptr)->on_drag_data_received(*G::Object::wrap<DragContext>(context),
		                                                        x, y, tmp_selection_data, info, time);
	}
	else
	{
		GtkWidgetClass *g_class = get_parent_class(widget);
		if (g_class && g_class->drag_data_received)
			g_class->drag_data_received(widget, context, x, y, selection_data, info, time);
	}
}

/*  Gtk::Widget signals
 */

const Gtk::Widget::ShowSignalType Gtk::Widget::show_signal("show", (GCallback)&G::Marshal::void_callback);

const Gtk::Widget::HideSignalType Gtk::Widget::hide_signal("hide", (GCallback)&G::Marshal::void_callback);

const Gtk::Widget::MapSignalType Gtk::Widget::map_signal("map", (GCallback)&G::Marshal::void_callback);

const Gtk::Widget::UnmapSignalType Gtk::Widget::unmap_signal("unmap", (GCallback)&G::Marshal::void_callback);

const Gtk::Widget::RealizeSignalType Gtk::Widget::realize_signal("realize", (GCallback)&G::Marshal::void_callback);

const Gtk::Widget::UnrealizeSignalType Gtk::Widget::unrealize_signal("unrealize", (GCallback)&G::Marshal::void_callback);

const Gtk::Widget::SizeRequestSignalType Gtk::Widget::size_request_signal("size_request", (GCallback)&Marshal::void_requistion_callback);

const Gtk::Widget::SizeAllocateSignalType Gtk::Widget::size_allocate_signal("size_allocate", (GCallback)&Marshal::void_allocation_callback);

const Gtk::Widget::StateChangedSignalType Gtk::Widget::state_changed_signal("state_changed", (GCallback)&Marshal::void_statetype_callback);

const Gtk::Widget::ParentSetSignalType Gtk::Widget::parent_set_signal("parent_set", (GCallback)&Marshal::void_widget_callback1);

const Gtk::Widget::HierarchyChangedSignalType Gtk::Widget::hierarchy_changed_signal("hierarchy_changed", (GCallback)&Marshal::void_widget_callback1);

const Gtk::Widget::StyleSetSignalType Gtk::Widget::style_set_signal("style_set", (GCallback)&Marshal::void_style_callback);

const Gtk::Widget::DirectionChangedSignalType Gtk::Widget::direction_changed_signal("direction_changed", (GCallback)&Marshal::void_textdirection_callback);

const Gtk::Widget::GrabNotifySignalType Gtk::Widget::grab_notify_signal("grab_notify", (GCallback)&G::Marshal::void_bool_callback);

const Gtk::Widget::ChildNotifySignalType Gtk::Widget::child_notify_signal("child_notify", (GCallback)&Marshal::void_gparamspec_callback);

const Gtk::Widget::MnemonicActivateSignalType Gtk::Widget::mnemonic_activate_signal("mnemonic_activate", (GCallback)&Marshal::bool_bool_callback);

const Gtk::Widget::GrabFocusSignalType Gtk::Widget::grab_focus_signal("grab_focus", (GCallback)&G::Marshal::void_callback);

const Gtk::Widget::FocusSignalType Gtk::Widget::focus_signal("focus", (GCallback)&Marshal::bool_directiontype_callback);

const Gtk::Widget::AccelClosuresChangedSignalType Gtk::Widget::accel_closures_changed_signal("accel_closures_changed", (GCallback)&G::Marshal::void_callback);

const Gtk::Widget::ScreenChangedSignalType Gtk::Widget::screen_changed_signal("screen_changed", (GCallback)&Marshal::void_gdkscreen_callback);

const Gtk::Widget::CanActivateAccelSignalType Gtk::Widget::can_activate_accel_signal("can_activate_accel", (GCallback)&Marshal::bool_uint_callback);

const Gtk::Widget::SelectionGetSignalType Gtk::Widget::selection_get_signal("selection_get", (GCallback)&Marshal::void_selectiondata_uint_uint_callback);

const Gtk::Widget::SelectionReceivedSignalType Gtk::Widget::selection_received_signal("selection_received", (GCallback)&Marshal::void_selectiondata_uint_callback);

const Gtk::Widget::DragBeginSignalType Gtk::Widget::drag_begin_signal("drag_begin", (GCallback)&Marshal::void_dragcontext_callback);

const Gtk::Widget::DragEndSignalType Gtk::Widget::drag_end_signal("drag_end", (GCallback)&Marshal::void_dragcontext_callback);

const Gtk::Widget::DragDataGetSignalType Gtk::Widget::drag_data_get_signal("drag_data_get", (GCallback)&Marshal::void_dragcontext_selectiondata_uint_uint_callback);

const Gtk::Widget::DragDataDeleteSignalType Gtk::Widget::drag_data_delete_signal("drag_data_delete", (GCallback)&Marshal::void_dragcontext_callback);

const Gtk::Widget::DragLeaveSignalType Gtk::Widget::drag_leave_signal("drag_leave", (GCallback)&Marshal::void_dragcontext_uint_callback);

const Gtk::Widget::DragMotionSignalType Gtk::Widget::drag_motion_signal("drag_motion", (GCallback)&Marshal::bool_dragcontext_int_int_uint_callback);

const Gtk::Widget::DragDropSignalType Gtk::Widget::drag_drop_signal("drag_drop", (GCallback)&Marshal::bool_dragcontext_int_int_uint_callback);

const Gtk::Widget::DragDataReceivedSignalType Gtk::Widget::drag_data_received_signal("drag_data_received", (GCallback)&Marshal::void_dragcontext_int_int_selectiondata_uint_uint_callback);

const Gtk::Widget::EventSignalType Gtk::Widget::event_signal("event", (GCallback)&Marshal::bool_event_callback);

const Gtk::Widget::EventAfterSignalType Gtk::Widget::event_after_signal("event-after", (GCallback)&Marshal::void_event_callback);

const Gtk::Widget::ButtonPressEventSignalType Gtk::Widget::button_press_event_signal("button_press_event", (GCallback)&Marshal::bool_eventbutton_callback);

const Gtk::Widget::ButtonReleaseEventSignalType Gtk::Widget::button_release_event_signal("button_release_event", (GCallback)&Marshal::bool_eventbutton_callback);

const Gtk::Widget::ScrollEventSignalType Gtk::Widget::scroll_event_signal("scroll_event", (GCallback)&Marshal::bool_eventscroll_callback);

const Gtk::Widget::MotionNotifyEventSignalType Gtk::Widget::motion_notify_event_signal("motion_notify_event", (GCallback)&Marshal::bool_eventmotion_callback);

const Gtk::Widget::DeleteEventSignalType Gtk::Widget::delete_event_signal("delete_event", (GCallback)&Marshal::bool_event_callback);

const Gtk::Widget::DestroyEventSignalType Gtk::Widget::destroy_event_signal("destroy_event", (GCallback)&Marshal::bool_eventany_callback);

const Gtk::Widget::ExposeEventSignalType Gtk::Widget::expose_event_signal("expose_event", (GCallback)&Marshal::bool_eventexpose_callback);

const Gtk::Widget::KeyPressEventSignalType Gtk::Widget::key_press_event_signal("key_press_event", (GCallback)&Marshal::bool_eventkey_callback);

const Gtk::Widget::KeyReleaseEventSignalType Gtk::Widget::key_release_event_signal("key_release_event", (GCallback)&Marshal::bool_eventkey_callback);

const Gtk::Widget::EnterNotifyEventSignalType Gtk::Widget::enter_notify_event_signal("enter_notify_event", (GCallback)&Marshal::bool_eventcrossing_callback);

const Gtk::Widget::LeaveNotifyEventSignalType Gtk::Widget::leave_notify_event_signal("leave_notify_event", (GCallback)&Marshal::bool_eventcrossing_callback);

const Gtk::Widget::ConfigureEventSignalType Gtk::Widget::configure_event_signal("configure_event", (GCallback)&Marshal::bool_eventconfigure_callback);

const Gtk::Widget::FocusInEventSignalType Gtk::Widget::focus_in_event_signal("focus_in_event", (GCallback)&Marshal::bool_eventfocus_callback);

const Gtk::Widget::FocusOutEventSignalType Gtk::Widget::focus_out_event_signal("focus_out_event", (GCallback)&Marshal::bool_eventfocus_callback);

const Gtk::Widget::MapEventSignalType Gtk::Widget::map_event_signal("map_event", (GCallback)&Marshal::bool_eventany_callback);

const Gtk::Widget::UnmapEventSignalType Gtk::Widget::unmap_event_signal("unmap_event", (GCallback)&Marshal::bool_eventany_callback);

const Gtk::Widget::PropertyNotifyEventSignalType Gtk::Widget::property_notify_event_signal("property_notify_event", (GCallback)&Marshal::bool_eventproperty_callback);

const Gtk::Widget::SelectionClearEventSignalType Gtk::Widget::selection_clear_event_signal("selection_clear_event", (GCallback)&Marshal::bool_eventselection_callback);

const Gtk::Widget::SelectionRequestEventSignalType Gtk::Widget::selection_request_event_signal("selection_request_event", (GCallback)&Marshal::bool_eventselection_callback);

const Gtk::Widget::SelectionNotifyEventSignalType Gtk::Widget::selection_notify_event_signal("selection_notify_event", (GCallback)&Marshal::bool_eventselection_callback);

const Gtk::Widget::ProximityInEventSignalType Gtk::Widget::proximity_in_event_signal("proximity_in_event", (GCallback)&Marshal::bool_eventproximity_callback);

const Gtk::Widget::ProximityOutEventSignalType Gtk::Widget::proximity_out_event_signal("proximity_out_event", (GCallback)&Marshal::bool_eventproximity_callback);

const Gtk::Widget::VisibilityNotifyEventSignalType Gtk::Widget::visibility_notify_event_signal("visibility_notify_event", (GCallback)&Marshal::bool_eventvisibility_callback);

const Gtk::Widget::ClientEventSignalType Gtk::Widget::client_event_signal("client_event", (GCallback)&Marshal::bool_eventclient_callback);

const Gtk::Widget::NoExposeEventSignalType Gtk::Widget::no_expose_event_signal("no_expose_event", (GCallback)&Marshal::bool_eventany_callback);

const Gtk::Widget::WindowStateEventSignalType Gtk::Widget::window_state_event_signal("window_state_event", (GCallback)&Marshal::bool_eventwindowstate_callback);

