/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  plug.cc - GtkPlug C++ wrapper implementation
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
 
#include "plug.hh"
#include "plugsignals.hh"
#include "socket.hh"
#include "private/marshal.hh"
#include "private/plugclass.hh"
#include "../gdk/display.hh"
#include "../gdk/window.hh"

using namespace Xfc;

/*  Gtk::Plug
 */

Gtk::Plug::Plug(GtkPlug *plug, bool owns_reference)
: Window((GtkWindow*)plug, owns_reference)
{
}

Gtk::Plug::Plug(GdkNativeWindow socket_id, const Gdk::Display *display)
: Window((GtkWindow*)PlugClass::create())
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	gtk_plug_construct_for_display(gtk_plug(), tmp_display, socket_id);
}

Gtk::Plug::~Plug()
{
}

bool
Gtk::Plug::has_socket() const
{
	return GDK_IS_WINDOW(gtk_plug()->socket_window);
}

Gdk::Window*
Gtk::Plug::socket_window() const
{
	return G::Object::wrap<Gdk::Window>(gtk_plug()->socket_window);
}

/*  Gtk::PlugClass
 */

void
Gtk::PlugClass::init(GtkPlugClass *g_class)
{
	WindowClass::init((GtkWindowClass*)g_class);
	g_class->embedded = &embedded_proxy;
}

GtkPlugClass*
Gtk::PlugClass::get_parent_class(void *instance)
{
	return static_cast<GtkPlugClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::PlugClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_PLUG, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::PlugClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::PlugClass::embedded_proxy(GtkPlug *plug)
{
	PlugSignals *signals = dynamic_cast<PlugSignals*>(G::ObjectSignals::pointer((GObject*)plug));
	if (signals)
		signals->on_embedded();
	else
	{
		GtkPlugClass *g_class = get_parent_class(plug);
		if (g_class && g_class->embedded)
			g_class->embedded(plug);
	}
}

/*  Gtk::Plug signals
 */

const Gtk::Plug::EmbeddedSignalType Gtk::Plug::embedded_signal("embedded", (GCallback)&G::Marshal::void_callback);

