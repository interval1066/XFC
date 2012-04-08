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
 
/// @file xfc/atk/document.hh
/// @brief An AtkDocument C++ wrapper interface.
///
/// Provides Document, an interface which allows access to a DOM associated with an object.

#ifndef XFC_ATK_DOCUMENT_HH
#define XFC_ATK_DOCUMENT_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __ATK_DOCUMENT_H__
#include <atk/atkdocument.h>
#endif

namespace Xfc {

namespace Atk {

/// @class Document document.hh xfc/atk/document.hh
/// @brief An AtkDocument C++ wrapper class.
///
/// The Document interface should be supported by any object that has an associated 
/// document object model (DOM). This interface provides the standard mechanism 
/// allowing an assistive technology access to the DOM.

class Document : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Document();
	///< Constructs a new Document object.

	virtual ~Document() = 0;
	///< Destructor.

/// @}

public:
/// @name Accessors
/// @{

	AtkDocument* atk_document() const;
	///< Get a pointer to the AtkDocument structure.

	operator AtkDocument* () const;
	///< Conversion operator; safely converts a Document to an AtkDocument pointer.

	String get_document_type() const;
	///< Gets a string indicating the document type.
	///< @return A string indicating the document type.

	void* get_document() const;
	///< Gets a generic pointer that points to an instance of the DOM.
	///< @return A generic pointer that points to an instance of the DOM.
	///< 
	///< It is up to the caller to check the GType by calling G::TypeInstance::type()
	///< to determine how to cast this pointer.

/// *}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/document.inl>

#endif // XFC_ATK_DOCUMENT_HH

