/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  celllayout.cc - GtkCellLayout C++ wrapper implementation
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

#include "celllayout.hh"
#include "cellrenderer.hh"
#include "treemodel.hh"
#include "../gdk/events.hh"

using namespace Xfc;

/*  Gtk::CellColumnAttributes
 */
 
Gtk::CellColumnAttributes::CellColumnAttributes()
{
}

Gtk::CellColumnAttributes::CellColumnAttributes(const char *attribute, int column)
{
	add(attribute, column);
}

Gtk::CellColumnAttributes::CellColumnAttributes(const String& attribute, int column)
{
	add(attribute, column);
}
	
Gtk::CellColumnAttributes::~CellColumnAttributes()
{
}

const std::vector<String>& 
Xfc::Gtk::CellColumnAttributes::get_attributes() const
{
	return attributes_;
}

void 
Gtk::CellColumnAttributes::add(const char *attribute, int column)
{
	attributes_.push_back(attribute);
	columns_.push_back(column);
}

void 
Gtk::CellColumnAttributes::add(const String& attribute, int column)
{
	attributes_.push_back(attribute);
	columns_.push_back(column);
}

void 
Gtk::CellColumnAttributes::clear()
{
	attributes_.clear();
	columns_.clear();
}

/*  Gtk::CellLayout
 */

Gtk::CellLayout::CellLayout()
{
}
	
Gtk::CellLayout::~CellLayout()
{
}
	
void 
Gtk::CellLayout::pack_start(CellRenderer& cell, bool expand)
{
	gtk_cell_layout_pack_start(gtk_cell_layout(), cell.gtk_cell_renderer(), expand);
}

void 
Gtk::CellLayout::pack_end(CellRenderer& cell, bool expand)
{
	gtk_cell_layout_pack_end(gtk_cell_layout(), cell.gtk_cell_renderer(), expand);
}

void 
Gtk::CellLayout::add_attribute(CellRenderer& cell, const char *attribute, int column)
{
	gtk_cell_layout_add_attribute(gtk_cell_layout(), cell.gtk_cell_renderer(), attribute, column);
}
	
void 
Gtk::CellLayout::add_attribute(CellRenderer& cell, const String& attribute, int column)
{
	add_attribute(cell, attribute.c_str(), column);
}
	
void 
Gtk::CellLayout::set_attributes(CellRenderer& cell, const CellColumnAttributes& attributes)
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

	static void notify(GtkCellLayout*, GtkCellRenderer *cell, GtkTreeModel *model, GtkTreeIter *iter, void *data)
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
Gtk::CellLayout::set_cell_data_func(CellRenderer& cell, const CellDataSlot& slot)
{
	CellDataCallback *cb = new CellDataCallback(slot);
	gtk_cell_layout_set_cell_data_func(gtk_cell_layout(), cell.gtk_cell_renderer(),
	                                   &CellDataCallback::notify, cb, &CellDataCallback::destroy);
}

void 
Gtk::CellLayout::remove_cell_data_func(CellRenderer& cell)
{
	gtk_cell_layout_set_cell_data_func(gtk_cell_layout(), cell.gtk_cell_renderer(), 0, 0, 0);
}

void 
Gtk::CellLayout::reorder(CellRenderer& cell, int position)
{
	gtk_cell_layout_reorder(gtk_cell_layout(), cell.gtk_cell_renderer(), position);
}

void 
Gtk::CellLayout::clear_attributes(CellRenderer& cell)
{
	gtk_cell_layout_clear_attributes(gtk_cell_layout(), cell.gtk_cell_renderer());
}

