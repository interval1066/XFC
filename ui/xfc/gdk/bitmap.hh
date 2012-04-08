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
 
/// @file xfc/gdk/bitmap.hh
/// @brief A GdkBitmap C++ wrapper interface.
///
/// Provides Bitmap, an object that represents an offscreen monochrome drawable.

#ifndef XFC_GDK_BITMAP_HH
#define XFC_GDK_BITMAP_HH

#ifndef XFC_GDK_PIXMAP_HH
#include <xfc/gdk/pixmap.hh>
#endif

namespace Xfc {

namespace Gdk {

/// @class Bitmap bitmap.hh xfc/gdk/bitmap.hh
/// @brief A GdkBitmap C++ wrapper class.
///
/// Bitmap, like Pixmaps are offscreen drawables. They can be drawn upon with the
/// standard drawing primitives, then copied to another drawable (such as a 
/// Gdk::Window) with Gdk::Pixmap::draw(). The depth of a pixmap is the number of
/// bits per pixels. Bitmaps are simply pixmaps with a depth of 1. (That is, they
/// are monochrome bitmaps, each pixel can be either on or off).
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Bitmap : public Pixmap
{
	friend class G::Object;

	Bitmap(const Bitmap&);
	Bitmap& operator=(const Bitmap&);

protected:
/// @name Constructors
/// @{

	explicit Bitmap(GdkBitmap *bitmap, bool owns_reference = true);
	///< Construct a new Bitmap from an existing GdkBitmap.
	///< @param bitmap A pointer to a GdkBitmap.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>bitmap</EM> can be a newly created GdkBitmap or an existing
	///< GdkBitmap. (see G::Object::Object).

/// @}

public:
	typedef GdkBitmap CObjectType;

/// @name Constructors
/// @{

	Bitmap(const char *data, int width, int height);
	///< Create a new bitmap from data in XBM format using the root window
	///< to determine the default values.
	///< @param data A pointer to the XBM data.
	///< @param width The width of the new bitmap in pixels.
	///< @param height The height of the new bitmap in pixels.
	///< 
	///< Bitmap is created with a reference count of 1 that the caller owns.

	Bitmap(const Window& window, const char *data, int width, int height);
	///< Create a new bitmap from data in XBM format using window
	///< to determine the default values.
	///< @param window The window to use.
	///< @param data A pointer to the XBM data.
	///< @param width The width of the new bitmap in pixels.
	///< @param height The height of the new bitmap in pixels.
	///< 
	///< Bitmap is created with a reference count of 1 that the caller owns.

	virtual ~Bitmap();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GdkBitmap* gdk_bitmap() const;
	///< Get a pointer to the GdkBitmap structure.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/bitmap.inl>

#endif // XFC_GDK_BITMAP_HH

