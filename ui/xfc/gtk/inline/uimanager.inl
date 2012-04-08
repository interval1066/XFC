/*  XFC: Xfce Foundation Classes (User Interface Library)
*  Copyright (C) 2004 The XFC Development Team.
 *
 *  uimanager.inl - Gtk::UIManager inline functions
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

inline GtkUIManager*
Xfc::Gtk::UIManager::gtk_ui_manager() const
{
	return reinterpret_cast<GtkUIManager*>(instance_);
}

inline Xfc::Gtk::UIManager::operator GtkUIManager* () const
{
	return this ? gtk_ui_manager() : 0;
}

inline bool 
Xfc::Gtk::UIManager::get_add_tearoffs() const
{
	return gtk_ui_manager_get_add_tearoffs(gtk_ui_manager());
}

inline void 
Xfc::Gtk::UIManager::set_add_tearoffs(bool add_tearoffs)
{
	gtk_ui_manager_set_add_tearoffs(gtk_ui_manager(), add_tearoffs);
}

inline const Xfc::Gtk::UIManager::AddWidgetSignalProxy
Xfc::Gtk::UIManager::signal_add_widget()
{
	return AddWidgetSignalProxy(this, &add_widget_signal);
}

	
inline const Xfc::Gtk::UIManager::ActionsChangedSignalProxy
Xfc::Gtk::UIManager::signal_actions_changed()
{
	return ActionsChangedSignalProxy(this, &actions_changed_signal);
}

inline const Xfc::Gtk::UIManager::ConnectProxySignalProxy
Xfc::Gtk::UIManager::signal_connect_proxy()
{
	return ConnectProxySignalProxy(this, &connect_proxy_signal);
}

inline const Xfc::Gtk::UIManager::DisconnectProxySignalProxy
Xfc::Gtk::UIManager::signal_disconnect_proxy()
{
	return DisconnectProxySignalProxy(this, &disconnect_proxy_signal);
}

inline const Xfc::Gtk::UIManager::PreActivateSignalProxy
Xfc::Gtk::UIManager::signal_pre_activate()
{
	return PreActivateSignalProxy(this, &pre_activate_signal);
}

inline const Xfc::Gtk::UIManager::PostActivateSignalProxy
Xfc::Gtk::UIManager::signal_post_activate()
{
	return PostActivateSignalProxy(this, &post_activate_signal);
}

