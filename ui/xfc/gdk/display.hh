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

/// @file xfc/gdk/display.hh
/// @brief A GdkDisplay C++ wrapper interface.
///
/// Provides Display, an object that controls the keyboard and mouse pointer grabs, and a set of Screens.

#ifndef XFC_GDK_DISPLAY_HH
#define XFC_GDK_DISPLAY_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {

class Device;
class Event;
class Screen;
class Window;

/// @class Display display.hh xfc/gdk/display.hh
/// @brief A GdkDisplay C++ wrapper class.
///
/// The purpose of Display objects are two fold:
/// - To grab/ungrab the keyboard focus and mouse pointer.
/// - To manage and provide information about the Screen(s) available for this Display.
///
/// Display objects are the GDK representation of the X Display which can be described as
/// a workstation consisting of a keyboard, a pointing device (such as a mouse) and one or
/// more screens. It is used to open and keep track of various Screen objects currently
/// instantiated by the application. It is also used to grab and release the keyboard and
/// mouse pointer.

class Display : public G::Object
{
	friend class G::Object;

	Display(const Display&);
	Display& operator=(const Display&);

protected:
/// @name Constructors
/// @{

	explicit Display(GdkDisplay *display, bool owns_reference = true);
	///< Construct a new Display from an existing GdkDisplay.
	///< @param display A pointer to a GdkDisplay.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>display</EM> can be a newly created GdkDisplay or an existing
	///< GdkDisplay. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, bool> ClosedSignalType;
	typedef G::SignalProxy<TypeInstance, ClosedSignalType> ClosedSignalProxy;
	static const ClosedSignalType closed_signal;
	///< Closed signal (see signal_closed()). Calls a slot with the signature:
	///< @code
	///< void function(bool is_error);
	///< // is_error: Is true if the display was closed due to an error.
	///< @endcode
	
/// @}

public:
	typedef GdkDisplay CObjectType;

/// @name Constructors
/// @{

	virtual ~Display();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GdkDisplay* gdk_display() const;
	///< Get a pointer to the GdkDisplay structure.

	operator GdkDisplay* () const;
	///< Conversion operator; safely converts a Display to a GdkDisplay pointer.

	String get_name() const;
	///< Gets the name of the display.
	///< @return A String representing the display name.

	int get_n_screens() const;
	///< Gets the number of screen managed by the display.
	///< @return The number of screens.

	Screen* get_screen(int screen_num) const;
	///< Returns a screen object for one of the screens of the display.
	///< @param screen_num The screen number.
	///< @return The Screen object.

	Screen* get_default_screen() const;
	///< Get the default screen for the display.
	///< @return The default Screen object for the display.

	bool pointer_is_grabbed() const;
	///< Test if the pointer is grabbed.
	///< @return <EM>true</EM> if an active X pointer grab is in effect 

	bool list_devices(std::vector<Device*>& devices) const;
	///< Returns the list of available input devices attached to the display.
	///< @param devices A reference to a vector of Device* to hold the list of devices.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< The devices in this list are statically allocated and will be freed by GTK+.

	Device* get_core_pointer() const;
	///< Returns the core pointer device for the given display.
	///< @return The core pointer device; this is owned by the display and must not be unreferenced.
	
	void get_pointer(Screen **screen, int *x, int *y, ModifierType *mask = 0) const;
	///< Gets the current location of the pointer and the current modifier mask for the display.
	///< @param screen The location to store the screen that the cursor is on, or null.
	///< @param x The location to store root window X coordinate of pointer, or null.
	///< @param y The location to store root window Y coordinate of pointer, or null.
	///< @param mask The location to store current modifier mask, or null.

	void get_pointer(Screen **screen, Point *point, ModifierType *mask = 0) const;
	///< Gets the current location of the pointer and the current modifier mask for the display.
	///< @param screen The location to store the screen that the cursor is on, or null.
	///< @param point The location to store root window X and Y coordinates of the pointer, or null.
	///< @param mask The location to store current modifier mask, or null.
	
