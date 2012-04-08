/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  fixed.inl - Gtk::Fixed inline functions
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

inline GtkFixed*
Xfc::Gtk::Fixed::gtk_fixed() const
{
	return reinterpret_cast<GtkFixed*>(instance_);
}

inline Xfc::Gtk::Fixed::operator GtkFixed* () const
{
	return this ? gtk_fixed() : 0;
}

inline bool
Xfc::Gtk::Fixed::get_has_window() const
{
	return gtk_fixed_get_has_window(gtk_fixed());
}

inline void
Xfc::Gtk::Fixed::set_has_window(bool has_window)
{
	gtk_fixed_set_has_window(gtk_fixed(), has_window);
}

