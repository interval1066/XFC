/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  break.inl - Pango::LogAttr inline functions
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

inline PangoLogAttr*
Xfc::Pango::LogAttr::pango_log_attr() const
{
	return const_cast<PangoLogAttr*>(&attr_);
}

inline Xfc::Pango::LogAttr::operator PangoLogAttr* () const
{
	return this ? const_cast<PangoLogAttr*>(&attr_) : 0;
}

inline bool
Xfc::Pango::LogAttr::is_line_break() const
{
	return attr_.is_line_break != 0;
}

inline bool
Xfc::Pango::LogAttr::is_mandatory_break() const
{
	return attr_.is_mandatory_break != 0;
}

inline bool
Xfc::Pango::LogAttr::is_char_break() const
{
	return attr_.is_char_break != 0;
}

inline bool
Xfc::Pango::LogAttr::is_white() const
{
	return attr_.is_white != 0;
}

inline bool
Xfc::Pango::LogAttr::is_cursor_position() const
{
	return attr_.is_cursor_position != 0;
}

inline bool
Xfc::Pango::LogAttr::is_word_start() const
{
	return attr_.is_word_start != 0;
}

inline bool
Xfc::Pango::LogAttr::is_word_end() const
{
	return attr_.is_word_end != 0;
}

inline bool
Xfc::Pango::LogAttr::is_sentence_boundary() const
{
	return attr_.is_sentence_boundary != 0;
}

inline bool
Xfc::Pango::LogAttr::is_sentence_start() const
{
	return attr_.is_sentence_start != 0;
}

inline bool
Xfc::Pango::LogAttr::is_sentence_end() const
{
	return attr_.is_sentence_end != 0;
}

inline bool
Xfc::Pango::LogAttr::backspace_deletes_character() const
{
	return attr_.backspace_deletes_character != 0;
}

inline void
Xfc::Pango::LogAttr::set_is_line_break(bool setting)
{
	attr_.is_line_break = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_mandatory_break(bool setting)
{
	attr_.is_mandatory_break = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_char_break(bool setting)
{
	attr_.is_char_break = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_white(bool setting)
{
	attr_.is_white = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_cursor_position(bool setting)
{
	attr_.is_cursor_position = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_word_start(bool setting)
{
	attr_.is_word_start = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_word_end(bool setting)
{
	attr_.is_word_end = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_sentence_boundary(bool setting)
{
	attr_.is_sentence_boundary = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_sentence_start(bool setting)
{
	attr_.is_sentence_start = setting;
}

inline void
Xfc::Pango::LogAttr::set_is_sentence_end(bool setting)
{
	attr_.is_sentence_end = setting;
}

