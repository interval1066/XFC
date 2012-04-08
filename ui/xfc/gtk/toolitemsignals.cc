/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toolitemsignals.cc - Gtk::ToolItem virtual signal handlers
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

#include "toolitem.hh"
#include "toolitemsignals.hh"
#include "private/toolitemclass.hh"
#include "tooltips.hh"

using namespace Xfc;

/*  Gtk::ToolItemSignals
 */

Gtk::ToolItemSignals::ToolItemSignals(ToolItem *tool_item)
: ContainerSignals(tool_item)
{
}

Gtk::ToolItemSignals::~ToolItemSignals()
{
}

bool 
Gtk::ToolItemSignals::on_create_menu_proxy()
{
	bool result = false;	
	GtkToolItemClass *g_class = ToolItemClass::get_parent_class(instance_);
	if (g_class && g_class->create_menu_proxy)
		result = g_class->create_menu_proxy((GtkToolItem*)instance_);
	return result;
}

void 
Gtk::ToolItemSignals::on_toolbar_reconfigured()
{
	GtkToolItemClass *g_class = ToolItemClass::get_parent_class(instance_);
	if (g_class && g_class->toolbar_reconfigured)
		g_class->toolbar_reconfigured((GtkToolItem*)instance_);
}

bool 
Gtk::ToolItemSignals::on_set_tooltip(Tooltips& tooltips, const String& tip_text, const String& tip_private)
{
	bool result = false;	
	GtkToolItemClass *g_class = ToolItemClass::get_parent_class(instance_);
	if (g_class && g_class->set_tooltip)
		result = g_class->set_tooltip((GtkToolItem*)instance_, tooltips.gtk_tooltips(), 
		                             tip_text.c_str(), tip_private.c_str());
	return result;
}

