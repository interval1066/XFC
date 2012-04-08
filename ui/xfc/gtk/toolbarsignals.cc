/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toolbarsignals.cc - Gtk::Toolbar virtual signal handlers.
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
 
#include "toolbar.hh"
#include "toolbarsignals.hh"
#include "private/toolbarclass.hh"

using namespace Xfc;

/*  Gtk::ToolbarSignals
 */

Gtk::ToolbarSignals::ToolbarSignals(Toolbar *toolbar)
: ContainerSignals(toolbar)
{
}

Gtk::ToolbarSignals::~ToolbarSignals()
{
}
	
void
Gtk::ToolbarSignals::on_orientation_changed(Orientation orientation)
{
	GtkToolbarClass *g_class = ToolbarClass::get_parent_class(instance_);
	if (g_class && g_class->orientation_changed)
		g_class->orientation_changed((GtkToolbar*)instance_, (GtkOrientation)orientation);
}

void
Gtk::ToolbarSignals::on_style_changed(ToolbarStyle style)
{
	GtkToolbarClass *g_class = ToolbarClass::get_parent_class(instance_);
	if (g_class && g_class->style_changed)
		g_class->style_changed((GtkToolbar*)instance_, (GtkToolbarStyle)style);
}

bool
Gtk::ToolbarSignals::on_popup_context_menu(int x, int y, int button_number)
{
	bool result = false;
	GtkToolbarClass *g_class = ToolbarClass::get_parent_class(instance_);
	if (g_class && g_class->popup_context_menu)
		result = g_class->popup_context_menu((GtkToolbar*)instance_, x, y, button_number);
	return result;
}

