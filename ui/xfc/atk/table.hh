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

/// @file xfc/atk/table.hh
/// @brief An AtkTable C++ wrapper interface.
///
/// Provides Table, an interface implemented for UI components which contain tabular or row/column information.

#ifndef XFC_ATK_TABLE_HH
#define XFC_ATK_TABLE_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __ATK_TABLE_H__
#include <atk/atktable.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Atk {

class Object;

/// @class Table table.hh xfc/atk/table.hh
/// @brief An AtkTable C++ wrapper class.
///
/// Table should be implemented by components which present elements ordered via rows and columns.
/// It may also be used to present tree-structured information if the nodes of the trees can be 
/// said to contain multiple "columns". Individual elements of an Table are typically referred 
/// to as "cells", and these cells are exposed by Table as child Atk::Objects of the Table. Both
/// row/column and child-index-based access to these children is provided.
///
/// Children of Table are frequently "lightweight" objects, that is, they may not have backing
/// widgets in the host UI toolkit. They are therefore often transient.
/// 
/// Since tables are often very complex, Table includes provision for offering simplified summary
/// information, as well as row and column headers and captions. Headers and captions are Atk::Objects
/// which may implement other interfaces (Text, Image, etc.) as appropriate. Table summaries may 
/// themselves be (simplified) Tables, etc.

class Table : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Table();
	///< Constructs a new Table object.
	
	virtual ~Table() = 0;
	///< Destructor.
	
/// @}
/// @name Signals Prototypes
/// @{

	typedef G::Signal<void, int, int> RowInsertedSignalType;
	typedef G::SignalProxy<TypeInstance, RowInsertedSignalType> RowInsertedSignalProxy;
	static const RowInsertedSignalType row_inserted_signal;
	///< Row inserted signal (see signal_row_inserted()). Calls a slot with the signature:
	///< @code
	///< void function(int row, int num_inserted);
	///< // row: The index of the first row inserted.
	///< // num_inserted: The number of rows inserted.
	///< @endcode

	typedef G::Signal<void, int, int> ColumnInsertedSignalType;
	typedef G::SignalProxy<TypeInstance, ColumnInsertedSignalType> ColumnInsertedSignalProxy;
	static const ColumnInsertedSignalType column_inserted_signal;
	///< Column inserted signal (see signal_column_inserted()). Calls a slot with the signature:
	///< @code
	///< void function(int column, int num_inserted);
	///< // column: The index of the first column inserted.
	///< // num_inserted: The number of columns inserted.
	///< @endcode

	typedef G::Signal<void, int, int> RowDeletedSignalType;
	typedef G::SignalProxy<TypeInstance, RowDeletedSignalType> RowDeletedSignalProxy;
	static const RowDeletedSignalType row_deleted_signal;
	///< Row deleted signal (see signal_row_deleted()). Calls a slot with the signature:
	///< @code
	///< void function(int row, int num_deleted);
	///< // row: The index of the first row deleted.
	///< // num_deleted: The number of rows deleted.
	///< @endcode

	typedef G::Signal<void, int, int> ColumnDeletedSignalType;
	typedef G::SignalProxy<TypeInstance, ColumnDeletedSignalType> ColumnDeletedSignalProxy;
	static const ColumnDeletedSignalType column_deleted_signal;
	///< Columnn deleted signal (see signal_column_deleted()). Calls a slot with the signature:
	///< @code
	///< void function(int column, int num_deleted);
	///< // column: The index of the first column deleted.
	///< // num_deleted: The number of columns deleted.
	///< @endcode

	typedef G::Signal<void> RowReorderedSignalType;
	typedef G::SignalProxy<TypeInstance, RowReorderedSignalType> RowReorderedSignalProxy;
	static const RowReorderedSignalType row_reordered_signal;
	///< Row reordered signal (see signal_row_reordered()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> ColumnReorderedSignalType;
	typedef G::SignalProxy<TypeInstance, ColumnReorderedSignalType> ColumnReorderedSignalProxy;
	static const ColumnReorderedSignalType column_reordered_signal;
	///< Column reordered signal (see signal_column_reordered()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> ModelChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ModelChangedSignalType> ModelChangedSignalProxy;
	static const ModelChangedSignalType model_changed_signal;
	///< Model changed signal (see signal_model_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
