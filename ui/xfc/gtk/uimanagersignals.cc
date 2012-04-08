/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  uimanagersignals.cc - Gtk::UIManager virtual signal handlers
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

#include "uimanager.hh"
#include "uimanagersignals.hh"
#include "private/uimanagerclass.hh"
#include "widget.hh"

using namespace Xfc;

/*  Gtk::UIManagerSignals
 */

Gtk::UIManagerSignals::UIManagerSignals(UIManager *ui_manager)
: G::ObjectSignals(ui_manager)
{
}

Gtk::UIManagerSignals::~UIManagerSignals()
{
}

void 
Gtk::UIManagerSignals::on_add_widget(Widget& widget)
{
	GtkUIManagerClass *g_class = UIManagerClass::get_parent_class(instance_);
	if (g_class && g_class->add_widget)
		g_class->add_widget((GtkUIManager*)instance_, widget.gtk_widget());
}
	
void
Gtk::UIManagerSignals::on_actions_changed()
{
	GtkUIManagerClass *g_class = UIManagerClass::get_parent_class(instance_);
	if (g_class && g_class->actions_changed)
		g_class->actions_changed((GtkUIManager*)instance_);
}
	
void
Gtk::UIManagerSignals::on_connect_proxy(Action& action, Widget& proxy)
{
	GtkUIManagerClass *g_class = UIManagerClass::get_parent_class(instance_);
	if (g_class && g_class->connect_proxy)
		g_class->connect_proxy((GtkUIManager*)instance_, action.gtk_action(), proxy.gtk_widget());
}
	
void
Gtk::UIManagerSignals::on_disconnect_proxy(Action& action, Widget& proxy)
{
	GtkUIManagerClass *g_class = UIManagerClass::get_parent_class(instance_);
	if (g_class && g_class->disconnect_proxy)
		g_class->disconnect_proxy((GtkUIManager*)instance_, action.gtk_action(), proxy.gtk_widget());
}
	
void
Gtk::UIManagerSignals::on_pre_activate(Action& action)
{
	GtkUIManagerClass *g_class = UIManagerClass::get_parent_class(instance_);
	if (g_class && g_class->pre_activate)
		g_class->pre_activate((GtkUIManager*)instance_, action.gtk_action());
}
	
void
Gtk::UIManagerSignals::on_post_activate(Action& action)
{
	GtkUIManagerClass *g_class = UIManagerClass::get_parent_class(instance_);
	if (g_class && g_class->post_activate)
		g_class->post_activate((GtkUIManager*)instance_, action.gtk_action());
}

