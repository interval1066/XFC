/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  adjustment.inl - Gtk::Adjustment inline functions
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

inline GtkAdjustment*
Xfc::Gtk::Adjustment::gtk_adjustment() const
{
	return reinterpret_cast<GtkAdjustment*>(instance_);
}

inline Xfc::Gtk::Adjustment::operator GtkAdjustment* () const
{
	return this ? gtk_adjustment() : 0;
}

inline double
Xfc::Gtk::Adjustment::lower() const
{
	return gtk_adjustment()->lower;
}

inline double
Xfc::Gtk::Adjustment::upper() const
{
	return gtk_adjustment()->upper;
}

inline double
Xfc::Gtk::Adjustment::step_increment() const
{
	return gtk_adjustment()->step_increment;
}

inline double
Xfc::Gtk::Adjustment::page_increment() const
{
	return gtk_adjustment()->page_increment;
}

inline double
Xfc::Gtk::Adjustment::page_size() const
{
	return gtk_adjustment()->page_size;
}

inline double
Xfc::Gtk::Adjustment::get_value() const
{
	return gtk_adjustment_get_value(gtk_adjustment());
}

inline void
Xfc::Gtk::Adjustment::changed()
{
	gtk_adjustment_changed(gtk_adjustment());
}

inline void
Xfc::Gtk::Adjustment::value_changed()
{
	gtk_adjustment_value_changed(gtk_adjustment());
}

inline void
Xfc::Gtk::Adjustment::clamp_page(double lower, double upper)
{
	gtk_adjustment_clamp_page(gtk_adjustment(), lower, upper);
}

inline void
Xfc::Gtk::Adjustment::set_value(double value)
{
	gtk_adjustment_set_value(gtk_adjustment(), value);
}

inline const Xfc::Gtk::Adjustment::ChangedSignalProxy
Xfc::Gtk::Adjustment::signal_changed()
{
	return ChangedSignalProxy(this, &changed_signal);
}

inline const Xfc::Gtk::Adjustment::ValueChangedSignalProxy
Xfc::Gtk::Adjustment::signal_value_changed()
{
	return ValueChangedSignalProxy(this, &value_changed_signal);
}

