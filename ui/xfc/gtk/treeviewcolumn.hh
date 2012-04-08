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
 
/// @file xfc/gtk/treeviewcolumn.hh
/// @brief A GtkTreeViewColumn C++ wrapper interface.
///
/// Provides TreeViewColumn, an object that represents a visible column in a TreeView widget.

#ifndef XFC_GTK_TREE_VIEW_COLUMN_HH
#define XFC_GTK_TREE_VIEW_COLUMN_HH

#ifndef XFC_GTK_OBJECT_HH
#include <xfc/gtk/object.hh>
#endif

#ifndef XFC_GTK_CELL_LAYOUT_HH
#include <xfc/gtk/celllayout.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef __GTK_TREE_VIEW_COLUMN_H__
#include <gtk/gtktreeviewcolumn.h>
#endif

namespace Xfc {

namespace Gdk {
class Rectangle;
}

namespace Gtk {

class CellRenderer;
class TreeIter;
class TreeModel;
class TreeViewColumn;
class Widget;

/// @enum TreeViewColumnSizing
/// TreeViewColumnSizing defines the sizing method a column uses to determine it's width.
/// Please note that TREE_VIEW_COLUMN_AUTOSIZE is inefficient for large views, and can 
/// make columns appear choppy. 

enum TreeViewColumnSizing
{
	TREE_VIEW_COLUMN_GROW_ONLY = GTK_TREE_VIEW_COLUMN_GROW_ONLY,
	///< Columns only get bigger in reaction to changes in the model. 
	
	TREE_VIEW_COLUMN_AUTOSIZE = GTK_TREE_VIEW_COLUMN_AUTOSIZE,
	///< Columns resize to be the optimal size everytime the model changes. 
	
	TREE_VIEW_COLUMN_FIXED = GTK_TREE_VIEW_COLUMN_FIXED
	///< Columns are a fixed numbers of pixels wide. 
};

/// @class TreeViewColumn treeviewcolumn.hh xfc/gtk/treeviewcolumn.hh
/// @brief A GtkTreeViewColumn C++ wrapper class.
///
/// A TreeViewColumn is the object that TreeView uses to organize the vertical columns
/// in the tree view. It needs to know the name of the column to label for the user, 
/// what type of cell renderer to use, and which piece of data to retrieve from the
/// model for a given row. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/treeview.html">TreeView Widget</A> HOWTO and example.

class TreeViewColumn : public Object, public CellLayout
{
	friend class G::Object;

	TreeViewColumn(const TreeViewColumn&);
	TreeViewColumn& operator=(const TreeViewColumn&);

protected:
/// @name Constructors
/// @{

	explicit TreeViewColumn(GtkTreeViewColumn *tree_column, bool owns_reference = false);
	///< Construct a new TreeViewColumn from an existing GtkTreeViewColumn.
	///< @param tree_column A pointer to a GtkTreeViewColumn.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tree_column</EM> can be a newly created GtkTreeViewColumn or an existing
	///< GtkTreeViewColumn (see G::Object::Object).
	
/// @}	
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ClickedSignalType;
	typedef G::SignalProxy<TypeInstance, ClickedSignalType> ClickedSignalProxy;
	static const ClickedSignalType clicked_signal;
	///< Clicked signal (see signal_clicked()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkTreeViewColumn CObjectType;

/// @name Constructors
/// @{

	TreeViewColumn();
	///< Construct a new tree view column.

	TreeViewColumn(const char *title);
	TreeViewColumn(const String& title);
	///< Construct a new tree column and sets the title.
	///< @param title The title to set the header to. 
	
	TreeViewColumn(const char *title, CellRenderer& cell, const char *attribute, int column);
	TreeViewColumn(const String& title, CellRenderer& cell, const String& attribute, int column);
	///< Construct a new tree column with a number of default values (see add_attribute()).
	///< @param title The title to set the header to. 
	///< @param cell The CellRenderer. 
	///< @param attribute An attribute on the renderer. 
	///< @param column The column position on the model to get the attribute from.
	///<	 
	///< This is equivalent constructing an empty column and calling set_title(),
	///< pack_start(), and add_attributes(). 
	///<
	///< <B>Here's a simple example:</B>
	///< @code
	///< enum { TEXT_COLUMN, N_COLUMNS };
	///< ...
	///< Gtk::CellRendererText  *cell = new Gtk::CellRendererText();
	///< Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn("Title", cell, "text", TEXT_COLUMN);
	///< @endcode
	
