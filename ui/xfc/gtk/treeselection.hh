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

/// @file xfc/gtk/treeselection.hh
/// @brief A GtkTreeSelection C++ wrapper interface.

#ifndef XFC_GTK_TREE_SELECTION_HH
#define XFC_GTK_TREE_SELECTION_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef __GTK_TREE_SELECTION_H__
#include <gtk/gtktreeselection.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gtk {
	
class TreeIter;
class TreeModel;
class TreePath;
class TreeView;

/// @class TreeSelection treeselection.hh xfc/gtk/treeselection.hh
/// @brief A GtkTreeSelection C++ wrapper class.
///
/// TreeSelection is a helper object that manages the selection for a TreeView widget. The
/// TreeSelection object is automatically created when a new TreeView widget is created,
/// and cannot exist independentally of this widget. The primary reason the TreeSelection 
/// object exists is for cleanliness of code and API. That is, there is no conceptual reason
/// why all its methods could not be methods on the TreeView widget.
///
/// The TreeSelection object is gotten from a TreeView by calling Gtk::TreeView::get_selection().
/// It can be manipulated to check the selection status of the tree, as well as select and
/// deselect individual rows. Selection is done completely view side. As a result, multiple
/// views of the same model can have completely different selections. Additionally, you cannot
/// change the selection of a row on the model that is not currently displayed by the view without
/// expanding its parents first. 
///
/// One of the important things to remember when monitoring the selection of a view is that the
/// <EM>changed</EM> signal is mostly a hint. That is, it may only emit one signal when a range of
/// rows is selected. Additionally, it may on occasion emit a <EM>changed</EM> signal when nothing
/// has happened (mostly as a result of programmers calling select_row on an already selected row).
 
class TreeSelection : public G::Object
{
	friend class G::Object;

	TreeSelection(const TreeSelection&);
	TreeSelection& operator=(const TreeSelection&);

protected:
/// @name Constructors
/// @{

	explicit TreeSelection(GtkTreeSelection *tree_selection, bool owns_reference = true);
	///< Construct a new TreeSelection from an existing GtkTreeSelection.
	///< @param tree_selection A pointer to a GtkTreeSelection.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tree_selection</EM> can be a newly created GtkTreeSelection or an existing
	///< GtkTreeSelection (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;
	///< Changed signal (see signal_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkTreeSelection CObjectType;
	
	typedef sigc::slot<bool, TreeModel&, const TreePath&, bool> SelectSlot;
	///< Signature of the callback slot used by set_select_function() to filter
	///< whether or not a row may be selected.
	///< <B>Example:</B> Method signature for SelectSlot.
	///< @code
	///< bool method(TreeModel& model, const TreePath& path, bool path_currently_selected);
	///<
	///< // model: The TreeModel being viewed.
	///< // path: The TreePath of the row in question.
	///< // path_currently_selected: true if the path is currently selected.
	///< // return: true if the selection state of the row can be toggled.
	///< @endcode
	///< This slot is called whenever a row's state might change. A return value of true
	///< indicates to the TreeSelection that it is okay to change the selection.

	typedef sigc::slot<void, TreeModel&, const TreePath&, const TreeIter&> ForeachSlot;
	///< Signature of the callback slot used by selected_foreach() to map all 
	///< selected rows.
	///< <B>Example:</B> Method signature for ForeachSlot.
	///< @code
	///< void method(TreeModel& model, const TreePath& path, const TreeIter& iter);
	///<
	///< // model: The TreeModel being viewed.
	///< // path: The TreePath of a selected row. 
	///< // iter: A TreeIter pointing to a selected row. 
	///< @endcode
	///< This slot will be called on every selected row in the tree view.

/// @name Constructors
/// @{

	virtual ~TreeSelection();
	///< Desrtuctor.
	
/// @}
/// @name Accessors
/// @{

	GtkTreeSelection* gtk_tree_selection() const;
	///< Get a pointer to the GtkTreeSelection structure.

	operator GtkTreeSelection* () const;
	///< Conversion operator; safely converts a TreeSelection to a GtkTreeSelection pointer.

	SelectionMode get_mode() const;
	///< Gets the selection mode for selection (see set_mode()).
	///< @return The current selection mode.

	TreeView* get_tree_view() const;
	///< Returns the tree view associated with the selection.
	
	bool any_selected() const;
	///< Returns true if there are any selected nodes.

