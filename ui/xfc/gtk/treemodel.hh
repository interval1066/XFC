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
 
/// @file xfc/gtk/treemodel.hh
/// @brief A GtkTreePath, GtkTreeIter, GtkTreeModel, and GtkTreeRowReference C++ wrapper interface.
///
/// Provides TreeIter, TreePath, TreeModel and TreeRowReference, a set of objects that defines 
/// a generic tree interface for use by the TreeView widget. It is an abstract interface, and
/// is designed to be usable with any derived class. 

#ifndef XFC_GTK_TREE_MODEL_HH
#define XFC_GTK_TREE_MODEL_HH

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef XFC_G_VALUE_HH
#include <xfc/glib/value.hh>
#endif

#ifndef __GTK_TREE_MODEL_H__
#include <gtk/gtktreemodel.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Object;
class Value;
}

namespace Gtk {
	
class SelectionData;

/// @enum TreeModelFlags
/// These flags indicate various properties of a TreeModel. They are returned by 
/// Gtk::TreeModel::get_flags(), and must be static for the lifetime of the object.
/// A more complete description of TREE_MODEL_ITERS_PERSIST can be found in the
/// TreeModel desription. 

enum TreeModelFlags
{
	TREE_MODEL_ITERS_PERSIST = GTK_TREE_MODEL_ITERS_PERSIST,
	///< Iterators survive all signals emitted by the tree. 
	
