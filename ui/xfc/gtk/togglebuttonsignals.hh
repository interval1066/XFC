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

/// @file xfc/gtk/togglebuttonsignals.hh
/// @brief Gtk::ToggleButton virtual signal handlers.
///
/// Provides Gtk::ToggleButtonSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::ToggleButton objects.

#ifndef XFC_GTK_TOGGLE_BUTTON_SIGNALS_HH
#define XFC_GTK_TOGGLE_BUTTON_SIGNALS_HH

#ifndef XFC_GTK_BUTTON_SIGNALS_HH
#include <xfc/gtk/buttonsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToggleButtonSignals togglebuttonsignals.hh xfc/gtk/togglebuttonsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::ToggleButton.

class ToggleButtonSignals : public ButtonSignals
{
protected:
/// @name Constructors
/// @{

	ToggleButtonSignals(ToggleButton *toggle_button);
	///< Constructs a new ToggleButtonSignals object.
	///< @param toggle_button A ToggleButton object inheriting the ToggleButtonSignals implementation.

	virtual ~ToggleButtonSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_toggled();
	///< Called whenever the toggle button's state is changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TOGGLE_BUTTON_SIGNALS_HH

