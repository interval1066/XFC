/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
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

/// @file xfc/gtk/widgetsignals.hh
/// @brief Gtk::Widget virtual signal handlers.
///
/// Provides Gtk::WidgetSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Widget objects.

#ifndef XFC_GTK_WIDGET_SIGNALS_HH
#define XFC_GTK_WIDGET_SIGNALS_HH

#ifndef XFC_GTK_OBJECT_SIGNALS_HH
#include <xfc/gtk/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class WidgetSignals widgetsignals.hh xfc/gtk/widgetsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Widget.

class WidgetSignals : public ObjectSignals
{
protected:
/// @name Constructors
/// @{

	WidgetSignals(Widget *widget);
	///< Constructs a new WidgetSignals object.
	///< @param widget A Widget object inheriting the WidgetSignals implementation.

	virtual ~WidgetSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Basic Signal Handlers
/// @{

	virtual void on_show();
	///< Called when a widget becomes visible.

	virtual void on_hide();
	///< Called when a widget is hidden (invisible to the user).

	virtual void on_map();
	///< Called when a widget becomes mapped.

	virtual void on_unmap();
	///< Called when a widget becomes unmapped.

	virtual void on_realize();
	///< Called when a widget is realized.

	virtual void on_unrealize();
	///< Called when a widget is unrealized.

	virtual void on_size_request(Requisition *requisition);
	///< Called to obtain the preferred size of a widget.
	///< @param requisition The Requisition to be filled in.

	virtual void on_size_allocate(const Allocation& allocation);
	///< Called when a child widget is allocated a size and position.
	///< @param allocation The position and size allocated to the widget.

	virtual void on_state_changed(StateType previous_state);
	///< Called when the widget state changes.
	///< @param previous_state The previous StateType.

	virtual void on_parent_set(Widget *previous_parent);
	///< Called when the parent container of the widget is set.
	///< @param previous_parent The previous parent of the widget, or null.

	virtual void on_hierarchy_changed(Widget *previous_toplevel);
	///< Called when there is a change in the hierarchy to which the widget belongs.
	///< @param previous_toplevel The previous toplevel widget.
	///<
	///< More precisely, a widget is anchored when its toplevel ancestor is a Gtk::Window.
	///< This handler is called when a widget changes from un-anchored to anchored or vice-versa.

	virtual void on_style_set(Style* previous_style);
	///< Called when the widget style is changed.
	///< @param previous_style The previous Style, or null.

	virtual void on_direction_changed(TextDirection  previous_direction);
	///< Called when the reading direction on the widget is changed.
	///< @param previous_direction The previous direction.

	virtual void on_grab_notify(bool was_grabbed);
	///< Called to notify the widget whether it is the current grabbed widget in an application.
	///< @param was_grabbed <EM>true</EM> if the widget is the current grabbed widget, <EM>false</EM>
	///<                    if it was but is no longer the current grabbed widget.
	///<
	///< The grabbed widget within an application is the widget that recieves all mouse
	///< and keyboard events, while interaction with other widgets is blocked.

	virtual void on_child_notify(GParamSpec *pspec);
	///< Called for each child property that has changed on a widget.
	///< @param pspec A GParamSpec object that holds the meta data specifying the new property.

	virtual bool on_mnemonic_activate(bool group_cycling);
	///< Called to activate the widget when the mnemonic key it's associated with is pressed.
	///< @param group_cycling

	virtual void on_grab_focus();
	///< Called when the widget receives the keyboard focus for the Window it's inside.

	virtual bool on_focus(DirectionType direction);
	///< Called when a child widget receives the focus (see child_focus()).
	///< @param direction The direction of focus movement.
	///< @return <EM>true</EM> if the focus ended up inside the child widget.

	virtual void on_screen_changed(Gdk::Screen *previous_screen);
	///< Called when the screen the widget is displayed on is changed.
	///< @param previous_screen The previous Gdk:Screen.

