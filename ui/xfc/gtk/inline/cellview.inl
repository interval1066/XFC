/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  cellview.inl - Gtk::CellView inline functions
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

inline GtkCellView*
Xfc::Gtk::CellView::gtk_cell_view() const
{
	return reinterpret_cast<GtkCellView*>(instance_);
}

inline Xfc::Gtk::CellView::operator GtkCellView* () const
{
	return this ? gtk_cell_view() : 0;
}

inline const Xfc::Gtk::CellView::BackgroundPropertyProxy
Xfc::Gtk::CellView::property_background()
{
	return BackgroundPropertyProxy(this, &background_property);
}

inline const Xfc::Gtk::CellView::BackgroundGdkPropertyProxy
Xfc::Gtk::CellView::property_background_gdk()
{
	return BackgroundGdkPropertyProxy(this, &background_gdk_property);
}

inline const Xfc::Gtk::CellView::BackgroundSetPropertyProxy
Xfc::Gtk::CellView::property_background_set()
{
	return BackgroundSetPropertyProxy(this, &background_set_property);
}