	Point get_pointer(Screen **screen = 0, ModifierType *mask = 0) const;
	///< Gets the current location of the pointer and the current modifier mask for the display.
	///< @param screen The location to store the screen that the cursor is on, or null.
	///< @param mask The location to store current modifier mask, or null.
	///< @return A Point storing root window X and Y coordinates of the pointer.
	
	Window* get_window_at_pointer(int *win_x, int *win_y) const;
	///< Obtains the window underneath the mouse pointer, returning the location of that window
	///< in win_x, win_y for the screen.
	///< @param win_x The return location for the X origin of the window under the pointer.
	///< @param win_y The return location for the Y origin of the window under the pointer.
	///< @return The window under the mouse pointer, or null.
	///<
	///< Returns null if the window under the mouse pointer is not known to GDK (for example,
	///< belongs to another application).

	Window* get_window_at_pointer(Point *win_origin) const;
	///< Obtains the window underneath the mouse pointer, returning the location of that window
	///< in win_origin for the screen.
	///< @param win_origin The return location for the X and Y origin of the window under the pointer.
	///< @return The window under the mouse pointer, or null.
	///<
	///< Returns null if the window under the mouse pointer is not known to GDK (for example,
	///< belongs to another application).

	bool supports_cursor_alpha() const;
	///< Determines if cursors can use an 8bit alpha channel on display, otherwise,
	///< cursors are restricted to bilevel alpha (i.e. a mask).
	///< @return <EM>true</EM> if cursors can have alpha channels.

	bool supports_cursor_color() const;
	///< Determines if multicolored cursors are supported on display.
	///< @return <EM>true</EM> if cursors can have multiple colors.
	///<
	///< If multicolored cursors not supported cursors have only a forground
	///< and a background color.

	unsigned int get_default_cursor_size() const;
	///< Gets the default size to use for cursors on the display.
	///< @return The default cursor size.

	void get_maximal_cursor_size(unsigned int *width, unsigned int *height) const;
	///< Gets the maximal size to use for cursors on the display.
	///< @param width The return location for the maximal cursor width.
	///< @param height The return location for the maximal cursor height.

	Window* get_default_group() const;
	///< Gets the default group leader window for all toplevel windows on display.
	///< @return The default group leader window for the display.
	///< 	 
	///< This window is implicitly created by GDK (see Gdk::Window::set_group()).

	bool supports_selection_notification() const;
	///< Determines whether Gdk::EventOwnerChange events will be sent when the owner of a selection changes.
	///< @return Whether Gdk::EventOwnerChange events will be sent.

	bool supports_clipboard_persistence() const;
	///< Determines whether the speicifed display supports clipboard persistance.
	///< @return <EM>true</EM> if the display supports clipboard persistance. 
	///<
	///< Persistance means if it's possible to store the clipboard data after an application
	///< has quit. On X11 this checks if a clipboard daemon is running.

/// @}
/// @name Accessors
/// @{

	static Display* get_default();
	///< Gets the default display.
	///< @return The default Display, or null if there is no default display.

/// @}
/// @name Methods
/// @{

	void pointer_ungrab(unsigned int time = GDK_CURRENT_TIME);
	///< Release any pointer grab.
	///< @param time A timestap (e.g. GDK_CURRENT_TIME).

	void keyboard_ungrab(unsigned int time = GDK_CURRENT_TIME);
	///< Release any keyboard grab.
	///< @param time A timestap (e.g. GDK_CURRENT_TIME).

	void beep();
	///< Emits a short beep on the display.

	void sync();
	///< Flushes any requests queued for the windowing system and waits until all requests
	///< have been handled. This is often used for making sure that the display is
	///< synchronized with the current state of the program. Calling sync() before
	///< gdk_error_trap_pop() makes sure that any errors generated from earlier requests
	///< are handled before the error trap is removed. This is most useful for X11. On
	///< windowing systems where requests are handled synchronously, this function will
	///< do nothing.

