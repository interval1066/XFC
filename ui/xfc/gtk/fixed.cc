/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  fixed.cc - GtkFixed C++ wrapper implementation
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
 
#include "fixed.hh"
#include "private/fixedclass.hh"

using namespace Xfc;

/*  Gtk::Fixed
 */

Gtk::Fixed::Fixed(GtkFixed *fixed, bool owns_reference)
: Container((GtkContainer*)fixed, owns_reference)
{
}

Gtk::Fixed::Fixed() 
: Container((GtkContainer*)FixedClass::create())
{
}

Gtk::Fixed::~Fixed()
{
}

void
Gtk::Fixed::put(Widget& widget, int x, int y)
{
	gtk_fixed_put(gtk_fixed(), widget.gtk_widget(), x, y);
}

void
Gtk::Fixed::move(Widget& widget, int x, int y)
{
	gtk_fixed_move(gtk_fixed(), widget.gtk_widget(), x, y);
}

/*  Gtk::FixedClass
 */

void
Gtk::FixedClass::init(GtkFixedClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
}

GType
Gtk::FixedClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FIXED, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::FixedClass::create()
{
	return g_object_new(get_type(), 0);
}

