/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  textiter.inl - Gtk::TextIter inline functions
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

inline GtkTextIter*
Xfc::Gtk::TextIter::gtk_text_iter() const
{
	return reinterpret_cast<GtkTextIter*>(boxed_);
}

inline Xfc::Gtk::TextIter::operator GtkTextIter* () const
{
	return this ? gtk_text_iter() : 0;
}

inline int
Xfc::Gtk::TextIter::get_offset() const
{
	return gtk_text_iter_get_offset(gtk_text_iter());
}

inline int
Xfc::Gtk::TextIter::get_line() const
{
	return gtk_text_iter_get_line(gtk_text_iter());
}

inline int
Xfc::Gtk::TextIter::get_line_offset() const
{
	return gtk_text_iter_get_line_offset(gtk_text_iter());
}

inline int
Xfc::Gtk::TextIter::get_line_index() const
{
	return gtk_text_iter_get_line_index(gtk_text_iter());
}

inline int
Xfc::Gtk::TextIter::get_visible_line_offset() const
{
	return gtk_text_iter_get_visible_line_offset(gtk_text_iter());
}

inline int
Xfc::Gtk::TextIter::get_visible_line_index() const
{
	return gtk_text_iter_get_visible_line_index(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::editable(bool default_setting) const
{
	return gtk_text_iter_editable(gtk_text_iter(), default_setting);
}

inline bool
Xfc::Gtk::TextIter::can_insert(bool default_editability) const
{
	return gtk_text_iter_can_insert(gtk_text_iter(), default_editability);
}

inline bool
Xfc::Gtk::TextIter::starts_word() const
{
	return gtk_text_iter_starts_word(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::ends_word() const
{
	return gtk_text_iter_ends_word(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::inside_word() const
{
	return gtk_text_iter_inside_word(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::starts_sentence() const
{
	return gtk_text_iter_starts_sentence(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::ends_sentence() const
{
	return gtk_text_iter_ends_sentence(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::inside_sentence() const
{
	return gtk_text_iter_inside_sentence(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::starts_line() const
{
	return gtk_text_iter_starts_line(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::ends_line() const
{
	return gtk_text_iter_ends_line(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::is_cursor_position() const
{
	return gtk_text_iter_is_cursor_position(gtk_text_iter());
}

inline int
Xfc::Gtk::TextIter::get_chars_in_line() const
{
	return gtk_text_iter_get_chars_in_line(gtk_text_iter());
}

inline int
Xfc::Gtk::TextIter::get_bytes_in_line() const
{
	return gtk_text_iter_get_bytes_in_line(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::is_end() const
{
	return gtk_text_iter_is_end(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::is_start() const
{
	return gtk_text_iter_is_start(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_char()
{
	return gtk_text_iter_forward_char(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::backward_char()
{
	return gtk_text_iter_backward_char(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_chars(int count)
{
	return gtk_text_iter_forward_chars(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::backward_chars(int count)
{
	return gtk_text_iter_backward_chars(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::forward_line()
{
	return gtk_text_iter_forward_line(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::backward_line()
{
	return gtk_text_iter_backward_line(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_lines(int count)
{
	return gtk_text_iter_forward_lines(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::backward_lines(int count)
{
	return gtk_text_iter_backward_lines(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::forward_word_end()
{
	return gtk_text_iter_forward_word_end(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::backward_word_start()
{
	return gtk_text_iter_backward_word_start(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_word_ends(int count)
{
	return gtk_text_iter_forward_word_ends(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::backward_word_starts(int count)
{
	return gtk_text_iter_backward_word_starts(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::forward_visible_word_end()
{
	return gtk_text_iter_forward_visible_word_end(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::backward_visible_word_start()
{
	return gtk_text_iter_backward_visible_word_start(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_visible_word_ends(int count)
{
	return gtk_text_iter_forward_visible_word_ends(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::backward_visible_word_starts(int count)
{
	return gtk_text_iter_backward_visible_word_starts(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::forward_sentence_end()
{
	return gtk_text_iter_forward_sentence_end(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::backward_sentence_start()
{
	return gtk_text_iter_backward_sentence_start(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_sentence_ends(int count)
{
	return gtk_text_iter_forward_sentence_ends(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::backward_sentence_starts(int count)
{
	return gtk_text_iter_backward_sentence_starts(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::forward_cursor_position()
{
	return gtk_text_iter_forward_cursor_position(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::backward_cursor_position()
{
	return gtk_text_iter_backward_cursor_position(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_cursor_positions(int count)
{
	return gtk_text_iter_forward_cursor_positions(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::backward_cursor_positions(int count)
{
	return gtk_text_iter_backward_cursor_positions(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::forward_visible_cursor_position()
{
	return gtk_text_iter_forward_visible_cursor_position(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::backward_visible_cursor_position()
{
	return gtk_text_iter_backward_visible_cursor_position(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_visible_cursor_positions(int count)
{
	return gtk_text_iter_forward_visible_cursor_positions(gtk_text_iter(), count);
}

inline bool
Xfc::Gtk::TextIter::backward_visible_cursor_positions(int count)
{
	return gtk_text_iter_backward_visible_cursor_positions(gtk_text_iter(), count);
}

inline void
Xfc::Gtk::TextIter::set_offset(int char_offset)
{
	gtk_text_iter_set_offset(gtk_text_iter(), char_offset);
}

inline void
Xfc::Gtk::TextIter::set_line(int line_number)
{
	gtk_text_iter_set_line(gtk_text_iter(), line_number);
}

inline void
Xfc::Gtk::TextIter::set_line_offset(int char_on_line)
{
	gtk_text_iter_set_line_offset(gtk_text_iter(), char_on_line);
}

inline void
Xfc::Gtk::TextIter::set_line_index(int byte_on_line)
{
	gtk_text_iter_set_line_index(gtk_text_iter(), byte_on_line);
}

inline void
Xfc::Gtk::TextIter::forward_to_end()
{
	gtk_text_iter_forward_to_end(gtk_text_iter());
}

inline bool
Xfc::Gtk::TextIter::forward_to_line_end()
{
	return gtk_text_iter_forward_to_line_end(gtk_text_iter());
}

inline void
Xfc::Gtk::TextIter::set_visible_line_offset(int char_on_line)
{
	gtk_text_iter_set_visible_line_offset(gtk_text_iter(), char_on_line);
}

inline void
Xfc::Gtk::TextIter::set_visible_line_index(int byte_on_line)
{
	gtk_text_iter_set_visible_line_index(gtk_text_iter(), byte_on_line);
}

