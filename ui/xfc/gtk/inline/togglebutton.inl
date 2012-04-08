/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  togglebutton.inl - Gtk::ToggleButton inline functions
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

inline GtkToggleButton*
Xfc::Gtk::ToggleButton::gtk_toggle_button() const
{
	return reinterpret_cast<GtkToggleButton*>(instance_);
}

inline Xfc::Gtk::ToggleButton::operator GtkToggleButton* () const
{
	return this ? gtk_toggle_button() : 0;
}

inline bool
Xfc::Gtk::ToggleButton::get_active() const
{
	return gtk_toggle_button_get_active(gtk_toggle_button());
}

inline bool
Xfc::Gtk::ToggleButton::get_mode() const
{
	return gtk_toggle_button_get_mode(gtk_toggle_button());
}

inline bool
Xfc::Gtk::ToggleButton::get_inconsistent() const
{
	return gtk_toggle_button_get_inconsistent(gtk_toggle_button());
}

inline void
Xfc::Gtk::ToggleButton::set_mode(bool draw_indicator)
{
	gtk_toggle_button_set_mode(gtk_toggle_button(), draw_indicator);
}

inline void
Xfc::Gtk::ToggleButton::set_active(bool is_active)
{
	gtk_toggle_button_set_active(gtk_toggle_button(), is_active);
}

inline void
Xfc::Gtk::ToggleButton::set_inconsistent(bool setting)
{
	gtk_toggle_button_set_inconsistent(gtk_toggle_button(), setting);
}

inline void
Xfc::Gtk::ToggleButton::toggled()
{
	gtk_toggle_button_toggled(gtk_toggle_button());
}

inline const Xfc::Gtk::ToggleButton::ToggledSignalProxy
Xfc::Gtk::ToggleButton::signal_toggled()
{
	return ToggledSignalProxy(this, &toggled_signal);
}

