/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  accelgroup.cc - GtkAccelGroup C++ wrapper implementation
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

#include "accelgroup.hh"
#include "accelgroupsignals.hh"
#include "private/accelgroupclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::accel_groups_activate
 */

bool
Gtk::accel_groups_activate(G::Object& object, const AccelKey& accel_key)
{
	return gtk_accel_groups_activate(object.g_object(), accel_key.key(), GdkModifierType(accel_key.mods()));
}

/*  Gtk::accelerator_valid
 */

bool
Gtk::accelerator_valid(const AccelKey& accel_key)
{
	return gtk_accelerator_valid(accel_key.key(), GdkModifierType(accel_key.mods()));
}

Gtk::AccelKey
Gtk::accelerator_parse(const String& accelerator, AccelFlagsField accel_flags)
{
	return AccelKey(accelerator.c_str(), accel_flags);
}

/*  Gtk::accelerator_name
 */

String
Gtk::accelerator_name(const AccelKey& accel_key)
{
	return gtk_accelerator_name(accel_key.key(), GdkModifierType(accel_key.mods()));
}

/*  Gtk::accelerator_get_label
 */
 
String 
Gtk::accelerator_get_label(unsigned int accelerator_key, Gdk::ModifierType accelerator_mods)
{
	char *label = gtk_accelerator_get_label(accelerator_key, (GdkModifierType)accelerator_mods);
	String s(label);
	g_free(label);
	return s;
}

/*  Gtk::AccelGroup
 */

Gtk::AccelGroup::AccelGroup(GtkAccelGroup *group, bool owns_reference)
: G::Object((GObject*)group, owns_reference)
{
}

Gtk::AccelGroup::AccelGroup()
: G::Object((GObject*)AccelGroupClass::create())
{
}

Gtk::AccelGroup::~AccelGroup()
{
}

Gtk::AccelGroup*
Gtk::AccelGroup::from_accel_closure(GClosure *closure)
{
	GtkAccelGroup *accel_group = gtk_accel_group_from_accel_closure(closure);
	return accel_group ? G::Object::wrap<AccelGroup>(accel_group) : 0;
}

void
Gtk::AccelGroup::connect(const AccelKey& accel_key, GClosure *closure)
{
	gtk_accel_group_connect(gtk_accel_group(), accel_key.key(), GdkModifierType(accel_key.mods()),
	                        GtkAccelFlags(accel_key.flags()), closure);
}

void
Gtk::AccelGroup::connect(const String& accel_path, GClosure *closure)
{
	connect(accel_path.c_str(), closure);
}

bool
Gtk::AccelGroup::disconnect(const AccelKey& accel_key)
{
	return gtk_accel_group_disconnect_key(gtk_accel_group(), accel_key.key(), GdkModifierType(accel_key.mods()));
}

/*  Gtk::AccelGroupClass
 */

void
Gtk::AccelGroupClass::init(GtkAccelGroupClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->accel_changed = &accel_changed_proxy;
}

GtkAccelGroupClass*
Gtk::AccelGroupClass::get_parent_class(void *instance)
{
	return static_cast<GtkAccelGroupClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::AccelGroupClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ACCEL_GROUP, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::AccelGroupClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::AccelGroupClass::accel_changed_proxy(GtkAccelGroup *accel_group, guint keyval, GdkModifierType modifier, GClosure *accel_closure)
{
	AccelGroupSignals *signals = dynamic_cast<AccelGroupSignals*>(G::ObjectSignals::pointer((GObject*)accel_group));
	if (signals)
	{
		AccelKey accel_key(keyval, (Gdk::ModifierTypeField)modifier);
		signals->on_accel_changed(accel_key, accel_closure);
	}
	else
	{
		GtkAccelGroupClass *g_class = get_parent_class(accel_group);
		if (g_class && g_class->accel_changed)
			g_class->accel_changed(accel_group, keyval, modifier, accel_closure);
	}
}

/*  Gtk::AccelGroup signals
 */

const Gtk::AccelGroup::AccelChangedSignalType Gtk::AccelGroup::accel_changed_signal("accel_changed", (GCallback)&Marshal::void_uint_gdkmodifiertype_gclosure_callback);