	void flush();
	///< Flushes any requests queued for the windowing system. This happens automatically
	///< when the main loop blocks waiting for new events, but if your application is
	///< drawing without returning control to the main loop, you may need to call this
	///< function explicitely. A common case where this function needs to be called is
	///< when an application is executing drawing commands from a thread other than the
	///< thread where the main loop is running.
	///<
	///< This method is most useful for X11. On windowing systems where requests are
	///< handled synchronously, this method will do nothing.

	void close();
	///< Closes the connection windowing system for the display, and cleans up
	///< associated resources.

	Pointer<Event> get_event();
	///< Gets the next GdkEvent to be processed for display, fetching events from the
	///< windowing system if necessary.
	///< @return The next GdkEvent to be processed, or null if no events are pending.

	Pointer<Event> peek_event();
	///< Gets a copy of the first GdkEvent in the display's event queue, without removing
	///< the event from the queue.
	///< @return A copy of the first GdkEvent on the event queue, or null if no events are in the queue.
	///<
	///< This method will not get more events from the windowing system. It only checks
	///< the events that have already been moved to the GDK event queue.

	void put_event(const Gdk::Event& event);
	///< Appends a copy of the given event onto the front of the event queue for display.
	///< @param event A GdkEvent.

	void add_client_message_filter(Atom message_type, GdkFilterFunc func, void *data);
	///< Adds a filter to be called when X ClientMessage events are received.
	///< @param message_type The type of ClientMessage events to receive; This will be checked
	///<                     against the message_type field of the XClientMessage event struct.
	///< @param func The function to call to process the event.
	///< @param data User data to pass to <EM>func</EM>.

	void set_double_click_time(unsigned int msec);
	///< Sets the double click time (two clicks within this time interval count as a double click
	///< and result in a GDK_2BUTTON_PRESS event).
	///< @param msec The double click time in milliseconds (thousandths of a second).
	///<
	///< Applications should NOT set this, it is a global user-configured setting.

	void set_double_click_distance(unsigned int distance);
	///< Sets the double click distance (two clicks within this distance count as a double click
	///< and result in a GDK_2BUTTON_PRESS event). 
	///< @param distance The distance in pixels.
	///<	
	///< Applications should not set this, it is a global user-configured setting.

	bool request_selection_notification(Atom selection);
	///< Request Gdk::EventOwnerChange events for ownership changes of the selection named by the given atom.
	///< @param selection The Gdk::Atom naming the selection for which ownership change notification is requested. 
	///< @return Whether GdkEventOwnerChange events will be sent.
	
	void store_clipboard(Window& clipboard_window, unsigned int time);
	///< Issues a request to the the clipboard manager to store the clipboard data for all available targets. 
	///< @param clipboard_window A Gdk::Window belonging to the clipboard owner. 
	///< @param time A timestamp. 
	///<	
	///< On X11, this is a special program that works according to the freedesktop clipboard specification,
	///< available at <A HREF="http://www.freedesktop.org/Standards/clipboard-manager-spec">freedesktop.org</A>.
	
	void store_clipboard(Window& clipboard_window, unsigned int time, const std::vector<Atom> targets);
	///< Issues a request to the the clipboard manager to store the clipboard data. 
	///< @param clipboard_window A Gdk::Window belonging to the clipboard owner. 
	///< @param time A timestamp. 
	///< @param targets A vector of Gdk::Atom containing the targets that should be saved. 
	///<	
	///< On X11, this is a special program that works according to the freedesktop clipboard specification,
	///< available at <A HREF="http://www.freedesktop.org/Standards/clipboard-manager-spec">freedesktop.org</A>.

/// @}
/// @name Methods
/// @{

	static Display* open(const char *display_name);
	static Display* open(const String& display_name);
	///< Opens a display.
	///< @param display_name The name of the display to open.
	///< @return A Display, or null if the display could not be opened.

/// @}
/// @name Signal Proxies
/// @{

	const ClosedSignalProxy signal_closed();
	///< Connect to the closed_signal; emitted when the display is closed.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/display.inl>

#endif // XFC_GDK_DISPLAY_HH

