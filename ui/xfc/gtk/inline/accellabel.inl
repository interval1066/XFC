/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  accellabel.inl - Gtk::AccelLabel inline functions
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

inline GtkAccelLabel*
Xfc::Gtk::AccelLabel::gtk_accel_label() const
{
	return reinterpret_cast<GtkAccelLabel*>(instance_);
}

inline
Xfc::Gtk::AccelLabel::operator GtkAccelLabel* () const
{
	return this ? gtk_accel_label() : 0;
}

inline unsigned int
Xfc::Gtk::AccelLabel::get_accel_width() const
{
	return gtk_accel_label_get_accel_width(gtk_accel_label());
}

inline void
Xfc::Gtk::AccelLabel::set_accel_closure(GClosure *accel_closure)
{
	gtk_accel_label_set_accel_closure(gtk_accel_label(), accel_closure);
}

inline bool
Xfc::Gtk::AccelLabel::refetch()
{
	return gtk_accel_label_refetch(gtk_accel_label());
}

