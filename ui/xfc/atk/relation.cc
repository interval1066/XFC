/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  relation.cc - AtkRelation and AtkRelationSet C++ wrapper implementation
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
 
#include "relation.hh"
#include "object.hh"
#include "private/relationclass.hh"

using namespace Xfc;

/*  Atk::Relation
 */

Atk::Relation::Relation(AtkRelation *relation, bool owns_reference)
: G::Object((GObject*)relation, owns_reference)
{
}
	
Atk::Relation::Relation(const std::vector<Atk::Object*>& targets, RelationType relationship)
: G::Object((GObject*)RelationClass::create())
{
	g_return_if_fail(!targets.empty());
	int count = targets.size();
	GPtrArray *array = g_ptr_array_sized_new(count);

	int i = 0;
	while (i < count)
	{
		targets[i]->ref();
		g_ptr_array_add(array, targets[i]->atk_object());
		++i;
	}

	atk_relation()->target = array;
	atk_relation()->relationship = (AtkRelationType)relationship;
}

Atk::Relation::~Relation()
{
}
	
bool
Atk::Relation::get_target(std::vector<Atk::Object*>& targets) const
{
	g_return_val_if_fail(targets.empty(), false);
	GPtrArray *tmp_targets = atk_relation_get_target(atk_relation());
	int count = tmp_targets->len;

	int i = 0;
	while (i < count)
	{
		targets.push_back(G::Object::wrap<Atk::Object>((AtkObject*)g_ptr_array_index(tmp_targets, i)));
		++i;
	}
	return !targets.empty();
}		
	
void 
Atk::Relation::add_target(Atk::Object& target)
{
	atk_relation_add_target(atk_relation(), target.atk_object());
}

/*  Atk::RelationClass
 */

void
Atk::RelationClass::init(AtkRelationClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Atk::RelationClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(ATK_TYPE_RELATION, (GClassInitFunc)&init);
	}
	return type;
}

void*
Atk::RelationClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Atk::RelationSet
 */
 
Atk::RelationSet::RelationSet(AtkRelationSet *set, bool owns_reference)
: G::Object((GObject*)set, owns_reference)
{
}
	
Atk::RelationSet::RelationSet()
: G::Object((GObject*)RelationSetClass::create())
{
}

Atk::RelationSet::~RelationSet()
{
}
	
Atk::Relation*
Atk::RelationSet::get_relation(int index) const
{
	AtkRelation *relation = atk_relation_set_get_relation(atk_relation_set(), index);
	return relation ? G::Object::wrap<Relation>(relation) : 0;
}

Atk::Relation*
Atk::RelationSet::get_relation(RelationType relationship) const
{
	AtkRelation *relation = atk_relation_set_get_relation_by_type(atk_relation_set(), (AtkRelationType)relationship);
	return relation ? G::Object::wrap<Relation>(relation) : 0;
}
	
void
Atk::RelationSet::add(Relation& relation)
{
	atk_relation_set_add(atk_relation_set(), relation.atk_relation());
}

void
Atk::RelationSet::remove(Relation& relation)
{
	atk_relation_set_remove(atk_relation_set(), relation.atk_relation());
}

void 
Atk::RelationSet::add_relation_by_type(RelationType relationship, Atk::Object& target)
{
	atk_relation_set_add_relation_by_type(atk_relation_set(), (AtkRelationType)relationship, target.atk_object());
}

/*  Atk::RelationSetClass
 */

void
Atk::RelationSetClass::init(AtkRelationSetClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Atk::RelationSetClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(ATK_TYPE_RELATION_SET, (GClassInitFunc)&init);
	}
	return type;
}

void*
Atk::RelationSetClass::create()
{
	return g_object_new(get_type(), 0);
}

