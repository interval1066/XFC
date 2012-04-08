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

/// @file xfc/gtk/viewportsignals.hh
/// @brief Gtk::Viewport virtual signal handlers.
///
/// Provides Gtk::ViewportSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Viewport objects.

#ifndef XFC_GTK_VIEWPORT_SIGNALS_HH
#define XFC_GTK_VIEWPORT_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ViewportSignals viewportsignals.hh xfc/gtk/viewportsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Viewport.

class ViewportSignals : public virtual ContainerSignals
{
protected:
/// @name Constructors
/// @{

	ViewportSignals(Viewport *viewport);
	///< Constructs a new ViewportSignals object.
	///< @param viewport A Viewport object inheriting the ViewportSignals implementation.

	virtual ~ViewportSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment);
	///< Called when a viewport is added to a scrolling aware parent.
	///< @param hadjustment The horizontal adjustment.
	///< @param vadjustment The vertical adjustment.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_VIEWPORT_SIGNALS_HH

