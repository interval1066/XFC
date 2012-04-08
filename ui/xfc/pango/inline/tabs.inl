/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  tabs.inl - Pango::TabArray inline functions
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

inline PangoTabArray*
Xfc::Pango::TabArray::pango_tab_array() const
{
	return reinterpret_cast<PangoTabArray*>(boxed_);
}

inline Xfc::Pango::TabArray::operator PangoTabArray* () const
{
	return this ? pango_tab_array() : 0;
}

inline bool
Xfc::Pango::TabArray::get_positions_in_pixels() const
{
	return pango_tab_array_get_positions_in_pixels(pango_tab_array());
}

inline void
Xfc::Pango::TabArray::resize(int new_size)
{
	pango_tab_array_resize(pango_tab_array(), new_size);
}

inline void
Xfc::Pango::TabArray::set_tab(int tab_index, int location, TabAlign alignment)
{
	pango_tab_array_set_tab(pango_tab_array(), tab_index, (PangoTabAlign)alignment, location);
}

