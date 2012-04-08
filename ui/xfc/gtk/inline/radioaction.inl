/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  radioaction.inl - Gtk::RadioAction inline functions
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

inline GtkRadioAction*
Xfc::Gtk::RadioAction::gtk_radio_action() const
{
	return reinterpret_cast<GtkRadioAction*>(instance_);
}

inline Xfc::Gtk::RadioAction::operator GtkRadioAction* () const
{
	return this ? gtk_radio_action() : 0;
}

inline int 
Xfc::Gtk::RadioAction::get_current_value() const
{
	return gtk_radio_action_get_current_value(gtk_radio_action());
}

inline Xfc::Gtk::RadioAction::Group* 
Xfc::Gtk::RadioAction::get_group() const
{
	return gtk_radio_action_get_group(gtk_radio_action());
}

inline void 
Xfc::Gtk::RadioAction::set_group(Group *group)
{
	gtk_radio_action_set_group(gtk_radio_action(), group);
}

inline const Xfc::Gtk::RadioAction::ChangedSignalProxy 
Xfc::Gtk::RadioAction::signal_changed()
{
	return ChangedSignalProxy(this, &changed_signal);
}

