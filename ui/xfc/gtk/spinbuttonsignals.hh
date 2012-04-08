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

/// @file xfc/gtk/spinbuttonsignals.hh
/// @brief Gtk::SpinButton virtual signal handlers.
///
/// Provides Gtk::SpinButtonSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::SpinButton objects.

#ifndef XFC_GTK_SPIN_BUTTON_SIGNALS_HH
#define XFC_GTK_SPIN_BUTTON_SIGNALS_HH

#ifndef XFC_GTK_ENTRY_SIGNALS_HH
#include <xfc/gtk/entrysignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class SpinButtonSignals spinbuttonsignals.hh xfc/gtk/spinbuttonsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::SpinButton.

class SpinButtonSignals : public virtual EntrySignals
{
protected:
/// @name Constructors
/// @{

	SpinButtonSignals(SpinButton *spin_button);
	///< Constructs a new SpinButtonSignals object.
	///< @param spin_button A SpinButton object inheriting the SpinButtonSignals implementation.

	virtual ~SpinButtonSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual int on_input(double *new_value);
	///< Called when a new value is displayed in the spinbutton.
	///< @param new_value The new value of the spin button.
	///< @return -1 if an error occurs, otherwise 0.

	virtual int on_output();
	///< Called to display the new value in the spin button.
	///< @return Always zero.

	virtual void on_value_changed();
	///< Called when the value has changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SPIN_BUTTON_SIGNALS_HH

