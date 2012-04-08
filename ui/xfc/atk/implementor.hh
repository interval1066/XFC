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
 
/// @file xfc/atk/implementor.hh
/// @brief An AtkImplementor C++ wrapper interface.
///
/// Provides Implementor, an interface implemented by G::Object instances wanting to access their Atk::Object implementation.

#ifndef XFC_ATK_IMPLEMENTOR_HH
#define XFC_ATK_IMPLEMENTOR_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __ATK_OBJECT_H__
#include <atk/atkobject.h>
#endif

namespace Xfc {

namespace Atk {

class Object;

/// @class Implementor implementor.hh xfc/atk/implementor.hh
/// @brief An AtkImplementor C++ wrapper class.
///
/// Implementor is an interface providing access to a G::Object's Atk::Object implementation.
/// This interface is implemented by Gtk::Widget (see ref_accessible()).

class Implementor : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Implementor();
	///< Constructs a new Implementor object.
	
	virtual ~Implementor() = 0;
	///< Destructor.
	
/// @}

public:
/// @name Accessors
/// @{

	AtkImplementor* atk_implementor() const;
	///< Get a pointer to the AtkImplementor structure.

	operator AtkImplementor* () const;
	///< Conversion operator; safely converts an Implementor to an AtkImplementor pointer.

	Pointer<Object> ref_accessible() const;
	///< Gets a reference to an object's Atk::Object implementation,
	///< if the object implements the Implementor interface.
	///< @return A smart pointer to an object's Atk::Object implementation.
	///<
	///< Gtk::Widget implements this interface. Calling Gtk::Widget::get_accessible()
	///< is the same calling this method on a widget, except this method  returns a
	///< smart pointer because it increments the Atk::Object's reference count,
	///< get_accessible() does not.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/implementor.inl>

#endif // XFC_ATK_IMPLEMENTOR_HH

