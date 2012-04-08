/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  menuitemsignals.cc - Gtk::MenuItem virtual signal handlers
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
 
#include "menuitem.hh"
#include "menuitemsignals.hh"
#include "menu.hh"
#include "private/menuitemclass.hh"

using namespace Xfc;

/*  Gtk::MenuItemSignals
 */

Gtk::MenuItemSignals::MenuItemSignals(MenuItem *menu_item)
: ItemSignals(menu_item)
{
}

Gtk::MenuItemSignals::~MenuItemSignals()
{
}

void
Gtk::MenuItemSignals::on_activate()
{
	GtkMenuItemClass *g_class = MenuItemClass::get_parent_class(instance_);
	if (g_class && g_class->activate)
		g_class->activate((GtkMenuItem*)instance_);
}

void
Gtk::MenuItemSignals::on_activate_item()
{
	GtkMenuItemClass *g_class = MenuItemClass::get_parent_class(instance_);
	if (g_class && g_class->activate_item)
		g_class->activate_item((GtkMenuItem*)instance_);
}

void
Gtk::MenuItemSignals::on_toggle_size_request(int *requisition)
{
	GtkMenuItemClass *g_class = MenuItemClass::get_parent_class(instance_);
	if (g_class && g_class->toggle_size_request)
		g_class->toggle_size_request((GtkMenuItem*)instance_, requisition);
}

void
Gtk::MenuItemSignals::on_toggle_size_allocate(int allocate)
{
	GtkMenuItemClass *g_class = MenuItemClass::get_parent_class(instance_);
	if (g_class && g_class->toggle_size_allocate)
		g_class->toggle_size_allocate((GtkMenuItem*)instance_, allocate);
}

