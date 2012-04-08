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

/// @file xfc/atk/gobjectaccessible.hh
/// @brief An AtkGObjectAccessible C++ wrapper interface.
///
/// Provides GObjectAccessible, an object class derived from Atk::Object that can be used
/// as a basis for implementing accessible objects.

#ifndef XFC_ATK_GOBJECT_ACCESSIBLE_HH
#define XFC_ATK_GOBJECT_ACCESSIBLE_HH

#ifndef XFC_ATK_OBJECT_HH
#include <xfc/atk/object.hh>
#endif

#ifndef __ATK_GOBJECT_ACCESSIBLE_H__
#include <atk/atkgobjectaccessible.h>
#endif

namespace Xfc {

namespace G {
class Object;
}

namespace Atk {

/// @class GObjectAccessible gobjectaccessible.hh xfc/atk/gobjectaccessible.hh
/// @brief An AtkGObjectAccessible C++ wrapper class.
///
/// This object class is derived from Atk::Object. It can be used as a basis for implementing
/// accessible objects for G::Objects which are not derived from Gtk::Widget. One example of
/// its use is in providing an accessible object for GnomeCanvasItem in the GAIL library.

class GObjectAccessible : public Atk::Object
{
	friend class G::Object;

	GObjectAccessible(const GObjectAccessible&);
	GObjectAccessible& operator=(const GObjectAccessible&);

protected:
/// @name Constructors
/// @{

	explicit GObjectAccessible(AtkGObjectAccessible *object, bool owns_reference = true);
	///< Construct a new GObjectAccessible from an existing AtkGObjectAccessible.
	///< @param object A pointer to a AtkGObjectAccessible.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>object</EM> can be a newly created AtkGObjectAccessible or an existing
	///< AtkGObjectAccessible. (see G::Object::Object).

/// @}

public:
	typedef GObjectAccessible CObjectType;

/// @name Constructors
/// @{

	virtual ~GObjectAccessible();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	AtkGObjectAccessible* atk_gobject_accessible() const;
	///< Get a pointer to the AtkGObjectAccessible structure.

	operator AtkGObjectAccessible* () const;
	///< Conversion operator; safely converts a GObjectAccessible to an AtkGObjectAccessible pointer.

	G::Object* get_object() const;
	///< Gets the G::Object for this accessible object.
	///< @return A G::Object which is the object for this accessible object.

/// @}
/// @name Accessors
/// @{


	static Object* for_object(G::Object& object);
	///< Gets the accessible object for the specified G::Object.
	///< @param object A G::Object.
	///< @return An Atk::Object which is the accessible object for <EM>object</EM>.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/gobjectaccessible.inl>

#endif // XFC_ATK_GOBJECT_ACCESSIBLE_HH

