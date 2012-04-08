/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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

/// @file xfc/atk/relation.hh
/// @brief An AtkRelation and AtkRelationSet C++ wrapper interface.
///
/// Provides Relation and RelationSet. Relation is used to describe a relation between an object
/// and one or more other objects. RelationSet is the set of Relations which an Atk::Object has.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

#ifndef XFC_ATK_RELATION_HH
#define XFC_ATK_RELATION_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_ATK_UTIL_HH
#include <xfc/atk/util.hh>
#endif

#ifndef __ATK_RELATION_H__
#include <atk/atkrelationset.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Atk {
	
class Object;

/// @class Relation relation.hh xfc/atk/relation.hh
/// @brief An AtkRelation C++ wrapper class.
///
/// A Relation describes a relation between an object and one or more other objects.
/// The actual relations that an object has with other objects are defined as a
/// RelationSet, which is a set of Relations.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Relation : public G::Object
{
	friend class G::Object;

	Relation(const Relation&);
	Relation& operator=(const Relation&);
	
protected:
/// @name Constructors
/// @{

	explicit Relation(AtkRelation *relation, bool owns_reference = true);
	///< Construct a new Relation from an existing AtkRelation.
	///< @param relation A pointer to a AtkRelation.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>relation</EM> can be a newly created AtkRelation or an existing
	///< AtkRelation. (see G::Object::Object).

/// @}

public:
	typedef AtkRelation CObjectType;

/// @name Constructors
/// @{

	Relation(const std::vector<Atk::Object*>& targets, RelationType relationship);
	///< Constructs a new relation for the specified <EM>relationship</EM>
	///< and the specified list of targets.
	///< @param targets A reference to a vector of Atk::Object* that lists the target objects.
	///< @param relationship A RelationType with which to create the new Relation.
	///<
	///< A Relation object is created with a reference count of 1 that the caller owns.
	
	virtual ~Relation();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	AtkRelation* atk_relation() const;
	///< Get a pointer to the AtkRelation structure.

	operator AtkRelation* () const;
	///< Conversion operator; safely converts a Relation to an AtkRelation pointer.

	RelationType get_relation_type() const;
	///< Gets the type of the relation.
	///< @return The type of the relation.

	bool get_target(std::vector<Atk::Object*>& targets) const;
	///< Gets the target list of the relation.
	///< @param targets A reference to a vector of Atk::Object* to hold the target list.
	///< @return <EM>true</EM> if the vector is not empty.

/// @}
/// @name Methods
/// @{

	void add_target(Atk::Object& target);
	///< Adds the specified Atk::Object to the target for the relation, if it is not already present.
	///< @param target An Atk::Object.

/// @}
};

/// @class RelationSet relation.hh xfc/atk/relation.hh
/// @brief An AtkRelationSet C++ wrapper class.
///
/// RelationSet is a set of Relations, normally the set of Relations which an Atk::Object has.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class RelationSet : public G::Object
{
	friend class G::Object;

	RelationSet(const RelationSet&);
	RelationSet& operator=(const RelationSet&);
	
protected:
/// @name Constructors
/// @{

	explicit RelationSet(AtkRelationSet *set, bool owns_reference = true);
	///< Construct a new RelationSet from an existing AtkRelationSet.
	///< @param set A pointer to a AtkRelationSet.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>set</EM> can be a newly created AtkRelationSet or an existing
	///< AtkRelationSet. (see G::Object::Object).

/// @}

public:
	typedef AtkRelationSet CObjectType;

/// @name Constructors
/// @{

	RelationSet();
	///< Constructs an empty relation set with a reference count of 1 that the caller owns.
	
	virtual ~RelationSet();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{
	
	AtkRelationSet* atk_relation_set() const;
	///< Get a pointer to the AtkRelationSet structure.

	operator AtkRelationSet* () const;
	///< Conversion operator; safely converts a RelationSet to an AtkRelationSet pointer.

	bool contains(RelationType relationship) const;
	///< Determines whether the relation set contains a relation that matches the specified type.
	///< @param relationship A RelationType.
	///< @return <EM>true</EM> if <EM>relationship</EM> is the relationship type of a relation
	///< in the set, <EM>false</EM> otherwise.

	int get_n_relations() const;
	///< Determines the number of relations in a relation set.
	///< @return An integer representing the number of relations in the set.

	Relation* get_relation(int index) const;
	///< Determines the relation at the specified position in the relation set.
	///< @param index An integer representing a position in the set, starting from 0.
	///< @return A Relation, which is the relation at position i in the set.

	Relation* get_relation(RelationType relationship) const;
	///< Finds a relation that matches the specified type.
	///< @param relationship A RelationType.
	///< @return A Relation, which is a relation matching the specified type.
	
/// @}
/// @name Methods
/// @{

	void add(Relation& relation);
	///< Add a new relation to the current relation set if it is not already present.
	///< @param relation A Relation.

	void remove(Relation& relation);
	///< Removes a relation from the relation set.
	///< @param relation A Relation.
	///<
	///< This method unreferences the Relation so it will be deleted, unless 
	///< there is another reference to it.

	void add_relation_by_type(RelationType relationship, Atk::Object& target);
	///< Add a new relation of the specified type with the specified target to the
	///< relation set if the relation set does not contain a relation of that type.
	///< @param relationship An Atk::RelationType.
	///< @param target An Atk::Object.
	///<	 
	///< If the relation set does contain a relation of that type a the target is added to the relation.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/relation.inl>

#endif // XFC_ATK_RELATION_HH

