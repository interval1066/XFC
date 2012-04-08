/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  accelkey.inl - Gtk::AccelKey inline functions
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

inline GtkAccelKey*
Xfc::Gtk::AccelKey::gtk_accel_key() const
{
	return const_cast<GtkAccelKey*>(&key_);
}

inline
Xfc::Gtk::AccelKey::operator GtkAccelKey* () const
{
	return this ? const_cast<GtkAccelKey*>(&key_) : 0;
}

inline unsigned int
Xfc::Gtk::AccelKey::key() const
{
	return key_.accel_key;
}

inline Xfc::Gdk::ModifierTypeField
Xfc::Gtk::AccelKey::mods() const
{
	return key_.accel_mods;
}

inline Xfc::Gtk::AccelFlagsField
Xfc::Gtk::AccelKey::flags() const
{
	return key_.accel_flags;
}

