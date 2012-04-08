/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  cellrendererprogress.cc - GtkCellRendererProgress C++ wrapper implementation
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
 
#include "cellrendererprogress.hh"
#include "private/cellrendererprogressclass.hh"

using namespace Xfc;

/*  Gtk::CellRendererProgress
 */

Gtk::CellRendererProgress::CellRendererProgress(GtkCellRendererProgress *cell, bool owns_reference)
: CellRenderer((GtkCellRenderer*)cell, owns_reference)
{
}

Gtk::CellRendererProgress::CellRendererProgress()
: CellRenderer((GtkCellRenderer*)CellRendererProgressClass::create())
{
}

Gtk::CellRendererProgress::~CellRendererProgress()
{
}

/*  Gtk::CellRendererProgressClass
 */

void
Gtk::CellRendererProgressClass::init(GtkCellRendererProgressClass *g_class)
{
	CellRendererClass::init((GtkCellRendererClass*)g_class);
}

GType
Gtk::CellRendererProgressClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CELL_RENDERER_PROGRESS, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CellRendererProgressClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::CellRendererProgress properties
 */

const Gtk::CellRendererProgress::ValuePropertyType Gtk::CellRendererProgress::value_property("value");

const Gtk::CellRendererProgress::TextPropertyType Gtk::CellRendererProgress::text_property("text");

