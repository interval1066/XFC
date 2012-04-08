/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  menu.inl - Gtk::Menu inline functions
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

inline GtkMenu*
Xfc::Gtk::Menu::gtk_menu() const
{
	return reinterpret_cast<GtkMenu*>(instance_);
}

inline Xfc::Gtk::Menu::operator GtkMenu* () const
{
	return this ? gtk_menu() : 0;
}

inline bool
Xfc::Gtk::Menu::get_tearoff_state() const
{
	return gtk_menu_get_tearoff_state(gtk_menu());
}

inline void
Xfc::Gtk::Menu::popup(unsigned int button, unsigned int activate_time)
{
	gtk_menu_popup(gtk_menu(), 0, 0, 0, 0, button, activate_time);
}

inline void
Xfc::Gtk::Menu::reposition()
{
	gtk_menu_reposition(gtk_menu());
}

inline void
Xfc::Gtk::Menu::popdown()
{
	gtk_menu_popdown(gtk_menu());
}

inline void
Xfc::Gtk::Menu::set_active(unsigned int index)
{
	gtk_menu_set_active(gtk_menu(), index);
}

inline void
Xfc::Gtk::Menu::set_accel_path(const char *accel_path)
{
	gtk_menu_set_accel_path(gtk_menu(), accel_path);
}

inline void
Xfc::Gtk::Menu::detach()
{
	gtk_menu_detach(gtk_menu());
}

inline void
Xfc::Gtk::Menu::set_tearoff_state(bool torn_off)
{
	gtk_menu_set_tearoff_state(gtk_menu(), torn_off);
}

inline void
Xfc::Gtk::Menu::set_title(const char *title)
{
	gtk_menu_set_title(gtk_menu(), title);
}

inline void
Xfc::Gtk::Menu::set_monitor(int monitor_num)
{
	gtk_menu_set_monitor (gtk_menu(), monitor_num);
}

