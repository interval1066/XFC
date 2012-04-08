/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  object.cc - AtkObject C++ wrapper implementation
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
#include "relation.hh"
#include "stateset.hh"
#include "private/objectclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Atk::role_register
 */

Atk::Role
Atk::role_register(const String& name)
{
	return (Role)atk_role_register(name.c_str());
}

/*  Atk::role_get_name
 */

String
Atk::role_get_name(Role role)
{
	return atk_role_get_name((AtkRole)role);
}

/*  Atk::role_get_localized_name
 */

String 
Atk::role_get_localized_name(Role role)
{
	return atk_role_get_localized_name((AtkRole)role);
}

/*  Atk::role_for_name
 */

Atk::Role
Atk::role_for_name(const String& name)
{
	return (Role)atk_role_for_name(name.c_str());
}

/*  Atk::Object
 */

Atk::Object::Object(AtkObject *object, bool owns_reference)
: G::Object((GObject*)object, owns_reference)
{
}

Atk::Object::~Object()
{
}

String
Atk::Object::get_name() const
{
	return atk_object_get_name(atk_object());
}

String
Atk::Object::get_description() const
{
	return atk_object_get_description(atk_object());
}

Atk::Object*
Atk::Object::get_parent() const
{
	AtkObject *parent = atk_object_get_parent(atk_object());
	return parent ? G::Object::wrap<Object>(parent) : 0;
}
	
Atk::Object*
Atk::Object::ref_accessible_child(int index) const
{
	AtkObject *child = atk_object_ref_accessible_child(atk_object(), index);
	return child ? G::Object::wrap<Object>(child) : 0;
}

Atk::RelationSet*
Atk::Object::ref_relation_set() const
{
	AtkRelationSet *set = atk_object_ref_relation_set(atk_object());
	return set ? G::Object::wrap<RelationSet>(set) : 0;
}

Pointer<Atk::StateSet>
Atk::Object::ref_state_set() const
{
	AtkStateSet *set = atk_object_ref_state_set(atk_object());
	return set ? G::Object::wrap<StateSet>(set, true) : 0;
}

void
Atk::Object::set_name(const String& name)
{
	atk_object_set_name(atk_object(), name.c_str());
}

void
Atk::Object::set_description(const String& description)
{
	atk_object_set_description(atk_object(), description.c_str());
}

void
Atk::Object::set_parent(Object& parent)
{
	atk_object_set_parent(atk_object(), parent.atk_object());
}

bool
Atk::Object::add_relationship(RelationType relationship, const Object& target)
{
	return atk_object_add_relationship(atk_object(), (AtkRelationType)relationship, target.atk_object());
}
	
bool 
Atk::Object::remove_relationship(RelationType relationship, const Object& target)
{
	return atk_object_remove_relationship(atk_object(), (AtkRelationType)relationship, target.atk_object());
}

/*  Atk::ObjectClass
 */

void
Atk::ObjectClass::init(AtkObjectClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->children_changed = &children_changed_proxy;
	g_class->focus_event = &focus_event_proxy;
	g_class->property_change = &property_change_proxy;
	g_class->state_change = &state_change_proxy;
	g_class->visible_data_changed = &visible_data_changed_proxy;
	g_class->active_descendant_changed = &active_descendant_changed_proxy;
}

AtkObjectClass*
Atk::ObjectClass::get_parent_class(void *instance)
{
	return static_cast<AtkObjectClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Atk::ObjectClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(ATK_TYPE_OBJECT, (GClassInitFunc)&init);
	}
	return type;
}

void*
Atk::ObjectClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Atk::ObjectClass::children_changed_proxy(AtkObject *accessible, guint change_index, gpointer changed_child)
{
	void *ptr = g_object_get_qdata((GObject*)accessible, G::ObjectSignals::quark());
	if (ptr)
		static_cast<ObjectSignals*>(ptr)->on_children_changed(change_index, changed_child);
	else
	{
		AtkObjectClass *g_class = get_parent_class(accessible);
		if (g_class && g_class->children_changed)
			g_class->children_changed(accessible, change_index, changed_child);
	}
}

void
Atk::ObjectClass::focus_event_proxy(AtkObject *accessible, gboolean focus_in)
{
	void *ptr = g_object_get_qdata((GObject*)accessible, G::ObjectSignals::quark());
	if (ptr)
		static_cast<ObjectSignals*>(ptr)->on_focus_event(focus_in);
	else
	{
		AtkObjectClass *g_class = get_parent_class(accessible);
		if (g_class && g_class->focus_event)
			g_class->focus_event(accessible, focus_in);
	}
}

void
Atk::ObjectClass::property_change_proxy(AtkObject *accessible, AtkPropertyValues *values)
{
	void *ptr = g_object_get_qdata((GObject*)accessible, G::ObjectSignals::quark());
	if (ptr)
		static_cast<ObjectSignals*>(ptr)->on_property_change(values);
	else
	{
		AtkObjectClass *g_class = get_parent_class(accessible);
		if (g_class && g_class->property_change)
			g_class->property_change(accessible, values);
	}
}

void
Atk::ObjectClass::state_change_proxy(AtkObject *accessible, const gchar *name, gboolean state_set)
{
	void *ptr = g_object_get_qdata((GObject*)accessible, G::ObjectSignals::quark());
	if (ptr)
	{
		String tmp_name(name);
		static_cast<ObjectSignals*>(ptr)->on_state_change(tmp_name, state_set);
	}
	else
	{
		AtkObjectClass *g_class = get_parent_class(accessible);
		if (g_class && g_class->state_change)
			g_class->state_change(accessible, name, state_set);
	}
}

void
Atk::ObjectClass::visible_data_changed_proxy(AtkObject *accessible)
{
	void *ptr = g_object_get_qdata((GObject*)accessible, G::ObjectSignals::quark());
	if (ptr)
		static_cast<ObjectSignals*>(ptr)->on_visible_data_changed();
	else
	{
		AtkObjectClass *g_class = get_parent_class(accessible);
		if (g_class && g_class->visible_data_changed)
			g_class->visible_data_changed(accessible);
	}
}

void
Atk::ObjectClass::active_descendant_changed_proxy(AtkObject *accessible, gpointer *child)
{
	void *ptr = g_object_get_qdata((GObject*)accessible, G::ObjectSignals::quark());
	if (ptr)
		static_cast<ObjectSignals*>(ptr)->on_active_descendant_changed(child);
	else
	{
		AtkObjectClass *g_class = get_parent_class(accessible);
		if (g_class && g_class->active_descendant_changed)
			g_class->active_descendant_changed(accessible, child);
	}
}

// Atk::Object signals

const Atk::Object::ChildrenChangedSignalType Atk::Object::children_changed_signal("children_changed", (GCallback)&Marshal::void_int_pvoid_callback);

const Atk::Object::FocusEventSignalType Atk::Object::focus_event_signal("focus_event", (GCallback)&G::Marshal::void_bool_callback);

const Atk::Object::PropertyChangeSignalType Atk::Object::property_change_signal("property_change", (GCallback)&Marshal::void_patkpropertyvalues_callback);

const Atk::Object::StateChangeSignalType Atk::Object::state_change_signal("state_change", (GCallback)&Marshal::void_string_bool_callback);

const Atk::Object::VisibleDataChangedSignalType Atk::Object::visible_data_changed_signal("visible_data_changed", (GCallback)&G::Marshal::void_callback);

const Atk::Object::ActiveDescendantChangedSignalType Atk::Object::active_descendant_changed_signal("active_descendant_changed", (GCallback)&Marshal::void_ppvoid_callback);

