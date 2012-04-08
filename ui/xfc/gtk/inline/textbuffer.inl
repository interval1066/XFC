/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  textbuffer.inl - Gtk::TextMark, Gtk::TextChildAnchor and Gtk::TextBuffer inline functions
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

/*  Gtk::TextMark
 */

inline GtkTextMark*
Xfc::Gtk::TextMark::gtk_text_mark() const
{
	return reinterpret_cast<GtkTextMark*>(instance_);
}

inline Xfc::Gtk::TextMark::operator GtkTextMark* () const
{
	return this ? gtk_text_mark() : 0;
}

inline bool
Xfc::Gtk::TextMark::get_visible() const
{
	return gtk_text_mark_get_visible(gtk_text_mark());
}

inline bool
Xfc::Gtk::TextMark::get_deleted() const
{
	return gtk_text_mark_get_deleted(gtk_text_mark());
}

inline bool
Xfc::Gtk::TextMark::get_left_gravity() const
{
	return gtk_text_mark_get_left_gravity(gtk_text_mark());
}

inline void
Xfc::Gtk::TextMark::set_visible(bool setting)
{
	gtk_text_mark_set_visible(gtk_text_mark(), setting);
}

/*  Gtk::TextChildAnchor
 */

inline GtkTextChildAnchor*
Xfc::Gtk::TextChildAnchor::gtk_text_child_anchor() const
{
	return reinterpret_cast<GtkTextChildAnchor*>(instance_);
}

inline Xfc::Gtk::TextChildAnchor::operator GtkTextChildAnchor* () const
{
	return this ? gtk_text_child_anchor() : 0;
}

inline bool
Xfc::Gtk::TextChildAnchor::get_deleted() const
{
	return gtk_text_child_anchor_get_deleted(gtk_text_child_anchor());
}

/*  Gtk::TextBuffer
 */

inline GtkTextBuffer*
Xfc::Gtk::TextBuffer::gtk_text_buffer() const
{
	return reinterpret_cast<GtkTextBuffer*>(instance_);
}

inline Xfc::Gtk::TextBuffer::operator GtkTextBuffer* () const
{
	return this ? gtk_text_buffer() : 0;
}

inline int
Xfc::Gtk::TextBuffer::get_line_count() const
{
	return gtk_text_buffer_get_line_count(gtk_text_buffer());
}

inline int
Xfc::Gtk::TextBuffer::get_char_count() const
{
	return gtk_text_buffer_get_char_count(gtk_text_buffer());
}

inline bool
Xfc::Gtk::TextBuffer::get_modified() const
{
	return gtk_text_buffer_get_modified(gtk_text_buffer());
}

inline void
Xfc::Gtk::TextBuffer::begin_user_action()
{
	gtk_text_buffer_begin_user_action(gtk_text_buffer());
}

inline void
Xfc::Gtk::TextBuffer::end_user_action()
{
	gtk_text_buffer_end_user_action(gtk_text_buffer());
}

inline void
Xfc::Gtk::TextBuffer::delete_mark_by_name(const char *name)
{
	gtk_text_buffer_delete_mark_by_name(gtk_text_buffer(), name);
}

inline void
Xfc::Gtk::TextBuffer::set_modified(bool setting)
{
	gtk_text_buffer_set_modified(gtk_text_buffer(), setting);
}

inline bool
Xfc::Gtk::TextBuffer::delete_selection(bool interactive, bool default_editable)
{
	return gtk_text_buffer_delete_selection(gtk_text_buffer(), interactive, default_editable);
}

inline const Xfc::Gtk::TextBuffer::InsertTextSignalProxy
Xfc::Gtk::TextBuffer::signal_insert_text()
{
	return InsertTextSignalProxy(this, &insert_text_signal);
}

inline const Xfc::Gtk::TextBuffer::InsertPixbufSignalProxy
Xfc::Gtk::TextBuffer::signal_insert_pixbuf()
{
	return InsertPixbufSignalProxy(this, &insert_pixbuf_signal);
}

inline const Xfc::Gtk::TextBuffer::InsertChildAnchorSignalProxy
Xfc::Gtk::TextBuffer::signal_insert_child_anchor()
{
	return InsertChildAnchorSignalProxy(this, &insert_child_anchor_signal);
}

inline const Xfc::Gtk::TextBuffer::DeleteRangeSignalProxy
Xfc::Gtk::TextBuffer::signal_delete_range()
{
	return DeleteRangeSignalProxy(this, &delete_range_signal);
}

inline const Xfc::Gtk::TextBuffer::ChangedSignalProxy
Xfc::Gtk::TextBuffer::signal_changed()
{
	return ChangedSignalProxy(this, &changed_signal);
}

inline const Xfc::Gtk::TextBuffer::ModifiedChangedSignalProxy
Xfc::Gtk::TextBuffer::signal_modified_changed()
{
	return ModifiedChangedSignalProxy(this, &modified_changed_signal);
}

inline const Xfc::Gtk::TextBuffer::MarkSetSignalProxy
Xfc::Gtk::TextBuffer::signal_mark_set()
{
	return MarkSetSignalProxy(this, &mark_set_signal);
}

inline const Xfc::Gtk::TextBuffer::MarkDeletedSignalProxy
Xfc::Gtk::TextBuffer::signal_mark_deleted()
{
	return MarkDeletedSignalProxy(this, &mark_deleted_signal);
}

inline const Xfc::Gtk::TextBuffer::ApplyTagSignalProxy
Xfc::Gtk::TextBuffer::signal_apply_tag()
{
	return ApplyTagSignalProxy(this, &apply_tag_signal);
}

inline const Xfc::Gtk::TextBuffer::RemoveTagSignalProxy
Xfc::Gtk::TextBuffer::signal_remove_tag()
{
	return RemoveTagSignalProxy(this, &remove_tag_signal);
}

inline const Xfc::Gtk::TextBuffer::BeginUserActionSignalProxy
Xfc::Gtk::TextBuffer::signal_begin_user_action()
{
	return BeginUserActionSignalProxy(this, &begin_user_action_signal);
}

inline const Xfc::Gtk::TextBuffer::EndUserActionSignalProxy
Xfc::Gtk::TextBuffer::signal_end_user_action()
{
	return EndUserActionSignalProxy(this, &end_user_action_signal);
}

