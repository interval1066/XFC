/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  pixbuf.inl - Gdk::PixbufFormat and Gdk::Pixbuf inline functions
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

inline GdkPixbuf*
Xfc::Gdk::Pixbuf::gdk_pixbuf() const
{
	return reinterpret_cast<GdkPixbuf*>(instance_);
}

inline Xfc::Gdk::Pixbuf::operator GdkPixbuf* () const
{
	return this ? gdk_pixbuf() : 0;
}

inline Xfc::Gdk::Colorspace
Xfc::Gdk::Pixbuf::get_colorspace() const
{
	return (Colorspace)gdk_pixbuf_get_colorspace(gdk_pixbuf());
}

inline int
Xfc::Gdk::Pixbuf::get_n_channels() const
{
	return gdk_pixbuf_get_n_channels(gdk_pixbuf());
}

inline bool
Xfc::Gdk::Pixbuf::get_has_alpha() const
{
	return gdk_pixbuf_get_has_alpha(gdk_pixbuf());
}

inline int
Xfc::Gdk::Pixbuf::get_bits_per_sample() const
{
	return gdk_pixbuf_get_bits_per_sample(gdk_pixbuf());
}

inline unsigned char*
Xfc::Gdk::Pixbuf::get_pixels() const
{
	return gdk_pixbuf_get_pixels(gdk_pixbuf());
}

inline int
Xfc::Gdk::Pixbuf::get_width() const
{
	return gdk_pixbuf_get_width(gdk_pixbuf());
}

inline int
Xfc::Gdk::Pixbuf::get_height() const
{
	return gdk_pixbuf_get_height(gdk_pixbuf());
}

inline int
Xfc::Gdk::Pixbuf::get_rowstride() const
{
	return gdk_pixbuf_get_rowstride(gdk_pixbuf());
}

inline void
Xfc::Gdk::Pixbuf::fill(unsigned int pixel)
{
	gdk_pixbuf_fill(gdk_pixbuf(), pixel);
}

