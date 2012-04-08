/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  containersignals.cc - Gtk::Container virtual signal handlers
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
 
#include "container.hh"
#include "containersignals.hh"
#include "private/containerclass.hh"

using namespace Xfc;

/*  Gtk::ContainerSignals
 */

Gtk::ContainerSignals::ContainerSignals(Container *container)
: WidgetSignals(container)
{
}

Gtk::ContainerSignals::~ContainerSignals()
{
}

void
Gtk::ContainerSignals::on_add(Widget& widget)
{
	GtkContainerClass *g_class = ContainerClass::get_parent_class(instance_);
	if (g_class && g_class->add)
		g_class->add((GtkContainer*)instance_, widget.gtk_widget());
}

void
Gtk::ContainerSignals::on_remove(Widget& widget)
{
	GtkContainerClass *g_class = ContainerClass::get_parent_class(instance_);
	if (g_class && g_class->remove)
		g_class->remove((GtkContainer*)instance_, widget.gtk_widget());
}

void
Gtk::ContainerSignals::on_check_resize()
{
	GtkContainerClass *g_class = ContainerClass::get_parent_class(instance_);
	if (g_class && g_class->check_resize)
		g_class->check_resize((GtkContainer*)instance_);
}

void
Gtk::ContainerSignals::on_set_focus_child(Widget *widget)
{
	GtkContainerClass *g_class = ContainerClass::get_parent_class(instance_);
	if (g_class && g_class->set_focus_child)
		g_class->set_focus_child((GtkContainer*)instance_, *widget);
}

