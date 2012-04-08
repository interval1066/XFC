/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  textview.cc - GtkTextView C++ wrapper implementation
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
 
#include "textview.hh"
#include "textviewsignals.hh"
#include "menu.hh"
#include "private/marshal.hh"
#include "private/textviewclass.hh"
#include "../gdk/window.hh"
#include "../pango/tabs.hh"

using namespace Xfc;

/*  Gtk::TextView
 */

Gtk::TextView::TextView(GtkTextView *text_view, bool owns_reference)
: Container((GtkContainer*)text_view, owns_reference)
{
}

Gtk::TextView::TextView()
: Container((GtkContainer*)TextViewClass::create())
{
}

Gtk::TextView::TextView(TextBuffer& buffer)
: Container((GtkContainer*)TextViewClass::create())
{
	set_buffer(&buffer);
}

Gtk::TextView::~TextView() 
{
}

Gtk::TextBuffer*
Gtk::TextView::get_buffer() const
{
	return G::Object::wrap<TextBuffer>(gtk_text_view_get_buffer(gtk_text_view()));
}

void
Gtk::TextView::get_visible_rect(Gdk::Rectangle& visible_rect)
{
	gtk_text_view_get_visible_rect(gtk_text_view(), visible_rect.gdk_rectangle());
}

Gdk::Rectangle
Gtk::TextView::get_visible_rect() const
{
	GdkRectangle rectangle;
	gtk_text_view_get_visible_rect(gtk_text_view(), &rectangle);
	return rectangle;
}

void
Gtk::TextView::get_iter_location(const TextIter& iter, Gdk::Rectangle& location)
{
	gtk_text_view_get_iter_location(gtk_text_view(), iter.gtk_text_iter(), location.gdk_rectangle());
}

Gdk::Rectangle
Gtk::TextView::get_iter_location(const TextIter& iter) const
{
	GdkRectangle rectangle;
	gtk_text_view_get_iter_location(gtk_text_view(), iter.gtk_text_iter(), &rectangle);
	return rectangle;
}

Gtk::TextIter
Gtk::TextView::get_iter_at_location(int x, int y) const
{
	GtkTextIter iter;
	gtk_text_view_get_iter_at_location(gtk_text_view(), &iter, x, y);
	return TextIter(&iter, true);
}

Gtk::TextIter 
Gtk::TextView::get_iter_at_position(int *trailing, int x, int y)
{
	GtkTextIter iter;
	gtk_text_view_get_iter_at_position(gtk_text_view(), &iter, trailing, x, y);
	return TextIter(&iter, true);
}
	
void
Gtk::TextView::get_line_yrange(const TextIter& iter, int *y, int *height) const
{
	gtk_text_view_get_line_yrange(gtk_text_view(), iter.gtk_text_iter(), y, height);
}

int
Gtk::TextView::get_line_y(const TextIter& iter) const
{
	int y;
	gtk_text_view_get_line_yrange(gtk_text_view(), iter.gtk_text_iter(), &y, 0);
	return y;
}

int
Gtk::TextView::get_line_height(const TextIter& iter) const
{
	int height;
	gtk_text_view_get_line_yrange(gtk_text_view(), iter.gtk_text_iter(), 0, &height);
	return height;
}

void
Gtk::TextView::get_line_at_y(TextIter& target_iter, int y, int *line_top) const
{
	gtk_text_view_get_line_at_y(gtk_text_view(), target_iter.gtk_text_iter(), y, line_top);
}

Gtk::TextIter
Gtk::TextView::get_line_at_y(int y) const
{
	GtkTextIter iter;
	gtk_text_view_get_line_at_y(gtk_text_view(), &iter, y, 0);
	return TextIter(&iter, true);
}

Gdk::Window*
Gtk::TextView::get_window(TextWindowType window_type) const
{
	return G::Object::wrap<Gdk::Window>(gtk_text_view_get_window(gtk_text_view(), (GtkTextWindowType)window_type));
}

Gtk::TextWindowType
Gtk::TextView::get_window_type(const Gdk::Window& window) const
{
	return (TextWindowType)gtk_text_view_get_window_type(gtk_text_view(), window.gdk_window());
}