	TreeViewColumn(const char *title, CellRenderer& cell, const CellColumnAttributes& attributes);
	TreeViewColumn(const String& title, CellRenderer& cell, const CellColumnAttributes& attributes);
	///< Construct a new tree column with a number of default values.
	///< @param title The title to set the header to. 
	///< @param cell The CellRenderer. 
	///< @param attributes The tree column attributes to set.
	///<	 
	///< This is equivalent constructing an empty column and calling set_title(),
	///< pack_start(), and add_attributes(). 
	///<
	///< <B>Here's a simple example:</B>
	///< @code
	///< enum { TEXT_COLUMN, COLOR_COLUMN, N_COLUMNS };
	///< ...
	///< Gtk::CellRendererText  *cell = new Gtk::CellRendererText();
	///<
	///< CellColumnAttributes attributes;
	///< attributes.add("text", TEXT_COLUMN);
	///< attributes.add("foreground", COLOR_COLUMN);
	///< Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn("Title", cell, attributes);
	///< @endcode

	virtual ~TreeViewColumn();
	///< Destructor.

/// @}
/// @name Accessors
/// @{
	
	GtkTreeViewColumn* gtk_tree_view_column() const;
	///< Get a pointer to the GtkTreeViewColumn structure.
	
	operator GtkTreeViewColumn* () const;
	///< Conversion operator; safely converts a TreeViewColumn to a GtkTreeViewColumn pointer.

	int get_spacing() const;
	///< Returns the spacing of the tree column, in pixels.
	
	bool get_visible() const;
	///< Returns true if the tree column is visible.
	///< @return Whether the column is visible or not. 
	///<
	///< If the tree column is visible, then the tree will show the column. 
	
	bool get_resizable() const;
	///< Returns true if the tree column can be resized by the end user.
	
	TreeViewColumnSizing get_sizing() const;
	///< Returns the current sizing method of the tree_column.
	
	int get_width() const;
	///< Returns the current size of the tree column in pixels.
	
	int get_fixed_width() const;
	///< Gets the fixed width of the column. This value may not be the actual width
	///< of the column on the screen, just what is requested.
	
	int get_min_width() const;
	///< Returns the minimum width in pixels of the tree column, or -1 if no minimum width is set.
	
	int get_max_width() const;
	///< Returns the maximum width in pixels of the tree column, or -1 if no maximum width is set.
	
	String get_title() const;
	///< Returns the title of the tree column.
	
	bool get_expand() const;
	///< Determines whether the column expands to take any of the available space.
	///< @return <EM>true</EM> if the column expands.

	bool get_clickable() const;
	///< Returns true if the user can click on the header for the column.
	
	Widget* get_widget() const;
	///< Returns the Widget in the button on the column header.
	///< @return The Widget in the column header, or null.
	///<
	///< If a custom widget has not been set then null is returned.
	 
	float get_alignment() const;
	///< Returns the current x alignment of the tree column. This value can range between 0.0 and 1.0.
	
	bool get_reorderable() const;
	///< Returns true if the tree column can be reordered by the user.
	
	int get_sort_column_id() const;
	///< Gets the logical <EM>sort_column_id</EM> that the model sorts on 
	///< when this column is selected for sorting (see set_sort_column_id()).
	///< @return The current <EM>sort_column_id</EM> for this column, or -1 if this
	///< column can't be used for sorting. 
	
	bool get_sort_indicator() const;
	///< Gets the value set by set_sort_indicator().
	///< @return Whether the sort indicator arrow is displayed.
	 
	SortType get_sort_order() const;
	///< Gets the value set by set_sort_order().
	///< @return The sort order the sort indicator is indicating.
	 
	bool get_cell_renderers(std::vector<CellRenderer*>& cell_list) const;
	///< Gets a list of all the cell renderers in the column, in no particular order.
	///< @param cell_list A reference to a vector of CellRenderer* to hold the list of cell renderers.
	///< @return <EM>true</EM> if cell_list is not empty.

	void cell_get_size(const Gdk::Rectangle *cell_area, int *x_offset, int *y_offset, int *width, int *height) const;
	///< Obtains the width and height needed to render the column.
	///< @param cell_area The area a cell in the column will be allocated, or null.
	///< @param x_offset The location to return X offset of a cell relative to cell_area, or null.
	///< @param y_offset The location to return Y offset of a cell relative to cell_area, or null.
	///< @param width The location to return width needed to render a cell, or null.
	///< @param height The location to return height needed to render a cell, or null.
	///<
	///< This is used primarily by the Gtk::TreeView.

