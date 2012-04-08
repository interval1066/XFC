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
 
/// @file xfc/gdk/window.hh
/// @brief A GdkWindow C++ wrapper interface.
///
/// Provides Window, an object that represents onscreen display areas in the target window system.

#ifndef XFC_GDK_WINDOW_HH
#define XFC_GDK_WINDOW_HH

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef XFC_GDK_DRAWABLE_HH
#include <xfc/gdk/drawable.hh>
#endif

#ifndef XFC_GDK_EVENTS_HH
#include <xfc/gdk/events.hh>
#endif

namespace Xfc {

namespace Gdk {

class Cursor;
class Pixbuf;

/// @enum WindowType
/// Describes the kind of window.

enum WindowType
{
	WINDOW_ROOT = GDK_WINDOW_ROOT,
	///< The root window; this window has no parent, covers the entire screen,
	///< and is created by the window system.

	WINDOW_TOPLEVEL = GDK_WINDOW_TOPLEVEL,
	///< Toplevel window (used to implement Gtk::Window)
	
	WINDOW_CHILD = GDK_WINDOW_CHILD,
	///< Child window (used to implement e.g. Gtk::Button)
	
	WINDOW_DIALOG = GDK_WINDOW_DIALOG,
	///< Useless/deprecated compatibility type.

	WINDOW_TEMP = GDK_WINDOW_TEMP,
	///< Override redirect temporary window (used to implement Gtk::Menu)

	WINDOW_FOREIGN = GDK_WINDOW_FOREIGN
	///< Foreign window.
};

/// @enum WMDecoration
/// Specifies hints the window manager can use when determining how to decorate
/// a window. The hint must be set before mapping the window. These hints were
/// originally defined by the Motif toolkit.

enum WMDecoration
{
	DECOR_ALL = GDK_DECOR_ALL, ///< All decorations should be applied.
	DECOR_BORDER = GDK_DECOR_BORDER, ///< A frame should be drawn around the window.
	DECOR_RESIZEH = GDK_DECOR_RESIZEH, ///< The frame should have resize handles.
	DECOR_TITLE = GDK_DECOR_TITLE, ///< A titlebar should be placed above the window.
	DECOR_MENU = GDK_DECOR_MENU, ///< A button for opening a menu should be included.
	DECOR_MINIMIZE = GDK_DECOR_MINIMIZE, ///< A minimize button should be included.
	DECOR_MAXIMIZE = GDK_DECOR_MAXIMIZE ///< A maximize button should be included.
};

/// WMDecorationField holds one or more values from the Gdk::WMDecoration enumeration OR'd together.

typedef unsigned int WMDecorationField;

/// @enum WMFunction
/// Specifies hints the window manager can use when determining the functions to offer
/// for the window. The hint must be set before mapping the window. These hints were
/// originally defined by the Motif toolkit.

enum WMFunction
{
	FUNC_ALL = GDK_FUNC_ALL, ///< All functions should be offered.
	FUNC_RESIZE = GDK_FUNC_RESIZE, ///< The window should be resizable.
	FUNC_MOVE = GDK_FUNC_MOVE, ///< The window should be movable.
	FUNC_MINIMIZE = GDK_FUNC_MINIMIZE, ///< The window should be minimizable.
	FUNC_MAXMIZE = GDK_FUNC_MAXIMIZE, ///< The window should be maximizable.
	FUNC_CLOSE = GDK_FUNC_CLOSE ///< The window should be closable.
};

/// WMFunctionField holds one or more values from the Gdk::WMFunction enumeration OR'd together.

typedef unsigned int WMFunctionField;

/// @name Window Methods
/// @{

Window* get_default_root_window();
///< Obtains the root window (parent all other windows are inside)
///< for the default display and screen.
///< @return The default root window.

/// @}

/// @class Geometry window.hh xfc/gdk/window.hh
/// @brief A GdkGeometry C++ wrapper class.
///
/// The Geometry object gives the window manager information about a window's geometry constraints.
/// Normally you would set these using Gtk::Window::set_geometry_hints(). Gtk::Window then sets the
/// hints on the Gdk::Window it creates.
///
/// Gdk::Window::set_geometry_hints() expects the hints to be fully valid already and simply passes
/// them to the window manager. In contrast, Gtk::Window::set_geometry_hints() performs some 
/// interpretation. For example, Gtk::Window will apply the hints to the geometry widget instead
/// of the toplevel window, if you set a geometry widget. Also, if the min_width, min_height, max_width
/// and max_height fields may be set to -1, Gtk::Window will substitute the size request of the window
/// or geometry widget. If the minimum size hint is not provided, Gtk::Window will use its requisition
/// as the minimum size. If the minimum size is provided and a geometry widget is set, Gtk::Window will
/// take the minimum size as the minimum size of the geometry widget rather than the entire window. The
/// base size is treated similarly.
///
/// The canonical use-case for Gtk::Window::set_geometry_hints() is to get a terminal widget to
/// resize properly. Here, the terminal text area should be the geometry widget; Gtk::Window will
/// then automatically set the base size to the size of other widgets in the terminal window, such
/// as the menubar and scrollbar. Then, the width_inc and height_inc fields should be set to the
/// size of one character in the terminal. Finally, the base size should be set to the size of one
/// character. The net effect is that the minimum size of the terminal will have a 1x1 character
/// terminal area, and only terminal sizes on the "character grid" will be allowed.
///
/// <B>Example:</B> How the terminal would be implemented.
/// @code
/// Gtk::Widget *terminal; // Assume a terminal area widget exists.
/// Gtk::Window *toplevel; // Assume a toplevel window exists.
/// Geometry hints;
///
/// hints.set_base_size(terminal->char_width, terminal->char_height);
/// hints.set_min_size(terminal->char_width, terminal->char_height);
/// hints.set_resize_increments(terminal->char_width, terminal->char_height);
/// toplevel->set_geometry_hints(terminal, hints);
/// @endcode
///
/// Geometry uses default copy, assignment and destruction.

class Geometry : public StackObject
{
	GdkGeometry geometry_;
	unsigned int mask_;

public:
/// @name Constructors
/// @{

	Geometry();
	///< Construct an empty geometry object

/// @}
/// @name Accessors
/// @{

	GdkGeometry* gdk_geometry() const;
	///< Get a pointer to the GdkGeometry structure.

	GdkWindowHints gdk_window_hints () const;
	///< Returns the bit flags that indicate which values are currently set.

	int min_width() const;
	///< Returns the minimum window width.

	int min_height() const;
	///< Returns the minimum window height.

	int max_width() const;
	///< Returns the maximum window width.

	int max_height() const;
	///< Returns the maximum window height.

	int base_width() const;
	///< Returns the base window width.

	int base_height() const;
	///< Returns the base window height.

	int width_increment() const;
	///< Returns the resize increment for the width.

	int height_increment() const;
	///< Returns the resize increment for the height.

	double min_aspect_ratio() const;
	///< Returns the minimum width/height ratio.

	double max_aspect_ratio() const;
	///< Returns the maximum width/height ratio.

	bool min_size_set() const;
	///< Returns true if the min size fields are set.

	bool max_size_set() const;
	///< Returns true if the max size fields are set.

	bool base_size_set() const;
	///< Returns true if the base size fields are set.

	bool aspect_range_set() const;
	///< Returns true if the aspect ratio fields are set.

	bool resize_increments_set() const;
	///< Returns true if the resize increment fields are set

/// @}
/// @name Methods
/// @{

	void set_min_size(int width, int height);
	///< Sets the minimum window size.
	///< @param width The minimum window width.
	///< @param height The minimum window height.

	void unset_min_size();
	///< Unsets the minimum size so that the minimum width and height fields will be ignored.

	void set_max_size(int width, int height);
	///< Sets the maximum window size.
	///< @param width The maximum window width.
	///< @param height The maximum window height.