	TREE_MODEL_LIST_ONLY = GTK_TREE_MODEL_LIST_ONLY
	///< The model is a list only, and never has children. 
};

/// TreeModelFlagsField holds one or more values from the Gtk::TreeModelFlags enumeration OR'd together.

typedef unsigned int TreeModelFlagsField;

/// @class TreePath treemodel.hh xfc/gtk/treemodel.hh
/// @brief A GtkTreePath C++ wrapper class.
///
/// A tree path is essentially a potential node. It is a location on a tree model that
/// may or may not actually correspond to a node on a specific model. The TreePath can
/// be converted into either a vector of integers or a string. The string form is a 
/// list of numbers separated by a colon. Each number refers to the offset at that
/// level. Thus, the path "0" refers to the root node and the path "2:4" refers to the
/// fifth child of the third node. 
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class TreePath : public G::Boxed
{
public:
/// @name Constructors
/// @{

	TreePath();
	///< Constructs a new tree path with a reference count of 1 that the caller owns.

	explicit TreePath(const char *path);
	explicit TreePath(const String& path);
	///< Constructs a new tree path initialized to <EM>path</EM>, or the root if <EM>path</EM> is null.
	///< @param path The string representation of a path.
	///<	
	///< The <EM>path</EM> is expected to be a colon separated list of numbers.
	///< For example, the string "10:4:0" would create a path of depth 3 pointing
	///< to the 11th child of the root node, the 5th child of that 11th child, and
	///< the 1st child of that 5th child. The TreePath is created with a reference
	///< count of 1 that the caller owns.

	explicit TreePath(int first_index, ...);
	///< Constructs a new path with <EM>first_index</EM> and <EM>varargs</EM> as the indices.
	///< @param first_index The first integer.
	///< @param ... A list of integers, terminated by -1.
	///<
	///< The TreePath is created with a reference count of 1 that the caller owns.
	
	explicit TreePath(GtkTreePath *path);
	///< Constructs a new tree path from an existing GtkTreePath.
	///< @param path A pointer to a GtkTreePath.
	///<
	///< The <EM>path</EM> can be a newly created GtkTreePath or an existing
	///< GtkTreePath. The TreePath object created is a temporary object. It doesn't
	///< take over the ownership of GtkTreePath and GtkTreePath is not freed by the
	///< destructor. The TreePath is created with a reference count of 1 that the
	///< caller owns.

	TreePath(GtkTreePath *path, bool copy);
	///< Constructs a new text iterator from an existing GtkTreePath.
	///< @param path A pointer to a GtkTreePath.
	///< @param copy Whether the TreePath object should make a copy of GtkTreePath or not.
	///<
	///< The <EM>path</EM> can be a newly created GtkTreePath or an existing GtkTreePath.
	///< If <EM>copy</EM> is true TreePath will make a copy of GtkTreePath. If <EM>copy</EM>
	///< is false TreePath wont make a copy but instead takes over the ownership of GtkTreePath.
	///< Either way, the destructor will free GtkTreePath when the TreePath object is destroyed.
	///< The TreePath is created with a reference count of 1 that the caller owns. This 
	///< constructor is used by G::Boxed::wrap() to wrap GtkTreePath objects in a C++ wrapper.

	TreePath(const TreePath& src);
	///< Copy constructor.
	///< @param src The source tree path.

	~TreePath();
	///< Destructor.

	TreePath& operator=(const TreePath& src);
	///< Assignment operator.
	///< @param src The source tree path.

/// @}
/// @name Accessors
/// @{

	GtkTreePath* gtk_tree_path() const;
	///< Get a pointer to the GtkTreePath structure.
	
	operator GtkTreePath* () const;
	///< Conversion operator; safely converts a TreePath to a GtkTreePath pointer.
	
	String to_string() const;
	///< Generates a string representation of the path. This string is a ':' separated
	///< list of numbers. For example, "4:10:0:3" would be an acceptable return value
	///< for this string.
	
	int get_depth() const;
	///< Returns the current depth of the path.

	std::vector<int> get_indices() const;
	///< Returns the current indices of the path as a vector of integers,
	///< each integer representing a node in a tree.
	
	int compare(const TreePath& other) const;
	///< Compares two paths. 
	///< @param other A TreePath to compare with. 
	///< @return The relative positions of two paths.
	///<	
	///< If this path appears before <EM>other</EM> in a tree, then -1 is returned.
	///< If <EM>other</EM> appears before this path, then 1 is returned. If the two 
	///< nodes are equal, then 0 is returned.

	bool is_ancestor(const TreePath& descendant) const;
	///< Returns true if descendant is a descendant of this path.
	///< @param descendant Another TreePath. 
	///< @return <EM>true</EM> if descendant is contained inside this path.
		
	bool is_descendant(const TreePath& ancestor) const;
	///< Returns true if path is a descendant of ancestor.
	///< @param ancestor Another TreePath. 
	///< @return <EM>true</EM> if ancestor contains path somewhere below it.
	 	
	bool operator==(const TreePath& other) const;
	///< Returns true if this path is equal to other.
	
	bool operator!=(const TreePath& other) const;
	///< Returns true if this path is not equal to other.
	
	bool operator<(const TreePath& other) const;
	///< Returns true if this path appears before other in a tree.
	
	bool operator>(const TreePath& other) const;
	///< Returns true if this path appears after other in a tree.
	
/// @}
/// @name Methods
/// @{

	void append_index(int index);
	///< Appends a new index to the path; as a result, the depth of the path is increased.
	///< @param index The index. 
		
	void prepend_index(int index);
	///< Prepends a new index to the path; as a result, the depth of the path is increased.
	///< @param index The index.
		
	void next();
	///< Moves the path to point to the next node at the current depth.
		
	bool prev();
	///< Moves the path to point to the previous node at the current depth, if it exists.
	///< @return <EM>true</EM> if the path has a previous node, and the move was made.
	 	
	bool up();
	///< Moves the path to point to it's parent node, if it has a parent.
	///< @return <EM>true</EM> if the path has a parent, and the move was made.
		
	void down();
	///< Moves the path to point to the first child of the current path.
	
/// @}
};

/// @class TreeIter treemodel.hh xfc/gtk/treemodel.hh
/// @brief A GtkTreeIter C++ wrapper class.
///
/// A TreeIter is a reference to a specific node on a specific model. It is a generic class with
/// an integer and three generic pointers. These are filled in by the model in a model-specific
/// way. One can convert a path to an iterator by calling Gtk::TreeModel::get_iter(). These
/// iterators are the primary way of accessing a model and are similar to the iterators used
/// by TextBuffer. They are generally statically allocated on the heap and only used for a
/// short time. The TreeModel interface defines a set of operations using them for navigating
/// the model. TreeIter is StackObject and can only be created on the stack. 
///
/// Note: <EM>TreeIter is a object that can only be created on the stack.</EM> 

class TreeIter : public G::Boxed, public StackObject
{
public:
/// @name Constructors
/// @{

	TreeIter();
	///< Construct an properly initialized tree iterator.
	
	explicit TreeIter(GtkTreeIter *iter);
	///< Construct a new tree iterator from an existing GtkTreeIter.
	///< @param iter A pointer to a GtkTreeIter.
	///<
	///< The <EM>iter</EM> can be a newly created GtkTreeIter or an existing
	///< GtkTreeIter. The TreeIter object created is a temporary object. It doesn't
	///< take over the ownership of GtkTreeIter and GtkTreeIter is not freed by the
	///< destructor.

