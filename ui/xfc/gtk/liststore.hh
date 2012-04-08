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
 
/// @file xfc/gtk/liststore.hh
/// @brief A GtkListStore C++ wrapper interface.
/// 
/// Provides ListStore, a list model object for use with a TreeView widget.

#ifndef XFC_GTK_LIST_STORE_HH
#define XFC_GTK_LIST_STORE_HH

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

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef __GTK_LIST_STORE_H__
#include <gtk/gtkliststore.h>
#endif

namespace Xfc {

namespace Gtk {

class TreeIter;

/// @class TreeRowValues liststore.hh xfc/gtk/liststore.hh
/// @brief An object used to set multiple values in a list store row.
///
/// TreeRowValues is a wrapper object for the 'integer' and 'GValue' arrays that would
/// otherwise have to be passed to the insert_with_values() method. Rather than pass 
/// these raw arrays, passing a TreeRowValues object provides a convenient way to set a
/// new row's values when inserting a new row into a list store (see insert_with_values()).

class TreeRowValues : public StackObject
{
	TreeRowValues(const TreeRowValues&);
	TreeRowValues& operator=(const TreeRowValues&);
	
	std::vector<int> columns_;	
	std::vector<GValue*> gvalues_;

	GValue* create_value(const G::Value& value);
	
public:
/// @name Constructors
/// @{
	
	TreeRowValues();
	///< Construct a new TreeRowValues object.

	~TreeRowValues();
	///< Destructor.

/// @}
/// @name Accessors
/// @{
	
	const GValue* gvalues() const;
	///< Returns a pointer to the internal GValue array that holds the values
	///< to set in each column in a newly inserted row.
	///< @return An array of GValues. 
	
	const int* columns() const;
	///< Returns a pointer to the internal integer array that holds the column
	///< numbers of the values in the GValue array. 
	///< @return An array of column numbers. 

	unsigned int size() const;
	///< Returns the size of the internal 'integer' and 'GValue' arrays.
	///< @return The number of values added.
	
///@ }
/// @name Methods
/// @{
	
	void clear();
	///< Removes all values added to the object and frees any resources. After calling
	///< this method the TreeRowValues object is empty and can be used again. 

	void add(int column, const G::Value& value);
	///< Adds the data <EM>value</EM> to be set in the cell identified <EM>column</EM> in the new row.
	///< @param column The column number to modify.
	///< @param value  The new value for the cell.
	
	void add(int column, const char *str);
	///< Adds the string <EM>value</EM> to be set in the cell identified <EM>column</EM> in the new row.
	///< @param column The column number to modify.
	///< @param str The string for the cell.

	void add(int column, const std::string& str);
	///< Adds the string <EM>value</EM> to be set in the cell identified <EM>column</EM> in the new row.
	///< @param column The column number to modify.
	///< @param str The string for the cell.
	
	template<typename DataType>
	void add(GType type, int column, const DataType& data);
	///< Adds the <EM>data</EM> to be set in the cell identified <EM>column</EM> in the new row.
	///< @param type The GType for the column <EM>column</EM>.
	///< @param column The column number to modify.
	///< @param data The data to set for the cell.
	///<
	///< This method is used to add values corresponding to the standard data types used
	///< by G::Value, such as bool, int, double, String and unsigned int.

	template<typename DataType>
	void add_enum(GType type, int column, const DataType& data);
	///< Adds the enum <EM>data</EM> to be set in the cell identified <EM>column</EM> in the new row.
	///< @param type The GType for the column <EM>column</EM>.
	///< @param column The column number to modify.
	///< @param data The enum value to set.
	///<
	///< This method is used to set enumeration values. The DataType is the type of the
	///< enumeration being set.

	template<typename DataType>
	void add_object(GType type, int column, const DataType& data);
	///< Adds the object pointer <EM>data</EM> to be set in the cell identified <EM>column</EM> in the new row.
	///< @param type The GType for the column <EM>column</EM>.
	///< @param column The column number to modify.
	///< @param data A pointer to an object derived from G::Object, passed by reference.

