/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treemodelsort.cc - GtkTreeModelSort C++ wrapper implementation
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
 
#include "treemodelsort.hh"
#include "private/treemodelsortclass.hh"
#include "private/treemodeliface.hh"
#include "private/treesortableiface.hh"
#include "xfc/glib/private/objectclass.hh"

using namespace Xfc;

/*  Gtk::TreeModelSort
 */

Gtk::TreeModelSort::TreeModelSort(GtkTreeModelSort *tree_model, bool owns_reference)
: G::Object((GObject*)tree_model, owns_reference)
{
}
	
Gtk::TreeModelSort::TreeModelSort(TreeModel& child_model)
: G::Object((GObject*)TreeModelSortClass::create(child_model.gtk_tree_model()))
{
}

Gtk::TreeModelSort::~TreeModelSort()
{
}
	
Gtk::TreeModel*
Gtk::TreeModelSort::get_model() const
{
	GtkTreeModel *child_model = gtk_tree_model_sort_get_model(gtk_tree_model_sort());
	TreeModel *tmp_child_model = 0;
	if (child_model)
	{
		G::Object *object = G::Object::pointer((GObject*)child_model);
		tmp_child_model = dynamic_cast<Gtk::TreeModel*>(object);
	}
	return tmp_child_model;
}

bool
Gtk::TreeModelSort::iter_is_valid(const TreeIter& iter) const
{
	return gtk_tree_model_sort_iter_is_valid(gtk_tree_model_sort(), iter.gtk_tree_iter());
}

Pointer<Gtk::TreePath>
Gtk::TreeModelSort::convert_child_path_to_path(const TreePath& child_path)
{
	GtkTreePath *path = gtk_tree_model_sort_convert_child_path_to_path(gtk_tree_model_sort(), child_path.gtk_tree_path());
	return path ? G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, path, false) : 0;
}

Gtk::TreeIter
Gtk::TreeModelSort::convert_child_iter_to_iter(const TreeIter& child_iter)
{
	GtkTreeIter sort_iter;
	gtk_tree_model_sort_convert_child_iter_to_iter(gtk_tree_model_sort(), &sort_iter, child_iter.gtk_tree_iter());
	return TreeIter(&sort_iter, true);
}

Pointer<Gtk::TreePath>
Gtk::TreeModelSort::convert_path_to_child_path(const TreePath& sorted_path)
{
	GtkTreePath *path = gtk_tree_model_sort_convert_path_to_child_path(gtk_tree_model_sort(), sorted_path.gtk_tree_path());
	return path ? G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, path, false) : 0;
}

Gtk::TreeIter
Gtk::TreeModelSort::convert_iter_to_child_iter(const TreeIter& sorted_iter)
{
	GtkTreeIter child_iter;
	gtk_tree_model_sort_convert_iter_to_child_iter(gtk_tree_model_sort(), &child_iter, sorted_iter.gtk_tree_iter());
	return TreeIter(&child_iter, true);
}

/*  Gtk::TreeModelSortClass
 */

void
Gtk::TreeModelSortClass::init(GtkTreeModelSortClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::TreeModelSortClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TREE_MODEL_SORT, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_TREE_MODEL, (GInterfaceInitFunc)&TreeModelIface::init);
		G::TypeInstance::add_interface(type, GTK_TYPE_TREE_SORTABLE, (GInterfaceInitFunc)&TreeSortableIface::init);
	}
	return type;
}

void*
Gtk::TreeModelSortClass::create(GtkTreeModel *child_model)
{
	return g_object_new(get_type(), "model", child_model, 0);
}

