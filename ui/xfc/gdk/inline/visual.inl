/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  visual.inl - Gdk::Visual inline functions
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

inline GdkVisual*
Xfc::Gdk::Visual::gdk_visual() const
{
	return reinterpret_cast<GdkVisual*>(instance_);
}

inline Xfc::Gdk::Visual::operator GdkVisual* () const
{
	return this ? gdk_visual() : 0;
}

inline Xfc::Gdk::VisualType
Xfc::Gdk::Visual::type() const
{
	return (VisualType)gdk_visual()->type;
}

inline int
Xfc::Gdk::Visual::depth() const
{
	return gdk_visual()->depth;
}

inline Xfc::Gdk::ByteOrder
Xfc::Gdk::Visual::byte_order() const
{
	return (ByteOrder)gdk_visual()->byte_order;
}

inline int
Xfc::Gdk::Visual::colormap_size() const
{
	return gdk_visual()->colormap_size;
}

inline int
Xfc::Gdk::Visual::bits_per_rgb() const
{
	return gdk_visual()->bits_per_rgb;
}

inline unsigned int
Xfc::Gdk::Visual::red_mask() const
{
	return gdk_visual()->red_mask;
}

inline int
Xfc::Gdk::Visual::red_shift() const
{
	return gdk_visual()->red_shift;
}

inline int
Xfc::Gdk::Visual::red_prec() const
{
	return gdk_visual()->red_prec;
}

inline unsigned int
Xfc::Gdk::Visual::green_mask() const
{
	return gdk_visual()->green_mask;
}

inline int
Xfc::Gdk::Visual::green_shift() const
{
	return gdk_visual()->green_shift;
}

inline int
Xfc::Gdk::Visual::green_prec() const
{
	return gdk_visual()->green_prec;
}

inline unsigned int
Xfc::Gdk::Visual::blue_mask() const
{
	return gdk_visual()->blue_mask;
}

inline int
Xfc::Gdk::Visual::blue_shift() const
{
	return gdk_visual()->blue_shift;
}

inline int
Xfc::Gdk::Visual::blue_prec() const
{
	return gdk_visual()->blue_prec;
}

inline int
Xfc::Gdk::Visual::get_best_depth() const
{
	return gdk_visual_get_best_depth();
}

inline Xfc::Gdk::VisualType
Xfc::Gdk::Visual::get_best_type() const
{
	return (VisualType)gdk_visual_get_best_type();
}