	template<typename DataType>
	void add_pointer(GType type, int column, const DataType& data);
	///< Adds the pointer <EM>data</EM> to be set in the cell identified <EM>column</EM> in the new row.
	///< @param type The GType for the column <EM>column</EM>.
	///< @param column The column number to modify.
	///< @param data The pointer to set in the cell.
	///<
	///< The <EM>data</EM> argument can be a pointer to any object. The pointer is managed
	///< internally as a generic (void*) pointer. Unlike add_object() which passes the G::Object
	///< pointer internally as a GObject pointer, add_pointer() passes the pointer as is, without
	///< interpretation. 

/// @}
};	

/// @class ListStore liststore.hh xfc/gtk/liststore.hh
/// @brief A GtkListStore C++ wrapper class.
///
/// The ListStore object is a list model for use with a TreeView widget. It implements
/// the TreeModel interface, and consequentialy, can use all of the methods available
/// there. It also implements the TreeSortable interface so it can be sorted by the
/// view. Finally, it also implements the tree drag and drop interfaces.
///
/// <B>Example:</B> Creating a simple list store.
/// @code
/// #include <xfc/main.hh>
/// #include <xfc/gtk/window.hh>
/// #include <xfc/gtk/liststore.hh>
/// #include <xfc/gtk/treeview.hh>
/// #include <xfc/gtk/cellrenderer.hh>
///
/// using namespace Xfc;
///
/// class ListStoreWindow : public Gtk::Window
/// {
/// 	Pointer<Gtk::ListStore> list_store;
/// 	Gtk::TreeView *tree_view;
/// public:
/// 	ListStoreWindow();
/// };
///
/// enum
/// {
/// 	COLUMN_STRING,
/// 	COLUMN_INT,
/// 	COLUMN_BOOLEAN,
/// 	N_COLUMNS
/// };
///
/// ListStoreWindow::ListStoreWindow()
/// {
/// 	list_store = new Gtk::ListStore(N_COLUMNS, G_TYPE_STRING, G_TYPE_INT, G_TYPE_BOOLEAN);
///
/// 	Gtk::TreeIter iter;
/// 	for (int i = 0; i < 10; i++)
/// 	{
/// 		// Add a new row to the model
/// 		iter = list_store->append();
/// 		list_store->set_value(iter, COLUMN_STRING, "Some Data");
/// 		list_store->set_value(iter, COLUMN_INT, i);
/// 		list_store->set_value(iter, COLUMN_BOOLEAN, false);
/// 	}
///
/// 	// Modify a particular row
/// 	Pointer<Gtk::TreePath> path = new Gtk::TreePath("4");
/// 	list_store->get_iter(iter, *path);
/// 	list_store->set_value(iter, COLUMN_BOOLEAN, true);
///
/// 	// Create a TreeView
/// 	tree_view = new Gtk::TreeView(*list_store);
///
/// 	// Create first column, associating the "text" attribute of the cell_renderer
/// 	// with the first column of the list_store. Add column to TreeView.
/// 	Gtk::CellRendererText *renderer = new Gtk::CellRendererText;
/// 	renderer->property_foreground().set("red");
/// 	Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn("Text", renderer, "text", COLUMN_STRING, 0);
/// 	tree_view->append_column(*column);
///
/// 	// Create second column, associating the "text" attribute of the cell_renderer
/// 	// with the second column of the list_store. Add column to TreeView.
/// 	renderer = new Gtk::CellRendererText;
/// 	renderer->property_foreground().set("blue");
/// 	column = new Gtk::TreeViewColumn("Number", renderer, "text", COLUMN_INT, 0);
/// 	tree_view->append_column(*column);
///
/// 	// Create third column, associating the "active" attribute of the toggle cell_renderer
/// 	// with the second column of the list_store. Add column to TreeView. To update checkbox
/// 	// when toggled you must connect to the "toggled_signal".
/// 	Gtk::CellRendererToggle *toggle_renderer = new Gtk::CellRendererToggle;
/// 	column = new Gtk::TreeViewColumn("Boolean", toggle_renderer, "active", COLUMN_BOOLEAN, 0);
/// 	tree_view->append_column(*column);
///
/// 	add(*tree_view);
/// 	show_all();
/// }
///
/// int main (int argc, char *argv[])
/// {
/// 	using namespace Main;
///
/// 	init(&argc, &argv);
///
/// 	ListStoreWindow window;
/// 	window.signal_destroy().connect(slot(&Xfc::Main::quit));
///
/// 	run();
/// 	return 0;
/// }
/// @endcode
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/treeview.html">TreeView Widget</A> HOWTO and example.

class ListStore : public G::Object, public TreeModel, public TreeSortable, public TreeDragSource, public TreeDragDest
{
	friend class G::Object;

