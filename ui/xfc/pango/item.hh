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

/// @file xfc/pango/item.hh
/// @brief A PangoAnalysis and PangoItem C++ wrapper interface.
///
/// Provides Analysis and Item, two objects that store information about a segment of text.

#ifndef XFC_PANGO_ITEM_HH
#define XFC_PANGO_ITEM_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __PANGO_ITEM_H__
#include <pango/pango-item.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Pango {

class Attribute;
class Font;

/// @class Analysis item.hh xfc/pango/item.hh
/// @brief A PangoAnalysis C++ wrapper class.
///
/// Analysis is a read-only object that stores information about the properties of a segment
/// of text. You can obtain an Analysis by calling Pango::Context::itemize() which returns a
/// vector of Pointer<Item>. Each Item has an analysis() accessor that returns a reference
/// to the item's Analysis object.

class Analysis
{
	PangoAnalysis analysis_;

public:
/// @name Accessors
/// @{

	PangoAnalysis* pango_analysis() const;
	///< Get a pointer to the PangoAnalysis structure.

	PangoEngineShape* shape_engine() const;
	///< Get a pointer to the PangoEngineShape structure.

	PangoEngineLang* lang_engine() const;
	///< Get a pointer to the PangoEngineLang structure.

	Pango::Font *font() const;
	///< Returns the font for this segment.

	guint8 level() const;
	///< Returns the bidrectional level for this segment.

	PangoLanguage* language() const;
	///< Returns the language tag for this segment.

	bool extra_attributes(std::vector<Pointer<Attribute> >& attrs) const;
	///< Gets a list of attributes that apply to this segment.
	///< @param attrs A reference to a vector of Pointer<Attribute> to hold the list of attributes.
	///< @return <EM>true</EM> if the vector is not empty.

/// @}
};

/// @class Item item.hh xfc/pango/item.hh
/// @brief A PangoItem C++ wrapper class.
///
/// Item is an object that stores information about a segment of text. You can obtain an
/// Item by calling Pango::Context::itemize() which returns a vector of Pointer<Item>.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Item : public Xfc::Object
{
	PangoItem *item_;

public:
/// @name Constructors
/// @{

	Item();
	///< Construct a new item initialized to default values. The Item is created
	///< with a reference count of 1 that the caller owns.

	explicit Item(PangoItem *item, bool copy);
	///< Construct a new item from an existing PangoItem.
	///< @param item A pointer to a PangoItem.
	///< @param copy Whether the Item object should make a copy of PangoItem or not.
	///<
	///< The <EM>item</EM> can be a newly created PangoItem or an existing
	///< PangoItem. If <EM>copy</EM> is true Item will make a copy of PangoItem.
	///< If <EM>copy</EM> is false Item wont make a copy but instead takes over
	///< the ownership of PangoItem. Either way, the destructor will free the
	///< PangoItem when the Item object is destroyed.
	///<
	///< The Item is created with a reference count of 1 that the caller owns.

	Item(const Item& src);
	///< Copy constructor.
	///< @param src The source Item.

	~Item();	
	///< Destructor.

	Item& operator=(const Item& src);
	///< Assignment operator.
	///< @param src The source Item.

/// @}
/// @name Accessors
/// @{

	PangoItem* pango_item() const;
	///< Get a pointer to the PangoItem structure.

	operator PangoItem* () const;
	///< Conversion operator; safely converts an Item to a PangoItem pointer.

	int offset() const;
	///< Returns the offset of the segment from the beginning of the string in bytes.

	int length() const;
	///< Returns the length of the segment in bytes.
	
	int num_chars() const;
	///< Returns the length of the segment in characters.
	
	const Analysis& analysis() const;
	///< Returns a reference to the analysis object that stores the properties of the segment.
	
/// @}
/// @name Methods
/// @{

	Pointer<Item> split(int split_index, int split_offset);
	///< Modifies the item to cover only the text after <EM>split_index</EM>, and returns a new
	///< item that covers the text before <EM>split_index</EM> that used to be in the item.
	///< @param split_index The byte index at the position to split the item, relative to the start of the item.
	///< @param split_offset The number of characters between the start of the item and <EM>split_index</EM>.
	///< @return A smart pointer to a new item representing the text before <EM>split_index</EM>.
	///<
	///< You can think of <EM>split_index</EM> as the length of the returned item.
	///< <EM>split_index</EM> may not be 0, and it may not be greater than or equal to
	///< the length this item before the split (that is, there must be at least one byte
	///< assigned to each item, you can't create a zero-length item). <EM>split_offset</EM>
	///< is the length chars of the first (returned) item, and must be provided because
	///< the text used to generate the item isn't available, so split() can't count the
	///< character length of the split items itself.

/// @}
};

/// @name Item methods
/// @{

	std::vector<Pointer<Item> > reorder_items(const std::vector<Pointer<Item> >& logical_items);
	///< From a list of items in logical order and the associated directional levels,
	///< produce a list in visual order (the original list is unmodified).
	///< @param logical_items A vector of Pointer<Item> in logical order.
	///< @return A vector of Pointer<Item> in visual order.
	///<
	///< Please mail otaylor@redhat.com if you use this method.	It is not a particularly
	///< convenient interface, and the code is duplicated elsewhere in Pango for that reason.
	
/// @}

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/item.inl>

#endif // XFC_PANGO_ITEM_HH

