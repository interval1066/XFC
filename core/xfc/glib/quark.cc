/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  quark.cc - GQuark C++ wrapper implementation
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
 
#include "quark.hh"

using namespace Xfc;

G::Quark::Quark(const char *str)
: Base(g_quark_from_string(str))
{
}

G::Quark::Quark(const String& str)
: Base(g_quark_from_string(str.c_str()))
{
}

G::Quark::Quark(GQuark quark)
: Base(quark)
{
}
	
G::Quark::Quark(const Quark& src) 
: Base(src.value_)
{
}
	
G::Quark& 
G::Quark::operator=(const Quark& src) 
{
	value_ = src.value_;
	return *this;
}

