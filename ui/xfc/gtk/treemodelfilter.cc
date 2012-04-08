/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treemodelfilter.cc - GtkTreeModelFilter C++ wrapper implementation
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
 
#include "treemodelfilter.hh"
#include "treemodel.hh"
#include "private/treemodelfilterclass.hh"
#include "private/treemodeliface.hh"
#include "xfc/glib/private/objectclass.hh"
#include "xfc/glib/value.hh"

using namespace Xfc;

/*  Gtk::TreeModelFilter
 */

Gtk::TreeModelFilter::TreeModelFilter(GtkTreeModelFilter *filter, bool owns_reference)
: G::Object((GObject*)filter, owns_reference)
{
}
	
Gtk::TreeModelFilter::TreeModelFilter(TreeModel& child_model, const TreePath *root)
: G::Object((GObject*)TreeModelFilterClass::create(child_model.gtk_tree_model(), *root))
{
}

Gtk::TreeModelFilter::~TreeModelFilter()
{
}
	
Gtk::TreeModel*
Gtk::TreeModelFilter::get_model() const
{
	GtkTreeModel *child_model = gtk_tree_model_filter_get_model(gtk_tree_model_filter());
	TreeModel *tmp_child_model = 0;
	if (child_model)
	{
		G::Object *object = G::Object::pointer((GObject*)child_model);
		tmp_child_model = dynamic_cast<Gtk::TreeModel*>(object);
	}
	return tmp_child_model;
}

namespace { // VisibleCallback

struct VisibleCallback
{
	typedef Gtk::TreeModelFilter::VisibleSlot VisibleSlot;
	VisibleSlot slot_;

	VisibleCallback(const VisibleSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(GtkTreeModel *model, GtkTreeIter *iter, void *data)
	{
		VisibleCallback *cb = static_cast<VisibleCallback*>(data);
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(iter);
		return cb->slot_(*tmp_model, tmp_iter);
	}

	static void destroy(void *data)
	{
		VisibleCallback *cb = static_cast<VisibleCallback*>(data);
		delete cb;
	}
};

} // namespace

void 
Gtk::TreeModelFilter::set_visible_func(const VisibleSlot& slot)
{
	VisibleCallback *cb = new VisibleCallback(slot);
	gtk_tree_model_filter_set_visible_func(gtk_tree_model_filter(), &VisibleCallback::notify, cb, &VisibleCallback::destroy);
}

namespace { // ModifyCallback

struct ModifyCallback
{
	typedef Gtk::TreeModelFilter::ModifySlot ModifySlot;
	ModifySlot slot_;

	ModifyCallback(const ModifySlot& slot)
	: slot_(slot)
	{
	}

	static void notify(GtkTreeModel *model, GtkTreeIter *iter, GValue *value, int column, void *data)
	{
		ModifyCallback *cb = static_cast<ModifyCallback*>(data);
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(iter);
		G::Value tmp_value(value);
		return cb->slot_(*tmp_model, tmp_iter, tmp_value, column);
	}

	static void destroy(void *data)
	{
		ModifyCallback *cb = static_cast<ModifyCallback*>(data);
		delete cb;
	}
};

} // namespace

void 
Gtk::TreeModelFilter::set_modify_func(int n_columns, const GType types[], const ModifySlot& slot)
{
	ModifyCallback *cb = new ModifyCallback(slot);
	gtk_tree_model_filter_set_modify_func(gtk_tree_model_filter(), n_columns, const_cast<GType*>(types), 
	                                      &ModifyCallback::notify, cb, &ModifyCallback::destroy);
}
	
Gtk::TreeIter 
Gtk::TreeModelFilter::convert_child_iter_to_iter(const TreeIter& child_iter)
{
	GtkTreeIter filter_iter;
	gtk_tree_model_filter_convert_child_iter_to_iter(gtk_tree_model_filter(), &filter_iter, child_iter.gtk_tree_iter());
	return TreeIter(&filter_iter, true);
}
 
Gtk::TreeIter 
Gtk::TreeModelFilter::convert_iter_to_child_iter(const TreeIter& filter_iter)
{
	GtkTreeIter child_iter;
	gtk_tree_model_filter_convert_iter_to_child_iter(gtk_tree_model_filter(), &child_iter, filter_iter.gtk_tree_iter());
	return TreeIter(&child_iter, true);
}
	
Pointer<Gtk::TreePath> 
Gtk::TreeModelFilter::convert_child_path_to_path(const TreePath& child_path)
{
	GtkTreePath *path = gtk_tree_model_filter_convert_child_path_to_path(gtk_tree_model_filter(), child_path.gtk_tree_path());
	return path ? G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, path, false) : 0;
}

Pointer<Gtk::TreePath> 
Gtk::TreeModelFilter::convert_path_to_child_path(const TreePath& filter_path)
{
	GtkTreePath *path = gtk_tree_model_filter_convert_path_to_child_path(gtk_tree_model_filter(), filter_path.gtk_tree_path());
	return path ? G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, path, false) : 0;
}

/*  Gtk::TreeModelFilterClass
 */

void
Gtk::TreeModelFilterClass::init(GtkTreeModelFilterClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::TreeModelFilterClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TREE_MODEL_FILTER, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_TREE_MODEL, (GInterfaceInitFunc)&TreeModelIface::init);
	}
	return type;
}

void*
Gtk::TreeModelFilterClass::create(GtkTreeModel *child_model, GtkTreePath *root)
{
	return g_object_new(get_type(), "child_model", child_model, "virtual_root", root, 0);
}