	void unset_max_size();
	///< Unsets the maximum size so that the maximum width and height fields will be ignored.

	void set_base_size(int width, int height);
	///< Sets the base window size.
	///< @param width The base window width.
	///< @param height The base window height.

	void unset_base_size();
	///< Unsets the base size so that the base width and height fields will be ignored.

	void set_resize_increments(int width_inc, int height_inc);
	///< Sets the resize increments.
	///< @param width_inc The resize increment for the width.
	///< @param height_inc The resize increment for the height.

	void unset_resize_increments();
	///< Unsets the resize increments so that the width_inc and height_inc fields will be ignored.

	void set_aspect_range(double min_aspect_ratio, double max_aspect_ratio);
	///< Sets the aspect range.
	///< @param min_aspect_ratio The minimum width/height aspect ratio.
	///< @param max_aspect_ratio The maximum width/height aspect ratio.

	void unset_aspect_range();
	///< Unsets the aspect range so that the min_aspect_ratio and max_aspect_ratio fields will be ignored.

	void constrain_size(unsigned int flags, int width, int height, int *new_width, int *new_height);
	///< Constrains a desired width and height according to a set of geometry hints
	///< (such as minimum and maximum size).
	///< @param flags A mask indicating what portions of geometry are set.
	///< @param width The desired width of the window.
	///< @param height The desired height of the window.
	///< @param new_width The location to store resulting width.
	///< @param new_height The location to store resulting height.

/// @}
};

/// @class WindowAttr window.hh xfc/gdk/window.hh
/// @brief A GdkWindowAttr C++ wrapper class.
///
/// WindowAttr is used to specify the attributes to use for a newly-created window.
/// It handles the the attibute mask internally; you only need to set the attributes
/// you want and pass the WindowAttr to a Gdk::Window constructor. You can re-use
/// the same WindowAttr be resetting one or more of the attributes.

class WindowAttr : public StackObject
{
	GdkWindowAttr attr_;
	int mask_;

public:
/// @name Constructors
/// @{

	WindowAttr(int width, int height, WindowType type, EventMaskField event_mask = 0);
	///< Construct a new WindowAttr object used to set the creation attributes for a new Gdk::Window.
	///< @param width The width of the new window.
	///< @param height The height of the new window.
	///< @param type The window type to create; one of the types in the Gdk::WindowType enumeration.
	///< @param event_mask The event mask for the new window; determines which events are reported for the window.

	WindowAttr(int x, int y, int width, int height, WindowType type, EventMaskField event_mask = 0);
	///< Construct a new WindowAttr object used to set the creation attributes for a new Gdk::Window.
	///< @param x The X coordinate for the upper-left corner of the window.
	///< @param y The Y coordinate for the upper-left corner of the window.
	///< @param width The width of the new window.
	///< @param height The height of the new window.
	///< @param type The window type to create; one of the types in the Gdk::WindowType enumeration.
	///< @param event_mask The event mask for the new window; determines which events are reported for the window.

	WindowAttr(const Rectangle& allocation, WindowType type, EventMaskField event_mask = 0);
	///< Construct a new WindowAttr object used to set the creation attributes for a new Gdk::Window.
	///< @param allocation The x, y, width and height of the new window. Call Gtk::Widget::get_allocation().
	///< @param type The window type to create; one of the types in the Gdk::WindowType enumeration.
	///< @param event_mask The event mask for the new window; determines which events are reported for the window.

/// @}
/// @name Methods
/// @{

	GdkWindowAttr* gdk_window_attr() const;
	///< Get a pointer to the GdkWindowAttr structure.

	int mask() const { return mask_; }
	///< Returns the bit flags that indicate which attributes are currently set.

	void set_title(const String& title);
	///< Set the title for a toplevel window.
	///< @param title The window title text.

	void set_type(WindowType type);
	///< Set the window type.
	///< @param type The window type to create; one of the types in the Gdk::WindowType enumeration.

	void set_events(EventMaskField event_mask);
	///< Set the events that will be reported for the window.
	///< @param event_mask The event mask for the new window.

	void set_position(int x, int y);
	///< Set the position of the window.
	///< @param x The X coordinate for the upper-left corner of the window.
	///< @param y The Y coordinate for the upper-left corner of the window.

	void set_size(int width, int height);
	///< Set the size of the window.
	///< @param width The width of the new window.
	///< @param height The height of the new window.

	void set_allocation(int x, int y, int width, int height);
	///< Set the positon and size of the window.
	///< @param x The X coordinate for the upper-left corner of the window.
	///< @param y The Y coordinate for the upper-left corner of the window.
	///< @param width The width of the new window.
	///< @param height The height of the new window.

	void set_allocation(const Rectangle& allocation);
	///< Set the positon and size of the window.
	///< @param allocation The x, y, width and height of the new window. Call Gtk::Widget::get_allocation().

	void set_cursor(const Cursor& cursor);
	///< Set the cursor the window will use.
	///< @param cursor A Cursor.

	void set_visual(const Visual& visual);
	///< Set the Visual for the window.
	///< @param visual a Visual.

	void set_colormap(const Colormap& colormap);
	///< Set the colormap for the window
	///< @param colormap A colormap.

	void set_input_only();
	///< Sets the GDK_INPUT_ONLY flag.
	///< Windows are GDK_INPUT_OUTPUT by default so that they can receive events and 
	///< be displayed on the screen. Only use this method in special circumstances when
	///< events need to be stolen from another window or windows. Input only windows
	///< have no visible output, so they are handy for placing over the top of a group
	///< of windows in order to grab the events (or filter the events) from those windows.

	void set_override_redirect();
	///< Sets the override_redirect flag to <EM>true</EM> so that the window bypasses the window manager.

/// @}
};

/// @class Window window.hh xfc/gdk/window.hh
/// @brief A GdkWindow C++ wrapper class.
///
/// A Gdk::Window is a rectangular region on the screen. It's a low-level object,
/// used to implement high-level objects such as Gtk::Widget and Gtk::Window. A
/// Gtk::Window is a toplevel window, the thing a user might think of as a
/// "window" with a titlebar and so on; a Gtk::Window may contain many Gdk::Window.
/// For example, each Gtk::Button has a Gdk::Window associated with it.

class Window : public Drawable
{
	friend class G::Object;

	Window(const Window&);
	Window& operator=(const Window&);
	
protected:
/// @name Constructors
/// @{

	explicit Window(GdkWindow *window, bool owns_reference = true);
	///< Construct a new Gdk::Window from an existing GdkWindow.
	///< @param window A pointer to a GdkWindow.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>window</EM> can be a newly created GdkWindow or an existing
	///< GdkWindow. (see G::Object::Object).

/// @}
	
public:
	typedef GdkWindow CObjectType;

/// @name Constructors
/// @{

	Window(const WindowAttr& attributes);
	///< Construct a new window with the root window of the default display as the parent.
	///< @param attributes The attributes of the new window.
	///< 
	///< A Gdk::Window must be explicitly destroyed by calling dispose(). 

	Window(const Window& parent, const WindowAttr& attributes);
	///< Construct a new window with <EM>parent</EM> as the parent.
	///< @param parent A Gdk::Window.
	///< @param attributes The attributes of the new window.
	///<
	///< This is the constructor to use to create a new window on a display 
	///< other than the default display. A Gdk::Window must be explicitly destroyed
	///< by calling dispose().

	virtual ~Window();
	///< Destructor.
	
/// @}
/// @name Constructors
/// @{

	static Pointer<Window> create(GdkNativeWindow anid, const Display *display = 0);
	///< Wraps a native window in a Gdk::Window.
	///< @param anid A native window handle.
	///< @param display The Display where the window handle comes from, or null for the default display.
	///< @return A smart pointer to the newly-created Gdk::Window wrapper for the native window,
	///< or null if the window has been destroyed.
	///<
	///< In the X backend, a native window handle is an Xlib XID. This method
	///< fail if the pixmap has been destroyed.

/// @}
/// @name Accessors
/// @{

