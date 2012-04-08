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

/// @file xfc/gdk/types.hh
/// @brief A GdkPoint, GdkRectangle, GdkSegment and GdkSpan C++ wrapper interface.
///
/// Provides common enumerations and four utility classes - Point, Rectangle, Segment and Span.

#ifndef XFC_GDK_TYPES_HH
#define XFC_GDK_TYPES_HH

#ifndef __GDK_H__
#include <gdk/gdk.h>
#endif

namespace Xfc {

namespace Gdk {

/// Atom is a typedef for GdkAtom.

typedef GdkAtom Atom;

/// @enum AxisUse
/// An enumeration describing the way in which a device axis (valuator) maps onto
/// the predefined valuator types that GTK+ understands.

enum AxisUse
{
	AXIS_IGNORE = GDK_AXIS_IGNORE, ///< The axis is ignored.
	AXIS_X = GDK_AXIS_X, ///< The axis is used as the x axis.
	AXIS_Y = GDK_AXIS_Y, ///< The axis is used as the y axis.
	AXIS_PRESSURE = GDK_AXIS_PRESSURE, ///< The axis is used for pressure information.
	AXIS_XTILT = GDK_AXIS_XTILT, ///< The axis is used for x tilt information.
	AXIS_YTILT = GDK_AXIS_YTILT, ///< The axis is used for x tilt information.
	AXIS_WHEEL = GDK_AXIS_WHEEL, ///< The axis is used for wheel information.
	AXIS_LAST = GDK_AXIS_LAST ///< A constant equal to the numerically highest axis value.
};

/// @enum ByteOrder
/// A set of values describing the possible byte-orders for storing pixel values in memory.

enum ByteOrder
{
	LSB_FIRST = GDK_LSB_FIRST,
	///< The values are stored with the least-significant byte first; for instance, the
	///< 32-bit value 0xffeecc would be stored in memory as 0xcc, 0xee, 0xff, 0x00.
	
	MSB_FIRST = GDK_MSB_FIRST
	///< The values are stored with the most-significant byte first; for instance, the
	///< 32-bit value 0xffeecc would be stored in memory as 0x00, 0xcc, 0xee, 0xff.
};

/// @enum DragAction
/// Used in Gdk::DragContext to indicate what the destination should do with the dropped data.

enum DragAction
{
	ACTION_DEFAULT = GDK_ACTION_DEFAULT,
	///< The default action for the protocol being used.

	ACTION_COPY = GDK_ACTION_COPY,
	///< Copy the data.

	ACTION_MOVE = GDK_ACTION_MOVE,
	///< Move the data, that is, first copy it, then delete it from the source using
	///< the DELETE target of the X selection protocol.
	
	ACTION_LINK = GDK_ACTION_LINK,
	///< Add a link to the data; note that this is only useful if source and destination
	///< agree on what it means.

	ACTION_PRIVATE = GDK_ACTION_PRIVATE,
	///< Special action which tells the source that the destination will do something
	///< that the source doesn't understand.

	ACTION_ASK = GDK_ACTION_ASK
	///< Ask the user what to do with the data.
};

/// DragActionField holds one or more values from the Gdk::DragAction enumeration OR'd together.

typedef unsigned int DragActionField;

/// @enum DragProtocol
/// Used in Gdk::DragContext to indicate the protocol according to which DND is done.

enum DragProtocol
{
	DRAG_PROTO_MOTIF = GDK_DRAG_PROTO_MOTIF, ///< The Motif DND protocol.
	DRAG_PROTO_XDND = GDK_DRAG_PROTO_XDND, ///< The Xdnd protocol.
	DRAG_PROTO_ROOTWIN = GDK_DRAG_PROTO_ROOTWIN, ///< Extension to Xdnd protocol for unclaimed root window drops.
	DRAG_PROTO_ = GDK_DRAG_PROTO_NONE, ///< No protocol.
	DRAG_PROTO_NONE = GDK_DRAG_PROTO_WIN32_DROPFILES, ///< The simple WM_DROPFILES protocol.
	DRAG_PROTO_OLE2 = GDK_DRAG_PROTO_OLE2, ///< The complex OLE2 DND protocol (not implemented).
	DRAG_PROTO_LOCAL = GDK_DRAG_PROTO_LOCAL ///< Intra-application DND.
};

/// @enum ExtensionMode
/// An enumeration used to specify which extension events are desired for a particular widget.

enum ExtensionMode
{
	EXTENSION_EVENTS_NONE = GDK_EXTENSION_EVENTS_NONE,
	///< No extension events are desired.

