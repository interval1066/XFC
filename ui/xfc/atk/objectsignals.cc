/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  objectsignals.cc - Atk::Object virtual signal handlers
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
#include "private/objectclass.hh"

using namespace Xfc;

/*  Atk::ObjectSignals
 */

Atk::ObjectSignals::ObjectSignals(Object *object)
: G::ObjectSignals(object)
{
}

Atk::ObjectSignals::~ObjectSignals()
{
}

void
Atk::ObjectSignals::on_children_changed(unsigned int change_index, gpointer changed_child)
{
	AtkObjectClass *g_class = ObjectClass::get_parent_class(instance_);
	if (g_class && g_class->children_changed)
		g_class->children_changed((AtkObject*)instance_, change_index, changed_child);
}

void
Atk::ObjectSignals::on_focus_event(bool focus_in)
{
	AtkObjectClass *g_class = ObjectClass::get_parent_class(instance_);
	if (g_class && g_class->focus_event)
		g_class->focus_event((AtkObject*)instance_, focus_in);
}

void
Atk::ObjectSignals::on_property_change(AtkPropertyValues *values)
{
	AtkObjectClass *g_class = ObjectClass::get_parent_class(instance_);
	if (g_class && g_class->property_change)
		g_class->property_change((AtkObject*)instance_, values);
}

void
Atk::ObjectSignals::on_state_change(const String& name, bool state_set)
{
	AtkObjectClass *g_class = ObjectClass::get_parent_class(instance_);
	if (g_class && g_class->state_change)
		g_class->state_change((AtkObject*)instance_, name.c_str(), state_set);
}

void
Atk::ObjectSignals::on_visible_data_changed()
{
	AtkObjectClass *g_class = ObjectClass::get_parent_class(instance_);
	if (g_class && g_class->visible_data_changed)
		g_class->visible_data_changed((AtkObject*)instance_);
}

void
Atk::ObjectSignals::on_active_descendant_changed(void **child)
{
	AtkObjectClass *g_class = ObjectClass::get_parent_class(instance_);
	if (g_class && g_class->active_descendant_changed)
		g_class->active_descendant_changed((AtkObject*)instance_, child);
}

