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

/// @file xfc/gdk/screen.hh
/// @brief A GdkScreen C++ wrapper interface.
///
/// Provides Screen, an object representing a physical screen.

#ifndef XFC_GDK_SCREEN_HH
#define XFC_GDK_SCREEN_HH

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

namespace G {
class Value;
}

namespace Gdk {

class Colormap;
class Display;
class Event;
class Rectangle;
class Visual;
class Window;

/// @class Screen screen.hh xfc/gdk/screen.hh
/// @brief A GdkScreen C++ wrapper class.
///
/// Screen objects are the GDK representation of a physical screen. They are used throughout
/// GDK and GTK+ to specify which screen the top level windows are to be displayed on. It
/// is also used to query the screen specification and default settings such as the default
/// colormap (get_default_colormap()), the screen width (get_width()), etc. Note that a screen
/// may consist of multiple monitors which are merged to form a large screen area.

class Screen : public G::Object
{
	friend class G::Object;

	Screen(const Screen&);
	Screen& operator=(const Screen&);

protected:
/// @name Constructors
/// @{

	explicit Screen(GdkScreen *screen, bool owns_reference = true);
	///< Construct a new Screen from an existing GdkScreen.
	///< @param screen A pointer to a GdkScreen.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>screen</EM> can be a newly created GdkScreen or an existing
	///< GdkScreen. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> SizeChangedSignalType;
	typedef G::SignalProxy<TypeInstance, SizeChangedSignalType> SizeChangedSignalProxy;
	static const SizeChangedSignalType size_changed_signal;
	///< Size changed signal (see signal_size_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GdkScreen CObjectType;

/// @name Constructors
/// @{

	virtual ~Screen();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GdkScreen* gdk_screen() const;
	///< Get a pointer to the GdkScreen structure.

	operator GdkScreen* () const;
	///< Conversion operator; safely converts a Screen to a GdkScreen pointer.

	Colormap* get_default_colormap() const;
	///< Gets the default colormap for the screen.
	///< @return The default Colormap.

	Colormap* get_system_colormap() const;
	///< Gets the system's default colormap for the screen.
	///< @return The default colormap for the screen.

	const Visual* get_system_visual() const;
	///< Get the system's default visual for the screen.
	///< @return The system visual.
	///<
	///< This is the visual for the root window of the display. The return value
	///< should not be unreferenced.

	Window* get_root_window() const;
	///< Gets the root window of the screen.
	///< @return The root window.

	Display* get_display() const;
	///< Returns the display to which the screen belongs.

	int get_number() const;
	///< Gets the index of the screen among the screens in the display to which it belongs (see get_display()).
	///< @return The index
	
	int get_width() const;
	///< Gets the width of the screen in pixels.
	///< @return The width of the screen in pixels.

	int get_height() const;
	///< Gets the height of the screen in pixels.
	///< @return The height of the screen in pixels.

	int get_width_mm() const;
	///< Gets the width of screen in millimeters.
	///< @return The width of the screen in millimeters.
	///<
	///< Note that on some X servers this value will not be correct.

	int get_height_mm() const;
	///< Gets the height of screen in millimeters.
	///< @return The height of the screen in millimeters.
	///<
	///< Note that on some X servers this value will not be correct.

	bool list_visuals(std::vector<const Visual*>& visuals) const;
	///< Lists the available visuals for the specified screen.
	///< @param visuals A reference to a vector of const Visual* to hold the list of visuals.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< A visual describes a hardware image data format. For example, a visual
	///< might support 24-bit color, or 8-bit color, and might expect pixels to be
	///< in a certain format.

	bool get_toplevels(std::vector<Window*>& toplevels) const;
	///< Obtains a list of all toplevel windows known to GDK on the screen.
	///< @param toplevels A reference to a vector of Window* to hold the list of toplevel windows.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< A toplevel window is a child of the root window (see get_default_root_window()).

	String make_display_name() const;
	///< Determines the name to pass to Gdk::Display::open() to get a display with
	///< this screen as the default screen.
	///< @return A String.

	int get_n_monitors() const;
	///< Returns the number of monitors that are part of the virtual screen.
	///< @return The number of monitors part of the virtual screen, or 0 if screen
	///< is not in virtual screen mode.

	void get_monitor_geometry(int monitor_num, Rectangle& dest) const;
	///< Retrieves the Gdk::Rectangle representing the size and start coordinates of
	///< the individual monitor within the the entire virtual screen.
	///< @param monitor_num The monitor number.
	///< @param dest A Rectangle to be filled with the monitor geometry.
	///<
	///< Note that the virtual screen coordinates can be retrieved via
	///< get_width() and get_height().

	Rectangle get_monitor_geometry(int monitor_num) const;
	///< Retrieves the Gdk::Rectangle representing the size and start coordinates of
	///< the individual monitor within the the entire virtual screen.
	///< @param monitor_num The monitor number.
	///< @return A Rectangle filled with the monitor geometry.
	///<
	///< Note that the virtual screen coordinates can be retrieved via
	///< get_width() and get_height().

	int get_monitor_at_point(int x, int y) const;
	///< Returns the monitor number in which the point (x,y) is located.
	///< @param x The X coordinate in the virtual screen.
	///< @param y The Y coordinate in the virtual screen.
	///< @return The monitor number in which the point (x,y) lies, or a monitor close
	///< to (x,y) if the point is not in any monitor.
	
	int get_monitor_at_point(const Point& point) const;
	///< Returns the monitor number in which the <EM>point</EM> is located.
	///< @param point The X and Y coordinates in the virtual screen.
	///< @return The monitor number in which the <EM>point</EM> lies, or a monitor close
	///< to <EM>point</EM> if the point is not in any monitor.

	int get_monitor_at_window(const Window& window) const;
	///< Returns the number of the monitor in which the largest area of the bounding
	///< rectangle of window resides.
	///< @param window A Window.
	///< @return The monitor number in which most of window is located, or if window
	///< does not intersect any monitors, a monitor close to window.

	bool get_setting(const char *name, G::Value& value) const;
	bool get_setting(const String& name, G::Value& value) const;
	///< Retrieves a desktop-wide setting such as double-click time for the screen.
	///< @param name The name of the setting.
	///< @param value The location to store the value of the setting.
	///< @return <EM>true</EM> if the setting existed and a value was stored in value,
	///< <EM>false</EM> otherwise.

/// @}
/// @name Accessors
/// @{

	static Screen* get_default();
	///< Gets the default screen.
	///< @return The default Screen, or null if there is no default display.

/// @}
/// @name Methods
/// @{

	void set_default_colormap(Colormap& colormap);
	///< Sets the default colormap for the screen.
	///< @param colormap A Colormap.

	void broadcast_client_message(Event& event);
	///< Sends an X ClientMessage event to all toplevel windows on the screen.
	///< @param event The Event.
	///<
	///< Toplevel windows are determined by checking for the WM_STATE property,
	///< as described in the Inter-Client Communication Conventions Manual (ICCCM).
	///< If no windows are found with the WM_STATE property set, the message is sent
	///< to all children of the root window.

/// @}
/// @name Signal Proxies
/// @{

	const SizeChangedSignalProxy signal_size_changed();
	///< Connect to the size_changed_signal; emitted when the size of the screen changes.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/screen.inl>

#endif // XFC_GDK_SCREEN_HH


