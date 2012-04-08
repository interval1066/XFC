/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  object.cc - GObject C++ wrapper implementation
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
#include "quark.hh"
#include "value.hh"
#include "private/marshal.hh"
#include "private/objectclass.hh"

using namespace Xfc;

/*  G::Object
 */

G::Object::Object(GObject *object, bool owns_reference)
{
	g_return_if_fail(object != 0);

	if (!g_object_get_qdata(object, ObjectClass::quark()))
	{
		g_object_set_qdata_full(object, ObjectClass::quark(), this, &destroy_notify);
		instance_ = (GTypeInstance*)object;
		set_owns_reference(owns_reference);
	}
	else
	{
		const char *name = g_type_name(((GTypeInstance*)object)->g_class->g_type);
		g_error("This %s object already has a XFC wrapper.", name);
	}
}

G::Object::~Object()
{
	if (instance_)
	{
		remove_data(ObjectClass::quark());
		if (owns_reference())
			unref();
		instance_ = 0;
	}
}

void
G::Object::destroy_notify(void *data)
{
	G::Object *object = static_cast<G::Object*>(data);
	if (object)
	{
		g_object_steal_qdata(*object, ObjectClass::quark());
		object->instance_ = 0;
		if (object->is_dynamic())
		{
			delete object;
		}
	}
}

void
G::Object::get_property(const char* property_name, G::Value& value) const
{
	g_object_get_property(g_object(), property_name, value.g_value());
}

void*
G::Object::get_data(const Quark& quark) const
{
	return g_object_get_qdata(g_object(), quark);
}

void*
G::Object::get_data(const String& key) const
{
	return get_data(key.c_str());
}

G::Object*
G::Object::pointer(GObject* object)
{
	return static_cast<Object*>(g_object_get_qdata(object, ObjectClass::quark()));
}

void
G::Object::ref()
{
	g_object_ref(g_object());
}

void
G::Object::unref()
{
	g_object_unref(g_object());
}

void
G::Object::dispose()
{
	g_object_run_dispose(g_object());
}

void
G::Object::set_property(const char* property_name, const G::Value& value)
{
	g_object_set_property(g_object(), property_name, value.g_value());
}

void
G::Object::set_data(const Quark& quark, void *data, GDestroyNotify destroy)
{
	g_object_set_qdata_full(g_object(), quark, data, destroy);
}

void
G::Object::set_data(const String& key, void *data, GDestroyNotify destroy)
{
	g_object_set_qdata_full(g_object(), g_quark_from_string(key.c_str()), data, destroy);
}

void*
G::Object::remove_data(const Quark& quark, bool notify)
{
	void *ptr = 0;
	if (notify)
		set_data(quark, 0);
	else
		ptr = g_object_steal_qdata(g_object(), quark);
	return ptr;
}

void*
G::Object::remove_data(const char *key, bool notify)
{
	return remove_data(G::Quark(key), notify);
}

void*
G::Object::remove_data(const String& key, bool notify)
{
	return remove_data(key.c_str(), notify);
}

void
G::Object::emit_by_name(const char *signal_name, ...)
{
	g_return_if_fail(signal_name != 0);
	
	GSignalQuery query;
	g_signal_query(g_signal_lookup(signal_name, type()), &query);
	g_return_if_fail(query.signal_id != 0);

	va_list args;
	va_start(args, signal_name);
	g_signal_emit_valist(g_object(), query.signal_id, 0, args);
	va_end (args);
}

bool
G::Object::disconnect_by_name(const char* signal_name)
{
	unsigned int id = g_signal_lookup(signal_name, type());
	if (id)
	{
		id = g_signal_handler_find(g_object(), G_SIGNAL_MATCH_ID, id, 0, 0, 0, 0);
		if (id)
			g_signal_handler_disconnect(g_object(), id);
	}
	return id != 0;
}

/*  G::ObjectClass
 */

void
G::ObjectClass::init(GObjectClass *g_class)
{
	g_class->notify = &notify_proxy;
}

GObjectClass*
G::ObjectClass::get_parent_class(void *instance)
{
	return static_cast<GObjectClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
G::ObjectClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(G_TYPE_OBJECT, (GClassInitFunc)&init);
	}
	return type;
}

GQuark
G::ObjectClass::quark()
{
	static GQuark quark_ = 0;
	if (!quark_)
	{
		quark_ = g_quark_from_static_string("xfc_object");
	}
	return quark_;
}

void*
G::ObjectClass::create()
{
	return g_object_new(get_type(), 0);
}

void
G::ObjectClass::notify_proxy(GObject *object, GParamSpec *pspec)
{
	void *ptr = g_object_get_qdata(object, ObjectSignals::quark());
	if (ptr)
		static_cast<ObjectSignals*>(ptr)->on_notify(pspec);
	else
	{
		GObjectClass *g_class = get_parent_class(object);
		if (g_class && g_class->notify)
			g_class->notify(object, pspec);
	}
}

/*  G::Object signals
 */

const G::Object::NotifySignalType G::Object::notify_signal("notify", (GCallback)&Marshal::void_gparamspec_callback);