	virtual bool on_can_activate_accel(unsigned int signal_id);
	///< Called to determine whether an accelerator that activates the signal identified by
	///< <EM>signal_id</EM> can currently be activated.
	///< @param signal_id The id of a signal installed on the widget.
	///< @return <EM>true</EM> if the accelerator can be activated.
	///<
	///< The default determination is made by checking to see if the widget is sensitive,
	///< and all of its parents mapped.

/// @}
/// @name Selection Signal Handlers
/// @{

	virtual void on_selection_get(SelectionData& selection_data, unsigned int info, unsigned int time);
	///< Called when the selection data is requested, if this widget is the selection owner.
	///< @param selection_data The SelectionData object to be filled in.
	///< @param info The info integer that was set when the target was registered (see TargetEntry).
	///< @param time The time of the conversion request as set by the requestor with selectionn_convert().
	///<
	///< This handler is called in response to a call to <EM>selection_convert()</EM>
	///< by the selection requestor. The <EM>selection_data</EM> object needs to be filled
	///< in. Calling Gtk::SelectionData::get_target() and Gtk::SelectionData::get_selection()
	///< enables you to know for which target of which selection the data needs to be
	///< formatted. The formatted data can then be set by calling Gtk::SelectionData:set()
	///< or Gtk::SelectionData::set_text(). The selection requestor will receive the data
	///< when this handler returns.
	
	virtual void on_selection_received(const SelectionData& selection_data, unsigned int time);
	///< Called to notify the widget that the requested selection data has been
	///< converted and provided by the selection owner.
	///< @param selection_data The requested selection data.
	///< @param time The time of the conversion request.

/// @}
/// @name Source-side Drag Signal Handlers
/// @{

	virtual void on_drag_begin(DragContext& context);
	///< Called on the drag source to notify it that a drag has started.
	///< @param context A reference to a Gtk::DragContext (only used by GTK+).
	///<
	///< It's quite useful to know when a drag-and-drop event has started. This makes it
	///< possible to create a snapshot of the data that will be provided for each target and
	///< to make sure that each event contains the latest version of the data. A typical reason
	///< to override this handler is to set up a custom drag icon with drag_source_set_icon().

	virtual void on_drag_end(DragContext& context);
	///< Called on the drag source to notify it when a drag is finished.
	///< @param context A reference to a Gtk::DragContext (only used by GTK+).
	///<
	///< It's useful to be notified when a drag-and-drop event ends. A typical
	///< reason to override this handler is to undo things done in on_drag_begin().

	virtual void on_drag_data_get(DragContext& context, SelectionData& data, unsigned int info, unsigned int time);
	///< Called after a valid drop to request the data of the first target
	///< supported by the destination widget.
	///< @param context A reference to a Gtk::DragContext (only used by GTK+).
	///< @param data The SelectionData that needs to be filled in to provide the requested data.
	///< @param info The info integer that was set when the target was registered (see TargertEntry).
	///< @param time The time of the conversion request.
	///< 
	///< To provide the data for the requested target <EM>data</EM> needs to be filled in.
	///< Calling Gtk::SelectionData::get_target() enables you to know for which target the
	///< data needs to be formatted. The formatted data can then be set by calling
	///< Gtk::SelectionData:set() or Gtk::SelectionData::set_text(). The destination widget
	///< will receive the data when this handler returns.
		
	virtual void on_drag_data_delete(DragContext& context);
	///< Called on the drag source when a drag with the action Gdk::ACTION_MOVE
	///< is successfully completed.
	///< @param context A reference to a Gtk::DragContext (only used by GTK+).
	///<
	///< The <EM>drag_data_delete</EM> signal is used internally by GTK+ to
	///< implement drag-and-drop support in text widgets, such as entry, TextBuffer
	///< and TextView. It wont be of much use to you unless you're implementing
	///< manual drag-and-drop. It indicates that the data can be deleted.
	
/// @}
/// @name Target-side Drag Signal Handlers
/// @{

	virtual void on_drag_leave(DragContext& context, unsigned int time);
	///< Called on the drop site when the cursor leaves the widget.
	///< @param context A reference to the Gtk::DragContext for the current drag-and-drop event.
	///< @param time The timestamp of the motion event.
	///<
	///< This handler might be useful to undo any action you took when the widget
	///< was first entered (i.e. on the first <EM>drag_motion</EM> signal), such as
	///< undo highlighting with drag_unhighlight().

