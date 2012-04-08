/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  celleditable.inl - Gtk::CellEditable inline functions
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

inline GtkCellEditable*
Xfc::Gtk::CellEditable::gtk_cell_editable() const
{
	return reinterpret_cast<GtkCellEditable*>(instance_);
}

inline Xfc::Gtk::CellEditable::operator GtkCellEditable* () const
{
	return this ? gtk_cell_editable() : 0;
}

inline void
Xfc::Gtk::CellEditable::editing_done()
{
	gtk_cell_editable_editing_done(gtk_cell_editable());
}

inline void
Xfc::Gtk::CellEditable::remove_widget()
{
	gtk_cell_editable_remove_widget(gtk_cell_editable());
}

inline const Xfc::Gtk::CellEditable::EditingDoneSignalProxy
Xfc::Gtk::CellEditable::signal_editing_done()
{
	return EditingDoneSignalProxy(this, &editing_done_signal);
}

inline const Xfc::Gtk::CellEditable::RemoveWidgetSignalProxy
Xfc::Gtk::CellEditable::signal_remove_widget()
{
	return RemoveWidgetSignalProxy(this, &remove_widget_signal);
}