	bool cell_is_visible() const;
	///< Returns true if any of the cells packed into the tree column are visible.
	///< @return <EM>true</EM> if any of the cells packed into the tree_column are currently visible.
	///<
	///< For this to be meaningful, you must first initialize the cells with cell_set_cell_data().

/// @}
/// @name Methods
/// @{
	
	void pack_start(CellRenderer& cell, bool expand = true);
	///< Packs the cell into the beginning of the column. 
	///< @param cell The CellRenderer. 
	///< @param expand <EM>true</EM> if cell is to be given extra space allocated to box.
	///<	
	///< If expand is false, then the cell is allocated no more space than it needs. 
	///< Any unused space is divided evenly between cells for which expand is true.
	
	void pack_end(CellRenderer& cell, bool expand = true);
	///< Adds the cell to end of the column. 
	///< @param cell The CellRenderer. 
	///< @param expand <EM>true</EM> if cell is to be given extra space allocated to box.
	///<	
	///< If expand is false, then the cell is allocated no more space than it needs. 
	///< Any unused space is divided evenly between cells for which expand is true.
	
	void clear();
	///< Unsets all the mappings on all renderers on the tree column.
 
	void add_attribute(CellRenderer& cell, const char *attribute, int column);
	void add_attribute(CellRenderer& cell, const String& attribute, int column);
	///< Adds an attribute mapping to the list in the tree column. 
	///< @param cell The CellRenderer to set attributes on. 
	///< @param attribute An attribute on the renderer. 
	///< @param column The column position on the model to get the attribute from.
	///< 	
	///< The <EM>column</EM> is the column of the model to get a value from,
	///< and the <EM>attribute</EM> is the parameter on <EM>cell</EM> to be set
	///< from the value. So for example if column 2 of the model contains strings,
	///< you could have the "text" attribute of a CellRendererText get its values
	///< from column 2.
	 
	void set_attributes(CellRenderer& cell, const CellColumnAttributes& attributes);
	///< Sets the attributes in the list as the attributes of the tree column. 
	///< @param cell The CellRenderer. 
	///< @param attributes The tree column attributes to set.
	
	void set_cell_data_func(CellRenderer& cell, const CellDataSlot& slot);
	///< Sets the CellDataSlot to use for the column. 
	///< @param cell A CellRenderer. 
	///< @param slot The CellDataSlot to use. 
	///<
	///< The CellDataSlot is used instead of the standard attributes mapping for
	///< setting the column value, and should set the value of the tree column's cell
	///< renderer as appropriate. <EM>slot</EM> may be null to remove an older one.
	
	void remove_cell_data_func(CellRenderer& cell);
	///< Removes the current CellDataSlot used for the column. 
	///< @param cell A CellRenderer. 
	
	void clear_attributes(CellRenderer& cell);
	///< Clears all existing attributes previously set with set_attributes().
	///< @param cell A CellRenderer to clear the attribute mapping on.
	 
	void set_spacing(int spacing);
	///< Sets the spacing field of the tree column, which is the number of pixels
	///< to place between cell renderers packed into it.
	///< @param spacing The distance between cell renderers in pixels.

	void set_visible(bool visible);
	///< Sets the visibility of the tree column.
	///< @param visible <EM>true</EM> if the tree column is visible.
	
	void set_resizable(bool resizable);
	///< If resizable is true, then the user can explicitly resize the column 
	///< by grabbing the outer edge of the column button.
	///< @param resizable <EM>true</EM> if the column can be resized.
	///<	
	///< If resizable is true and sizing mode of the column is TREE_VIEW_COLUMN_AUTOSIZE,
	///< then the sizing mode is changed to TREE_VIEW_COLUMN_GROW_ONLY.
	 
	void set_sizing(TreeViewColumnSizing type);
	///< Sets the growth behavior of the tree column to type.
	///< @param type The TreeViewColumnSizing.
	 
	void set_fixed_width(int fixed_width);
	///< Sets the size of the column in pixels. 
	///< @param fixed_width The size to set tree_column to. Must be greater than 0.
	///<	
	///< This is only meaningful if the sizing type is TREE_VIEW_COLUMN_FIXED. The size
	///< of the column is clamped to the min/max width for the column. Please note that the
	///< min/max width of the column doesn't actually affect the "fixed_width" property of
	///< the widget, just the actual size when displayed.
	 
	void set_min_width(int min_width);
	///< Sets the minimum width of the tree column.
	///< @param min_width The minimum width of the column in pixels, or -1. 
	///<	
	///< If min_width is -1, then the minimum width is unset.
 
