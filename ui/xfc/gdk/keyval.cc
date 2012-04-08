/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  keyval.cc - A C++ interface for GDK key values
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
 
#include "keyval.hh"

#ifndef GDK_VoidSymbol
#define GDK_VoidSymbol 0xFFFFFF
#endif

using namespace Xfc;

/*  Gdk::Keyval
 */

Gdk::Keyval::Keyval()
: Base(GDK_VoidSymbol)
{
}

Gdk::Keyval::Keyval(unsigned int keyval)
: Base(keyval)
{
}

Gdk::Keyval::Keyval(const char *keyval_name)
: Base(gdk_keyval_from_name(keyval_name))
{
}

Gdk::Keyval::Keyval(const String& keyval_name)
: Base(gdk_keyval_from_name(keyval_name.c_str()))
{
}

Gdk::Keyval::Keyval(const Keyval& src)
: Base(src.value_)
{
}

Gdk::Keyval& 
Gdk::Keyval::operator=(const Keyval& src)
{
	value_ = src.value_;
	return *this;
}

bool
Gdk::Keyval::is_keyval() const
{
	return value_ && value_ != GDK_VoidSymbol;
}

String
Gdk::Keyval::name() const
{
	return gdk_keyval_name(value_);
}

void
Gdk::Keyval::convert_case(Keyval& lower, Keyval& upper)
{
	unsigned int l, u;
	gdk_keyval_convert_case(value_, &l, &u);
	lower = l;
	upper = u;
}

Gdk::Keyval
Gdk::Keyval::to_upper() const
{
	return gdk_keyval_to_upper(value_);
}

Gdk::Keyval
Gdk::Keyval::to_lower() const
{
	return gdk_keyval_to_lower(value_);
}

G::Unichar
Gdk::Keyval::to_unicode() const
{
	return gdk_keyval_to_unicode(value_);
}

void 
Gdk::Keyval::from_unicode(const G::Unichar& wc)
{
	unsigned int value = gdk_unicode_to_keyval(wc);
	value_ = (value != (wc | 0x01000000)) ? value : GDK_VoidSymbol;
}

