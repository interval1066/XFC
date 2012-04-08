/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  type.cc - TypeInstance implementation
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
 
#include "type.hh"

using namespace Xfc;

/*  G::TypeInstance
 */

G::TypeInstance::TypeInstance()
: instance_(0)
{
}

G::TypeInstance::~TypeInstance()
{
}

bool
G::TypeInstance::is_a(GType is_a_type) const
{
	return g_type_is_a(type(), is_a_type);
}

String
G::TypeInstance::type_name() const
{
	return g_type_name(type());
}

GType
G::TypeInstance::parent_type() const
{
	return g_type_parent(type());
}

void
G::TypeInstance::add_interface(GType interface_type, GInterfaceInitFunc interface_init)
{
	add_interface(type(), interface_type, interface_init);
}

void
G::TypeInstance::add_interface(GType instance_type, GType interface_type, GInterfaceInitFunc interface_init)
{
	const GInterfaceInfo info =
	{
		interface_init,
		0, // GInterfaceFinalizeFunc
		0  // interface data
	};

	g_type_add_interface_static(instance_type, interface_type, &info);
}

GType
G::TypeInstance::register_type(GType parent_type, GClassInitFunc class_init)
{
	GType type = 0;
	GTypeQuery query;
	g_type_query(parent_type, &query);

	if (query.type)
	{
		const GTypeInfo info =
		{
			query.class_size,
			0, // GBaseInitFunc
			0, // GBaseFinalizeFunc
			class_init,
			0, // class_finalize
			0, // class_data
			query.instance_size, 
			0, // n_preallocs
			0,  // GInstanceInitFunc
			0, // value_table
		};

		String type_name("Xfc_");
		type_name.append(query.type_name);
		type = g_type_register_static(parent_type, type_name.c_str(), &info, GTypeFlags(0));
	}
	return type;
}

/*  G::TypeInterface
 */

G::TypeInterface::TypeInterface()
{
}

G::TypeInterface::~TypeInterface()
{
}

