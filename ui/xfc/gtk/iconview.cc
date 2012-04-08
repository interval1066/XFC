/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  iconview.cc - GtkIconView C++ wrapper implementation
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
 
#include "iconview.hh"
#include "iconviewsignals.hh"
#include "treemodel.hh"
#include "private/iconviewclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::IconView
 */

Gtk::IconView::IconView(GtkIconView *icon_view, bool owns_reference)
: Container((GtkContainer*)icon_view, owns_reference)
{
}

Gtk::IconView::IconView()
: Container((GtkContainer*)IconViewClass::create())
{
}

Gtk::IconView::IconView(TreeModel& model)
: Container((GtkContainer*)IconViewClass::create())
{
	set_model(&model);
}

Gtk::IconView::~IconView()
{
}

Gtk::TreeModel*
Gtk::IconView::get_model() const
{
	Gtk::TreeModel *tmp_model = 0;
	GtkTreeModel *model = gtk_icon_view_get_model(gtk_icon_view());
	if (model)
	{
		G::Object *object = G::Object::pointer((GObject*)model);
		tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
	}
	return tmp_model;
}

Pointer<Gtk::TreePath> 
Gtk::IconView::get_path_at_pos(int x, int y) const
{
	GtkTreePath *path = gtk_icon_view_get_path_at_pos(gtk_icon_view(), x, y);
	return path ? G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, path, false) : 0;
}

bool 
Gtk::IconView::path_is_selected(const TreePath& path) const
{
	return gtk_icon_view_path_is_selected(gtk_icon_view(), path.gtk_tree_path());
}

bool 
Gtk::IconView::get_selected_items(std::vector<TreePath>& items) const
{
	g_return_val_if_fail(items.empty(), false);
	GList *first = gtk_icon_view_get_selected_items(gtk_icon_view());
	GList *next = first;

	while (next)
	{
		items.push_back(TreePath((GtkTreePath*)next->data, false));
		next = g_list_next(next);
	}

 	g_list_free(first);
	return !items.empty();
}

void 
Gtk::IconView::set_model(TreeModel *model)
{
	gtk_icon_view_set_model(gtk_icon_view(), *model);
}

namespace { // foreach_slot_callback

void foreach_slot_callback(GtkIconView *icon_view, GtkTreePath *path, void *data)
{
	Gtk::IconView::ForeachSlot& slot = *static_cast<Gtk::IconView::ForeachSlot*>(data);
	Gtk::TreePath tmp_path(path);
	slot(tmp_path);
}

} // namespace

void 
Gtk::IconView::selected_foreach(const ForeachSlot& each)
{
	ForeachSlot tmp_each(each);
	gtk_icon_view_selected_foreach(gtk_icon_view(), &foreach_slot_callback, &tmp_each);
}

void 
Gtk::IconView::select_path(const TreePath& path)
{
	gtk_icon_view_select_path(gtk_icon_view(), path.gtk_tree_path());
}
	
void 
Gtk::IconView::unselect_path(const TreePath& path)
{
	gtk_icon_view_unselect_path(gtk_icon_view(), path.gtk_tree_path());
}

void 
Gtk::IconView::item_activated(const TreePath& path)
{
	gtk_icon_view_item_activated(gtk_icon_view(), path.gtk_tree_path());
}

/*  Gtk::IconViewClass
 */

void
Gtk::IconViewClass::init(GtkIconViewClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
	g_class->set_scroll_adjustments = &set_scroll_adjustments_proxy;
	g_class->item_activated = &item_activated_proxy;
	g_class->selection_changed = &selection_changed_proxy;
}

GtkIconViewClass*
Gtk::IconViewClass::get_parent_class(void *instance)
{
	return static_cast<GtkIconViewClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::IconViewClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ICON_VIEW, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::IconViewClass::create()
{
	return g_object_new(get_type(), 0);
}

void 
Gtk::IconViewClass::set_scroll_adjustments_proxy(GtkIconView *icon_view, GtkAdjustment *hadjustment, GtkAdjustment *vadjustment)
{
	IconViewSignals *signals = dynamic_cast<IconViewSignals*>(G::ObjectSignals::pointer((GObject*)icon_view));
	if (signals)
		signals->on_set_scroll_adjustments(G::Object::wrap<Gtk::Adjustment>(hadjustment),
		                                   G::Object::wrap<Gtk::Adjustment>(vadjustment));
	else
	{
		GtkIconViewClass *g_class = get_parent_class(icon_view);
		if (g_class && g_class->set_scroll_adjustments)
			g_class->set_scroll_adjustments(icon_view, hadjustment, vadjustment);
	}
}
	
void 
Gtk::IconViewClass::item_activated_proxy(GtkIconView *icon_view, GtkTreePath *path)
{
	IconViewSignals *signals = dynamic_cast<IconViewSignals*>(G::ObjectSignals::pointer((GObject*)icon_view));
	if (signals)
	{
		TreePath tmp_path(path);
		signals->on_item_activated(tmp_path);
	}
	else
	{
		GtkIconViewClass *g_class = get_parent_class(icon_view);
		if (g_class && g_class->item_activated)
			g_class->item_activated(icon_view, path);
	}
}
	
void 
Gtk::IconViewClass::selection_changed_proxy(GtkIconView *icon_view)
{
	IconViewSignals *signals = dynamic_cast<IconViewSignals*>(G::ObjectSignals::pointer((GObject*)icon_view));
	if (signals)
		signals->on_selection_changed();
	else
	{
		GtkIconViewClass *g_class = get_parent_class(icon_view);
		if (g_class && g_class->selection_changed)
			g_class->selection_changed(icon_view);
	}
}

/*  Gtk::IconView
 */

const Gtk::IconView::SetScrollAdjustmentsSignalType Gtk::IconView::set_scroll_adjustments_signal("set_scroll_adjustments", (GCallback)&Marshal::void_adjustment_adjustment_callback);

const Gtk::IconView::ItemActivatedSignalType Gtk::IconView::item_activated_signal("item_activated", (GCallback)&Marshal::void_treepath_callback);

const Gtk::IconView::SelectionChangedSignalType Gtk::IconView::selection_changed_signal("selection_changed", (GCallback)&G::Marshal::void_callback);

