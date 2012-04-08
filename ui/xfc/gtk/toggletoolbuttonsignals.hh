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

/// @file xfc/gtk/toggletoolbuttonsignals.hh
/// @brief Gtk::ToggleToolButton virtual signal handlers.
///
/// Provides Gtk::ToggleToolButtonSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::ToggleToolButton objects.

#ifndef XFC_GTK_TOGGLE_TOOL_BUTTON_SIGNALS_HH
#define XFC_GTK_TOGGLE_TOOL_BUTTON_SIGNALS_HH

#ifndef XFC_GTK_TOOL_BUTTON_SIGNALS_HH
#include <xfc/gtk/toolbuttonsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToggleToolButtonSignals toggletoolbuttonsignals.hh xfc/gtk/toggletoolbuttonsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::ToggleToolButton.

class ToggleToolButtonSignals : public ToolButtonSignals
{
protected:
/// @name Constructors
/// @{

	ToggleToolButtonSignals(ToggleToolButton *button);
	///< Construct a new ToolButtonSignals object.
	///< @param button A ToggleToolButton object inheriting the ToggleToolButtonSignals implementation.

	virtual ~ToggleToolButtonSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_toggled();
	///< Called whenever the toggle tool button changes state.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TOGGLE_TOOL_BUTTON_SIGNALS_HH

