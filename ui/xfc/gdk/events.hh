/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/gdk/events.hh
/// @brief A GdkEvent C++ wrapper interface.
///
/// Provides C++ wrapper classes the for GDK event structures.

#ifndef XFC_GDK_EVENTS_HH
#define XFC_GDK_EVENTS_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

namespace Xfc {

namespace Gdk {
	
class Device;
class Display;
class DragContext;
class EventAny;
class EventExpose;
class EventVisibility;
class EventMotion;
class EventButton;
class EventScroll;
class EventKey;
class EventCrossing;
class EventFocus;
class EventConfigure;
class EventProperty;
class EventSelection;
class EventOwnerChange;
class EventProximity;
class EventClient;
class EventSetting;
class EventWindowState;
class EventDND;
class Keyval;
class Region;
class Screen;
class Window;

/// @enum EventType
/// Specifies the type of the event.

enum EventType
{
	NOTHING = GDK_NOTHING,
	///< A special code to indicate a null event.
	
	DELETE = GDK_DELETE,
	///< The window manager has requested that the toplevel window be hidden or destroyed,
	///< usually when the user clicks on a special icon in the title bar.
	
	DESTROY = GDK_DESTROY,
	///< The window has been destroyed.
	
	EXPOSE = GDK_EXPOSE,
	///< All or part of the window has become visible and needs to be redrawn.
	
	MOTION_NOTIFY = GDK_MOTION_NOTIFY,
	///< The pointer (usually a mouse) has moved.

	BUTTON_PRESS = GDK_BUTTON_PRESS,
	///< A mouse button has been pressed.
	
	TWO_BUTTON_PRESS = GDK_2BUTTON_PRESS,
	///< A mouse button has been double-clicked (clicked twice within a short period of time);
	///< Note that each click also generates a GDK_BUTTON_PRESS event.
	
	THREE_BUTTON_PRESS = GDK_3BUTTON_PRESS,
	///< A mouse button has been clicked 3 times in a short period of time;
	///< Note that each click also generates a GDK_BUTTON_PRESS event.
	
	BUTTON_RELEASE = GDK_BUTTON_RELEASE,
	///< A mouse button has been released.
	
	KEY_PRESS = GDK_KEY_PRESS,
	///< A key has been pressed.
	
	KEY_RELEASE = GDK_KEY_RELEASE,
	///< A key has been released.
	
	ENTER_NOTIFY = GDK_ENTER_NOTIFY,
	///< The pointer has entered the window.
	
	LEAVE_NOTIFY = GDK_LEAVE_NOTIFY,
	///< The pointer has left the window.
	
	FOCUS_CHANGE = GDK_FOCUS_CHANGE,
	///< The keyboard focus has entered or left the window.
	
	CONFIGURE = GDK_CONFIGURE,
	///< The size, position or stacking order of the window has changed;
	///< Note that GTK+ discards these events for Gdk::WINDOW_CHILD windows.
	
	MAP = GDK_MAP,
	///< The window has been mapped.
	
	UNMAP = GDK_UNMAP,
	///< The window has been unmapped.
	
	PROPERTY_NOTIFY = GDK_PROPERTY_NOTIFY,
	///< A property on the window has been changed or deleted.
	
	SELECTION_CLEAR = GDK_SELECTION_CLEAR,
	///< The application has lost ownership of a selection.
	
	SELECTION_REQUEST = GDK_SELECTION_REQUEST,
	///< Another application has requested a selection.
	
	SELECTION_NOTIFY = GDK_SELECTION_NOTIFY,
	///< A selection has been received.
	
	PROXIMITY_IN = GDK_PROXIMITY_IN,
	///< An input device has moved into contact with a sensing surface (e.g. a touchscreen or graphics tablet).
	
	PROXIMITY_OUT = GDK_PROXIMITY_OUT,
	///< An input device has moved out of contact with a sensing surface.
	
	DRAG_ENTER = GDK_DRAG_ENTER,
	///< The mouse has entered the window while a drag is in progress.
	
	DRAG_LEAVE = GDK_DRAG_LEAVE,
	///< The mouse has entered the window while a drag is in progress.
	
	DRAG_MOTION = GDK_DRAG_MOTION,
	///< The mouse has moved in the window while a drag is in progress.
	
	DRAG_STATUS = GDK_DRAG_STATUS,
	///< The status of the drag operation initiated by the window has changed.
	
	DROP_START = GDK_DROP_START,
	///< A drop operation onto the window has started.
	
	DROP_FINISHED = GDK_DROP_FINISHED,
	///< The drop operation initiated by the window has completed.
	
	CLIENT_EVENT = GDK_CLIENT_EVENT,
	///< A message has been received from another application.
	
	VISIBILITY_NOTIFY = GDK_VISIBILITY_NOTIFY,
	///< The window visibility status has changed.
	
	NO_EXPOSE = GDK_NO_EXPOSE,
	///< Indicates that the source region was completely available when parts
	///< of a drawable were copied (this is not very useful).
	
	SCROLL = GDK_SCROLL,
	///< The mouse wheel was scrolled either up or down.

	WINDOW_STATE = GDK_WINDOW_STATE,
	///< The state of a toplevel window has chnaged (either not shown,
	///< minimized, maximized, sticky or fullscreen).

