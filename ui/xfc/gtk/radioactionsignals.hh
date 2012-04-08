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

/// @file xfc/gtk/radioactionsignals.hh
/// @brief Gtk::RadioAction virtual signal handlers.
///
/// Provides Gtk::RadioActionSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::RadioAction objects.

#ifndef XFC_GTK_RADIO_ACTION_SIGNALS_HH
#define XFC_GTK_RADIO_ACTION_SIGNALS_HH

#ifndef XFC_GTK_TOGGLE_ACTION_SIGNALS_HH
#include <xfc/gtk/toggleactionsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class RadioActionSignals radioactionsignals.hh xfc/gtk/radioactionsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::RadioAction.

class RadioActionSignals : public ToggleActionSignals
{
protected:
/// @name Constructors
/// @{

	RadioActionSignals(RadioAction *action);
	///< Construct a new RadioActionSignals object.
	///< @param action A RadioAction object inheriting the RadioActionSignals implementation.

	virtual ~RadioActionSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_changed(RadioAction& current);
	///< Called on every member of a radio group when the active member is changed.
	///< @param current The member of the action group which has just been activated. 
	///<	
	///< This handler is called after the Gtk::ActionSignals::on_activate() handler
	///< for the previous and current active members.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_RADIO_ACTION_SIGNALS_HH

