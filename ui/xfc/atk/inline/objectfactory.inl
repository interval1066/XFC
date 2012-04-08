/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  objectfactory.inl - Atk::ObjectFactory inline functions
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

inline AtkObjectFactory*
Xfc::Atk::ObjectFactory::atk_object_factory() const
{
	return reinterpret_cast<AtkObjectFactory*>(instance_);
}

inline Xfc::Atk::ObjectFactory::operator AtkObjectFactory* () const
{
	return this ? atk_object_factory() : 0;
}

inline GType
Xfc::Atk::ObjectFactory::get_accessible_type() const
{
	return atk_object_factory_get_accessible_type(atk_object_factory());
}

inline void
Xfc::Atk::ObjectFactory::invalidate()
{
	atk_object_factory_invalidate(atk_object_factory());
}

