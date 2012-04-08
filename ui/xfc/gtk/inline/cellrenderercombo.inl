/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  cellrenderercombo.inl - Gtk::CellRendererCombo inline functions
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

inline GtkCellRendererCombo*
Xfc::Gtk::CellRendererCombo::gtk_cell_renderer_combo() const
{
	return reinterpret_cast<GtkCellRendererCombo*>(instance_);
}

inline Xfc::Gtk::CellRendererCombo::operator GtkCellRendererCombo* () const
{
	return this ? gtk_cell_renderer_combo() : 0;
}

inline const Xfc::Gtk::CellRendererCombo::ModelPropertyProxy
Xfc::Gtk::CellRendererCombo::property_model()
{
	return ModelPropertyProxy(this, &model_property);
}

inline const Xfc::Gtk::CellRendererCombo::TextColumnPropertyProxy
Xfc::Gtk::CellRendererCombo::property_text_column()
{
	return TextColumnPropertyProxy(this, &text_column_property);
}

inline const Xfc::Gtk::CellRendererCombo::HasEntryPropertyProxy
Xfc::Gtk::CellRendererCombo::property_has_entry()
{
	return HasEntryPropertyProxy(this, &has_entry_property);
}

