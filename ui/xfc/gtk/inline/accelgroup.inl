/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  accelgroup.inl - Accelerator and Gtk::AccelGroup inline functions
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


inline Xfc::Gdk::ModifierTypeField
Xfc::Gtk::accelerator_get_default_mod_mask()
{
	return gtk_accelerator_get_default_mod_mask();
}

inline void
Xfc::Gtk::accelerator_set_default_mod_mask(Gdk::ModifierTypeField default_mod_mask)
{
	gtk_accelerator_set_default_mod_mask((GdkModifierType)default_mod_mask);
}

inline Xfc::Gtk::AccelKey
Xfc::Gtk::accelerator_parse(const char *accelerator, AccelFlagsField accel_flags)
{
	return AccelKey(accelerator, accel_flags);
}

/*  Gtk::AccelGroup
 */

inline GtkAccelGroup*
Xfc::Gtk::AccelGroup::gtk_accel_group() const
{
	return reinterpret_cast<GtkAccelGroup*>(instance_);
}

inline
Xfc::Gtk::AccelGroup::operator GtkAccelGroup* () const
{
	return this ? gtk_accel_group() : 0;
}

inline void
Xfc::Gtk::AccelGroup::lock()
{
	gtk_accel_group_lock(gtk_accel_group());
}

inline void
Xfc::Gtk::AccelGroup::unlock()
{
	gtk_accel_group_unlock(gtk_accel_group());
}

inline void
Xfc::Gtk::AccelGroup::connect(const char *accel_path, GClosure *closure)
{
	gtk_accel_group_connect_by_path(gtk_accel_group(), accel_path, closure);
}

inline bool
Xfc::Gtk::AccelGroup::disconnect(GClosure *closure)
{
	return gtk_accel_group_disconnect(gtk_accel_group(), closure);
}

inline const Xfc::Gtk::AccelGroup::AccelChangedSignalProxy
Xfc::Gtk::AccelGroup::signal_accel_changed()
{
	return AccelChangedSignalProxy(this, &accel_changed_signal);
}

