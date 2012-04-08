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

/// @file xfc/gtk/toolbuttonsignals.hh
/// @brief Gtk::ToolButton virtual signal handlers.
///
/// Provides Gtk::ToolButtonSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::ToolButton objects.

#ifndef XFC_GTK_TOOL_BUTTON_SIGNALS_HH
#define XFC_GTK_TOOL_BUTTON_SIGNALS_HH

#ifndef XFC_GTK_TOOL_ITEM_SIGNALS_HH
#include <xfc/gtk/toolitemsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToolButtonSignals toolbuttonsignals.hh xfc/gtk/toolbuttonsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::ToolButton.

class ToolButtonSignals : public ToolItemSignals
{
protected:
/// @name Constructors
/// @{

	ToolButtonSignals(ToolButton *tool_button);
	///< Construct a new ToolButtonSignals object.
	///< @param tool_button A ToolButton object inheriting the ToolButtonSignals implementation.

	virtual ~ToolButtonSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_clicked();
	///< Called when the tool button is clicked with the mouse or activated with the keyboard.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TOOL_BUTTON_SIGNALS_HH

