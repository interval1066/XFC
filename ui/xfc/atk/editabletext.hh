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
 
/// @file xfc/atk/editabletext.hh
/// @brief A AtkEditableText C++ wrapper interface.
///
/// Provides EditableText, an interface implemented by components containing user-editable text content.

#ifndef XFC_ATK_EDITABLE_TEXT_HH
#define XFC_ATK_EDITABLE_TEXT_HH

#ifndef XFC_ATK_TEXT_HH
#include <xfc/atk/text.hh>
#endif

#ifndef __ATK_EDITABLE_TEXT_H__
#include <atk/atkeditabletext.h>
#endif

namespace Xfc {

namespace Atk {

/// @class EditableText editabletext.hh xfc/atk/editabletext.hh
/// @brief A AtkEditableText C++ wrapper class.
///
/// The EditableText interface should be implemented by UI components which contain text
/// which the user can edit, via the Atk::Object corresponding to that component (see Atk::Object).
///
/// EditableText is a subclass of Text, and as such, an object which implements EditableText
/// is by definition a Text implementor as well.

class EditableText : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	EditableText();
	///< Constructs a new EditableText object.
	
	virtual ~EditableText() = 0;
	///< Destructor.

/// @}

public:
/// @name Accessors
/// @{

	AtkEditableText* atk_editable_text() const;
	///< Get a pointer to the AtkEditableText structure.

	operator AtkEditableText* () const;
	///< Conversion operator; safely converts an EditableText to an AtkEditableText pointer.

/// @}
/// @name Methods
/// @{

	bool set_run_attributes(const std::vector<Attribute>& attribs, int start_offset, int end_offset);
	///< Sets the attributes for a specified range. 
	///< @param attribs A reference to a vector of Attribute that holds the list of attributes to set.
	///< @param start_offset The start of the range in which to set the attributes.
	///< @param end_offset The end of the range in which to set the attributes.
	///< @return <EM>true</EM> if the attributes were successfully set for the specified range,
	///< otherwise <EM>false</EM>.
	///<
	///< See the Atk::TextAttribute enum for examples of attributes that can be set,
	///< such as TEXT_ATTR_LEFT_MARGIN. Note that other attributes that do not have
	///< a corresponding TextAttribute may also be set for certain text widgets.

	void set_text_contents(const char *str);
	void set_text_contents(const String& str);
	///< Set <EM>str</EM> as the text contents of the EditableText.
	///< @param str The string to set as the text contents of the EditableText.

	void insert_text(const char *str, int *position);
	void insert_text(const String& str, int *position);
	///< Insert text at the given <EM>position</EM>.
	///< @param str The text to insert.
	///< @param position The caller initializes this to the position at which to insert the text.
	///<
	///< When the method returns <EM>position</EM> points to the position after the newly inserted text.

	void copy_text(int start_pos, int end_pos);
	///< Copy text from <EM>start_pos</EM> up to, but not including <EM>end_pos</EM> to the clipboard.
	///< @param start_pos The start position.
	///< @param end_pos The end position.

	void cut_text(int start_pos, int end_pos);
	///< Copy text from <EM>start_pos</EM> up to, but not including <EM>end_pos</EM>
	///< to the clipboard and then delete the text from the widget.
	///< @param start_pos The start position.
	///< @param end_pos The end position.

	void delete_text(int start_pos, int end_pos);
	///< Delete text from <EM>start_pos</EM> up to, but not including <EM>end_pos</EM>.
	///< @param start_pos The start position.
	///< @param end_pos The end position.

	void paste_text(int position);
	///< Paste text from the clipboard to the specified position.
	///< @param position The position to paste the text to.
	
/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/editabletext.inl>

#endif // XFC_ATK_EDITABLE_TEXT_HH