	GdkWindow* gdk_window() const;
	///< Get a pointer to the GdkWindow structure.

	GdkWindowObject* gdk_window_object() const;
	///< Get a pointer to the GdkWindowObject structure.

	operator GdkWindow* () const;
	///< Conversion operator; safely converts an Gdk::Window to a GdkWindow pointer.

	WindowType get_window_type() const;
	///< Returns the type of the window (see Gdk::WindowType).

	bool is_visible() const;
	///< Gets whether the window has been mapped (with show() or show_unraised()).
	///< @return <EM>true</EM> if the window is mapped.

	bool is_viewable() const;
	///< Checks if the window and all ancestors of the window are mapped. 
	///< @return <EM>true</EM> if the window is viewable.
	///< 
	///< This is not necessarily "viewable" in the X sense, since we only check
	///< as far as we have GDK window parents, not to the root window.

	WindowState get_state() const;
	///< Gets the bitwise OR of the currently active window state flags, from the Gdk::WindowState enumeration.
	///< @return The window state bitfield.

	void get_user_data(void *&data) const;
	///< Retrieves the user data for window, which is normally the widget that window belongs to
	///< (see set_user_data()).
	///< @param data A reference to the return location for the user data.

	void get_geometry(int *x, int *y, int *width, int *height, int *depth) const;
	///< Gets the current geometry of the window.
	///< @param x The return location for the X coordinate of the window (relative to its parent).
	///< @param y The return location for the Y coordinate of the window (relative to its parent).
	///< @param width The return location for the width of the window.
	///< @param height The return location for the height of the window.
	///< @param depth The return location for the bit depth of the window.
	///<
	///< Any of the return location arguments to this method may be null, if you aren't
	///< interested in getting the value of that field. The X and Y coordinates returned are
	///< relative to the parent window of window, which for toplevels usually means relative
	///< to the window decorations (titlebar, etc.) rather than relative to the root window
	///< (screen-size background window).
	///<
	///< On the X11 platform, the geometry is obtained from the X server, so reflects the
	///< latest position of window; this may be out-of-sync with the position of window
	///< delivered in the most-recently-processed Gdk::EventConfigure. get_position() in
	///< contrast gets the position from the most recent configure event.

	void get_geometry(Rectangle& rectangle, int *depth) const;
	///< Gets the current geometry of the window.
	///< @param rectangle The return location for the x, y  coordinates, width and height
	///<                  of the window (relative to its parent).
	///< @param depth The return location for the bit depth of the window.
	///<
	///< The depth argument may be null, if you aren't interested in getting the depth. 
	///< The X and Y coordinates returned are relative to the parent window of window, which
	///< for toplevels usually means relative to the window decorations (titlebar, etc.) 
	///< rather than relative to the root window (screen-size background window).
	///<
	///< On the X11 platform, the geometry is obtained from the X server, so reflects the
	///< latest position of window; this may be out-of-sync with the position of window
	///< delivered in the most-recently-processed Gdk::EventConfigure. get_position() in
	///< contrast gets the position from the most recent configure event.

	void get_position(int *x, int *y) const;
	///< Obtains the position of the window as reported in the most-recently-processed
	///< Gdk::EventConfigure.
	///< @param x The X coordinate of the window relative to the window's parent window.
	///< @param y The Y coordinate of the window relative to the window's parent window.
	///<
	///< Contrast with get_geometry() which queries the X server for the current window
	///< position, regardless of which events have been received or processed. The position
	///< coordinates are relative to the window's parent window.

	Point get_position() const;
	///< Obtains the position of the window as reported in the most-recently-processed
	///< Gdk::EventConfigure (see get_position(int*, int*) const).
	///< @return A Point containing the x, y coordinates of the window relative to the parent window.
	///<
	///< Contrast with get_geometry() which queries the X server for the current window
	///< position, regardless of which events have been received or processed. The position
	///< coordinates are relative to the window's parent window.

	bool get_origin(int *x, int *y) const;
	///< Obtains the position of a window in root window coordinates.
	///< @param x The return location for X coordinate.
	///< @param y The return location for Y coordinate.
	///< @return Nothing meaningful, ignore it.
	///<
	///< Compare with get_position() and get_geometry() which return the position
	///< of a window relative to its parent window.

	Point get_origin() const;
	///< Obtains the position of a window in root window coordinates.
	///< @return A Point holding the x, y coordinates.
	///<
	///< Compare with get_position() and get_geometry() which return the position
	///< of a window relative to its parent window.

	void get_root_origin(int *x, int *y) const;
	///< Obtains the top-left corner of the window manager frame in root window coordinates.
	///< @param x The return location for X position of the window frame.
	///< @param y The return location for Y position of the window frame.

	Point get_root_origin() const;
	///< Obtains the top-left corner of the window manager frame in root window coordinates.
	///< @return A Point containing the x, y position of the window frame.

	Window* get_pointer(int *x, int *y, ModifierTypeField *mask) const;
	///< Obtains the current pointer position and modifier state. 
	///< @param x The return location for X coordinate of the pointer.
	///< @param y The return location for Y coordinate of the pointer.
	///< @param mask The return location for modifier mask.
	///< @return The window containing the pointer (as with at_pointer()), or null
	///< if the window containing the pointer isn't known to GDK
	///<
	///< The position is given in coordinates relative to the window.

	Window* get_parent() const;
	///< Obtains the parent of window, as known to GDK. 
	///< @return The parent of the window.
	///<
	///< Does not query the X server; thus this returns the parent as passed to
	///< the Gdk::Window constructor, not the actual parent. This should never 
	///< matter unless you're using Xlib calls mixed with GDK calls on the X11
	///< platform. It may also matter for toplevel windows, because the window
	///< manager may choose to reparent them.

	Window* get_toplevel() const;
	///< Gets the toplevel window that's an ancestor of the window.
	///< @return The toplevel window containing the window.

	bool get_children(std::vector<Window*>& child_list) const;
	///< Gets the list of children of the window known to GDK.
	///< @param child_list A reference to a vector of Window* to hold the child windows.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< This method only returns children created via GDK, so for example
	///< it's useless when used with the root window; it only returns windows
	///< an application created itself.
	
	EventMaskField get_events() const;
	///< Gets the event mask for window (see set_events()).
	///< @return The event mask for window.

	Window* get_group() const;
	/// Gets the group leader window for this window (see set_group()).
	/// @return The group leader window for the window.
		
	bool get_decorations(WMDecorationField *decorations) const;
	///< Gets the decorations set on the window with set_decorations().
	///< @param decorations The return location for the window's Gdk::WMDecoration bitfield.
	///< @return <EM>true</EM> if the window has decorations set, false otherwise.

	Pointer<Region> get_update_area() const;
	///< Transfers ownership of the update area from the window to the caller of the method.
	///< @return The update area for the window, or null if there is no update area.
	///<
	///< After calling this method the window will no longer have an invalid/dirty region;
	///< the update area is removed from the window and handed to you.

	Rectangle get_frame_extents() const;
	///< Obtains the bounding box of the window, including window manager titlebar/borders if any.
	///< @return A Rectangle filled with bounding box of the window frame.
	///<
	///< The frame position is given in root window coordinates. To get the position of the
	///< window itself (rather than the frame) in root window coordinates, use get_origin().

	void get_frame_extents(Rectangle& rectangle) const;
	///< Obtains the bounding box of the window, including window manager titlebar/borders if any.
	///< @param rectangle The rectangle to fill with bounding box of the window frame.
	///<
	///< The frame position is given in root window coordinates. To get the position of the
	///< window itself (rather than the frame) in root window coordinates, use get_origin().

/// @}
/// @name Accessors
/// @{

