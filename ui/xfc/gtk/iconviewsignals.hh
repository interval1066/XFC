/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
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
 
/// @file xfc/gtk/iconviewsignals.hh
/// @brief GtkIconView virtual signal handlers.
///
/// Provides Gtk::IconViewSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::IconView objects.

#ifndef XFC_GTK_ICON_VIEW_SIGNALS_HH
#define XFC_GTK_ICON_VIEW_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class IconViewSignals iconviewsignals.hh xfc/gtk/iconviewsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::IconView.

class IconViewSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	IconViewSignals(IconView *icon_view);
	///< Constructs a new IconViewSignals object.
	///< @param icon_view A IconView object inheriting the IconViewSignals implementation.

	virtual ~IconViewSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment);
	///< Called when an icon view is added to a scrolling aware parent.
	///< @param hadjustment The horizontal adjustment.
	///< @param vadjustment The vertical adjustment.
	
	virtual void on_item_activated(const TreePath& path);
	///< Called when the item determined by <EM>path</EM> is activated.
	///< @param path The path to the item being activated.

	virtual void on_selection_changed();
	///< Called whenever the selection in the icon view changes.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_ICON_VIEW_SIGNALS_HH

