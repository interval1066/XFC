/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  cellrendererprogress.inl - Gtk::CellRendererProgress inline functions
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

inline GtkCellRendererProgress*
Xfc::Gtk::CellRendererProgress::gtk_cell_renderer_progress() const
{
	return reinterpret_cast<GtkCellRendererProgress*>(instance_);
}

inline Xfc::Gtk::CellRendererProgress::operator GtkCellRendererProgress* () const
{
	return this ? gtk_cell_renderer_progress() : 0;
}

inline const Xfc::Gtk::CellRendererProgress::ValuePropertyProxy
Xfc::Gtk::CellRendererProgress::property_value()
{
	return ValuePropertyProxy(this, &value_property);
}

inline const Xfc::Gtk::CellRendererProgress::TextPropertyProxy
Xfc::Gtk::CellRendererProgress::property_text()
{
	return TextPropertyProxy(this, &text_property);
}

