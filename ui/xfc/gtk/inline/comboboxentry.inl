/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  comboboxntry.inl - Gtk::ComboBoxEntry inline functions
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

/* Gtk::ComboBoxEntry
 */

inline GtkComboBoxEntry*
Xfc::Gtk::ComboBoxEntry::gtk_combo_box_entry() const
{
	return reinterpret_cast<GtkComboBoxEntry*>(instance_);
}

inline Xfc::Gtk::ComboBoxEntry::operator GtkComboBoxEntry* () const
{
	return this ? gtk_combo_box_entry() : 0;
}

inline int 
Xfc::Gtk::ComboBoxEntry::get_text_column() const
{
	return gtk_combo_box_entry_get_text_column(gtk_combo_box_entry());
}

inline void 
Xfc::Gtk::ComboBoxEntry::set_text_column(int text_column)
{
	gtk_combo_box_entry_set_text_column(gtk_combo_box_entry(), text_column);
}

/* Gtk::ComboBoxEntryText
 */

inline void 
Xfc::Gtk::ComboBoxEntryText::append(const char *text)
{
	gtk_combo_box_append_text(gtk_combo_box(), text);
}

inline void 
Xfc::Gtk::ComboBoxEntryText::prepend(const char *text)
{
	gtk_combo_box_prepend_text(gtk_combo_box(), text);
}

inline void 
Xfc::Gtk::ComboBoxEntryText::insert(int position, const char *text)
{
	gtk_combo_box_insert_text(gtk_combo_box(), position, text);
}

inline void 
Xfc::Gtk::ComboBoxEntryText::remove(int position)
{
	gtk_combo_box_remove_text(gtk_combo_box(), position);
}

