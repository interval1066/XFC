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
 
/// @file xfc/gdk/image.hh
/// @brief A GdkImage C++ wrapper interface.
///
/// Provides Image, an object that represents an area for drawing bit-mapped graphics.

#ifndef XFC_GDK_IMAGE_HH
#define XFC_GDK_IMAGE_HH

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

namespace Xfc {

namespace Gdk {
	
class Colormap;
class Drawable;
class Pixbuf;
class Visual;

// @enum Gdk::ImageType
/// Specifies the type of a Gdk::Image.

enum ImageType
{
	IMAGE_NORMAL = GDK_IMAGE_NORMAL,
	///< The original X image type, which is quite slow since the image has to be
	///< transferred from the client to the server to display it.
	
	IMAGE_SHARED = GDK_IMAGE_SHARED,
	///< A faster image type, which uses shared memory to transfer the image data
	///< between client and server;	However this will only be available if client
	///< and server are on the same machine and the shared memory extension is 
	///< supported by the server.

	IMAGE_FASTEST = GDK_IMAGE_FASTEST
	///< Specifies that IMAGE_SHARED should be tried first, and if that fails
	///< then IMAGE_NORMAL will be used.
};

/// @class Image image.hh xfc/gdk/image.hh
/// @brief A GdkImage C++ wrapper class.
///
/// The Image object represents an area for drawing graphics. It has now been superceded
/// to a large extent by the much more flexible Gdk::Drawable RGB drawing methods.
///
/// An Image can be manipulated with get_pixel() and put_pixel(), or alternatively by 
/// changing the actual pixel data. Though manipulating the pixel data requires 
/// complicated code to cope with the different formats that may be used. To draw an
/// Image in a Gdk::Window or Gdk::Pixmap use Gdk::Drawable::draw_image().

class Image : public G::Object
{
	friend class G::Object;

	Image(const Image&);
	Image& operator=(const Image&);

protected:
/// @name Constructors
/// @{

	explicit Image(GdkImage *image, bool owns_reference = true);
	///< Construct a new Image from an existing GdkImage.
	///< @param image A pointer to a GdkImage.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>image</EM> can be a newly created GdkImage or an existing
	///< GdkImage. (see G::Object::Object).

/// @}

public:
	typedef GdkImage CObjectType;

/// @name Constructors
/// @{

	virtual ~Image();
	///< Destructor.

/// @}
/// @name Constructors
/// @{

	static Pointer<Image> create(ImageType type, const Visual& visual, int width, int height);
	///< Creates a new image.
	///< @param type The type of the image, one of IMAGE_NORMAL, IMAGE_SHARED and IMAGE_FASTEST.
	///< @param visual The Visual to use for the image.
	///< @param width The width of the image in pixels.
	///< @param height The height of the image in pixels.
	///< @return A smart pointer to the new Image, or null if the image could not be created.
	///
	///< IMAGE_FASTEST is probably the best choice, since it will try creating an
	///< IMAGE_SHARED image first and if that fails it will then use IMAGE_NORMAL.

/// @}
/// @name Accessors
/// @{

	GdkImage* gdk_image() const;
	///< Get a pointer to the GdkImage structure.

	operator GdkImage* () const;
	///< Conversion operator; safely converts a Image to a GdkImage pointer.

	ImageType image_type() const;
	///< Returns the type of the image.

	const Visual& visual() const;
	///< Returns the Visual used to create the image.

	ByteOrder byte_order() const;
	///< Returns the byte order for the image.

	int width() const;
	///< Returns the width of the image in pixels.

	int height() const;
	///< Returns the height of the image in pixels.

	unsigned short depth() const;
	///< Returns the depth of the image, i.e. the number of bits per pixel.

	unsigned short bytes_per_pixel() const;
	///< Returns the number of bytes per pixel.
	
	unsigned short bytes_per_line() const;
	///< Returns the number of bytes per line of the image.

	unsigned int get_pixel(int x, int y) const;
	///< Gets a pixel value at a specified position in the image.
	///< @param x The X coordinate of the pixel to get.
	///< @param y The Y coordinate of the pixel to get.
	///< @return The pixel value at the given position.

	Colormap* get_colormap() const;
	///< Retrieves the colormap for a given image, if it exists.
	///< @return The colormap for the image.
	///<
	///< An image will have a colormap if the drawable from which it was created
	///< has a colormap, or if a colormap was set explicitely with set_colormap().
	
/// @}
/// @name Methods
/// @{

	void put_pixel(int x, int y, unsigned int pixel);
	///< Sets a pixel in the image to a given pixel value.
	///< @param x The X coordinate of the pixel to set.
	///< @param y The Y coordinate of the pixel to set.
	///< @param pixel The pixel value to set.

	void set_colormap(Colormap& colormap);
	///< Sets the colormap for the image to the given colormap.
	///< @param colormap A Colormap.
	///<
	///< Normally there's no need to use this method, images are created with the
	///< correct colormap if you get the image from a drawable. If you create the image
	///< from scratch, use the colormap of the drawable you intend to render the image to.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/image.inl>

#endif // XFC_GDK_IMAGE_HH

