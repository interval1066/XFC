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
 
/// @file xfc/gtk/colorselectionsignals.hh
/// @brief Gtk::ColorSelection virtual signal handlers.
///
/// Provides Gtk::ColorSelectionSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::ColorSelection objects.

#ifndef XFC_GTK_COLOR_SELECTION_SIGNALS_HH
#define XFC_GTK_COLOR_SELECTION_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ColorSelectionSignals colorselectionsignals.hh xfc/gtk/colorselectionsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::ColorSelection.

class ColorSelectionSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{
	
	ColorSelectionSignals(ColorSelection *color_selection);
	///< Construct a new ColorSelectionSignals object.
	///< @param color_selection A ColorSelection object inheriting the ColorSelectionSignals implementation.
	
	virtual ~ColorSelectionSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_color_changed();
	///< Called when the color changes in the ColorSelection according to its update policy.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_COLOR_SELECTION_SIGNALS_HH