	static Window* lookup(GdkNativeWindow anid, const Display *display = 0);
	///< Looks up the Gdk::Window that wraps the given native window handle.
	///< @param anid A native pixmap handle.
	///< @param display The Display corresponding to the window handle, or null for the default display.
	///< @return The Gdk::Window wrapper for the native window, or null if there is none.
	///<
	///< In the X backend, a native window handle is an Xlib XID.

	static Window* at_pointer(int *win_x, int *win_y, const Display *display = 0);
	///< Obtains the window underneath the mouse pointer on <EM>display</EM>, returning
	///< the location of that window in win_x, win_y.
	///< @param win_x The return location for the X coordinate of the origin of the window under the pointer.
	///< @param win_y The return location for the Y coordinate of the origin of the window under the pointer
	///< @param display The display to use, or null for the default display.
	///< @return A pointer to the Gdk::Window under the mouse pointer.
	///<
	///< Returns null if the window under the mouse pointer is not known to GDK
	///< (if the window belongs to another application and a Gdk::Window hasn't been
	///< created for it with create()).

	static Window* at_pointer(Point& point, const Display *display = 0);
	///< Obtains the window underneath the mouse pointer on <EM>display</EM>, returning
	///< the location of that window in <EM>point</EM>.
	///< @param point The return location for the x, y coordinates of the origin of the window under the pointer.
	///< @param display The display to use, or null for the default display.
	///< @return A pointer to the Gdk::Window under the mouse pointer.
	///<
	///< Returns null if the window under the mouse pointer is not known to GDK
	///< (if the window belongs to another application and a Gdk::Window hasn't been
	///< created for it with create()).

	static bool get_toplevels(std::vector<Window*>& toplevels);
	///< Obtains a list of all toplevel windows known to GDK on the default screen
	///< (see get_toplevels_for_screen()).
	///< @param toplevels A reference to a vector of Window* to hold the list of toplevel windows.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< A toplevel window is a child of the root window (see Gdk::get_default_root_window()).

	static void process_all_updates();
	///< Calls process_updates() for all the GDK windows in the application (see process_updates()).

	static void add_filter(Window *window, GdkFilterFunc function, void *data);
	///< Adds an event filter for <EM>window</EM>, allowing you to intercept events before they reach GDK.
	///< @param window The Gdk::Window to get the events for, or null for all windows.
	///< @param function The filter callback to call on each event.
	///< @param data Data to pass to filter callback.
	///<
	///< This is a low-level operation and makes it easy to break GDK and/or GTK+,
	///< so you have to know what you're doing.

	static void remove_filter(Window *window, GdkFilterFunc function, void *data);
	///< Remove a filter previously added with add_filter().
	///< @param window The Gdk::Window the filter was added to, or null for all windows.
	///< @param function The filter callback to call on each event.
	///< @param data Data to pass to filter callback.

/// @}
/// @name Methods
/// @{

	virtual void dispose();
	///< Destroys the window system resources associated with the window and
	///< decrements window's reference count. The window system resources for
	///< all children of window are also destroyed, but the children's reference
	///< counts are not decremented.
	///<
	///< <B>Note:</B> A Gdk::Window will not be destroyed automatically when its
	///< reference count reaches zero. You must call this method yourself before
	///< that happens. This method is declared virtual for XFC's use only.

	void show();
	///< Like show_unraised(), but also raises the window to the top of the
	///< window stack (moves the window to the front of the Z-order). This
	///< method maps a window so it's visible onscreen. It's opposite is hide().
	///<
	///< <B>Note:</B> When implementing a Gtk::Widget, you should call this
	///< method on the widget's Gdk::Window as part of the "map" method.

	void show_unraised();
	///< Shows a Gdk::Window onscreen, but does not modify its stacking order.
	///< In contrast, show() will raise the window to the top of the window stack.
	///< On the X11 platform, in Xlib terms, this function calls XMapWindow() 
	///< (it also updates some internal GDK state, which means that you can't
	///< really use XMapWindow() directly on a GDK window).

	void hide();
	///< For toplevel windows, withdraws them, so they will no longer be known
	///< to the window manager; for all windows, unmaps them, so they won't be
	///< displayed. Normally done automatically as part of Gtk::Widget::hide().

	void withdraw();
	///< Withdraws the window (unmaps it and asks the window manager to forget about it).
	///< This function is not really useful as hide() automatically withdraws toplevel
	///< windows before hiding them.
	
	void move(int x, int y);
	///< Repositions the window relative to its parent window.
	///< @param x The X coordinate relative to window's parent.
	///< @param y The Y coordinate relative to window's parent.
	///<
	///< For toplevel windows, window managers may ignore or modify the move;
	///< you should probably use Gtk::Window_move() on a Gtk::Window widget anyway,
	///< instead of using GDK methods. For child windows, the move will reliably succeed.
	///< If you're also planning to resize the window, use move_resize() to both move and
	///< resize simultaneously, for a nicer visual effect.

	void move(const Point& point);
	///< Repositions the window relative to its parent window.
	///< @param point The x, y coordinates relative to window's parent.
	///<
	///< For toplevel windows, window managers may ignore or modify the move;
	///< you should probably use Gtk::Window_move() on a Gtk::Window widget anyway,
	///< instead of using GDK methods. For child windows, the move will reliably succeed.
	///< If you're also planning to resize the window, use move_resize() to both move and
	///< resize simultaneously, for a nicer visual effect.

	void resize(int width, int height);
	///< Resizes the window; for toplevel windows, asks the window manager to resize the window. 
	///< @param width The new width of the window.
	///< @param height The new height of the window.
	///<
	///< The window manager may not allow the resize. Use Gtk::Window::resize()
	///< instead of this low-level method. Windows may not be resized below 1x1. If
	///< you're also planning to move the window, use move_resize() to both move and
	///< resize simultaneously, for a nicer visual effect.

	void move_resize(int x, int y, int width, int height);
	///< Equivalent to calling move() and resize(), except that both operations are
	///< performed at once, avoiding strange visual effects.
	///< @param x The X coordinate relative to window's parent.
	///< @param y The Y coordinate relative to window's parent.
	///< @param width The new width of the window.
	///< @param height The new height of the window.
	///<
	///< The user may be able to see the window first move, then resize, if you don't use move_resize().

	void move_resize(const Rectangle& rectangle);
	///< Equivalent to calling move() and resize(), except that both operations are
	///< performed at once, avoiding strange visual effects.
	///< @param rectangle A Gdk::Rectangle holding the new x, y coordinates relative to
	///< window's parent, and the new width and height.

	void reparent(Window& new_parent, int x, int y);
	///< Reparents the window into the given new_parent. The window being reparented
	///< will be unmapped as a side effect.
	///< @param new_parent The new parent to move window into.
	///< @param x The X location inside the new parent.
	///< @param y The Y location inside the new parent.

	void clear();
	///< Clears the entire window to the background color or background pixmap.

	void clear_area(int x, int y, int width, int height, bool generate_expose = false);
	///< Clears an area of the window to the background color or background pixmap.
	///< @param x The X coordinate of the origin of rectangle to clear.
	///< @param y The Y coordinate of the origin of rectangle to clear.
	///< @param width The width of the rectangle to clear.
	///< @param height The height of the rectangle to clear.
	///< @param generate_expose If <EM>true</EM> generates an expose event for the cleared area.

	void clear_area(const Rectangle& rectangle, bool generate_expose = false);
	///< Clears an area of the window to the background color or background pixmap.
	///< @param rectangle The rectangle to clear.
	///< @param generate_expose If <EM>true</EM> generates an expose event for the cleared area.

	void raise();
	///< Raises the window to the top of the Z-order (stacking order), so that other windows
	///< with the same parent window appear below the window.
	///<
	///< This method works whether or not the windows are visible. If window is a toplevel,
	///< the window manager may choose to deny the request to move the window in the Z-order,
	///< raise() only requests the restack, does not guarantee it.

