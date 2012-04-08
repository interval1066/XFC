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

/// @file xfc/gtk/treeviewsignals.hh
/// @brief Gtk::TreeView virtual signal handlers.
///
/// Provides Gtk::TreeViewSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::TreeView objects.

#ifndef XFC_GTK_TREE_VIEW_SIGNALS_HH
#define XFC_GTK_TREE_VIEW_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class TreeViewSignals treeviewsignals.hh xfc/gtk/treeviewsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::TreeView.

class TreeViewSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	TreeViewSignals(TreeView *tree_view);
	///< Constructs a new TreeViewSignals object.
	///< @param tree_view A TreeView object inheriting the TreeViewSignals implementation.

	virtual ~TreeViewSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment);
	///< Called when a tree view is added to a scrolling aware parent.
	///< @param hadjustment The horizontal adjustment.
	///< @param vadjustment The vertical adjustment.

	virtual void on_row_activated(const TreePath& path, TreeViewColumn& column);
	///< Called when the cell determined by path and column is activated.
	///< @param path The TreePath being activated.
	///< @param column The TreeViewColumn being activated.

	virtual bool on_test_expand_row(const TreeIter& iter, const TreePath& path);
	///< Called to determine if the row identified by iter and path has child rows
	///< and can be opened.
	///< @param iter A valid iterator pointing to path.
	///< @param path The path to the row being checked.
	///< @return <EM>true</EM> if the row has chil rows and can be expanded.

	virtual bool on_test_collapse_row(const TreeIter& iter, const TreePath& path);
	///< Called to determine if the row identified by iter and path has child rows
	///< that are visible and can be collapsed.
	///< @param iter A valid iterator pointing to path.
	///< @param path The path to the row being checked.
	///< @return <EM>true</EM> if the row has child rows that are visible and can be collapsed.

	virtual void on_row_expanded(const TreeIter& iter, const TreePath& path);
	///< Called when the row determined by iter and path is opened so its children are visible.
	///< @param iter A valid iterator pointing to path.
	///< @param path The path to the row being expanded.

	virtual void on_row_collapsed(const TreeIter& iter, const TreePath& path);
	///< Called when the row determined by iter and path is collapsed to hide its child rows.
	///< @param iter A valid iterator pointing to path.
	///< @param path The path to the row being collapsed.

	virtual void on_columns_changed();
	///< Called whenever the order or number of columns in the tree view changes.

	virtual void on_cursor_changed();
	///< Called whenever the current keyboard focus changes.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TREE_VIEW_SIGNALS_HH