	SETTING = GDK_SETTING,
	///< A setting was modified.
	
	OWNER_CHANGE = GDK_OWNER_CHANGE
	///< The owner of a selection changed.
};

/// @enum EventMask
/// A set of bit-flags to indicate which events a window is to receive. Most
/// of these masks map onto one or more of the EventType event types.
///
/// POINTER_MOTION_HINT_MASK is a special mask which is used to reduce the number
/// of MOTION_NOTIFY events received. Normally a MOTION_NOTIFY event is received
/// each time the mouse moves. However, if the application spends a lot of time
/// processing the event (updating the display, for example), it can easily lag
/// behind the position of the mouse. When using the POINTER_MOTION_HINT_MASK the
/// server will only send MOTION_NOTIFY events when the application asks for them,
/// by calling Gdk::Window::get_pointer().

enum EventMask
{
	EXPOSURE_MASK = GDK_EXPOSURE_MASK, ///< Maps to the expose-event.
	POINTER_MOTION_MASK = GDK_POINTER_MOTION_MASK, ///< Maps to the motion-notify-event.
	POINTER_MOTION_HINT_MASK = GDK_POINTER_MOTION_HINT_MASK, ///< Decreases the number of motion-notify events.
	BUTTON_MOTION_MASK = GDK_BUTTON_MOTION_MASK, ///< Maps to the motion-notify-event.
	BUTTON1_MOTION_MASK = GDK_BUTTON1_MOTION_MASK, ///< Maps to the motion-notify-event.
	BUTTON2_MOTION_MASK = GDK_BUTTON2_MOTION_MASK, ///< Maps to the motion-notify-event.
	BUTTON3_MOTION_MASK = GDK_BUTTON3_MOTION_MASK, ///< Maps to the motion-notify-event.
	BUTTON_PRESS_MASK = GDK_BUTTON_PRESS_MASK, ///< Maps to the button-press-event.
	BUTTON_RELEASE_MASK = GDK_BUTTON_RELEASE_MASK, ///< Maps to the button-press-event.
	KEY_PRESS_MASK = GDK_KEY_PRESS_MASK, ///< Maps to the key-press-event.
	KEY_RELEASE_MASK = GDK_KEY_RELEASE_MASK, ///< Maps to the key-release-event.
	ENTER_NOTIFY_MASK = GDK_ENTER_NOTIFY_MASK, ///< Maps to the enter-notify-event.
	LEAVE_NOTIFY_MASK = GDK_LEAVE_NOTIFY_MASK, ///< Maps to the leave-notify-event.
	FOCUS_CHANGE_MASK = GDK_FOCUS_CHANGE_MASK, ///< Maps to the focus-change-event.
	STRUCTURE_MASK = GDK_STRUCTURE_MASK, ///< Allows map, unmap, destroy and configure events to be captured.
	PROPERTY_CHANGE_MASK = GDK_PROPERTY_CHANGE_MASK, ///< Maps to the property-notify-event.
	VISIBILITY_NOTIFY_MASK = GDK_VISIBILITY_NOTIFY_MASK, ///< Maps to the visibilty-notify-event.
	PROXIMITY_IN_MASK = GDK_PROXIMITY_IN_MASK, ///< Maps to the proximity-in-event.
	PROXIMITY_OUT_MASK = GDK_PROXIMITY_OUT_MASK, ///< Maps to the proximity-out-event.
	SUBSTRUCTURE_MASK = GDK_SUBSTRUCTURE_MASK, ///< Allows a window to receive STRUCTURE_MASK events on any child windows.
	SCROLL_MASK = GDK_SCROLL_MASK, ///< Maps to the scroll-event
	ALL_EVENTS_MASK = GDK_ALL_EVENTS_MASK ///< Maps to the all events.
};

/// EventMaskField is a bit-field that holds one or more values from the Gdk::EventMask enumeration.

typedef unsigned int EventMaskField;

/// @enum VisibilityState
/// Specifies the visiblity status of a window for an EventVisibility.

enum VisibilityState
{
	VISIBILITY_UNOBSCURED = GDK_VISIBILITY_UNOBSCURED, ///< The window is completely visible.
	VISIBILITY_PARTIAL = GDK_VISIBILITY_PARTIAL, ///< The window is partially visible.
	VISIBILITY_FULLY_OBSCURED = GDK_VISIBILITY_FULLY_OBSCURED ///< The window is not visible at all.
};

/// @enum ScrollDirection
/// Specifies the direction for an EventScroll.

enum ScrollDirection
{
	SCROLL_UP = GDK_SCROLL_UP, ///< The window is scrolled up.
	SCROLL_DOWN = GDK_SCROLL_DOWN, /// The window is scrolled down.
	SCROLL_LEFT = GDK_SCROLL_LEFT, ///< The window is scrolled to the left.
	SCROLL_RIGHT = GDK_SCROLL_RIGHT ///< The window is scrolled to the right.
};

/// @enum NotifyType
/// Specifies the kind of crossing for an EventCrossing. See the X11 protocol specification
/// of LeaveNotify for full details of crossing event generation.

enum NotifyType
{
	NOTIFY_ANCESTOR = GDK_NOTIFY_ANCESTOR, 
	///< The window is entered from an ancestor or left towards an ancestor.