	void lower();
	///< Lowers the window to the bottom of the Z-order (stacking order), so that other windows
	///< with the same parent window appear above the window.
	///<
	///< This is true whether or not the other windows are visible. If the window is a
	///< toplevel, the window manager may choose to deny the request to move the window in
	///< the Z-order, lower() only requests the restack, does not guarantee it.
	///<
	///< Note that show() raises the window again, so don't call this function before show()
	///< (try show_unraised()).

	void focus(unsigned int timestamp);
	///< Sets keyboard focus to the window.
	///< @param timestamp A timestamp of the event triggering the window focus.
	///<
	///< If window is not onscreen this method will not work. In most cases, 
	///< Gtk::Window::present() should be used on a Gtk::Window, rather than 
	///< calling this method.

	void set_user_data(void *user_data);
	///< For most purposes this method is deprecated in favor of G::Object::set_data().
	///< @param user_data The user_data.
	///<
	///< For historical reasons GTK+ stores the GtkWidget that owns a Gdk::Window
	///< as user data on the Gdk::Window. So, custom widget implementations should use
	///< this method for that. If GTK+ receives an event for a Gdk::Window, and the
	///< user data for the window is non-null, GTK+ will assume the user data is a
	///< GtkWidget, and forward the event to that widget.
	
	void set_override_redirect(bool override_redirect);
	///< An override redirect window is not under the control of the window manager (this means
	///< it won't have a titlebar, won't be minimizable, etc., it will be entirely under the
	///< control of the application).
	///< @param override_redirect <EM>true</EM> if window should be override redirect.
	///<
	///< The window manager can't see the override redirect window at all. Override redirect
	///< should only be used for short-lived temporary windows, such as popup menus. Gtk::Menu
	///< uses an override redirect window in its implementation, for example.

	void set_accept_focus(bool accept_focus);
	///< Setting accept_focus to <EM>false</EM> hints the desktop environment that the window
	///< doesn't want to receive the input focus.
	///< @param accept_focus Set <EM>true</EM> if the window should receive input focus.
	///<
	///< On X, it is the responsibility of the window manager to interpret this hint.
	///< ICCCM-compliant window managers usually respect it.

	void set_focus_on_map(bool focus_on_map);
	///< Setting <EM>focus_on_map</EM> to false hints the desktop environment that the window
	///< doesn't want to receive input focus when it is mapped. 
	///< @param focus_on_map Set to <EM>true</EM> if the window should receive input focus when mapped.	
	///< 	
	///< The <EM>focus_on_map</EM> property should be turned off for windows that aren't triggered
	///< interactively (such as popups from network activity). On X, it is the responsibility of 
	///< the window manager to interpret this hint. Window managers following the freedesktop.org
	///< window manager extension specification should respect it.
	
	void scroll(int dx, int dy);
	///< Scroll the contents of window, both pixels and children, by the given amount.
	///< @param dx The amount to scroll in the X direction.
	///< @param dy The amount to scroll in the Y direction.
	///<
	///< The window itself does not move. Portions of the window that the scroll
	///< operation brings in from offscreen areas are invalidated. The invalidated
	///< region may be bigger than what would strictly be necessary. (For X11, a
	///< minimum area will be invalidated if the window has no subwindows, or if the
	///< edges of the window's parent do not extend beyond the edges of the window.
	///< In other cases, a multi-step process is used to scroll the window which may
	///< produce temporary visual artifacts and unnecessary invalidations.)

	void shape_combine_mask(Bitmap *shape_mask, int x = 0, int y = 0);
	///< Make a shaped partially transparent window using a bitmap mask.
	///< @param shape_mask The shape mask, or null to unset a previously set shape mask.
	///< @param x The X position of <EM>shape_mask</EM> with respect to the window.
	///< @param y The Y position of <EM>shape_mask</EM> with respect to the window.
	///<
	///< Applies <EM>shape_mask</EM> to the window. Pixels in the window corresponding
	///< to set bits in the mask will be visible; pixels in the window corresponding to 
	///< unset bits in the mask will be transparent. This gives a non-rectangular window.
	///< If <EM>shape_mask</EM> is null, the shape mask will be unset, and the x/y parameters
	///< are not used.
	///<
	///< On the X11 platform, this uses an X server extension which is widely available
	///< on most common platforms, but not available on very old X servers, and occasionally
	///< the implementation will be buggy. On servers without the shape extension, this
	///< method will do nothing.
	///<
	///< <B>Note:</B> This method works on both toplevel and child windows.

	void shape_combine_region(Region *shape_region, int offset_x = 0, int offset_y = 0);
	///< Makes pixels in the window outside <EM>shape_region</EM> be transparent, so that
	///< the window may be non-rectangular (see also shape_combine_mask() to use a bitmap
	///< as the mask.
	///< @param shape_region The region of the window to be non-transparent, 
	///<                     or null to unset a previously set <EM>shape_region</EM>.
	///< @param offset_x The X position of <EM>shape_region</EM> in window coordinates.
	///< @param offset_y The Y position of <EM>shape_region</EM> in window coordinates.
	///<
	///< If <EM>shape_region</EM> is null, the shape will be unset, so the whole
	///< window will be opaque again. <EM>offset_x</EM> and <EM>offset_y</EM> are ignored
	///< if <EM>shape_region</EM> is null.
	///<
	///< On the X11 platform, this uses an X server extension which is widely available
	///< on most common platforms, but not available on very old X servers, and occasionally
	///< the implementation will be buggy. On servers without the shape extension, this
	///< method will do nothing.
	///<
	///< <B>Note:</B> This method works on both toplevel and child windows.
	
	void set_child_shapes();
	///< Sets the shape mask of the window to the union of shape masks for all children of the
	///< window, ignoring the shape mask of the window itself. Contrast with merge_child_shapes()
	///< which includes the shape mask of the window in the masks to be merged. This method
	///< quickly takes the shapes of all the child windows and uses their shapes as the shape
	///< mask for this window.
	
	void merge_child_shapes();
	///< Merges the shape masks for any child windows into the shape mask for this window
	///< (that is, the union of all masks for the window and its children will become the
	///< new mask for window (see shape_combine_mask()). This method is distinct from 
	///< set_child_shapes() because it includes window's shape mask in the set of shapes
	///< to be merged.
	
	bool set_static_gravities(bool use_static);
	///< Set the bit gravity of the window to static and flag it so all children get
	///< static subwindow gravity.
	///< @param use_static set <EM>true</EM> to turn on static gravity.
	///< @return <EM>true</EM> if the server supports static gravity.
	///<
	///< This is used if you are implementing scary features that involve deep
	///< knowledge of the windowing system. Don't worry about it unless you have to.

	void set_type_hint(WindowTypeHint hint);
	///< The application can use this call to provide a hint to the window manager
	///< about the functionality of the window.
	///< @param hint A hint of the function this window will have.
	///<
	///< The window manager can use this information when determining the decoration
	///< and behaviour of the window. The hint must be set before the window is mapped.

	void set_modal_hint(bool modal);
	///< The application can use this hint to tell the window manager that a certain
	///< window has modal behaviour. 
	///< @param modal Set <EM>true</EM> if the window is modal, <EM>false</EM> otherwise.
	///<
	///< The window manager can use this information to handle modal windows in a special way.
	///< You should only use this on windows for which you have previously called set_transient_for().

	void set_skip_taskbar_hint(bool skips_taskbar);
	///< Toggles whether the window should appear in a task list or window list.
	///< @param skips_taskbar Set <EM>true</EM> to skip the taskbar.
	///<
	///< If a window's semantic type as specified with set_type_hint() already fully
	///< describes the window, this method should NOT be called in addition, instead you
	///< should allow the window to be treated according to standard policy for its 
	///< semantic type.
	
