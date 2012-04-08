/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  buttonsignals.cc - Gtk::Button virtual signal handlers
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
 
#include "button.hh"
#include "buttonsignals.hh"
#include "private/buttonclass.hh"

using namespace Xfc;

Gtk::ButtonSignals::ButtonSignals(Button *button) 
: ContainerSignals(button)
{
}

Gtk::ButtonSignals::~ButtonSignals()
{
}

void
Gtk::ButtonSignals::on_pressed()
{
	GtkButtonClass *g_class = ButtonClass::get_parent_class(instance_);
	if (g_class && g_class->pressed)
		g_class->pressed((GtkButton*)instance_);
}

void
Gtk::ButtonSignals::on_released()
{
	GtkButtonClass *g_class = ButtonClass::get_parent_class(instance_);
	if (g_class && g_class->released)
		g_class->released((GtkButton*)instance_);
}

void
Gtk::ButtonSignals::on_clicked()
{
	GtkButtonClass *g_class = ButtonClass::get_parent_class(instance_);
	if (g_class && g_class->clicked)
		g_class->clicked((GtkButton*)instance_);
}

void
Gtk::ButtonSignals::on_enter()
{
	GtkButtonClass *g_class = ButtonClass::get_parent_class(instance_);
	if (g_class && g_class->enter)
		g_class->enter((GtkButton*)instance_);
}

void
Gtk::ButtonSignals::on_leave()
{
	GtkButtonClass *g_class = ButtonClass::get_parent_class(instance_);
	if (g_class && g_class->leave)
		g_class->leave((GtkButton*)instance_);
}

void
Gtk::ButtonSignals::on_activate()
{
	GtkButtonClass *g_class = ButtonClass::get_parent_class(instance_);
	if (g_class && g_class->activate)
		g_class->activate((GtkButton*)instance_);
}

