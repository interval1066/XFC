/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  spinbutton.inl - Gtk::SpinButton inline functions
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

inline GtkSpinButton*
Xfc::Gtk::SpinButton::gtk_spin_button() const
{
	return reinterpret_cast<GtkSpinButton*>(instance_);
}

inline Xfc::Gtk::SpinButton::operator GtkSpinButton* () const
{
	return this ? gtk_spin_button() : 0;
}

inline unsigned int
Xfc::Gtk::SpinButton::get_digits() const
{
	return gtk_spin_button_get_digits(gtk_spin_button());
}

inline void
Xfc::Gtk::SpinButton::get_increments(double *step, double *page) const
{
	gtk_spin_button_get_increments(gtk_spin_button(), step, page);
}

inline void
Xfc::Gtk::SpinButton::get_range(double *min, double *max) const
{
	gtk_spin_button_get_range(gtk_spin_button(), min, max);
}

inline double
Xfc::Gtk::SpinButton::get_value() const
{
	return gtk_spin_button_get_value(gtk_spin_button());
}

inline int
Xfc::Gtk::SpinButton::get_value_as_int() const
{
	return gtk_spin_button_get_value_as_int(gtk_spin_button());
}

inline Xfc::Gtk::SpinButtonUpdatePolicy
Xfc::Gtk::SpinButton::get_update_policy() const
{
	return (SpinButtonUpdatePolicy)gtk_spin_button_get_update_policy(gtk_spin_button());
}

inline bool
Xfc::Gtk::SpinButton::get_numeric() const
{
	return gtk_spin_button_get_numeric(gtk_spin_button());
}

inline bool
Xfc::Gtk::SpinButton::get_wrap() const
{
	return gtk_spin_button_get_wrap(gtk_spin_button());
}

inline bool
Xfc::Gtk::SpinButton::get_snap_to_ticks() const
{
	return gtk_spin_button_get_snap_to_ticks(gtk_spin_button());
}

inline void
Xfc::Gtk::SpinButton::set_digits(unsigned int digits)
{
	gtk_spin_button_set_digits(gtk_spin_button(), digits);
}

inline void
Xfc::Gtk::SpinButton::set_increments(double step, double page)
{
	gtk_spin_button_set_increments(gtk_spin_button(), step, page);
}

inline void
Xfc::Gtk::SpinButton::set_range(double min, double max)
{
	gtk_spin_button_set_range(gtk_spin_button(), min, max);
}
inline void
Xfc::Gtk::SpinButton::set_value(double value)
{
	gtk_spin_button_set_value(gtk_spin_button(), value);
}

inline void
Xfc::Gtk::SpinButton::set_update_policy(SpinButtonUpdatePolicy policy)
{
	gtk_spin_button_set_update_policy(gtk_spin_button(), (GtkSpinButtonUpdatePolicy)policy);
}

inline void
Xfc::Gtk::SpinButton::set_numeric(bool numeric)
{
	gtk_spin_button_set_numeric(gtk_spin_button(), numeric);
}

inline void
Xfc::Gtk::SpinButton::spin(SpinType direction, double increment)
{
	gtk_spin_button_spin(gtk_spin_button(), (GtkSpinType)direction, increment);
}

inline void
Xfc::Gtk::SpinButton::set_wrap(bool wrap)
{
	gtk_spin_button_set_wrap(gtk_spin_button(), wrap);
}

inline void
Xfc::Gtk::SpinButton::set_snap_to_ticks(bool snap_to_ticks)
{
	gtk_spin_button_set_snap_to_ticks(gtk_spin_button(), snap_to_ticks);
}

inline void
Xfc::Gtk::SpinButton::update()
{
	gtk_spin_button_update(gtk_spin_button());
}

inline const Xfc::Gtk::SpinButton::InputSignalProxy 
Xfc::Gtk::SpinButton::signal_input()
{
	return InputSignalProxy(this, &input_signal);
}

inline const Xfc::Gtk::SpinButton::OutputSignalProxy 
Xfc::Gtk::SpinButton::signal_output()
{
	return OutputSignalProxy(this, &output_signal);
}

inline const Xfc::Gtk::SpinButton::ValueChangedSignalProxy 
Xfc::Gtk::SpinButton::signal_value_changed()
{
	return ValueChangedSignalProxy(this, &value_changed_signal);
}

