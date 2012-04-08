/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treestore.cc - GtkTreeStore C++ wrapper implementation
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
 
#include "treestore.hh"
#include "private/treestoreclass.hh"
#include "private/treemodeliface.hh"
#include "private/treesortableiface.hh"
#include "xfc/glib/value.hh"

using namespace Xfc;

/*  Gtk::TreeStore
 */

Gtk::TreeStore::TreeStore()
: G::Object((GObject*)TreeStoreClass::create())
{
}

Gtk::TreeStore::TreeStore(GtkTreeStore *tree_store, bool owns_reference)
: G::Object((GObject*)tree_store, owns_reference)
{
}

Gtk::TreeStore::TreeStore(int n_columns, ...)
: G::Object((GObject*)TreeStoreClass::create())
{
	g_return_if_fail(n_columns > 0);
	va_list args;
	va_start(args, n_columns);
	GType *types = new GType[n_columns];

	int i = 0;
	while (i < n_columns)
	{
		types[i] = va_arg(args, GType);
		++i;
	}

	set_column_types(n_columns, types);
	delete [] types;
	va_end(args);
}

Gtk::TreeStore::TreeStore(int n_columns, const GType *types)
: G::Object((GObject*)TreeStoreClass::create())
{
	set_column_types(n_columns, types);
}

Gtk::TreeStore::~TreeStore()
{
}
	
void 
Gtk::TreeStore::set_column_types(int n_columns, const GType *types)
{
	gtk_tree_store_set_column_types(gtk_tree_store(), n_columns, const_cast<GType*>(types));
}

bool
Gtk::TreeStore::is_ancestor(const TreeIter& iter, const TreeIter& descendant) const
{
	return gtk_tree_store_is_ancestor(gtk_tree_store(), iter.gtk_tree_iter(), descendant.gtk_tree_iter()) != 0;
}

int
Gtk::TreeStore::iter_depth(const TreeIter& iter) const
{
	return gtk_tree_store_iter_depth(gtk_tree_store(), iter.gtk_tree_iter());
}

bool
Gtk::TreeStore::iter_is_valid(const TreeIter& iter) const
{
	return gtk_tree_store_iter_is_valid(gtk_tree_store(), iter.gtk_tree_iter());
}

void
Gtk::TreeStore::set_value(const TreeIter& iter, int column, const G::Value& value)
{
	gtk_tree_store_set_value(gtk_tree_store(), iter.gtk_tree_iter(), column, value.g_value());
}

void
Gtk::TreeStore::set_value(const TreeIter& iter, int column, const char *str)
{
	G::Value value(gtk_tree_store()->column_headers[column]);
	value.set(String(str));
	gtk_tree_store_set_value(gtk_tree_store(), iter, column, value.g_value());
}

void
Gtk::TreeStore::set_value(const TreeIter& iter, int column, const std::string& str)
{
	set_value(iter, column, str.c_str());
}

Gtk::TreeIter
Gtk::TreeStore::append(TreeIter *parent)
{
	GtkTreeIter iter;
	gtk_tree_store_append(gtk_tree_store(), &iter, *parent);
	return TreeIter(&iter, true);
}

Gtk::TreeIter
Gtk::TreeStore::prepend(TreeIter *parent)
{
	GtkTreeIter iter;
	gtk_tree_store_prepend(gtk_tree_store(), &iter, *parent);
	return TreeIter(&iter, true);
}

Gtk::TreeIter
Gtk::TreeStore::insert(int position, TreeIter *parent)
{
	GtkTreeIter iter;
	gtk_tree_store_insert(gtk_tree_store(), &iter, *parent, position);
	return TreeIter(&iter, true);
}

Gtk::TreeIter
Gtk::TreeStore::insert_before(TreeIter& sibling, TreeIter *parent)
{
	GtkTreeIter iter;
	gtk_tree_store_insert_before(gtk_tree_store(), &iter, *parent, sibling.gtk_tree_iter());
	return TreeIter(&iter, true);
}

Gtk::TreeIter
Gtk::TreeStore::insert_after(TreeIter& sibling, TreeIter *parent)
{
	GtkTreeIter iter;
	gtk_tree_store_insert_after(gtk_tree_store(), &iter, *parent, sibling.gtk_tree_iter());
	return TreeIter(&iter, true);
}

bool
Gtk::TreeStore::remove(TreeIter& iter)
{
	return gtk_tree_store_remove(gtk_tree_store(), iter.gtk_tree_iter());
}

void 
Gtk::TreeStore::reorder(const TreeIter& parent, int *new_order)
{
	gtk_tree_store_reorder(gtk_tree_store(), parent.gtk_tree_iter(), new_order);
}

void
Gtk::TreeStore::swap(const TreeIter& a, const TreeIter& b)
{
	gtk_tree_store_swap(gtk_tree_store(), a.gtk_tree_iter(), b.gtk_tree_iter());
}

void 
Gtk::TreeStore::move_after(const TreeIter& iter, const TreeIter *position)
{
	gtk_tree_store_move_after(gtk_tree_store(), iter.gtk_tree_iter(), *position);
}

void 
Gtk::TreeStore::move_before(const TreeIter& iter, const TreeIter *position)
{
	gtk_tree_store_move_before(gtk_tree_store(), iter.gtk_tree_iter(), *position);
}

/*  Gtk::TreeStoreClass
 */

void
Gtk::TreeStoreClass::init(GtkTreeStoreClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::TreeStoreClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TREE_STORE, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_TREE_MODEL, (GInterfaceInitFunc)&TreeModelIface::init);
		G::TypeInstance::add_interface(type, GTK_TYPE_TREE_SORTABLE, (GInterfaceInitFunc)&TreeSortableIface::init);
	}
	return type;
}

void*
Gtk::TreeStoreClass::create()
{
	return g_object_new(get_type(), 0);
}

