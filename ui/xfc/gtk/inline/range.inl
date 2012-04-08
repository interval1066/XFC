/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  range.inl - Gtk::Range inline functions
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

inline GtkRange*
Xfc::Gtk::Range::gtk_range() const
{
	return reinterpret_cast<GtkRange*>(instance_);
}

inline Xfc::Gtk::Range::operator GtkRange* () const
{
	return this ? gtk_range() : 0;
}

inline bool
Xfc::Gtk::Range::get_inverted() const
{
	return gtk_range_get_inverted(gtk_range());
}

inline double
Xfc::Gtk::Range::get_value() const
{
	return gtk_range_get_value(gtk_range());
}

inline void
Xfc::Gtk::Range::set_round_digits(int round_digits)
{
	gtk_range()->round_digits = round_digits;
}

inline void
Xfc::Gtk::Range::set_update_policy(UpdateType policy)
{
	gtk_range_set_update_policy(gtk_range(), (GtkUpdateType)policy);
}

inline void
Xfc::Gtk::Range::set_inverted(bool setting)
{
	gtk_range_set_inverted(gtk_range(), setting);
}

inline void
Xfc::Gtk::Range::set_increments(double step, double page)
{
	gtk_range_set_increments(gtk_range(), step, page);
}

inline void
Xfc::Gtk::Range::set_range(double min, double max)
{
	gtk_range_set_range(gtk_range(), min, max);
}

inline void
Xfc::Gtk::Range::set_value(double value)
{
	gtk_range_set_value(gtk_range(), value);
}

inline const Xfc::Gtk::Range::ValueChangedSignalProxy 
Xfc::Gtk::Range::signal_value_changed()
{
	return ValueChangedSignalProxy(this, &value_changed_signal);
}

inline const Xfc::Gtk::Range::AdjustBoundsSignalProxy 
Xfc::Gtk::Range::signal_adjust_bounds()
{
	return AdjustBoundsSignalProxy(this, &adjust_bounds_signal);
}

