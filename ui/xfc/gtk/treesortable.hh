/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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

/// @file xfc/gtk/treesortable.hh
/// @brief A GtkTreeSortable C++ wrapper interface.
/// 
/// Provides TreeSortable, an object that defines a generic interface for sorting a model.

#ifndef XFC_GTK_TREE_SORTABLE_HH
#define XFC_GTK_TREE_SORTABLE_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef __GTK_TREE_SORTABLE_H__
#include <gtk/gtktreesortable.h>
#endif

namespace Xfc {

namespace Gtk {

class TreeIter;
class TreeModel;
class TreeSortableIface;

/// @class TreeSortable treesortable.hh xfc/gtk/treesortable.hh
/// @brief A GtkTreeSortable C++ wrapper class.
///
/// The TreeSortable interface defines a generic interface for sorting a model.
/// It is an abstract interface, and is designed to be usable with any derived 
/// class. The programmer just has to multiplely inherit this interface on their
/// own model for it to be sortable. To make life easier two generic sortable 
/// models are already provided, ListStore and TreeStore.

class TreeSortable : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	TreeSortable();
	///< Constructs a new TreeSortable object.	
	
	virtual ~TreeSortable() = 0;
	///< Destructor.

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> SortColumnChangedSignalType;
	typedef G::SignalProxy<TypeInstance, SortColumnChangedSignalType> SortColumnChangedSignalProxy;
	static const SortColumnChangedSignalType sort_column_changed_signal;
	///< Sort column changed signal (see signal_sort_column_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef sigc::slot<int, const TreeIter&, const TreeIter&> CompareSlot;
	///< Signature of the callback slot to be used for comparing two TreeIter's when sorting.
	///< <B>Example:</B> Method signature for CompareSlot.
	///< @code
	///< int method(const TreeIter& a, const TreeIter& b);
	///<
	///< // a: A TreeIter.
	///< // b: Another TreeIter.
	///< // return: -1 if "a" comes before "b" in the tree, 1 if "a" comes after "b" in
	///< //         the tree and 0 if a and b point to the same location in the tree.
	///< @endcode
	
	enum { DEFAULT_SORT_COLUMN_ID = -1, UNSORTED_SORT_COLUMN_ID = -2 };
	///< Special sort column id's.

/// @name Accessors
/// @{

	GtkTreeSortable* gtk_tree_sortable() const;
	///< Get a pointer to the GtkTreeSortable structure.

	operator GtkTreeSortable* () const;
	///< Conversion operator; safely converts a TreeSortable to a GtkTreeSortable pointer.

	bool get_sort_column_id(int *sort_column_id, SortType *order) const;
	///< Fills in <EM>sort_column_id</EM> and <EM>order</EM> with the current sort column
	///< and the order, if applicable. 
	///< @param sort_column_id The sort column id to be filled in.
	///< @param order The SortType to be filled in. 
	///< @return <EM>true</EM> if the sort column is not one of the special sort column ids.
	///<	
	///< If <EM>sort_column_id</EM> is one of the special sort column id's: DEFAULT_SORT_COLUMN_ID
	///< or UNSORTED_SORT_COLUMN_ID, <EM>false</EM> is returned.
	 
	bool has_default_sort_func() const;
	///< Returns true if the model has a default sort function. 
	///< @return <EM>true</EM> if the model has a default sort function.
	///< 
	///< This is used primarily by TreeViewColumns in order to determine if a model
	///< can go back to its default state, or not.

/// @}
/// @name Methods
/// @{

	void sort_column_changed();
	///< Emits a "sort_column_changed" signal on the sortable.
	
	void set_sort_column_id(int sort_column_id, SortType order);
	///< Sets the current sort column to be <EM>sort_column_id</EM>. 
	///< @param sort_column_id The sort column id to set. 
	///< @param order The sort order of the column.
	///<	
	///< The sortable will resort itself to reflect this change, after emitting a
	///< <EM>sort_column_changed</EM> signal. If <EM>sort_column_id</EM> is 
	///< DEFAULT_SORT_COLUMN_ID, then the default sort function will be used, if it is set.
	 
	void set_sort_func(int sort_column_id, const CompareSlot& compare);
	///< Sets the comparison callback slot used when sorting to be <EM>compare</EM>.
	///< @param sort_column_id The sort column id to set the callback slot for. 
	///< @param compare The sorting slot to call. 
	///<	 
	///< If the current sort column id of sortable is the same as <EM>sort_column_id</EM>,
	///< then the model will sort using this function.
	
	void set_default_sort_func(const CompareSlot& compare);
	///< Sets the default comparison callback slot used when sorting to be <EM>compare</EM>.
	///< @param compare The sorting slot. 
	///< 	 
	///< If the current sort_column_id of sortable is Gtk::TreeSortable::DEFAULT_SORT_COLUMN_ID,
	///< then the model will sort using this function.

	void reset_default_sort_func();
	///< Resets the default sort function to be in the 'unsorted' state. After calling this method
	///< there will be no default comparison callback slot. This means that once the model has been
	///< sorted, it can't go back to its default state. In this case, when the current sort column
	///< id of the sortable is Gtk::TreeSortable::DEFAULT_SORT_COLUMN_ID, the model will be unsorted.

/// @}
/// @name Signal Proxies
/// @{
	
	const SortColumnChangedSignalProxy signal_sort_column_changed();
	///< Connect to the sort_column_changed_signal; emitted whenever the current sort column is changed.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treesortable.inl>

#endif // XFC_GTK_TREE_SORTABLE_HH

