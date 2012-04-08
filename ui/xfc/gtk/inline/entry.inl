/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  entry.inl - Gtk::Entry inline functions
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

inline GtkEntry*
Xfc::Gtk::Entry::gtk_entry() const
{
	return reinterpret_cast<GtkEntry*>(instance_);
}

inline Xfc::Gtk::Entry::operator GtkEntry* () const
{
	return this ? ((GtkEntry*)instance_) : 0;
}

inline bool
Xfc::Gtk::Entry::get_visibility() const
{
	return gtk_entry_get_visibility((GtkEntry*)instance_);
}

inline bool
Xfc::Gtk::Entry::get_has_frame() const
{
	return gtk_entry_get_has_frame(gtk_entry());
}

inline int
Xfc::Gtk::Entry::get_max_length() const
{
	return gtk_entry_get_max_length(gtk_entry());
}

inline bool
Xfc::Gtk::Entry::get_activates_default() const
{
	return gtk_entry_get_activates_default(gtk_entry());
}

inline int
Xfc::Gtk::Entry::get_width_chars() const
{
	return gtk_entry_get_width_chars(gtk_entry());
}

inline void
Xfc::Gtk::Entry::get_layout_offsets(int *x, int *y) const
{
	gtk_entry_get_layout_offsets(gtk_entry(), x, y);
}

inline float 
Xfc::Gtk::Entry::get_alignment() const
{
	return gtk_entry_get_alignment(gtk_entry());
}	
	
inline int 
Xfc::Gtk::Entry::layout_index_to_text_index(int layout_index)
{
	return gtk_entry_layout_index_to_text_index(gtk_entry(), layout_index);
}
	
inline int 
Xfc::Gtk::Entry::text_index_to_layout_index(int text_index)
{
	return gtk_entry_text_index_to_layout_index(gtk_entry(), text_index);
}

inline void
Xfc::Gtk::Entry::set_visibility(bool visible)
{
	gtk_entry_set_visibility(gtk_entry(), visible);
}

inline void
Xfc::Gtk::Entry::set_has_frame(bool setting)
{
	gtk_entry_set_has_frame(gtk_entry(), setting);
}

inline void
Xfc::Gtk::Entry::set_max_length(int max)
{
	gtk_entry_set_max_length(gtk_entry(), max);
}

inline void
Xfc::Gtk::Entry::set_text(const char *text)
{
	gtk_entry_set_text(gtk_entry(), text);
}

inline void
Xfc::Gtk::Entry::set_activates_default(bool setting)
{
	gtk_entry_set_activates_default(gtk_entry(), setting);
}

inline void
Xfc::Gtk::Entry::set_width_chars(int n_chars)
{
	gtk_entry_set_width_chars(gtk_entry(), n_chars);
}

inline void 
Xfc::Gtk::Entry::set_alignment(float xalign)
{
	gtk_entry_set_alignment(gtk_entry(), xalign);
}

inline const Xfc::Gtk::Entry::PopulatePopupSignalProxy 
Xfc::Gtk::Entry::signal_populate_popup()
{
	return PopulatePopupSignalProxy(this, &populate_popup_signal);
}

inline const Xfc::Gtk::Entry::ActviateSignalProxy
Xfc::Gtk::Entry::signal_activate()
{
	return ActviateSignalProxy(this, &activate_signal);
}

inline const Xfc::Gtk::Entry::InsertAtCursorSignalProxy
Xfc::Gtk::Entry::signal_insert_at_cursor()
{
	return InsertAtCursorSignalProxy(this, &insert_at_cursor_signal);
}

