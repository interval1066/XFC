/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treeviewsignals.cc - Gtk::TreeView virtual signal handlers
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
 
#include "treeview.hh"
#include "treeviewsignals.hh"
#include "treemodel.hh"
#include "private/treeviewclass.hh"

using namespace Xfc;

/*  Gtk::TreeeViewSignals
 */

Gtk::TreeViewSignals::TreeViewSignals(TreeView *tree_view)
: ContainerSignals(tree_view)
{
}

Gtk::TreeViewSignals::~TreeViewSignals() 
{
}

void
Gtk::TreeViewSignals::on_set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment)
{
	GtkTreeViewClass *g_class = TreeViewClass::get_parent_class(instance_);
	if (g_class && g_class->set_scroll_adjustments)
		g_class->set_scroll_adjustments((GtkTreeView*)instance_, *hadjustment, *vadjustment);
}

void
Gtk::TreeViewSignals::on_row_activated(const TreePath& path, TreeViewColumn& column)
{
	GtkTreeViewClass *g_class = TreeViewClass::get_parent_class(instance_);
	if (g_class && g_class->row_activated)
		g_class->row_activated((GtkTreeView*)instance_, path.gtk_tree_path(), column.gtk_tree_view_column());
}

bool
Gtk::TreeViewSignals::on_test_expand_row(const TreeIter& iter, const TreePath& path)
{
	bool result = false;
	GtkTreeViewClass *g_class = TreeViewClass::get_parent_class(instance_);
	if (g_class && g_class->test_expand_row)
		result = g_class->test_expand_row((GtkTreeView*)instance_, iter.gtk_tree_iter(), path.gtk_tree_path());
	return result;
}

bool
Gtk::TreeViewSignals::on_test_collapse_row(const TreeIter& iter, const TreePath& path)
{
	bool result = false;
	GtkTreeViewClass *g_class = TreeViewClass::get_parent_class(instance_);
	if (g_class && g_class->test_collapse_row)
		result = g_class->test_collapse_row((GtkTreeView*)instance_, iter.gtk_tree_iter(), path.gtk_tree_path());
	return result;
}

void
Gtk::TreeViewSignals::on_row_expanded(const TreeIter& iter, const TreePath& path)
{
	GtkTreeViewClass *g_class = TreeViewClass::get_parent_class(instance_);
	if (g_class && g_class->row_expanded)
		g_class->row_expanded((GtkTreeView*)instance_, iter.gtk_tree_iter(), path.gtk_tree_path());
}

void
Gtk::TreeViewSignals::on_row_collapsed(const TreeIter& iter, const TreePath& path)
{
	GtkTreeViewClass *g_class = TreeViewClass::get_parent_class(instance_);
	if (g_class && g_class->row_collapsed)
		g_class->row_collapsed((GtkTreeView*)instance_, iter.gtk_tree_iter(), path.gtk_tree_path());
}

void
Gtk::TreeViewSignals::on_columns_changed()
{
	GtkTreeViewClass *g_class = TreeViewClass::get_parent_class(instance_);
	if (g_class && g_class->columns_changed)
		g_class->columns_changed((GtkTreeView*)instance_);
}

void
Gtk::TreeViewSignals::on_cursor_changed()
{
	GtkTreeViewClass *g_class = TreeViewClass::get_parent_class(instance_);
	if (g_class && g_class->cursor_changed)
		g_class->cursor_changed((GtkTreeView*)instance_);
}

