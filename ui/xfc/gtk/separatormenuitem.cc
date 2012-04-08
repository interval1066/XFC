/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  separatormenuitem.cc - GtkSeparatorMenuItem C++ wrapper implementation
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
 
#include "separatormenuitem.hh"
#include "private/separatormenuitemclass.hh"

using namespace Xfc;

/*  Gtk::SeparatorMenuItem
 */

Gtk::SeparatorMenuItem::SeparatorMenuItem(GtkSeparatorMenuItem *menu_item, bool owns_reference)
: MenuItem((GtkMenuItem*)menu_item, owns_reference)
{
}
	
Gtk::SeparatorMenuItem::SeparatorMenuItem()
: MenuItem((GtkMenuItem*)SeparatorMenuItemClass::create())
{
}

Gtk::SeparatorMenuItem::~SeparatorMenuItem()
{
}

/*  Gtk::SeparatorMenuItemClass
 */

void
Gtk::SeparatorMenuItemClass::init(GtkSeparatorMenuItemClass *g_class)
{
	MenuItemClass::init((GtkMenuItemClass*)g_class);
}

GType
Gtk::SeparatorMenuItemClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SEPARATOR_MENU_ITEM, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::SeparatorMenuItemClass::create()
{
	return g_object_new(get_type(), 0);
}