	TreeIter(GtkTreeIter *iter, bool copy);
	///< Construct a new text iterator from an existing GtkTreeIter.
	///< @param iter A pointer to a GtkTreeIter.
	///< @param copy Whether the TreeIter object should make a copy of GtkTreeIter or not.
	///<
	///< The <EM>iter</EM> can be a newly created GtkTreeIter or an existing GtkTreeIter.
	///< If <EM>copy</EM> is true TreeIter will make a copy of GtkTreeIter. If <EM>copy</EM>
	///< is false TreeIter wont make a copy but instead takes over the ownership of GtkTreeIter.
	///< Either way, the destructor will free GtkTreeIter when the TreeIter object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap GtkTreeIter objects in a C++ wrapper.

	TreeIter(const TreeIter& src);
	///< Copy constructor.
	///< @param src The source tree iterator.

	~TreeIter();
	///< Destructor.

	TreeIter& operator=(const TreeIter& src);
	///< Assignment operator.
	///< @param src The source tree iterator.
	
/// @}
/// @name Accessors
/// @{

	GtkTreeIter* gtk_tree_iter() const;
	///< Get a pointer to the GtkTreeIter structure.

	operator GtkTreeIter* () const;
	///< Conversion operator; safely converts a TreeIter to a GtkTreeIter pointer.

/// @}
};

/// @class TreeModel treemodel.hh xfc/gtk/treemodel.hh
/// @brief A GtkTreeModel C++ wrapper class.
///
/// The TreeModel interface defines a generic tree interface for use by the TreeView widget.
/// It is an abstract interface, and is designed to be usable with any derived class. The 
/// programmer just has to multiplely inherit this interface on their own class for it to
/// be viewable by a TreeView widget.
///
/// The model is represented as a hierarchical tree of strongly-typed, columned data. In 
/// other words, the model can be seen as a tree where every node has different values 
/// depending on which column is being queried. The type of data found in a column is 
/// determined by using the GType system (ie. G_TYPE_INT, GTK_TYPE_BUTTON, G_TYPE_POINTER,
/// etc.). The types are homogeneous per column across all nodes. It is important to note
/// that this interface only provides a way of examining a model and observing changes. 
/// The implementation of each individual model decides how and if changes are made. 
///
/// In order to make life simpler for programmers who do not need to write their own 
/// specialized model, two generic models are provided - the TreeStore and the ListStore.
/// To use these, the developer simply pushes data into these models as necessary. These
/// models provide the data structure as well as all appropriate tree interfaces. As a
/// result, implementing drag and drop, sorting, and storing data is trivial. For the vast
/// majority of trees and lists, these two models are sufficient. 
///
/// Models are accessed on a node/column level of granularity. One can query for the value
/// of a model at a certain node and a certain column on that node. There are two structures
/// used to reference a particular node in a model. They are the TreePath and the TreeIter.
/// Most of the interface consists of operations on a TreeIter. A tree path is essentially
/// a potential node. It is a location on a model that may or may not actually correspond
/// to a node on a specific model. The TreePath object can be converted into either an vector
/// of integers or a string. The string form is a list of numbers separated by a colon. 
/// Each number refers to the offset at that level. Thus, the path "0" refers to the root
/// node and the path "2:4" refers to the fifth child of the third node. By contrast, a
/// TreeIter is a reference to a specific node on a specific model. It is a generic struct
/// with an integer and three generic pointers. These are filled in by the model in a 
/// model-specific way. One can convert a path to an iterator by calling get_iter(). These
/// iterators are the primary way of accessing a model and are similar to the iterators used
/// by TextBuffer. They are generally statically allocated on the heap and only used for a
/// short time. The model interface defines a set of operations using them for navigating the
/// model. 
///
/// It is expected that models fill in the iterator with private data. For example, the 
/// ListStore model, which is internally a simple linked list, stores a list node in one of
/// the pointers. The TreeModelSort stores an array and an offset in two of the pointers.
/// Additionally, there is an integer field. This field is generally filled with a unique
/// stamp per model. This stamp is for catching errors resulting from using invalid iterators
/// with a model. 
///
/// The lifecycle of an iterator can be a little confusing at first. Iterators are expected
/// to always be valid for as long as the model is unchanged (and doesn't emit a signal). The
/// model is considered to own all outstanding iterators and nothing needs to be done to free
/// them from the user's point of view. Additionally, some models guarantee that an iterator
/// is valid for as long as the node it refers to is valid (most notably the TreeStore and
/// ListStore). Although generally uninteresting, as one always has to allow for the case where 
/// iterators do not persist beyond a signal, some very important performance enhancements were
/// made in the sort model. As a result, the TREE_MODEL_ITERS_PERSIST flag was added to 
/// indicate this behavior. 
///
/// To help show some common operations of a model, two examples are provided. The first example
/// shows three ways of getting the iter at the location "3:2:5". While the first method shown
/// is easier, the second is much more common, as you often get paths from callbacks.
///
/// <B>Example 1:</B> Three ways of getting the TreeIter pointing to a location
/// @code
/// Gtk::TreeIter iter;
///
/// // Get the iterator from a string
/// model->get_iter(iter, "3:2:5");
///
/// // Get the iterator from a path
/// Pointer<Gtk::TreePath> path = new Gtk::TreePath("3:2:5");
/// model->get_iter(iter, path);
///
/// // Walk the tree to find the iterator
/// model->iter_nth_child(iter, 0, 3);
/// Gtk::TreeIter parent_iter = iter;
/// model->iter_nth_child(iter, parent_iter, 2);
/// parent_iter = iter;
/// model->iter_nth_child(iter, parent_iter, 5);
/// @endcode
///
/// This second example shows a quick way of iterating through a list and getting a string and
/// an integer from each row. See the ListStore documentation for an example on constructing a
/// ListStore model.
///
/// <B>Example 2:</B> Reading data from a TreeModel
/// @code
/// Gtk::TreeIter iter;
///
/// // Get the first iter in the list
/// bool valid = model->get_iter_first(iter);
/// int row_count = 0;
///
/// while (valid)
/// {
/// 	/// Walk through the list, reading each row.
/// 	String str_data;
///	model->get_value(iter, STRING_COLUMN, str_data);
/// 	int int_data;
///	model->get_value(iter, INT_COLUMN, int_data);
///
/// 	// Do something with the data
/// 	g_print("Row %d: (%s,%d)\n", row_count, str_data.c_str(), int_data);
/// 
/// 	row_count++;
/// 	valid = model->iter_next(iter);
/// }
/// @endcode
///
/// <B>See also:</B> the <A HREF="../../howto/html/treeview.html">TreeView Widget</A> HOWTO and example.

class TreeModel : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	TreeModel();
	///< Constructs a new TreeModel object.	
	
