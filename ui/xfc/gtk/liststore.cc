/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  liststore.cc - GtkListStore C++ wrapper implementation
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
 
#include "liststore.hh"
#include "private/liststoreclass.hh"
#include "private/treemodeliface.hh"
#include "private/treesortableiface.hh"
#include "xfc/glib/value.hh"

using namespace Xfc;

/*  Gtk::TreeRowValues
 */
 
Gtk::TreeRowValues::TreeRowValues()
{
}

Gtk::TreeRowValues::~TreeRowValues()
{
	clear();
}

GValue* 
Gtk::TreeRowValues::create_value(const G::Value& value) 
{
	GValue *tmp_value = g_new0(GValue, 1);	
	g_value_init(tmp_value, value.type());
	g_value_copy(value.g_value(), tmp_value);
	return tmp_value;
}
	
void 
Gtk::TreeRowValues::add(int column, const G::Value& value)
{
	gvalues_.push_back(create_value(value));	
	columns_.push_back(column);	
}		

void 
Gtk::TreeRowValues::add(int column, const char *str)
{
	GValue *tmp_value = g_new0(GValue, 1);	
	g_value_init(tmp_value, G_TYPE_STRING);
	g_value_set_string(tmp_value, str);
	gvalues_.push_back(tmp_value);	
	columns_.push_back(column);	
}

void 
Gtk::TreeRowValues::add(int column, const std::string& str)
{
	add(column, str.c_str());	
}

void 
Gtk::TreeRowValues::clear()
{
	unsigned int i = 0;
	while (i < gvalues_.size())
	{
		if (G_VALUE_TYPE(gvalues_[i]))	
			g_value_unset(gvalues_[i]);
		g_free(gvalues_[i]);
	}
	gvalues_.clear();
	columns_.clear();
}

/*  Gtk::ListStore
 */

Gtk::ListStore::ListStore()
: G::Object((GObject*)ListStoreClass::create())
{
}

Gtk::ListStore::ListStore(GtkListStore *list_store, bool owns_reference)
: G::Object((GObject*)list_store, owns_reference)
{
}

Gtk::ListStore::ListStore(int n_columns, ...)
: G::Object((GObject*)ListStoreClass::create())
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

Gtk::ListStore::ListStore(int n_columns, const GType *types)
: G::Object((GObject*)ListStoreClass::create())
{
	set_column_types(n_columns, types);
}

Gtk::ListStore::~ListStore()
{
}

void 
Gtk::ListStore::set_column_types(int n_columns, const GType *types)
{
	gtk_list_store_set_column_types(gtk_list_store(), n_columns, const_cast<GType*>(types));
}

bool
Gtk::ListStore::iter_is_valid(const TreeIter& iter) const
{
	return gtk_list_store_iter_is_valid(gtk_list_store(), iter.gtk_tree_iter());
}

Gtk::TreeIter
Gtk::ListStore::append()
{
	GtkTreeIter iter;
	gtk_list_store_append(gtk_list_store(), &iter);
	return TreeIter(&iter, true);
}

Gtk::TreeIter
Gtk::ListStore::prepend()
{
	GtkTreeIter iter;
	gtk_list_store_prepend(gtk_list_store(), &iter);
	return TreeIter(&iter, true);
}

Gtk::TreeIter
Gtk::ListStore::insert(int position)
{
	GtkTreeIter iter;
	gtk_list_store_insert(gtk_list_store(), &iter, position);
	return TreeIter(&iter, true);
}

Gtk::TreeIter
Gtk::ListStore::insert_before(TreeIter& sibling)
{
	GtkTreeIter iter;
	gtk_list_store_insert_before(gtk_list_store(), &iter, sibling.gtk_tree_iter());
	return TreeIter(&iter, true);
}

Gtk::TreeIter
Gtk::ListStore::insert_after(TreeIter& sibling)
{
	GtkTreeIter iter;
	gtk_list_store_insert_after(gtk_list_store(), &iter, sibling.gtk_tree_iter());
	return TreeIter(&iter, true);
}

Gtk::TreeIter 
Gtk::ListStore::insert_with_values(int position, const TreeRowValues& values)
{
	GtkTreeIter iter;
	gtk_list_store_insert_with_valuesv(gtk_list_store(), &iter, position, 
	                                   const_cast<int*>(values.columns()), 
	                                   const_cast<GValue*>(values.gvalues()),
					   values.size());
	return TreeIter(&iter, true);
}

bool
Gtk::ListStore::remove(TreeIter& iter)
{
	return gtk_list_store_remove(gtk_list_store(), iter.gtk_tree_iter());
}

void
Gtk::ListStore::swap(const TreeIter& a, const TreeIter& b)
{
	gtk_list_store_swap(gtk_list_store(), a.gtk_tree_iter(), b.gtk_tree_iter());
}

void 
Gtk::ListStore::move_after(const TreeIter& iter, const TreeIter *position)
{
	gtk_list_store_move_after(gtk_list_store(), iter.gtk_tree_iter(), *position);
}

void
Gtk::ListStore::move_before(const TreeIter& iter, const TreeIter *position)
{
	gtk_list_store_move_before(gtk_list_store(), iter.gtk_tree_iter(), *position);
}

void
Gtk::ListStore::set_value(const TreeIter& iter, int column, const G::Value& value)
{
	gtk_list_store_set_value(gtk_list_store(), iter.gtk_tree_iter(), column, value.g_value());
}

void
Gtk::ListStore::set_value(const TreeIter& iter, int column, const char *str)
{
	G::Value value(gtk_list_store()->column_headers[column]);
	value.set(String(str));
	gtk_list_store_set_value(gtk_list_store(), iter, column, value.g_value());
}

void
Gtk::ListStore::set_value(const TreeIter& iter, int column, const std::string& str)
{
	set_value(iter, column, str.c_str());
}

/*  Gtk::ListStoreClass
 */

void
Gtk::ListStoreClass::init(GtkListStoreClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::ListStoreClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_LIST_STORE, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_TREE_MODEL, (GInterfaceInitFunc)&TreeModelIface::init);
		G::TypeInstance::add_interface(type, GTK_TYPE_TREE_SORTABLE, (GInterfaceInitFunc)&TreeSortableIface::init);
	}
	return type;
}

void*
Gtk::ListStoreClass::create()
{
	return g_object_new(get_type(), 0);
}

