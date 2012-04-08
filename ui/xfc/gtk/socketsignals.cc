/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  socketsignals.cc - Gtk::Socket virtual signal handlers
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
 
#include "socket.hh"
#include "socketsignals.hh"
#include "private/socketclass.hh"

using namespace Xfc;

/*  Gtk::SocketSignals
 */

Gtk::SocketSignals::SocketSignals(Socket *socket)
: ContainerSignals(socket)
{
}

Gtk::SocketSignals::~SocketSignals()
{
}

void
Gtk::SocketSignals::on_plug_added()
{
	GtkSocketClass *g_class = SocketClass::get_parent_class(instance_);
	if (g_class && g_class->plug_added)
		g_class->plug_added((GtkSocket*)instance_);
}

bool
Gtk::SocketSignals::on_plug_removed()
{
	GtkSocketClass *g_class = SocketClass::get_parent_class(instance_);
	bool result = false;
	if (g_class && g_class->plug_removed)
		result = g_class->plug_removed((GtkSocket*)instance_);
	return result;
}