	void set_max_width(int max_width);
	///< Sets the maximum width of the tree column. 
	///< @param max_width The maximum width of the column in pixels, or -1.
	///< 	
	///< If max_width is -1, then the maximum width is unset. Note, the column
	///< can actually be wider than <EM>max_width</EM> if it's the last column in
	///< a view. In this case, the column expands to fill any extra space.
	 
	void set_title(const char *title);
	void set_title(const String& title);
	///< Sets the title of the tree column.
	///< @param title The title of the tree column.
	///<	
	///< If a custom widget has been set, then this value is ignored.
	 
	void set_expand(bool expand);
	///< Sets the column to take available extra space.
	///< @param expand Set <EM>true</EM> if the column should expand.
	///<
	///< This space is shared equally amongst all columns that have <EM>expand</EM> set to true.
	///< If no column has this option set, then the last column gets all extra space. By default,
	///< every column is created with this false.

	void clicked();
	///< Emits the "clicked" signal on the column. This method will only work if
	///< the tree column is clickable.

	void set_clickable(bool active);
	///< Sets the header to be active if active is true.
	///< @param active <EM>true</EM> if the header is active.
	///<
	///< When the header is active, then it can take keyboard focus, and can be clicked.

	void set_widget(Widget *widget);
	///< Sets the widget in the header to be widget. 
	///< @param widget A child Widget, or null.
	///<	
	///< If widget is null, then the header button is set with a Label
	///< set to the title of tree_column.

	void set_alignment(float xalign);
	///< Sets the alignment of the title or custom widget inside the column header.
	///< @param xalign The alignment, which is between [0.0 and 1.0] inclusive. 
	///<	 
	///< The alignment determines its location inside the button - 0.0 for left,
	///< 0.5 for center, 1.0 for right.
	
	void set_reorderable(bool reorderable);
  	///< If reorderable is true, then the column can be reordered by the end user dragging the header.
	///< @param reorderable <EM>true</EM> if the column can be reordered. 
		
	void set_sort_column_id(int sort_column_id);
	///< Sets the logical <EM>sort_column_id</EM> that this column sorts on
	///< when this column is selected for sorting. 
	///< @param sort_column_id The sort_column_id of the model to sort on. 
	///<	
	///< Setting the logical <EM>sort_column_id</EM> makes the column header clickable.
	///< You probably only want to use set_sort_column_id(). The other sorting methods 
	///< exist to allow for custom sorting.

	void set_sort_indicator(bool setting);
	///< Call this method with a setting of true to display an arrow in the header button
	///< indicating the column is sorted.
	///< @param setting <EM>true</EM> to display an indicator that the column is sorted.
	///<	
	///< Call set_sort_order() to change the direction of the arrow.
	 
	void set_sort_order(SortType order);
	///< Changes the appearance of the sort indicator. 
	///< @param order The sort order that the sort indicator should indicate. 
	///<
	///< This does not actually sort the model. Use set_sort_column_id() if you want
	///< automatic sorting support. This method is primarily for custom sorting behavior,
	///< and should be used in conjunction with Gtk::TreeSortable::set_sort_column() to
	///< do that. For custom models, the mechanism will vary.
	///<
	///< The sort indicator changes direction to indicate normal sort or reverse sort.
	///< Note that you must have the sort indicator enabled to see anything when calling
	///< this method; see set_sort_indicator().

	void cell_set_cell_data(const TreeModel& model, const TreeIter& iter, bool is_expander, bool is_expanded);
	///< Sets the cell renderer based on the tree <EM>model</EM> and <EM>iter</EM>.
	///< @param model The TreeModel to to get the cell renderers attributes from.
	///< @param iter The TreeIter to to get the cell renderer's attributes from.
	///< @param is_expander Set <EM>true</EM> if the row has children.
	///< @param is_expanded Set <EM>true</EM> if the row has visible children.
	///<
	///< That is, for every attribute mapping in the tree column, it will get a value
	///< from the set column on the iter, and use that value to set the attribute on the
	///< cell renderer. This is used primarily by the Gtk::TreeView.

	void focus_cell(CellRenderer& cell);
	///< Sets the current keyboard focus to be at cell, if the column contains 2
	///< or more editable and activatable cells.
	///< @param cell A CellRenderer.

/// @}
/// @name Signal Proxies
/// @{

	const ClickedSignalProxy signal_clicked();
	///< Connect to the clicked_signal; emitted when the user clicks on the header for the column.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treeviewcolumn.inl>

#endif // XFC_GTK_TREE_VIEW_COLUMN_HH

