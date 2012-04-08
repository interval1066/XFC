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
 
/// @file xfc/gtk/radiobuttonsignals.hh
/// @brief Gtk::RadioButton virtual signal handlers.
///
/// Provides Gtk::RadioButtonSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::RadioButton objects.

#ifndef XFC_GTK_RADIO_BUTTON_SIGNALS_HH
#define XFC_GTK_RADIO_BUTTON_SIGNALS_HH

#ifndef XFC_GTK_TOGGLE_BUTTON_SIGNALS_HH
#include <xfc/gtk/togglebuttonsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class RadioButtonSignals radiobuttonsignals.hh xfc/gtk/radiobuttonsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::RadioButton.

class RadioButtonSignals : public ToggleButtonSignals
{
protected:
/// @name Constructors
/// @{

	RadioButtonSignals(RadioButton *radio_button);
	///< Constructs a new RadioButtonSignals object.
	///< @param radio_button A RadioButton object inheriting the RadioButtonSignals implementation.

	virtual ~RadioButtonSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_group_changed();
	///< Called when the group of radio buttons that a radio button belongs to changes. 
	///< This handler is called when a radio button switches from being alone to being
	///< part of a group of 2 or more buttons, or vice-versa, and when a buttton is 
	///< moved from one group of 2 or more buttons to a different one, but not when the
	///< composition of the group that a button belongs to changes.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_RADIO_BUTTON_SIGNALS_HH

