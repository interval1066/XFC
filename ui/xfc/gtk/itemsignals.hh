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
 
/// @file xfc/gtk/itemsignals.hh
/// @brief Gtk::Item virtual signal handlers.
///
/// Provides Gtk::ItemSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Item objects.

#ifndef XFC_GTK_ITEM_SIGNALS_HH
#define XFC_GTK_ITEM_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ItemSignals itemsignals.hh xfc/gtk/itemsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Item.

class ItemSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	ItemSignals(Item *item);
	///< Construct a new ItemSignals object.
	///< @param item An Item object inheriting the ItemSignals implementation.

	virtual ~ItemSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_select();
	///< Called when the item is selected.

	virtual void on_deselect();
	///< Called when the item is deselected.

	virtual void on_toggle();
	///< Called when the item is toggled.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_ITEM_SIGNALS_HH

