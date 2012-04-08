/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
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

/// @file xfc/gtk/uimanagersignals.hh
/// @brief Gtk::UIManager virtual signal handlers.
///
/// Provides Gtk::UIManagerSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::UIManager objects.

#ifndef XFC_GTK_UI_MANAGER_SIGNALS_HH
#define XFC_GTK_UI_MANAGER_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class UIManagerSignals uimanagersignals.hh xfc/gtk/uimanagersignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::UIManager.

class UIManagerSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	UIManagerSignals(UIManager *ui_manager);
	///< Construct a new UIManagerSignals object.
	///< @param ui_manager A UIManager object inheriting the UIManagerSignals implementation.

	virtual ~UIManagerSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_add_widget(Widget& widget);
	///< Called for each generated menubar and toolbar.
	///< @param widget The added widget.
	///<
	///< This method is not called for generated popup menus, which can be
	///< obtained by Gtk::UIManager::get_widget().
	
	virtual void on_actions_changed();
	///< Called whenever the set of actions changes.
	
	virtual void on_connect_proxy(Action& action, Widget& proxy);
	///< Called after connecting a proxy widget to an action in the group.
	///< @param action The action.
	///< @param proxy The proxy widget. 
	///< 
	///< This handler is intended for simple customizations for which
	///< a custom action class would be too clumsy, e.g. showing tooltips
	///< for menu items in the statusbar.
	
	virtual void on_disconnect_proxy(Action& action, Widget& proxy);
	///< Called after disconnecting a proxy widget from an action in the group. 
	///< @param action The action.
	///< @param proxy The proxy widget. 
	
	virtual void on_pre_activate(Action& action);
	///< Called just before the action is activated.
	///< @param action The action.
	///<
	///< This handler is intended for applications to get notification
	///< just before any action is activated.
	
	virtual void on_post_activate(Action& action);
	///< Called just after the action is activated.
	///< @param action The action.
	///<
	///< This handler is intended for applications to get notification
	///< just after any action is activated.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_UI_MANAGER_SIGNALS_HH