/// @name Accessors
/// @{

	AtkTable* atk_table() const;
	///< Get a pointer to the AtkTable structure.

	operator AtkTable* () const;
	///< Conversion operator; safely converts a Table to an AtkTable pointer.

	Object* ref_at(int row, int column) const;
	///< Get a reference to the table cell at row, column.
	///< @param row An integer representing a row in table.
	///< @param column an integer representing a column in the table.
	///< @return A pointer to Atk::Object representing the referred to accessible.

	int get_index_at(int row, int column) const;
	///< Gets a integer representing the index at the specified row and column. 
	///< @param row An integer representing a row in the table.
	///< @param column An integer representing a column in the table.
	///< @return An integer representing the index at specified position.
	///<
	///< The value -1 is returned if the object at <EM>row, column</EM> is not
	///< a child of the table or the table does not implement this interface.

	int get_column_at_index(int index) const;
	///< Gets an integer representing the column at the specified <EM>index</EM>.
	///< @param index An integer representing an index in the table.
	///< @return An integer representing the column at the specified index, or or -1
	///< if the table does not implement this interface.

	int get_row_at_index(int index) const;
	///< Gets an integer representing the row at the specified <EM>index</EM>.
	///< @param index An integer representing an index in the table.
	///< @return An integer representing the row at the specified index, or or -1
	///< if the table does not implement this interface.

	int get_n_columns() const;
	///< Gets the number of columns in the table.
	///< @return An integer representing the number of columns, or 0 if the table
	///< does not implement this interface.

	int get_n_rows() const;
	///< Gets the number of rows in the table.
	///< @return An integer representing the number of rows, or 0 if the table
	///< does not implement this interface.

	int get_column_extent_at(int row, int column) const;
	///< Gets the number of columns occupied by the accessible object at the
	///< specified row and column in the table.
	///< @param row An integer representing a row in the table.
	///< @param column An integer representing a column in the table.
	///< @return An integer representing the column extent at specified position, or 0
	///< if the table does not implement this interface.

	int get_row_extent_at(int row, int column) const;
	///< Gets the number of rows occupied by the accessible object at the
	///< specified row and column in the table.
	///< @param row An integer representing a row in the table.
	///< @param column An integer representing a column in the table.
	///< @return An integer representing the row extent at specified position, or 0
	///< if the table does not implement this interface.

	Object* get_caption() const;
	///< Gets the caption for the table.
	///< @return A pointer to an Atk::Object representing the table caption, or null
	///< if table does not implement this interface.

	String get_column_description(int column) const;
	///< Gets the description text of the specified column in the table.
	///< @param column An integer representing a column in the table.
	///< @return A string representing the column description, or a null String if
	///< the table does not implement this interface.

	Object* get_column_header(int column) const;
	///< Gets the column header of a specified column in an accessible table.
	///< @param column An integer representing a column in the table.
	///< @return A pointer to an Atk::Object representing the specified column header,
	///< or null if table does not implement this interface.

	String get_row_description(int row) const;
	///< Gets the description text of the specified row in the table.
	///< @param row An integer representing a row in the table.
	///< @return A string representing the row description, or null if the table
	///< does not implement this interface.

	Object* get_row_header(int row) const;
	///< Gets the row header of a specified row in an accessible table.
	///< @param row An integer representing a row in the table.
	///< @return A pointer to an Atk::Object representing the specified row header,
	///< or null if table does not implement this interface.

	Object* get_summary() const;
	///< Gets the summary description of the table.
	///< @return A pointer to an Atk::Object representing a summary description of the table,
	///< or null if table does not implement this interface.

	bool get_selected_columns(std::vector<int>& selected) const;
	///< Gets the selected columns of the table.
	///< @param selected A vector of int that is to hold the selected columns numbers.
	///< @return <EM>true</EM> if the vector is not empty.

	bool get_selected_rows(std::vector<int>& selected) const;
	///< Gets the selected rows of the table.
	///< @param selected A vector of int that is to hold the selected rows numbers.
	///< @return <EM>true</EM> if the vector is not empty.

	bool is_column_selected(int column) const;
	///< Gets whether the specified column is selected.
	///< @param column An integer representing a column in the table.
	///< @return <EM>true</EM> if the column is selected, or <EM>false</EM> if the table
	///< does not implement this interface.	bool is_row_selected(int row);

	bool is_row_selected(int row) const;
	///< Gets whether the specified row is selected.
	///< @param row An integer representing a row in the table.
	///< @return <EM>true</EM> if the row is selected, or <EM>false</EM> if the table
	///< does not implement this interface.
		
	bool is_selected(int row, int column) const;
	///< Gets a bool value indicating whether the accessible object at the specified
	///< <EM>row</EM> and <EM>column</EM> is selected.
	///< @param row An integer representing a row in the table.
	///< @param column An integer representing a column in the table.
	///< @return <EM>true</EM> if the cell is selected, or <EM>false</EM> if the table
	///< does not implement this interface.

