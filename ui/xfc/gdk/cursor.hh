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
 
/// @file xfc/gdk/cursor.hh
/// @brief A GdkCursor C++ wrapper interface.
///
/// Provides a standard and pixmap Cursor object .

#ifndef XFC_GDK_CURSOR_HH
#define XFC_GDK_CURSOR_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef __GDK_CURSOR_H__
#include <gdk/gdkcursor.h>
#endif

namespace Xfc {

namespace Gdk {

class Color;
class Display;
class Pixmap;
class Pixbuf;

/// @class Cursor cursor.hh xfc/gdk/cursor.hh
/// @brief A GdkCursor C++ wrapper class.
///
/// The Cursor object represents a cursor. A cursor is a pixmap with a depth of one, 
/// known as a bitmap. The cursor displayed inside a window's area is an attribute
/// of the window and can be modified. The initial value of a window's cursor attribute
/// is null, indicating the parent window's cursor should be used.
///
/// There are several ways to construct a Cursor. You can specify one of the system's 
/// predefined cursor types in the GdkCursorType enumeration or you can create your
/// own using pixmaps.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Cursor : public G::Boxed
{
public:
/// @name Constructors
/// @{

	Cursor(GdkCursorType cursor_type, const Display *display = 0);
	///< Constructs a new cursor for the specified display from the set of builtin cursors.
	///< @param cursor_type The cursor to create.
	///< @param display The Display to create the cursor for, or null for the default display.
	///<
	///< To make the cursor invisible, construct it from pixmaps with no pixels in them.
	///< Cursor is created with a reference count of 1 that the caller owns.

	Cursor(const Pixmap& source, const Pixmap& mask, const Color& fg, const Color& bg, int x, int y);
	///< Constructs a new cursor from a given pixmap and mask.
	///< @param source The pixmap specifying the cursor.
	///< @param mask The pixmap specifying the mask, which must be the same size as source.
	///< @param fg The foreground color, used for the bits in the source which are 1.
	///< @param bg The background color, used for the bits in the source which are 0.
	///< @param x The horizontal offset of the 'hotspot' of the cursor.
	///< @param y The vertical offset of the 'hotspot' of the cursor.
	///<
	///< The foreground and background colors don't need to be allocated first.
	///< Both the pixmap and mask must have a depth of 1 (i.e. each pixel has only
	///< 2 values - on or off). The standard cursor size is 16 by 16 pixels. You can 
	///< create a bitmap from inline data as in the below example.
	///<
	///< <B>Example:</B> Creating a custom cursor
	///< @code
	///< // This data is in X bitmap format, and can be created with the 'bitmap' utility.
	///<
	///< const int cursor1_width 16;
	///< const int cursor1_height 16;
	///<
	///< static unsigned char cursor1_bits[] = {
	///<   0x80, 0x01, 0x40, 0x02, 0x20, 0x04, 0x10, 0x08, 0x08, 0x10, 0x04, 0x20,
	///<   0x82, 0x41, 0x41, 0x82, 0x41, 0x82, 0x82, 0x41, 0x04, 0x20, 0x08, 0x10,
	///<   0x10, 0x08, 0x20, 0x04, 0x40, 0x02, 0x80, 0x01};
	///<
	///< static unsigned char cursor1mask_bits[] = {
	///<   0x80, 0x01, 0xc0, 0x03, 0x60, 0x06, 0x30, 0x0c, 0x18, 0x18, 0x8c, 0x31,
	///<   0xc6, 0x63, 0x63, 0xc6, 0x63, 0xc6, 0xc6, 0x63, 0x8c, 0x31, 0x18, 0x18,
	///<   0x30, 0x0c, 0x60, 0x06, 0xc0, 0x03, 0x80, 0x01};
	///<
	///< Gdk::Color fg(65535, 0, 0); // Red
	///< Gdk::Color bg(0, 0, 65535 }; // Blue
	///<
	///< Pointer<Gdk::Bitmap> source = new Gdk::Bitmap(cursor1_bits, cursor1_width, cursor1_height);
	///< Pointer<Gdk::Bitmap> mask = new Gdk::Bitmap(cursor1mask_bits, cursor1_width, cursor1_height);
	///<
	///< Gdk::Cursor *cursor = new Gdk::Cursor(source, mask, fg, bg, 8, 8);
	///< widget->get_window()->set_cursor(cursor);
	///< @endcode
	///<
	///< Cursor is created with a reference count of 1 that the caller owns.

	Cursor(const Pixbuf& pixbuf, int x, int y, const Display *display = 0);
 	///< Constructs a new cursor from a pixbuf.
	///< @param pixbuf The Gdk::Pixbuf containing the cursor image.
	///< @param x The horizontal offset of the 'hotspot' of the cursor.
	///< @param y The vertical offset of the 'hotspot' of the cursor.
	///< @param display The Display to create the cursor for, or null for the default display.
	///<
	///< Not all GDK backends support RGBA cursors. If they are not supported, a monochrome
	///< approximation will be displayed. The functions Gdk::Display::supports_cursor_alpha() and
	///< Gdk::Display::supports_cursor_color() can be used to determine whether RGBA cursors are
	///< supported; Gdk::Display::get_default_cursor_size() and Gdk::display::get_maximal_cursor_size()
	///< give information about cursor sizes.
	///<
	///< On the X backend, support for RGBA cursors requires a sufficently new version of the
	///< X Render extension. Cursor is created with a reference count of 1 that the caller owns.

	explicit Cursor(GdkCursor *cursor);
	///< Construct a new cursor from an existing GdkCursor.
	///< @param cursor A pointer to a GdkCursor.
	///<
	///< The <EM>cursor</EM> can be a newly created GdkCursor or an existing
	///< GdkCursor. The Cursor object created is a temporary object. It doesn't
	///< take over the ownership of GdkCursor and GdkCursor is not freed by the
	///< destructor. Cursor is created with a reference count of 1 that the caller
	///< owns.

	Cursor(GdkCursor *cursor, bool copy);
	///< Construct a new cursor from an existing GdkCursor.
	///< @param cursor A pointer to a GdkCursor.
	///< @param copy Whether the Cursor object should make a copy of GdkCursor or not.
	///<
	///< The <EM>cursor</EM> can be a newly created GdkCursor or an existing GdkCursor.
	///< If <EM>copy</EM> is true Cursor will make a copy of GdkCursor. If <EM>copy</EM>
	///< is false Cursor wont make a copy but instead takes over the ownership of GdkCursor.
	///< Either way, the destructor will free GdkCursor when the Cursor object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap GdkCursor objects in a
	///< C++ wrapper. Cursor is created with a reference count of 1 that the caller owns.

	Cursor(const Cursor& src);
	///< Copy constructor.
	///< @param src The source cursor.

	~Cursor();
	///< Destructor.

	Cursor& operator=(const Cursor& src);
	///< Assignment operator.
	///< @param src The source cursor.

/// @}
/// @name Accessors
/// @{

	GdkCursor* gdk_cursor() const;
	///< Get a pointer to the GdkCursor structure.

	operator GdkCursor* () const;
	///< Conversion operator; safely converts a Cursor to a GdkCursor pointer.

	GdkCursorType type() const;
	///< Returns the type of this cursor. This will usually be one of the standard cursor types,
	///< such as GDK_ARROW or GDK_CROSSHAIR, or GDK_CURSOR_IS_PIXMAP is you constructed your
	///< cursor from pixmaps.

	Display* get_display() const;
	///< Gets the display on which the cursor is defined.
	///< @returns The Display associated with the cursor.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/cursor.inl>

#endif // XFC_GDK_CURSOR_HH