	EXTENSION_EVENTS_ALL = GDK_EXTENSION_EVENTS_ALL,
	///< All extension events are desired.

	EXTENSION_EVENTS_CURSOR = GDK_EXTENSION_EVENTS_CURSOR
	///< Extension events are desired only if a cursor will be displayed for the device.
};

/// @enum FilterReturn
/// Specifies the result of applying a FilterSlot to a native event.

enum FilterReturn
{
	FILTER_CONTINUE = GDK_FILTER_CONTINUE, ///< Event not handled, continue processesing.
	FILTER_TRANSLATE = GDK_FILTER_TRANSLATE, ///< Translated the event stored.
	FILTER_REMOVE = GDK_FILTER_REMOVE ///< Terminate processing, removing event.
};

/// @enum GrabStatus
/// Returned by pointer_grab() and keyboard_grab() to indicate success
/// or the reason for the failure of the grab attempt.

enum GrabStatus
{
	GRAB_SUCCESS = GDK_GRAB_SUCCESS,
	///< The resource was successfully grabbed.

	GRAB_ALREADY_GRABBED = GDK_GRAB_ALREADY_GRABBED,
	///< The resource is actively grabbed by another client.
	
	GRAB_INVALID_TIME = GDK_GRAB_INVALID_TIME,
	///< The resource was grabbed more recently than the specified time.

	GRAB_NOT_VIEWABLE = GDK_GRAB_NOT_VIEWABLE,
	///< The grab window or the confine_to window are not viewable.

	GRAB_FROZEN = GDK_GRAB_FROZEN
	///< The resource is frozen by an active grab of another client.
};

/// @enum Gravity
/// Defines the reference point of a window and the meaning of coordinates
/// passed to Gtk::Window::move().

enum Gravity
{
	GRAVITY_NORTH_WEST = GDK_GRAVITY_NORTH_WEST,
	///< The reference point is at the top left corner.

	GRAVITY_NORTH = GDK_GRAVITY_NORTH,
	///< The reference point is in the middle of the top edge.
	
	GRAVITY_NORTH_EAST = GDK_GRAVITY_NORTH_EAST,
	///< The reference point is at the top right corner.
	
	GRAVITY_WEST = GDK_GRAVITY_WEST,
	///< The reference point is at the middle of the left edge.
	
	GRAVITY_CENTER = GDK_GRAVITY_CENTER,
	///< The reference point is at the center of the window.
	
	GRAVITY_EAST = GDK_GRAVITY_EAST,
	///< The reference point is at the middle of the right edge.
	
	GRAVITY_SOUTH_WEST = GDK_GRAVITY_SOUTH_WEST,
	///< The reference point is at the lower left corner.
	
	GRAVITY_SOUTH = GDK_GRAVITY_SOUTH,
	///< The reference point is at the middle of the lower edge.

	GRAVITY_SOUTH_EAST = GDK_GRAVITY_SOUTH_EAST,
	///< The reference point is at the lower right corner.

	GRAVITY_STATIC = GDK_GRAVITY_STATIC
	///< The reference point is at the top left corner of the window itself,
	///< ignoring window manager decorations.
};

/// @enum ModifierType
/// A set of bit-flags to indicate the state of modifier keys and mouse buttons
/// in various event types. Typical modifier keys are Shift, Control, Meta, Super,
/// Hyper, Alt, Compose, Apple, CapsLock or ShiftLock.
///
/// Like the X Window System, GDK supports 8 modifier keys and 5 mouse buttons.

enum ModifierType
{
	SHIFT_MASK = GDK_SHIFT_MASK,
	///< The Shift key.
	
	LOCK_MASK = GDK_LOCK_MASK,
	///< A Lock key (depending on the modifier mapping of the X server
	///< this may either be CapsLock or ShiftLock).
	
	CONTROL_MASK = GDK_CONTROL_MASK,
	///< The Control key.
	
	MOD1_MASK = GDK_MOD1_MASK,
	///< The fourth modifier key (it depends on the modifier mapping of the X server
	///< which key is interpreted as this modifier, but normally it is the Alt key).
	
	MOD2_MASK = GDK_MOD2_MASK,
	///< The fifth modifier key (it depends on the modifier mapping of the X server
	///< which key is interpreted as this modifier).
	
	MOD3_MASK = GDK_MOD3_MASK,
	///< The sixth modifier key (it depends on the modifier mapping of the X server
	///< which key is interpreted as this modifier).
	
	MOD4_MASK = GDK_MOD4_MASK,
	///< The seventh modifier key (it depends on the modifier mapping of the X server
	///< which key is interpreted as this modifier).
	
