/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  pixbuf-io.inl - Gdk::PixbufFormat inline functions
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

inline GdkPixbufFormat*
Xfc::Gdk::PixbufFormat::gdk_pixbuf_format() const
{
	return format_;
}

inline bool
Xfc::Gdk::PixbufFormat::is_writable() const
{
	return gdk_pixbuf_format_is_writable(format_);
}

inline bool 
Xfc::Gdk::PixbufFormat::is_scalable() const
{
	return gdk_pixbuf_format_is_scalable(gdk_pixbuf_format());
}

inline bool 
Xfc::Gdk::PixbufFormat::is_disabled() const
{
	return gdk_pixbuf_format_is_disabled(gdk_pixbuf_format());
}

inline void 
Xfc::Gdk::PixbufFormat::set_disabled(bool disabled)
{
	gdk_pixbuf_format_set_disabled(gdk_pixbuf_format(), disabled);
}

