/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  display.inl - Gdk::Display inline functions
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

inline GdkDisplay*
Xfc::Gdk::Display::gdk_display() const
{
	return reinterpret_cast<GdkDisplay*>(instance_);
}

inline Xfc::Gdk::Display::operator GdkDisplay* () const
{
	return this ? gdk_display() : 0;
}

inline int
Xfc::Gdk::Display::get_n_screens() const
{
	return gdk_display_get_n_screens(gdk_display());
}

inline bool
Xfc::Gdk::Display::pointer_is_grabbed() const
{
	return gdk_display_pointer_is_grabbed(gdk_display());
}

inline bool
Xfc::Gdk::Display::supports_cursor_alpha() const
{
	return gdk_display_supports_cursor_alpha(gdk_display());
}

inline bool
Xfc::Gdk::Display::supports_cursor_color() const
{
	return gdk_display_supports_cursor_color((GdkDisplay*)instance_);
}

inline unsigned int
Xfc::Gdk::Display::get_default_cursor_size() const
{
	return gdk_display_get_default_cursor_size(gdk_display());
}

inline void
Xfc::Gdk::Display::get_maximal_cursor_size(unsigned int *width, unsigned int *height) const
{
	gdk_display_get_maximal_cursor_size(gdk_display(), width, height);
}

inline bool 
Xfc::Gdk::Display::supports_selection_notification() const
{
	return gdk_display_supports_selection_notification(gdk_display());
}

inline bool
Xfc::Gdk::Display::supports_clipboard_persistence() const
{
	return gdk_display_supports_clipboard_persistence(gdk_display());
}

inline void
Xfc::Gdk::Display::pointer_ungrab(unsigned int time)
{
	gdk_display_pointer_ungrab(gdk_display(), time);
}

inline void
Xfc::Gdk::Display::keyboard_ungrab(unsigned int time)
{
	gdk_display_keyboard_ungrab(gdk_display(), time);
}

inline void
Xfc::Gdk::Display::beep()
{
	gdk_display_beep(gdk_display());
}

inline void
Xfc::Gdk::Display::sync()
{
	gdk_display_sync(gdk_display());
}

inline void
Xfc::Gdk::Display::flush()
{
	gdk_display_flush(gdk_display());
}

inline void
Xfc::Gdk::Display::close()
{
	gdk_display_close(gdk_display());
}

inline void
Xfc::Gdk::Display::add_client_message_filter(Atom message_type, GdkFilterFunc func, void *data)
{
	gdk_display_add_client_message_filter(gdk_display(), message_type, func, data);
}

inline void
Xfc::Gdk::Display::set_double_click_time(unsigned int msec)
{
	gdk_display_set_double_click_time(gdk_display(), msec);
}

inline void 
Xfc::Gdk::Display::set_double_click_distance(unsigned int distance)
{
	gdk_display_set_double_click_distance(gdk_display(), distance);
}

inline bool 
Xfc::Gdk::Display::request_selection_notification(Atom selection)
{
	return gdk_display_request_selection_notification(gdk_display(), selection);
}
	
inline const Xfc::Gdk::Display::ClosedSignalProxy
Xfc::Gdk::Display::signal_closed()
{
	return ClosedSignalProxy(this, &closed_signal);
}

