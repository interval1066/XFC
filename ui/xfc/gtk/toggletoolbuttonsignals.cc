/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toggletoolbuttonsignals.cc - Gtk::ToggleToolButton virtual signal handlers
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

#include "toggletoolbutton.hh"
#include "toggletoolbuttonsignals.hh"
#include "private/toggletoolbuttonclass.hh"

using namespace Xfc;

/*  Gtk::ToggleToolButtonSignals
 */

Gtk::ToggleToolButtonSignals::ToggleToolButtonSignals(ToggleToolButton *button)
: ToolButtonSignals(button)
{
}

Gtk::ToggleToolButtonSignals::~ToggleToolButtonSignals()
{
}

void
Gtk::ToggleToolButtonSignals::on_toggled()
{
	GtkToggleToolButtonClass *g_class = ToggleToolButtonClass::get_parent_class(instance_);
	if (g_class && g_class->toggled)
		g_class->toggled((GtkToggleToolButton*)instance_);
}

