/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  checkmenuitem.inl - Gtk::CheckMenuItem inline functions
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

inline GtkCheckMenuItem*
Xfc::Gtk::CheckMenuItem::gtk_check_menu_item() const
{
	return reinterpret_cast<GtkCheckMenuItem*>(instance_);
}

inline Xfc::Gtk::CheckMenuItem::operator GtkCheckMenuItem* () const
{
	return this ? gtk_check_menu_item() : 0;
}

inline bool
Xfc::Gtk::CheckMenuItem::get_active() const
{
	return gtk_check_menu_item_get_active(gtk_check_menu_item());
}

inline bool
Xfc::Gtk::CheckMenuItem::get_inconsistent() const
{
	return gtk_check_menu_item_get_inconsistent(gtk_check_menu_item());
}

inline bool
Xfc::Gtk::CheckMenuItem::get_draw_as_radio() const
{
	return gtk_check_menu_item_get_draw_as_radio(gtk_check_menu_item());
}

inline void
Xfc::Gtk::CheckMenuItem::set_active(bool is_active)
{
	gtk_check_menu_item_set_active(gtk_check_menu_item(), is_active);
}

inline void
Xfc::Gtk::CheckMenuItem::set_inconsistent(bool setting)
{
	gtk_check_menu_item_set_inconsistent(gtk_check_menu_item(), setting);
}

inline void
Xfc::Gtk::CheckMenuItem::set_draw_as_radio(bool draw_as_radio)
{
	gtk_check_menu_item_set_draw_as_radio(gtk_check_menu_item(), draw_as_radio);
}

inline void
Xfc::Gtk::CheckMenuItem::toggled()
{
	gtk_check_menu_item_toggled(gtk_check_menu_item());
}

inline const Xfc::Gtk::CheckMenuItem::ToggledSignalProxy
Xfc::Gtk::CheckMenuItem::signal_toggled()
{
	return ToggledSignalProxy(this, &toggled_signal);
}