	NOTIFY_VIRTUAL = GDK_NOTIFY_VIRTUAL,
	///< The pointer moves between an ancestor and an inferior of the window.
	
	NOTIFY_INFERIOR = GDK_NOTIFY_INFERIOR,
	///< The window is entered from an inferior or left towards an inferior.
	
	NOTIFY_NONLINEAR = GDK_NOTIFY_NONLINEAR,
	///< The window is entered from or left towards a window which is neither an ancestor nor an inferior.
	
	NOTIFY_NONLINEAR_VIRTUAL = GDK_NOTIFY_NONLINEAR_VIRTUAL,
	///< The pointer moves between two windows which are not ancestors of each other
	///< and the window is part of the ancestor chain between one of these windows
	///< and their least common ancestor.
	
	NOTIFY_UNKNOWN = GDK_NOTIFY_UNKNOWN
	///< Unknown
};

/// @enum CrossingMode
/// Specifies the crossing mode for an EventCrossing.

enum CrossingMode
{
	CROSSING_NORMAL = GDK_CROSSING_NORMAL, ///< Crossing because of pointer motion.
	CROSSING_GRAB = GDK_CROSSING_GRAB, ///< Crossing because a grab is activated.
	CROSSING_UNGRAB = GDK_CROSSING_UNGRAB ///< Crossing because a grab is deactivated.
};

/// @enum PropertyState
/// Specifies the type of a property change for an EventProperty.

enum PropertyState
{
	PROPERTY_NEW_VALUE = GDK_PROPERTY_NEW_VALUE, ///< The property value was changed.
	PROPERTY_DELETE = GDK_PROPERTY_DELETE ///< The property was deleted.
};

/// @enum WindowState
/// Specifies the state of a toplevel window.

enum WindowState
{
	WINDOW_STATE_WITHDRAWN = GDK_WINDOW_STATE_WITHDRAWN, ///< The window is not shown.
	WINDOW_STATE_ICONIFIED = GDK_WINDOW_STATE_ICONIFIED, ///< The window is minimized.
	WINDOW_STATE_MAXIMIZED = GDK_WINDOW_STATE_MAXIMIZED, ///< The window is maximized.
	WINDOW_STATE_STICKY = GDK_WINDOW_STATE_STICKY, ///< The window is sticky.
	WINDOW_STATE_FULLSCREEN = GDK_WINDOW_STATE_FULLSCREEN, ///< The window is fullscreen.
	WINDOW_STATE_ABOVE = GDK_WINDOW_STATE_ABOVE, ///< The window is kept above other windows.
	WINDOW_STATE_BELOW = GDK_WINDOW_STATE_BELOW ///< The window is kept below other windows.
};

/// WindowStateField is a bit-field that holds one or more values from the Gdk::WindowState enumeration.

typedef unsigned int WindowStateField;

/// @enum SettingAction
/// Specifies the kind of modification applied to a setting in an EventSetting.

enum SettingAction
{
	SETTING_ACTION_NEW = GDK_SETTING_ACTION_NEW, ///< A setting was added.
	SETTING_ACTION_CHANGED = GDK_SETTING_ACTION_CHANGED, ///< A setting was changed.
	SETTING_ACTION_DELETED = GDK_SETTING_ACTION_DELETED ///< A setting was deleted.
};

/// @enum OwnerChange
/// Specifies why a selection ownership was changed. 

enum OwnerChange
{
  OWNER_CHANGE_NEW_OWNER = GDK_OWNER_CHANGE_NEW_OWNER, ///< Some other application claimed the ownership.
  OWNER_CHANGE_DESTROY = GDK_OWNER_CHANGE_DESTROY, ///< The window was destroyed.
  OWNER_CHANGE_CLOSE = GDK_OWNER_CHANGE_CLOSE ///< The client was closed.
};

/// @name Event Methods
/// @{

bool get_show_events();
///< Returns true if event debugging output is enabled.

bool events_pending();
///< Checks if any events are ready to be processed for any display.
///< @return <EM>true</EM> if any events are pending.

void set_show_events(bool show_events);
///< Sets whether a trace of received events is output.
///< @param show_events Set <EM>true</EM> to output event debugging information.
///<
///< Note that GTK+ must be compiled with debugging (that is, configured
///< using the --enable-debug option) to use this option.

/// @}

/// @class Event events.hh xfc/gdk/events.hh
/// @brief The Event object represents a GdkEvent.
/// 
/// Event is the base class from which all event objects are derived. Event doesn't
/// have a virtual destructor because it's not meant to be used to derive suclasses,
/// other than the ones derived by XFC.

class Event : public G::Boxed
{
protected: 
	Event();

public:
/// @name Constructors
/// @{

	explicit Event(EventType type);
	///< Construct a new event of the specified type.
	///< @param type The EventType.

	explicit Event(GdkEvent* event);
	///< Construct a new event from an existing GdkEvent.
	///< @param event A pointer to a GdkEvent.
	///<
	///< The <EM>event</EM> can be a newly created GdkEvent or an existing
	///< GdkEvent. The Event object created is a temporary object. It doesn't
	///< take over the ownership of GdkEvent and GdkEvent is not freed by the
	///< destructor.