	bool get_selected(TreeIter *iter, TreeModel **model = 0) const;
	///< Sets <EM>iter</EM> to the currently selected node if selection is set to SELECTION_SINGLE or
	///< SELECTION_BROWSE. 
	///< @param iter The TreeIter, or null. 
	///< @param model A pointer to set to the TreeModel, or null. 
	///< @return <EM>true</EM> if there is a selected node.
	///<	
	///< <EM>iter</EM> may be null if you just want to test if selection has any selected
	///< nodes. <EM>model</EM> is filled with the current model as a convenience. This method
	///< will not work if you use the selection mode SELECTION_MULTIPLE.

	bool get_selected_rows(std::vector<TreePath>& rows, TreeModel **model = 0);
	///< Creates a list of TreePath of all selected rows.
	///< @param rows A reference to a vector of TreePath to hold the list of selected rows.
	///< @param model A pointer to set to the TreeModel, or null.
	///< @returns <EM>true</EM> if the vector is not empty.
	///<
	///< Additionally, if you are planning on modifying the model after calling this function,
	///< you may want to convert the returned list into a list of TreeRowReferences. To do this,
	///< you can use the constructor TreeRowReference(G::Object&, TreeModel&, const TreePath&).

	int count_selected_rows() const;
	///< Returns the number of rows that have been selected in the tree.

	bool path_is_selected(const TreePath& path) const;
	///< Returns true if the row pointed to by <EM>path</EM> is currently selected. 
	///< @param path A TreePath to check selection on. 
	/// @return <EM>true</EM> if <EM>path</EM> is selected.
	///<	
	///< If <EM>path</EM> does not point to a valid location, false is returned.

	bool iter_is_selected(const TreeIter& iter) const;
	///< Returns true if the row at <EM>iter</EM> is currently selected.
	///< @param iter A valid TreeIter.
	 	
/// @}
/// @name Methods
/// @{
	
	void set_mode(SelectionMode type);
	///< Sets the selection mode of the selection. 
	///< @param type The selection mode.
	///<	
	///< If the previous type was SELECTION_MULTIPLE, then the anchor is kept selected,
	///< if it was previously selected.
	 
	void set_select_function(const SelectSlot& select);
	///< Sets the selection callback slot. 
	///< @param select The selection slot to call. 
	///<	
	///< If set, this method is called before any node is selected or unselected, 
	///< giving some control over which nodes are selected. The selection slot should 
	///< return <EM>true</EM> if the state of the node may be toggled, and <EM>false</EM>
	///< if the state of the node should be left unchanged.

	void selected_foreach(const ForeachSlot& each);
	///< Calls <EM>each</EM> for each selected node. 
	///< @param each The slot to call for each selected node. 
	///<	
	///< Note that you cannot modify the tree or selection from within this method.
	///< As a result, get_selected_rows() might be more useful.
	
	void select_path(const TreePath& path);
	///< Select the row at path.
	///< @param path The TreePath to be selected.
	 
	void unselect_path(const TreePath& path);
	///< Unselects the row at path.
	///< @param path The TreePath to be unselected.
	 
	void select_iter(const TreeIter& iter);
	///< Selects the specified iterator.
	///< @param iter The TreeIter to be selected. 

	void unselect_iter(const TreeIter& iter);
	///< Unselects the specified iterator.
	///< @param iter The TreeIter to be unselected. 

	void select_all();
	///< Selects all the nodes. The selection mode is must be set to SELECTION_MULTIPLE.
	
	void unselect_all();
	///< Unselects all the nodes.
 
	void select_range(const TreePath& start_path, const TreePath& end_path);
	///< Selects a range of nodes, determined by <EM>start_path</EM> and <EM>end_path</EM> inclusive.
	///< @param start_path The initial node of the range.
	///< @param end_path The final node of the range.

	void unselect_range(const TreePath& start_path, const TreePath& end_path);
	///< Unselects a range of nodes, determined by start_path and end_path inclusive.
	///< @param start_path The initial node of the range.
	///< @param end_path The final node of the range.

/// @}
/// @name Signal Proxies
/// @{
	
	const ChangedSignalProxy signal_changed();
	///< Connect to the changed_signal; emitted whenever the selection has (possibly) changed.
	///< Please note that this signal is mostly a hint. It may only be emitted once when a 
	///< range of rows are selected, and it may occasionally be emitted when nothing has happened.
		
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treeselection.inl>

#endif // XFC_GTK_TREE_SELECTION_HH