	virtual ~TreeModel() = 0;
	///< Destructor.
	
/// @}
/// @name Signal Prototpyes
/// @{

	typedef G::Signal<void, TreePath&, TreeIter&> RowChangedSignalType;
	typedef G::SignalProxy<TypeInstance, RowChangedSignalType> RowChangedSignalProxy;
	static const RowChangedSignalType row_changed_signal;
	///< Row changed signal (see signal_row_changed()). Calls a slot with the signature:
	///< @code
	///< void function(const TreePath& path, const TreeIter& iter);
	///< // path: A TreePath pointing to the changed row.
	///< // iter: A valid TreeIter pointing to the changed row.
	///< @endcode

	typedef G::Signal<void, TreePath&, TreeIter&> RowInsertedSignalType;
	typedef G::SignalProxy<TypeInstance, RowInsertedSignalType> RowInsertedSignalProxy;
	static const RowInsertedSignalType row_inserted_signal;
	///< Row inserted signal (see signal_row_inserted()). Calls a slot with the signature:
	///< @code
	///< void function(const TreePath& path, const TreeIter& iter);
	///< // path: A TreePath pointing to the inserted row.
	///< // iter: A valid TreeIter pointing to the inserted row.
	///< @endcode

	typedef G::Signal<void, TreePath&, TreeIter&> RowHasChildToggledSignalType;
	typedef G::SignalProxy<TypeInstance, RowHasChildToggledSignalType> RowHasChildToggledSignalProxy;
	static const RowHasChildToggledSignalType row_has_child_toggled_signal;
	///< Row has child toggled signal (see signal_row_has_child_toggled()). Calls a slot with the signature:
	///< @code
	///< void function(const TreePath& path, const TreeIter& iter);
	///< // path: A TreePath pointing to the changed row.
	///< // iter: A valid TreeIter pointing to the changed row.
	///< @endcode

	typedef G::Signal<void, TreePath&> RowDeletedSignalType;
	typedef G::SignalProxy<TypeInstance, RowDeletedSignalType> RowDeletedSignalProxy;
	static const RowDeletedSignalType row_deleted_signal;
	///< Row deleted signal (see signal_row_deleted()). Calls a slot with the signature:
	///< @code
	///< void function(const TreePath& path);
	///< // path: A TreePath pointing to the previous location of the deleted row.
	///< @endcode

