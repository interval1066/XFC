/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treemodelsignals.cc - Gtk::TreeModel virtual signal handlers
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
 
#include "treemodel.hh"
#include "treemodelsignals.hh"
#include "private/treemodeliface.hh"

using namespace Xfc;

/*  Gtk::TreeModelSignals
 */

Gtk::TreeModelSignals::~TreeModelSignals()
{
}

void
Gtk::TreeModelSignals::on_row_changed(const TreePath& path, const TreeIter& iter)
{
	GtkTreeModelIface *g_iface = TreeModelIface::get_parent_iface(instance_);
	if (g_iface && g_iface->row_changed)
		g_iface->row_changed((GtkTreeModel*)instance_, path.gtk_tree_path(), iter.gtk_tree_iter());
}

void
Gtk::TreeModelSignals::on_row_inserted(const TreePath& path, const TreeIter& iter)
{
	GtkTreeModelIface *g_iface = TreeModelIface::get_parent_iface(instance_);
	if (g_iface && g_iface->row_inserted)
		g_iface->row_inserted((GtkTreeModel*)instance_, path.gtk_tree_path(), iter.gtk_tree_iter());
}

void
Gtk::TreeModelSignals::on_row_has_child_toggled(const TreePath& path, const TreeIter& iter)
{
	GtkTreeModelIface *g_iface = TreeModelIface::get_parent_iface(instance_);
	if (g_iface && g_iface->row_has_child_toggled)
		g_iface->row_has_child_toggled((GtkTreeModel*)instance_, path.gtk_tree_path(), iter.gtk_tree_iter());
}

void
Gtk::TreeModelSignals::on_row_deleted(const TreePath& path)
{
	GtkTreeModelIface *g_iface = TreeModelIface::get_parent_iface(instance_);
	if (g_iface && g_iface->row_deleted)
		g_iface->row_deleted((GtkTreeModel*)instance_, path.gtk_tree_path());
}

void
Gtk::TreeModelSignals::on_rows_reordered(const TreePath& path, const TreeIter& iter, int *new_order)
{
	GtkTreeModelIface *g_iface = TreeModelIface::get_parent_iface(instance_);
	if (g_iface && g_iface->rows_reordered)
		g_iface->rows_reordered((GtkTreeModel*)instance_, path.gtk_tree_path(), iter.gtk_tree_iter(), new_order);
}

