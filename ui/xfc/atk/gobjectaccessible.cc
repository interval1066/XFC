/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  gobjectaccessible.cc - AtkGObjectAccessible C++ wrapper implmentation
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

#include "gobjectaccessible.hh"
#include "private/gobjectaccessibleclass.hh"
#include "xfc/glib/object.hh"

using namespace Xfc;

/*  Atk::GObjectAccessible
 */

Atk::GObjectAccessible::GObjectAccessible(AtkGObjectAccessible *object, bool owns_reference)
: Atk::Object((AtkObject*)object, owns_reference)
{
}

Atk::GObjectAccessible::~GObjectAccessible()
{
}

Atk::Object*
Atk::GObjectAccessible::for_object(G::Object& object)
{
	return G::Object::wrap<Atk::Object>(atk_gobject_accessible_for_object(object.g_object()));
}

G::Object*
Atk::GObjectAccessible::get_object() const
{
	return G::Object::wrap<G::Object>(atk_gobject_accessible_get_object (atk_gobject_accessible()));
}

/*  Atk::GObjectAccessibleClass
 */

void
Atk::GObjectAccessibleClass::init(AtkGObjectAccessibleClass *g_class)
{
	ObjectClass::init((AtkObjectClass*)g_class);
}

GType
Atk::GObjectAccessibleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(ATK_TYPE_GOBJECT_ACCESSIBLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Atk::GObjectAccessibleClass::create()
{
	return g_object_new(get_type(), 0);
}

