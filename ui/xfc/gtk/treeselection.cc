/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treeselection.cc - GtkTreeSelection C++ wrapper implementation
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
#include "private/marshal.hh"
#include "treemodel.hh"

using namespace Xfc;

/*  Gtk::TreeSelection
 */

Gtk::TreeSelection::TreeSelection(GtkTreeSelection *tree_selection, bool owns_reference)
: G::Object((GObject*)tree_selection, owns_reference)
{
}

Gtk::TreeSelection::~TreeSelection()
{
}
	
Gtk::TreeView*
Gtk::TreeSelection::get_tree_view() const
{
	GtkTreeView *tree_view = gtk_tree_selection_get_tree_view(gtk_tree_selection());
	return static_cast<TreeView*>(G::Object::pointer((GObject*)tree_view));
}

bool
Gtk::TreeSelection::get_selected(TreeIter *iter, TreeModel **model) const
{
	GType type = gtk_tree_selection()->type;
	g_return_val_if_fail(type == GTK_SELECTION_SINGLE || type == GTK_SELECTION_BROWSE, false);

	GtkTreeModel *tmp_model = 0;
	bool result = gtk_tree_selection_get_selected(gtk_tree_selection(), &tmp_model, *iter);
	if (model && tmp_model)
	{
		G::Object *object = G::Object::pointer((GObject*)tmp_model);
		*model = dynamic_cast<Gtk::TreeModel*>(object);
	}
	return result;
}

bool
Gtk::TreeSelection::get_selected_rows(std::vector<TreePath>& rows, TreeModel **model)
{
	g_return_val_if_fail(rows.empty(), false);

	GtkTreeModel *tmp_model = 0;
	GList *first = gtk_tree_selection_get_selected_rows(gtk_tree_selection(), &tmp_model);
	GList *next = first;

	while (next)
	{
		rows.push_back(TreePath((GtkTreePath*)next->data, false));
		next = g_list_next(next);
	}

	if (model && tmp_model)
	{
		G::Object *object = G::Object::pointer((GObject*)tmp_model);
		*model = dynamic_cast<TreeModel*>(object);
	}

	g_list_free(first);
	return !rows.empty();
}

bool
Gtk::TreeSelection::path_is_selected(const TreePath& path) const
{
	return gtk_tree_selection_path_is_selected(gtk_tree_selection(), path.gtk_tree_path());
}

bool
Gtk::TreeSelection::iter_is_selected(const TreeIter& iter) const
{
	return gtk_tree_selection_iter_is_selected(gtk_tree_selection(), iter.gtk_tree_iter());
}

namespace { // SelectCallback

struct SelectCallback
{
	typedef Gtk::TreeSelection::SelectSlot SelectSlot;
	SelectSlot slot_;

	SelectCallback(const SelectSlot& slot)
	: slot_(slot)
	{
	}

	static gboolean notify(GtkTreeSelection*, GtkTreeModel *model, GtkTreePath *path, gboolean path_selected , void *data)
	{
		SelectCallback *cb = static_cast<SelectCallback*>(data);
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreePath tmp_path(path);
		return cb->slot_(*tmp_model, tmp_path, path_selected);
	}

	static void destroy(void *data)
	{
		SelectCallback *cb = static_cast<SelectCallback*>(data);
		delete cb;
	}
};

} // namespace

void
Gtk::TreeSelection::set_select_function(const SelectSlot& select)
{
	SelectCallback *cb = new SelectCallback(select);
	gtk_tree_selection_set_select_function(gtk_tree_selection(), &SelectCallback::notify, cb, &SelectCallback::destroy);
}

namespace { // foreach_slot_calback

void foreach_slot_calback(GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, gpointer data)
{
	Gtk::TreeSelection::ForeachSlot& slot = *static_cast<Gtk::TreeSelection::ForeachSlot*>(data);
	G::Object *object = G::Object::pointer((GObject*)model);
	Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
	Gtk::TreePath tmp_path(path);
	Gtk::TreeIter tmp_iter(iter);
	slot(*tmp_model, tmp_path, tmp_iter);
}

} // namespace

void
Gtk::TreeSelection::selected_foreach(const ForeachSlot& each)
{
	ForeachSlot tmp_each(each);
	gtk_tree_selection_selected_foreach(gtk_tree_selection(), &foreach_slot_calback, &tmp_each);
}

void
Gtk::TreeSelection::select_path(const TreePath& path)
{
	gtk_tree_selection_select_path(gtk_tree_selection(), path.gtk_tree_path());
}

void
Gtk::TreeSelection::unselect_path(const TreePath& path)
{
	gtk_tree_selection_unselect_path(gtk_tree_selection(), path.gtk_tree_path());
}

void
Gtk::TreeSelection::select_iter(const TreeIter& iter)
{
	gtk_tree_selection_select_iter(gtk_tree_selection(), iter.gtk_tree_iter());
}

void
Gtk::TreeSelection::unselect_iter(const TreeIter& iter)
{
	gtk_tree_selection_unselect_iter(gtk_tree_selection(), iter.gtk_tree_iter());
}

void 
Gtk::TreeSelection::select_range(const TreePath& start_path, const TreePath& end_path)
{
	gtk_tree_selection_select_range(gtk_tree_selection(), start_path.gtk_tree_path(), end_path.gtk_tree_path());
}

void 
Gtk::TreeSelection::unselect_range(const TreePath& start_path, const TreePath& end_path)
{
	gtk_tree_selection_unselect_range(gtk_tree_selection(), start_path.gtk_tree_path(), end_path.gtk_tree_path());
}

/*  Signals
 */

const Gtk::TreeSelection::ChangedSignalType Gtk::TreeSelection::changed_signal("changed", (GCallback)&G::Marshal::void_callback);

