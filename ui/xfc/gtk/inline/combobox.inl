/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  combobox.inl - Gtk::ComboBox inline functions
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

/* Gtk::ComboBox
 */

inline GtkComboBox*
Xfc::Gtk::ComboBox::gtk_combo_box() const
{
	return reinterpret_cast<GtkComboBox*>(instance_);
}

inline Xfc::Gtk::ComboBox::operator GtkComboBox* () const
{
	return this ? gtk_combo_box() : 0;
}

inline int 
Xfc::Gtk::ComboBox::get_wrap_width() const
{
	return gtk_combo_box_get_wrap_width(gtk_combo_box());
}

inline int
Xfc::Gtk::ComboBox::get_row_span_column() const
{
	return gtk_combo_box_get_row_span_column(gtk_combo_box());
}

inline int
Xfc::Gtk::ComboBox::get_column_span_column() const
{
	return gtk_combo_box_get_column_span_column(gtk_combo_box());
}

inline bool 
Xfc::Gtk::ComboBox::get_add_tearoffs() const
{
	return gtk_combo_box_get_add_tearoffs(gtk_combo_box());
}
	
inline bool 
Xfc::Gtk::ComboBox::get_focus_on_click() const
{
	return gtk_combo_box_get_focus_on_click(gtk_combo_box());
}

inline int 
Xfc::Gtk::ComboBox::get_active() const
{
	return gtk_combo_box_get_active(gtk_combo_box());
}

inline void 
Xfc::Gtk::ComboBox::set_wrap_width(int width)
{
	gtk_combo_box_set_wrap_width(gtk_combo_box(), width);
}

inline void 
Xfc::Gtk::ComboBox::set_row_span_column(int row_span)
{
	gtk_combo_box_set_row_span_column(gtk_combo_box(), row_span);
}
	
inline void 
Xfc::Gtk::ComboBox::set_column_span_column(int column_span)
{
	gtk_combo_box_set_column_span_column(gtk_combo_box(), column_span);
}

inline void 
Xfc::Gtk::ComboBox::set_add_tearoffs(bool add_tearoffs)
{
	gtk_combo_box_set_add_tearoffs(gtk_combo_box(), add_tearoffs);
}
	
inline void 
Xfc::Gtk::ComboBox::set_focus_on_click(bool focus_on_click)
{
	gtk_combo_box_set_focus_on_click(gtk_combo_box(), focus_on_click);
}

inline void 
Xfc::Gtk::ComboBox::set_active(int index)
{
	gtk_combo_box_set_active(gtk_combo_box(), index);
}

inline void 
Xfc::Gtk::ComboBox::popup()
{
	gtk_combo_box_popup(gtk_combo_box());
}
	
inline void 
Xfc::Gtk::ComboBox::popdown()
{
	gtk_combo_box_popdown(gtk_combo_box());
}

inline const Xfc::Gtk::ComboBox::ChangedSignalProxy
Xfc::Gtk::ComboBox::signal_changed()
{
	return ChangedSignalProxy(this, &changed_signal);
}

/* Gtk::ComboBoxText
 */

inline void 
Xfc::Gtk::ComboBoxText::append(const char *text)
{
	gtk_combo_box_append_text(gtk_combo_box(), text);
}

inline void 
Xfc::Gtk::ComboBoxText::prepend(const char *text)
{
	gtk_combo_box_prepend_text(gtk_combo_box(), text);
}

inline void 
Xfc::Gtk::ComboBoxText::insert(int position, const char *text)
{
	gtk_combo_box_insert_text(gtk_combo_box(), position, text);
}

inline void 
Xfc::Gtk::ComboBoxText::remove(int position)
{
	gtk_combo_box_remove_text(gtk_combo_box(), position);
}

