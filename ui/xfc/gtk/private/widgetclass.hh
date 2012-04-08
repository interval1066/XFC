/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  widgetclass.hh - Private interface
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

#ifndef XFC_GTK_WIDGET_CLASS_HH
#define XFC_GTK_WIDGET_CLASS_HH

#include <xfc/gtk/private/objectclass.hh>

namespace Xfc {

namespace Gtk {

class WidgetClass
{
public:
	static void init(GtkWidgetClass *g_class);

	static GtkWidgetClass* get_parent_class(void *instance);

	static GType get_type();

	static void* create();

	static void show_proxy(GtkWidget *widget);

	static void hide_proxy(GtkWidget *widget);

	static void map_proxy(GtkWidget *widget);

	static void unmap_proxy(GtkWidget *widget);

	static void realize_proxy(GtkWidget *widget);

	static void unrealize_proxy(GtkWidget *widget);

	static void size_request_proxy(GtkWidget *widget, GtkRequisition *requisition);

	static void size_allocate_proxy(GtkWidget *widget, GtkAllocation *allocation);

	static void state_changed_proxy(GtkWidget *widget, GtkStateType previous_state);

	static void parent_set_proxy(GtkWidget *widget, GtkWidget *previous_parent);

	static void hierarchy_changed_proxy(GtkWidget *widget, GtkWidget *previous_toplevel);

	static void style_set_proxy(GtkWidget *widget, GtkStyle *previous_style);

	static void direction_changed_proxy(GtkWidget *widget, GtkTextDirection previous_direction);

	static void grab_notify_proxy(GtkWidget *widget, gboolean was_grabbed);

	static void child_notify_proxy(GtkWidget *widget, GParamSpec *pspec);

	static gboolean mnemonic_activate_proxy(GtkWidget *widget, gboolean group_cycling);

	static void grab_focus_proxy(GtkWidget *widget);

	static gboolean focus_proxy(GtkWidget *widget, GtkDirectionType direction);

	static gboolean event_proxy(GtkWidget	*widget, GdkEvent *event);

	static gboolean button_press_event_proxy(GtkWidget *widget, GdkEventButton *event);

	static gboolean button_release_event_proxy(GtkWidget *widget, GdkEventButton *event);

	static gboolean scroll_event_proxy(GtkWidget *widget, GdkEventScroll *event);

	static gboolean motion_notify_event_proxy(GtkWidget *widget, GdkEventMotion *event);

	static gboolean delete_event_proxy(GtkWidget *widget, GdkEventAny *event);
	
	static gboolean destroy_event_proxy(GtkWidget *widget, GdkEventAny *event);

	static gboolean expose_event_proxy(GtkWidget *widget, GdkEventExpose *event);

	static gboolean key_press_event_proxy(GtkWidget *widget, GdkEventKey *event);

	static gboolean key_release_event_proxy(GtkWidget *widget, GdkEventKey *event);

	static gboolean enter_notify_event_proxy(GtkWidget *widget, GdkEventCrossing *event);

	static gboolean leave_notify_event_proxy(GtkWidget *widget, GdkEventCrossing *event);

	static gboolean configure_event_proxy(GtkWidget *widget, GdkEventConfigure *event);

	static gboolean focus_in_event_proxy(GtkWidget *widget, GdkEventFocus *event);

	static gboolean focus_out_event_proxy(GtkWidget *widget, GdkEventFocus *event);

	static gboolean map_event_proxy(GtkWidget	*widget, GdkEventAny *event);

	static gboolean unmap_event_proxy(GtkWidget *widget, GdkEventAny *event);

	static gboolean property_notify_event_proxy(GtkWidget *widget, GdkEventProperty *event);

	static gboolean selection_clear_event_proxy(GtkWidget *widget, GdkEventSelection *event);

	static gboolean selection_request_event_proxy(GtkWidget *widget, GdkEventSelection *event);

	static gboolean selection_notify_event_proxy(GtkWidget *widget, GdkEventSelection *event);

	static gboolean proximity_in_event_proxy(GtkWidget *widget, GdkEventProximity *event);

	static gboolean proximity_out_event_proxy(GtkWidget *widget, GdkEventProximity *event);

	static gboolean visibility_notify_event_proxy(GtkWidget *widget, GdkEventVisibility *event);

	static gboolean client_event_proxy(GtkWidget *widget, GdkEventClient *event);

	static gboolean no_expose_event_proxy(GtkWidget *widget, GdkEventAny *event);

	static gboolean window_state_event_proxy(GtkWidget *widget, GdkEventWindowState *event);

	static void selection_get_proxy(GtkWidget *widget, GtkSelectionData *selection_data, guint info, guint time);

	static void selection_received_proxy(GtkWidget *widget, GtkSelectionData *selection_data, guint time);

	static void drag_begin_proxy(GtkWidget *widget, GdkDragContext *context);

	static void drag_end_proxy(GtkWidget *widget, GdkDragContext *context);

	static void drag_data_get_proxy(GtkWidget *widget, GdkDragContext *context, GtkSelectionData *selection_data, guint info, guint time);

	static void drag_data_delete_proxy(GtkWidget *widget, GdkDragContext *context);

	static void drag_leave_proxy(GtkWidget *widget, GdkDragContext *context, guint time);

	static gboolean drag_motion_proxy(GtkWidget *widget, GdkDragContext *context, gint x, gint y, guint time);

	static gboolean drag_drop_proxy(GtkWidget *widget, GdkDragContext *context, gint x, gint y, guint time);

	static void drag_data_received_proxy(GtkWidget *widget, GdkDragContext *context, gint x, gint y, GtkSelectionData *selection_data, guint info, guint time);

	static void screen_changed_proxy(GtkWidget *widget, GdkScreen *previous_screen);

	static gboolean can_activate_accel_proxy(GtkWidget *widget, guint signal_id);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_WIDGET_CLASS_HH

