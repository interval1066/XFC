/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  table.inl - Gtk::Table inline functions
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

inline GtkTable*
Xfc::Gtk::Table::gtk_table() const
{
	return reinterpret_cast<GtkTable*>(instance_);
}

inline Xfc::Gtk::Table::operator GtkTable* () const
{
	return this ? gtk_table() : 0;
}

inline unsigned int
Xfc::Gtk::Table::get_row_spacing(unsigned int row) const
{
	return gtk_table_get_row_spacing(gtk_table(), row);
}


inline unsigned int
Xfc::Gtk::Table::get_column_spacing(unsigned int column) const
{
	return gtk_table_get_col_spacing(gtk_table(), column);
}

inline unsigned int
Xfc::Gtk::Table::get_default_row_spacing() const
{
	return gtk_table_get_default_row_spacing(gtk_table());
}

inline unsigned int
Xfc::Gtk::Table::get_default_col_spacing() const
{
	return gtk_table_get_default_col_spacing(gtk_table());
}

inline bool
Xfc::Gtk::Table::get_homogeneous() const
{
	return gtk_table_get_homogeneous(gtk_table());
}

inline void
Xfc::Gtk::Table::resize(unsigned int rows, unsigned int columns)
{
	gtk_table_resize(gtk_table(), rows, columns);
}

inline void
Xfc::Gtk::Table::set_row_spacing(unsigned int row, unsigned int spacing)
{
	gtk_table_set_row_spacing(gtk_table(), row, spacing);
}

inline void
Xfc::Gtk::Table::set_col_spacing(unsigned int column, unsigned int spacing)
{
	gtk_table_set_col_spacing(gtk_table(), column, spacing);
}

inline void
Xfc::Gtk::Table::set_row_spacings(unsigned int spacing)
{
	gtk_table_set_row_spacings(gtk_table(), spacing);
}

inline void
Xfc::Gtk::Table::set_col_spacings(unsigned int spacing)
{
	gtk_table_set_col_spacings(gtk_table(), spacing);
}

inline void
Xfc::Gtk::Table::set_homogeneous(bool homogeneous)
{
	gtk_table_set_homogeneous(gtk_table(), homogeneous);
}

