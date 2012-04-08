/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  menuitem.inl - Gtk::MenuItem inline functions
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

inline GtkMenuItem*
Xfc::Gtk::MenuItem::gtk_menu_item() const
{
	return reinterpret_cast<GtkMenuItem*>(instance_);
}

inline Xfc::Gtk::MenuItem::operator GtkMenuItem* () const
{
	return this ? gtk_menu_item() : 0;
}

inline bool
Xfc::Gtk::MenuItem::has_submenu() const
{
	return gtk_menu_item()->submenu;
}

inline bool
Xfc::Gtk::MenuItem::get_right_justified() const
{
	return gtk_menu_item_get_right_justified(gtk_menu_item());
}

inline void
Xfc::Gtk::MenuItem::activate()
{
	gtk_menu_item_activate(gtk_menu_item());
}

inline void
Xfc::Gtk::MenuItem::toggle_size_request(int *requisition)
{
	gtk_menu_item_toggle_size_request(gtk_menu_item(), requisition);
}

inline void
Xfc::Gtk::MenuItem::toggle_size_allocate(int allocation)
{
	gtk_menu_item_toggle_size_allocate(gtk_menu_item(), allocation);
}

inline void
Xfc::Gtk::MenuItem::set_right_justified(bool right_justified)
{
	gtk_menu_item_set_right_justified(gtk_menu_item(), right_justified);
}

inline void
Xfc::Gtk::MenuItem::set_accel_path(const char *accel_path)
{
	gtk_menu_item_set_accel_path(gtk_menu_item(), accel_path);
}

inline const Xfc::Gtk::MenuItem::ActivateSignalProxy
Xfc::Gtk::MenuItem::signal_activate()
{
	return ActivateSignalProxy(this, &activate_signal);
}

inline const Xfc::Gtk::MenuItem::ActivateItemSignalProxy
Xfc::Gtk::MenuItem::signal_activate_item()
{
	return ActivateItemSignalProxy(this, &activate_item_signal);
}

inline const Xfc::Gtk::MenuItem::ToggleSizeRequestSignalProxy
Xfc::Gtk::MenuItem::signal_toggle_size_request()
{
	return ToggleSizeRequestSignalProxy(this, &toggle_size_request_signal);
}

inline const Xfc::Gtk::MenuItem::ToggleSizeAllocateSignalProxy
Xfc::Gtk::MenuItem::signal_toggle_size_allocate()
{
	return ToggleSizeAllocateSignalProxy(this, &toggle_size_allocate_signal);
}