	void set_skip_pager_hint(bool skips_pager);
	///< Toggles whether the window should appear in a pager (workspace switcher, or other
	///< desktop utility program that displays a small thumbnail representation of the 
	///< windows on the desktop). 
	///< @param skips_pager Set <EM>true</EM> to skip the pager.
	///<
	///< If a window's semantic type as specified with set_type_hint() already fully
	///< describes the window, this function should NOT be called in addition, instead 
	///< you should allow the window to be treated according to standard policy for its
	///< semantic type.

	void set_geometry_hints(const Geometry *geometry);
	///< Sets the geometry hints for the window. 
	///< @param geometry A Geometry object containing geometry information, or null to unset all hints.
	///<
	///< Geometry hints not specifically set in geometry will be unset. To unset all hints
	///< pass a geometry of null.
	///<
	///< This method provides hints to the windowing system about acceptable sizes
	///< for a toplevel window. The purpose of this is to constrain user resizing, 
	///< but the windowing system will typically (but is not required to) also constrain
	///< the current size of the window to the provided values and constrain programatic
	///< resizing via resize() or move_resize().
	///< 
	///< Note that on X11, this effect has no effect on windows of type WINDOW_TEMP or 
	///< windows where override_redirect has been turned on via set_override_redirect()
	///< since these windows are not resizable by the user.
	///<
	///< Since you can't count on the windowing system doing the constraints for programmatic
	///< resizes, you should generally call Gdk::Geometry::constrain_size() yourself to
	///< determine appropriate sizes.

	void begin_paint(const Rectangle& rectangle);
	///< Indicates that you are beginning the process of redrawing a rectangular region.
	///< @param rectangle The rectangualr region you intend to draw to.
	///<
	///< This method is a convenience wrapper around begin_paint(const Region&)) which
	///< creates a rectangular region for you.

	void begin_paint(const Region& region);
	///< Indicates that you are beginning the process of redrawing region. 
	///< @param region The region you intend to draw to.
	///<
	///< A backing store (offscreen buffer) large enough to contain region will be created.
	///< The backing store will be initialized with the background color or background pixmap
	///< for the window. Then, all drawing operations performed on window will be diverted to
	///< the backing store. When you call end_paint(), the backing store will be copied to the
	///< window, making it visible onscreen. Only the part of the window contained in the region
	///< will be modified; that is, drawing operations are clipped to the region. The net result
	///< of all this is to remove flicker, because the user sees the finished product appear all
	///< at once when you call end_paint(). If you draw to the window directly without calling
	///< begin_paint(), the user may see flicker as individual drawing operations are performed
	///< in sequence. The clipping and background-initializing features of begin_paint() are
	///< conveniences for the programmer, so you can avoid doing that work yourself.
	///<
	///< The GTK+ widget system automatically places calls to begin_paint() and end_paint()
	///< around emissions of the <EM>expose_event</EM> signal. That is, if you're writing an
	///< expose event handler, you can assume that the exposed area in Gdk::EventExpose has
	///< already been cleared to the window background, is already set as the clip region,
	///< and already has a backing store. Therefore in most cases, application code need not
	///< call begin_paint(). You can disable the automatic calls around expose events on a
	///< widget-by-widget basis by calling Gtk::Widget::set_double_buffered().
	///<
	///< If you call this method multiple times before calling the matching end_paint(),
	///< the backing stores are pushed onto a stack. end_paint() copies the topmost backing
	///< store onscreen, subtracts the topmost region from all other regions in the stack,
	///< and pops the stack. All drawing operations affect only the topmost backing store in
	///< the stack. One matching call to end_paint() is required for each call to begin_paint().

	void end_paint();
	///< Indicates that the backing store created by the most recent call to begin_paint() should
	///< be copied onscreen and deleted, leaving the next-most-recent backing store or no backing
	///< store at all as the active paint region (see begin_paint(const Region&) for full details).
	///< It is an error to call this method without a matching begin_paint() first.

	void set_title(const char *title);
	void set_title(const String& title);
	///< Sets the title of a toplevel window, to be displayed in the titlebar.
	///< @param title The title of the window.
	///<
	///< If you haven't explicitly set the icon name for the window (using set_icon_name()),
	///< the icon name will be set to title as well.

	void set_role(const char *role);
	void set_role(const String& role);
	///< Typically you should use Gtk::Window::set_role() instead of this low-level method.
	///< @param role A string indicating its role.
	///<
	///< The window manager and session manager use a window's role to distinguish
	///< it from other kinds of window in the same application. When an application is
	///< restarted after being saved in a previous session, all windows with the same
	///< title and role are treated as interchangeable. So if you have two windows with
	///< the same title that should be distinguished for session management purposes, you
	///< should set the role on those windows. It doesn't matter what string you use for
	///< the role, as long as you have a different role for each non-interchangeable kind
	///< of window.

	void set_transient_for(Window& parent);
	///< Indicates to the window manager that window is a transient dialog
	///< associated with the application window parent. 
	///< @param parent Another toplevel Gdk::Window.
	///<
	///< This allows the window manager to do things like center window on parent
	///< and keep window above parent. See Gtk::Window::set_transient_for() if you're
	///< using Gtk::Window or Gtk::Dialog.

	void set_background(const Color& color);
	///< Sets the background color of the window.
	///< @param color An allocated Color.
	///<
	///< When using a Gtk::Widget, set the background of the widget with Gtk::Widget::modify_bg()
	///< if you're an application, or Gtk::Style::set_background() if you're implementing a custom
	///< widget. The color must be allocated; Gdk::Colormap::rgb_find_color() is the best way to
	///< allocate a color. See also set_back_pixmap().

	void set_back_pixmap(Pixmap *pixmap, bool parent_relative = false);
	///< Sets the background pixmap of the window.
	///< @param pixmap A Pixmap, or null for no background.
	///< @param parent_relative Whether the tiling origin is at the origin of window's parent.
	///<
	///< To set a background of "None" on the window, set a background pixmap of null. 
	///< A background pixmap will be tiled, positioning the first tile at the origin of
	///< the window, or if parent_relative is true, the tiling will be done based on the
	///< origin of the parent window (useful to align tiles in a parent with tiles in a child).
	///<
	///< A background pixmap of null means that the window will have no background. A window with
	///< no background will never have its background filled by the windowing system, instead the
	///< window will contain whatever pixels were already in the corresponding area of the display.
	///< The windowing system will normally fill a window with its background when the window is
	///< obscured then exposed, and when you call clear().

	void set_cursor(const Cursor& cursor);
	///< Sets the mouse pointer for the window.
	///< @param cursor A Cursor.
	///<
	///< By default, most windows use the cursor of its parent window.
	
	void set_events(EventMaskField event_mask);
	///< Sets the event mask for the window.
	///< @param event_mask The event mask for the window.
	///<
	///< The event mask for a window determines which events will be reported
	///< for that window. For example, an event mask including BUTTON_PRESS_MASK
	///< means the window should report button press events. The event mask is 
	///< the bitwise OR of values from the EventMask enumeration.

	void set_icon_list(const std::vector<Pixbuf*>& pixbufs);
	///< Sets a list of icons for the window.
	///< @param pixbufs A reference to a vector of Pixbuf* that holds a list of pixbufs, of different sizes.
	///<
	///< One of these will be used to represent the window when it has been iconified.
	///< The icon is usually shown in an icon box or some sort of task bar. Which icon size
	///< is shown depends on the window manager. The window manager can scale the icon but
	///< setting several size icons can give better image quality since the window manager
	///< may only need to scale the icon by a small amount or not at all.

