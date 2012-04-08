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

/// @file xfc/gtk/treemodelsignals.hh
/// @brief Gtk::TreeModel virtual signal handlers.
///
/// Provides Gtk::TreeModelSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::TreeModel objects.

#ifndef XFC_GTK_TREE_MODEL_SIGNALS_HH
#define XFC_GTK_TREE_MODEL_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class TreeModelSignals treemodelsignals.hh xfc/gtk/treemodelsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::TreeModel.

class TreeModelSignals : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	virtual ~TreeModelSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_row_changed(const TreePath& path, const TreeIter& iter);
	///< Called when a row in the model is changed.
	///< @param path A TreePath pointing to the changed row.
	///< @param iter A valid TreeIter pointing to the changed row.

	virtual void on_row_inserted(const TreePath& path, const TreeIter& iter);
	///< Called when a row is inserted into the model.
	///< @param path A TreePath pointing to the inserted row.
	///< @param iter A valid TreeIter pointing to the inserted row.

	virtual void on_row_has_child_toggled(const TreePath& path, const TreeIter& iter);
	///< Called after the child state of a node changes.
	///< @param path A TreePath pointing to the changed row.
	///< @param iter A valid TreeIter pointing to the changed row.

	virtual void on_row_deleted(const TreePath& path);
	///< Called when a row is removed from the model.
	///< @param path A TreePath pointing to the previous location of the deleted row.

	virtual void on_rows_reordered(const TreePath& path, const TreeIter& iter, int *new_order);
	///< Called when the model's rows have been reordered.
	///< @param path A TreePath pointing to the tree node whose children have been reordered.
	///< @param iter A valid TreeIter pointing to the node whose children have been reordered.
	///< @param new_order An array of integers containing the new indices of the children,
	///< i.e. the former child n is now at position new_order[n].

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TREE_MODEL_SIGNALS_HH

