/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  windowsignals.cc - Gtk::Window virtual signal handlers
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

#include "window.hh"
#include "windowsignals.hh"
#include "private/windowclass.hh"

using namespace Xfc;

/*  Gtk::WindowSignals
 */

Gtk::WindowSignals::WindowSignals(Window *window)
: ContainerSignals(window)
{
}

Gtk::WindowSignals::~WindowSignals()
{
}

void
Gtk::WindowSignals::on_set_focus(Widget *focus)
{
	GtkWindowClass *g_class = WindowClass::get_parent_class(instance_);
	if (g_class && g_class->set_focus)
		g_class->set_focus((GtkWindow*)instance_, *focus);
}

bool
Gtk::WindowSignals::on_frame_event(const Gdk::Event& event)
{
	bool result = false;
	GtkWindowClass *g_class = WindowClass::get_parent_class(instance_);
	if (g_class && g_class->frame_event)
		result = g_class->frame_event((GtkWindow*)instance_, event.gdk_event());
	return result;
}

void
Gtk::WindowSignals::on_keys_changed()
{
	GtkWindowClass *g_class = WindowClass::get_parent_class(instance_);
	if (g_class && g_class->keys_changed)
		g_class->keys_changed((GtkWindow*)instance_);
}

