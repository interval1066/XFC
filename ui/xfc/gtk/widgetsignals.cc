/*  XFC: Xfce Foundation Classes (User Interface Library)
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
#include "style.hh"
#include "private/widgetclass.hh"
#include "../gdk/screen.hh"

using namespace Xfc;

/*  Gtk::WidgetSignals
 */

Gtk::WidgetSignals::WidgetSignals(Widget *widget)
: ObjectSignals(widget)
{
}

Gtk::WidgetSignals::~WidgetSignals()
{
}

void
Gtk::WidgetSignals::on_show()
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->show)
		g_class->show((GtkWidget*)instance_);
}

void
Gtk::WidgetSignals::on_hide()
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->hide)
		g_class->hide((GtkWidget*)instance_);
}

void
Gtk::WidgetSignals::on_map()
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->map)
		g_class->map((GtkWidget*)instance_);
}

void
Gtk::WidgetSignals::on_unmap()
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->unmap)
		g_class->unmap((GtkWidget*)instance_);
}

void
Gtk::WidgetSignals::on_realize()
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->realize)
		g_class->realize((GtkWidget*)instance_);
}

void
Gtk::WidgetSignals::on_unrealize()
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->unrealize)
		g_class->unrealize((GtkWidget*)instance_);
}

void
Gtk::WidgetSignals::on_size_request(Requisition *requisition)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->size_request)
		g_class->size_request((GtkWidget*)instance_, requisition->gtk_requisition());
}

void
Gtk::WidgetSignals::on_size_allocate(const Allocation& allocation)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->size_allocate)
		g_class->size_allocate((GtkWidget*)instance_, allocation.gtk_allocation());
}

void
Gtk::WidgetSignals::on_state_changed(StateType previous_state)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->state_changed)
		g_class->state_changed((GtkWidget*)instance_, (GtkStateType)previous_state);
}

void
Gtk::WidgetSignals::on_parent_set(Widget *previous_parent)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->parent_set)
		g_class->parent_set((GtkWidget*)instance_, *previous_parent);
}

void
Gtk::WidgetSignals::on_hierarchy_changed(Widget *previous_toplevel)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->hierarchy_changed)
		g_class->hierarchy_changed((GtkWidget*)instance_, *previous_toplevel);
}

void
Gtk::WidgetSignals::on_style_set(Style* previous_style)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->style_set)
		g_class->style_set((GtkWidget*)instance_, *previous_style);
}

void
Gtk::WidgetSignals::on_direction_changed(TextDirection  previous_direction)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->direction_changed)
		g_class->direction_changed((GtkWidget*)instance_, (GtkTextDirection)previous_direction);
}

void
Gtk::WidgetSignals::on_grab_notify(bool was_grabbed)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->grab_notify)
		g_class->grab_notify((GtkWidget*)instance_, was_grabbed);
}

void
Gtk::WidgetSignals::on_child_notify(GParamSpec *pspec)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->child_notify)
		g_class->child_notify((GtkWidget*)instance_, pspec);
}

bool
Gtk::WidgetSignals::on_mnemonic_activate(bool group_cycling)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->mnemonic_activate)
		result = g_class->mnemonic_activate((GtkWidget*)instance_, group_cycling);
	return result;
}

void
Gtk::WidgetSignals::on_grab_focus()
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->grab_focus)
		g_class->grab_focus((GtkWidget*)instance_);
}

bool
Gtk::WidgetSignals::on_focus(DirectionType direction)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->focus)
		result = g_class->focus((GtkWidget*)instance_, (GtkDirectionType)direction);
	return result;
}

void
Gtk::WidgetSignals::on_screen_changed(Gdk::Screen *previous_screen)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->screen_changed)
		g_class->screen_changed((GtkWidget*)instance_, *previous_screen);
}

bool
Gtk::WidgetSignals::on_can_activate_accel(unsigned int signal_id)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->can_activate_accel)
		result = g_class->can_activate_accel((GtkWidget*)instance_, signal_id);
	return result;
}

void
Gtk::WidgetSignals::on_selection_get(SelectionData& selection_data, unsigned int info, unsigned int time)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->selection_get)
		g_class->selection_get((GtkWidget*)instance_, selection_data.gtk_selection_data(), info, time);
}

