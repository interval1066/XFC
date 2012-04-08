/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treesortable.cc - GtkTreeSortable C++ wrapper implementation
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
 
#include "treesortable.hh"
#include "treesortablesignals.hh"
#include "treemodel.hh"
#include "private/marshal.hh"
#include "private/treesortableiface.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"

using namespace Xfc;

/*  Gtk::TreeSortable
 */

Gtk::TreeSortable::TreeSortable()
{
}

Gtk::TreeSortable::~TreeSortable()
{
}
	
namespace { // CompareCallback

struct CompareCallback
{
	typedef Gtk::TreeSortable::CompareSlot CompareSlot;
	CompareSlot slot_;

	CompareCallback(const CompareSlot& slot)
	: slot_(slot)
	{
	}

	static int notify(GtkTreeModel*, GtkTreeIter *a, GtkTreeIter *b, void *data)
	{
		CompareCallback *cb = static_cast<CompareCallback*>(data);
		Gtk::TreeIter tmp_a(a);
		Gtk::TreeIter tmp_b(b);
		return cb->slot_(tmp_a, tmp_b);
	}

	static void destroy(void *data)
	{
		CompareCallback *cb = static_cast<CompareCallback*>(data);
		delete cb;
	}
};

} // namespace

void
Gtk::TreeSortable::set_sort_func(int sort_column_id, const CompareSlot& compare)
{
	CompareCallback *cb = new CompareCallback(compare);
	gtk_tree_sortable_set_sort_func(gtk_tree_sortable(), sort_column_id, &CompareCallback::notify, cb, &CompareCallback::destroy);
}

void
Gtk::TreeSortable::set_default_sort_func(const CompareSlot& compare)
{
	CompareCallback *cb = new CompareCallback(compare);
	gtk_tree_sortable_set_default_sort_func(gtk_tree_sortable(), &CompareCallback::notify, cb, &CompareCallback::destroy);
}

void
Gtk::TreeSortable::reset_default_sort_func()
{
	gtk_tree_sortable_set_default_sort_func(gtk_tree_sortable(), 0, 0, 0);
}

/*  Gtk::TreeSortableIface
 */

void
Gtk::TreeSortableIface::init(GtkTreeSortableIface *g_iface)
{
	g_iface->sort_column_changed = &sort_column_changed_proxy;
}

GtkTreeSortableIface*
Gtk::TreeSortableIface::get_parent_iface(void *instance)
{
	return static_cast<GtkTreeSortableIface*>(g_type_interface_peek_parent(GTK_TREE_SORTABLE_GET_IFACE(instance)));
}

void
Gtk::TreeSortableIface::sort_column_changed_proxy(GtkTreeSortable *sortable)
{
	TreeSortableSignals *signals = dynamic_cast<TreeSortableSignals*>(G::ObjectSignals::pointer((GObject*)sortable));
	if (signals)
	{
		signals->on_sort_column_changed();
	}
	else
	{
		GtkTreeSortableIface *g_iface = get_parent_iface(sortable);
		if (g_iface && g_iface->sort_column_changed)
			g_iface->sort_column_changed(sortable);
	}
}

/*  Gtk::TreeSortable signals
 */

const Gtk::TreeSortable::SortColumnChangedSignalType Gtk::TreeSortable::sort_column_changed_signal("sort_column_changed", (GCallback)&G::Marshal::void_callback);
