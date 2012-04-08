/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  object.cc - Reference counted base class for dynamic objects handled the XFC smart pointer.
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

#include "object.hh"

using namespace Xfc;

/*  Object
 */

Object::Object()
{
	ref_count = 1;
	set_owns_reference(true);
}

Object::~Object()
{
}

void
Object::ref()
{
	++ref_count;
}

void
Object::unref()
{
	if (--ref_count == 0 && is_dynamic())
		delete this;
}

