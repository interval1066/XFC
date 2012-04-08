/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treeviewclass.hh - Private interface
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

#ifndef XFC_GTK_TREE_VIEW_CLASS_HH
#define XFC_GTK_TREE_VIEW_CLASS_HH

#include <xfc/gtk/private/containerclass.hh>

namespace Xfc {

namespace Gtk {

class TreeViewClass
{
public:
	static void init(GtkTreeViewClass *g_class);

	static GtkTreeViewClass* get_parent_class(void *instance);

	static GType get_type();

	static void* create();

	static void set_scroll_adjustments_proxy(GtkTreeView *tree_view, GtkAdjustment *hadjustment, GtkAdjustment *vadjustment);

	static void row_activated_proxy(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column);

	static gboolean test_expand_row_proxy(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path);

	static gboolean test_collapse_row_proxy(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path);

	static void row_expanded_proxy(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path);

	static void row_collapsed_proxy(GtkTreeView *tree_view, GtkTreeIter *iter, GtkTreePath *path);

	static void columns_changed_proxy(GtkTreeView *tree_view);

	static void cursor_changed_proxy(GtkTreeView *tree_view);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TREE_VIEW_CLASS_HH

