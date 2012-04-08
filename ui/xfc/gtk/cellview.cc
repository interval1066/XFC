/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  cellview.cc - GtkCellView C++ wrapper implementation
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
 
#include "cellview.hh"
#include "private/cellviewclass.hh"
#include "cellrendererpixbuf.hh"
#include "cellrenderertext.hh"
#include "treemodel.hh"
#include "../gdk/color.hh"

using namespace Xfc;

/*  Gtk::CellView
 */

Gtk::CellView::CellView(GtkCellView *cell_view, bool owns_reference)
: Widget((GtkWidget*)cell_view, owns_reference)
{
}

Gtk::CellView::CellView()
: Widget((GtkWidget*)CellViewClass::create())
{
}	

namespace { // init_cell_view

void init_cell_view(Gtk::CellView& cell_view, const String& text, bool use_markup)
{
	Gtk::CellRendererText *cell = new Gtk::CellRendererText;  
	
	if (use_markup)
		cell->property_markup() = text;
	else
		cell->property_text() = text;
		
	cell_view.pack_start(*cell);	
}

} // namespace	

Gtk::CellView::CellView(const char *text, bool use_markup)
: Widget((GtkWidget*)CellViewClass::create())
{
	init_cell_view(*this, text, use_markup);
}
	
Gtk::CellView::CellView(const String& text, bool use_markup)
: Widget((GtkWidget*)CellViewClass::create())
{
	init_cell_view(*this, text, use_markup);
}
	
Gtk::CellView::CellView(Gdk::Pixbuf& pixbuf)
: Widget((GtkWidget*)CellViewClass::create())
{
	Gtk::CellRendererPixbuf *cell = new Gtk::CellRendererPixbuf;  
	cell->property_pixbuf() = &pixbuf;	
	pack_start(*cell);
} 

Gtk::CellView::~CellView()
{
}

Pointer<Gtk::TreePath> 
Gtk::CellView::get_displayed_row() const
{
	return G::Boxed::wrap<TreePath>(GTK_TYPE_TREE_PATH, gtk_cell_view_get_displayed_row(gtk_cell_view()), false);
}

bool 
Gtk::CellView::get_size_of_row(const TreePath& path, Requisition& requisition)
{
	return gtk_cell_view_get_size_of_row(gtk_cell_view(), path.gtk_tree_path(), requisition.gtk_requisition());
}

bool 
Gtk::CellView::get_cell_renderers(std::vector<CellRenderer*>& cell_list)
{
	g_return_val_if_fail(cell_list.empty(), false);
	GList *first = gtk_cell_view_get_cell_renderers(gtk_cell_view());
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
Gtk::CellView::set_model(TreeModel *model)
{
	gtk_cell_view_set_model(gtk_cell_view(), *model);
}
	
void 
Gtk::CellView::set_displayed_row(const TreePath *path)
{
	gtk_cell_view_set_displayed_row(gtk_cell_view(), *path);
}

void 
Gtk::CellView::set_background_color(const Gdk::Color *color)
{
	gtk_cell_view_set_background_color(gtk_cell_view(), *color);
}

/*  Gtk::CellViewClass
 */

void
Gtk::CellViewClass::init(GtkCellViewClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
}

GType
Gtk::CellViewClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CELL_VIEW, (GClassInitFunc)&init);
		G::TypeInstance::add_interface(type, GTK_TYPE_CELL_LAYOUT, (GInterfaceInitFunc)0);
	}
	return type;
}

void*
Gtk::CellViewClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::CellView properties
 */

const Gtk::CellView::BackgroundPropertyType Gtk::CellView::background_property("background");

const Gtk::CellView::BackgroundGdkPropertyType Gtk::CellView::background_gdk_property("background_gdk");

const Gtk::CellView::BackgroundSetPropertyType Gtk::CellView::background_set_property("background_set");

