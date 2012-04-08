/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  celllayout.inl - Gtk::CellLayout inline functions
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

/*  Gtk::CellColumnAttributes
 */

inline const std::vector<int>& 
Xfc::Gtk::CellColumnAttributes::get_columns() const
{
	return columns_;
}

inline int 
Xfc::Gtk::CellColumnAttributes::size() const
{
	return attributes_.size();
}

inline bool 
Xfc::Gtk::CellColumnAttributes::empty() const
{
	return attributes_.empty(); 	
}

/*  Gtk::CellLayout
 */

inline GtkCellLayout*
Xfc::Gtk::CellLayout::gtk_cell_layout() const
{
	return reinterpret_cast<GtkCellLayout*>(instance_);
}

inline Xfc::Gtk::CellLayout::operator GtkCellLayout* () const
{
	return this ? gtk_cell_layout() : 0;
}

inline void 
Xfc::Gtk::CellLayout::clear()
{
	gtk_cell_layout_clear(gtk_cell_layout());
}