	MOD5_MASK = GDK_MOD5_MASK,
	///< The eighth modifier key (it depends on the modifier mapping of the X server
	///< which key is interpreted as this modifier).
	
	BUTTON1_MASK = GDK_BUTTON1_MASK,
	///< The first mouse button.

	BUTTON2_MASK = GDK_BUTTON2_MASK,
	///< The second mouse button.
	
	BUTTON3_MASK = GDK_BUTTON3_MASK,
	///< The third mouse button.

	BUTTON4_MASK = GDK_BUTTON4_MASK,
	///< The fourth mouse button.

	BUTTON5_MASK = GDK_BUTTON5_MASK,
	///< The fifth mouse button.
	
	RELEASE_MASK = GDK_RELEASE_MASK,
	///< Not used in GDK itself; GTK+ uses it to differentiate between (keyval, modifiers)
	///< pairs from key press and release events.

	MODIFIER_MASK = GDK_MODIFIER_MASK
	///< Unknown
};

/// ModifierTypeField holds one or more values from the Gdk::ModifierType enumeration OR'd together.

typedef unsigned int ModifierTypeField;

/// @enum RgbDither
/// Selects whether or not GdkRGB applies dithering to the image on display.
/// Since GdkRGB currently only handles images with 8 bits per component, 
/// dithering on 24 bit per pixel displays is a moot point.

enum RgbDither
{
	RGB_DITHER_NONE = GDK_RGB_DITHER_NONE, ///< Never use dithering.
	RGB_DITHER_NORMAL = GDK_RGB_DITHER_NORMAL, ///< Use dithering in 8 bits per pixel (and below) only.
	RGB_DITHER_MAX = GDK_RGB_DITHER_MAX ///< Use dithering in 16 bits per pixel and below.
};

/// @enum WindowEdge
/// Determines a window edge or corner.

enum WindowEdge
{
	WINDOW_EDGE_NORTH_WEST = GDK_WINDOW_EDGE_NORTH_WEST, ///< The top left corner.
	WINDOW_EDGE_NORTH = GDK_WINDOW_EDGE_NORTH, ///< The top edge.
	WINDOW_EDGE_NORTH_EAST = GDK_WINDOW_EDGE_NORTH_EAST, ///< The top right corner.
	WINDOW_EDGE_WEST = GDK_WINDOW_EDGE_WEST, ///< The left edge.
	WINDOW_EDGE_EAST = GDK_WINDOW_EDGE_EAST, ///< The right edge.
	WINDOW_EDGE_SOUTH_WEST = GDK_WINDOW_EDGE_SOUTH_WEST, ///< The lower left corner.
	WINDOW_EDGE_SOUTH = GDK_WINDOW_EDGE_SOUTH, ///< The lower edge.
	WINDOW_EDGE_SOUTH_EAST = GDK_WINDOW_EDGE_SOUTH_EAST ///< The lower right corner.
};

/// @enum WindowTypeHint
/// These are hints for the window manager that indicate what type of function the window has.
/// The window manager can use this when determining decoration and behaviour of the window.
/// The hint must be set before mapping the window.

enum WindowTypeHint
{
	WINDOW_TYPE_HINT_NORMAL = GDK_WINDOW_TYPE_HINT_NORMAL, ///< Normal toplevel window.
	WINDOW_TYPE_HINT_DIALOG = GDK_WINDOW_TYPE_HINT_DIALOG, ///< Dialog window.
	WINDOW_TYPE_HINT_MENU = GDK_WINDOW_TYPE_HINT_MENU, ///< Window used to implement a menu.
	WINDOW_TYPE_HINT_TOOLBAR = GDK_WINDOW_TYPE_HINT_TOOLBAR, ///< Window used to implement toolbars.
	WINDOW_TYPE_HINT_SPLASHSCREEN = GDK_WINDOW_TYPE_HINT_SPLASHSCREEN, ///< Window used to implement a splashscreen
	WINDOW_TYPE_HINT_UTILITY = GDK_WINDOW_TYPE_HINT_UTILITY, ///<
	WINDOW_TYPE_HINT_DOCK = GDK_WINDOW_TYPE_HINT_DOCK, ///<
	WINDOW_TYPE_HINT_DESKTOP = GDK_WINDOW_TYPE_HINT_DESKTOP ///<
};

/// @name Keyboard/Pointer Methods
/// @{

void keyboard_ungrab(unsigned int time = GDK_CURRENT_TIME);
///< Ungrabs the keyboard for the default display, if it is grabbed
///< by this application (see Gdk::Display::keyboard_ungrab()).
///< @param time A timestamp from a Gdk::Event, or GDK_CURRENT_TIME if no timestamp is available.

bool pointer_is_grabbed();
///< Returns true if the pointer for the default display is currently grabbed
///< by this application (see Gdk::Display::pointer_is_grabbed()).
///< @return <EM>true</EM> if the pointer is currently grabbed by this application.
///<
///< Note that this does not take the implicit pointer grab on button presses into account.

void pointer_ungrab(unsigned int time = GDK_CURRENT_TIME);
///< Ungrabs the pointer for the default display, if it is grabbed by this application.
///< (see Gdk::Display::pointer_ungrab()).
///< @param time A timestamp from a Gdk::Event, or GDK_CURRENT_TIME if no timestamp is available.

/// @}
/// @name Thread Methods
/// @{

void flush();
///< Flushes the X output buffer and waits until all requests have been processed by the
///< server. This is rarely needed by single-threaded applications. It's main use in XFC
///< is for multi-threaded programming. Before unlocking a critical section of code with
///< a call to Gdk::Mutex::unlock() you might want to call flush() to send all pending
///< commands to the windowing system.

/// @}

/// @class Mutex types.hh xfc/gdk/types.hh
/// @brief A C++ wrapper for the GDK Mutex object.
///
/// Mutex wraps the GDK mutex object that C programs lock and unlock with calls to
/// gdk_threads_enter() and gdk_threads_leave() respectively. In XFC you don't use
/// these fucntions. Instead you wrap critical sections of code in calls to
/// Gdk::Mutex::lock() and Gdk::Mutex::unlock();

class Mutex
{
public:
	static void lock();
	///< This method marks the beginning of a critical section in which Gdk and Gtk
	///< methods can be called. Only one thread at a time can be in such a critial
	///< section. If threads have not been enabled this method does nothing.