	typedef G::Signal<void, TreePath&, TreeIter&, int*> RowsReorderedSignalType;
	typedef G::SignalProxy<TypeInstance, RowsReorderedSignalType> RowsReorderedSignalProxy;
	static const RowsReorderedSignalType rows_reordered_signal;
	///< Rows reordered signal (see signal_rows_reordered()). Calls a slot with the signature:
	///< @code
	///< void function(const TreePath& path, const TreeIter& iter, int *new_order);
	///< // path: A TreePath pointing to the tree node whose children have been reordered.
	///< // iter: A valid TreeIter pointing to the node whose children have been reordered.
	///< // new_order: An array of integers containing the new indices of the children.
	///< @endcode
	
/// @}

public:

	typedef sigc::slot<bool, const TreePath&, const TreeIter&> ForeachSlot;
	///< Signature of the callback slot to be called on each node in the model in a
	///< depth-first fashion.
	///< <B>Example:</B> Method signature for ForeachSlot.
	///< @code
	///< bool method(const TreePath& path, const TreeIter& iter);
	///<
	///< // path: A TreePath pointing to a row.
	///< // iter: A TreeIter pointing to a row.
	///< // return: true to stop walking the tree.
	///< @endcode
	///< If the slot returns true, then the tree ceases to be walked, and foreach() returns.

/// @name Accessors
/// @{

	GtkTreeModel* gtk_tree_model() const;
	///< Get a pointer to the GtkTreeModel structure.

	operator GtkTreeModel* () const;
	///< Conversion operator; safely converts a TreeModel to a GtkTreeModel pointer.

	TreeModelFlagsField get_flags() const;
	///< Returns a set of flags supported by this interface.
	///< @return The Gtk::TreeModelFlags supported by this interface.
	///<
	///< The flags are a bitwise combination of TreeModelFlags. The flags supported
	///< should not change during the lifecycle of the tree_model.

	int get_n_columns() const;
	///< Returns the number of columns supported by the tree model.

	GType get_column_type(int index) const;
	///< Returns the type of the column at <EM>index</EM>.
	///< @param index The column index.
	///< @return The type of the column.

	bool get_iter(TreeIter& iter, const TreePath& path) const;
	///< Sets <EM>iter</EM> to a valid iterator pointing to path.
	///< @param iter The TreeIter.
	///< @param path The TreePath.
	///< @return <EM>true</EM> if <EM>iter</EM> was set.

	bool get_iter(TreeIter& iter, const char *path) const;
	bool get_iter(TreeIter& iter, const String& path) const;
	///< Sets <EM>iter</EM> to a valid iterator pointing to <EM>path</EM>, if it exists,
	///< otherwise, <EM>iter</EM> is left invalid and false is returned.
	///< @param iter A TreeIter. 
	///< @param path A string representation of a TreePath. 
	///< @return <EM>true</EM> if <EM>iter</EM> was set.
	 
	String get_string_from_iter(const TreeIter& iter) const;
	///< Generates a string representation of the iter.
	///< @param iter A TreeIter.
	///< @return A String.
	///<
	///< This string is a ':' separated list of numbers. For example, "4:10:0:3" 
	///< would be an acceptable return value for this string.

	bool get_iter_first(TreeIter& iter) const;
	///< Initializes <EM>iter</EM> with the first iterator in the tree (the one at the path "0").
	///< @param iter The TreeIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> was set; <EM>false</EM> if the tree is empty.
	
	Pointer<TreePath> get_path(const TreeIter& iter) const;
	///< Returns a newly-created TreePath referenced by <EM>iter</EM>.
	///< @param iter The TreeIter. 
	///< @return A smart pointer to a newly-created TreePath.

	void get_value(const TreeIter& iter, int column, G::Value& value) const;
	///< Initializes and sets value to that at <EM>column</EM>.
	///< @param iter The TreeIter.
	///< @param column The column to lookup the value at.
	///< @param value An empty G::Value to set.

	String get_value(const TreeIter& iter, int column) const;
	///< Retrieves the string value at <EM>column</EM>.
	///< @param iter The TreeIter.
	///< @param column The column to lookup the value at.
	///< @return The String value at coulmn, or a null String if no value is set.

	bool get_value(const TreeIter& iter, int column, String& str) const;
	///< Convenience method to make retrieving the string value at <EM>column</EM> easier.
	///< @param iter The TreeIter.
	///< @param column The column to lookup the value at. 
	///< @param str An empty String to set.
	///< @return <EM>true</EM> if a String value is retrieved.
	
	bool get_value(const TreeIter& iter, int column, std::string& str) const;
	///< Convenience method to make retrieving the string value at <EM>column</EM> easier.
	///< @param iter The TreeIter.
	///< @param column The column to lookup the value at. 
	///< @param str An empty String to set.
	///< @return <EM>true</EM> if a std::string value is retrieved.