Pointer<Pango::TabArray>
Gtk::TextView::get_tabs() const
{
	return G::Boxed::wrap<Pango::TabArray>(PANGO_TYPE_TAB_ARRAY, gtk_text_view_get_tabs(gtk_text_view()), false);
}

Pointer<Gtk::TextAttributes>
Gtk::TextView::get_default_attributes() const
{
	return G::Boxed::wrap<TextAttributes>(GTK_TYPE_TEXT_ATTRIBUTES, gtk_text_view_get_default_attributes(gtk_text_view()), false);
}

void
Gtk::TextView::set_buffer(TextBuffer *buffer)
{
	gtk_text_view_set_buffer(gtk_text_view(), *buffer);
}

bool
Gtk::TextView::scroll_to_iter(const TextIter& iter, double within_margin, bool use_align, double xalign, double yalign)
{
	return gtk_text_view_scroll_to_iter(gtk_text_view(), iter.gtk_text_iter(), within_margin, use_align, xalign, yalign);
}

void
Gtk::TextView::scroll_to_mark(const TextMark& mark, double within_margin, bool use_align, double xalign, double yalign)
{
	gtk_text_view_scroll_to_mark(gtk_text_view(), mark.gtk_text_mark(), within_margin, use_align, xalign, yalign);
}

void
Gtk::TextView::scroll_mark_onscreen(const TextMark& mark)
{
	gtk_text_view_scroll_mark_onscreen(gtk_text_view(), mark.gtk_text_mark());
}

bool
Gtk::TextView::move_mark_onscreen(const TextMark& mark)
{
	return gtk_text_view_move_mark_onscreen(gtk_text_view(), mark.gtk_text_mark());
}

void
Gtk::TextView::buffer_to_window_coords(TextWindowType window_type, int buffer_x, int buffer_y, int *window_x, int *window_y)
{
	gtk_text_view_buffer_to_window_coords(gtk_text_view(), (GtkTextWindowType)window_type, buffer_x, buffer_y, window_x, window_y);
}

void
Gtk::TextView::window_to_buffer_coords(TextWindowType window_type, int window_x, int window_y, int *buffer_x, int *buffer_y)
{
	gtk_text_view_window_to_buffer_coords(gtk_text_view(), (GtkTextWindowType)window_type, window_x, window_y, buffer_x, buffer_y);
}

bool
Gtk::TextView::forward_display_line(TextIter& iter)
{
	return gtk_text_view_forward_display_line(gtk_text_view(), iter.gtk_text_iter());
}

bool
Gtk::TextView::backward_display_line(TextIter& iter)
{
	return gtk_text_view_backward_display_line(gtk_text_view(), iter.gtk_text_iter());
}

bool
Gtk::TextView::forward_display_line_end(TextIter& iter)
{
	return gtk_text_view_forward_display_line_end(gtk_text_view(), iter.gtk_text_iter());
}

bool
Gtk::TextView::backward_display_line_start(TextIter& iter)
{
	return gtk_text_view_backward_display_line_start(gtk_text_view(), iter.gtk_text_iter());
}

bool
Gtk::TextView::starts_display_line(const TextIter& iter)
{
	return gtk_text_view_starts_display_line(gtk_text_view(), iter.gtk_text_iter());
}

bool
Gtk::TextView::move_visually(TextIter& iter, int count)
{
	return gtk_text_view_move_visually(gtk_text_view(), iter.gtk_text_iter(), count);
}

void 
Gtk::TextView::add_child_at_anchor(Widget& child, TextChildAnchor& anchor)
{
	gtk_text_view_add_child_at_anchor(gtk_text_view(), child.gtk_widget(), anchor.gtk_text_child_anchor());
}

void 
Gtk::TextView::add_child_in_window(Widget& child, TextWindowType which_window, int xpos, int ypos)
{
	gtk_text_view_add_child_in_window(gtk_text_view(), child, (GtkTextWindowType)which_window, xpos, ypos);
}

void 
Gtk::TextView::move_child(const Widget& child, int xpos, int ypos)
{
	gtk_text_view_move_child(gtk_text_view(), child.gtk_widget(), xpos, ypos);
}

