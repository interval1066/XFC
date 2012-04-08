/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
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
 
/// @file xfc/gdk-pixbuf/pixbuf-io.hh
/// @brief A GtkAboutDialog C++ wrapper interface.
///
///  Provides a module interface that extends Gdk::Pixbuf.

#ifndef XFC_GDK_PIXBUF_IO_HH
#define XFC_GDK_PIXBUF_IO_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef GDK_PIXBUF_IO_H
#include <gdk-pixbuf/gdk-pixbuf-io.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {

/// @class PixbufFormat pixbuf-io.hh xfc/gdk-pixbuf/pixbuf-io.hh
/// @brief A GdkPixbufFormat C++ wrapper class.
///
/// PixbufFormat contains information about the image format accepted by a module.

class PixbufFormat : public Xfc::Object
{
	PixbufFormat(const PixbufFormat&);
	PixbufFormat& operator=(const PixbufFormat&);

	GdkPixbufFormat *format_;

public:
/// @name Constructors
/// @{

	explicit PixbufFormat(GdkPixbufFormat *format);
	///< Construct a new PixbufFormat from an existing GdkPixbufFormat.
	///< @param format A pointer to a GdkPixbufFormat.
	
	~PixbufFormat();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GdkPixbufFormat* gdk_pixbuf_format() const;
	///< Get a pointer to the GdkPixbufFormat structure.

	String get_name() const;
	///< Returns the name of the format.

	String get_description() const;
	///< Returns a description of the format.

	std::vector<String> get_mime_types() const;
	///< Gets the mime types supported by the format.
	///< @return A vector of String holding the list mime types.

	std::vector<String> get_extensions() const;
	///< Gets the filename extensions typically used for files in the given format.
	///< @return A vector of String holding the list of filename extensions.

	bool is_writable() const;
	///< Determines whether pixbufs can be saved in the given format.
	///< @return <EM>true</EM> if pixbufs can be saved in the given format.
	
	bool is_scalable() const;
	///< Determines whether this image format is scalable. 
	///< @return Whether this image format is scalable.
	///<	
	///< If a file is in a scalable format, it is preferable to load it at the desired size, rather
	///< than loading it at the default size and scaling the resulting pixbuf to the desired size.

	bool is_disabled() const;
	///< Determines whether this image format is disabled (see set_disabled()).
	///< @return Whether this image format is disabled.
	
	String get_license() const;
	///< Returns information about the license of the image loader for the format. 
	///< @return A string describing the license of format.
	///< 	
	///< The returned string should be a shorthand for a wellknown license, e.g. 
	///< "LGPL", "GPL", "QPL", "GPL/QPL", or "other" to indicate some other license.
 
/// @}
/// @name Accessors
/// @{

	static bool get_formats(std::vector<Pointer<PixbufFormat> >& formats);
	///< Obtains the available information about the image formats supported by Gdk::Pixbuf.
	///< @param formats A vector of Pointer<PixbufFormat> to hold the list of the supported image formats.
	///< @return <EM>true</EM> if the vector is not empty.

	static PixbufFormat* get_file_info(const char *filename, int *width, int *height);
	static PixbufFormat* get_file_info(const String& filename, int *width, int *height);
	///< Parses an image file far enough to determine its format and size.
	///< @param filename The name of the file to identify. 
	///< @param width The return location for the width of the image, or null. 
	///< @param height The return location for the height of the image, or null. 
	///< @return A PixbufFormat object describing the image format of the file,
	///< or null if the image format wasn't recognized.
	 
/// @}
/// @name Methods
/// @{
	
	void set_disabled(bool disabled);
	///< Disables or enables an image format. 
	///< @param disabled Set to <EM>true</EM> to disable this pixbuf format.
	///<	
	///< If a format is disabled, gdk-pixbuf won't use the image loader for this format
	///< to load images. Applications can use this to avoid using image loaders with an
	///< inappropriate license, (see get_license()).
	
/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk-pixbuf/inline/pixbuf-io.inl>

#endif // XFC_GDK_PIXBUF_IO_HH