void
Gtk::WidgetSignals::on_selection_received(const SelectionData& selection_data, unsigned int time)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->selection_received)
		g_class->selection_received((GtkWidget*)instance_, selection_data.gtk_selection_data(), time);
}

void
Gtk::WidgetSignals::on_drag_begin(DragContext& context)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->drag_begin)
		g_class->drag_begin((GtkWidget*)instance_, context.gdk_drag_context());
}

void
Gtk::WidgetSignals::on_drag_end(DragContext& context)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->drag_end)
		g_class->drag_end((GtkWidget*)instance_, context.gdk_drag_context());
}

void
Gtk::WidgetSignals::on_drag_data_get(DragContext& context, SelectionData& selection_data, unsigned int info, unsigned int time)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->drag_data_get)
		g_class->drag_data_get((GtkWidget*)instance_, context.gdk_drag_context(), selection_data.gtk_selection_data(), info, time);
}

void
Gtk::WidgetSignals::on_drag_data_delete(DragContext& context)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->drag_data_delete)
		g_class->drag_data_delete((GtkWidget*)instance_, context.gdk_drag_context());
}

void
Gtk::WidgetSignals::on_drag_leave(DragContext& context, unsigned int time)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->drag_leave)
		g_class->drag_leave((GtkWidget*)instance_, context.gdk_drag_context(), time);
}

bool
Gtk::WidgetSignals::on_drag_motion(DragContext& context, int x, int y, unsigned int time)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->drag_motion)
		result = g_class->drag_motion((GtkWidget*)instance_, context.gdk_drag_context(), x, y, time);
	return result;
}

bool
Gtk::WidgetSignals::on_drag_drop(DragContext& context, int x, int y, unsigned int time)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->drag_drop)
		result = g_class->drag_drop((GtkWidget*)instance_, context.gdk_drag_context(), x, y, time);
	return result;
}

void
Gtk::WidgetSignals::on_drag_data_received(DragContext& context, int x, int y, const SelectionData& selection_data, unsigned int info, unsigned int time)
{
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->drag_data_received)
		g_class->drag_data_received((GtkWidget*)instance_, context.gdk_drag_context(), x, y, selection_data.gtk_selection_data(), info, time);
}

bool
Gtk::WidgetSignals::on_event(const Gdk::Event& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->event)
		result = g_class->event((GtkWidget*)instance_, event.gdk_event());
	return result;
}

bool
Gtk::WidgetSignals::on_button_press_event(const Gdk::EventButton& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->button_press_event)
		result = g_class->button_press_event((GtkWidget*)instance_, event.gdk_event_button());
	return result;
}

bool
Gtk::WidgetSignals::on_button_release_event(const Gdk::EventButton& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->button_release_event)
		result = g_class->button_release_event((GtkWidget*)instance_, event.gdk_event_button());
	return result;
}

bool
Gtk::WidgetSignals::on_scroll_event(const Gdk::EventScroll& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->scroll_event)
		result = g_class->scroll_event((GtkWidget*)instance_, event.gdk_event_scroll());
	return result;
}

bool
Gtk::WidgetSignals::on_motion_notify_event(const Gdk::EventMotion& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->motion_notify_event)
		result = g_class->motion_notify_event((GtkWidget*)instance_, event.gdk_event_motion());
	return result;
}

bool
Gtk::WidgetSignals::on_delete_event(const Gdk::EventAny& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->delete_event)
		result = g_class->delete_event((GtkWidget*)instance_, event.gdk_event_any());
	return result;
}

bool
Gtk::WidgetSignals::on_destroy_event(const Gdk::EventAny& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->destroy_event)
		result = g_class->destroy_event((GtkWidget*)instance_, event.gdk_event_any());
	return result;
}

bool
Gtk::WidgetSignals::on_expose_event(const Gdk::EventExpose& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->expose_event)
		result = g_class->expose_event((GtkWidget*)instance_, event.gdk_event_expose());
	return result;
}

bool
Gtk::WidgetSignals::on_key_press_event(const Gdk::EventKey& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->key_press_event)
		result = g_class->key_press_event((GtkWidget*)instance_, event.gdk_event_key());
	return result;
}

