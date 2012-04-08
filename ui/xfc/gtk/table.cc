/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  table.cc - GtkTable C++ wrapper implementation
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
 
#include "table.hh"
#include "private/tableclass.hh"

using namespace Xfc;

/*  Gtk::Table
 */

Gtk::Table::Table(GtkTable *table, bool owns_reference)
: Container((GtkContainer*)table, owns_reference)
{
}

Gtk::Table::Table(unsigned int rows, unsigned int columns, bool homogeneous) 
: Container((GtkContainer*)TableClass::create())
{
	resize(rows, columns);
	set_homogeneous(homogeneous);
}

Gtk::Table::~Table() 
{
}
	
void
Gtk::Table::attach(Widget& child, unsigned int left_attach, unsigned int right_attach, unsigned int top_attach, unsigned int bottom_attach,
                   AttachOptionsField xoptions, AttachOptionsField yoptions, unsigned int xpadding, unsigned int ypadding)
{
	gtk_table_attach(gtk_table(), child.gtk_widget(), left_attach, right_attach, top_attach, bottom_attach,
	                 (GtkAttachOptions)xoptions, (GtkAttachOptions)yoptions, xpadding, ypadding);
}

void
Gtk::Table::set_spacings(unsigned int row_spacing, unsigned int col_spacing)
{
	set_row_spacings(row_spacing);
	set_col_spacings(col_spacing);
}

/*  Gtk::TableClass
 */

void
Gtk::TableClass::init(GtkTableClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
}

GType
Gtk::TableClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TABLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TableClass::create()
{
	return g_object_new(get_type(), 0);
}