	void set_icon(Pixmap *pixmap, Bitmap *mask, Window *icon_window = 0);
	///< Sets the icon of the window as a pixmap or window. 
	///< @param icon_window A Gdk::Window to use for the icon, or null to unset.
	///< @param pixmap A Pixmap to use as the icon, or null to unset.
	///< @param mask A 1-bit pixmap (Gdk::Bitmap) to use as mask for pixmap, or null for none.
	///<
	///< Investigate Gtk::Window::set_default_icon_list() first, and then
	///< Gtk::Window::set_icon_list() and Gtk::Window::set_icon(). If those 
	///< don't meet your needs, look at Gdk::Window::set_icon_list(). Only if
	///< all those are too high-level do you want to fall back to set_icon().

	void set_icon_name(const char *name);
	void set_icon_name(const String& name);
	///< Windows may have a name used while minimized, distinct from the name
	///< they display in their titlebar. 
	///< @param name The name of window while iconified (minimized).
	///<
	///< Most of the time this is a bad idea from a user interface standpoint.
	///< But you can set such a name with this method, if you like.

	void set_group(Window& leader);
	///< Sets the group leader window for the window. 
	///< @param leader The group leader window.
	///<
	///< By default, GDK sets the group leader for all toplevel windows
	///< to a global window implicitly created by GDK. With this function you
	///< can override this default. The group leader window allows the window
	///< manager to distinguish all windows that belong to a single application.
	///< It may for example allow users to minimize/unminimize all windows 
	///< belonging to an application at once. You should only set a non-default
	///< group window if your application pretends to be multiple applications.
	///< The group leader window may not be changed after a window has been 
	///< mapped (with show() for example).

	void set_decorations(WMDecorationField decorations);
	///< "Decorations" are the features the window manager adds to a toplevel Gdk::Window.
	///< @param decorations The Gdk::WMDecoration hint mask.
	///<
	///< This method sets the traditional Motif window manager hints that tell the
	///< window manager which decorations you would like your window to have. Usually
	///< you should use Gtk::Window::set_decorated() on a Gtk::Window instead of using
	///< this GDK method.
	///<
	///< The decorations argument is the logical OR of the fields in the WMDecoration
	///< enumeration. If DECOR_ALL is included in the mask, the other bits indicate which
	///< decorations should be turned off. If DECOR_ALL is not included, then the other 
	///< bits indicate which decorations should be turned on.
	///<
	///< Most window managers honor a decorations hint of 0 to disable all decorations,
	///< but very few honor all possible combinations of bits.

	void set_functions(WMFunctionField functions);
	///< Sets the traditional Motif window manager hint for which operations the
	///< window manager should allow on a toplevel window.
	///< @param functions The Gdk::WMFunction bitmask of operations to allow on the window.
	///<
	///< This method isn't really good for much. Few window managers do anything
	///< reliable or interesting with this hint. Many ignore it entirely.
	///<
	///< The functions argument is the logical OR of values from the GdkWMFunction
	///< enumeration. If the bitmask includes FUNC_ALL, then the other bits indicate
	///< which functions to disable; if it doesn't include FUNC_ALL, it indicates 
	///< which functions to enable.

	void iconify();
	///< Asks to iconify (minimize) the window. The window manager may choose to ignore
	///< the request, but normally will honor it. Using Gtk::Window::iconify() is 
	///< preferred, if you have a Gtk::Window widget. This method only makes sense when
	///< the window is a toplevel window.

	void deiconify();
	///< Attempts to deiconify (unminimize) the window. On X11 the window manager may
	///< choose to ignore the request to deiconify. Using Gtk::Window::deiconify() 
	///< instead of the Gdk::Window variant is preferred. Or better yet, you probably
	///< want to use Gtk::Window::present(), which raises the window, focuses it, 
	///< unminimizes it, and puts it on the current desktop.

	void stick();
	///< "Pins" the window such that it's on all workspaces and does not scroll with
	///< viewports, for window managers that have scrollable viewports. When using
	///< Gtk::Window, Gtk::Window::stick() may be more useful. On the X11 platform,
	///< this method depends on window manager support, so may have no effect with
	///< many window managers. However, GDK will do the best it can to convince the
	///< window manager to stick the window. For window managers that don't support
	///< this operation, there's nothing you can do to force it to happen.

	void unstick();
	///< Reverse operation for stick(); see Gdk::Window::stick(), and Gtk::Window::unstick().

	void maximize();
	///< Maximizes the window. If the window was already maximized, then this method
	///< does nothing. On X11, asks the window manager to maximize window, if the window
	///< manager supports this operation. Not all window managers support this, and some
	///< deliberately ignore it or don't have a concept of "maximized"; so you can't rely
	///< on the maximization actually happening. But it will happen with most standard
	///< window managers, and GDK makes a best effort to get it to happen.
	
	void unmaximize();
	///< Unmaximizes the window. If the window wasn't maximized, then this method does
	///< nothing. On X11, asks the window manager to unmaximize window, if the window 
	///< manager supports this operation. Not all window managers support this, and some
	///< deliberately ignore it or don't have a concept of "maximized"; so you can't rely
	///< on the unmaximization actually happening. But it will happen with most standard
	///< window managers, and GDK makes a best effort to get it to happen.

	void fullscreen();
	///< Moves the window into fullscreen mode. This means the window covers the entire screen
	///< and is above any panels or task bars. If the window was already fullscreen, then this
	///< function does nothing. On X11, asks the window manager to put window in a fullscreen
	///< state, if the window manager supports this operation. Not all window managers support
	///< this, and some deliberately ignore it or don't have a concept of "fullscreen"; so you
	///< can't rely on the fullscreenification actually happening. But it will happen with most
	///< standard window managers, and GDK makes a best effort to get it to happen.

	void unfullscreen();
	///< Moves the window out of fullscreen mode. If the window was not fullscreen, does
	///< nothing. On X11, asks the window manager to move window out of the fullscreen
	///< state, if the window manager supports this operation. Not all window managers
	///< support this, and some deliberately ignore it or don't have a concept of 
	///< "fullscreen"; so you can't rely on the unfullscreenification actually happening.
	///< But it will happen with most standard window managers, and GDK makes a best
	///< effort to get it to happen.

	void set_keep_above(bool setting);
	///< Set if the window must be kept above other windows.
	///< @param setting Whether to keep the window above other windows.
	///<
	///< If the window was already above, then this function does nothing. On X11,
	///< this method asks the window manager to keep the window above, if the window
	///< manager supports this operation. Not all window managers support this, and
	///< some deliberately ignore it or don't have a concept of "keep above"; so you
	///< can't rely on the window being kept above. But it will happen with most
	///< standard window managers, and GDK makes a best effort to get it to happen.

	void set_keep_below(bool setting);
	///< Set if the window must be kept below other windows.
	///< @param setting Whether to keep the window below other windows.
	///<
	///< If the window was already below, then this function does nothing. On X11,
	///< this method asks the window manager to keep window below, if the window
	///< manager supports this operation. Not all window managers support this, and
	///< some deliberately ignore it or don't have a concept of "keep below"; so you
	///< can't rely on the window being kept below. But it will happen with most
	///< standard window managers, and GDK makes a best effort to get it to happen.

	void register_dnd();
	///< Registers a window as a potential drop destination. 

	void begin_resize_drag(WindowEdge edge, int button, int root_x, int root_y, unsigned int timestamp);
	///< Begins a window resize operation (for a toplevel window).
	///< @param edge The edge or corner from which the drag is started.
	///< @param button The button being used to drag.
	///< @param root_x The root window X coordinate of the mouse click that began the drag.
	///< @param root_y The root window Y coordinate of the mouse click that began the drag.
	///< @param timestamp Timestamp of the mouse click that began the drag (use Gdk::Event::get_time()).
	///<
	///< You might use this method to implement a "window resize grip," for example;
	///< in fact Gtk::Statusbar uses it. The method works best with window managers that
	///< support the Extended Window Manager Hints spec (see http://www.freedesktop.org),
	///< but has a fallback implementation for other window managers.

