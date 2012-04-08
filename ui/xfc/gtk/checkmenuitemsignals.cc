/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  checkmenuitemsignals.cc - Gtk::CheckMenuItem virtual signal handlers
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
 
#include "checkmenuitem.hh"
#include "checkmenuitemsignals.hh"
#include "private/checkmenuitemclass.hh"

using namespace Xfc;

/*  Gtk::CheckMenuItemSignals
 */

Gtk::CheckMenuItemSignals::CheckMenuItemSignals(CheckMenuItem *check_menu_item)
: MenuItemSignals(check_menu_item)
{
}

Gtk::CheckMenuItemSignals::~CheckMenuItemSignals()
{
}

void
Gtk::CheckMenuItemSignals::on_toggled()
{
	GtkCheckMenuItemClass *g_class = CheckMenuItemClass::get_parent_class(instance_);
	if (g_class && g_class->toggled)
		g_class->toggled((GtkCheckMenuItem*)instance_);
}

