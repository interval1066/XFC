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

/// @file xfc/gtk/treednd.hh
/// @brief A GtkTreeDragSource and GtkTreeDragDest C++ wrapper interface.
/// 
/// Provides TreeDragSource and TreeDragDest interfaces for drag-and-drop support in Gtk::TreeView.

#ifndef XFC_GTK_TREE_DND_HH
#define XFC_GTK_TREE_DND_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __GTK_TREE_DND_H__
#include <gtk/gtktreednd.h>
#endif

namespace Xfc {

namespace Gtk {

class SelectionData;
class TreePath;

/// @class TreeDragSource treednd.hh xfc/gtk/treednd.hh
/// @brief A GtkTreeDragSource C++ wrapper class.
///
/// GTK+ supports Drag-and-Drop in tree views with a high-level and a low-level API. 
///
/// The low-level API consists of the GTK+ DND API, augmented by some treeview utility
/// functions: Gtk::TreeView::set_drag_dest_row(), Gtk::TreeView::get_drag_dest_row(), 
/// Gtk::TreeView::get_dest_row_at_pos() and Gtk::TreeView::create_row_drag_icon(). 
/// This API leaves a lot of flexibility, but nothing is done automatically, and 
/// implementing advanced features like hover-to-open-rows or autoscrolling on top
/// of this API is a lot of work. 
///
/// On the other hand, if you write to the high-level TreeDragSource and TreeDragDest
/// API, then all the bookkeeping of rows is done for you, as well as things like 
/// hover-to-open and auto-scroll. The TreeDragSource interface is implemented by 
/// Gtk::TreeModelSort, Gtk::TreeStore, Gtk::ListStore and Gtk::TreeModelFilter. The
/// TreeDragDest interface is implemented by Gtk::TreeStore and Gtk::ListStore.

class TreeDragSource : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	TreeDragSource();
	///< Constructs a new TreeDragSource object.	
	
	virtual ~TreeDragSource() = 0;
	///< Destructor.

/// @}

public:
/// @name Accessors
/// @{

	GtkTreeDragSource* gtk_tree_drag_source() const;
	///< Get a pointer to the GtkTreeDragSource structure.

	operator GtkTreeDragSource* () const;
	///< Conversion operator; safely converts a TreeDragSource to a GtkTreeDragSource pointer.

	bool row_draggable(const TreePath& path) const;
	///< Determines whether a particular row can be used as the source of a DND operation.
	///< @param path The row on which user is initiating a drag. 
	///< @return <EM>true</EM> if the row can be dragged. 	
	///<	 
	///< If the source doesn't implement this interface, the row is assumed draggable.

/// @}
/// @name Methods
/// @{

	bool drag_data_delete(TreePath& path);
	///< Asks the TreeDragSource to delete the row at <EM>path</EM>, because it was moved 
	///< somewhere else via drag-and-drop. 
	///< @param path The row that was being dragged.
	///< @return <EM>true</EM> if the row was successfully deleted. 	
	///<
	///< Returns <EM>false</EM> if the deletion fails because path no longer exists,
	///< or for some model-specific reason. Should robustly handle a path no longer found
	///< in the model!

	bool drag_data_get(const TreePath& path, SelectionData& selection_data);
	///< Asks the TreeDragSource to fill in selection_data with a representation
	///< of the row at <EM>path</EM>. 
	///< @param path The row that was dragged.
	///< @param selection_data A Gtk::SelectionData to fill with data from the dragged row 
	///< @return <EM>true</EM> if data of the required type was provided. 	
	///<	
	///< Note, selection_data->get_target() gives the required type of the data. 
	///< Should robustly handle a path no longer found in the model!

/// @}
};

/// @class TreeDragDest treednd.hh xfc/gtk/treednd.hh
/// @brief A GtkTreeDragDest C++ wrapper class.
///
/// GTK+ supports Drag-and-Drop in tree views with a high-level and a low-level API. 
///
/// The low-level API consists of the GTK+ DND API, augmented by some treeview utility
/// functions: Gtk::TreeView::set_drag_dest_row(), Gtk::TreeView::get_drag_dest_row(), 
/// Gtk::TreeView::get_dest_row_at_pos() and Gtk::TreeView::create_row_drag_icon(). 
/// This API leaves a lot of flexibility, but nothing is done automatically, and 
/// implementing advanced features like hover-to-open-rows or autoscrolling on top
/// of this API is a lot of work. 
///
/// On the other hand, if you write to the high-level TreeDragSource and TreeDragDest
/// API, then all the bookkeeping of rows is done for you, as well as things like 
/// hover-to-open and auto-scroll. The TreeDragSource interface is implemented by 
/// Gtk::TreeModelSort, Gtk::TreeStore, Gtk::ListStore and Gtk::TreeModelFilter. The
/// TreeDragDest interface is implemented by Gtk::TreeStore and Gtk::ListStore.

class TreeDragDest : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	TreeDragDest();
	///< Constructs a new TreeDragDest object.	
	
	virtual ~TreeDragDest() = 0;
	///< Destructor.

/// @}

public:
/// @name Accessors
/// @{

	GtkTreeDragDest* gtk_tree_drag_dest() const;
	///< Get a pointer to the GtkTreeDragDest structure.

	operator GtkTreeDragDest* () const;
	///< Conversion operator; safely converts a TreeDragDest to a GtkTreeDragDest pointer.

	bool row_drop_possible(const TreePath& dest_path, const SelectionData& selection_data) const;
	///< Determines whether a drop is possible before the given <EM>dest_path</EM>, 
	///< at the same depth as <EM>dest_path</EM>, that is, can we drop the data in
	///< selection_data at that location. 
	///< @param dest_path The destination row. 
	///< @param selection_data The data being dragged. 
	///< @returns <EM>true</EM> if a drop is possible before <EM>dest_path</EM>.
	///<	
	///< Note, <EM>dest_path</EM> doesn't have to exist but the return value will almost
	///< certainly be false if the parent of <EM>dest_path</EM> doesn't exist, though.

/// @}
/// @name Methods
/// @{

	bool drag_data_received(const TreePath& dest, const SelectionData& selection_data);
	///< Asks the TreeDragDest to insert a row before the path dest, deriving
	///< the contents of the row from <EM>selection_data</EM>. 
	///< @param dest The row to drop in front of. 
	///< @param selection_data The data to drop. 
	///< @return Whether a new row was created before position <EM>dest</EM>.
	///<	
	///< If dest is outside the tree so that inserting before it is impossible,
	///< false will be returned. Also, false may be returned if the new row is not
	///< created for some model-specific reason. Should robustly handle a dest no
	///< longer found in the model!
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treednd.inl>

#endif // XFC_GTK_TREE_DND_HH