	void begin_move_drag(int button, int root_x, int root_y, unsigned int timestamp);
	///< Begins a window move operation (for a toplevel window). 
	///< @param button The button being used to drag.
	///< @param root_x The root window X coordinate of the mouse click that began the drag.
	///< @param root_y The root window Y coordinate of the mouse click that began the drag.
	///< @param timestamp The timestamp of the mouse click that began the drag.
	///<
	///< You might use this method to implement a "window move grip," for example.
	///< The method works best with window managers that support the Extended Window
	///< Manager Hints spec (see http://www.freedesktop.org), but has a fallback
	///< implementation for other window managers.

	void invalidate(const Rectangle& rectangle, bool invalidate_children);
	///< Adds <EM>rectangle</EM> to the update area for the window.
	///< @param rectangle A Rectangle.
	///< @param invalidate_children Set <EM>true</EM> to also invalidate child windows.
	///<
	///< This method is a convenience wrapper around invalidate(const Region&, bool)
	///< which invalidates a rectangular region.

	void invalidate(const Region& region, bool invalidate_children);
	///< Adds <EM>region</EM> to the update area for the window.
	///< @param region A Region to invalidate.
	///< @param invalidate_children Set <EM>true</EM> to also invalidate child windows.
	///<
	///< The update area is the region that needs to be redrawn, or "dirty region." 
	///< The call process_updates() sends one or more expose events to the window, which
	///< together cover the entire update area. An application would normally redraw the
	///< contents of the window in response to those expose events.
	///<
	///< GDK will call process_all_updates() on your behalf whenever your program returns
	///< to the main loop and becomes idle, so normally there's no need to do that manually,
	///< you just need to invalidate regions that you know should be redrawn.
	///<
	///< The <EM>invalidate_children</EM> parameter controls whether the region of each child
	///< window that intersects region will also be invalidated. If false, then the update
	///< area for child windows will remain unaffected. See gdk_window_invalidate_maybe_recurse()
	///< if you need fine grained control over which children are invalidated.

	void freeze_updates();
	///< Temporarily freezes a window such that it won't receive expose events. The window will
	///< begin receiving expose events again when thaw_updates() is called. If freeze_updates()
	///< has been called more than once, thaw_updates() must be called an equal number of times
	///< to begin processing exposes.

	void thaw_updates();
	///< Thaws a window frozen with freeze_updates().

	void process_updates(bool update_children);
	///< Sends one or more expose events to the window. 
	///< @param update_children Whether to also process updates for child windows.
	///<
	///< The areas in each expose event will cover the entire update area for the window (see
	///< invalidate(const Region&, bool) for details). Normally GDK calls process_all_updates() on
	///< your behalf, so there's no need to call this function unless you want to force expose events
	///< to be delivered immediately and synchronously (vs. the usual case, where GDK delivers them in
	///< an idle handler). Occasionally this is useful to produce nicer scrolling behavior, for example.

	void set_debug_updates(bool setting);
	///< With update debugging enabled, calls to invalidate(const Region&, bool) clear the 
	///< invalidated region of the screen to a noticeable color, and GDK pauses for a short
	///< time before sending exposes to windows during process_updates().
	///< @param setting Set <EM>true</EM> to turn on update debugging.
	///<
	///< The net effect is that you can see the invalid region for each window and watch
	///< redraws as they occur. This allows you to diagnose inefficiencies in your application.
	///< In essence, because the GDK rendering model prevents all flicker, if you are redrawing
	///< the same region 400 times you may never notice, aside from noticing a speed problem.
	///< Enabling update debugging causes GTK to flicker slowly and noticeably, so you can see
	///< exactly what's being redrawn when, in what order.
	///<
	///< The --gtk-debug=updates command line option passed to GTK+ programs enables 
	///< this debug option at application startup time. That's usually more useful
	///< than calling set_debug_updates() yourself, though you might want to use this
	///< method to enable updates sometime after application startup time.

	void enable_synchronized_configure();
	///< Indicates that the application will cooperate with the window system in synchronizing
	///< the window repaint with the window manager during resizing operations.  After an 
	///< application calls this function, it must call configure_finished() every time it has
	///< finished all processing associated with a set of "configure" events. Toplevel GTK+ 
	///< windows automatically use this protocol. On X, calling this function makes window
	///< participate in the _NET_WM_SYNC_REQUEST window manager protocol.
	
	void configure_finished();
	///< Signal to the window system that the application has finished handling "configure" events
	///< it has received. Window Managers can use this to better synchronize the frame repaint with
	///< the application. GTK+ applications will automatically call this function when appropriate. 

	GrabStatus keyboard_grab(bool owner_events = false, unsigned int time = GDK_CURRENT_TIME);
	///< This window grabs the keyboard so that all events are passed to this application until
	///< the keyboard is ungrabbed with Gdk::keyboard_ungrab(). 
	///< @param owner_events If <EM>false</EM> then all keyboard events are reported with respect to
	///<                     the window. If <EM>true</EM> then keyboard events for this application
	///<                     are reported as normal, but keyboard events outside this application are
	///<                     reported with respect to the window. Both key press and key release events
	///<                     are always reported, independant of the event mask set by the application.
	///< @param time A timestamp from a Gdk::Event, or GDK_CURRENT_TIME if no timestamp is available.
	///< @return GRAB_SUCCESS if the grab was successful.
	///<
	///< This overrides any previous keyboard grab by this client.

	GrabStatus pointer_grab(EventMaskField event_mask, Window *confine_to = 0, Cursor *cursor = 0,
	                        bool owner_events = false, unsigned int time = GDK_CURRENT_TIME);
	///< This window grabs the pointer (usualy a mouse) so that all events are passed to
	///< this application until the pointer is ungrabbed with Gdk::pointer_ungrab(),
	///< or the grab window becomes unviewable.
	///< @param event_mask Specifies the event mask, which is used in accordance with owner_events.
	///< @param confine_to If non-null, the pointer will be confined to this window during the grab.
	///<                   If the pointer is outside confine_to, it will automatically be moved to
	///<                   the closest edge of confine_to and enter and leave events will be
	///<                   generated as necessary.
	///< @param cursor The cursor to display while the grab is active. If this is null then the normal
	///<               cursors are used for window and its descendants, and the cursor for window is
	///<               used for all other windows.
	///< @param owner_events If false then all pointer events are reported with respect to window
	///<                     and are only reported if selected by event_mask. If true then pointer
	///<                     events for this application are reported as normal, but pointer events
	///<                     outside this application are reported with respect to window and only
	///<                     if selected by event_mask. In either mode, unreported events are discarded.
	///< @param time The timestamp of the event which led to this pointer grab. This usually comes from
	///<             Gdk::EventButton, though GDK_CURRENT_TIME can be used if the time isn't known.
	///< @return GRAB_SUCCESS if the grab was successful.
	///<
	///< This overrides any previous pointer grab by this client. Pointer grabs are used
	///< for operations which need complete control over mouse events, even if the mouse leaves
	///< the application. For example in GTK+ it is used for Drag and Drop, and for dragging the
	///< handle in the Gtk::HPaned and Gtk::VPaned widgets.
	///<
	///< Note that if the event mask of an X window has selected both button press and 
	///< button release events, then a button press event will cause an automatic pointer
	///< grab until the button is released. X does this automatically since most 
	///< applications expect to receive button press and release events in pairs. It is
	///< equivalent to a pointer grab on the window with owner_events set to true.

/// @}
/// @name Input methods
/// @{

	void set_extension_events(int mask, ExtensionMode mode);
	///< Turns extension events on or off for a particular window,
	///< and specifies the event mask for extension events.
	///< @param mask The event mask.
	///< @param mode The type of extension events that are desired.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/window.inl>

#endif // XFC_GDK_WINDOW_HH