/// @}
/// @name Methods
/// @{

	void set_caption(const Object *caption);
	///< Sets the caption for the table.
	///< @param caption An Atk::Object representing the caption to set for the table.

	void set_column_description(int column, const char *description);
	void set_column_description(int column, const String& description);
	///< Sets the description text for the specified <EM>column</EM> of the table.
	///< @param column An integer representing a column in the table.
	///< @param description A string representing the description text to
	///< set for the specified <EM>column</EM> of the table.

	void set_column_header(int column, const Object *header);
	///< Sets the specified column header to header.
	///< @param column An integer representing a column in the table.
	///< @param header An Atk::Object representing the specified column header.

	void set_row_description(int row, const char *description);
	void set_row_description(int row, const String& description);
	///< Sets the description text for the specified <EM>row</EM> of the table.
	///< @param row An integer representing a row in the table.
	///< @param description A string representing the description text to
	///< set for the specified <EM>row</EM> of the table.

	void set_row_header(int row, const Object *header);
	///< Sets the specified row header to header.
	///< @param row An integer representing a row in the table.
	///< @param header An Atk::Object representing the specified row header.

	void set_summary(const Object *accessible);
	///< Sets the summary description of the table.
	///< @param accessible An Atk::Object representing the summary description to set for table.

	bool add_row_selection(int row);
	///< Adds the specified row to the selection.
	///< @param row An integer representing a row in the table.
	///< @return <EM>true</EM> if the row was successfully added to the selection,
	///< or <EM>false</EM> if the table does not implement this interface.

	bool remove_row_selection(int row);
	///< Removes the specified row from the selection.
	///< @param row An integer representing a row in the table.
	///< @return <EM>true</EM> if the row was successfully removed from the selection,
	///< or <EM>false</EM> if the table does not implement this interface.

	bool add_column_selection(int column);
	///< Adds the specified column to the selection.
	///< @param column An integer representing a column in the table.
	///< @return <EM>true</EM> if the column was successfully added to the selection,
	///< or <EM>false</EM> if the table does not implement this interface.

	bool remove_column_selection(int column);
	///< Removes the specified column from the selection.
	///< @param column An integer representing a column in the table.
	///< @return <EM>true</EM> if the column was successfully removed from the selection,
	///< or <EM>false</EM> if the table does not implement this interface.

/// @}
/// @name Signal Proxies
/// @{

	const RowInsertedSignalProxy signal_row_inserted();
	///< Connect to the row_inserted_signal; emitted when one or more rows are inserted into a table.

	const ColumnInsertedSignalProxy signal_column_inserted();
	///< Connect to the column_inserted_signal; emitted when one or more columns are inserted into a table.

	const RowDeletedSignalProxy signal_row_deleted();
	///< Connect to the row_deleted_signal; emitted when one or more rows in a table are deleted.

	const ColumnDeletedSignalProxy signal_column_deleted();
	///< Connect to the column_deleted_signal; emitted when one or more columns in a table are deleted.

	const RowReorderedSignalProxy signal_row_reordered();
	///< Connect to the row_reordered_signal; emitted when the rows in a table are reordered.

	const ColumnReorderedSignalProxy signal_column_reordered();
	///< Connect to the column_reordered_signal; emitted when the columns in a table are reordered.

	const ModelChangedSignalProxy signal_model_changed();
	///< Connect to the model_changed_signal.

/// @}
};

} // namespace Atk

} // namespace Xfc

#include <xfc/atk/inline/table.inl>

#endif // XFC_ATK_TABLE_HH

