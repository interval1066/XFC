/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treedndinl - Gtk::TreeDragSource and Gtk::TreeDragDest inline functions
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

/*  Gtk::TreeDragSource
 */

inline GtkTreeDragSource*
Xfc::Gtk::TreeDragSource::gtk_tree_drag_source() const
{
	return reinterpret_cast<GtkTreeDragSource*>(instance_);
}

inline Xfc::Gtk::TreeDragSource::operator GtkTreeDragSource* () const
{
	return this ? gtk_tree_drag_source() : 0;
}

/*  Gtk::TreeDragDest
 */

inline GtkTreeDragDest*
Xfc::Gtk::TreeDragDest::gtk_tree_drag_dest() const
{
	return reinterpret_cast<GtkTreeDragDest*>(instance_);
}

inline Xfc::Gtk::TreeDragDest::operator GtkTreeDragDest* () const
{
	return this ? gtk_tree_drag_dest() : 0;
}