	ListStore(const ListStore&);
	ListStore& operator=(const ListStore&);

protected:
/// @name Constructors
/// @{

	ListStore();
	///< Constructs a new list store with a reference count of 1 that the caller owns.
	///< After calling this constructor you must call set_column_types() to set the 
	///< column types for the list store.
	
	explicit ListStore(GtkListStore *list_store, bool owns_reference = true);
	///< Construct a new ListStore from an existing GtkListStore.
	///< @param list_store A pointer to a GtkListStore.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>list_store</EM> can be a newly created GtkListStore or an existing
	///< GtkListStore (see G::Object::Object).

/// @}
/// @name Methods
/// @{

	void set_column_types(int n_columns, const GType *types);
	///< Sets the column types for the list store. 
	///< @param n_columns The number of columns in the list store.
	///< @param types An array of GType containing the column types, from first to last.
	///<
	///< This method is meant primarily for objects that derive from ListStore, and
	///< and should only be used when constructing a new list store. It will not function
	///< after a row has been added, or a method on the Gtk::TreeModel interface is called.

/// @}

public:
	typedef GtkListStore CObjectType;

/// @name Constructors
/// @{

	ListStore(int n_columns, ...);
	///< Construct a list store of <EM>n_columns</EM> columns of each of the types
	///< passed in the variable argument list.
	///< @param n_columns The number of columns in the list store.
	///< @param ... All the GType types for the columns, from first to last.
	///<
	///< As an example, ListStore(3, G_TYPE_INT, G_TYPE_STRING, GDK_TYPE_PIXBUF)
	///< will create a new list store with three columns, of type int, string and 
	///< GdkPixbuf respectively. ListStore is created with a reference count of 1
	///< that the caller owns.

	ListStore(int n_columns, const GType *types);
	///< Construct a list store of <EM>n_columns</EM> columns of each of the types
	///< passed in the array of GType.
	///< @param n_columns The number of columns in the list store.
	///< @param types An array of GType containing the column types, from first to last.
	///<
	///<  ListStore is created with a reference count of 1 that the caller owns.

	virtual ~ListStore();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkListStore* gtk_list_store() const;
	///< Get a pointer to the GtkListStore structure.

	operator GtkListStore* () const;
	///< Conversion operator; safely converts a ListStore to a GtkListStore pointer.

	bool iter_is_valid(const TreeIter& iter) const;
	///< Checks if the given <EM>iter</EM> is a valid iter for the list store.
	///< @param iter A TreeIter.
	///< @return <EM>true</EM> if the iter is valid, <EM>false</EM> if it's not.
	///<
	///< <B>WARNING:</B> This function is slow. Only use it for debugging and/or
	///< testing purposes.

/// @}
/// @name Methods
/// @{

	TreeIter prepend();
	///< Prepends a new row to a ListStore.
	///< @return An unset TreeIter set to the prepended row.
	///<
	///< The row will be empty after this method is called. To fill in values,
	///< you need to call set_value(), set_object() or set_pointer().

	TreeIter append();
	///< Appends a new row to a ListStore.
	///< @return An unset TreeIter set to the appended row.
	///<
	///< The row will be empty after this method is called. To fill in values,
	///< you need to call set_value(), set_object() or set_pointer().

	TreeIter insert(int position);
	///< Inserts a new row at <EM>position</EM>.
	///< @param position The position to insert the new row.
	///< @return An unset TreeIter set to the inserted row.
	///<
	///< If position is larger than the number of rows on the list, then the new row
	///< will be appended to the list.The row will be empty after this method is called.
	///< To fill in values, you need to call set_value(), set_object() or set_pointer().

	TreeIter insert_before(TreeIter& sibling);
	///< Inserts a new row before sibling.
	///< @param sibling A valid TreeIter.
	///< @return An unset TreeIter set to the inserted row.
	///<
	///< The row will be empty after this method is called. To fill in values,
	///< you need to call set_value(), set_object() or set_pointer().

	TreeIter insert_after(TreeIter& sibling);
	///< Inserts a new row after sibling.
	///< @param sibling A valid TreeIter.
	///< @return An unset TreeIter set to the inserted row.
	///<
	///< The row will be empty after this method is called. To fill in values,
	///< you need to call set_value(), set_object() or set_pointer().

