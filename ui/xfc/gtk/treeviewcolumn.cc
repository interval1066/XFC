/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treeviewcolumn.cc - GtkTreeViewColumn C++ wrapper implementation
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
 
#include "treeviewcolumn.hh"
#include "treeviewcolumnsignals.hh"
#include "cellrenderer.hh"
#include "treemodel.hh"
#include "widget.hh"
#include "private/marshal.hh"
#include "private/treeviewcolumnclass.hh"

using namespace Xfc;

/*  Gtk::TreeViewColumn
 */

Gtk::TreeViewColumn::TreeViewColumn(GtkTreeViewColumn *tree_column, bool owns_reference)
: Object((GtkObject*)tree_column, owns_reference)
{
}
	
Gtk::TreeViewColumn::TreeViewColumn()
: Object((GtkObject*)TreeViewColumnClass::create())
{
}

Gtk::TreeViewColumn::TreeViewColumn(const char *title)
: Object((GtkObject*)TreeViewColumnClass::create())
{
	set_title(title);
}
	
Gtk::TreeViewColumn::TreeViewColumn(const String& title)
: Object((GtkObject*)TreeViewColumnClass::create())
{
	set_title(title);
}
	
Gtk::TreeViewColumn::TreeViewColumn(const char *title, CellRenderer& cell, const char *attribute, int column)
: Object((GtkObject*)TreeViewColumnClass::create())
{
	set_title(title);
	pack_start(cell);
	add_attribute(cell, attribute, column);
}
	
Gtk::TreeViewColumn::TreeViewColumn(const String& title, CellRenderer& cell, const String& attribute, int column)
: Object((GtkObject*)TreeViewColumnClass::create())
{
	set_title(title);
	pack_start(cell);
	add_attribute(cell, attribute, column);
}
	
Gtk::TreeViewColumn::TreeViewColumn(const char *title, CellRenderer& cell, const CellColumnAttributes& attributes)
: Object((GtkObject*)TreeViewColumnClass::create())
{
	set_title(title);
	pack_start(cell);
	set_attributes(cell, attributes);
}

Gtk::TreeViewColumn::TreeViewColumn(const String& title, CellRenderer& cell, const CellColumnAttributes& attributes)
: Object((GtkObject*)TreeViewColumnClass::create())
{
	set_title(title);
	pack_start(cell);
	set_attributes(cell, attributes);
}

Gtk::TreeViewColumn::~TreeViewColumn()
{
}

String
Gtk::TreeViewColumn::get_title() const
{
	return gtk_tree_view_column_get_title(gtk_tree_view_column());
}

Gtk::Widget*
Gtk::TreeViewColumn::get_widget() const
{
	return G::Object::wrap<Widget>(gtk_tree_view_column_get_widget(gtk_tree_view_column()));
}