	static void unlock();
	///< This method marks the end of a critical section in which Gdk and Gtk methods
	///< can be called. Only one thread at a time can be in such a critial section.
	///< If threads have not been enabled this method does nothing.
};

/// @class Point types.hh xfc/gdk/types.hh
/// @brief A GdkPoint C++ wrapper class.
///
/// Point is a simple object containing the x and y coordinate of a point. Point uses
/// default copy, assignment and destruction.

class Point
{
	GdkPoint point_;

public:
/// @name Constructors
/// @{
	
	Point();
	///< Construct a new point (0, 0).

	Point(int x, int y);
	///< Construct a new point from two ints.
	///< @param x The X coordinate of the point.
	///< @param y The Y coordinate of the point.

	Point(double x, double y);
	///< Construct a new point form two doubles.
	///< @param x The X coordinate of the point.
	///< @param y The Y coordinate of the point.

	Point(const GdkPoint& point);
	///< Construct a new point from an existing GdkPoint.
	///< @param point A GdkPoint.

/// @}
/// @name Accessors
/// @{
	
	GdkPoint* gdk_point() const;
	///< Get a pointer to the GdkPoint structure.

	operator GdkPoint* () const;
	///< Conversion operator; safely converts a Point to a GdkPoint pointer.
	
	int x() const;
	///< Returns the X coordinate of the point.

	int y() const;
	///< Returns the Y coordinate of the point.

	bool operator==(const Point& other) const;
	///< Equality operator.
	///< @param other A Point.
	///< @return <EM>true</EM> if this point compares equal to <EM>other</EM>.

	bool operator!=(const Point& other) const;
	///< Inequality operator.
	///< @param other A Point.
	///< @return <EM>true</EM> if this point compares unequal to <EM>other</EM>.

/// @}
/// @name Methods
/// @{

	void set_x(int x);
	///< Set the x coordinate for the point.
	///< @param x The X coordinate of the point.

	void set_x(double x);
	///< Set the x coordinate for the point.
	///< @param x The X coordinate of the point.

	void set_y(int y);
	///< Set the y coordinate for the point.
	///< @param y The Y coordinate of the point.

	void set_y(double y);
	///< Set the y coordinate for the point.
	///< @param y The Y coordinate of the point.

	void set(int x, int y);
	///< Set the coordinates for the point.
	///< @param x The X coordinate of the point.
	///< @param y The Y coordinate of the point.

	void set(double x, double y);
	///< Set the coordinates for the point.
	///< @param x The X coordinate of the point.
	///< @param y The Y coordinate of the point.

