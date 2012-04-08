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

/// @file xfc/gtk/fontbuttonsignals.hh
/// @brief Gtk::FontButton virtual signal handlers.
///
/// Provides Gtk::FontButtonSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::FontButton objects.

#ifndef XFC_GTK_FONT_BUTTON_SIGNALS_HH
#define XFC_GTK_FONT_BUTTON_SIGNALS_HH

#ifndef XFC_GTK_BUTTON_SIGNALS_HH
#include <xfc/gtk/buttonsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class FontButtonSignals fontbuttonsignals.hh xfc/gtk/fontbuttonsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::FontButton.

class FontButtonSignals : public ButtonSignals
{
protected:
/// @name Constructors
/// @{

	FontButtonSignals(FontButton *font_button);
	///< Construct a new FontButtonSignals object.
	///< @param font_button A FontButton object inheriting the FontButtonSignals implementation.

	virtual ~FontButtonSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_font_set();
	///< Called when the user selects a font. When handling this signal, use get_font_name()
	///< to find out which font was just selected.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_FONT_BUTTON_SIGNALS_HH

