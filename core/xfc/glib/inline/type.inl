/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  type.inl - G::TypeInstance and G::TypeInterface inline functions
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

/*  G::TypeTnstance
 */

inline GTypeInstance*
Xfc::G::TypeInstance::g_type_instance() const
{
	return instance_;
}

inline GType
Xfc::G::TypeInstance::type() const
{
	return G_TYPE_FROM_INSTANCE(instance_);
}

/*  G::TypeInterface
 */

inline bool
Xfc::G::TypeInterface::is_interface(GType type)
{
	return G_TYPE_IS_INTERFACE(type);
}

inline GTypeInterface*
Xfc::G::TypeInterface::g_type_interface(GType type) const
{
	return G_TYPE_INSTANCE_GET_INTERFACE(instance_, type, GTypeInterface);
}

