/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  pixbuf-animation.inl - Gdk::PixbufAnimationIter and Gdk::PixbufAnimation inline functions
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

/*  Gdk::PixbufAnimationIter
 */

inline GdkPixbufAnimationIter*
Xfc::Gdk::PixbufAnimationIter::gdk_pixbuf_animation_iter() const
{
	return reinterpret_cast<GdkPixbufAnimationIter*>(instance_);
}

inline Xfc::Gdk::PixbufAnimationIter::operator GdkPixbufAnimationIter* () const
{
	return this ? gdk_pixbuf_animation_iter() : 0;
}

inline bool
Xfc::Gdk::PixbufAnimationIter::on_currently_loading_frame() const
{
	return gdk_pixbuf_animation_iter_on_currently_loading_frame(gdk_pixbuf_animation_iter());
}

/*  Gdk::PixbufAnimation
 */

inline GdkPixbufAnimation*
Xfc::Gdk::PixbufAnimation::gdk_pixbuf_animation() const
{
	return reinterpret_cast<GdkPixbufAnimation*>(instance_);
}

inline Xfc::Gdk::PixbufAnimation::operator GdkPixbufAnimation* () const
{
	return this ? gdk_pixbuf_animation() : 0;
}

inline int
Xfc::Gdk::PixbufAnimation::get_width() const
{
	return gdk_pixbuf_animation_get_width(gdk_pixbuf_animation());
}

inline int
Xfc::Gdk::PixbufAnimation::get_height() const
{
	return gdk_pixbuf_animation_get_height(gdk_pixbuf_animation());
}

inline bool
Xfc::Gdk::PixbufAnimation::is_static_image() const
{
	return gdk_pixbuf_animation_is_static_image(gdk_pixbuf_animation());
}

