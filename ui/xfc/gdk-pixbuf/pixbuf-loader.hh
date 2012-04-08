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

/// @file xfc/gdk-pixbuf/pixbuf-loader.hh
/// @brief A GdkPixbufLoader C++ wrapper interface.
///
/// PixbufLoader is an object that provides application-driven progressive image loading.

#ifndef XFC_GDK_PIXBUF_LOADER_HH
#define XFC_GDK_PIXBUF_LOADER_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef GDK_PIXBUF_H
#include <gdk-pixbuf/gdk-pixbuf.h>
#endif

#ifndef GDK_PIXBUF_LOADER_H
#include <gdk-pixbuf/gdk-pixbuf-loader.h>
#endif

namespace Xfc {

namespace G {
class Error;
}

namespace Gdk {
	
class Pixbuf;
class PixbufAnimation;
class PixbufFormat;

/// @class PixbufLoader pixbuf-loader.hh xfc/gdk-pixbuf/pixbuf-loader.hh
/// @brief A GdkPixbufLoader C++ wrapper class.
///
/// PixbufLoader provides a way for applications to drive the process of loading an image, by
/// letting them send the image data directly to the loader instead of having the loader read
/// the data from a file. Applications can use this functionality instead of constructing a 
/// Pixbuf or a PixbufAnimation directly from a file when they need to parse image data in
/// small chunks. For example, it should be used when reading an image from a (potentially)
/// slow network connection, or when loading an extremely large file.
///
/// To use PixbufLoader to load an image, just construct a new one, and call write() to send
/// the data to it. When done, close() should be called to end the stream and finalize 
/// everything. The loader will emit three important signals throughout the process. The
/// first, <EM>size_prepared</EM>, will be called as soon as the image has enough information
/// to determine the size of the image to be used. If you want to scale the image while 
/// loading it, you can call set_size() in response to this signal.
///
/// The second signal, <EM>area_prepared</EM>, will be called as soon as the pixbuf of the
/// desired size has been allocated. You can obtain it by calling get_pixbuf(). If you want
/// to use it, simply ref() it. In addition, no actual information will be passed in yet, so
/// the pixbuf can be safely filled with any temporary graphics (or an initial color) as
/// needed. You can also call get_pixbuf() later and get the same pixbuf.
///
/// The last signal, <EM>area_updated</EM> gets called every time a region is updated. This
/// way you can update a partially completed image. Note that you do not know anything about
/// the completeness of an image from the area updated. For example, in an interlaced image,
/// you need to make several passes before the image is done loading.
///
/// Loading an animation is almost as easy as loading an image. Once the first <EM>area_prepared</EM>
/// signal has been emitted, you can call get_animation() to get the PixbufAnimation object and 
/// get_iter() to get an PixbufAnimationIter for displaying it.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class PixbufLoader : public G::Object
{
	friend class G::Object;

	PixbufLoader(const PixbufLoader&);
	PixbufLoader& operator=(const PixbufLoader&);
	
protected:
/// @name Constructors
/// @{

	explicit PixbufLoader(GdkPixbufLoader *pixbuf_loader, bool owns_reference = true);
	///< Construct a new PixbufLoader from an existing GdkPixbufLoader.
	///< @param pixbuf_loader A pointer to a GdkPixbufLoader.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>pixbuf_loader</EM> can be a newly created GdkPixbufLoader or an existing
	///< GdkPixbufLoader. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, int, int> SizePreparedSignalType;
	typedef G::SignalProxy<TypeInstance, SizePreparedSignalType> SizePreparedSignalProxy;
	static const SizePreparedSignalType size_prepared_signal;
	///< Size prepared signal (see signal_size_prepared()). Calls a slot with the signature:
	///< @code
	///< void function(int width, int height);
	///< // width: The width of the image the pixbuf loader will create.
	///< // height: The height of the image the pixbuf loader will create.
	///< @endcode

	typedef G::Signal<void> AreaPreparedSignalType;
	typedef G::SignalProxy<TypeInstance, AreaPreparedSignalType> AreaPreparedSignalProxy;
	static const AreaPreparedSignalType area_prepared_signal;
	///< Area prepared signal (see signal_area_prepared()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, int, int, int, int> AreaUpdatedSignalType;
	typedef G::SignalProxy<TypeInstance, AreaUpdatedSignalType> AreaUpdatedSignalProxy;
	static const AreaUpdatedSignalType area_updated_signal;
	///< Area updated signal (see signal_area_updated()). Calls a slot with the signature:
	///< @code
	///< void function(int x, int y, int width, int height);
	///< // x: The X coordinate of the updated area.
	///< // y: The Y coordinate of the updated area.
	///< // width: The width of the updated area.
	///< // height: The height of the updated area.
	///< @endcode

	typedef G::Signal<void> ClosedSignalType;
	typedef G::SignalProxy<TypeInstance, ClosedSignalType> ClosedSignalProxy;
	static const ClosedSignalType closed_signal;
	///< Closed signal (see signal_closed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GdkPixbufLoader CObjectType;

/// @name Constructors
/// @{

	PixbufLoader();
	///< Constructs a new pixbuf loader object with a reference count of 1 that the caller owns.

	virtual ~PixbufLoader();
	///< Destructor.

/// @}
/// @name Constructors
/// @{

	static Pointer<PixbufLoader> create_with_type(const char *image_type, G::Error *error = 0);
	static Pointer<PixbufLoader> create_with_type(const String& image_type, G::Error *error = 0);
	///< Creates a new pixbuf loader object that always attempts to parse
	///< image data as if it were an image of type image_type, instead of
	///< identifying the type automatically.
	///< @param image_type The name of the image format to be loaded with the image.
	///< @param error The return location for an allocated G::Error, or null to ignore errors.
	///< @return A newly-created pixbuf loader, or null if any error occurs.
	///<
	///< Useful if you want an error if the image isn't the expected type,
	///< for loading image formats that can't be reliably identified by looking
	///< at the data, or if the user manually forces a specific type. The
	///< <EM>image_type</EM> can be png, jpeg, tiff, gif, xpm, pnm, ras, ico,
	///< bmp or wbmp.

	static Pointer<PixbufLoader> create_with_mime_type(const char *mime_type, G::Error *error = 0);
	static Pointer<PixbufLoader> create_with_mime_type(const String& mime_type, G::Error *error = 0);
	///< Creates a new pixbuf loader object that always attempts to parse image data
	///< as if it were an image of mime type <EM>mime_type</EM>, instead of identifying
	///< the type automatically.
	///< @param mime_type The mime type to be loaded.
	///< @param error The return location for an allocated G::Error, or null to ignore errors.
	///< @return A newly-created pixbuf loader, or null if any error occurs.
	///<
	///< This is useful if you want an error if the image isn't the expected mime type,
	///< for loading image formats that can't be reliably identified by looking at the data,
	///< or if the user manually forces a specific mime type.

/// @}
/// @name Accessors
/// @{

	GdkPixbufLoader* gdk_pixbuf_loader() const;
	///< Get a pointer to the GdkPixbufLoader structure.

	operator GdkPixbufLoader* () const;
	///< Conversion operator; safely converts a PixbufLoader to a GdkPixbufLoader pointer.

	Pointer<Pixbuf> get_pixbuf() const;
	///< Queries the Pixbuf that the pixbuf loader is currently creating.
	///< @return A smart pointer to the new Pixbuf the loader is creating, or null if
	///< not enough data has been read to determine how to create the image buffer.
	///<
	///< In general it only makes sense to call this function after the
	///< <EM>area_prepared</EM> signal has been emitted by the loader; this
	///< means that enough data has been read to know the size of the image
	///< that will be allocated. If the loader has not received enough data
	///< via write(), then this function returns null. The returned pixbuf
	///< will be the same in all future calls to the loader. If the loader
	///< is an animation, it will return the "static image" of the animation
	///< (see Gdk::PixbufAnimation::get_static_image()).

	Pointer<PixbufAnimation> get_animation() const;
	///< Queries the PixbufAnimation that the pixbuf loader is currently creating.
	///< @return A smart pointer to the PixbufAnimation that the loader is loading,
	///< or null if not enough data has been read to determine the information.
	///<
	///< In general it only makes sense to call this function after the
	///< <EM>area_prepared</EM> signal has been emitted by the loader. If the
	///< loader doesn't have enough bytes yet (hasn't emitted the area_prepared
	///< signal) this method will return null.

	Pointer<PixbufFormat> get_format() const;
	///< Obtains the available information about the format of the currently loading image file.
	///< @return A smart pointer to the new PixbufFormat, or null.

/// @}
/// @name Methods
/// @{

	void set_size(int width, int height);
	///< Causes the image to be scaled while it is loaded.
	///< @param width The desired width of the image being loaded.
	///< @param height The desired height of the image being loaded.
	///<
	///< The desired image size can be determined relative to the original
	///< size of the image by calling set_size() from a signal handler for the
	///< <EM>size_prepared</EM> signal. Attempts to set the desired image size
	///< are ignored after the emission of the <EM>size_prepared</EM> signal.

	bool write(const unsigned char *buffer, size_t count, G::Error *error);
	///< This method will cause a pixbuf loader to parse the next count bytes of an image.
	///< @param buffer A pointer to the image data.
	///< @param count The length of <EM>buffer</EM> in bytes.
	///< @param error The return location for errors.
	///< @return <EM>true</EM> if the data was loaded successfully, <EM>false</EM> if an error occurred.
	///<
	///< If an error occurs, the loader will be closed, and will not accept further writes.
	///< If false is returned, error will be set to an error from the GDK_PIXBUF_ERROR or G_FILE_ERROR domains.

	bool close(G::Error *error = 0);
	///< Informs a pixbuf loader that no further writes with write() will occur,
	///< so that it can free its internal loading structures. 
	///< @param error The return location for a G::Error, or null to ignore errors.
	///< @return <EM>true</EM> if all image data written so far was successfully
	///< passed out via the <EM>area_updated</EM> signal.
	///<
	///< This method tries to parse any data that hasn't yet been parsed;
	///< if the remaining data is partial or corrupt, an error will be returned.
	///< If false is returned, error will be set to an error from the 
	///< GDK_PIXBUF_ERROR or G_FILE_ERROR domains. If you're just cancelling a
	///< load rather than expecting it to be finished, passing null for error to
	///< ignore it is reasonable.

/// @}
/// @name Signal Proxies
/// @{

	const SizePreparedSignalProxy signal_size_prepared();
	///< Connect to the size_prepared_signal; emitted when the pixbuf loader
	///< has been fed the initial amount of data that is required to figure
	///< out the size of the image that it will create.

	const AreaPreparedSignalProxy signal_area_prepared();
	///< Connect to the area_prepared_signal; emitted when the pixbuf loader
	///< has allocated the pixbuf in the desired size.

	const AreaUpdatedSignalProxy signal_area_updated();
	///< Connect to the area_updated_signal; emitted when a significant area
	///< of the image being loaded has been updated.

	const ClosedSignalProxy signal_closed();
	///< Connect to the closed_signal; emitted when close() is called.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk-pixbuf/inline/pixbuf-loader.inl>

#endif // XFC_GDK_PIXBUF_LOADER_HH