	Event(GdkEvent* event, bool copy);
	///< Construct a new event from an existing GdkEvent.
	///< @param event A pointer to a GdkEvent.
	///< @param copy Whether the Color object should make a copy of GdkEvent or not.
	///<
	///< The <EM>event</EM> can be a newly created GdkEvent or an existing GdkEvent.
	///< If <EM>copy</EM> is true Event will make a copy of GdkEvent. If <EM>copy</EM>
	///< is false Event wont make a copy but instead takes over the ownership of GdkEvent.
	///< Either way, the destructor will free GdkEvent when the Event object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap GdkEvent objects in a
	///< C++ wrapper.

	Event(const Event& src);
	///< Copy constructor.
	///< @param src The source event.

 	~Event();
	///< Destructor.

	Event& operator=(const Event& src);
	///< Assignment operator.
	///< @param src The source event.

/// @}
/// @name Accessors
/// @{

	GdkEvent* gdk_event() const;
	///< Get a pointer to the GdkEvent structure.

	operator GdkEvent* () const;
	///< Conversion operator; safely converts a Event to a GdkEvent pointer.

	EventType type() const;
	///< Returns the type of the event;

	EventAny* any() const;
	///< Return this event as a pointer to an EventAny.

	EventExpose* expose() const;
	///< If this is a "expose" event, returns a pointer to the EventExpose, otherwise returns null.

	EventVisibility* visibility() const;
	///< If this is a "visibility-notify" event, returns a pointer to the EventVisibility,
	///< otherwise returns null.

	EventMotion* motion() const;
	///< If this is a "motion-notify" event, returns a pointer to the EventMotion,
	///< otherwise returns null.

	EventButton* button() const;
	///< If this is a "button-press" or "button-release" event, returns a pointer to the EventButton,
	///< otherwise returns null.

	EventScroll* scroll() const;
	///< If this is a "scroll" event, returns a pointer to the EventScroll,
	///< otherwise returns null.

	EventKey* key() const;
	///< If this is a "key-press" or "key-release" event, returns a pointer to the EventKey,
	///< otherwise returns null.

	EventCrossing* crossing() const;
	///< If this is an "enter-notify" or "leave-notify" event, returns a pointer to the EventCrossing,
	///< otherwise returns null.

	EventFocus* focus_change() const;
	///< If this is a "focus-change" event, returns a pointer to the EventFocus,
	///< otherwise returns null.

	EventConfigure* configure() const;
	///< If this is a "configure" event, returns a pointer to the EventConfigure,
	///< otherwise returns null.

	EventProperty* property() const;
	///< If this is a "property-notify" event, returns a pointer to the EventProperty,
	///< otherwise returns null.

	EventSelection* selection() const;
	///< If this is a "selection" event, returns a pointer to the EventSelection,
	///< otherwise returns null.

	EventOwnerChange* owner_change() const;	
	///< If this is an "owner_change" event, returns a pointer to the EventOwnerChange,
	///< otherwise returns null.
	
	EventProximity* proximity() const;
	///< If this is an "proximity-in" or "proximity-out" event, returns a pointer to the EventProximity,
	///< otherwise returns null.

	EventClient* client() const;
	///< If this is a "client" event, returns a pointer to the EventClient,
	///< otherwise returns null.

	EventSetting* setting() const;
	///< If this is a "setting" event, returns a pointer to the EventSetting,
	///< otherwise returns null.

	EventWindowState* window_state() const;
	///< If this is a "window-state" event, returns a pointer to the EventWindowState,
	///< otherwise returns null.

	EventDND* dnd() const;
	///< If this is an "drag" or "drop" event, returns a pointer to the EventDND,
	///< otherwise returns null.

	unsigned int get_time() const;
	///< Returns the time stamp of the event, if there is one; otherwise returns GDK_CURRENT_TIME.
	///< @return The time stamp field from the event.
	///<
	///< If event is null, returns GDK_CURRENT_TIME.

	bool get_state(ModifierTypeField *state) const;
	///< If the event contains a "state" field, puts that field in state;
	///< otherwise stores an empty state (0).
	///< @param state The return location for the state.
	///< @return <EM>true</EM> if there was a state field in the event.
	///<
	///< The event may be null, in which case it's treated as if the event
	///< had no state field.

	bool get_axis(AxisUse axis_use, double *value) const;
	///< Extract the axis value for a particular axis use from an event structure.
	///< @param axis_use The axis use to look for.
	///< @param value The location to store the value found.
	///< @return <EM>true</EM> if the specified axis was found, otherwise <EM>false</EM>.

	bool get_coords(double *x_win, double *y_win) const;
	///< Extract the event window relative x/y coordinates from the event.
	///< @param x_win The location to put event window x coordinate.
	///< @param y_win The location to put event window y coordinate.
	///< @returns <EM>true</EM> if the event delivered event window coordinates.

