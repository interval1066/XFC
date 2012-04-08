/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  radiomenuitem.inl - Gtk::RadioMenuItem inline functions
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

inline GtkRadioMenuItem*
Xfc::Gtk::RadioMenuItem::gtk_radio_menu_item() const
{
	return reinterpret_cast<GtkRadioMenuItem*>(instance_);
}

inline Xfc::Gtk::RadioMenuItem::operator GtkRadioMenuItem* () const
{
	return this ? gtk_radio_menu_item() : 0;
}

inline Xfc::Gtk::RadioMenuItem::Group*
Xfc::Gtk::RadioMenuItem::get_group() const
{
	return gtk_radio_menu_item_get_group(gtk_radio_menu_item());
}

inline void
Xfc::Gtk::RadioMenuItem::set_group(Group *group)
{
	gtk_radio_menu_item_set_group(gtk_radio_menu_item(), group);
}

inline const Xfc::Gtk::RadioMenuItem::GroupChangedSignalProxy 
Xfc::Gtk::RadioMenuItem::signal_group_changed()
{
	return GroupChangedSignalProxy(this, &group_changed_signal);
}

