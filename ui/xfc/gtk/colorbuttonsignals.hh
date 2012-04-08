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

/// @file xfc/gtk/colorbuttonsignals.hh
/// @brief Gtk::ColorButton virtual signal handlers.
///
/// Provides Gtk::ColorButtonSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::ColorButton objects.

#ifndef XFC_GTK_COLOR_BUTTON_SIGNALS_HH
#define XFC_GTK_COLOR_BUTTON_SIGNALS_HH

#ifndef XFC_GTK_BUTTON_SIGNALS_HH
#include <xfc/gtk/buttonsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ColorButtonSignals colorbuttonsignals.hh xfc/gtk/colorbuttonsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::ColorButton.

class ColorButtonSignals : public ButtonSignals
{
protected:
/// @name Constructors
/// @{

	ColorButtonSignals(ColorButton *color_button);
	///< Construct a new ColorButtonSignals object.
	///< @param color_button A ColorButton object inheriting the ColorButtonSignals implementation.

	virtual ~ColorButtonSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_color_set();
	///< Called when the user selects a color. When handling this signal, use get_color() and 
	///< get_alpha() to find out which color was just selected.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_COLOR_BUTTON_SIGNALS_HH

