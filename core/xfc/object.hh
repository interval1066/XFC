/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/object.hh
/// @brief Reference counted base class interface.
///
/// Provides a reference counted base class for dynamic objects handled the XFC smart pointer.

#ifndef XFC_OBJECT_HH
#define XFC_OBJECT_HH

#ifndef XFC_TRACKABLE_HH
#include <xfc/trackable.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

namespace Xfc {

/// @class Object object.hh xfc/object.hh
/// @brief Reference counting base class.
///
/// Object is a base class that implements reference counting. Derived from Trackable, it
/// adds an integer reference counter so that dynamic objects can have their memory allocation
/// handled by the XFC smart pointer: Pointer<>. This keeps the memory management in XFC
/// consistent across all classes. If you derive a class from Xfc::Object and allocate it
/// on the heap, you free the memory and destroy the object by calling unref(), <B>not delete</B>.
///
/// Note if you declare a class that derives from Xfc::Object on the stack you don't
/// need to call unref(). It's not an error to do so though because nothing will happen.

class Object : public virtual Trackable
{
	Object(const Object&);
	Object& operator=(const Object&);

	int ref_count;

protected:
	Object();
	///< Constructor.

	virtual ~Object() = 0;
	///< Destructor.

public:
	virtual void ref();
	///< Increase an object's reference count by one.

	virtual void unref();
	///< Decrease an object's reference count by one.
	///< When the reference count becomes zero delete is called. Remember, with Object
	///< you must call unref() on dynmaically allocated objects, not delete.
};

} // namespace Xfc

#endif // XFC_OBJECT_HH