	virtual bool on_drag_motion(DragContext& context, int x, int y, unsigned int time);
	///< Called when the mouse passes over the widget to verifiy whether it can accept a drop.
	///< @param context A reference to the Gtk::DragContext for the current drag-and-drop event.
	///< @param x The X position of the mouse pointer relative to the widget.
	///< @param y The Y position of the mouse pointer relative to the widget.
	///< @param time The time when the event occurred.
	///< @return <EM>true</EM> if the widget is a valid drag-and-drop destination.
	///<
	///< If false is returned the widget is not a drag-and-drop destination and
	///< the parent should be checked instead. When true is returned, the widget
	///< will be seen as a drag-and-drop destination and you'll have to verify if
	///< it can accept a drop.
	///<
	///< Gdk::DragContext::targets() retrieves a list of atoms of all the targets
	///< supported by the source widget. You need this list to verify if one of the
	///< targets corresponds to the targets that can be accepted by the destination
	///< widget. Gdk::DragContext::actions() returns the actions supported by the
	///< source widget. Gdk::DragContext::suggested_action() returns the action
	///< suggested by automatically by GTK+. You're free to choose any of the
	///< default actions but this action is usually the best choice.
	///<
	///< The source widget needs to be notified if the destination widget will accept
	///< a drop according to the provided targets and actions. This is done by calling
	///< Gdk::DragContext::status(). This method must always be called if this handler
	///< returns true. If it's not called the source widget will not issue another
	///< <EM>drag_motion</EM> signal.

	virtual bool on_drag_drop(DragContext& context, int x, int y, unsigned int time);
	///< Called to notify the widget that a drop has occurred.
	///< @param context A reference to the Gtk::DragContext for the current drag-and-drop event.
	///< @param x The X position of the mouse pointer relative to the widget.
	///< @param y The Y position of the mouse pointer relative to the widget.
	///< @param time The time when the event occurred.
	///< @return <EM>true</EM> if the widget is a valid drag-and-drop destination.
	///<
	///< Gdk::DragContext::targets() can be called to decide which target's data
	///< has to be obtained. When this is known, the drag_get_data() method has to
	///< be called to actually request the data. The data will be provided through
	///< a <EM>drag_data_received</EM> signal.

	virtual void on_drag_data_received(DragContext& context, int x, int y, const SelectionData& data, unsigned int info, unsigned int time);
	///< Called to notify the widget when the data from a drop is received.
	///< @param context A reference to a Gtk::DragContext.
	///< @param x The X position of the mouse pointer relative to the widget. 
	///< @param y The Y position of the mouse pointer relative to the widget. 
	///< @param data The SelectionData that contains all the information about the data received.
	///< @param info The info integer that was set when the target was registered (see TargertEntry).
	///< @param time The time of the conversion request.
	
/// @}
/// @name GDK Event Signal Handlers
/// @{

	virtual bool on_event(const Gdk::Event& event);
	///< Called when any GDK event occurs.
	///< @param event The Gdk::Event.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_button_press_event(const Gdk::EventButton& event);
	///< Called when a mouse button has been pressed.
	///< @param event The Gdk::EventButton.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_button_release_event(const Gdk::EventButton& event);
	///< Called when a mouse button has been released.
	///< @param event The Gdk::EventButton.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_scroll_event(const Gdk::EventScroll& event);
	///< Called when a mouse wheel is scrolled either up or down.
	///< @param event The Gdk::EventScroll.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_motion_notify_event(const Gdk::EventMotion& event);
	///< Called when the mouse is moved.
	///< @param event The Gdk::EventMotion.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_delete_event(const Gdk::EventAny& event);
	///< Called when the user tries to close an application from the window manager frame.
	///< @param event The Gdk::Event.
	///< @return <EM>false</EM> to allow the application window to close.
	///<
	///< The <EM>event.type()</EM> method will return the type identifier Gdk::DELETE.
	///< The <EM>event.window()</EM> method will return the Gdk::Window reporting the event.
	///< The <EM>event.send_event()</EM> method indicates whether the event came from the
	///< X server or another source. Returning true will prevent the application window
	///< from closing.
	///<
	///< <B>Note:</B> only top-level windows can receive the <EM>delete_event</EM>.