	bool get_root_coords(double *x_root, double *y_root) const;
	///< Extract the root window relative x/y coordinates from the event.
	///< @param x_root The location to put root window x coordinate.
	///< @param y_root The location to put root window y coordinate.
	///< @return <EM>true</EM> if the event delivered root window coordinates.

	Screen* get_screen() const;
	///< Returns the screen for the event.
	///< @return The Screen for the event.
	///<
	///< The screen is typically the screen for any()->window(), but for events such as mouse events,
	///< it is the screen where the the pointer was when the event occurs. That is, the screen which has
	///< the root window to which motion()->x_root and motion()->y_root are relative.

/// @}
/// @name Accessors
/// @{

	static Pointer<Event> get();
	///< Checks all open displays for an event to process, fetching events
	///< from the windowing system if necessary (see Gdk::Display::get_event()).
	///< @return A smart pointer to the next event to be processed, or null if no events are pending.

	static Pointer<EventExpose> get_graphics_expose(const Window& window);
	///< Waits for a GraphicsExpose or NoExpose event from the X server.
	///< @return An EventExpose if a GraphicsExpose event was received, or null if a NoExpose event was received.
	///<
	///< This is used in the GtkText widget in GTK+ to make sure any GraphicsExpose events
	///< are handled before the widget is scrolled.

	static Pointer<Event> peek();
	///< If there is an event waiting in the event queue of some open display,
	///< returns a wrapped copy of it (see Gdk::Display::peek_event()).
	///< @return A smart pointer to a newly allocated Event, or null if no events are in any queues.

/// @}
/// @name Methods
/// @{

	void put();
	///< Appends a copy of this event onto the front of the event queue for any()->window()'s display,
	///< or the default event queue if any()->window() is null (see Gdk::Display::put_event()).

	bool send_client_message(GdkNativeWindow winid, const Display *display = 0);
	///< Sends an X ClientMessage event to a given window.
	///< @param display The Display for the window where the message is to be sent, or null for the default display.
	///< @param winid The window to send the X ClientMessage event to.
	///< @return <EM>true</EM> on success, <EM>false</EM> on failure or if the event is not an EventClient.
	///<
	///< This could be used for communicating between different applications, though the
	///< amount of data is limited to 20 bytes. If display is null the given window must be
	///< on the default Display.

	void send_clientmessage_toall();
	///< Sends an X ClientMessage event to all toplevel windows on the default Screen.
	///< Toplevel windows are determined by checking for the WM_STATE property, as
	///< described in the Inter-Client Communication Conventions Manual (ICCCM). If
	///< no windows are found with the WM_STATE property set, the message is sent to
	///< all children of the root window.
	///<
	///< <B>Note:</B> This method does nothing if the event is not an EventClient.

	void set_screen(Screen& screen);
	///< Sets the screen for event to screen. The event must have been allocated by GTK+.
	///< @param screen A Screen.

/// @}
};

/// @class EventAny events.hh xfc/gdk/events.hh
/// @brief A GdkEventAny C++ wrapper class.
///
/// EventAny contains methods which access the event fields common to all event objects.
/// Any event can safely call any() to return a pointer to an EventAny object.

class EventAny : public Event
{
public:
/// @name Accessors
/// @{

	GdkEventAny* gdk_event_any() const;
	///< Get a pointer to the GdkEventAny structure.

	Window* window() const;
	///< Returns the Gdk::Window which received the event.

	bool send_event() const;
	///< Returns true if the event was sent explicitly (for example, using XSendEvent).

/// @}
};

/// @class EventExpose events.hh xfc/gdk/events.hh
/// @brief A GdkEventExpose C++ wrapper class.
///
/// An EventExpose is generated when all or part of a window becomes visible and
/// needs to be redrawn.
///
/// The event type is EXPOSE.

class EventExpose : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventExpose* gdk_event_expose() const;
	///< Get a pointer to the GdkEventExpose structure.

	const Rectangle& area() const;
	///< Returns the bounding box of region.

	Pointer<Region> region() const;
	///< Returns the region that needs to be redrawn.

	int count() const;
	///< Returns the number of contiguous EXPOSE events following this one. The only use
	///< for this is "exposure compression", i.e. handling all contiguous EXPOSE events
	///< in one go, though GDK performs some exposure compression so this is not normally
	///< needed.
	
/// @}
};

/// @class EventVisibility events.hh xfc/gdk/events.hh
/// @brief A GdkEventVisibility C++ wrapper class.
///
/// An EventVisibility is generated when the window visibility status has changed.
///
/// The event type is VISIBILITY_NOTIFY.

class EventVisibility : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventVisibility* gdk_event_visibility() const;
	///< Get a pointer to the GdkEventVisibility structure.

	VisibilityState state() const;
	///< Returns the new visibility state (VISIBILITY_FULLY_OBSCURED, VISIBILITY_PARTIAL or VISIBILITY_UNOBSCURED).
	
/// @}
};

/// @class EventMotion events.hh xfc/gdk/events.hh
/// @brief A GdkEventMotion C++ wrapper class.
///
/// An EventMotion is generated when the pointer moves.
///
/// The event type is MOTION_NOTIFY.

