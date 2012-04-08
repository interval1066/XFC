/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treemodel.cc - GtkTreePath, GtkTreeIter, GtkTreeModel and GtkTreeRowReference C++ wrapper implementation
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
#include "selection.hh"
#include "private/marshal.hh"
#include "private/treemodeliface.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"
#include "xfc/glib/value.hh"

using namespace Xfc;

/*  Gtk::TreePath
 */
 
Gtk::TreePath::TreePath()
: G::Boxed(GTK_TYPE_TREE_PATH, gtk_tree_path_new(), false)
{
}

Gtk::TreePath::TreePath(const char *path)
: G::Boxed(GTK_TYPE_TREE_PATH, path ? gtk_tree_path_new_from_string(path) : gtk_tree_path_new_first(), false)
{
	if (!path)
		append_index(0);
}

Gtk::TreePath::TreePath(const String& path)
: G::Boxed(GTK_TYPE_TREE_PATH, gtk_tree_path_new_from_string(path.c_str()), false)
{
	if (path.null())
		append_index(0);
}

Gtk::TreePath::TreePath(int first_index, ...)
: G::Boxed(GTK_TYPE_TREE_PATH, gtk_tree_path_new(), false)
{
	va_list args;
	va_start(args, first_index);
	int arg = first_index;

	while (arg != -1)
	{
		append_index(arg);
		arg = va_arg(args, int);
	}

	va_end(args);
}

Gtk::TreePath::TreePath(GtkTreePath *path)
: G::Boxed(GTK_TYPE_TREE_PATH, path)
{
}

Gtk::TreePath::TreePath(GtkTreePath *path, bool copy)
: G::Boxed(GTK_TYPE_TREE_PATH, path, copy)
{
}

Gtk::TreePath::TreePath(const TreePath& src)
: G::Boxed(GTK_TYPE_TREE_PATH, src.g_boxed(), true)
{
}

Gtk::TreePath::~TreePath()
{
}

