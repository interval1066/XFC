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
 
/// @file xfc/gtk/table.hh
/// @brief A GtkTable C++ wrapper interface.
///
/// Provides Table, a widget that allows the programmer to arrange widgets in rows and columns,
/// making it easy to align many widgets next to each other, horizontally and vertically.

#ifndef XFC_GTK_TABLE_HH
#define XFC_GTK_TABLE_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_TABLE_H__
#include <gtk/gtktable.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Table table.hh xfc/gtk/table.hh
/// @brief A GtkTable C++ wrapper class.
///
/// The Table widget allows the programmer to arrange widgets in rows and columns, making it easy
/// to align many widgets next to each other, horizontally and vertically. 
///
/// The size of a table can be changed with resize(). Widgets can be added to a table using
/// attach(). To alter the space next to a specific row, use set_row_spacing(), and for a 
/// column, set_col_spacing(). The gaps between all rows or columns can be changed by calling
/// set_row_spacings() or set_col_spacings() respectively. set_homogeneous() can be used to
/// set whether all cells in the table will resize themselves to the size of the largest 
/// widget in the table.
///
/// <B>See also:</B> the <A HREF="../../howto/html/tables.html">Table Widget</A> HOWTO and example.

class Table : public Container
{
	friend class G::Object;

	Table(const Table&);
	Table& operator=(const Table&);
	
protected:
/// @name Constructors
/// @{

	explicit Table(GtkTable *table, bool owns_reference = false);
	///< Construct a new Table from an existing GtkTable.
	///< @param table A pointer to a GtkTable.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>table</EM> can be a newly created GtkTable or an existing
	///< GtkTable (see G::Object::Object).

/// @}

public:
	typedef GtkTable CObjectType;

/// @name Constructors
/// @{

	Table(unsigned int rows, unsigned int columns, bool homogeneous = false);
	///< Construct new table widget. 
	///< @param rows The number of rows the new table should have.
	///< @param columns The number of columns the new table should have.
	///< @param homogeneous <EM>true</EM> if all cells should be resized to the size of the largest cell.
	///<
	///< An initial size must be given by specifying how many rows and columns
	///< the table should have, although this can be changed later with resize().
	///< The <EM>rows</EM> and <EM>columns</EM> must both be in the range 0 .. 65535.
	
	virtual ~Table();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkTable* gtk_table() const;
	///< Get a pointer to the GtkTable structure.

	operator GtkTable* () const;
	///< Conversion operator; safely converts a Table to a GtkTable pointer.

	unsigned int get_row_spacing(unsigned int row) const;
	///< Gets the amount of space between row <EM>row</EM>, and row <EM>row + 1</EM> (see set_row_spacing()).
	///< @param row A row in the table, 0 indicates the first row.
	///< @return The row spacing.

	unsigned int get_column_spacing(unsigned int column) const;
	///< Gets the amount of space between column <EM>column</EM>, and column <EM>column + 1</EM>
	///< (see set_col_spacing()).
	///< @param column A column in the table, 0 indicates the first column.
	/// @return The column spacing.

	unsigned int get_default_row_spacing() const;
	///< Gets the default row spacing for the table.
	///< @return The default row spacing.
	///<
	///< This is the spacing that will be used for newly added rows (see set_row_spacings()).

	unsigned int get_default_col_spacing() const;
	///< Gets the default column spacing for the table.
	///< @return The default column spacing.
	///<
	///< This is the spacing that will be used for newly added columns (see set_col_spacings()).

	bool get_homogeneous() const;
	///< Returns whether the table cells are all constrained to the same width and height (see set_homogeneous()).
	///< @return <EM>true</EM> if the cells are all constrained to the same size.

/// @}
/// @name Methods
/// @{

	void resize(unsigned int rows, unsigned int columns);
	///< If you need to change the table's size after it has been created,
	///< this method allows you to do so.
	///< @param rows The new number of rows.
	///< @param columns The new number of columns.
	
	void attach
	(
		Widget& child, 
		unsigned int left_attach,
		unsigned int right_attach, 
		unsigned int top_attach, 
		unsigned int bottom_attach,
		AttachOptionsField xoptions = EXPAND | FILL,
		AttachOptionsField yoptions = EXPAND | FILL,
		unsigned int xpadding = 0, 
		unsigned int ypadding = 0
	);
	///< Adds a widget to a table.
	///< @param child The widget to add.
	///< @param left_attach The column number to attach the left side of a child widget to.
	///< @param right_attach The column number to attach the right side of a child widget to.
	///< @param top_attach The row number to attach the top of a child widget to.
	///< @param bottom_attach The row number to attach the bottom of a child widget to.
	///< @param xoptions Used to specify the properties of the child widget when the table is resized.
	///< @param yoptions The same as xoptions, except this field determines behaviour of vertical resizing.
	///< @param xpadding An integer specifying the padding on the left and right of the widget being added.
	///< @param ypadding The amount of padding above and below the child widget.
	///<
	///< The number of 'cells' that a widget will occupy is specified by left_attach,
	///< right_attach, top_attach and bottom_attach. These each represent the leftmost,
	///< rightmost, uppermost and lowest column and row numbers of the table. (Columns
	///< and rows are indexed from zero).

	void set_row_spacing(unsigned int row, unsigned int spacing);
	///< Changes the space between a given table row and its surrounding rows.
	///< @param row The row number whose spacing will be changed.
	///< @param spacing The number of pixels that the spacing should take up.

	void set_col_spacing(unsigned int column, unsigned int spacing);
	///< Alters the amount of space between a given table column and the adjacent columns.
	///< @param column The column whose spacing should be changed.
	///< @param spacing The number of pixels that the spacing should take up.

	void set_row_spacings(unsigned int spacing);
	///< Sets the space between every row in the table equal to spacing.
	///< @param spacing The number of pixels of space to place between every row in the table.

	void set_col_spacings(unsigned int spacing);
	///< Sets the space between every column in the table equal to spacing.
	///< @param spacing The number of pixels of space to place between every column in the table.

	void set_spacings(unsigned int row_spacing, unsigned int col_spacing);
	///< Sets the space between every row in the table equal to row_spacing and every column
	///< in the table equal to col_spacing.
	///< @param row_spacing The number of pixels of space to place between every row in the table.
	///< @param col_spacing The number of pixels of space to place between every column in the table.

	void set_homogeneous(bool homogeneous);
	///< Sets whether all cells in the table are of equal size or not.
	///< @param homogeneous Set <EM>true</EM> to ensure all table cells are the same size.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/table.inl>

#endif // XFC_GTK_TABLE_HH

