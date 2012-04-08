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

/// @file xfc/gdk-pixbuf/pixbuf.hh
/// @brief A GdkPixbuf C++ wrapper interface.
///
/// Pixbuf is an object that contains information that describes an image in memory.

#ifndef XFC_GDK_PIXBUF_HH
#define XFC_GDK_PIXBUF_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef GDK_PIXBUF_H
#include <gdk-pixbuf/gdk-pixbuf.h>
#endif

#ifndef __GDK_RGB_H__
#include <gdk/gdkrgb.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Error;
}

namespace Gdk {
	
class Bitmap;
class Colormap;
class Drawable;
class GC;
class Image;
class Pixmap;

/// @enum Colorspace
/// Defines the color spaces that are supported by the gdk-pixbuf library.
/// Currently only RGB is supported.

enum Colorspace
{
	COLORSPACE_RGB = GDK_COLORSPACE_RGB ///< Indicates a red/green/blue additive color space.
};

/// @enum InterpType
/// Describes the different interpolation modes that can be used with the scaling functions. 
/// INTERP_NEAREST is the fastest scaling method, but has horrible quality when scaling down.
/// INTERP_BILINEAR is the best choice if you aren't sure what to choose, it has a good 
/// speed/quality balance.
///
/// <B>Note:</B> Cubic filtering is missing from the list; hyperbolic interpolation is
/// just as fast and results in higher quality.

enum InterpType
{
	INTERP_NEAREST = GDK_INTERP_NEAREST,
	///< Nearest neighbor sampling; this is the fastest and lowest quality mode;
	///< Quality is normally unacceptable when scaling down, but may be OK when
	///< scaling up.
	
	INTERP_TILES = GDK_INTERP_TILES,
	///< This is an accurate simulation of the PostScript image operator without
	///< any interpolation enabled; Each pixel is rendered as a tiny parallelogram
	///< of solid color, the edges of which are implemented with antialiasing;
	///< It resembles nearest neighbor for enlargement, and bilinear for reduction.
	
	INTERP_BILINEAR = GDK_INTERP_BILINEAR,
	///< Best quality/speed balance; use this mode by default (bilinear interpolation);
	///< For enlargement, it is equivalent to point-sampling the ideal bilinear-interpolated
	///< image; For reduction, it is equivalent to laying down small tiles and integrating
	///< over the coverage area.
	
	INTERP_HYPER = GDK_INTERP_HYPER
	///< This is the slowest and highest quality reconstruction function; It is derived
	///< from the hyperbolic filters in Wolberg's "Digital Image Warping", and is formally
	///< defined as the hyperbolic-filter sampling the ideal hyperbolic-filter interpolated
	///< image (the filter is designed to be idempotent for 1:1 pixel mapping).
};

/// @enum PixbufRotation
/// The possible rotations which can be passed to rotate_simple(). To make them easier to use,
/// their numerical values are the actual degrees.
 
enum PixbufRotation
{
	PIXBUF_ROTATE_NONE = GDK_PIXBUF_ROTATE_NONE, ///< No rotation.
	PIXBUF_ROTATE_COUNTERCLOCKWISE = GDK_PIXBUF_ROTATE_COUNTERCLOCKWISE, ///< Rotate by 90 degrees.
	PIXBUF_ROTATE_UPSIDEDOWN = GDK_PIXBUF_ROTATE_UPSIDEDOWN, ///< Rotate by 180 degrees.
	PIXBUF_ROTATE_CLOCKWISE = GDK_PIXBUF_ROTATE_CLOCKWISE ///< Rotate by 270 degrees.
};

/// @enum PixbufAlphaMode
/// These values can be passed to render_to_drawable_alpha() to control how the alpha chanel
/// of an image should be handled. This method can create a bilevel clipping mask (black and
/// white) and use it while pagfcng the image. In the future, when the X Window System gets
/// an alpha channel extension, it will be possible to do full alpha compositing onto arbitrary
/// drawables. For now both cases fall back to a bilevel clipping mask.

enum PixbufAlphaMode
{
	PIXBUF_ALPHA_BILEVEL = GDK_PIXBUF_ALPHA_BILEVEL,
	///< A bilevel clipping mask (black and white) will be created and used
	///< to draw the image; Pixels below 0.5 opacity will be considered fully
	///< transparent, and all others will be considered fully opaque.

