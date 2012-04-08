/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  color.inl - Gdk::Color and Gdk::Colormap inline functions
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

/*  Gdk::Color
 */

inline GdkColor*
Xfc::Gdk::Color::gdk_color() const
{
	return reinterpret_cast<GdkColor*>(boxed_);
}

inline Xfc::Gdk::Color::operator GdkColor* () const
{
	return this ? gdk_color() : 0;
}

inline double
Xfc::Gdk::Color::red() const
{
	return gdk_color()->red / 65535.0;
}

inline double
Xfc::Gdk::Color::green() const
{
	return gdk_color()->green / 65535.0;
}

inline double
Xfc::Gdk::Color::blue() const
{
	return gdk_color()->blue / 65535.0;
}

inline unsigned short
Xfc::Gdk::Color::get_red() const
{
	return gdk_color()->red;
}

inline unsigned short
Xfc::Gdk::Color::get_green() const
{
	return gdk_color()->green;
}

inline unsigned short
Xfc::Gdk::Color::get_blue() const
{
	return gdk_color()->blue;
}

inline unsigned long
Xfc::Gdk::Color::get_pixel() const
{
	return gdk_color()->pixel;
}

inline void
Xfc::Gdk::Color::red(double r)
{
	gdk_color()->red = (unsigned short)(r * 65535.0);
}

inline void
Xfc::Gdk::Color::green(double g)
{
	gdk_color()->green = (unsigned short)(g * 65535.0);
}

inline void
Xfc::Gdk::Color::blue(double b)
{
	gdk_color()->blue = (unsigned short)(b * 65535.0);
}

inline void
Xfc::Gdk::Color::set_red(unsigned short r)
{
	gdk_color()->red = r;
}

inline void
Xfc::Gdk::Color::set_green(unsigned short g)
{
	gdk_color()->green = g;
}

inline void
Xfc::Gdk::Color::set_blue(unsigned short b)
{
	gdk_color()->blue = b;
}

inline void
Xfc::Gdk::Color::set_pixel(unsigned long p)
{
	gdk_color()->pixel = p;
}

inline bool
Xfc::Gdk::Color::parse(const char *spec)
{
	return gdk_color_parse(spec, gdk_color());
}

inline unsigned int
Xfc::Gdk::Color::hash() const
{
	return gdk_color_hash(gdk_color());
}

/*  Gdk::Colormap
 */

inline GdkColormap*
Xfc::Gdk::Colormap::gdk_colormap() const
{
	return reinterpret_cast<GdkColormap*>(instance_);
}

inline Xfc::Gdk::Colormap::operator GdkColormap* () const
{
	return this ? gdk_colormap() : 0;
}

