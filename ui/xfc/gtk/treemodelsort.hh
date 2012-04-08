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

/// @file xfc/gtk/treemodelsort.hh
/// @brief A GtkTreeModelSort C++ wrapper interface.
///
/// Provides TreeModelSort, an object that implements a model that can be sorted.

#ifndef XFC_GTK_TREE_MODEL_SORT_HH
#define XFC_GTK_TREE_MODEL_SORT_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_TREE_MODEL_HH
#include <xfc/gtk/treemodel.hh>
#endif

#ifndef XFC_GTK_TREE_SORTABLE_HH
#include <xfc/gtk/treesortable.hh>
#endif

#ifndef XFC_GTK_TREE_DND_HH
#include <xfc/gtk/treednd.hh>
#endif

#ifndef __GTK_TREE_MODEL_SORT_H__
#include <gtk/gtktreemodelsort.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class TreeModelSort treemodelsort.hh xfc/gtk/treemodelsort.hh
/// @brief A GtkTreeModelSort C++ wrapper class.
///
/// TreeModelSort implements a model that can be sorted.

class TreeModelSort :  public G::Object, public TreeModel, public TreeSortable, public TreeDragSource
{
	friend class G::Object;

	TreeModelSort(const TreeModelSort&);
	TreeModelSort& operator=(const TreeModelSort&);
	
protected:
/// @name Constructors
/// @{

	explicit TreeModelSort(GtkTreeModelSort *tree_model, bool owns_reference = true);
	///< Construct a new TreeModelSort from an existing GtkTreeModelSort.
	///< @param tree_model A pointer to a GtkTreeModelSort.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tree_model</EM> can be a newly created GtkTreeModelSort or an existing
	///< GtkTreeModelSort (see G::Object::Object).
	
/// @}

public:
	typedef GtkTreeModelSort CObjectType;

/// @name Constructors
/// @{

	TreeModelSort(TreeModel& child_model);
	///< Constructs a new tree model, with <EM>child_model</EM> as the child model.
	///< @param child_model A TreeModel.
	///<
	///< TreeModelSort is created with a reference count of 1 that the caller owns.  
	
	virtual ~TreeModelSort();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkTreeModelSort* gtk_tree_model_sort() const;
	///< Get a pointer to the GtkTreeModelSort structure.
	
	operator GtkTreeModelSort* () const;
	///< Conversion operator; safely converts a TreeModelSort to a GtkTreeModelSort pointer.
	
	TreeModel* get_model() const;
	///< Returns the model the TreeModelSort is sorting.
	///< @return The "child model" being sorted.

	bool iter_is_valid(const TreeIter& iter) const;
	///< Checks if the given iter is a valid iter for this TreeModelSort.
	///< @param iter A TreeIter.
	///< @return <EM>true</EM> if the iter is valid, <EM>false</EM> if the iter is invalid.
	///<
	///< <B>WARNING:</B> This function is slow. Only use it for debugging and/or testing purposes.

/// @}
/// @name Methods
/// @{

	Pointer<TreePath> convert_child_path_to_path(const TreePath& child_path);
	///< Converts <EM>child_path</EM> to a path relative to the TreeModelSort.
	///< @param child_path A TreePath to convert. 
	///< @return A newly allocated TreePath, or null.
	///< 
	///< <EM>child_path</EM> points to a path in the child model. The returned path
	///< will point to the same row in the sorted model. If <EM>child_path</EM> isn't a
	///< valid path on the child model, then null is returned.

	TreeIter convert_child_iter_to_iter(const TreeIter& child_iter);
	///< Returns a TreeIter that points to the row in the TreeModelSort that corresponds
	///< to the row pointed at by <EM>child_iter</EM>.
	///< @param child_iter A valid TreeIter pointing to a row on the child model.
	///< @return A TreeIter pointing to the row in the model being sorted.
	 
	Pointer<TreePath> convert_path_to_child_path(const TreePath& sorted_path);
	///< Converts <EM>sorted_path</EM> to a path on the child model of the TreeModelSort. 
	///< @param sorted_path A TreePath to convert. 
	///< @return A newly allocated TreePath, or null.
	///<	
	///< <EM>sorted_path</EM> points to a location in the TreeModelSort. The returned path
	///< will point to the same location in the model not being sorted. If <EM>sorted_path</EM>
	///< does not point to a location in the child model, null is returned.
	
	TreeIter convert_iter_to_child_iter(const TreeIter& sorted_iter);
	///< Returns a TreeIter that points to the row on the model being sorted that corresponds
	///< to the row on the TreeModelSort pointed to by <EM>sorted_iter</EM>.
	///< @param sorted_iter A valid TreeIter pointing to a row on the TreeModelSort.
	///< @return A TreeIter pointing to the row on the model being sorted.
			
	void reset_default_sort_func();
	///< This resets the default sort function to be in the 'unsorted' state. That is, it is in
	///< the same order as the child model. It will re-sort the model to be in the same order as
	///< the child model only if the TreeModelSort is in 'unsorted' state.
	
	void clear_cache();
	///< This method should almost never be called. It clears the TreeModelSort of any cached
	///< iterators that haven't been reffed with ref_node(). This might be useful if the child
	///< model being sorted is static (and doesn't change often) and there has been a lot of
	///< unreffed access to nodes. As a side effect of this function, all unreffed iters will
	///< become invalid.
 
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treemodelsort.inl>

#endif // XFC_GTK_TREE_MODEL_SORT_HH

