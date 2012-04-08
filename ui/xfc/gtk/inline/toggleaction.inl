/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  toggleaction.inl - Gtk::ToggleAction inline functions
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

inline GtkToggleAction*
Xfc::Gtk::ToggleAction::gtk_toggle_action() const
{
	return reinterpret_cast<GtkToggleAction*>(instance_);
}

inline Xfc::Gtk::ToggleAction::operator GtkToggleAction* () const
{
	return this ? gtk_toggle_action() : 0;
}

inline bool 
Xfc::Gtk::ToggleAction::get_active() const
{
	return gtk_toggle_action_get_active(gtk_toggle_action());
}

inline bool 
Xfc::Gtk::ToggleAction::get_draw_as_radio() const
{
	return gtk_toggle_action_get_draw_as_radio(gtk_toggle_action());
}

inline void 
Xfc::Gtk::ToggleAction::toggled()
{
	gtk_toggle_action_toggled(gtk_toggle_action());
}

	
inline void 
Xfc::Gtk::ToggleAction::set_active(bool is_active)
{
	gtk_toggle_action_set_active(gtk_toggle_action(), is_active);
}
	 
inline void 
Xfc::Gtk::ToggleAction::set_draw_as_radio(bool draw_as_radio)
{
	gtk_toggle_action_set_draw_as_radio(gtk_toggle_action(), draw_as_radio);
}

inline const Xfc::Gtk::ToggleAction::ToggledSignalProxy 
Xfc::Gtk::ToggleAction::signal_toggled()
{
	return ToggledSignalProxy(this, &toggled_signal);
}

