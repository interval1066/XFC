/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  stateset.cc - AtkStateSet C++ wrapper implementation
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
 
#include "stateset.hh"
#include "private/statesetclass.hh"

using namespace Xfc;

/*  Atk::state_type_register
 */

Atk::StateType
Atk::state_type_register(const String& name)
{
	return (StateType)atk_state_type_register(name.c_str());
}

/*  Atk::state_type_get_name
 */

String
Atk::state_type_get_name(StateType type)
{
	return atk_state_type_get_name((AtkStateType)type);
}

/*  Atk::state_type_for_name
 */

Atk::StateType
Atk::state_type_for_name(const String& name)
{
	return (StateType)atk_state_type_for_name(name.c_str());
}

/*  Atk::StateSet
 */

Atk::StateSet::StateSet(AtkStateSet *set, bool owns_reference)
: G::Object((GObject*)set, owns_reference)
{
}
	
Atk::StateSet::StateSet()
: G::Object((GObject*)StateSetClass::create())
{
}

Atk::StateSet::~StateSet()
{
}
	
bool
Atk::StateSet::contains_states(const std::vector<StateType>& types) const
{
	return atk_state_set_contains_states(atk_state_set(), (AtkStateType*)const_cast<StateType*>(&types[0]), types.size());
}

void
Atk::StateSet::add_states(const std::vector<StateType>& types)
{
	atk_state_set_add_states(atk_state_set(), (AtkStateType*)const_cast<StateType*>(&types[0]), types.size());
}

Pointer<Atk::StateSet> 
Atk::StateSet::and_sets(StateSet& compare_set)
{
	AtkStateSet *set = atk_state_set_and_sets(atk_state_set(), compare_set.atk_state_set());
	return set ? G::Object::wrap_new<StateSet>(set, true) : 0;
}

Pointer<Atk::StateSet> 
Atk::StateSet::or_sets(StateSet& compare_set)
{
	AtkStateSet *set = atk_state_set_or_sets(atk_state_set(), compare_set.atk_state_set());
	return set ? G::Object::wrap_new<StateSet>(set, true) : 0;
}

Pointer<Atk::StateSet> 
Atk::StateSet::xor_sets(StateSet& compare_set)
{
	AtkStateSet *set = atk_state_set_xor_sets(atk_state_set(), compare_set.atk_state_set());
	return set ? G::Object::wrap_new<StateSet>(set, true) : 0;
}

/*  Atk::StateSetClass
 */

void
Atk::StateSetClass::init(AtkStateSetClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Atk::StateSetClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(ATK_TYPE_STATE_SET, (GClassInitFunc)&init);
	}
	return type;
}

void*
Atk::StateSetClass::create()
{
	return g_object_new(get_type(), 0);
}

