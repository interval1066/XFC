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
 
/// @file xfc/gtk/menuitemsignals.hh
/// @brief Gtk::MenuItem virtual signal handlers.
///
/// Provides Gtk::MenuItemSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::MenuItem objects.

#ifndef XFC_GTK_MENU_ITEM_SIGNALS_HH
#define XFC_GTK_MENU_ITEM_SIGNALS_HH

#ifndef XFC_GTK_ITEM_SIGNALS_HH
#include <xfc/gtk/itemsignals.hh>
#endif

namespace Xfc {

namespace Gtk {
	
/// @class MenuItemSignals menuitemsignals.hh xfc/gtk/menuitemsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::MenuItem.

class MenuItemSignals : public ItemSignals
{
protected:
/// @name Contructors
/// @{

	MenuItemSignals(MenuItem *menu_item);
	///< Construct a new MenuItemSignals object.
	///< @param menu_item A MenuItem object inheriting the MenuItemSignals implementation.

	virtual ~MenuItemSignals() = 0;
	///< Destructor.
	
/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_activate();
	///< Called when the menu item is activated.

	virtual void on_activate_item();
	///< Called when the menu item is activated, but also if the menu item has a submenu.
	///< For normal applications, the relevant signal is "activate".

	virtual void on_toggle_size_request(int *requisition);
	///< Called when MenuBar or Menu requests the size of the toggle.
	///< @param requisition The return location for the size of the toggle.
	///<
	///< For CheckMenuItem the toggle is a checkbox. For ImageMenuItem the Toggle
	///< is an image.

	virtual void on_toggle_size_allocate(int allocate);
	///< Called when MenuBar or Menu allocates a size for the toggle.
	///< @param allocate The size allocated to the toggle.
	///<
	///< For CheckMenuItem the toggle is a checkbox. For ImageMenuItem the Toggle
	///< is an image.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_MENU_ITEM_SIGNALS_HH

