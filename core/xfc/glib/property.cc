/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  property.cc - GObject properties C++ wrapper implementation
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

#include "property.hh"
#include "object.hh"

using namespace Xfc;

G::PropertyBase::PropertyBase(const char* name)
: name_(name)
{
}

G::PropertyBase::~PropertyBase()
{
}

GParamSpec*
G::PropertyBase::find_property(const Object *object) const
{
	return g_object_class_find_property(G_OBJECT_GET_CLASS(object->g_object()), name_);
}

void
G::PropertyBase::get_property(const Object *object, Value& value) const
{
	g_object_get_property(object->g_object(), name_, value.g_value());
}

void
G::PropertyBase::set_property(const Object *object, Value& value) const
{
	g_object_set_property(object->g_object(), name_, value.g_value());
}

