/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  socket.inl - Gtk::Socket inline functions
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

inline GtkSocket*
Xfc::Gtk::Socket::gtk_socket() const
{
	return reinterpret_cast<GtkSocket*>(instance_);
}

inline Xfc::Gtk::Socket::operator GtkSocket* () const
{
	return this ? gtk_socket() : 0;
}

inline bool
Xfc::Gtk::Socket::has_plug() const
{
	return GDK_IS_WINDOW(gtk_socket()->plug_window);
}

inline bool
Xfc::Gtk::Socket::same_app() const
{
	return gtk_socket()->same_app;
}

inline GdkNativeWindow
Xfc::Gtk::Socket::get_id() const
{
	return gtk_socket_get_id(gtk_socket());
}

inline void
Xfc::Gtk::Socket::add_id(GdkNativeWindow window_id)
{
	gtk_socket_add_id(gtk_socket(), window_id);
}

inline const Xfc::Gtk::Socket::PlugAddedSignalProxy
Xfc::Gtk::Socket::signal_plug_added()
{
	return PlugAddedSignalProxy(this, &plug_added_signal);
}

inline const Xfc::Gtk::Socket::PlugRemovedSignalProxy
Xfc::Gtk::Socket::signal_plug_removed()
{
	return PlugRemovedSignalProxy(this, &plug_removed_signal);
}

