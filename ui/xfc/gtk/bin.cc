/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  bin.cc - GtkBin C++ wrapper implementation
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
 
#include "bin.hh"
#include "private/binclass.hh"

using namespace Xfc;

/*  Gtk::Bin
 */

Gtk::Bin::Bin(GtkBin *bin, bool owns_reference)
: Container((GtkContainer*)bin, owns_reference)
{
}

Gtk::Bin::~Bin()
{
}

Gtk::Widget*
Gtk::Bin::get_child() const
{
	return G::Object::wrap<Widget>(gtk_bin_get_child(gtk_bin()));
}

/*  Gtk::BinClass
 */

void
Gtk::BinClass::init(GtkBinClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
}

GType
Gtk::BinClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_BIN, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::BinClass::create()
{
	return g_object_new(get_type(), 0);
}