class EventMotion : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventMotion* gdk_event_motion() const;
	///< Get a pointer to the GdkEventMotion structure.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	double x() const;
	///< Returns the X coordinate of the pointer relative to the window, as a double.

	double y() const;
	///< Returns the Y coordinate of the pointer relative to the window, as a double.

	int x_int() const;
	///< Returns the X coordinate of the pointer relative to the window, as an integer.

	int y_int() const;
	///< Returns the Y coordinate of the pointer relative to the window, as an integer.

	double* axes() const;
	///< Returns x, y translated to the axes of the device, or null if device is the mouse.

	ModifierTypeField state() const;
	///< Returns a bit-mask representing the state of the modifier keys (for example,
	///< Control, Shift and Alt) and the pointer buttons (see Gdk::ModifierType).

	bool is_hint() const;
	///< Returns true if the POINTER_MOTION_HINT_MASK is set.

	Device* device() const;
	///< Returns the Device where the event originated.

	double x_root() const;
	///< Returns the X coordinate of the pointer relative to the root of the screen.

	double y_root() const;
	///< Returns the Y coordinate of the pointer relative to the root of the screen.

/// @}
};

/// @class EventButton events.hh xfc/gdk/events.hh
/// @brief A GdkEventButton C++ wrapper class.
///
/// An EventButton is used for button press and button release events. 
///
/// The event type will be one of BUTTON_PRESS, TWO_BUTTON_PRESS, THREE_BUTTON_PRESS and
/// BUTTON_RELEASE. Double and triple-clicks result in a sequence of events being received. 
///
/// For double-clicks the order of events will be:
/// - BUTTON_PRESS
/// - BUTTON_RELEASE
/// - BUTTON_PRESS
/// - TWO_BUTTON_PRESS
/// - BUTTON_RELEASE
///
/// Note that the first click is received just like a normal button press, while the second click
/// results in a TWO_BUTTON_PRESS being received just after the BUTTON_PRESS.
///
/// Triple-clicks are very similar to double-clicks, except that THREE_BUTTON_PRESS is inserted
/// after the third click. The order of the events is:
/// - BUTTON_PRESS
/// - BUTTON_RELEASE
/// - BUTTON_PRESS
/// - TWO_BUTTON_PRESS
/// - BUTTON_RELEASE
/// - BUTTON_PRESS
/// - THREE_BUTTON_PRESS
/// - BUTTON_RELEASE
///
/// For a double click to occur, the second button press must occur within 1/4 of a second of the
/// first. For a triple click to occur, the third button press must also occur within 1/2 second
/// of the first button press.

class EventButton : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventButton* gdk_event_button() const;
	///< Get a pointer to the GdkEventButton structure.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	double x() const;
	///< Returns the X coordinate of the pointer relative to the window, as a double.

	double y() const;
	///< Returns the Y coordinate of the pointer relative to the window, as a double.

	int x_int() const;
	///< Returns the X coordinate of the pointer relative to the window, as an integer.

	int y_int() const;
	///< Returns the Y coordinate of the pointer relative to the window, as an integer.

	double* axes() const;
	///< Returns x, y translated to the axes of the device, or null if device is the mouse.

	ModifierTypeField state() const;
	///< Returns a bit-mask representing the state of the modifier keys (for example,
	///< Control, Shift and Alt) and the pointer buttons (see Gdk::ModifierType).

	unsigned int button() const;
	///< Returns the button which was pressed or released, numbered from 1 to 5. Normally
	///< button 1 is the left mouse button, 2 is the middle button, and 3 is the right
	///< button. On 2-button mice, the middle button can often be simulated by pressing
	///< both mouse buttons together.

	Device* device() const;
	///< Returns the Device where the event originated.

	double x_root() const;
	///< Returns the X coordinate of the pointer relative to the root of the screen.

	double y_root() const;
	///< Returns the Y coordinate of the pointer relative to the root of the screen.

/// @}
};

/// @class EventScroll events.hh xfc/gdk/events.hh
/// @brief A GdkEventScroll C++ wrapper class.
///
/// An EventScroll is generated from button presses for the buttons 4 to 7. Wheel mice
/// are usually configured to generate button press events for buttons 4 and 5 when
/// the wheel is turned.
///
/// The event type is SCROLL.

class EventScroll : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventScroll* gdk_event_scroll() const;
	///< Get a pointer to the GdkEventScroll structure.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	double x() const;
	///< Returns the X coordinate of the pointer relative to the window, as a double.

	double y() const;
	///< Returns the Y coordinate of the pointer relative to the window, as a double.

	int x_int() const;
	///< Returns the X coordinate of the pointer relative to the window, as an integer.

	int y_int() const;
	///< Returns the Y coordinate of the pointer relative to the window, as an integer.

	ModifierTypeField state() const;
	///< Returns a bit-mask representing the state of the modifier keys (for example,
	///< Control, Shift and Alt) and the pointer buttons (see Gdk::ModifierType).

	ScrollDirection direction() const;
	///< Returns the direction to scroll to (one of SCROLL_UP, SCROLL_DOWN, SCROLL_LEFT and SCROLL_RIGHT).

	Device* device() const;
	///< Returns the Device where the event originated.

	double x_root() const;
	///< Returns the X coordinate of the pointer relative to the root of the screen.

	double y_root() const;
	///< Returns the Y coordinate of the pointer relative to the root of the screen.

