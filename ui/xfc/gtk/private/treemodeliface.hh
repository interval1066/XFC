/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treemodeliface.hh - Private interface
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

#ifndef XFC_GTK_TREE_MODEL_IFACE_HH
#define XFC_GTK_TREE_MODEL_IFACE_HH

namespace Xfc {

namespace Gtk {

class TreeModelIface
{
public:
	static void init(GtkTreeModelIface *g_iface);

	static GtkTreeModelIface* get_parent_iface(void *instance);

	static void row_changed_proxy(GtkTreeModel *tree_model, GtkTreePath *path, GtkTreeIter *iter);

	static void row_inserted_proxy(GtkTreeModel *tree_model, GtkTreePath *path, GtkTreeIter *iter);

	static void row_has_child_toggled_proxy(GtkTreeModel *tree_model, GtkTreePath *path, GtkTreeIter *iter);

	static void row_deleted_proxy(GtkTreeModel *tree_model, GtkTreePath *path);

	static void rows_reordered_proxy(GtkTreeModel *tree_model, GtkTreePath *path, GtkTreeIter *iter, gint *new_order);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TREE_MODEL_IFACE_HH