	bool iter_has_child(const TreeIter& iter) const;
	///< Returns true if iter has children, false otherwise.

/// @}
/// @name Templates
/// @{
	
	template<typename DataType>
	void get_value(const TreeIter& iter, int column, DataType& data) const;
	///< Gets the data set in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row.
	///< @param column The column to lookup the data at.
	///< @param data The return location for the data of type DataType.
	///<
	///< This method is used to get values corresponding to the standard data types used
	///< by G::Value, such as bool, int, double, String and unsigned int. There is a good
	///< example of setting values in the gfc-demo program <demos/gfc-demo/liststore.cc>.

	template<typename DataType>
	void get_enum(const TreeIter& iter, int column, DataType& data) const;
	///< Gets the enum value set in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row.
	///< @param column The column to lookup the data at.
	///< @param data The return location for the enum value of type DataType.
	///<
	///< This method is used to get enumeration values. It is a separate method
	///< because G::Value handles an enumeration internally as an int. The DataType
	///< can be any enumeration. There is a good example of setting values in the
	///< gfc-demo program <demos/gfc-demo/liststore.cc>.

	template<typename DataType>
	void get_object(const TreeIter& iter, int column, DataType& data) const;
	///< Gets the object pointer set in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row.
	///< @param column The column to lookup the data at.
	///< @param data The return location for the object pointer of type DataType.
	///<
	///< The <EM>data</EM> argument is a pointer to an object derived from G::Object,
	///< passed by reference. The object is has its reference count incremented so you
	///< will have to call unref(). There is a good example of getting values in the
	///< gfc-demo program <demos/gfc-demo/liststore.cc>.

	template<typename DataType>
	void get_pointer(const TreeIter& iter, int column, DataType& data) const;
	///< Gets the pointer set in the cell specified by iter and column.
	///< @param iter A valid TreeIter for the row.
	///< @param column The column to lookup the data at.
	///< @param data The return location for the pointer of type DataType.
	///<
	///< The <EM>data</EM> argument can be a pointer to any object. The pointer is managed
	///< internally as a generic (void*) pointer. Unlike get_object() which passes the G::Object
	///< pointer internally as a GObject pointer, get_pointer() passes the pointer as is, without
	///< interpretation. There is a good example of setting values in the gfc-demo program
	///< <demos/gfc-demo/liststore.cc>.

/// @}
/// @name Methods
/// @{

	bool iter_next(TreeIter& iter);
	///< Sets <EM>iter</EM> to point to the node following it at the current level.
	///< @param iter The TreeIter.
	///< @return <EM>true</EM> if iter has been changed to the next node.
	///<
	///< If there is no next iter, false is returned and iter is set to be invalid.

	bool iter_children(TreeIter& iter, const TreeIter *parent = 0);
	///< Sets <EM>iter</EM> to point to the first child of <EM>parent</EM>.
	///< @param iter The TreeIter to be set to the child.
	///< @param parent The parent TreeIter, or null. 
	///< @return <EM>true</EM> if child has been set to the first child.
	///<
	///< If <EM>parent</EM> has no children, false is returned and iter is set
	///< to be invalid. <EM>parent</EM> will remain a valid node after this method
	///< has been called. If parent is null this method returns the first node, 
	///< equivalent to get_iter_first(iter);

	int iter_n_children(const TreeIter *iter);
	///< Returns the number of children that iter has.
	///< @param iter The TreeIter, or null. 
	///< @return The number of children of iter.
	///<	
	///< As a special case, if iter is null, then the number of toplevel nodes is returned.
	 
	bool iter_nth_child(TreeIter& iter, const TreeIter *parent, int n);
	///< Sets <EM>iter</EM> to be the child of parent, using the given index. 
	///< @param iter The TreeIter to set to the nth child. 
	///< @param parent The TreeIter to get the child from, or null. 
	///< @param n The n index of the desired child. 
	///< @return <EM>true</EM> if parent has an nth child. 
	///<	
	///< The first index is 0. If index is too big, or parent has no children, <EM>iter</EM>
	///< is set to an invalid iterator and false is returned. <EM>parent</EM> will remain a valid
	///< node after this method has been called. As a special case, if parent is null, then the 
	///< nth root node is set.
	
	bool iter_parent(TreeIter& iter, const TreeIter& child);
	///< Sets <EM>iter</EM> to be the parent of <EM>child</EM>. 
	///< @param iter The new TreeIter to set to the parent. 
	///< @param child The TreeIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> is set to the parent of <EM>child</EM>. 
	///<	
	///< If child is at the toplevel, and doesn't have a parent, then iter is set to an 
	///< invalid iterator and false is returned. <EM>child</EM> will remain a valid node 
	///< after this method has been called.

