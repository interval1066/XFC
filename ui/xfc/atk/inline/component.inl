/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  component.inl - Atk::Component inline functions
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

inline AtkComponent*
Xfc::Atk::Component::atk_component() const
{
	return reinterpret_cast<AtkComponent*>(instance_);
}

inline Xfc::Atk::Component::operator AtkComponent* () const
{
	return this ? atk_component() : 0;
}

inline void
Xfc::Atk::Component::get_extents(int *x, int *y, int *width, int *height, CoordType coord_type) const
{
	atk_component_get_extents((AtkComponent*)instance_, x, y, width, height, (AtkCoordType)coord_type);
}

inline void
Xfc::Atk::Component::get_position(int *x, int *y, CoordType coord_type) const
{
	atk_component_get_position(atk_component(), x, y, (AtkCoordType)coord_type);

}

inline void
Xfc::Atk::Component::get_size(int *width, int *height) const
{
	atk_component_get_size(atk_component(), width, height);
}

inline Xfc::Atk::Layer
Xfc::Atk::Component::get_layer() const
{
	return (Layer)atk_component_get_layer(atk_component());
}

inline int
Xfc::Atk::Component::get_mdi_zorder() const
{
	return atk_component_get_mdi_zorder(atk_component());
}

inline unsigned int
Xfc::Atk::Component::add_focus_handler(AtkFocusHandler handler)
{
	return atk_component_add_focus_handler(atk_component(), handler);
}

inline bool
Xfc::Atk::Component::contains(int x, int y, CoordType coord_type) const
{
	return atk_component_contains(atk_component(), x, y, (AtkCoordType)coord_type);
}

inline bool
Xfc::Atk::Component::grab_focus()
{
	return atk_component_grab_focus(atk_component());
}

inline void
Xfc::Atk::Component::remove_focus_handler(unsigned int handler_id)
{
	atk_component_remove_focus_handler(atk_component(), handler_id);
}

inline bool
Xfc::Atk::Component::set_extents(int x, int y, int width, int height, CoordType coord_type)
{
	return atk_component_set_extents(atk_component(), x, y, width, height, (AtkCoordType)coord_type);
}

inline bool
Xfc::Atk::Component::set_position(int x, int y, CoordType coord_type)
{
	return atk_component_set_position(atk_component(), x, y, (AtkCoordType)coord_type);
}

inline bool
Xfc::Atk::Component::set_size(int width, int height)
{
	return atk_component_set_size(atk_component(), width, height);
}