	Point& offset(int dx, int dy);
	///< Move the point.
	///< @param dx The number of pixels to move the X coordinate of the point.
	///< @param dy The number of pixels to move the Y coordinate of the point.
	///< @return A reference to the offset point.
	///<
	///< <EM>dx</EM> and <EM>dy</EM> can be a positive or negative value.

	Point& operator+=(int increment);
	///< Move the x, y coordinates of the point by <EM>increment</EM> pixels
	///< in a positive direction.
	///< @param increment The number of pixels to increment x, y by.
	///< @return A reference to the moved point.

	Point& operator+=(const Point& other);
	///< Move the x, y coordinates of the point by the other.x and other.y.
	///< @param other A Point.
	///< @return A reference to the moved point.

	Point& operator-=(int decrement);
	///< Move the x, y coordinates of the point by <EM>decrement</EM> pixels
	///< in a negative direction.
	///< @param decrement The number of pixels to decrement x, y by.
	///< @return A reference to the moved point.

	Point& operator-=(const Point& other);
	///< Move the x, y coordinates of the point by the -other.x and -other.y.
	///< @param other A Point.
	///< @return A reference to the moved point.

	Point& operator++();
	///< Move the x, y coordinates of the point by one pixel in a positive direction.
	///< @return A reference to the moved point.

	Point& operator--();
	///< Move the x, y coordinates of the point by one pixel in a negative direction.
	///< @return A reference to the moved point.

/// @}
/// @name Methods returning a new Point
/// @{

	Point offset_by(int dx, int dy);
	///< Calculates a new point whose value is x + dx and y + dy.
	///< @param dx The number of pixels to add the X coordinate of the point.
	///< @param dy The number of pixels to add the Y coordinate of the point.
	///< @return A new point.
	///<
	///< <EM>dx</EM> and <EM>dy</EM> can be a positive or negative value.

	Point operator+(const Point& other) const;
	///< Calculates a new point whose value is x + other.x and y + other.y.
	///< @param other A Point.
	///< @return A new point.

	Point operator-(const Point& other) const;
	///< Calculates a new point whose value is x - other.x and y - other.y.
	///< @param other A Point.
	///< @return A new point.

/// @}
};

/// @class Rectangle types.hh xfc/gdk/types.hh
/// @brief A GdkRectangle C++ wrapper class.
///
/// Rectangle is an object that holds the position and size of a rectangle. The
/// intersection of two rectangles can be computed with intersect_with(). To
/// find the union of two rectangles use union_with(). Rectangle uses default copy,
/// assignment and destruction.

class Rectangle
{
	GdkRectangle rectangle_;

public:
/// @name Constructors
/// @{
	
	Rectangle();
	///< Construct a null rectangle. A null rectangle has its
	///< x, y, width and height set to 0;

	Rectangle(int x, int y, int width, int height);
	///< Construct a new rectangle.
	///< @param x The X coordinate of the rectangle.
	///< @param y The Y coordinate of the rectangle.
	///< @param width The width of the rectangle.
	///< @param height The height of the rectangle.

	Rectangle(const Point& point, int width, int height);
	///< Construct a new rectangle.
	///< @param point The x, y coordinates of the top-left corner of the rectangle.
	///< @param width The width of the rectangle.
	///< @param height The height of the rectangle.

	Rectangle(const GdkRectangle& rectangle);
	///< Construct a new rectangle from an existing GdkRectangle.
	///< @param rectangle A GdkRectangle.

/// @}
/// @name Accessors
/// @{

	GdkRectangle* gdk_rectangle() const;
	///< Get a pointer to the GdkRectangle structure.

	operator GdkRectangle* () const;
	///< Conversion operator; safely converts a Rectangle to a GdkRectangle pointer.

	int x() const;
	///< Returns the X coordinate of the top-left corner of the rectangle.

	int y() const;
	///< Returns the Y coordinate of the top-left corner of the rectangle.

	int width() const;
	///< Returns the width of the rectangle.

	int height() const;
	///< Returns the height of the rectangle.

	long area() const;
	///< Returns the area of the rectangle.

	Point center() const;
	///< Returns the point at the center of the rectangle.

	bool contains(int x, int y) const;
	///< Returns <EM>true</EM> if the rectangle contains the point [x, y].
	
	bool contains(const Point& point) const;
	///< Returns <EM>true</EM> if the rectangle contains <EM>point</EM>.

	bool equal(const Rectangle& other) const;
	///< Returns <EM>true</EM> if this rectangle compares equal to <EM>other</EM>.
	///< @param other A Gdk::Rectangle.

	bool empty() const;
	///< Returns true if the rectangle is empty. A rectangle is empty
	///< if either the width or height is 0;

