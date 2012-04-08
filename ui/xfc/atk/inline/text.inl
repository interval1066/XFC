/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  text.inl - Atk::Text inline functions
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

/*  Atk::Attribute
 */

inline AtkAttribute*
Xfc::Atk::Attribute::atk_attribute() const
{
	return const_cast<AtkAttribute*>(&attrib_);
}

inline Xfc::Atk::TextAttribute
Xfc::Atk::Attribute::attr() const
{
	return (TextAttribute)atk_text_attribute_for_name(attrib_.name);
}

/*  Atk::TextRectangle
 */

inline AtkTextRectangle*
Xfc::Atk::TextRectangle::atk_text_rectangle() const
{
	return const_cast<AtkTextRectangle*>(&rectangle_);
}

inline Xfc::Atk::TextRectangle::operator AtkTextRectangle* () const
{
	return this ? const_cast<AtkTextRectangle*>(&rectangle_) : 0;
}

inline int
Xfc::Atk::TextRectangle::x() const
{
	return rectangle_.x;
}

inline int
Xfc::Atk::TextRectangle::y() const
{
	return rectangle_.y;
}

inline int
Xfc::Atk::TextRectangle::width() const
{
	return rectangle_.width;
}

inline int
Xfc::Atk::TextRectangle::height() const
{
	return rectangle_.height;
}

/*  Atk::TextRange
 */

inline AtkTextRange*
Xfc::Atk::TextRange::atk_text_rectangle() const
{
	return const_cast<AtkTextRange*>(&range_);
}

inline int
Xfc::Atk::TextRange::start_offset() const
{
	return range_.start_offset;
}

inline int
Xfc::Atk::TextRange::end_offset() const
{
	return range_.end_offset;
}

inline const char*
Xfc::Atk::TextRange::content() const
{
	return range_.content;
}

/*  Atk::Text
 */

inline AtkText*
Xfc::Atk::Text::atk_text() const
{
	return reinterpret_cast<AtkText*>(instance_);
}

inline Xfc::Atk::Text::operator AtkText* () const
{
	return this ? atk_text() : 0;
}

inline int
Xfc::Atk::Text::get_caret_offset() const
{
	return atk_text_get_caret_offset(atk_text());
}

inline void
Xfc::Atk::Text::get_character_extents(int offset, int *x, int *y, int *width, int *height, CoordType coords) const
{
	atk_text_get_character_extents(atk_text(), offset, x, y, width, height, (AtkCoordType)coords);
}

inline int
Xfc::Atk::Text::get_character_count() const
{
	return atk_text_get_character_count(atk_text());
}

inline int
Xfc::Atk::Text::get_offset_at_point(int x, int y, CoordType coords) const
{
	return atk_text_get_offset_at_point(atk_text(), x, y, (AtkCoordType)coords);
}

inline int
Xfc::Atk::Text::get_n_selections() const
{
	return atk_text_get_n_selections(atk_text());
}

inline bool
Xfc::Atk::Text::add_selection(int start_offset, int end_offset)
{
	return atk_text_add_selection(atk_text(), start_offset, end_offset);
}

inline bool
Xfc::Atk::Text::remove_selection(int selection_num)
{
	return atk_text_remove_selection(atk_text(), selection_num);
}

inline bool
Xfc::Atk::Text::set_selection(int selection_num, int start_offset, int end_offset)
{
	return atk_text_set_selection(atk_text(), selection_num, start_offset, end_offset);
}

inline bool
Xfc::Atk::Text::set_caret_offset(int offset)
{
	return atk_text_set_caret_offset(atk_text(), offset);
}

inline const Xfc::Atk::Text::TextChangedSignalProxy
Xfc::Atk::Text::signal_text_changed()
{
	return TextChangedSignalProxy(this, &text_changed_signal);
}

inline const Xfc::Atk::Text::TextCaretMovedSignalProxy
Xfc::Atk::Text::signal_text_caret_moved()
{
	return TextCaretMovedSignalProxy(this, &text_caret_moved_signal);
}

inline const Xfc::Atk::Text::TextSelectionChangedSignalProxy
Xfc::Atk::Text::signal_text_selection_changed()
{
	return TextSelectionChangedSignalProxy(this, &text_selection_changed_signal);
}

inline const Xfc::Atk::Text::TextAttributesChangedSignalProxy
Xfc::Atk::Text::signal_text_attributes_changed()
{
	return TextAttributesChangedSignalProxy(this, &text_attributes_changed_signal);
}