/// @}
};

/// @class EventKey events.hh xfc/gdk/events.hh
/// @brief A GdkEventKey C++ wrapper class.
///
/// An EventKey describes a key press or key release event.
///
/// The event type will be KEY_PRESS or KEY_RELEASE.

class EventKey : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventKey* gdk_event_key() const;
	///< Get a pointer to the GdkEventKey structure.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	ModifierTypeField state() const;
	///< Returns a bit-mask representing the state of the modifier keys (for example,
	///< Control, Shift and Alt) and the pointer buttons (see Gdk::ModifierType).

	Keyval keyval() const;
	///< Returns the key that was pressed or released as a Keyval. See the <gdk/gdkkeysym.h> header file
	///< for a complete list of GDK key codes.

	unsigned short hardware_keycode() const;
	///< Returns the raw code of the key that was pressed or released.

	unsigned char group() const;
	///< Returns the keyboard group.
	
/// @}
};

/// @class EventCrossing events.hh xfc/gdk/events.hh
/// @brief A GdkEventCrossing C++ wrapper class.
///
/// EventCrossing is generated when the pointer enters or leaves a window.
///
/// The event type will be either ENTER_NOTIFY or LEAVE_NOTIFY.

class EventCrossing : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventCrossing* gdk_event_crossing() const;
	///< Get a pointer to the GdkEventCrossing structure.

	Window* subwindow() const;
	///< Returns the subwindow that was entered or left.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	double x() const;
	///< Returns the X coordinate of the pointer relative to the window, as a double.

	double y() const;
	///< Returns the Y coordinate of the pointer relative to the window, as a double.

	int x_int() const;
	///< Returns the X coordinate of the pointer relative to the window, as an integer.

	int y_int() const;
	///< Returns the Y coordinate of the pointer relative to the window, as an integer.

	double x_root() const;
	///< Returns the X coordinate of the pointer relative to the root of the screen, as a double.

	double y_root() const;
	///< Returns the Y coordinate of the pointer relative to the root of the screen, as a double.

	int x_root_int() const;
	///< Returns the X coordinate of the pointer relative to the root of the screen, as an integer.

	int y_root_int() const;
	///< Returns the Y coordinate of the pointer relative to the root of the screen, as an integer.

	CrossingMode mode() const;
	///< Returns the crossing mode (CROSSING_NORMAL, CROSSING_GRAB or CROSSING_UNGRAB).

	NotifyType detail() const;
	///< Returns the kind of crossing that happened (NOTIFY_INFERIOR, NOTIFY_ANCESTOR, NOTIFY_VIRTUAL,
	///< NOTIFY_NONLINEAR or NOTIFY_NONLINEAR_VIRTUAL).

	bool focus() const;
	///< Returns true if window is the focus window or an inferior.

	ModifierTypeField state() const;
	///< Returns a bit-mask representing the state of the modifier keys (for example,
	///< Control, Shift and Alt) and the pointer buttons (see Gdk::ModifierType).

/// @}
};

/// @class EventFocus events.hh xfc/gdk/events.hh
/// @brief A GdkEventFocus C++ wrapper class.
///
/// An EventFocus describes a change of keyboard focus.
///
/// The event type is FOCUS_CHANGE

class EventFocus : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventFocus* gdk_event_focus() const;
	///< Get a pointer to the GdkEventFocus structure.

	bool in() const;
	///< Returns true if the window has gained the keyboard focus.

	bool out() const;
	///< Returns true if the window has lost the keyboard focus.
	
/// @}
};

/// @class EventConfigure events.hh xfc/gdk/events.hh
/// @brief A GdkEventConfigure C++ wrapper class.
///
/// An EventConfigure is generated when a window size or position has changed.
///
/// The event type is CONFIGURE.

class EventConfigure : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventConfigure* gdk_event_configure() const;
	///< Get a pointer to the GdkEventConfigure structure.

	int x() const;
	///< Returns the new X coordinate of the window, relative to its parent.

	int y() const;
	///< Returns the new Y coordinate of the window, relative to its parent.

	int width() const;
	///< Returns the new width of the window.

	int height() const;
	///< Returns the new height of the window.
	
/// @}
};

/// @class EventProperty events.hh xfc/gdk/events.hh
/// @brief A GdkEventProperty C++ wrapper class.
///
/// An EventProperty describes a property change on a window.
///
/// The event type is PROPERTY_NOTIFY.

class EventProperty : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventProperty* gdk_event_property() const;
	///< Get a pointer to the GdkEventProperty structure.

	Atom atom() const;
	/// Returns the property that was changed.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	PropertyState state() const;
	///< Returns whether the property was changed (PROPERTY_NEW_VALUE) or deleted (PROPERTY_DELETE).

/// @}
};

/// @class EventSelection events.hh xfc/gdk/events.hh
/// @brief A GdkEventSelection C++ wrapper class.
///
/// An EventSelection is generated when a selection is requested or ownership
/// of a selection is taken over by another client application.
///
/// The event type will be one of SELECTION_CLEAR, SELECTION_NOTIFY or SELECTION_REQUEST.