	bool null() const;
	///< Returns true if the rectangle is null. A null rectangle
	///< has its x, y, width and height set to 0;

	bool intersect(const Rectangle& other) const;
	///< Returns <EM>true</EM> if this rectangle and other intersect.
	///< @param other A Gdk::Rectangle.

	Point& position() const;
	///< Returns a reference to the Point at top-left corner of the rectangle.

	bool operator==(const Rectangle& other) const;
	///< Returns <EM>true</EM> if this rectangle and other compare equal.
	///< @param other A Gdk::Rectangle.

	bool operator!=(const Rectangle& other) const;
	///< Returns <EM>true</EM> if this rectangle and other compare unequal.
	///< @param other A Gdk::Rectangle.

/// @}
/// @name Methods
/// @{

	void set(int x, int y, int width, int height);
	///< Sets the position and size of the rectangle.
	///< @param x The new X coordinate of the rectangle.
	///< @param y The new Y coordinate of the rectangle.
	///< @param width The new width of the rectangle.
	///< @param height The new height of the rectangle.

	void set_empty();
	///< Sets the width and height of the rectangle to 0.

	void set_null();
	///< Sets the x, y, width and height of the rectangle to 0.

	void set_position(int x, int y);
	///< Sets the position of the rectangle.
	///< @param x The new X coordinate of the rectangle.
	///< @param y The new Y coordinate of the rectangle.

	void set_position(const Point& point);
	///< Sets the position of the rectangle.
	///< @param point The new x, y coordinates of the top-left corner of the rectangle.

	void set_size(int width, int height);
	///< Sets the size of the rectangle.
	///< @param width The new width of the rectangle.
	///< @param height The new height of the rectangle.

	void capture(Point& point) const;
	///< Keeps <EM>point</EM> within the boundries of the rectangle.
	///< @param point A reference to a Point.
	///<
	///< This method is useful if you want to confine the cursor to a
	///< rectangle (e.g. a dialog) until the user makes a selection. Just
	///< use the captured point to set the cursor position in response to
	///< a <EM>motion_event</EM> signal.

	Rectangle& inflate(int dx, int dy);
	///< Resize the rectangle.
	///< @param dx The number of pixels to add/subtract the X coordinate of each corner.
	///< @param dy The number of pixels to add/subtract the Y coordinate of each corner.
	///< @return A reference to the resized rectangle.
	///<
	///< Positive values for <EM>dx</EM> and <EM>dy</EM> will enlarge the rectangle,
	///< and a negative values for <EM>dx</EM> and <EM>dy</EM> will shrink the rectangle.

	bool intersect_with(const Rectangle& other);
	///< Calculates the intersection of two rectangles.
	///< @param other A Gdk::Rectangle.
	///< @return <EM>true</EM> if this rectangle and other intersect.
	///<
	///< On returning, this rectangle contains the intersection the original rectangle
	///< and other. If the two rectangles don't intersect, the rectangle will be unchanged.

	Rectangle& offset(int dx, int dy);
	///< Move the rectangle.
	///< @param dx The number of pixels to add/subtract the X coordinate of the top-left corner.
	///< @param dy The number of pixels to add/subtract the Y coordinate of the top-left corner.
	///< @return A reference to the resized rectangle.

	void union_with(const Rectangle& other);
	///< Calculates the union of this rectangle and other.
	///< @param other A Gdk::Rectangle.
	///<
	///< The union of two rectangles is the smallest rectangle which includes both
	///< rectangles within it. On returning, this rectangle contains the union the original
	///< rectangle and other.
	
	Rectangle& operator+=(int increment);
	///< Inflates the rectangle by <EM>increment</EM> in all directions.
	///< @param increment The number of pixels to inflate the rectangle by.
	///< @return A reference to the resized rectangle.

	Rectangle& operator+=(const Point& point);
	///< Offsets the rectangle by point.x and point.y.
	///< @param point A Point specifying the dx and dy values to offset the top-left corner by.
	///< @return A reference to the moved rectangle.

	Rectangle& operator-=(int increment);
	///< Shrinks the rectangle by <EM>increment</EM> in all directions.
	///< @param increment The number of pixels to shrink the rectangle by.
	///< @return A reference to the resized rectangle.

	Rectangle& operator-=(const Point& point);
	///< Offsets the rectangle by -point.x and -point.y.
	///< @param point A Point specifying the dx and dy values to offset the top-left corner by.
	///< @return A reference to the moved rectangle.

	Rectangle& operator++();
	///< Inflates the rectangle in all directions by one pixel.
	///< @return A reference to the resized rectangle.