	void ref_node(TreeIter *iter);
	///< Lets the tree ref the node.
	///< @param iter The TreeIter.
	///<
	///< This is an optional method for models to implement. Models may ignore 
	///< this call as it exists primarily for performance reasons. This method is
	///< primarily meant as a way for views to let a caching model know when nodes
	///< are being displayed (and hence, whether or not to cache that node). For
	///< example, a file-system based model would not want to keep the entire file
	///< hierarchy in memory, just the sections that are currently being displayed
	///< by every current view. A model should be expected to be able to get an 
	///< iter independent of it's reffed state.

	void unref_node(TreeIter *iter);
	///< Lets the tree unref the node.
	///< @param iter The TreeIter.
	///<	
	///< This is an optional method for models to implement. Models may ignore this
	///< call as it exists primarily for performance reasons. For more information on
	///< what this means, see ref_node(). Please note that nodes that are deleted are
	///< not unreffed.

	void foreach(const ForeachSlot& each);
	///< Calls <EM>each</EM> on each node in model in a depth-first fashion. 
	///< @param each The callback slot to be called on each row. 
	///<	
	///< If <EM>each</EM> returns true, then the tree ceases to be walked, and 
	///< foreach() returns.

	void row_changed(const TreePath& path, const TreeIter& iter);
	///< Emits the "row_changed" signal on the tree model.
	///< @param path A TreePath pointing to the changed row. 
	///< @param iter A valid TreeIter pointing to the changed row.
	 
	void row_inserted(const TreePath& path, const TreeIter& iter);
	///< Emits the "row_inserted" signal on the tree model.
	///< @param path A TreePath pointing to the inserted row. 
	///< @param iter A valid TreeIter pointing to the inserted row.

	void row_has_child_toggled(const TreePath& path, const TreeIter& iter);
	///< Emits the "row_has_child_toggled" signal on the tree model. 
	///< @param path A TreePath pointing to the changed row. 
	///< @param iter A valid TreeIter pointing to the changed row.
	///<	
	///< This should be called by models after the child state of a node changes.
	
	void row_deleted(const TreePath& path);
	///< Emits the "row_deleted" signal on the tree model. 
	///< @param path A TreePath pointing to the previous location of the deleted row.
	///<	
	///< This should be called by models after a row has been removed. The location pointed
	///< to by path should be the location that the row previously was at. It may not be a valid
	///< location anymore.
	
	void rows_reordered(const TreePath& path, const TreeIter& iter, int *new_order);
	///< Emits the "rows_reordered" signal on tree_model. 
	///< @param path A TreePath pointing to the tree node whose children have been reordered. 
	///< @param iter A valid TreeIter pointing to the node whose children have been reordered. 
	///< @param new_order An array of integers containing the new indices of the children, 
	///< that is, the former child n is now at position new_order[n].
	///<	
	///< This should be called by models when their rows have been reordered.
	 
/// @}
/// @name Signal Proxies
/// @{

	const RowChangedSignalProxy signal_row_changed();
	///< Connect to the row_changed_signal; emitted when a row in the model is changed.

	const RowInsertedSignalProxy signal_row_inserted();
	///< Connect to the row_inserted_signal; emitted when a row is inserted into the model.

	const RowHasChildToggledSignalProxy signal_row_has_child_toggled();
	///< Connect to the row_has_child_toggled_signal; emitted after the child state of a node changes.

	const RowDeletedSignalProxy signal_row_deleted();
	///< Connect to the row_deleted_signal; emitted when a row is removed from the model.

	const RowsReorderedSignalProxy signal_rows_reordered();
	///< Connect to the rows_reordered_signal; emitted when the model's rows have been reordered.
	
/// @}
};

