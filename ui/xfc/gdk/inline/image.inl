/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  image.inl - Gdk::Image inline functions
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

inline GdkImage*
Xfc::Gdk::Image::gdk_image() const
{
	return reinterpret_cast<GdkImage*>(instance_);
}

inline Xfc::Gdk::Image::operator GdkImage* () const
{
	return this ? gdk_image() : 0;
}

inline Xfc::Gdk::ImageType
Xfc::Gdk::Image::image_type() const
{
	return (ImageType)gdk_image()->type;
}

inline Xfc::Gdk::ByteOrder
Xfc::Gdk::Image::byte_order() const
{
	return (ByteOrder)gdk_image()->byte_order;
}

inline int
Xfc::Gdk::Image::width() const
{
	return gdk_image()->width;
}

inline int
Xfc::Gdk::Image::height() const
{
	return gdk_image()->height;
}

inline unsigned short
Xfc::Gdk::Image::depth() const
{
	return gdk_image()->depth;
}

inline unsigned short
Xfc::Gdk::Image::bytes_per_pixel() const
{
	return gdk_image()->bpp;
}

inline unsigned short
Xfc::Gdk::Image::bytes_per_line() const
{
	return gdk_image()->bpl;
}

inline unsigned int
Xfc::Gdk::Image::get_pixel(int x, int y) const
{
	return gdk_image_get_pixel(gdk_image(), x, y);
}

inline void
Xfc::Gdk::Image::put_pixel(int x, int y, unsigned int pixel)
{
	gdk_image_put_pixel(gdk_image(), x, y, pixel);
}

