/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  accelmap.inl - Gtk::AccelMap inline functions
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

inline GtkAccelMap*
Xfc::Gtk::AccelMap::gtk_accel_map() const
{
	return reinterpret_cast<GtkAccelMap*>(instance_);
}

inline
Xfc::Gtk::AccelMap::operator GtkAccelMap* () const
{
	return this ? gtk_accel_map() : 0;
}

inline bool
Xfc::Gtk::AccelMap::lookup_entry(const char *accel_path, AccelKey *accel_key)
{
	return gtk_accel_map_lookup_entry(accel_path, *accel_key);
}

inline void
Xfc::Gtk::AccelMap::load(const char *filename)
{
	gtk_accel_map_load(filename);
}

inline void
Xfc::Gtk::AccelMap::load(int file_descriptor)
{
	gtk_accel_map_load_fd(file_descriptor);
}

inline void
Xfc::Gtk::AccelMap::save(const char *filename)
{
	gtk_accel_map_save(filename);
}

inline void
Xfc::Gtk::AccelMap::save(int file_descriptor)
{
	gtk_accel_map_save_fd(file_descriptor);
}

inline void
Xfc::Gtk::AccelMap::lock_path(const char *accel_path)
{
	gtk_accel_map_lock_path(accel_path);
}

inline void
Xfc::Gtk::AccelMap::unlock_path(const char *accel_path)
{
	gtk_accel_map_unlock_path(accel_path);
}

inline const Xfc::Gtk::AccelMap::ChangedSignalProxy 
Xfc::Gtk::AccelMap::signal_changed(const char *accel_path)
{
	return ChangedSignalProxy(this, &changed_signal, accel_path);
}

inline const Xfc::Gtk::AccelMap::ChangedSignalProxy 
Xfc::Gtk::AccelMap::signal_changed(const String& accel_path)
{
	return ChangedSignalProxy(this, &changed_signal, accel_path.c_str());
}