bool
Gtk::WidgetSignals::on_key_release_event(const Gdk::EventKey& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->key_release_event)
		result = g_class->key_release_event((GtkWidget*)instance_, event.gdk_event_key());
	return result;
}

bool
Gtk::WidgetSignals::on_enter_notify_event(const Gdk::EventCrossing& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->enter_notify_event)
		result = g_class->enter_notify_event((GtkWidget*)instance_, event.gdk_event_crossing());
	return result;
}

bool
Gtk::WidgetSignals::on_leave_notify_event(const Gdk::EventCrossing& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->leave_notify_event)
		result = g_class->leave_notify_event((GtkWidget*)instance_, event.gdk_event_crossing());
	return result;
}

bool
Gtk::WidgetSignals::on_configure_event(const Gdk::EventConfigure& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->configure_event)
		result = g_class->configure_event((GtkWidget*)instance_, event.gdk_event_configure());
	return result;
}

bool
Gtk::WidgetSignals::on_focus_in_event(const Gdk::EventFocus& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->focus_in_event)
		result = g_class->focus_in_event((GtkWidget*)instance_, event.gdk_event_focus());
	return result;
}

bool
Gtk::WidgetSignals::on_focus_out_event(const Gdk::EventFocus& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->focus_out_event)
		result = g_class->focus_out_event((GtkWidget*)instance_, event.gdk_event_focus());
	return result;
}

bool
Gtk::WidgetSignals::on_map_event(const Gdk::EventAny& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->map_event)
		result = g_class->map_event((GtkWidget*)instance_, event.gdk_event_any());
	return result;
}

bool
Gtk::WidgetSignals::on_unmap_event(const Gdk::EventAny& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->unmap_event)
		result = g_class->unmap_event((GtkWidget*)instance_, event.gdk_event_any());
	return result;
}

bool
Gtk::WidgetSignals::on_property_notify_event(const Gdk::EventProperty& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->property_notify_event)
		result = g_class->property_notify_event((GtkWidget*)instance_, event.gdk_event_property());
	return result;
}

bool
Gtk::WidgetSignals::on_selection_clear_event(const Gdk::EventSelection& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->selection_clear_event)
		result = g_class->selection_clear_event((GtkWidget*)instance_, event.gdk_event_selection());
	return result;
}

bool
Gtk::WidgetSignals::on_selection_request_event(const Gdk::EventSelection& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->selection_request_event)
		result = g_class->selection_request_event((GtkWidget*)instance_, event.gdk_event_selection());
	return result;
}

bool
Gtk::WidgetSignals::on_selection_notify_event(const Gdk::EventSelection& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->selection_notify_event)
		result = g_class->selection_notify_event((GtkWidget*)instance_, event.gdk_event_selection());
	return result;
}

bool
Gtk::WidgetSignals::on_proximity_in_event(const Gdk::EventProximity& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->proximity_in_event)
		result = g_class->proximity_in_event((GtkWidget*)instance_, event.gdk_event_proximity());
	return result;
}

bool
Gtk::WidgetSignals::on_proximity_out_event(const Gdk::EventProximity& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->proximity_out_event)
		result = g_class->proximity_out_event((GtkWidget*)instance_, event.gdk_event_proximity());
	return result;
}

bool
Gtk::WidgetSignals::on_visibility_notify_event(const Gdk::EventVisibility& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->visibility_notify_event)
		result = g_class->visibility_notify_event((GtkWidget*)instance_, event.gdk_event_visibility());
	return result;
}

bool
Gtk::WidgetSignals::on_client_event(const Gdk::EventClient& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->client_event)
		result = g_class->client_event((GtkWidget*)instance_, event.gdk_event_client());
	return result;
}

bool
Gtk::WidgetSignals::on_no_expose_event(const Gdk::EventAny& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->no_expose_event)
		result = g_class->no_expose_event((GtkWidget*)instance_, event.gdk_event_any());
	return result;
}

bool
Gtk::WidgetSignals::on_window_state_event(const Gdk::EventWindowState& event)
{
	bool result = false;
	GtkWidgetClass *g_class = WidgetClass::get_parent_class(instance_);
	if (g_class && g_class->window_state_event)
		result = g_class->window_state_event((GtkWidget*)instance_, event.gdk_event_window_state());
	return result;
}

