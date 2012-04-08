/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  accessible.cc - GtkAccessible C++ wrapper implementation
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

#include "accessible.hh"
#include "private/accessibleclass.hh"

using namespace Xfc;

/*  Gtk::Accessible
 */

Gtk::Accessible::Accessible(GtkAccessible *accessible, bool owns_reference)
: Atk::Object((AtkObject*)accessible, owns_reference)
{
}

Gtk::Accessible::~Accessible()
{
}

/*  Gtk::AccessibleClass
 */

void
Gtk::AccessibleClass::init(GtkAccessibleClass *g_class)
{
	Atk::ObjectClass::init((AtkObjectClass*)g_class);
}

GType
Gtk::AccessibleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ACCESSIBLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::AccessibleClass::create()
{
	return g_object_new(get_type(), 0);
}