/// @class TreeRowReference treemodel.hh xfc/gtk/treemodel.hh
/// @brief A GtkTreeRowReference C++ wrapper class.
///
/// A TreeRowReference can be used to point to a node in a model, so long as it exists.
/// The row reference will monitor all signals emitted by the model and update the node
/// path appropriately.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class TreeRowReference : public G::Boxed
{
public:
/// @name Constructors
/// @{

	TreeRowReference(TreeModel& model, const TreePath& path);
	///< Constructs a row reference based on path.
	///< @param model A TreeModel.
	///< @param path A valid TreePath to monitor.
	///<
	///< This reference will keep pointing to the node pointed to by path, so long as it exists.
	///< It listens to all signals emitted by model, and updates it's path appropriately. The
	///< TreeRowReference is created with a reference count of 1 that the caller owns.

	TreeRowReference(G::Object& proxy, TreeModel& model, const TreePath& path);
	///< Constructs a row reference based on path. You do not need to use this constructor..
	///< @param proxy A proxy G::Object.
	///< @param model A TreeModel.
	///< @param path A valid TreePath to monitor.
	///<
	///< You do not need to use this constructor. The row reference will keep pointing to
	///< the node pointed to by path, so long as it exists. However, unlike references created
	///< with the other constructors, it does not listen to the model for changes. The creator
	///< of the row reference must do this explicitly using  inserted(), deleted() and
	///< reordered(). This must be called once per signal per proxy. This type of row reference
	///< is primarily meant for use when you need to carefully monitor exactly when a row
	///< reference updates itself. It is not generally needed by most applications. The
	///< TreeRowReference is created with a reference count of 1 that the caller owns.

	explicit TreeRowReference(GtkTreeRowReference *reference);
	///< Constructs a row reference from an existing GtkTreeRowReference.
	///< @param reference A pointer to a GtkTreeRowReference.
	///<
	///< The <EM>reference</EM> can be a newly created GtkTreeRowReference or an existing
	///< GtkTreeRowReference. The TreeRowReference object created is a temporary object. It
	///< doesn't take over the ownership of GtkTreeRowReference and GtkTreeRowReference is not
	///< freed by the destructor. The TreeRowReference is created with a reference count of 1
	///< that the caller owns.

	TreeRowReference(GtkTreeRowReference *reference, bool copy);
	///< Constructs a row reference from an existing GtkTreeRowReference.
	///< @param reference A pointer to a GtkTreeRowReference.
	///< @param copy Whether the TreePath object should make a copy of GtkTreePath or not.
	///<
	///< The <EM>reference</EM> can be a newly created GtkTreeRowReference or an existing
	///< GtkTreeRowReference. If <EM>copy</EM> is true TreeRowReference will make a copy of
	///< GtkTreeRowReference. If <EM>copy</EM> is false TreeRowReference wont make a copy but
	///< instead takes over the ownership of GtkTreeRowReference. Either way, the destructor
	///< will free GtkTreeRowReference when the TreeRowReference object is destroyed. This
	///< constructor is used by G::Boxed::wrap() to wrap GtkTreeRowReference objects in a
	///< C++ wrapper. The TreeRowReference is created with a reference count of 1 that the
	///< caller owns.

	TreeRowReference(const TreeRowReference& src);
	///< Copy constructor.
	///< @param src The source tree row reference.
	
	~TreeRowReference();
	///< Destructor.

	TreeRowReference& operator=(const TreeRowReference& src);
	///< Assignment operator.
	///< @param src The source tree row reference.

/// @}
/// @name Accessors
/// @{

	GtkTreeRowReference* gtk_tree_row_reference() const;
	///< Get a pointer to the GtkTreeRowReference structure.

	operator GtkTreeRowReference* () const;
	///< Conversion operator; safely converts a TreeRowReference to a GtkTreeRowReference pointer.

	Pointer<TreePath> get_path() const;
	///< Returns a path that the row reference currently points to, or null
	///< if the path pointed to is no longer valid.
	///< @return A current path, or null. 
	
	bool valid() const;
	///< Returns true if the reference is non-null and refers to a current valid path.
	///< @return <EM>true</EM> if reference points to a valid path. 
	
/// @}
/// @name Methods
/// @{

	static void inserted(const G::Object& proxy, const TreePath& path);
	///< Lets a row reference created by the proxy object constructor know that the
	///< model emitted the "row_inserted" signal.
	///< @param proxy A G::Object. 
	///< @param path The row position that was inserted.
	 
	static void deleted(const G::Object& proxy, const TreePath& path);
	///< Lets a row reference created by the proxy object constructor know that the
	///< model emitted the "row_deleted" signal.
	///< @param proxy A G::Object. 
	///< @param path The path position that was deleted.
	 
	static void reordered(const G::Object& proxy, const TreePath& path, const TreeIter& iter, int *new_order);
	///< Lets a row reference created by the proxy object constructor know that the
	///< model emitted the "rows_reordered" signal.
	///< @param proxy A G::Object. 
	///< @param path The parent path of the reordered signal. 
	///< @param iter The iter pointing to the parent of the reordered row. 
	///< @param new_order The new order of rows.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treemodel.inl>

#endif // XFC_GTK_TREE_MODEL_HH

