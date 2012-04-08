/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  toggletoolbutton.inl - Gtk::ToggleToolButton inline functions
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

inline GtkToggleToolButton*
Xfc::Gtk::ToggleToolButton::gtk_toggle_tool_button() const
{
	return reinterpret_cast<GtkToggleToolButton*>(instance_);
}

inline Xfc::Gtk::ToggleToolButton::operator GtkToggleToolButton* () const
{
	return this ? gtk_toggle_tool_button() : 0;
}

inline bool 
Xfc::Gtk::ToggleToolButton::get_active() const
{
	return gtk_toggle_tool_button_get_active(gtk_toggle_tool_button());
}

inline void 
Xfc::Gtk::ToggleToolButton::set_active(bool is_active)
{
	gtk_toggle_tool_button_set_active(gtk_toggle_tool_button(), is_active);
}

inline const Xfc::Gtk::ToggleToolButton::ToggledSignalProxy
Xfc::Gtk::ToggleToolButton::signal_toggled()
{
	return ToggledSignalProxy(this, &toggled_signal);
}
	
