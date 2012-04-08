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
 
/// @file xfc/gtk/checkmenuitemsignals.hh
/// @brief Gtk::CheckMenuItem virtual signal handlers.
///
/// Provides Gtk::CheckMenuItemSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::CheckMenuItem objects.

#ifndef XFC_GTK_MENU_CHECK_ITEM_SIGNALS_HH
#define XFC_GTK_MENU_CHECK_ITEM_SIGNALS_HH

#ifndef XFC_GTK_MENU_ITEM_SIGNALS_HH
#include <xfc/gtk/menuitemsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class CheckMenuItemSignals checkmenuitemsignals.hh xfc/gtk/checkmenuitemsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::CheckMenuItem.

class CheckMenuItemSignals : public MenuItemSignals
{
protected:
/// @name Constructors
/// @{

	CheckMenuItemSignals(CheckMenuItem *check_menu_item);
	///< Construct a new CheckMenuItemSignals object.
	///< @param check_menu_item A CheckMenuItem object inheriting the CheckMenuItemSignals implementation.

	virtual ~CheckMenuItemSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{
	virtual void on_toggled();
	///< Called when the state of the check box is changed. Call get_active() to discover the new state.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_MENU_CHECK_ITEM_SIGNALS_HH

