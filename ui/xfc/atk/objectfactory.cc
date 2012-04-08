/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  objectfactory.cc - AtkObjectFactory C++ wrapper implementation
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
 
#include "objectfactory.hh"
#include "object.hh"
#include "private/objectfactoryclass.hh"

using namespace Xfc;

/*  Atk::ObjectFactory
 */

Atk::ObjectFactory::ObjectFactory(AtkObjectFactory *factory, bool owns_reference)
: G::Object((GObject*)factory, owns_reference)
{
}
	
Atk::ObjectFactory::~ObjectFactory() 
{
}
	
Atk::Object*
Atk::ObjectFactory::create_accessible(const G::Object& object)
{
	return G::Object::wrap<Atk::Object>(atk_object_factory_create_accessible(atk_object_factory(), object.g_object()));
}

/*  Atk::ObjectFactoryClass
 */

void
Atk::ObjectFactoryClass::init(AtkObjectFactoryClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Atk::ObjectFactoryClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(ATK_TYPE_OBJECT_FACTORY, (GClassInitFunc)&init);
	}
	return type;
}

void*
Atk::ObjectFactoryClass::create()
{
	return g_object_new(get_type(), 0);
}

