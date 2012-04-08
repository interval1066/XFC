/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  cellrendererpixbuf.cc - GtkCellRendererPixbuf C++ wrapper implementation
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
 
#include "cellrendererpixbuf.hh"
#include "private/cellrendererpixbufclass.hh"
#include "../gdk-pixbuf/pixbuf.hh"

using namespace Xfc;

/*  Gtk::CellRendererPixbuf
 */

Gtk::CellRendererPixbuf::CellRendererPixbuf(GtkCellRendererPixbuf *cell, bool owns_reference)
: CellRenderer((GtkCellRenderer*)cell, owns_reference)
{
}

Gtk::CellRendererPixbuf::CellRendererPixbuf()
: CellRenderer((GtkCellRenderer*)CellRendererPixbufClass::create())
{
}

Gtk::CellRendererPixbuf::~CellRendererPixbuf()
{
}

/*  Gtk::CellRendererPixbufClass
 */

void
Gtk::CellRendererPixbufClass::init(GtkCellRendererPixbufClass *g_class)
{
	CellRendererClass::init((GtkCellRendererClass*)g_class);
}

GType
Gtk::CellRendererPixbufClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CELL_RENDERER_PIXBUF, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CellRendererPixbufClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::CellRendererPixbuf properties
 */

const Gtk::CellRendererPixbuf::PixbufPropertyType Gtk::CellRendererPixbuf::pixbuf_property("pixbuf");

const Gtk::CellRendererPixbuf::PixbufExpanderOpenPropertyType Gtk::CellRendererPixbuf::pixbuf_expander_open_property("pixbuf_expander_open");

const Gtk::CellRendererPixbuf::PixbufExpanderClosedPropertyType Gtk::CellRendererPixbuf::pixbuf_expander_closed_property("pixbuf_expander_closed");

const Gtk::CellRendererPixbuf::StockIdPropertyType Gtk::CellRendererPixbuf::stock_id_property("stock_id");

const Gtk::CellRendererPixbuf::StockSizePropertyType Gtk::CellRendererPixbuf::stock_size_property("stock_size");

const Gtk::CellRendererPixbuf::StockDetailPropertyType Gtk::CellRendererPixbuf::stock_detail_property("stock_detail");

