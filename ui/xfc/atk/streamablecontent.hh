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
 
/// @file xfc/atk/streamablecontent.hh
/// @brief An AtkStreamableContent C++ wrapper interface.
///
/// Provides StreamableContent, an interface which provides access to streamable content.

#ifndef XFC_ATK_STREAMABLE_CONTENT_HH
#define XFC_ATK_STREAMABLE_CONTENT_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __ATK_STREAMABLE_CONTENT_H__
#include <atk/atkstreamablecontent.h>
#endif

namespace Xfc {

namespace G {
class IOChannel;
}

namespace Atk {

/// @class StreamableContent streamablecontent.hh xfc/atk/streamablecontent.hh
/// @brief An AtkStreamableContent C++ wrapper class.
///
/// StreamableContent is an interface which provides access to streamable content.

class StreamableContent : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	StreamableContent();
	///< Constructs a new StreamableContent object.
	
	virtual ~StreamableContent() = 0;
	///< Destructors.

/// @}

public:
/// @name Accessors
/// @{

	AtkStreamableContent* atk_streamable_content() const;
	///< Get a pointer to the AtkStreamableContent structure.

	operator AtkStreamableContent* () const;
	///< Conversion operator; safely converts a StreamableContent to an AtkStreamableContent pointer.

	int get_n_mime_types() const;
	///< Gets the number of mime types supported by this object.
	///< @return an integer which is the number of mime types supported by the object.

	String get_mime_type(int i) const;
	///< Gets the character string of the specified mime type. 
	///< @param i An integer representing the position of the mime type starting from 0.
	///< @return A string representing the specified mime type.
	///<
	///< The first mime type is at position 0, the second at position 1, and so on.

	Pointer<G::IOChannel> get_stream(const char *mime_type) const;
	Pointer<G::IOChannel> get_stream(const String& mime_type) const;
	///< Gets the content in the specified mime type.
	///< @param mime_type A string representing the mime type.
	///< @return A GIOChannel which contains the content in the specified mime type.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/streamablecontent.inl>

#endif // XFC_ATK_STREAMABLE_CONTENT_HH

