/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  registry.inl - Atk::Registry inline functions
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

inline AtkRegistry*
Xfc::Atk::Registry::atk_registry() const
{
	return reinterpret_cast<AtkRegistry*>(instance_);
}

inline Xfc::Atk::Registry::operator AtkRegistry* () const
{
	return this ? atk_registry() : 0;
}

inline GType
Xfc::Atk::Registry::get_factory_type(GType type) const
{
	return atk_registry_get_factory_type(atk_registry(), type);
}

inline void
Xfc::Atk::Registry::set_factory_type(GType type, GType factory_type)
{
 	atk_registry_set_factory_type(atk_registry(), type, factory_type);
}