void
Gtk::TextView::set_tabs(const Pango::TabArray& tabs)
{
	gtk_text_view_set_tabs(gtk_text_view(), tabs.pango_tab_array());
}

/*  Gtk::TextViewClass
 */

void
Gtk::TextViewClass::init(GtkTextViewClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
	g_class->set_scroll_adjustments = &set_scroll_adjustments_proxy;
	g_class->populate_popup = &populate_popup_proxy;
	g_class->set_anchor = &set_anchor_proxy;
	g_class->insert_at_cursor = &insert_at_cursor_proxy;
}

GtkTextViewClass*
Gtk::TextViewClass::get_parent_class(void *instance)
{
	return static_cast<GtkTextViewClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::TextViewClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TEXT_VIEW, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TextViewClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::TextViewClass::set_scroll_adjustments_proxy(GtkTextView *text_view, GtkAdjustment *hadjustment, GtkAdjustment *vadjustment)
{
	TextViewSignals *signals = dynamic_cast<TextViewSignals*>(G::ObjectSignals::pointer((GObject*)text_view));
	if (signals)
	{
		Adjustment *tmp_hadjustment = G::Object::wrap<Adjustment>(hadjustment);
		Adjustment *tmp_vadjustment = G::Object::wrap<Adjustment>(vadjustment);
		signals->on_set_scroll_adjustments(tmp_hadjustment, tmp_vadjustment);
	}
	else
	{
		GtkTextViewClass *g_class = get_parent_class(text_view);
		if (g_class && g_class->set_scroll_adjustments)
			g_class->set_scroll_adjustments(text_view, hadjustment, vadjustment);
	}
}

void
Gtk::TextViewClass::populate_popup_proxy(GtkTextView *text_view, GtkMenu *menu)
{
	TextViewSignals *signals = dynamic_cast<TextViewSignals*>(G::ObjectSignals::pointer((GObject*)text_view));
	if (signals)
		signals->on_populate_popup(*G::Object::wrap<Menu>(menu));
	else
	{
		GtkTextViewClass *g_class = get_parent_class(text_view);
		if (g_class && g_class->populate_popup)
			g_class->populate_popup(text_view, menu);
	}
}

void
Gtk::TextViewClass::set_anchor_proxy(GtkTextView *text_view)
{
	TextViewSignals *signals = dynamic_cast<TextViewSignals*>(G::ObjectSignals::pointer((GObject*)text_view));
	if (signals)
		signals->on_set_anchor();
	else
	{
		GtkTextViewClass *g_class = get_parent_class(text_view);
		if (g_class && g_class->set_anchor)
			g_class->set_anchor(text_view);
	}
}

void
Gtk::TextViewClass::insert_at_cursor_proxy(GtkTextView *text_view, const gchar *str)
{
	TextViewSignals *signals = dynamic_cast<TextViewSignals*>(G::ObjectSignals::pointer((GObject*)text_view));
	if (signals)
	{
		std::string tmp_str(str);
		signals->on_insert_at_cursor(tmp_str);
	}
	else
	{
		GtkTextViewClass *g_class = get_parent_class(text_view);
		if (g_class && g_class->insert_at_cursor)
			g_class->insert_at_cursor(text_view, str);
	}
}

/*  Gtk::TextView signals
 */

const Gtk::TextView::SetScrollAdjustmentsSignalType Gtk::TextView::set_scroll_adjustments_signal("set_scroll_adjustments", (GCallback)&Marshal::void_adjustment_adjustment_callback);

const Gtk::TextView::PopulatePopupSignalType Gtk::TextView::populate_popup_signal("populate_popup", (GCallback)&Marshal::void_menu_callback);

const Gtk::TextView::SetAnchorSignalType Gtk::TextView::set_anchor_signal("set_anchor", (GCallback)&G::Marshal::void_callback);

const Gtk::TextView::InsertAtCursorSignalType Gtk::TextView::insert_at_cursor_signal("insert_at_cursor", (GCallback)&Marshal::void_string_callback);

