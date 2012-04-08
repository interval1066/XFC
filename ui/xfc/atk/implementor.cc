/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  implementor.cc - AtkImplementor C++ wrapper implementation
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
 
#include "implementor.hh"
#include "object.hh"

using namespace Xfc;

/*  Atk::Implementor
 */
 
Atk::Implementor::Implementor() 
{
}

Atk::Implementor::~Implementor() 
{
}
	
Pointer<Atk::Object>
Atk::Implementor::ref_accessible() const
{

	return G::Object::wrap<Atk::Object>(atk_implementor_ref_accessible(atk_implementor()), true);
}

