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
 
/// @file xfc/gtk/treestore.hh
/// @brief A GtkTreeStore C++ wrapper interface.
/// 
/// Provides TreeStore, a tree-like model object for use with a TreeView widget.

#ifndef XFC_GTK_TREE_STORE_HH
#define XFC_GTK_TREE_STORE_HH

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

#ifndef __GTK_TREE_STORE_H__
#include <gtk/gtktreestore.h>
#endif

namespace Xfc {

namespace Gtk {

class TreeIter;

/// @class TreeStore treestore.hh xfc/gtk/treestore.hh
/// @brief A GtkTreeStore C++ wrapper class.
///
/// The TreeStore object is a tree-like model for use with a TreeView widget. It implements the
/// TreeModel interface, and consequentialy, can use all of the methods available there.
/// It also implements the TreeSortable interface so it can be sorted by the view. Finally,
/// it also implements the tree drag and drop interfaces (see Gtk::ListStore). 
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/treeview.html">TreeView Widget</A> HOWTO and example.

class TreeStore : public G::Object, public TreeModel, public TreeSortable, public TreeDragSource, public TreeDragDest
{
	friend class G::Object;

	TreeStore(const TreeStore&);
	TreeStore& operator=(const TreeStore&);

protected:
/// @name Constructors
/// @{

	TreeStore();
	///< Constructs a new tree store with a reference count of 1 that the caller owns.
	///< After calling this constructor you must call set_column_types() to set column
	///< types for the tree store.
	
	explicit TreeStore(GtkTreeStore *tree_store, bool owns_reference = true);
	///< Construct a new TreeStore from an existing GtkTreeStore.
	///< @param tree_store A pointer to a GtkTreeStore.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tree_store</EM> can be a newly created GtkTreeStore or an existing
	///< GtkTreeStore (see G::Object::Object).
	
/// @}
/// @name Methods
/// @{

	void set_column_types(int n_columns, const GType *types);
	///< Sets the column types for the tree store. 
	///< @param n_columns The number of columns in the tree store.
	///< @param types An array of GType containing the column types, from first to last.
	///<
	///< This method is meant primarily for objects that derive from TreeStore, and
	///< and should only be used when constructing a new tree store. It will not function
	///< after a row has been added, or a method on the Gtk::TreeModel interface is called.

/// @}

public:
	typedef GtkTreeStore CObjectType;

/// @name Constructors
/// @{

	TreeStore(int n_columns, ...);
	///< Construct a tree store of n_columns columns of each of the types passed in the variable argument list.
	///< @param n_columns The number of columns in the tree store.
	///< @param ... All the GType types for the columns, from first to last.
	///<
	///< As an example, TreeStore(3, G_TYPE_INT, G_TYPE_STRING, GDK_TYPE_PIXBUF) will create
	///< a new tree store with three columns, of type int, string and GdkPixbuf respectively.
	///< TreeStore is created with a reference count of 1 that the caller owns.

	TreeStore(int n_columns, const GType *types);
	///< Construct a tree store of <EM>n_columns</EM> columns of each of the types
	///< passed in the array of GType.
	///< @param n_columns The number of columns in the tree store.
	///< @param types An array of GType containing the column types, from first to last.
	///<
	///< TreeStore is created with a reference count of 1 that the caller owns.

	virtual ~TreeStore();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkTreeStore* gtk_tree_store() const;
	///< Get a pointer to the GtkTreeStore structure.

	operator GtkTreeStore* () const;
	///< Conversion operator; safely converts a TreeStore to a GtkTreeStore pointer.

	bool is_ancestor(const TreeIter& iter, const TreeIter& descendant) const;
	///< Returns true if <EM>iter</EM> is an ancestor of <EM>descendant</EM>, that is,
	///< <EM>iter</EM> is the parent (or grandparent or great-grandparent) of descendant.
	///< @param iter A valid TreeIter.
	///< @param descendant A valid TreeIter. 
	///< @return <EM>true</EM> if iter is an ancestor of descendant.
	 
	int iter_depth(const TreeIter& iter) const;
	///< Returns the depth of <EM>iter</EM>. 
	///< @param iter A valid TreeIter.
	///< @return The depth of <EM>iter</EM>.
	///<
	///< The depth will be 0 for anything on the root level, 1 for anything down a level, etc.

	bool iter_is_valid(const TreeIter& iter) const;
	///< Checks if the given <EM>iter</EM> is a valid iter for the tree store.
	///< @param iter A TreeIter.
	///< @return <EM>true</EM> if the iter is still valid, <EM>false</EM> if it's not.
	///<
	///< <B>WARNING:</B> This function is slow. Only use it for debugging and/or testing purposes.

/// @}
/// @name Methods
/// @{

	TreeIter prepend(TreeIter *parent = 0);
	///< Prepends a new row to the tree store. 
	///< @param parent A valid TreeIter, or null.
	///< @return An unset TreeIter to set to the prepended row. 
	///<	
	///< If parent is non-null, then it will prepend the new row before the first child
	///< of <EM>parent</EM>, otherwise it will prepend a row to the top level. The returned
	///< TreeIter will point to this new row. The row will be empty after this function is
	///< called. To fill in values, you need to call set_value() or set_value_type().

	TreeIter append(TreeIter *parent = 0);
	///< Appends a new row to the tree store. 
	///< @param parent A valid TreeIter, or null.
	///< @return An unset TreeIter to set to the appended row. 
	///<	
	///< If parent is non-null, then it will append the new row after the last child
	///< of <EM>parent</EM>, otherwise it will append a row to the top level. The returned
	///< TreeIter will point to this new row. The row will be empty after this function is
	///< called. To fill in values, you need to call set_value() or set_value_type().