	virtual bool on_destroy_event(const Gdk::EventAny& event);
	///< Called when the widget has been destroyed.
	///< @param event The Gdk::EventAny.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_expose_event(const Gdk::EventExpose& event);
	///< Called when all or part of the widget has become visible and needs to be redrawn.
	///< @param event The Gdk::EventExpose.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_key_press_event(const Gdk::EventKey& event);
	///< Called when a key is pressed.
	///< @param event The Gdk::EventKey.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_key_release_event(const Gdk::EventKey& event);
	///< Called when a key is released.
	///< @param event The Gdk::EventKey.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_enter_notify_event(const Gdk::EventCrossing& event);
	///< Called when a widget is entered.
	///< @param event The Gdk::EventCrossing.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_leave_notify_event(const Gdk::EventCrossing& event);
	///< Called when a widget is exited.
	///< @param event The Gdk::EventCrossing.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_configure_event(const Gdk::EventConfigure& event);
	///< Called when the size, position or stacking order of the widget is changed.
	///< @param event The Gdk::EventConfigure.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.
	///<
	///< Note that these events are discarded for Gdk::WINDOW_CHILD windows.

	virtual bool on_focus_in_event(const Gdk::EventFocus& event);
	///< Called when the widget gains the keybaord focus (the focus widget gets keyboard events).
	///< @param event The Gdk::EventFocus.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_focus_out_event(const Gdk::EventFocus& event);
	///< Called when the widget looses the keyboard focus.
	///< @param event The Gdk::EventFocus.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_map_event(const Gdk::EventAny& event);
	///< Called when the widget has been mapped (visible on the screen).
	///< @param event The Gdk::EventAny.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_unmap_event(const Gdk::EventAny& event);
	///< Called when the widget has been unmapped (no longer visible on the screen).
	///< @param event The Gdk::EventAny.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_property_notify_event(const Gdk::EventProperty& event);
	///< Called when a property on the widget has been changed or deleted.
	///< @param event The Gdk::EventProperty.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_selection_clear_event(const Gdk::EventSelection& event);
	///< Called when an application has lost ownership of a selection.
	///< @param event The Gdk::EventSelection.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_selection_request_event(const Gdk::EventSelection& event);
	///< Called when another application has requested a selection.
	///< @param event The Gdk::EventSelection.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_selection_notify_event(const Gdk::EventSelection& event);
	///< Called when a selection has been received.
	///< @param event The Gdk::EventSelection.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_proximity_in_event(const Gdk::EventProximity& event);
	///< Called when an input device has moved into contact with a sensing surface
	///< (such as a touchscreen or graphics tablet).
	///< @param event The Gdk::EventProximity.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_proximity_out_event(const Gdk::EventProximity& event);
	///< Called when an input device has moved out of contact with a sensing surface.
	///< @param event The Gdk::EventProximity.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_visibility_notify_event(const Gdk::EventVisibility& event);
	///< Called when the widget's visibility status has changed (either fully obscured,
	///< partially obscured or unobscured.
	///< @param event The Gdk::EventVisibility.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_client_event(const Gdk::EventClient& event);
	///< Called when a message has been received from another application.
	///< @param event The Gdk::EventClient.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

	virtual bool on_no_expose_event(const Gdk::EventAny& event);
	///< Called when all or part of the widget has become visible, but no expose event was generated.
	///< @param event The Gdk::EventAny.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.
	///<
	///< Indicates that the source region was completely available when parts of a drawable
	///< were copied. This is not very useful.

	virtual bool on_window_state_event(const Gdk::EventWindowState& event);
	///< Called when the state of a toplevel window changes (either not shown, minimized,
	///< maximized, sticky or fullscreen).
	///< @param event The Gdk::EventWindowState.
	///< @return <EM>true</EM> to stop invoking other handlers, <EM>false</EM> to propagate the event.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_WIDGET_SIGNALS_HH

