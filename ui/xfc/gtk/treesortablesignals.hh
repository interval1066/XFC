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

/// @file xfc/gtk/treesortablesignals.hh
/// @brief Gtk::TreeSortable virtual signal handlers.
///
/// Provides Gtk::TreeSortableSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::TreeSortable objects.

#ifndef XFC_GTK_TREE_SORTABLE_SIGNALS_HH
#define XFC_GTK_TREE_SORTABLE_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class TreeSortableSignals treesortablesignals.hh xfc/gtk/treesortablesignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::TreeSortable.

class TreeSortableSignals : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	virtual ~TreeSortableSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_sort_column_changed();
	///< Called whenever the current sort column is changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TREE_SORTABLE_SIGNALS_HH

