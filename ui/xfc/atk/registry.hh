/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
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
 
/// @file xfc/atk/registry.hh
/// @brief An AtkRegistry C++ wrapper interface.
///
/// Provides Registry, an object used to store the GType of the factories used to create
/// an accessible object for an object of a particular GType.

#ifndef XFC_ATK_REGISTRY_HH
#define XFC_ATK_REGISTRY_HH

#ifndef XFC_ATK_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __ATK_REGISTRY_H__
#include <atk/atkregistry.h>
#endif

namespace Xfc {

namespace Atk {

class ObjectFactory;

/// @class Registry registry.hh xfc/atk/registry.hh
/// @brief An AtkRegistry C++ wrapper class.
///
/// Registry is an object that is used to store the GType of the factories
/// used to create an accessible object for an object of a particular GType.

class Registry : public G::Object
{
	friend class G::Object;

	Registry(const Registry&);
	Registry& operator=(const Registry&);
	
protected:
/// @name Constructors
/// @{

	explicit Registry(AtkRegistry *registry, bool owns_reference = true);
	///< Construct a new Registry from an existing AtkRegistry.
	///< @param registry A pointer to a AtkRegistry.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>registry</EM> can be a newly created AtkRegistry or an existing
	///< AtkRegistry. (see G::Object::Object).

/// @}

public:
	typedef AtkRegistry CObjectType;
	
/// @name Constructors
/// @{

	virtual ~Registry();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	AtkRegistry* atk_registry() const;
	///< Get a pointer to the AtkRegistry structure.

	operator AtkRegistry* () const;
	///< Conversion operator; safely converts a Registry to an AtkRegistry pointer.

	GType get_factory_type(GType type) const;
	///< Provides a GType indicating the ObjectFactory subclass associated with type.
	///< @param type A GType with which to look up the associated ObjectFactory subclass.
	///< @return A GType associated with type <EM>type</EM>.

	ObjectFactory* get_factory(GType type) const;
	///< Gets an ObjectFactory appropriate for creating Atk::Objects appropriate for <EM>type</EM>.
	///< @param type A GType with which to look up the associated ObjectFactory.
	///< @return An ObjectFactory appropriate for creating Atk::Objects appropriate for <EM>type</EM>.

/// @}
/// @name Accessors
/// @{

	static Registry* get_default();
	///< Gets a default implementation of the ObjectFactory/type registry.
	///< @return A default implementation of the ObjectFactory/type registry.
	///<
	///< <B>Note:</B> For most toolkit maintainers, this will be the correct registry
	///< for registering new AtkObject factories. Following a call to this function,
	///< maintainers may call set_factory_type() to associate an ObjectFactory subclass
	///< with the GType of objects for whom accessibility information will be provided.

/// @}
/// @name Methods
/// @{

	void set_factory_type(GType type, GType factory_type);
	///< Associate an ObjectFactory subclass with a GType. 
	///< @param type The Atk::Object type.
	///< @param factory_type An ObjectFactory type to associate with <EM>type</EM>
	///< (must implement an Atk::Object appropriate for <EM>type</EM>).
	///<
	///< <B>Note:</B> The associated factory_type will thereafter be responsible for the
	///< creation of new Atk::Object implementations for instances appropriate for type.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/registry.inl>

#endif // XFC_ATK_REGISTRY_HH