bool
Gtk::TreeViewColumn::get_cell_renderers(std::vector<CellRenderer*>& cell_list) const
{
	g_return_val_if_fail(cell_list.empty(), false);
	GList *first = gtk_tree_view_column_get_cell_renderers(gtk_tree_view_column());
	GList *next = first;

	while (next)
	{
		cell_list.push_back(G::Object::wrap<CellRenderer>((GtkCellRenderer*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !cell_list.empty();
}	

void 
Gtk::TreeViewColumn::cell_get_size(const Gdk::Rectangle *cell_area, int *x_offset, int *y_offset, int *width, int *height) const
{
	gtk_tree_view_column_cell_get_size(gtk_tree_view_column(), *cell_area, x_offset, y_offset, width, height);
}

void
Gtk::TreeViewColumn::pack_start(CellRenderer& cell, bool expand)
{
	gtk_tree_view_column_pack_start(gtk_tree_view_column(), cell.gtk_cell_renderer(), expand);
}

void
Gtk::TreeViewColumn::pack_end(CellRenderer& cell, bool expand)
{
	gtk_tree_view_column_pack_end(gtk_tree_view_column(), cell.gtk_cell_renderer(), expand);
}

void
Gtk::TreeViewColumn::add_attribute(CellRenderer& cell, const char *attribute, int column)
{
	gtk_tree_view_column_add_attribute(gtk_tree_view_column(), cell.gtk_cell_renderer(), attribute, column);
}

void
Gtk::TreeViewColumn::add_attribute(CellRenderer& cell, const String& attribute, int column)
{
	add_attribute(cell, attribute.c_str(), column);
}

void 
Gtk::TreeViewColumn::set_attributes(CellRenderer& cell, const CellColumnAttributes& attributes)
{
	g_return_if_fail(!attributes.empty());
	clear_attributes(cell);
	int i = 0;
	while (i < attributes.size())
	{	
		add_attribute(cell, attributes.get_attributes()[i].c_str(), attributes.get_columns()[i]);
		++i;
	};
}
	
namespace { // CellDataCallback

struct CellDataCallback
{
	typedef Gtk::CellLayout::CellDataSlot CellDataSlot;
	CellDataSlot slot_;

	CellDataCallback(const CellDataSlot& slot)
	: slot_(slot)
	{
	}

	static void notify(GtkTreeViewColumn*, GtkCellRenderer *cell, GtkTreeModel *model, GtkTreeIter *iter, void *data)
	{
		CellDataCallback *cb = static_cast<CellDataCallback*>(data);
		G::Object *object = G::Object::pointer((GObject*)model);
		Gtk::TreeModel *tmp_model = dynamic_cast<Gtk::TreeModel*>(object);
		Gtk::TreeIter tmp_iter(iter);
		cb->slot_(*G::Object::wrap<Gtk::CellRenderer>(cell), *tmp_model, tmp_iter);
	}

	static void destroy(void *data)
	{
		CellDataCallback *cb = static_cast<CellDataCallback*>(data);
		delete cb;
	}
};

} // namespace

void
Gtk::TreeViewColumn::set_cell_data_func(CellRenderer& cell, const CellDataSlot& data)
{
	CellDataCallback *cb = new CellDataCallback(data);
	gtk_tree_view_column_set_cell_data_func(gtk_tree_view_column(), cell.gtk_cell_renderer(),
	                                        &CellDataCallback::notify, cb, &CellDataCallback::destroy);
}

void
Gtk::TreeViewColumn::remove_cell_data_func(CellRenderer& cell)
{
	gtk_tree_view_column_set_cell_data_func(gtk_tree_view_column(), cell.gtk_cell_renderer(), 0, 0, 0);
}

void
Gtk::TreeViewColumn::clear_attributes(CellRenderer& cell)
{
	gtk_tree_view_column_clear_attributes(gtk_tree_view_column(), cell.gtk_cell_renderer());
}

void
Gtk::TreeViewColumn::set_title(const String& title)
{
	gtk_tree_view_column_set_title(gtk_tree_view_column(), title.c_str());
}

void
Gtk::TreeViewColumn::set_widget(Widget *widget)
{
	gtk_tree_view_column_set_widget(gtk_tree_view_column(), *widget);
}

void
Gtk::TreeViewColumn::cell_set_cell_data(const TreeModel& model, const TreeIter& iter, bool is_expander, bool is_expanded)
{
	gtk_tree_view_column_cell_set_cell_data(gtk_tree_view_column(), model.gtk_tree_model(),
	                                        iter.gtk_tree_iter(), is_expander, is_expanded);
}

void 
Gtk::TreeViewColumn::focus_cell(CellRenderer& cell)
{
	gtk_tree_view_column_focus_cell(gtk_tree_view_column(), cell.gtk_cell_renderer());
}

/*  Gtk::TreeViewColumnClass
 */

void
Gtk::TreeViewColumnClass::init(GtkTreeViewColumnClass *g_class)
{
	ObjectClass::init((GtkObjectClass*)g_class);
	g_class->clicked = &clicked_proxy;
}

GtkTreeViewColumnClass*
Gtk::TreeViewColumnClass::get_parent_class(void *instance)
{
	return static_cast<GtkTreeViewColumnClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::TreeViewColumnClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TREE_VIEW_COLUMN, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TreeViewColumnClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::TreeViewColumnClass::clicked_proxy(GtkTreeViewColumn *tree_column)
{
	TreeViewColumnSignals *signals = dynamic_cast<TreeViewColumnSignals*>(G::ObjectSignals::pointer((GObject*)tree_column));
	if (signals)
		signals->on_clicked();
	else
	{
		GtkTreeViewColumnClass *g_class = get_parent_class(tree_column);
		if (g_class && g_class->clicked)
			g_class->clicked(tree_column);
	}
}

/*  Gtk::TreeViewColumn signals
 */

const Gtk::TreeViewColumn::ClickedSignalType Gtk::TreeViewColumn::clicked_signal("clicked", (GCallback)&G::Marshal::void_callback);

