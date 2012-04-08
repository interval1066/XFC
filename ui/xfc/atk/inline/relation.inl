/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  relation.inl - Atk::Relation and Atk::RelationSet inline functions
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

/*  Atk::Releation
 */

inline AtkRelation*
Xfc::Atk::Relation::atk_relation() const
{
	return reinterpret_cast<AtkRelation*>(instance_);
}

inline Xfc::Atk::Relation::operator AtkRelation* () const
{
	return this ? atk_relation() : 0;
}

inline Xfc::Atk::RelationType
Xfc::Atk::Relation::get_relation_type() const
{
	return (RelationType)atk_relation_get_relation_type(atk_relation());
}

/*  Atk::ReleationSet
 */

inline AtkRelationSet*
Xfc::Atk::RelationSet::atk_relation_set() const
{
	return reinterpret_cast<AtkRelationSet*>(instance_);
}

inline Xfc::Atk::RelationSet::operator AtkRelationSet* () const
{
	return this ? atk_relation_set() : 0;
}

inline bool
Xfc::Atk::RelationSet::contains(RelationType relationship) const
{
	return atk_relation_set_contains(atk_relation_set(), (AtkRelationType)relationship);
}

inline int
Xfc::Atk::RelationSet::get_n_relations() const
{
	return atk_relation_set_get_n_relations(atk_relation_set());
}

