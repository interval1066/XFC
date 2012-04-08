/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  drawable.inl - Gdk::Drawable inline functions
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

inline GdkDrawable*
Xfc::Gdk::Drawable::gdk_drawable() const
{
	return reinterpret_cast<GdkDrawable*>(instance_);
}

inline Xfc::Gdk::Drawable::operator GdkDrawable* () const
{
	return this ? gdk_drawable() : 0;
}

inline int
Xfc::Gdk::Drawable::get_depth() const
{
	return gdk_drawable_get_depth(gdk_drawable());
}

