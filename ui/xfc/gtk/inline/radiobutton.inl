/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  radiobutton.inl - Gtk::RadioButton inline functions
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

inline GtkRadioButton*
Xfc::Gtk::RadioButton::gtk_radio_button() const
{
	return reinterpret_cast<GtkRadioButton*>(instance_);
}

inline Xfc::Gtk::RadioButton::operator GtkRadioButton* () const
{
	return this ? gtk_radio_button() : 0;
}

inline Xfc::Gtk::RadioButton::Group*
Xfc::Gtk::RadioButton::get_group() const
{
	return gtk_radio_button_group(gtk_radio_button());
}

inline void
Xfc::Gtk::RadioButton::set_group(Group *group)
{
	gtk_radio_button_set_group(gtk_radio_button(), group);
}

inline const Xfc::Gtk::RadioButton::GroupChangedSignalProxy 
Xfc::Gtk::RadioButton::signal_group_changed()
{
	return GroupChangedSignalProxy(this, &group_changed_signal);
}

