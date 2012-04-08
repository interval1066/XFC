/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  object.cc - GtkObject C++ wrapper implementation
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
 
#include "object.hh"
#include "objectsignals.hh"
#include "private/marshal.hh"
#include "private/objectclass.hh"

using namespace Xfc;

/*  Gtk::Object
 */

Gtk::Object::Object(GtkObject *object, bool owns_reference)
: G::Object((GObject*)object, owns_reference)
{
}

Gtk::Object::~Object()
{
}

void
Gtk::Object::ref()
{
	G::Object::ref();
	if (gtk_object()->flags & GTK_FLOATING)
	{
		sink();
		set_owns_reference(true);
	}
}

void
Gtk::Object::dispose()
{
	if (!(gtk_object()->flags & GTK_IN_DESTRUCTION))
		G::Object::dispose();
}

/*  Gtk::ObjectClass
 */

void
Gtk::ObjectClass::init(GtkObjectClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->destroy = &destroy_proxy;
}

GtkObjectClass*
Gtk::ObjectClass::get_parent_class(void *instance)
{
	return static_cast<GtkObjectClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ObjectClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_OBJECT, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ObjectClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ObjectClass::destroy_proxy(GtkObject *object)
{
	void *ptr = g_object_get_qdata((GObject*)object, G::ObjectSignals::quark());
	if (ptr)
		static_cast<ObjectSignals*>(ptr)->on_destroy();
	else
	{
		GtkObjectClass *g_class = get_parent_class(object);
		if (g_class && g_class->destroy)
			g_class->destroy(object);
	}
}

/*  Gtk::Object  signals
 */

const Gtk::Object::DestroySignalType Gtk::Object::destroy_signal("destroy", (GCallback)&G::Marshal::void_callback);