	TreeIter insert_with_values(int position, const TreeRowValues& values);
	///< Creates a new row at <EM>position</EM> and fills the row with the values in <EM>values</EM>.
	///< @param position The position to insert the new row. 
	///< @param values A TreeRowValues object that holds the column values to set for the new row. 
	///< @return A TreeIter set to the new row.
	///<	
	///< If <EM>position</EM> is larger than the number of rows on the list, then the new row 
	///< will be appended to the list. Calling insert_with_values() has the same effect as calling:
	///<
	///< @code
	///< TreeIter iter = list_store->insert(position);
	///< list_store->set_value(iter, column, value);
	///< @endcode
	///<
	///< with the difference that the former will only emit a "row_inserted" signal, while
	///< the latter will emit "row_inserted", "row_changed" and, if the list store is sorted,
	///< "rows_reordered". Since emitting the "rows_reordered" signal repeatedly can affect
	///< the performance of the program, insert_with_values() should generally be preferred
	///< when inserting rows in a sorted list store. To use insert_with_values() do something 
	///< like this:
	///<
	///< @code
	///< enum { TEXT_COLUMN, COLOR_COLUMN, PIXBUF_COLUMN, N_COLUMNS };
	///< Gtk::ListStore *model; // allocated somewhere else	
	///< ...
	///< TreeRowValues values;
	///< values.add(TEXT_COLUMN, "text");
	///< values.add(COLOR_COLUMN, "color");
	///< values.add_object(GDK_TYPE_PIXBUF, PIXBUF_COLUMN, pixbuf);
	///< model->insert_with_values(row_number, values);
	///< @endcode
	
	bool remove(TreeIter& iter);
	///< Removes the given row from the list store. 
	///< @param iter A valid TreeIter.
	///< @return <EM>true</EM> if <EM>iter</EM> is valid, <EM>false</EM> if it's not.
	///<
	///< After being removed, iter is set to be the next valid row, or invalidated
	///< if it pointed to the last row in list_store.

	void clear();
	///< Removes all rows from the list store.

	void reorder(int *new_order);
	///< Reorders the list store to follow the order indicated by <EM>new_order</EM>.
	///< @param new_order An integer array indicating the new order for the list.
	///<
	///< <B>Note:</B> This method only works with unsorted stores.

	void swap(const TreeIter& a, const TreeIter& b);
	///< Swaps <EM>a</EM> and <EM>b</EM> in the list store.
	///< @param a A TreeIter.
	///< @param b Another TreeIter.
	///<
	///< <B>Note:</B> This method only works with unsorted stores.

	void move_after(const TreeIter& iter, const TreeIter *position);
	///< Moves <EM>iter</EM> in the list store to the position after position.
	///< @param iter A TreeIter.
	///< @param position A TreeIter, or null.
	///<
	///< <B>Note:</B> This function only works with unsorted stores. If position
	///< is null, iter will be moved to the start of the list.

	void move_before(const TreeIter& iter, const TreeIter *position);
	///< Moves <EM>iter</EM> in the list store to the position before position.
	///< @param iter A TreeIter.
	///< @param position A TreeIter, or null.
	///<
	///< <B>Note:</B> This function only works with unsorted stores. If position
	///< is null, iter will be moved to the end of the list.

	void set_value(const TreeIter& iter, int column, const G::Value& value);
	///< Sets the data in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param value  The new value for the cell.
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
	///< example of setting values in the xfc-demo program <demos/xfc-demo/liststore.cc>.

	template<typename DataType>
	void set_enum(const TreeIter& iter, int column, const DataType& data);
	///< Sets the enum data in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param data The enum value to set.
	///<
	///< This method is used to set enumeration values. The DataType is the type of the
	///< enumeration being set. There is a good example of setting values in the xfc-demo
	///< program <demos/xfc-demo/liststore.cc>.

	template<typename DataType>
	void set_object(const TreeIter& iter, int column, const DataType& data);
	///< Sets the object pointer <EM>data</EM> in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row being modified.
	///< @param column The column number to modify.
	///< @param data A pointer to an object derived from G::Object, passed by reference.
	///<
	///< There is a good example of setting values in the xfc-demo program
	///< <demos/xfc-demo/liststore.cc>.

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
	///< interpretation. There is a good example of setting values in the xfc-demo program
	///< <demos/xfc-demo/liststore.cc>.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/liststore.inl>

#endif // XFC_GTK_LIST_STORE_HH

