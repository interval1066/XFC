/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  boxed.cc - Boxed type C++ wraper implementation.
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

#include "boxed.hh"

using namespace Xfc;

G::Boxed::Boxed(GType boxed_type)
: boxed_type_(boxed_type), can_free(false), boxed_(0)
{
}

G::Boxed::Boxed(GType boxed_type, void *boxed)
: boxed_type_(boxed_type), can_free(false), boxed_(boxed)
{
}

G::Boxed::Boxed(GType boxed_type, void *boxed, bool copy)
: boxed_type_(boxed_type), can_free(true)
{
	boxed_ = copy ? g_boxed_copy(boxed_type_, boxed) : boxed;
}

G::Boxed::~Boxed()
{
	if (boxed_ && can_free)
		g_boxed_free(boxed_type_, boxed_);
	boxed_ = 0;
}

void
G::Boxed::copy(const Boxed& src)
{
	g_return_if_fail(src.boxed_type_ == boxed_type_);

	if (boxed_ && can_free)
		g_boxed_free(boxed_type_, boxed_);

	boxed_ = g_boxed_copy(boxed_type_, src.boxed_);
	can_free = true;
}

void
G::Boxed::copy(const void *boxed)
{
	boxed_ = g_boxed_copy(boxed_type_, boxed);
	can_free = true;
}