class EventSelection : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventSelection* gdk_event_selection() const;
	///< Get a pointer to the GdkEventSelection structure.

	Atom selection() const;
	///< Returns the selection.

	Atom target() const;
	///< Returns the target to which the selection should be converted.

	Atom property() const;
	///< Returns the property in which to place the result of the conversion.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	GdkNativeWindow requestor() const;
	///< Returns the native window on which to place property.
	
/// @}
};

/// @class EventOwnerChange events.hh xfc/gdk/events.hh
/// @brief A GdkEventOwnerChange C++ wrapper class.
///
/// EventOwnerChange events are generated when the owner of a selection changes. On X11,
/// this information is only available if the X server supports the XFIXES extension. 
///
/// The type of event will be OWNER_CHANGE.

class EventOwnerChange : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventOwnerChange* gdk_event_owner_change() const;
	///< Get a pointer to the GdkEventOwnerChange structure.

	GdkNativeWindow owner() const;
	///< Returns the new owner of the selection.
  
	OwnerChange reason() const;
	///< Returns the reason for the ownership change as a Gdk::OwnerChange value.
	
	Atom selection() const;
	///< Returns the atom identifying the selection.
	
	unsigned int time() const;
	///< Returns the time of the event (in milliseconds).

	unsigned int selection_time() const;
	///< Returns the time at which the selection ownership was taken over (in milliseconds).

/// @}
};

/// @class EventProximity events.hh xfc/gdk/events.hh
/// @brief A GdkEventProximity C++ wrapper class.
///
/// Proximity events are generated when using GDK's wrapper for the XInput extension.
/// The XInput extension is an add-on for standard X that allows you to use nonstandard
/// devices such as graphics tablets. A proximity event indicates that the stylus has 
/// moved in or out of contact with the tablet, or perhaps that the user's finger has
/// moved in or out of contact with a touch screen.
///
/// The type of event will be either PROXIMITY_IN or PROXIMITY_OUT.

class EventProximity : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventProximity* gdk_event_proximity() const;
	///< Get a pointer to the GdkEventProximity structure.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	Device* device() const;
	///< Returns the Device where the event originated.

/// @}
};

/// @class EventClient events.hh xfc/gdk/events.hh
/// @brief A GdkEventClient C++ wrapper class.
///
/// A Client event is sent by another client application.
///
/// The type of event is CLIENT_EVENT.

class EventClient : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventClient* gdk_event_client() const;
	///< Get a pointer to the GdkEventClient structure.

	Atom message_type() const;
	///< Returns the type of the message, which can be defined by the application.

	unsigned short data_format() const;
	///< Returns the format of the data, given as the number of bits in each data element,

	const char* char_data() const;
	///< Returns 8-bit data.

	const short* short_data() const;
	///< Returns 16-bit data.

	const long* long_data() const;
	///< Returns 32-bit data.
	
/// @}
};

/// @class EventSetting events.hh xfc/gdk/events.hh
/// @brief A GdkEventSetting C++ wrapper class.
///
/// An EventSetting is generated when a setting is modified.
///
/// The event type is SETTING.

class EventSetting : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventSetting* gdk_event_setting() const;
	///< Get a pointer to the GdkEventSetting structure.

	SettingAction action() const;
	///< Returns what happened to the setting (SETTING_ACTION_NEW, SETTING_ACTION_CHANGED or SETTING_ACTION_DELETED).

	String name() const;
	///< Returns the name of the setting.
	
/// @}
};

/// @class EventWindowState events.hh xfc/gdk/events.hh
/// @brief A GdkEventWindowState C++ wrapper class.
///
/// An EventWindowState is generated when the state of a toplevel window changes.
///
/// The event type is WINDOW_STATE.

class EventWindowState : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventWindowState* gdk_event_window_state() const;
	///< Get a pointer to the GdkEventWindowState structure.

  	WindowStateField changed_mask() const;
	///< Returns the bit-mask specifying what flags have changed (see Gdk::WindowState).

	WindowStateField new_window_state() const;
	///< Returns the new window state, a combination of Gdk::WindowState bits.
	
/// @}
};

/// @class EventDND events.hh xfc/gdk/events.hh
/// @brief A GdkEventDND C++ wrapper class.
///
/// An EventDND is generated during drag-and-drop operations.
///
/// The event type will be one of  DRAG_ENTER, DRAG_LEAVE, DRAG_MOTION, DRAG_STATUS, DROP_START or DROP_FINISHED.

class EventDND : public EventAny
{
public:
/// @name Accessors
/// @{

	GdkEventDND* gdk_event_dnd() const;
	///< Get a pointer to the GdkEventDND structure.

	DragContext* context() const;
	///< Returns the Gdk::DragContext for the current DND operation.

	unsigned int time() const;
	///< Returns the time of the event in milliseconds.

	short x_root() const;
	///< Returns the X coordinate of the pointer relative to the root of the screen,
	///< only set for DRAG_MOTION and DROP_START.

	short y_root() const;
	///< Returns the Y coordinate of the pointer relative to the root of the screen,
	///< only set for DRAG_MOTION and DROP_START.
	
/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/event.inl>

#endif // XFC_GDK_EVENTS_HH