	PIXBUF_ALPHA_FULL = GDK_PIXBUF_ALPHA_FULL
	///< For now falls back to PIXBUF_ALPHA_BILEVEL; In the future it will do
	///< full alpha compositing.
};

/// @class Pixbuf pixbuf.hh xfc/gdk-pixbuf/pixbuf.hh
/// @brief A GdkPixbuf C++ wrapper class.
///
/// Pixbuf is an object that contains information describing an image in memory.
///
/// The XFC demo program has several examples of using G::Error with Pixbufs. See
/// <demowindow.cc> and <image.cc> in the <demos/gfc-demo> subdirectory.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Pixbuf : public G::Object
{
	friend class G::Object;

	Pixbuf(const Pixbuf&);
	Pixbuf& operator=(const Pixbuf&);

protected:
/// @name Constructors
/// @{

	explicit Pixbuf(GdkPixbuf *pixbuf, bool owns_reference = true);
	///< Construct a new Pixbuf from an existing GdkPixbuf.
	///< @param pixbuf A pointer to a GdkPixbuf.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>pixbuf</EM> can be a newly created GdkPixbuf or an existing
	///< GdkPixbuf. (see G::Object::Object).

/// @}
	
public:
	typedef GdkPixbuf CObjectType;
	
	typedef sigc::slot<bool, const char*, size_t, G::Error*> SaveSlot;
	///< Signature of the callback slot to be called when saving a pixbuf.
	///<
	///< <B>Example:</B> Method signature for SaveSlot.
	///< @code
	///< bool method(const char *buffer, size_t count, G::Error *error);
	///<
	///< // buffer: The bytes to be written. 
	///< // count:  The number of bytes in <EM>buffer</EM>. 
	///< // error:  The return location for any error.
	///< // return: true if successful, false (with error set) if failed. 
	///< @endcode
	///<
	///< SaveSlot is called once for each block of bytes that is "written"
	///< by one of the overloaded save methods. If successful it should return
	///< true. If an error occurs it should set error and return false, in 
	///< which case the save method will fail with the same error. 

/// @name Constructors
/// @{

	Pixbuf(const Pixbuf& src, int src_x, int src_y, int width, int height);
	///< Constructs a new pixbuf (a sub-pixbuf) which represents a sub-region of <EM>src</EM>.
	///< @param src A Pixbuf.
	///< @param src_x The source X coordinate in <EM>src</EM>.
	///< @param src_y The source Y coordinate in <EM>src</EM>.
	///< @param width The width of the region in <EM>src</EM>.
	///< @param height The height of region in <EM>src</EM>.
	///<
	///< The new pixbuf shares its pixels with the original pixbuf, so writing to one
	///< affects both. The new pixbuf holds a reference to <EM>src</EM> pixbuf, so <EM>src</EM> 
	///< pixbuf will not be finalized until the new pixbuf is finalized. Pixbuf is created
	///< with a reference count of 1 that the caller owns.

	Pixbuf(const unsigned char *data, int width, int height, int rowstride, bool has_alpha,
	       GdkPixbufDestroyNotify destroy_fn = 0, void *destroy_fn_data = 0,
	       int bits_per_sample = 8, Colorspace colorspace = COLORSPACE_RGB);
	///< Constructs a new pixbuf out of in-memory image data.
	///< @param data The image data in 8-bit/sample packed format.
	///< @param width The width of the image in pixels.
	///< @param height The height of the image in pixels.
	///< @param rowstride The distance in bytes between rows.
	///< @param has_alpha Whether the data has an opacity channel.
	///< @param destroy_fn The function used to free the data when the pixbuf's reference
	///<                   count drops to zero, or null if the data should not be freed.
	///< @param destroy_fn_data The closure data to pass to the destroy notification function.
	///< @param bits_per_sample The number of bits per sample.
	///< @param colorspace The Gdk::Colorspace for the image data.
	///<
	///< Currently only RGB images with 8 bits per sample are supported. Wrapping
	///< an existing pixel buffer is the most basic way to construct a pixbuf. You need
	///< to specify the destroy notification function that will be called when the data
	///< buffer needs to be freed; this will happen when a Gdk::Pixbuf is finalized by the
	///< reference counting functions. If you have a chunk of static data compiled into
	///< your application, you can pass in null as the destroy notification function so
	///< that the data will not be freed. Pixbuf is created with a reference count of 1
	///< that  the caller owns.

	Pixbuf(const char **data);
	///< Constructs a new pixbuf by parsing XPM data in memory.
	///< @param data A pointer to inline XPM data.
	///<
	///< This data is commonly the result of including an XPM file into a program's C source.
	///< Pixbuf is created with a reference count of 1 that  the caller owns.

	virtual ~Pixbuf();
	///< Destructor.
	
/// @}
/// @name Constructors
/// @{

	static Pointer<Pixbuf> create(const char *filename, G::Error *error = 0);
	static Pointer<Pixbuf> create(const String& filename, G::Error *error = 0);
	///< Creates a new pixbuf by loading an image from a file.
	///< @param filename The name of file to load.
	///< @param error The return location for an error.
	///< @return A newly-created pixbuf, or null if any of several error conditions occurred.
	///<
	///< The file format is detected automatically. If an error occurs, then <EM>error</EM>
	///< will be set and G::Error::get() will return true. Possible errors are in the
	///< GDK_PIXBUF_ERROR and G_FILE_ERROR domains.
	///<
	///< The image is loaded from the file in a synchronous fashion. This means
	///< that the GDK-PIXBUF library takes control of the application while the
	///< file is being loaded; from the user's point of view, the application
	///< will block until the image is done loading. This constructor can be used
	///< by applications in which blocking is acceptable while an image is being
	///< loaded. It can also be used to load small images in general. Applications
	///< that need progressive loading can use the PixbufLoader functionality instead.
	///<

	static Pointer<Pixbuf> create(const char *filename, int width, int height, bool preserve_aspect_ratio, G::Error *error = 0);
 	static Pointer<Pixbuf> create(const String& filename, int width, int height, bool preserve_aspect_ratio, G::Error *error = 0);
	///< Creates a new pixbuf by loading an image from a file.
	///< @param filename The name of file to load.
	///< @param width The width the image should have.
	///< @param height The height the image should have.
	///< @param preserve_aspect_ratio Set to <EM>true</EM> to preserve the image's aspect ratio.
	///< @param error The return location for an error.
	///< @return A newly-created pixbuf, or null if any of several error conditions occurred.
	///<
	///< The file format is detected automatically. If an error occurs, then <EM>error</EM>
	///< will be set and G::Error::get() will return true. Possible errors are in the
	///< GDK_PIXBUF_ERROR and G_FILE_ERROR domains. The image will be scaled to fit in the
	///< requested size, preserving its aspect ratio.
	///<
	///< Possible error conditions include: the file could not be opened, there was no
	///< loader for the file's format, there was not enough memory to allocate the
	///< image buffer, or the image file contained invalid data.

	static Pointer<Pixbuf> create(int width, int height, bool has_alpha, int bits_per_sample = 8, Colorspace colorspace = COLORSPACE_RGB);
	///< Creates a new (blank) pixbuf with an optimal rowstride and a new buffer.
	///< @param width The width of the image in pixels.
	///< @param height The height of the image in pixels.
	///< @param has_alpha Whether the image should have transparency information.
	///< @param bits_per_sample The number of bits per color sample.
	///< @param colorspace The Gdk::Colorspace for the image.
	///< @return A smart pointer to the new pixbuf, or null if not enough memory could be allocated.
	///<
	///< Note that the buffer is not cleared; you will have to fill it completely yourself.
	///< This is a convenience constructor used to create a pixbuf with an empty buffer. This
	///< is equivalent to constructing a pixbuf with a newly allocating data buffer. It computes
	///< an optimal rowstride so that rendering can be performed with an efficient algorithm.

	static Pointer<Pixbuf> create(const Drawable& drawable, int x, int y, int width, int height, Colormap *colormap = 0);
	///< Creates a new pixbuf with image data from a server-side drawable
	///< (see get_from_drawable() for full details).
	///< @param drawable The source drawable.
	///< @param x The source X coordinate within <EM>drawable</EM>.
	///< @param y The source Y coordinate within <EM>drawable</EM>.
	///< @param width The width in pixels of region to get.
	///< @param height The height in pixels of region to get.
	///< @param colormap A colormap if <EM>drawable</EM> doesn't have one set.
	///< @return A smart pointer to the new pixbuf, or null if an error occurs;
	///< The new pixbuf has no alpha channel.

	static Pointer<Pixbuf> create(const Image& image, int x, int y, int width, int height, Colormap *colormap = 0);
	///< Creates a new pixbuf from the specified image (see get_from_drawable() for full details).
	///< @param image The source image.
	///< @param x The source X coordinate within <EM>image</EM>.
	///< @param y The source Y coordinate within <EM>image</EM>.
	///< @param width The width in pixels of region to get.
	///< @param height The height in pixels of region to get.
	///< @param colormap A colormap if <EM>image</EM> doesn't have one set.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if an error occurs.

	static Pointer<Pixbuf> create(int data_length, const unsigned char *data, bool copy_pixels, G::Error *error = 0);
	///< Creates a pixbuf from a flat representation that is suitable
	///< for storing as inline data in a program.
	///< @param data_length The length in bytes of the data argument.
	///< @param data The byte data containing a serialized GdkPixdata structure.
	///< @param copy_pixels Set <EM>true</EM> to copy the pixel data, or use direct
	///<                    pointers data for the resulting pixbuf.
	///< @param error The G::Error return location, may be null to ignore errors.
	///< @return A newly-created Pixbuf, or null if an error occurred.
	///<
	///< This is useful if you want to ship a program with images, but don't
	///< want to depend on any external files. GTK+ ships with a program called
	///< gdk-pixbuf-csource which allows for conversion of GdkPixbufs into such
	///< a inline representation. In almost all cases, you should pass the --raw
	///< flag to gdk-pixbuf-csource. A sample invocation would be:<BR>
	///< @code
	///< gdk-pixbuf-csource --raw --name=myimage_inline myimage.png
	///< @endcode
	///< For the typical case where the inline pixbuf is read-only static data,
	///< you don't need to copy the pixel data unless you intend to write to it,
	///< so you can pass false for copy_pixels. (If you pass --rle to
	///< gdk-pixbuf-csource, a copy will be made even if copy_pixels is false,
	///< so using this option is generally a bad idea.)
	///<
	///< If you create a pixbuf from const inline data compiled into your program,
	///< it's probably safe to ignore errors, since things will always succeed. For
	///< non-const inline data, you could get out of memory. For untrusted inline
	///< data located at runtime, you could have corrupt inline data in addition.

/// @}
/// @name Accessors
/// @{

	GdkPixbuf* gdk_pixbuf() const;
	///< Get a pointer to the GdkPixbuf structure.

	operator GdkPixbuf* () const;
	///< Conversion operator; safely converts a Pixbuf to a GdkPixbuf pointer.

	Colorspace get_colorspace() const;
	///< Returns the color space of a pixbuf.
	
	int get_n_channels() const;
	///< Returns the number of channels of a pixbuf.
	
	bool get_has_alpha() const;
	///< Returns true if a pixbuf has an alpha channel (opacity information).
	
	int get_bits_per_sample() const;
	///< Returns the number of bits per color sample in a pixbuf.
	
	unsigned char* get_pixels() const;
	///< Gets a pointer to the pixel data of a pixbuf.
	///< @return A pointer to the pixbuf's pixel data.

	int get_width() const;
	///< Returns the width of a pixbuf in pixels.

	int get_height() const;
	///< Returns the height of a pixbuf in pixels.

	int get_rowstride() const;
	///< Returns the rowstride of a pixbuf, which is the number of bytes between rows.
	
	String get_option(const char *key) const;
	String get_option(const String& key) const;
	///< Looks up <EM>key</EM> in the list of options that may have been attached
	///< to the pixbuf when it was loaded.
	///< @param key A String.
	///< @return The value associated with <EM>key</EM>, or a null String if <EM>key</EM> was not found.

/// @}
/// @name Methods
/// @{

	Pointer<Pixbuf> copy() const;
	///< Creates a new pixbuf from a copy of the information in this pixbuf.
	///< @return A newly created pixbuf, or null if not enough memory could be allocated.
	///<
	///< This is not the same as just doing a ref() on the old pixbuf; the copy method
	///< will actually duplicate the pixel data in memory and create a new Pixbuf for it.

	void fill(unsigned int pixel);
	///< Clears a pixbuf to the given RGBA value, converting the RGBA value into the pixbuf's pixel format.
	///< @param pixel The RGBA pixel to clear to (0xffffffff is opaque white, 0x00000000 transparent black).
	///<
	///< The alpha will be ignored if the pixbuf doesn't have an alpha channel.

	bool save(const String& filename, const char *type, G::Error *error, ...);
	///< Saves the pixbuf to a file in type, which is currently "jpeg" or "png".
	///< @param filename The name of the file to save.
	///< @param type The name of the file format.
	///< @param error The return location for any error, or null to ignore errors.
	///< @param ... A variable list of key-value (char* / char*) save options.
	///< @return <EM>true</EM> if an error was set.
	///<
	///< If error is set, false will be returned. Possible errors include those in
	///< the GDK_PIXBUF_ERROR and the G_FILE_ERROR domains. The variable argument list
	///< should be null-terminated; if not empty, it should contain pairs of character
	///< strings that modify the save parameters. For example:<BR>
	///< @code
	///< G::Error error;
	///< pixbuf->save(filename, "jpeg", &error, "quality", "100", 0);
	///< @endcode
	///< Currently only a few parameters exist. JPEG images can be saved with a "quality"
	///< parameter with a value in the range [0,100]. Text chunks can be attached to PNG
	///< images by specifying parameters of the form \htmlonly"tEXt::key"\endhtmlonly,
	///< where key is an ASCII string of length 1-79. The values are UTF-8 encoded strings.

	bool save(const char *filename, const char *type, char **option_keys, char **option_values, G::Error *error = 0);
	bool save(const String& filename, const char *type, char **option_keys, char **option_values, G::Error *error = 0);
	///< Saves the pixbuf to a file in type, which is currently "jpeg" or "png".
	///< @param filename The name of the file to save.
	///< @param type The name of the file format.
	///< @param option_keys The name of the options to set, null-terminated;
	///< @param option_values The values for the named options.
	///< @param error The return location for any error, or null to ignore errors.
	///< @return <EM>true</EM> if an error was set.
	///<
	///< If error is set, false will be returned. Possible errors include those in
	///< the GDK_PIXBUF_ERROR and the G_FILE_ERROR domains.

	bool save(const SaveSlot& slot, const char *type, G::Error *error, ...);
	///< Saves the pixbuf in format type by feeding the produced data to a callback slot.
	///< @param slot A callback slot that is called to save each block of data that the save routine generates. 
	///< @param type The name of file format. 
	///< @param error The return location for any error, or null. 
	///< @param ... A variable list of key-value (char* / char*) save options.
	///< @return Whether an error was set.
	///<	 
	///< Can be used when you want to store the image to something other than a file,
	///< such as an in-memory buffer or a socket. If error is set, false will be returned.
	///< Possible errors include those in the GDK_PIXBUF_ERROR domain and whatever the 
	///< save function generates. 
	
	bool save(const SaveSlot& slot, const char *type, char **option_keys, char **option_values, G::Error *error = 0);
	///< Saves the pixbuf to a callback slot in format type, which is currently "jpeg", "png" or "ico". 
	///< @param slot A callback slot that is called to save each block of data that the save routine generates. 
	///< @param type The name of file format. 
	///< @param option_keys The name of options to set, null-terminated.
	///< @param option_values The values for the named <EM>options</EM>. 
	///< @param error The return location for any error, or null. 
	///< @return Whether an error was set.
	///<	
	///< If error is set, <EM>false</EM> will be returned.

	bool save(char **buffer, size_t *buffer_size, const char *type, G::Error *error, ...);
	///< Saves the pixbuf to a new buffer in format type, which is currently "jpeg", "png" or "ico". 
	///< @param buffer The location to receive a pointer to the new buffer. 
	///< @param buffer_size The location to receive the size of the new buffer. 
	///< @param type The name of file format. 
	///< @param error The return location for any error, or null. 
	///< @param ... A variable list of key-value (char* / char*) save options.
	///< @return Whether an error was set.
	///<	
	///< This is a convenience function that uses gdk_pixbuf_save_to_callback()
	///< to do the real work. Note that the buffer is not null-terminated and may
	///< contain embedded nulls. If error is set, <EM>false</EM> will be returned
	///< and the string will be set to null. Possible errors include those in the
	///< GDK_PIXBUF_ERROR domain. 

	bool save(char **buffer, size_t *buffer_size, const char *type, char **option_keys, char **option_values, G::Error *error = 0);
	///< Saves the pixbuf to a new buffer in format type, which is currently "jpeg", "png" or "ico". 
	///< @param buffer The location to receive a pointer to the new buffer. 
	///< @param buffer_size The location to receive the size of the new buffer. 
	///< @param type The name of file format. 
	///< @param option_keys The name of options to set, null-terminated.
	///< @param option_values The values for the named <EM>options</EM>. 
	///< @param error The return location for any error, or null. 
	
	Pointer<Pixbuf> add_alpha(bool substitute_color, unsigned char red, unsigned char green, unsigned char blue);
	///< Adds an alpha channel to this pixbuf and returns the result as a new pixbuf
	///< @param substitute_color Whether to set a color to zero opacity. If this is false,
	///<                         then the (r, g, b) arguments will be ignored.
	///< @param red The red value to substitute.
	///< @param green The green value to substitute.
	///< @param blue the blue value to substitute.
	///< @return A newly-created pixbuf.
	///<
	///< If the existing pixbuf already had an alpha channel, the channel values are copied
	///< from the original; otherwise, the alpha channel is initialized to 255 (full opacity).
	///< If substitute_color is true, then the color specified by (r, g, b) will be assigned
	///< zero opacity. That is, if you pass (255, 255, 255) for the substitute color, all
	///< white pixels will become fully transparent.

	void copy_area(const Pixbuf& src, int src_x, int src_y, int width, int height, int dest_x, int dest_y);
	///< Copies a rectangular area from <EM>src</EM> to this pixbuf; conversion
	///< of pixbuf formats is done automatically.
	///< @param src The source pixbuf.
	///< @param src_x The source X coordinate within <EM>src</EM>.
	///< @param src_y The source Y coordinate within <EM>src</EM>.
	///< @param width The width of the area to copy.
	///< @param height The height of the area to copy.
	///< @param dest_x The destination X coordinate within this pixbuf.
	///< @param dest_y The destination Y coordinate within this pixbuf.

	void copy_area(const Pixbuf& src, const Rectangle& src_rect, int dest_x, int dest_y);
	///< Copies a rectangular area from <EM>src</EM> to this pixbuf; conversion
	///< of pixbuf formats is done automatically.
	///< @param src The source pixbuf.
	///< @param src_rect The rectangular area within <EM>src</EM> to copy.
	///< @param dest_x The destination X coordinate within this pixbuf.
	///< @param dest_y The destination Y coordinate within this pixbuf.

	void saturate_and_pixelate(const Pixbuf& src, float saturation, bool pixelate);
	///< Modifies saturation and optionally pixelates <EM>src</EM>, placing the result this pixbuf.
	///< @param src The source image.
	///< @param saturation The saturation factor.
	///< @param pixelate Whether to pixelate.
	///<
	///< If saturation is 1.0 then saturation is not changed. If it's less than 1.0,
	///< saturation is reduced (the image is darkened); if greater than 1.0, saturation
	///< is increased (the image is brightened). If pixelate is true, then pixels are
	///< faded in a checkerboard pattern to create a pixelated image. This pixbuf and
	///< <EM>src</EM> must have the same image format, size, and rowstride.

	void saturate_and_pixelate(float saturation, bool pixelate);
	///< Modifies saturation and optionally pixelates the pixbuf.
	///< @param saturation The saturation factor.
	///< @param pixelate Whether to pixelate.
	///<
	///< If saturation is 1.0 then saturation is not changed. If it's less than 1.0,
	///< saturation is reduced (the image is darkened); if greater than 1.0, saturation
	///< is increased (the image is brightened). If pixelate is true, then pixels are
	///< faded in a checkerboard pattern to create a pixelated image. This pixbuf and
	///< <EM>src</EM> must have the same image format, size, and rowstride.

/// @}
/// @name Transformation Methods
/// @{
	
	Pointer<Pixbuf> scale_simple(int width, int height, InterpType interp_type);
	///< Create a new pixbuf containing a copy of this pixbuf scaled to width x height.
	///< @param width The width of destination image.
	///< @param height The height of destination image.
	///< @param interp_type The interpolation type for the transformation.
	///< @return A smart pointer to the new pixbuf, or null if not enough memory could
	///< be allocated for it.
	///<
	///< Leaves this pixbuf unaffected. interp_type should be Gdk::INTERP_NEAREST
	///< if you want maximum speed (but when scaling down, Gdk::INTERP_NEAREST is usually
	///< unusably ugly). The default interp_type should be Gdk::INTERP_BILINEAR which
	///< offers reasonable quality and speed. You can scale a sub-portion of this pixbuf
	///< by constructing a sub-pixbuf pointing into this pixbuf.
	///<
	///< For more complicated scaling/compositing see scale() and composite().

	void scale
	(
		const Pixbuf& src,
		int dest_x,
		int dest_y,
		int dest_width,
		int dest_height,
		double offset_x,
		double offset_y,
		double scale_x,
		double scale_y,
		InterpType interp_type
	);
	///< Creates a transformation of the source image <EM>src</EM> by scaling by
	///< <EM>scale_x</EM> and <EM>scale_y</EM> then translating by <EM>offset_x</EM>
	///< and <EM>offset_y</EM>, then renders the rectangle (dest_x, dest_y, dest_width,
	///< dest_height) of the resulting image onto the destination image replacing the
	///< previous contents.
	///< @param src The source pixbuf.
	///< @param dest_x The left coordinate for the region to render.
	///< @param dest_y The top coordinate for the region to render.
	///< @param dest_width The width of the region to render.
	///< @param dest_height The height of the region to render
	///< @param offset_x The offset in the X direction (currently rounded to an integer).
	///< @param offset_y The offset in the Y direction (currently rounded to an integer).
	///< @param scale_x The scale factor in the X direction.
	///< @param scale_y The scale factor in the Y direction.
	///< @param interp_type The interpolation type for the transformation.
	///<
	///< Try to use scale_simple() first, this method is the industrial-strength
	///< power tool you can fall back to if scale_simple() isn't powerful enough.

	void scale
	(
		const Pixbuf& src,
		const Rectangle& dest_rect,
		double offset_x,
		double offset_y,
		double scale_x,
		double scale_y,
		InterpType interp_type
	);
	///< Creates a transformation of the source image <EM>src</EM> by scaling by
	///< <EM>scale_x</EM> and <EM>scale_y</EM> then translating by <EM>offset_x</EM>
	///< and <EM>offset_y</EM>, then renders the rectangle <EM>dest_rect</EM> of the
	///< resulting image onto the destination image replacing the previous contents.
	///< @param src The source pixbuf.
	///< @param dest_rect The rectangular region to render.
	///< @param offset_x The offset in the X direction (currently rounded to an integer).
	///< @param offset_y The offset in the Y direction (currently rounded to an integer).
	///< @param scale_x The scale factor in the X direction.
	///< @param scale_y The scale factor in the Y direction.
	///< @param interp_type The interpolation type for the transformation.
	///<
	///< Try to use scale_simple() first, this method is the industrial-strength
	///< power tool you can fall back to if scale_simple() isn't powerful enough.

	Pointer<Pixbuf> composite_color_simple
	(
		int width,
		int height,
		InterpType interp_type,
		int overall_alpha,
		int check_size,
		unsigned int color1,
		unsigned int color2

	);
	///< Creates a new pixbuf by scaling this pixbuf to <EM>width</EM> x <EM>height</EM> and
	///< compositing the result with a checkboard of colors <EM>color1</EM> and <EM>color2</EM>.
	///< @param width The width of new image.
	///< @param height The height of new image.
	///< @param interp_type The interpolation type for the transformation.
	///< @param overall_alpha The overall alpha for this (source) pixbuf (0..255).
	///< @param check_size The size of checks in the checkboard (must be a power of two).
	///< @param color1 The color of check at upper left.
	///< @param color2 The color of the other check.
	///< @return A smart pointer to the new pixbuf, or null if not enough memory could be allocated for it.

	void composite
	(
		const Pixbuf& src,
		int dest_x,
		int dest_y,
		int dest_width,
		int dest_height,
		double offset_x,
		double offset_y,
		double scale_x,
		double scale_y,
		InterpType interp_type,
		int overall_alpha
	);
	///< Creates a transformation of the source image <EM>src</EM> by scaling by
	///< <EM>scale_x</EM> and <EM>scale_y</EM> then translating by <EM>offset_x</EM>
	///< and <EM>offset_y</EM>, then composites the rectangle (dest_x, dest_y, dest_width,
	///< dest_height) of the resulting image onto the destination image.
	///< @param src The source pixbuf.
	///< @param dest_x The left coordinate for the region to render.
	///< @param dest_y The top coordinate for the region to render.
	///< @param dest_width The width of the region to render.
	///< @param dest_height The height of the region to render
	///< @param offset_x The offset in the X direction (currently rounded to an integer).
	///< @param offset_y The offset in the Y direction (currently rounded to an integer).
	///< @param scale_x The scale factor in the X direction.
	///< @param scale_y The scale factor in the Y direction.
	///< @param interp_type The interpolation type for the transformation.
	///< @param overall_alpha The overall alpha for source image (0..255).

	void composite
	(
		const Pixbuf& src,
		const Rectangle& dest_rect,
		double offset_x,
		double offset_y,
		double scale_x,
		double scale_y,
		InterpType interp_type,
		int overall_alpha
	);
	///< Creates a transformation of the source image <EM>src</EM> by scaling by
	///< <EM>scale_x</EM> and <EM>scale_y</EM> then translating by <EM>offset_x</EM>
	///< and <EM>offset_y</EM>, then composites the rectangle <EM>dest_rect</EM> of
	///< the resulting image onto the destination image.
	///< @param src The source pixbuf.
	///< @param dest_rect The rectangular region to render.
	///< @param offset_x The offset in the X direction (currently rounded to an integer).
	///< @param offset_y The offset in the Y direction (currently rounded to an integer).
	///< @param scale_x The scale factor in the X direction.
	///< @param scale_y The scale factor in the Y direction.
	///< @param interp_type The interpolation type for the transformation.
	///< @param overall_alpha The overall alpha for source image (0..255).

	void composite_color
	(
		const Pixbuf& src,
		int dest_x,
		int dest_y,
		int dest_width,
		int dest_height,
		double offset_x,
		double offset_y,
		double scale_x,
		double scale_y,
		InterpType interp_type,
		int overall_alpha,
		int check_x,
		int check_y,
		int check_size,
		unsigned int color1,
		unsigned int color2
	);
	///< Creates a transformation of the source image <EM>src</EM> by scaling by
	///< <EM>scale_x</EM> and <EM>scale_y</EM> then translating by <EM>offset_x</EM>
	///< and <EM>offset_y</EM>, then composites the rectangle (dest_x, dest_y, dest_width,
	///< dest_height) of the resulting image with a checkboard of the colors <EM>color1</EM>
	///< and <EM>color2</EM> and renders it onto the destination image.
	///< @param src The source pixbuf.
	///< @param dest_x The left coordinate for the region to render.
	///< @param dest_y The top coordinate for the region to render.
	///< @param dest_width The width of the region to render.
	///< @param dest_height The height of the region to render
	///< @param offset_x The offset in the X direction (currently rounded to an integer).
	///< @param offset_y The offset in the Y direction (currently rounded to an integer).
	///< @param scale_x The scale factor in the X direction.
	///< @param scale_y The scale factor in the Y direction.
	///< @param interp_type The interpolation type for the transformation.
	///< @param overall_alpha The overall alpha for source image (0..255).
	///< @param check_x The X offset for the checkboard (origin of checkboard is at -check_x, -check_y).
	///< @param check_y The Y offset for the checkboard.
	///< @param check_size The size of checks in the checkboard (must be a power of two).
	///< @param color1 The color of check at upper left.
	///< @param color2 The color of the other check.
	///<
	///< See composite_color_simple() for a simpler variant of this method suitable for many tasks.

	void composite_color
	(
		const Pixbuf& src,
		const Rectangle& dest_rect,
		double offset_x,
		double offset_y,
		double scale_x,
		double scale_y,
		InterpType interp_type,
		int overall_alpha,
		const Point& check_offset,
		int check_size,
		unsigned int color1,
		unsigned int color2
	);
	///< Creates a transformation of the source image <EM>src</EM> by scaling by
	///< <EM>scale_x</EM> and <EM>scale_y</EM> then translating by <EM>offset_x</EM>
	///< and <EM>offset_y</EM>, then composites the rectangle <EM>dest_rect</EM> of
	///< the resulting image with a checkboard of the colors <EM>color1</EM> and
	///< <EM>color2</EM> and renders it onto the destination image.
	///< @param src The source pixbuf.
	///< @param dest_rect The rectangular region to render.
	///< @param offset_x The offset in the X direction (currently rounded to an integer).
	///< @param offset_y The offset in the Y direction (currently rounded to an integer).
	///< @param scale_x The scale factor in the X direction.
	///< @param scale_y The scale factor in the Y direction.
	///< @param interp_type The interpolation type for the transformation.
	///< @param overall_alpha The overall alpha for source image (0..255).
	///< @param check_offset A Point holding the x, y offset for the checkboard (origin of
	///<                     the checkboard is at -check_offset.x, -check_offset.y).
	///< @param check_size The size of checks in the checkboard (must be a power of two).
	///< @param color1 The color of check at upper left.
	///< @param color2 The color of the other check.
	///<
	///< See composite_color_simple() for a simpler variant of this method suitable for many tasks.

	Pointer<Pixbuf> rotate_simple(PixbufRotation angle);
	///< Rotates a the pixbuf by a multiple of 90 degrees, and returns the result in a new pixbuf.
	///< @param angle The angle to rotate by. 
	///< @return A new pixbuf.
	
	Pointer<Pixbuf> flip(bool horizontal);
	///< Flips the pixbuf horizontally or vertically and returns the result in a new pixbuf.
	///< @param horizontal Set to <EM>true</EM> to flip horizontally, <EM>false</EM> to flip vertically. 
	///< @return A new pixbuf.

/// @}
/// @name GDK Pixbuf Methods
/// @{

	void render_threshold_alpha
	(
		Bitmap& bitmap,
		int src_x,
		int src_y,
		int dest_x,
		int dest_y,
		int width,
		int height,
		int alpha_threshold
	);
	///< Takes the opacity values in a rectangular portion of the pixbuf and thresholds them
	///< to produce a bi-level alpha mask that can be used as a clipping mask for a drawable.
	///< @param bitmap The Bitmap where the bilevel mask will be painted to.
	///< @param src_x The source X coordinate within the pixbuf.
	///< @param src_y The source Y coordinate within the pixbuf.
	///< @param dest_x The destination X coordinate within the bitmap.
	///< @param dest_y The destination Y coordinate within the bitmap.
	///< @param width The width of the region to threshold, or -1 to use the pixbuf width.
	///< @param height The height of the region to threshold, or -1 to use the pixbuf height.
	///< @param alpha_threshold Opacity values below this will be painted as zero;
	///< all other values will be painted as one.

	void render_pixmap_and_mask
	(
		Pointer<Pixmap> *pixmap_return,
		Pointer<Bitmap> *mask_return,
		int alpha_threshold,
		Colormap *colormap = 0
	);
	///< Creates a pixmap and a mask bitmap which are returned in the pixmap_return and
	///< mask_return arguments, respectively, and renders a pixbuf and its corresponding
	///< thresholded alpha mask to them.
	///< @param pixmap_return The location to store a pointer to the created pixmap,
	///<                      or null if the pixmap is not needed.
	///< @param mask_return The location to store a pointer to the created mask,
	///<                    or null if the mask is not needed.
	///< @param alpha_threshold The threshold value for opacity values.
	///< @param colormap A Colormap, or null to use the colormap returned by gdk_rgb_get_colormap().
	///<
	///< This is merely a convenience method; applications that need to render pixbufs
	///< with dither offsets or to given drawables should use render_threshold_alpha() or
	///< Gdk::Drawable::draw_pixbuf().
	///<
	///< If <EM>colormap</EM> is null the pixmap is created with the Colormap returned
	///< by gdk_rgb_get_colormap(). Normally you will want to use the actual colormap
	///< for a widget instead. If the pixbuf does not have an alpha channel, then 
	///< mask_return will be set to null.

	bool get_from_drawable
	(
		const Drawable& src,
		int src_x,
		int src_y,
		int dest_x,
		int dest_y,
		int width,
		int height,
		Colormap *colormap = 0
	);
	///< Transfers (copies) image data from a server-side drawable to the
	///< client-side RGB(A) buffer inside this pixbuf.
	///< @param src The source drawable.
	///< @param src_x The source X coordinate within the <EM>src</EM> drawable.
	///< @param src_y The source Y coordinate within the <EM>src</EM> drawable.
	///< @param dest_x The destination X coordinate in this pixbuf.
	///< @param dest_y The destination Y coordinate in this pixbuf.
	///< @param width The width in pixels of region to get.
	///< @param height The height in pixels of region to get.
	///< @param colormap A colormap if <EM>src</EM> doesn't have one set.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if an error occurs.
	///<
	///< This allows you to efficiently read individual pixels on the client side.
	///< If the drawable is a pixmap, a colormap must be specified. If the <EM>src</EM>
	///< drawable src has no colormap (Gdk::drawable::get_colormap() returns null), 
	///< then a suitable colormap must be specified. Typically a Gdk::Window or a pixmap
	///< created from a Gdk::Window will already have a colormap associated with it. If
	///< the drawable has a colormap, the <EM>colormap</EM> argument will be ignored.
	///< If the drawable is a bitmap (1 bit per pixel pixmap), then a colormap is not
	///< required; pixels with a value of 1 are assumed to be white, and pixels with a
	///< value of 0 are assumed to be black. For taking screenshots,
	///< Gdk::Colormap::get_system() returns the correct colormap to use. If this pixbuf
	///< contains alpha information, then the filled pixels will be set to full opacity 
	///< (alpha = 255).
	///<
	///< If the specified drawable is a pixmap, then the requested source rectangle must
	///< be completely contained within the pixmap, otherwise the method will return
	///< false. For pixmaps only (not for windows) passing -1 for width or height is
	///< allowed to mean the full width or height of the pixmap.
	///<
	///< If the specified drawable is a window, and the window is off the screen, then
	///< there is no image data in the obscured/offscreen regions to be placed in the
	///< pixbuf. The contents of portions of the pixbuf corresponding to the offscreen
	///< region are undefined. If the window you're obtaining data from is partially
	///< obscured by other windows, then the contents of the pixbuf areas corresponding
	///< to the obscured regions are undefined.
	///<
	///< If the target drawable is not mapped (typically because it's iconified/minimized
	///< or not on the current workspace), then false will be returned. If memory can't be
	///< allocated for the return value, false will be returned instead.
	///<
	///< <B>Note:</B> There are several ways this method can fail, and if it fails
	///< it returns false; so check the return value.
	///<
	///< This method calls Gdk::Drawable::get_image() internally and converts the resulting
	///< image to a Gdk::Pixbuf, so the documentation for Gdk::Drawable::get_image() may
	///< also be relevant.

	bool get_from_image
	(
		const Image& src,
		int src_x,
		int src_y,
		int dest_x,
		int dest_y,
		int width,
		int height,
		Colormap *colormap = 0
	);
	///< Copies image data from an Image to this pixbuf (see get_from_drawable() for details).
	///< @param src The source image.
	///< @param src_x The source X coordinate within the <EM>src</EM> image.
	///< @param src_y The source Y coordinate within the <EM>src</EM> image.
	///< @param dest_x The destination X coordinate within this pixbuf.
	///< @param dest_y The destination Y coordinate within this pixbuf.
	///< @param width The width in pixels of region to get.
	///< @param height The height in pixels of region to get.
	///< @param colormap A colormap if <EM>src</EM> doesn't have one set.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if an error occurs.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk-pixbuf/inline/pixbuf.inl>

#endif // XFC_GDK_PIXBUF_HH

