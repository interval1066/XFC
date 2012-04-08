/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  menushellsignals.cc - Gtk::MenuShell virtual signal handlers
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
 
#include "menushell.hh"
#include "menushellsignals.hh"
#include "private/menushellclass.hh"

using namespace Xfc;

/*  Gtk::MenuShellSignals
 */

Gtk::MenuShellSignals::MenuShellSignals(MenuShell *menu_shell)
: ContainerSignals(menu_shell)
{
}

Gtk::MenuShellSignals::~MenuShellSignals()
{
}

void
Gtk::MenuShellSignals::on_deactivate()
{
	GtkMenuShellClass *g_class = MenuShellClass::get_parent_class(instance_);
	if (g_class && g_class->deactivate)
		g_class->deactivate((GtkMenuShell*)instance_);
}

void
Gtk::MenuShellSignals::on_selection_done()
{
	GtkMenuShellClass *g_class = MenuShellClass::get_parent_class(instance_);
	if (g_class && g_class->selection_done)
		g_class->selection_done((GtkMenuShell*)instance_);
}

