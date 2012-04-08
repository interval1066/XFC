/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  editable.inl - Gtk::Editable inline functions
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

inline GtkEditable*
Xfc::Gtk::Editable::gtk_editable() const
{
	return reinterpret_cast<GtkEditable*>(instance_);
}

inline Xfc::Gtk::Editable::operator GtkEditable* () const
{
	return this ? ((GtkEditable*)instance_) : 0;
}

inline bool
Xfc::Gtk::Editable::get_selection_bounds(int *start, int *end) const
{
	return gtk_editable_get_selection_bounds(gtk_editable(), start, end);
}

inline int
Xfc::Gtk::Editable::get_position() const
{
	return gtk_editable_get_position(gtk_editable());
}

inline bool
Xfc::Gtk::Editable::get_editable() const
{
	return gtk_editable_get_editable(gtk_editable());
}

inline void
Xfc::Gtk::Editable::select_region (int start, int end)
{
	gtk_editable_select_region(gtk_editable(), start, end);
}

inline void
Xfc::Gtk::Editable::insert_text(const char *new_text, int& position)
{
	gtk_editable_insert_text(gtk_editable(), new_text, -1, &position);
}

inline void
Xfc::Gtk::Editable::delete_text(int start_pos, int end_pos)
{
	gtk_editable_delete_text(gtk_editable(), start_pos, end_pos);
}

inline void
Xfc::Gtk::Editable::cut_clipboard()
{
	gtk_editable_cut_clipboard(gtk_editable());
}

inline void
Xfc::Gtk::Editable::copy_clipboard()
{
	gtk_editable_copy_clipboard(gtk_editable());
}

inline void
Xfc::Gtk::Editable::paste_clipboard()
{
	gtk_editable_paste_clipboard(gtk_editable());
}

inline void
Xfc::Gtk::Editable::delete_selection()
{
	gtk_editable_delete_selection(gtk_editable());
}

inline void
Xfc::Gtk::Editable::set_position(int position)
{
	gtk_editable_set_position(gtk_editable(), position);
}

inline void
Xfc::Gtk::Editable::set_editable(bool is_editable)
{
	gtk_editable_set_editable(gtk_editable(), is_editable);
}

inline const Xfc::Gtk::Editable::InsertTextSignalProxy
Xfc::Gtk::Editable::signal_insert_text()
{
	return InsertTextSignalProxy(this, &insert_text_signal);
}

inline const Xfc::Gtk::Editable::DeleteTextSignalProxy
Xfc::Gtk::Editable::signal_delete_text()
{
	return DeleteTextSignalProxy(this, &delete_text_signal);
}

inline const Xfc::Gtk::Editable::ChangedSignalProxy
Xfc::Gtk::Editable::signal_changed()
{
	return ChangedSignalProxy(this, &changed_signal);
}