	TreeIter insert(int position, TreeIter *parent = 0);
	///< Creates a new row at <EM>position</EM>.
	///< @param position The position to insert the new row.
	///< @param parent A valid TreeIter, or null.
	///< @return An TreeIter set to the new row. 
	///<	
	///< If parent is non-null, then the row will be made a child of parent. Otherwise,
	///< the row will be created at the toplevel. If position is larger than the number of
	///< rows at that level, then the new row will be inserted to the end of the list. An
	///< empty TreeIter pointing to the new row is returned. To fill in values, you need to
	///< call set_value() or set_value_type().
	
	TreeIter insert_before(TreeIter& sibling, TreeIter *parent = 0);
	///< Inserts a new row before <EM>sibling</EM>. 
	///< @param sibling A valid TreeIter. 
	///< @param parent A valid TreeIter, or null. 
	///< @return An TreeIter set to the new row. 
	///<	
	///< <EM>parent</EM> is optional but if set it must be the parent of <EM>sibling</EM>. 
	///< An empty TreeIter pointing to the new row is returned. To fill in values, you need
	///< to call set_value() or set_value_type().

	TreeIter insert_after(TreeIter& sibling, TreeIter *parent = 0);
	///< Inserts a new row after <EM>sibling</EM>. 
	///< @param sibling A valid TreeIter. 
	///< @param parent A valid TreeIter, or null. 
	///< @return An TreeIter set to the new row. 
	///<
	///< <EM>parent</EM> is optional but if set it must be the parent of <EM>sibling</EM>. 
	///< An empty TreeIter pointing to the new row is returned. To fill in values, you need
	///< to call set_value() or set_value_type().

	bool remove(TreeIter& iter);
	///< Removes iter from the tree store. 
	///< @param iter A valid TreeIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> is valid, <EM>false</EM> if it's not.
	///<
	///< After being removed, iter is set to the next valid row at that level, or invalidated
	///< if it previously pointed to the last one.

	void clear();
	///< Removes all rows from the tree store.
 
	void reorder(const TreeIter& parent, int *new_order);
	///< Reorders the children of <EM>parent</EM> in the tree store to follow the order
	///< indicated by <EM>new_order</EM>.
	///< @param parent A TreeIter.
	///< @param new_order An integer array indicating the new order for the list.
	///<
	///< <B>Note:</B> This method only works with unsorted stores.

	void swap(const TreeIter& a, const TreeIter& b);
	///< Swaps <EM>a</EM> and <EM>b</EM> in the same level of the tree store.
	///< @param a A TreeIter.
	///< @param b Another TreeIter.
	///<
	///< <B>Note:</B> This method only works with unsorted stores.

	void move_after(const TreeIter& iter, const TreeIter *position);
	///< Moves <EM>iter</EM> in the tree store to the position after position
	///< (iter and position should be in the same level).
	///< @param iter A TreeIter.
	///< @param position A TreeIter, or null.
	///<
	///< <B>Note:</B> This function only works with unsorted stores. If position
	///< is null, iter will be moved to the start of the level.

	void move_before(const TreeIter& iter, const TreeIter *position);
	///< Moves <EM>iter</EM> in the tree store to the position before position
	///< (iter and position should be in the same level).
	///< @param iter A TreeIter.
	///< @param position A TreeIter, or null.
	///<
	///< <B>Note:</B> This function only works with unsorted stores. If position
	///< is null, iter will be moved to the end of the level.

	void set_value(const TreeIter& iter, int column, const G::Value& value);
	///< Sets the data in the cell specified by <EM>iter</EM> and <EM>column</EM>.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param value The new value for the cell.
	///< 	 
	///< The type of value must be convertible to the type of the column.

	void set_value(const TreeIter& iter, int column, const char *str);
	///< Sets a string value in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param str The new string for the cell.
	
	void set_value(const TreeIter& iter, int column, const std::string& str);
	///< Sets a string value in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param str The new string for the cell.

/// @}
/// @name Templates
/// @{
	
	template<typename DataType>
	void set_value(const TreeIter& iter, int column, const DataType& data);
	///< Sets the data in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param data The data to set for the cell.
	///<
	///< This method is used to set values corresponding to the standard data types used
	///< by G::Value, such as bool, int, double, String and unsigned int. There is a good
	///< example of setting values in the gfc-demo program <demos/gfc-demo/liststore.cc>.

	template<typename DataType>
	void set_enum(const TreeIter& iter, int column, const DataType& data);
	///< Sets the enum data in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param data The enum value to set.
	///<
	///< This method is used to set enumeration values. The DataType is the type of the
	///< enumeration being set. There is a good example of setting values in the gfc-demo
	///< program <demos/gfc-demo/liststore.cc>.

	template<typename DataType>
	void set_object(const TreeIter& iter, int column, const DataType& data);
	///< Sets the object pointer <EM>data</EM> in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param data A pointer to an object derived from G::Object, passed by reference.
	///<
	///< There is a good example of setting values in the gfc-demo program
	///< <demos/gfc-demo/liststore.cc>.

	template<typename DataType>
	void set_pointer(const TreeIter& iter, int column, const DataType& data);
	///< Sets the pointer <EM>data</EM> in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param data The pointer to set in the cell.
	///<
	///< The <EM>data</EM> argument can be a pointer to any object. The pointer is managed
	///< internally as a generic (void*) pointer. Unlike set_object() which passes the G::Object
	///< pointer internally as a GObject pointer, set_pointer() passes the pointer as is, without
	///< interpretation. There is a good example of setting values in the gfc-demo program
	///< <demos/gfc-demo/liststore.cc>.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treestore.inl>

#endif // XFC_GTK_TREE_STORE_HH

