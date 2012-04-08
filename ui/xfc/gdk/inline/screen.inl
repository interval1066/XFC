/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  screen.inl - Gdk::Screen inline functions
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

inline GdkScreen*
Xfc::Gdk::Screen::gdk_screen() const
{
	return reinterpret_cast<GdkScreen*>(instance_);
}

inline Xfc::Gdk::Screen::operator GdkScreen* () const
{
	return this ? gdk_screen() : 0;
}

inline int
Xfc::Gdk::Screen::get_number() const
{
	return gdk_screen_get_number(gdk_screen());
}

inline int
Xfc::Gdk::Screen::get_width() const
{
	return gdk_screen_get_width(gdk_screen());
}

inline int
Xfc::Gdk::Screen::get_height() const
{
	return gdk_screen_get_height(gdk_screen());
}

inline int
Xfc::Gdk::Screen::get_width_mm() const
{
	return gdk_screen_get_width_mm(gdk_screen());
}

inline int
Xfc::Gdk::Screen::get_height_mm() const
{
	return gdk_screen_get_height_mm(gdk_screen());
}

inline int
Xfc::Gdk::Screen::get_n_monitors() const
{
	return gdk_screen_get_n_monitors(gdk_screen());
}

inline int
Xfc::Gdk::Screen::get_monitor_at_point(int x, int y) const
{
	return gdk_screen_get_monitor_at_point(gdk_screen(), x, y);
}

inline const Xfc::Gdk::Screen::SizeChangedSignalProxy
Xfc::Gdk::Screen::signal_size_changed()
{
	return SizeChangedSignalProxy(this, &size_changed_signal);
}

