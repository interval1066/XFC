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
 
/// @file xfc/atk/image.hh
/// @brief An AtkImage C++ wrapper interface.
///
/// Provides Image, an interface implemented by components which expose image or pixmap content on-screen.

#ifndef XFC_ATK_IMAGE_HH
#define XFC_ATK_IMAGE_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef XFC_ATK_UTIL_HH
#include <xfc/atk/util.hh>
#endif

#ifndef __ATK_IMAGE_H__
#include <atk/atkimage.h>
#endif

namespace Xfc {

namespace Atk {

/// @class Image image.hh xfc/atk/image.hh
/// @brief An AtkImage C++ wrapper class.
///
/// Image should be implemented by Atk::Object subtypes on behalf of components which
/// display image or pixmap information on-screen, and which provide information (other
/// than just widget borders, etc.) via that image content. For instance, icons, buttons
/// with icons, toolbar elements, and image viewing panes typically should implement Image.
///
/// Image primarily provides two types of information: coordinate information (useful for
/// screen review mode of screen readers, and for use by on-screen magnifiers), and
/// descriptive information. The descriptive information is provided for alternative, 
/// text-only presentation of the most significant information present in the image.

class Image : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Image();
	///< Constructs a new Image object.
	
	virtual ~Image() = 0;
	///< Destructor.

/// @}

public:
/// @name Accessors
/// @{

	AtkImage* atk_image() const;
	///< Get a pointer to the AtkImage structure.

	operator AtkImage* () const;
	///< Conversion operator; safely converts an Image to an AtkImage pointer.

	String get_image_description() const;
	///< Get a textual description of the image.
	///< @return A string representing the image description.

	void get_image_size(int *height, int *width) const;
	///< Get the width and height in pixels for the specified image. 
	///< @param width The address of an int filled with the image width, or null.
	///< @param height The address of an int filled with the image height, or null.
	///<
	///< The values of width and height are returned as -1 if the values
	///< cannot be obtained.
	
	void get_image_position(int *x, int *y, CoordType coord_type) const;
	///< Gets the position of the image in the form of a point specifying
	///< the images top-left corner. 
	///< @param x The address of an int to put the x coordinate position, or null.
	///< @param y The address of an int to put the y coordinate position, or null.
	///< @param coord_type Specifies whether the coordinates are relative to the screen
	///< or to the components top level window.
	///<
	///< The values of <EM>x</EM> and <EM>y</EM> are returned as -1 if
	///< the values cannot be obtained.

/// @}
/// @name Methods
/// @{

	bool set_image_description(const char *description);
	bool set_image_description(const String& description);
	///< Sets the textual description for the image.
	///< @param description A string description to set for image.
	///< @return <EM>true</EM> if the description is set, <EM>false</EM> otherwise.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/image.inl>

#endif // XFC_ATK_IMAGE_HH