	Rectangle& operator--();
	///< Shrink the rectangle in all directions by one pixel.
	///< @return A reference to the resized rectangle.

	bool operator&=(const Rectangle& other);
	///< Calculates the intersection of two rectangles (same as intersect_with()).
	///< @param other A Gdk::Rectangle.
	///< @return <EM>true</EM> if this rectangle and other intersect.

	void operator|=(const Rectangle& other);
	///< Calculates the union of this rectangle and other (same as union_with()).
	///< @param other A Gdk::Rectangle.

/// @}
/// @name Methods returning a new Rectangle
/// @{
	
	Rectangle inflate_by(int dx, int dy) const;
	///< Resize this rectangle and return the result as a new Rectangle.
	///< @param dx The number of pixels to add/subtract the X coordinate of each corner.
	///< @param dy The number of pixels to add/subtract the Y coordinate of each corner.
	///< @return A new rectangle (see inflate()).
	///<
	///< Positive values for <EM>dx</EM> and <EM>dy</EM> will enlarge the rectangle,
	///< and a negative values for <EM>dx</EM> and <EM>dy</EM> will shrink the rectangle.

	Rectangle offset_by(int dx, int dy) const;
	///< Move the rectangle and return the result as a new rectangle.
	///< @param dx The number of pixels to add/subtract the X coordinate of the top-left corner.
	///< @param dy The number of pixels to add/subtract the Y coordinate of the top-left corner.
	///< @return A new rectangle (see offset()).

/// @}
};

/// @class Segment types.hh xfc/gdk/types.hh
/// @brief A GdkSegment C++ wrapper class.
///
/// Segment specifies the start and end point of a line for use by the
/// Gdk::Drawable::draw_segments() method. Segment uses default copy,
/// assignment and destruction.

class Segment
{
	GdkSegment segment_;

public:
/// @name Constructors
/// @{

	Segment();
	///< Constructs an empty segment with x1, y1, x2 and y2 all set to 0.

	Segment(int x1, int y1, int x2, int y2);
	///< Construct a new segment.
	///< @param x1 The X coordinate at the start of the segment.
	///< @param y1 The Y coordinate at the start of the segment.
	///< @param x2 The X coordinate at the end of the segment.
	///< @param y2 The Y coordinate at the end of the segment.

	Segment(const Point& start, const Point& end);
	///< Construct a new segemnt.
	///< @param start The x, y coordinates at the start of the segment.
	///< @param end The x, y coordinates at the end of the segment.

/// @}
/// @name Accessors
/// @{

	GdkSegment* gdk_segment() const;
	///< Get a pointer to the GdkSegment structure.

	operator GdkSegment* () const;
	///< Conversion operator; safely converts a Segment to a GdkSegment pointer.

	int x1() const;
	///< Returns the X coordinate of the starting point of the segment.

	int y1() const;
	///< Returns the Y coordinate of the starting point of the segment.

	int x2() const;
	///< Returns the X coordinate of the end point of the segment.

	int y2() const;
	///< Returns the Y coordinate of the end point of the segment.

	bool equal(const Segment& other) const;
	///< Returns <EM>true</EM> if this segment and other compare equal.
	///< @param other A Segment.

	bool operator==(const Segment& other) const;
	///< Returns <EM>true</EM> if this segment and other compare equal.
	///< @param other A Segment.

	bool operator!=(const Segment& other) const;
	///< Returns <EM>true</EM> if this segment and other compare unequal.
	///< @param other A Segment.

/// @}
/// @name Methods
/// @{

	void set(int x1, int y1, int x2, int y2);
	///< Sets the coordinates for the segment.
	///< @param x1 The X coordinate at the start of the segment.
	///< @param y1 The Y coordinate at the start of the segment.
	///< @param x2 The X coordinate at the end of the segment.
	///< @param y2 The Y coordinate at the end of the segment.

	void set(const Point& start, const Point& end);
	///< Sets the coordinates for the segment.
	///< @param start The x, y coordinates at the start of the segment.
	///< @param end The x, y coordinates at the end of the segment.

	void set_start(int x, int y);
	///< Sets the start coordinates of the segment.
	///< @param x The X coordinate at the start of the segment.
	///< @param y The Y coordinate at the start of the segment.

	void set_start(const Point& point);
	///< Sets the start coordinates of the segment.
	///< @param point The x, y coordinates at the start of the segment.

	void set_end(int x, int y);
	///< Sets the end coordinates of the segment.
	///< @param x The X coordinate at the end of the segment.
	///< @param y The Y coordinate at the end of the segment.

