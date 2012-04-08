/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  actiongroup.inl - Gtk::ActionGroup inline functions
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

inline GtkActionGroup*
Xfc::Gtk::ActionGroup::gtk_action_group() const
{
	return reinterpret_cast<GtkActionGroup*>(instance_);
}

inline Xfc::Gtk::ActionGroup::operator GtkActionGroup* () const
{
	return this ? gtk_action_group() : 0;
}

inline bool 
Xfc::Gtk::ActionGroup::get_sensitive() const
{
	return gtk_action_group_get_sensitive(gtk_action_group());
}

inline bool 
Xfc::Gtk::ActionGroup::get_visible() const
{
	return gtk_action_group_get_visible(gtk_action_group());
}

inline void 
Xfc::Gtk::ActionGroup::set_sensitive(bool sensitive)
{
	gtk_action_group_set_sensitive(gtk_action_group(), sensitive);
}
	 
inline void 
Xfc::Gtk::ActionGroup::set_visible(bool visible)
{
	gtk_action_group_set_visible(gtk_action_group(), visible);
}

inline const Xfc::Gtk::ActionGroup::ConnectProxySignalProxy 
Xfc::Gtk::ActionGroup::signal_connect_proxy()
{
	return ConnectProxySignalProxy(this, &connect_proxy_signal);
}
	
inline const Xfc::Gtk::ActionGroup::DisconnectProxySignalProxy 
Xfc::Gtk::ActionGroup::signal_disconnect_proxy()
{
	return DisconnectProxySignalProxy(this, &disconnect_proxy_signal);
}

inline const Xfc::Gtk::ActionGroup::PreActivateSignalProxy 
Xfc::Gtk::ActionGroup::signal_pre_activate()
{
	return PreActivateSignalProxy(this, &pre_activate_signal);
}

inline const Xfc::Gtk::ActionGroup::PostActivateSignalProxy 
Xfc::Gtk::ActionGroup::signal_post_activate()
{
	return PostActivateSignalProxy(this, &post_activate_signal);
}

