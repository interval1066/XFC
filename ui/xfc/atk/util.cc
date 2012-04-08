/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  util.cc - AtkUtil C++ wrapper implementation
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
 
#include "util.hh"
#include "object.hh"
#include <atk/atkrelation.h>

using namespace Xfc;

Atk::RelationType
Atk::relation_type_register(const String& name)
{
	return (RelationType)atk_relation_type_register(name.c_str());
}

String
Atk::relation_type_get_name(RelationType type)
{
	return atk_relation_type_get_name((AtkRelationType)type);
}

Atk::RelationType
Atk::relation_type_for_name(const String& name)
{
	return (RelationType)atk_relation_type_for_name(name.c_str());
}

Atk::Object*
Atk::get_root()
{
	AtkObject *accessible = atk_get_root();
	return accessible ? G::Object::wrap<Atk::Object>(accessible) : 0;
}

Atk::Object*
Atk::get_focus_object()
{
	AtkObject *accessible = atk_get_focus_object();
	return accessible ? G::Object::wrap<Atk::Object>(accessible) : 0;
}

String
Atk::get_toolkit_name()
{
	return atk_get_toolkit_name();
}

String
Atk::get_toolkit_version()
{
	return atk_get_toolkit_version();
}

