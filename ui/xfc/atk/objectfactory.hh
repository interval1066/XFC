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
 
/// @file xfc/atk/objectfactory.hh
/// @brief An AtkObjectFactory C++ wrapper interface.
///
/// Provides ObjectFactory, the base object class for a factory used to create
/// accessible objects for objects of a specific GType.

#ifndef XFC_ATK_OBJECT_FACTORY_HH
#define XFC_ATK_OBJECT_FACTORY_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __ATK_OBJECT_FACTORY_H__
#include <atk/atkobjectfactory.h>
#endif

namespace Xfc {

namespace Atk {

class Object;

/// @class ObjectFactory objectfactory.hh xfc/atk/objectfactory.hh
/// @brief An AtkObjectFactory C++ wrapper class.
///
/// ObjectFactory is the base object class for a factory used to create an accessible object
/// for a specific GType. The method set_factory_type() is normally called to store in the
/// registry the factory type to be used to create an accessible of a particular GType.
///
/// An ObjectFactory is returned by Atk::Registry::get_factory(). You wont need to use this
/// class unless you are implementating your own accessible objects (for an example see
/// gtk_widget_real_get_accessible() in gtkwidget.c, if you have the GTK+ source code).

class ObjectFactory : public G::Object
{
	friend class G::Object;

	ObjectFactory(const ObjectFactory&);
	ObjectFactory& operator=(const ObjectFactory&);
	
protected:
/// @name Constructors
/// @{

	explicit ObjectFactory(AtkObjectFactory *factory, bool owns_reference = true);
	///< Construct a new ObjectFactory from an existing AtkObjectFactory.
	///< @param factory A pointer to a AtkObjectFactory.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>factory</EM> can be a newly created AtkObjectFactory or an existing
	///< AtkObjectFactory. (see G::Object::Object).

/// @}

public:
	typedef AtkObjectFactory CObjectType;

/// @name Constructors
/// @{

	virtual ~ObjectFactory();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	AtkObjectFactory* atk_object_factory() const;
	///< Get a pointer to the AtkObjectFactory structure.

	operator AtkObjectFactory* () const;
	///< Conversion operator; safely converts an ObjectFactory to an AtkObjectFactory pointer.

	GType get_accessible_type() const;
	///< Gets the GType of the accessible which is created by the factory.
	///< @return The type of the accessible which is created by the factory.
	///<
	///< The value G_TYPE_INVALID is returned if no type is found.
	
/// @}
/// @name Methods
/// @{

	Atk::Object* create_accessible(const G::Object& object);
	///< Provides an AtkObject that implements an accessibility interface on behalf of <EM>object</EM>.
	///< @param object A G::Object.
	///< @return An pointer to an Atk::Object that implements an accessibility interface on behalf of object.

	void invalidate();
	///< Inform the factory that it is no longer being used to create accessibles. 
	///< When called, the factory may need to inform Atk::Objects which it has created
	///< that they need to be re-instantiated. 
	///<
	///< <B>Note:</B> primarily used for runtime replacement of ObjectFactorys in object registries.


/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/objectfactory.inl>

#endif // XFC_ATK_OBJECT_FACTORY_HH