Gtk::TreePath&
Gtk::TreePath::operator=(const TreePath& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

String
Gtk::TreePath::to_string() const
{
	char *tmp_path = gtk_tree_path_to_string(gtk_tree_path());
	String path(tmp_path);
	g_free(tmp_path);
	return path;
}

std::vector<int>
Gtk::TreePath::get_indices() const
{
	std::vector<int> indices;
	int *tmp_indices = gtk_tree_path_get_indices(gtk_tree_path());
	int count = gtk_tree_path_get_depth(gtk_tree_path());

	int i = 0;
	while (i < count)
	{
		indices.push_back(tmp_indices[i]);
		++i;
	}
	return indices;
}
	
int
Gtk::TreePath::compare(const TreePath& other) const
{
	return gtk_tree_path_compare(gtk_tree_path(), other.gtk_tree_path());
}

bool 
Gtk::TreePath::is_ancestor(const TreePath& descendant) const
{
	return gtk_tree_path_is_ancestor(gtk_tree_path(), descendant.gtk_tree_path());
}

bool 
Gtk::TreePath::is_descendant(const TreePath& ancestor) const
{
 	return gtk_tree_path_is_descendant(gtk_tree_path(), ancestor.gtk_tree_path());
}

bool 
Gtk::TreePath::operator==(const TreePath& other) const
{
	return compare(other) == 0;
}

bool 
Gtk::TreePath::operator!=(const TreePath& other) const
{
	return compare(other);
}
	
bool 
Gtk::TreePath::operator<(const TreePath& other) const
{
	return compare(other) > 0;
}
	
bool 
Gtk::TreePath::operator>(const TreePath& other) const
{
	return compare(other) < 0;
}
	
/*  Gtk::TreeIter
 */

Gtk::TreeIter::TreeIter()
: G::Boxed(GTK_TYPE_TREE_ITER)
{
	GtkTreeIter iter = { 0, };
	copy(&iter);
}

Gtk::TreeIter::TreeIter(GtkTreeIter *iter)
: G::Boxed(GTK_TYPE_TREE_ITER, iter)
{
}

Gtk::TreeIter::TreeIter(GtkTreeIter *iter, bool copy)
: G::Boxed(GTK_TYPE_TREE_ITER, iter, copy)
{
}

Gtk::TreeIter::TreeIter(const TreeIter& src)
: G::Boxed(GTK_TYPE_TREE_ITER, src.g_boxed(), true)
{
}

Gtk::TreeIter::~TreeIter()
{
}

Gtk::TreeIter&
Gtk::TreeIter::operator=(const TreeIter& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

/*  Gtk::TreeModel
 */

Gtk::TreeModel::TreeModel()
{
}

Gtk::TreeModel::~TreeModel()
{
}

bool
Gtk::TreeModel::get_iter(TreeIter& iter, const TreePath& path) const
{
	return gtk_tree_model_get_iter(gtk_tree_model(), iter.gtk_tree_iter(), path.gtk_tree_path());
}

bool
Gtk::TreeModel::get_iter(TreeIter& iter, const char *path) const
{
	return gtk_tree_model_get_iter_from_string(gtk_tree_model(), iter.gtk_tree_iter(), path);
}

bool
Gtk::TreeModel::get_iter(TreeIter& iter, const String& path) const
{
	return gtk_tree_model_get_iter_from_string(gtk_tree_model(), iter.gtk_tree_iter(), path.c_str());
}

String
Gtk::TreeModel::get_string_from_iter(const TreeIter& iter) const
{
	char *tmp =  gtk_tree_model_get_string_from_iter(gtk_tree_model(), iter.gtk_tree_iter());
	String s(tmp);
	g_free(tmp);
	return s;
}

bool
Gtk::TreeModel::get_iter_first(TreeIter& iter) const
{
	return gtk_tree_model_get_iter_first(gtk_tree_model(), iter.gtk_tree_iter());
}

Pointer<Gtk::TreePath>
Gtk::TreeModel::get_path(const TreeIter& iter) const
{
	return G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, gtk_tree_model_get_path(gtk_tree_model(), iter.gtk_tree_iter()), false);
}

void
Gtk::TreeModel::get_value(const TreeIter& iter, int column, G::Value& value) const
{
	gtk_tree_model_get_value(gtk_tree_model(), iter.gtk_tree_iter(), column, value.g_value());
}

String
Gtk::TreeModel::get_value(const TreeIter& iter, int column) const
{
	String s;
	get_value(iter, column, s);
	return s;
}

bool
Gtk::TreeModel::get_value(const TreeIter& iter, int column, String& str) const
{
	G::Value value;
	gtk_tree_model_get_value(gtk_tree_model(), iter.gtk_tree_iter(), column, value.g_value());
	return value.get(str);
}

bool
Gtk::TreeModel::get_value(const TreeIter& iter, int column, std::string& str) const
{
	String s;
	bool result = get_value(iter, column, s);
	str.assign(s.str());	
	return result;
}

bool
Gtk::TreeModel::iter_has_child(const TreeIter& iter) const
{
	return gtk_tree_model_iter_has_child(gtk_tree_model(), iter.gtk_tree_iter());
}

bool
Gtk::TreeModel::iter_next(TreeIter& iter)
{
	return gtk_tree_model_iter_next(gtk_tree_model(), iter.gtk_tree_iter());
}

bool
Gtk::TreeModel::iter_children(TreeIter& iter, const TreeIter *parent)
{
	return gtk_tree_model_iter_children(gtk_tree_model(), iter.gtk_tree_iter(), *parent);
}

int
Gtk::TreeModel::iter_n_children(const TreeIter *iter)
{
	return gtk_tree_model_iter_n_children(gtk_tree_model(), *iter);
}

bool
Gtk::TreeModel::iter_nth_child(TreeIter& iter, const TreeIter *parent, int n)
{
	return gtk_tree_model_iter_nth_child(gtk_tree_model(), iter.gtk_tree_iter(), *parent, n);
}

bool
Gtk::TreeModel::iter_parent(TreeIter& iter, const TreeIter& child)
{
	return gtk_tree_model_iter_parent(gtk_tree_model(), iter.gtk_tree_iter(), child.gtk_tree_iter());
}

void
Gtk::TreeModel::ref_node(TreeIter *iter)
{
	gtk_tree_model_ref_node(gtk_tree_model(), *iter);
}

void
Gtk::TreeModel::unref_node(TreeIter *iter)
{
	gtk_tree_model_unref_node(gtk_tree_model(), *iter);
}

namespace { // ForeachSlot callback

gboolean foreach_slot_callback(GtkTreeModel*, GtkTreePath *path, GtkTreeIter *iter, gpointer data)
{
	Gtk::TreeModel::ForeachSlot& slot = *static_cast<Gtk::TreeModel::ForeachSlot*>(data);
	Gtk::TreePath tmp_path(path);
	Gtk::TreeIter tmp_iter(iter);
	return slot(tmp_path, tmp_iter);
}

} // namespace

void
Gtk::TreeModel::foreach(const ForeachSlot& each)
{
	ForeachSlot tmp_each(each);
	gtk_tree_model_foreach(gtk_tree_model(), &foreach_slot_callback, &tmp_each);
}

void
Gtk::TreeModel::row_changed(const TreePath& path, const TreeIter& iter)
{
	gtk_tree_model_row_changed(gtk_tree_model(), path.gtk_tree_path(), iter.gtk_tree_iter());
}

void
Gtk::TreeModel::row_inserted(const TreePath& path, const TreeIter& iter)
{
	gtk_tree_model_row_inserted(gtk_tree_model(), path.gtk_tree_path(), iter.gtk_tree_iter());
}

void
Gtk::TreeModel::row_has_child_toggled(const TreePath& path, const TreeIter& iter)
{
	gtk_tree_model_row_has_child_toggled(gtk_tree_model(), path.gtk_tree_path(), iter.gtk_tree_iter());
}

void
Gtk::TreeModel::row_deleted(const TreePath& path)
{
	gtk_tree_model_row_deleted(gtk_tree_model(), path.gtk_tree_path());
}

void
Gtk::TreeModel::rows_reordered(const TreePath& path, const TreeIter& iter, int *new_order)
{
	gtk_tree_model_rows_reordered(gtk_tree_model(), path.gtk_tree_path(), iter.gtk_tree_iter(), new_order);
}

/*  Gtk::TreeModelIface
 */

void
Gtk::TreeModelIface::init(GtkTreeModelIface *g_iface)
{
	g_iface->row_changed = &row_changed_proxy;
	g_iface->row_inserted = &row_inserted_proxy;
	g_iface->row_has_child_toggled = &row_has_child_toggled_proxy;
	g_iface->row_deleted = &row_deleted_proxy;
	g_iface->rows_reordered = &rows_reordered_proxy;
}

GtkTreeModelIface*
Gtk::TreeModelIface::get_parent_iface(void *instance)
{
	return static_cast<GtkTreeModelIface*>(g_type_interface_peek_parent(GTK_TREE_MODEL_GET_IFACE(instance)));
}

void
Gtk::TreeModelIface::row_changed_proxy(GtkTreeModel *tree_model, GtkTreePath *path, GtkTreeIter *iter)
{
	TreeModelSignals *signals = dynamic_cast<TreeModelSignals*>(G::ObjectSignals::pointer((GObject*)tree_model));
	if (signals)
	{
		TreePath tmp_path(path);
		TreeIter tmp_iter(iter);
		signals->on_row_changed(tmp_path, tmp_iter);
	}
	else
	{
		GtkTreeModelIface *g_iface = get_parent_iface(tree_model);
		if (g_iface && g_iface->row_changed)
			g_iface->row_changed(tree_model, path, iter);
	}
}

void
Gtk::TreeModelIface::row_inserted_proxy(GtkTreeModel *tree_model, GtkTreePath *path, GtkTreeIter *iter)
{
	TreeModelSignals *signals = dynamic_cast<TreeModelSignals*>(G::ObjectSignals::pointer((GObject*)tree_model));
	if (signals)
	{
		TreePath tmp_path(path);
		TreeIter tmp_iter(iter);
		signals->on_row_inserted(tmp_path, tmp_iter);
	}
	else
	{
		GtkTreeModelIface *g_iface = get_parent_iface(tree_model);
		if (g_iface && g_iface->row_inserted)
			g_iface->row_inserted(tree_model, path, iter);
	}
}

void
Gtk::TreeModelIface::row_has_child_toggled_proxy(GtkTreeModel *tree_model, GtkTreePath *path, GtkTreeIter *iter)
{
	TreeModelSignals *signals = dynamic_cast<TreeModelSignals*>(G::ObjectSignals::pointer((GObject*)tree_model));
	if (signals)
	{
		TreePath tmp_path(path);
		TreeIter tmp_iter(iter);
		signals->on_row_has_child_toggled(tmp_path, tmp_iter);
	}
	else
	{
		GtkTreeModelIface *g_iface = get_parent_iface(tree_model);
		if (g_iface && g_iface->row_has_child_toggled)
			g_iface->row_has_child_toggled(tree_model, path, iter);
	}
}

void
Gtk::TreeModelIface::row_deleted_proxy(GtkTreeModel *tree_model, GtkTreePath *path)
{
	TreeModelSignals *signals = dynamic_cast<TreeModelSignals*>(G::ObjectSignals::pointer((GObject*)tree_model));
	if (signals)
	{
		TreePath tmp_path(path);
		signals->on_row_deleted(tmp_path);
	}
	else
	{
		GtkTreeModelIface *g_iface = get_parent_iface(tree_model);
		if (g_iface && g_iface->row_deleted)
			g_iface->row_deleted(tree_model, path);
	}
}

void
Gtk::TreeModelIface::rows_reordered_proxy(GtkTreeModel *tree_model, GtkTreePath *path, GtkTreeIter *iter, gint *new_order)
{
	TreeModelSignals *signals = dynamic_cast<TreeModelSignals*>(G::ObjectSignals::pointer((GObject*)tree_model));
	if (signals)
	{
		TreePath tmp_path(path);
		TreeIter tmp_iter(iter);
		signals->on_rows_reordered(tmp_path, tmp_iter, new_order);
	}
	else
	{
		GtkTreeModelIface *g_iface = get_parent_iface(tree_model);
		if (g_iface && g_iface->rows_reordered)
			g_iface->rows_reordered(tree_model, path, iter, new_order);
	}
}

/*  Gtk::TreeModel signals
 */

const Gtk::TreeModel::RowChangedSignalType Gtk::TreeModel::row_changed_signal("row_changed", (GCallback)&Marshal::void_treepath_treeiter_callback);

const Gtk::TreeModel::RowInsertedSignalType Gtk::TreeModel::row_inserted_signal("row_inserted", (GCallback)&Marshal::void_treepath_treeiter_callback);

const Gtk::TreeModel::RowHasChildToggledSignalType Gtk::TreeModel::row_has_child_toggled_signal("row_has_child_toggled", (GCallback)&Marshal::void_treepath_treeiter_callback);

const Gtk::TreeModel::RowDeletedSignalType Gtk::TreeModel::row_deleted_signal("row_deleted", (GCallback)&Marshal::void_treepath_callback);

const Gtk::TreeModel::RowsReorderedSignalType Gtk::TreeModel::rows_reordered_signal("rows_reordered", (GCallback)&Marshal::void_treepath_treeiter_pint_callback);

/*  Gtk::TreeRowReference
 */

Gtk::TreeRowReference::TreeRowReference(TreeModel& model, const TreePath& path)
: G::Boxed(GTK_TYPE_TREE_ROW_REFERENCE, gtk_tree_row_reference_new(model.gtk_tree_model(), path.gtk_tree_path()), false)
{
}

Gtk::TreeRowReference::TreeRowReference(G::Object& proxy, TreeModel& model, const TreePath& path)
: G::Boxed(GTK_TYPE_TREE_ROW_REFERENCE, gtk_tree_row_reference_new_proxy(proxy.g_object(), model.gtk_tree_model(), path.gtk_tree_path()), false)
{
}

Gtk::TreeRowReference::TreeRowReference(GtkTreeRowReference *reference)
: G::Boxed(GTK_TYPE_TREE_ROW_REFERENCE, reference)
{
}

Gtk::TreeRowReference::TreeRowReference(GtkTreeRowReference *reference, bool copy)
: G::Boxed(GTK_TYPE_TREE_ROW_REFERENCE, reference, copy)
{
}

Gtk::TreeRowReference::TreeRowReference(const TreeRowReference& src)
: G::Boxed(GTK_TYPE_TREE_ROW_REFERENCE, src.g_boxed(), true)
{
}

Gtk::TreeRowReference::~TreeRowReference()
{
}

Gtk::TreeRowReference&
Gtk::TreeRowReference::operator=(const TreeRowReference& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

Pointer<Gtk::TreePath>
Gtk::TreeRowReference::get_path() const
{
	return G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, gtk_tree_row_reference_get_path(gtk_tree_row_reference()), false);
}

void
Gtk::TreeRowReference::inserted(const G::Object& proxy, const TreePath& path)
{
	gtk_tree_row_reference_inserted(proxy.g_object(), path.gtk_tree_path());
}

void
Gtk::TreeRowReference::deleted(const G::Object& proxy, const TreePath& path)
{
	gtk_tree_row_reference_deleted(proxy.g_object(), path.gtk_tree_path());
}

void
Gtk::TreeRowReference::reordered(const G::Object& proxy, const TreePath& path, const TreeIter& iter, int *new_order)
{
	gtk_tree_row_reference_reordered(proxy.g_object(), path.gtk_tree_path(), iter.gtk_tree_iter(), new_order);
}

