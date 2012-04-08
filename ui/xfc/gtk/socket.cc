/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  socket.cc - GtkSocket C++ wrapper implementation
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
#include "private/marshal.hh"
#include "private/socketclass.hh"
#include "../gdk/window.hh"

using namespace Xfc;

/*  Gtk::Socket
 */

Gtk::Socket::Socket(GtkSocket *socket, bool owns_reference)
: Container((GtkContainer*)socket, owns_reference)
{
}

Gtk::Socket::Socket()
: Container((GtkContainer*)SocketClass::create())
{
}

Gtk::Socket::~Socket()
{
}

Gdk::Window*
Gtk::Socket::plug_window() const
{
	return G::Object::wrap<Gdk::Window>(gtk_socket()->plug_window);
}

Gtk::Widget*
Gtk::Socket::plug_widget() const
{
	return G::Object::wrap<Widget>(gtk_socket()->plug_widget);
}

/*  Gtk::SocketClass
 */

void
Gtk::SocketClass::init(GtkSocketClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
	g_class->plug_added = &plug_added_proxy;
	g_class->plug_removed = &plug_removed_proxy;
}

GtkSocketClass*
Gtk::SocketClass::get_parent_class(void *instance)
{
	return static_cast<GtkSocketClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::SocketClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SOCKET, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::SocketClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::SocketClass::plug_added_proxy(GtkSocket *socket)
{
	SocketSignals *signals = dynamic_cast<SocketSignals*>(G::ObjectSignals::pointer((GObject*)socket));
	if (signals)
		signals->on_plug_added();
	else
	{
		GtkSocketClass *g_class = get_parent_class(socket);
		if (g_class && g_class->plug_added)
			g_class->plug_added(socket);
	}
}

gboolean
Gtk::SocketClass::plug_removed_proxy(GtkSocket *socket)
{
	gboolean result = FALSE;
	SocketSignals *signals = dynamic_cast<SocketSignals*>(G::ObjectSignals::pointer((GObject*)socket));
	if (signals)
		result = signals->on_plug_removed();
	else
	{
		GtkSocketClass *g_class = get_parent_class(socket);
		if (g_class && g_class->plug_removed)
			result = g_class->plug_removed(socket);
	}
	return result;
}

/*  Gtk::Socket signals
 */

const Gtk::Socket::PlugAddedSignalType Gtk::Socket::plug_added_signal("plug_added", (GCallback)&G::Marshal::void_callback);

const Gtk::Socket::PlugRemovedSignalType Gtk::Socket::plug_removed_signal("plug_removed", (GCallback)&Marshal::bool_callback);

