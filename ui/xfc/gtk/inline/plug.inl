/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  plug.inl - Gtk::Plug inline functions
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

inline GtkPlug*
Xfc::Gtk::Plug::gtk_plug() const
{
	return reinterpret_cast<GtkPlug*>(instance_);
}

inline Xfc::Gtk::Plug::operator GtkPlug* () const
{
	return this ? gtk_plug() : 0;
}

inline bool
Xfc::Gtk::Plug::same_app() const
{
	return gtk_plug()->same_app;
}

inline GdkNativeWindow
Xfc::Gtk::Plug::get_id() const
{
	return gtk_plug_get_id(gtk_plug());
}

inline const Xfc::Gtk::Plug::EmbeddedSignalProxy
Xfc::Gtk::Plug::signal_embedded()
{
	return EmbeddedSignalProxy(this, &embedded_signal);
}

