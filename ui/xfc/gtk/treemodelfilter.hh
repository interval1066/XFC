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

/// @file xfc/gtk/treemodelfilter.hh
/// @brief A GtkTreeModelFilter C++ wrapper interface.
///
/// Provides TreeModelFilter, a TreeModel which hides parts of an underlying tree model.

#ifndef XFC_GTK_TREE_MODEL_FILTER_HH
#define XFC_GTK_TREE_MODEL_FILTER_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_TREE_MODEL_HH
#include <xfc/gtk/treemodel.hh>
#endif

#ifndef XFC_GTK_TREE_DND_HH
#include <xfc/gtk/treednd.hh>
#endif

#ifndef __GTK_TREE_MODEL_FILTER_H__
#include <gtk/gtktreemodelfilter.h>
#endif

namespace Xfc {

namespace G {
class Value;
}

namespace Gtk {

class TreeIter;
class TreeModel;
class TreePath;

/// @class TreeModelFilter treemodelfilter.hh xfc/gtk/treemodelfilter.hh
/// @brief A GtkTreeModelFilter C++ wrapper class.
///
/// A TreeModelFilter is a tree model which wraps another tree model, and can do the following things:
/// - Filter specific rows, based on data from a "visible column", a column storing booleans indicating
///   whether the row should be filtered or not, or based on the return value of a "visible function",
///   which gets a model, iter and user_data and returns a boolean indicating whether the row should 
///   be filtered or not.
/// - Modify the "appearance" of the model, using a modify function. This is extremely powerful and 
///   allows for just changing some values and also for creating a completely different model based
///   on the given child model. 
/// - Set a different root node, also known as a "virtual root". You can pass in a Gtk::TreePath 
///   indicating the root node for the filter at construction time. 
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class TreeModelFilter :  public G::Object, public TreeModel, public TreeDragSource
{
	friend class G::Object;

	TreeModelFilter(const TreeModelFilter&);
	TreeModelFilter& operator=(const TreeModelFilter&);
	
protected:
/// @name Constructors
/// @{

	explicit TreeModelFilter(GtkTreeModelFilter *filter, bool owns_reference = true);
	///< Construct a new TreeModelFilter from an existing GtkTreeModelFilter.
	///< @param filter A pointer to a GtkTreeModelFilter.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>filter</EM> can be a newly created GtkTreeModelFilter or an existing
	///< GtkTreeModelFilter (see G::Object::Object).
	
/// @}

public:
	typedef GtkTreeModelFilter CObjectType;
	
	typedef sigc::slot<bool, const TreeModel&, const TreeIter&> VisibleSlot;
	///< Signature of the callback slot which decides whether the row indicated by TreeIter is visible.
	///< <B>Example:</B> Method signature for VisibleSlot.
	///< @code
	///< bool method(const TreeModel& model, const TreeIter& iter);
	///< // model: The Gtk::TreeModelFilter.
	///< // iter: A Gtk::TreeIter pointing to the row whose visibility is determined.
	///< // return: Whether the row indicated by iter is visible.
	///< @endcode
					       
	typedef sigc::slot<void, const TreeModel&, const TreeIter&, G::Value&, int> ModifySlot;
	///< Signature of the callback slot which calculates display values from raw values in the model.
	///< <B>Example:</B> Method signature for ModifySlot.
	///< @code
	///< void method(const TreeModel& model, const TreeIter& iter, G::Value& value, int column);
	///< // model: The Gtk::TreeModelFilter.
	///< // iter: A Gtk::TreeIter pointing to the row whose display values are determined.
	///< // value: A G::Value already initialized with the correct type for the specifed column. 
	///< // column: The column whose display value is determined. 
	///< @endcode
	///<
	///< The slot must fill the G::Value with the display value for the specified column
	///< in the row indicated by TreeIter. Since this slot is called for each data access,
	///< it's not a particularly efficient operation. 

/// @name Constructors
/// @{

	TreeModelFilter(TreeModel& child_model, const TreePath *root = 0);
	///< Constructs a new TreeModelFilter, with <EM>child_model</EM> as the child_model
	///< and <EM>root</EM> as the virtual root.
	///< @param child_model A Gtk::TreeModel. 
	///< @param root  A Gtk::TreePath or null.
	///<
	///< TreeModelFilter is created with a reference count of 1 that the caller owns. 
	
	virtual ~TreeModelFilter();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkTreeModelFilter* gtk_tree_model_filter() const;
	///< Get a pointer to the GtkTreeModelFilter structure.
	
	operator GtkTreeModelFilter* () const;
	///< Conversion operator; safely converts a TreeModelFilter to a GtkTreeModelFilter pointer.
	
	TreeModel* get_model() const;
	///< Gets a pointer to the child model of the filter.
	///< @return The child model of the filter.

/// @}
/// @name Methods
/// @{
	
	void set_visible_func(const VisibleSlot& slot);
	///< Sets the visible function used when filtering the filter to be <EM>slot</EM>. 
	///< @param slot A Gtk::TreeModelFilter::VisibleSlot, the visible callack function. 
	///<	
	///< The visible slot should return <EM>true</EM> if the given row should be visible
	///< and <EM>false</EM> otherwise.

	void set_modify_func(int n_columns, const GType types[], const ModifySlot& slot);
	///< With the <EM>n_columns</EM> and <EM>types</EM> parameters, you give an array of
	///< column types for this model (which will be exposed to the parent model/view). 
	///< @param n_columns The number of columns in the filter model. 
	///< @param types The GTypes of the columns. 
	///< @param slot A Gtk::TreeModelFilter::ModifySlot, the modify callack function.  
	///<	
	///< The modify <EM>slot</EM> will get called for each data access, the goal
	///< of the modify slot is to return the data which should be displayed at the 
	///< location specified using the parameters of the modify slot.

	void set_visible_column(int column);
	///< Sets column of the filter's child model to be the <EM>column</EM> where the 
	///< filter should look for visibility information. 
	///< @param column An integer which is the column containing the visible information.	
	///<	
	///< The columns should be a column of type G_TYPE_BOOLEAN, where <EM>true</EM>
	///< means that a row is visible, and <EM>false</EM> if not.
	
	TreeIter convert_child_iter_to_iter(const TreeIter& child_iter);
	///< Returns a TreeIter that points to the row in the TreeModelFilter that corresponds
	///< to the row pointed at by <EM>child_iter</EM>.
	///< @param child_iter A valid TreeIter pointing to a row on the child model.
	///< @return A TreeIter pointing to the row in the model being filtered.
 
	TreeIter convert_iter_to_child_iter(const TreeIter& filter_iter);
	///< Returns a TreeIter that points to the row on the child model that corresponds
	///< to the row pointed to by <EM>filter_iter</EM>.
	///< @param filter_iter A valid TreeIter pointing to a row in the TreeModelFilter.
	///< @return A TreeIter pointing to the row in the child model.
	
	Pointer<TreePath> convert_child_path_to_path(const TreePath& child_path);
	///< Converts <EM>child_path</EM> to a path relative to the TreeModelFilter.
	///< @param child_path A TreePath to convert. 
	///< @return A newly allocated TreePath, or null.
	///< 
	///< The returned path will point to the same row in the filtered model. If 
	///< <EM>child_path</EM> isn't a valid path on the child model, then null is returned.	

	Pointer<TreePath> convert_path_to_child_path(const TreePath& filter_path);
	///< Converts <EM>filter_path</EM> to a path in the child model of the TreeModelFilter. 
	///< @param filter_path A TreePath to convert. 
	///< @return A newly allocated TreePath, or null.
	///<	
	///< The returned path will point to the same row in the filtered model. If 
	///< <EM>child_path</EM> isn't a valid path in the child model, then null is returned.

	void refilter();
	///< Emits a "row_changed" for each row in the child model, which causes the filter
	///< to re-evaluate whether a row is visible or not.

	void clear_cache();
	///< This method should almost never be called. It clears the filter of any cached iterators
	///< that haven't been reffed with ref_node(). This might be useful if the child model being
	///< filtered is static (and doesn't change often) and there has been a lot of unreffed access
	///< to nodes. As a side effect of this function, all unreffed iters will become invalid.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treemodelfilter.inl>

#endif // XFC_GTK_TREE_MODEL_FILTER_HH

