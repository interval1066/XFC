/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treednd.cc - GtkTreeDragSource and GtkTreeDragDest C++ wrapper implementation
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
 
#include "treednd.hh"
#include "selection.hh"
#include "treemodel.hh"

using namespace Xfc;

/*  Gtk::TreeDragSource
 */

Gtk::TreeDragSource::TreeDragSource()
{
}

Gtk::TreeDragSource::~TreeDragSource()
{
}
	
bool 
Gtk::TreeDragSource::row_draggable(const TreePath& path) const
{
	return gtk_tree_drag_source_row_draggable(gtk_tree_drag_source(), path.gtk_tree_path());
}

bool 
Gtk::TreeDragSource::drag_data_delete(TreePath& path)
{
	return gtk_tree_drag_source_drag_data_delete(gtk_tree_drag_source(), path.gtk_tree_path());
}

bool 
Gtk::TreeDragSource::drag_data_get(const TreePath& path, SelectionData& data)
{
	return gtk_tree_drag_source_drag_data_get(gtk_tree_drag_source(), path.gtk_tree_path(), data.gtk_selection_data());
}

/*  Gtk::TreeDragDest
 */

Gtk::TreeDragDest::TreeDragDest()
{
}

Gtk::TreeDragDest::~TreeDragDest()
{
}
	
bool 
Gtk::TreeDragDest::row_drop_possible(const TreePath& dest_path, const SelectionData& data) const
{
	return gtk_tree_drag_dest_row_drop_possible(gtk_tree_drag_dest(), dest_path.gtk_tree_path(), data.gtk_selection_data());
}


bool 
Gtk::TreeDragDest::drag_data_received(const TreePath& dest, const SelectionData& data)
{
	return gtk_tree_drag_dest_drag_data_received(gtk_tree_drag_dest(), dest.gtk_tree_path(), data.gtk_selection_data());
}

