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

/// @file xfc/stackobject.hh
/// @brief A C++ base class for automatic (or stack) objects.
///
/// Provides StackObject, a base class that declares 'operator new' and 'operator delete'
/// private, thereby forcing dervied objects to be created on the stack.

#ifndef XFC_STACK_OBJECT_HH
#define XFC_STACK_OBJECT_HH

#ifndef _CPP_CSTDDEF
#include <cstddef>
#endif

namespace Xfc {

/// @class StackObject stackobject.hh xfc/stackobject.hh
/// @brief A C++ base class for automatic (or stack) objects.
///
/// StackObject is a base class for automatic (or stack) objects. The purpose
/// of this class is to declare 'operator new' and 'operator delete' private,
/// thereby forcing derived objects to be created on the stack.

class StackObject
{
	StackObject(const StackObject&);
	StackObject& operator=(const StackObject&);

	static void *operator new(size_t size);
	static void *operator new[](size_t size);

protected:
/// @name Constructors
/// @{

	StackObject();
	///< Construct a new stack object.

/// @}

public:
/// @name Constructors
/// @{

	~StackObject();
	///< Destructor.

/// @}
};

} // namespace Xfc

#endif // XFC_STACK_OBJECT_HH


