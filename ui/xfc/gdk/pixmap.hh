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
 
/// @file xfc/gdk/pixmap.hh
/// @brief A GdkPixmap C++ wrapper interface.
///
/// Provides Pixmap, an object that represents an offscreen drawable.

#ifndef XFC_GDK_PIXMAP_HH
#define XFC_GDK_PIXMAP_HH

#ifndef XFC_GDK_DRAWABLE_HH
#include <xfc/gdk/drawable.hh>
#endif

namespace Xfc {

namespace Gdk {
	
class Window;

/// @class Pixmap pixmap.hh xfc/gdk/pixmap.hh
/// @brief A GdkPixmap C++ wrapper class.
///
/// Pixmaps are offscreen drawables. They can be drawn upon with the standard
/// drawing primitives, then copied to another drawable (such as a Gdk::Window)
/// with draw(). The depth of a pixmap is the number of bits per pixels. Bitmaps
/// are simply pixmaps with a depth of 1. (That is, they are monochrome bitmaps,
/// each pixel can be either on or off).
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Pixmap : public Drawable
{
	friend class G::Object;

	Pixmap(const Pixmap&);
	Pixmap& operator=(const Pixmap&);

protected:
/// @name Constructors
/// @{

	explicit Pixmap(GdkPixmap *pixmap, bool owns_reference = true);
	///< Construct a new Pixmap from an existing GdkPixmap.
	///< @param pixmap A pointer to a GdkPixmap.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>pixmap</EM> can be a newly created GdkPixmap or an existing
	///< GdkPixmap. (see G::Object::Object).

/// @}

public:
	typedef GdkPixmap CObjectType;

/// @name Constructors
/// @{

	Pixmap(const Drawable& drawable, int width, int height);
	///< Construct a new pixmap with the given size, using <EM>window</EM>
	///< to determine the default values.
	///< @param drawable The Drawable to use to get the depth.
	///< @param width The width of the new pixmap in pixels.
	///< @param height The height of the new pixmap in pixels.
	///<
	///< The depth of the new pixmap will be equal to that of the window.
	///< Pixmap is created with a reference count of 1 that the caller owns.


	Pixmap(int width, int height, int depth);
	///< Create a new pixmap with the given size and depth.
	///< @param width The width of the new pixmap in pixels.
	///< @param height The height of the new pixmap in pixels.
	///< @param depth The depth (number of bits per pixel) of the new pixmap.
	///< 
	///< Pixmap is created with a reference count of 1 that the caller owns.

	Pixmap(const Drawable& drawable, const char* data, int width, int height, const Color& fg, const Color& bg);
	///< Create a two colored pixmap from data in XBM format.
	///< @param drawable The Drawable to use to get the depth.
	///< @param data A pointer to the data.
	///< @param width The width of the new pixmap in pixels.
	///< @param height The height of the new pixmap in pixels.
	///< @param fg The foreground color.
	///< @param bg The background color.
	///< 
	///< Pixmap is created with a reference count of 1 the caller owns.

	Pixmap(const char* data, int width, int height, int depth, const Color& fg, const Color& bg);
	///< Create a two colored pixmap from data in XBM format using the root window
	///< to determine the default values.
	/// @param data A pointer to the data.
	/// @param width The width of the new pixmap in pixels.
	/// @param height The height of the new pixmap in pixels.
	/// @param depth The depth (number of bits per pixel) of the new pixmap.
	/// @param fg The foreground color.
	/// @param bg The background color.
	///< 
	///< Pixmap is created with a reference count of 1 that the caller owns.

	Pixmap(const Drawable& drawable, const String& filename, Pointer<Bitmap> *mask = 0, const Color *transparent_color = 0);
	///< Create a pixmap from a XPM file.
	///< @param drawable The Drawable whose colormap the pixmap will use.
	///< @param filename The filename of a file containing XPM data.
	///< @param mask A smart pointer to a place to store a bitmap representing the transparency mask
	///<             of the XPM file. Can be null, in which case transparency will be ignored.
	///< @param transparent_color The color to be used for the pixels that are transparent in the input
	///<                          file. Can be null, in which case a default color will be used.
	///< 
	///< Pixmap is created with a reference count of 1 that the caller owns.

	Pixmap(Colormap *colormap, const String& filename, Pointer<Bitmap> *mask = 0, const Color *transparent_color = 0);
	///< Create a pixmap from a XPM file using a particular colormap.
	///< @param colormap The Colormap that the new pixmap will be use.
	///< @param filename The filename of a file containing XPM data.
	///< @param mask A smart pointer to a place to store a bitmap representing the transparency mask
	///<             of the XPM file. Can be null, in which case transparency will be ignored.
	///< @param transparent_color The color to be used for the pixels that are transparent in the input
	///<                          file. Can be null, in which case a default color will be used.
	///< 
	///< Pixmap is created with a reference count of 1 that the caller owns.

	Pixmap(const Drawable& drawable, const char * const *data, Pointer<Bitmap> *mask = 0, const Color *transparent_color = 0);
	///< Create a pixmap from data in XPM format.
	///< @param drawable The Drawable whose colormap the pixmap will use.
	///< @param data A pointer to a string containing the XPM data.
	///< @param mask A smart pointer to a place to store a bitmap representing the transparency mask
	///<             of the XPM file. Can be null, in which case transparency will be ignored.
	///< @param transparent_color The color to be used for the pixels that are transparent in the input
	///<                          file. Can be null, in which case a default color will be used.
	///< 
	///< Pixmap is created with a reference count of 1 that the caller owns.

	Pixmap(Colormap *colormap, const char * const *data, Pointer<Bitmap> *mask = 0, const Color *transparent_color = 0);
	///< Create a pixmap from data in XPM format using a particular colormap.
	///< @param colormap The Colormap that the new pixmap will be use.
	///< @param data A pointer to a string containing the XPM data.
	///< @param mask A smart pointer to a place to store a bitmap representing the transparency mask
	///<             of the XPM file. Can be null, in which case transparency will be ignored.
	///< @param transparent_color The color to be used for the pixels that are transparent in the input
	///<                          file. Can be null, in which case a default color will be used.
	///< 
	///< Pixmap is created with a reference count of 1 that the caller owns.

	virtual ~Pixmap();
	///< Destructor.
	
/// @}
/// @name Constructors
/// @{

	static Pointer<Pixmap> create(GdkNativeWindow anid, const Display *display = 0);
	///< Wraps a native pixmap in a Gdk::Pixmap.
	///< @param anid A native pixmap handle.
	///< @param display The Display where <EM>anid</EM> is located, or null for the default display.
	///< @return A smart pointer to the newly-created Gdk::Pixmap wrapper for the native pixmap,
	///< or null if the pixmap has been destroyed.
	///<
	///< In the X backend, a native pixmap handle is an Xlib XID. This method
	///< fail if the pixmap has been destroyed.

/// @}
/// @name Accessors
/// @{

	GdkPixmap* gdk_pixmap() const;
	///< Get a pointer to the GdkPixmap structure.

	GdkPixmapObject* gdk_pixmap_object() const;
	///< Get a pointer to the GdkPixmapObject structure.

/// @}
/// @name Accessors
/// @{

	static Pointer<Pixmap> lookup(GdkNativeWindow anid, const Display *display = 0);
	///< Looks up the Gdk::Pixmap that wraps the given native pixmap handle.
	///< @param anid A native pixmap handle.
	///< @param display The Display associated with anid, or null for the default display.
	///< @return The Gdk::Pixmap wrapper for the native pixmap, or null if there is none.
	///<
	///< In the X backend, a native pixmap handle is an Xlib XID.

/// @}
/// @name Methods
/// @{

	void clear(GC& gc, const Color& color);
	///< Clears a pixmap with the color specified.
	///< @param gc A graphics context.
	///< @param color The color to clear the pixmap with. 
	
/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/pixmap.inl>

#endif // XFC_GDK_PIXMAP_HH

