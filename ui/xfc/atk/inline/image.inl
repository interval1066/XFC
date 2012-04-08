/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  image.inl - Atk::Image inline functions
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

inline AtkImage*
Xfc::Atk::Image::atk_image() const
{
	return reinterpret_cast<AtkImage*>(instance_);
}

inline Xfc::Atk::Image::operator AtkImage* () const
{
	return this ? atk_image() : 0;
}

inline void
Xfc::Atk::Image::get_image_size(int *height, int *width) const
{
	atk_image_get_image_size(atk_image(), height, width);
}

inline void
Xfc::Atk::Image::get_image_position(int *x, int *y, CoordType coord_type) const
{
	atk_image_get_image_position(atk_image(), x, y, (AtkCoordType)coord_type);
}

inline bool
Xfc::Atk::Image::set_image_description(const char *description)
{
	return atk_image_set_image_description(atk_image(), description);
}