	void set_end(const Point& point);
	///< Sets the end coordinates of the segment.
	///< @param point The x, y coordinates at the end of the segment.

/// @}
};

/// @class Span types.hh xfc/gdk/types.hh
/// @brief A GdkSpan C++ wrapper class.
///
/// Span represents a horizontal line of pixels starting at the pixel with
/// coordinates x, y and ending before x + width, y. Span uses default copy,
/// assignment and destruction, and allows public access to x, y and width.

class Span
{
	GdkSpan span_;

public:
/// @name Constructors
/// @{
	
	Span();
	///< Construct a null span with x, y and width set to 0.

	Span(int x, int y, int width);
	///< Construct a new span.
	///< @param x The X coordinate of the first pixel in the span.
	///< @param y The Y coordinate of the first pixel in the span.
	///< @param width The number of pixels in the span.

	Span(const Point& first, int width);
	///< Construct a new span.
	///< @param first The x, y coordinates of the first pixel in the span.
	///< @param width The number of pixels in the span.

/// @}
/// @name Accessors
/// @{

	GdkSpan* gdk_span() const;
	///< Get a pointer to the GdkSpan structure.

	operator GdkSpan* () const;
	///< Conversion operator; safely converts a Span to a GdkSpan pointer.

	int x() const;
	///< Returns the X coordinate of the first point in the span.

	int y() const;
	///< Returns the Y coordinate of the first point in the span.

	int width() const;
	///< Returns the number of pixels in the span.
	
	bool equal(const Span& other) const;
	///< Returns <EM>true</EM> if this span and other compare equal.
	///< @param other A Span.

	bool operator==(const Span& other) const;
	///< Returns <EM>true</EM> if this span and other compare equal.
	///< @param other A Span.

	bool operator!=(const Span& other) const;
	///< Returns <EM>true</EM> if this span and other compare unequal.
	///< @param other A Span.

/// @}
/// @name Methods
/// @{

	void set(int x, int y);
	///< Sets the coordinates for the first pixel in the span.
	///< @param x The X coordinate of the first pixel in the span.
	///< @param y The Y coordinate of the first pixel in the span.

	void set(const Point& first);
	///< Sets the coordinates for the first pixel in the span.
	///< @param first The x, y coordinates of the first pixel in the span.

	void set(int x, int y, int width);
	///< Sets the position and width of the span.
	///< @param x The X coordinate of the first pixel in the span.
	///< @param y The Y coordinate of the first pixel in the span.
	///< @param width The number of pixels in the span.

	void set(const Point& first, int width);
	///< Sets the position and width of the span.
	///< @param first The x, y coordinates of the first pixel in the span.
	///< @param width The number of pixels in the span.

/// @}
};

/// @class Trapezoid types.hh xfc/gdk/types.hh
/// @brief A GdkTrapezoid C++ wrapper class.
///
/// Trapezoid specifies a trapezpoid for use by the Gdk::Drawable::draw_trapezoids().
/// The trapezoids used here have parallel, horizontal top and bottom edges. 

class Trapezoid
{
	GdkTrapezoid trapezoid_;

public:
/// @name Constructors
/// @{
	
	Trapezoid();
	///< Construct an empty trapezoid, with all coordinates set to zero.

	Trapezoid(double y1, double x11, double x21, double y2, double x12, double x22);
	///< Construct a new trapezoid.
	///< @param y1 The y coordinate of the start point.
	///< @param x11 The x coordinate of the top left corner.
	///< @param x21 The x coordinate of the top right corner.
	///< @param y2 The y coordinate of the end point.
	///< @param x12 The x coordinate of the bottom left corner.
	///< @param x22 The y coordinate of the bottom right point.

/// @}
/// @name Accessors
/// @{

	GdkTrapezoid* gdk_trapezoid() const;
	///< Get a pointer to the GdkTrapezoid structure.

	operator GdkTrapezoid* () const;
	///< Conversion operator; safely converts a Trapezoid to a GdkTrapezoid pointer.

/// @}
/// @name Methods
/// @{

	void set(double y1, double x11, double x21, double y2, double x12, double x22);
	///< Set the coordinates for the trapezoid.
	///< @param y1 The y coordinate of the start point.
	///< @param x11 The x coordinate of the top left corner.
	///< @param x21 The x coordinate of the top right corner.
	///< @param y2 The y coordinate of the end point.
	///< @param x12 The x coordinate of the bottom left corner.
	///< @param x22 The y coordinate of the bottom right point.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/types.inl>

#endif // XFC_GDK_TYPES_HH

