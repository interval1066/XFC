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
 
/// @file xfc/gtk/treeview.hh
/// @brief A GtkTreeView C++ wrapper interface.
///
/// Provides TreeView, a widget that displays any object that implements the TreeModel interface.  

#ifndef XFC_GTK_TREE_VIEW_HH
#define XFC_GTK_TREE_VIEW_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef XFC_GTK_CELL_RENDERER_HH
#include <xfc/gtk/cellrenderer.hh>
#endif

#ifndef XFC_GTK_TREE_SELECTION_HH
#include <xfc/gtk/treeselection.hh>
#endif

#ifndef XFC_GTK_TREE_VIEW_COLUMN_HH
#include <xfc/gtk/treeviewcolumn.hh>
#endif

#ifndef __GTK_TREE_VIEW_H__
#include <gtk/gtktreeview.h>
#endif

namespace Xfc {

namespace Gtk {

class CellRenderer;
class DragContext;
class TreeIter;
class TreeModel;
class TreePath;

/// @enum TreeViewDropPosition
/// TreeViewDropPosition is used to determine where a dropped row goes. 

enum TreeViewDropPosition
{
	TREE_VIEW_DROP_BEFORE = GTK_TREE_VIEW_DROP_BEFORE, 
	///< Drop before this row.
	
	TREE_VIEW_DROP_AFTER = GTK_TREE_VIEW_DROP_AFTER, 
	///< Drop after this row.
	
	TREE_VIEW_DROP_INTO_OR_BEFORE = GTK_TREE_VIEW_DROP_INTO_OR_BEFORE,
	///< Drop as a child of this row (with fallback to before if into is not possible).
	
	TREE_VIEW_DROP_INTO_OR_AFTER = GTK_TREE_VIEW_DROP_INTO_OR_AFTER
	///< Drop as a child of this row (with fallback to after if into is not possible).
};

/// @class TreeView treeview.hh xfc/gtk/treeview.hh
/// @brief A GtkTreeView C++ wrapper class.
///
/// TreeView is a widget that can display any object that implements the TreeModel interface.
///
/// To use TreeView in your application you only need to include two header files <xfc/gtk/treeview.hh>
/// and either <xfc/gtk/liststore.hh> or <xfc/gtk/treestore.hh>. These header files include all the other header
/// files that TreeView needs.
///
/// <B>See also:</B> the <A HREF="../../howto/html/treeview.html">TreeView Widget</A> HOWTO and example.

class TreeView : public Container
{
	friend class G::Object;

	TreeView(const TreeView&);
	TreeView& operator=(const TreeView&);

protected:
/// @name Constructors
/// @{

	explicit TreeView(GtkTreeView *tree_view, bool owns_reference = false);
	///< Construct a new TreeView from an existing GtkTreeView.
	///< @param tree_view A pointer to a GtkTreeView.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tree_view</EM> can be a newly created GtkTreeView or an existing
	///< GtkTreeView (see G::Object::Object).
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Adjustment*, Adjustment*> SetScrollAdjustmentsSignalType;
	typedef G::SignalProxy<TypeInstance, SetScrollAdjustmentsSignalType> SetScrollAdjustmentsSignalProxy;
	static const SetScrollAdjustmentsSignalType set_scroll_adjustments_signal;
	///< Set scroll adjustments signal (see signal_set_scroll_adjustments()). Calls a slot with the signature:
	///< @code
	///< void function(Adjustment *hadjustment, Adjustment *vadjustment);
	///< // hadjustment: The horizontal adjustment.
	///< // vadjustment: The vertical adjustment.
	///< @endcode

	typedef G::Signal<void, const TreePath&, TreeViewColumn&> RowActivatedSignalType;
	typedef G::SignalProxy<TypeInstance, RowActivatedSignalType> RowActivatedSignalProxy;
	static const RowActivatedSignalType row_activated_signal;
	///< Row activated signal (see signal_row_activated()). Calls a slot with the signature:
	///< @code
	///< void function(const TreePath& path, TreeViewColumn& column);
	///< // path: The TreePath being activated.
	///< // column: The TreeViewColumn being activated.
	///< @endcode

	typedef G::Signal<bool, const TreeIter&, const TreePath&> TestExpandRowSignalType;
	typedef G::SignalProxy<TypeInstance, TestExpandRowSignalType> TestExpandRowSignalProxy;
	static const TestExpandRowSignalType test_expand_row_signal;
	///< Test expand row signal (see signal_test_expand_row()). Calls a slot with the signature:
	///< @code
	///< bool function(const TreeIter& iter, const TreePath& path);
	///< // iter: A valid iterator pointing to path.
	///< // path: The path to the row being checked.
	///< // return: true if the row has chil rows and can be expanded.
	///< @endcode

	typedef G::Signal<bool, const TreeIter&, const TreePath&> TestCollapseRowSignalType;
	typedef G::SignalProxy<TypeInstance, TestCollapseRowSignalType> TestCollapseRowSignalProxy;
	static const TestCollapseRowSignalType test_collapse_row_signal;
	///< Test collapse row signal (see signal_test_collapse_row()). Calls a slot with the signature:
	///< @code
	///< bool function(const TreeIter& iter, const TreePath& path);
	///< // iter: A valid iterator pointing to path.
	///< // path: The path to the row being checked.
	///< // return: true if the row has child rows that are visible and can be collapsed.
	///< @endcode

	typedef G::Signal<void, const TreeIter&, const TreePath&> RowExpandedSignalType;
	typedef G::SignalProxy<TypeInstance, RowExpandedSignalType> RowExpandedSignalProxy;
	static const RowExpandedSignalType row_expanded_signal;
	///< Row expanded signal (see signal_row_expanded()). Calls a slot with the signature:
	///< @code
	///< void function(const TreeIter& iter, const TreePath& path);
	///< // iter: A valid iterator pointing to path.
	///< // path: The path to the row being expanded.
	///< @endcode

	typedef G::Signal<void, const TreeIter&, const TreePath&> RowCollapsedSignalType;
	typedef G::SignalProxy<TypeInstance, RowCollapsedSignalType> RowCollapsedSignalProxy;
	static const RowCollapsedSignalType row_collapsed_signal;
	///< Row collapsed signal (see signal_row_collapsed()). Calls a slot with the signature:
	///< @code
	///< void function(const TreeIter& iter, const TreePath& path);
	///< // iter: A valid iterator pointing to path.
	///< // path: The path to the row being collapsed.
	///< @endcode

	typedef G::Signal<void> ColumnsChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ColumnsChangedSignalType> ColumnsChangedSignalProxy;
	static const ColumnsChangedSignalType columns_changed_signal;
	///< Columns changed signal (see signal_columns_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> CursorChangedSignalType;
	typedef G::SignalProxy<TypeInstance, CursorChangedSignalType> CursorChangedSignalProxy;
	static const CursorChangedSignalType cursor_changed_signal;
	///< Cursor changed signal (see signal_cursor_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkTreeView CObjectType;
	
	typedef CellLayout::CellDataSlot CellDataSlot;
	///< Signature of the callback slot to be called to set the properties of a cell
	///< instead of just using the straight mapping between the cell and the model
	///< (see Gtk::TreeViewColumn::CellDataSlot).

	typedef sigc::slot<bool, TreeView&, TreeViewColumn&, TreeViewColumn*, TreeViewColumn*> ColumnDropSlot;
	///< Signature of the callback slot for determining whether a column can be dropped in a
	///< particular spot (as determined by prev_column and next_column).
	///< <B>Example:</B> Method signature for ColumnDropSlot.
	///< @code
	///< bool method(TreeView& tree_view, TreeViewColumn& column, TreeViewColumn *prev_column, TreeViewColumn *next_column);
	///<
	///< // tree_view: A TreeView.
	///< // column: The TreeViewColumn being dragged.
	///< // prev_column: A TreeViewColumn on one side of column.
	///< // next_column: A TreeViewColumn on the other side of column.
	///< // return: true if column can be dropped in this spot.
	///< @endcode
	///< In left to right locales, prev_column is on the left of the potential drop spot,
	///< and next_column is on the right. In right to left mode, this is reversed. This
	///< slot should return true if the spot is a valid drop spot. Please note that 
	///< returning true does not actually indicate that the column drop was made, but is
	///< meant only to indicate a possible drop spot to the user.

	typedef sigc::slot<void, TreeView&, const TreePath&> MappingSlot;
	///< Signature of the callback slot to be called on each expanded row.
	///< <B>Example:</B> Method signature for MappingSlot.
	///< @code
	///< void method(TreeView& tree_view, const TreePath& path);
	///<
	///< // tree_view: The TreeView.
	///< // path: The path being expanded.
	///< @endcode
	
	typedef sigc::slot<bool, const TreeModel&, int, const String&, const TreeIter&> SearchEqualSlot;
	///< Signature of the callback slot to be called during an interactvie search.
	///< <B>Example:</B> Method signature for SearchEqualSlot.
	///< @code
	///< bool method(const TreeModel& model, int column, const String& key, const TreeIter& iter);
	///<
	///< // model: The TreeModel.
	///< // column: The coloumn identifier.
	///< // key: The string being search for.
	///< // iter: A valid TreeIter for the row being searched.
	///< // return: <EM>false</EM> to stop the search, <EM>true</EM> to continue.
	///< @endcode

	typedef sigc::slot<bool, const TreeModel&, const TreeIter&> RowSeparatorSlot; 
	///< Signature of the callback slot called to determine whether the row
	///< pointed to by iter should be rendered as a separator. 
	///<
	///< <B>Example:</B> Method signature for RowSeparatorSlot.
	///< @code
	///< void method(const TreeModel& model, const TreeIter& iter);
	///< // model: The TreeModel.
	///< // iter: A TreeIter pointing to a row in the model. 
	///< // return: <EM>true</EM> if the row is a separator.	
	///< @endcode
	///<
	///< A common way to implement this is to have a boolean column in the model, 
	///< whose values the RowSeparatorSlot returns. 

/// @name Constructors
/// @{

	TreeView();
	///< Construct a new tree view.

	explicit TreeView(TreeModel& model);
	///< Construct a new tree view with the model initialized to <EM>model</EM>.
	///< @param model The model.

	virtual ~TreeView();
	///< Destructor.
	
/// @}	
/// @name Accessors
/// @{

	GtkTreeView* gtk_tree_view() const;
	///< Get a pointer to the GtkTreeView structure.
	
	operator GtkTreeView* () const;
	///< Conversion operator; safely converts a TreeView to a GtkTreeView pointer.
	
	TreeModel* get_model() const;
	///< Returns the model the tree view is based on. 
	///< @return The model, or null if the model is currently unset.

	TreeSelection* get_selection() const;
	///< Returns the TreeSelection associated with the tree view.
 
	Adjustment* get_hadjustment() const;
	///< Gets the Adjustment currently being used for the horizontal aspect.
	///< @return An Adjustment object, or null if none is currently being used.
	 
	Adjustment* get_vadjustment() const;
	///< Gets the Adjustment currently being used for the vertical aspect.
	///< @return An Adjustment object, or null if none is currently being used.

	bool get_headers_visible() const;
	///< Returns <EM>true</EM> if the headers on the tree view are visible.
	///< @return Whether the headers are visible or not.
	 
	TreeViewColumn* get_column(int position) const;
	///< Gets the TreeViewColumn at the given position in the tree view.
	///< @param position The position of the column, counting from 0. 
	///< @return The TreeViewColumn, or null if the position is outside the range of columns. 
	
	bool get_columns(std::vector<TreeViewColumn*>& columns) const;
	///< Returns a list of all the columns currently in tree_view. 
	///< @param columns A reference to a vector of TreeViewcolumn* to hold the list of columns.
	///< @return <EM>true</EM> if <EM>columns</EM> is not empty.	
	
	TreeViewColumn* get_expander_column() const;
	///< Returns the column that is the current expander column, that is, the column
	///< that has the expander arrow drawn next to it.
	///< @return The expander column.
	 
	bool row_expanded(const TreePath& path) const;
	///< Returns true if the node pointed to by <EM>path</EM> is expanded in the tree view.
	///< @param path A TreePath to test expansion state. 
	///< @return <EM>true</EM> if <EM>path</EM> is expanded.
	 
	bool get_reorderable() const;
	///< Retrieves whether the user can reorder the tree via drag-and-drop (see set_reorderable()).
	///< @return <EM>true</EM> if the tree can be reordered.
	 	
	void get_cursor(Pointer<TreePath> *path, TreeViewColumn **focus_column) const;
	///< Fills in <EM>path</EM> and <EM>focus_column</EM> with the current path and focus column.
	///< @param path A smart pointer to be filled with the current cursor path, or null. 
	///< @param focus_column A pointer to be filled with the current focus column, or null.
	///<	 
	///< If the cursor isn't currently set, then '*path' will be null. If no column currently
	///< has the focus, then '*focus_column' will be null.
	 
	Gdk::Window* get_bin_window() const;
	///< Returns the window that tree view renders to. 
	///< @return A Gdk::Window, or null when tree_view hasn't been realized yet.
	///<	
	///< This is used primarily to compare to event->window to confirm that the event on
	///< the tree view is on the right window.
	 	
	bool get_path_at_pos(int x, int y, Pointer<TreePath> *path, TreeViewColumn **column, int *cell_x, int *cell_y) const;
	///< Finds the path at the point (x, y), relative to widget coordinates. 
	///< @param x The x position to be identified. 
	///< @param y The y position to be identified. 
	///< @param path A smart pointer to a TreePath pointer to be filled in, or null. 
	///< @param column A pointer to a TreeViewColumn pointer to be filled in, or null. 
	///< @param cell_x A pointer where the X coordinate relative to the cell can be placed, or null. 
	///< @param cell_y A pointer where the Y coordinate relative to the cell can be placed, or null. 
	///< @return <EM>true</EM> if a row exists at that coordinate.
	///<	
	///< <EM>x</EM> and <EM>y</EM> are relative to an event's coordinates and must come from
	///< an event on the tree view only where event->window == get_bin_window(). It is primarily
	///< for things like popup menus. If <EM>path</EM> is non-null, then it will be filled with
	///< the TreePath at that point. If <EM>column</EM> is non-null, then it will be filled with
	///< the column at that point. <EM>cell_x</EM> and <EM>cell_y</EM> return the coordinates
	///< relative to the cell background (i.e. the background_area passed to 
	///< Gtk::CellRenderer::render()). This method is only meaningful if the tree view is realized.

	void get_cell_area(const TreePath *path, const TreeViewColumn *column, Gdk::Rectangle& rectangle) const;
	///< Fills the bounding rectangle in tree window coordinates for the cell at the row
	///< specified by <EM>path</EM> and the column specified by <EM>column</EM>. 
	///< @param path A TreePath for the row, or null to get only horizontal coordinates. 
	///< @param column A TreeViewColumn for the column, or null to get only vertical coordinates. 
	///< @param rectangle The rectangle to fill with the cell area. 
	///<	
	///< If <EM>path</EM> is null, or points to a path not currently displayed, the y and height
	///< fields of the rectangle will be filled with 0. If <EM>column</EM> is null, the x and width
	///< fields will be filled with 0. The sum of all cell rects does not cover the entire tree;
	///< there are extra pixels in between rows, for example. The returned rectangle is equivalent
	///< to the cell_area passed to Gtk::CellRenderer::render(). This method is only valid if the
	///< tree view is realized.

	Gdk::Rectangle get_cell_area(const TreePath *path, const TreeViewColumn *column) const;
	///< Returns a rectangle filled with the bounding rectangle in tree window coordinates for
	///< the cell at the row specified by <EM>path</EM> and the column specified by <EM>column</EM>. 
	///< @param path A TreePath for the row, or null to get only horizontal coordinates. 
	///< @param column A TreeViewColumn for the column, or null to get only vertical coordinates.
	///< @return A rectangle filled with the cell area. 
	///<	
	///< If <EM>path</EM> is null, or points to a path not currently displayed, the y and height
	///< fields of the rectangle will be filled with 0. If <EM>column</EM> is null, the x and width
	///< fields will be filled with 0. The sum of all cell rects does not cover the entire tree;
	///< there are extra pixels in between rows, for example. The returned rectangle is equivalent
	///< to the cell_area passed to Gtk::CellRenderer::render(). This method is only valid if the
	///< tree view is realized.

	void get_background_area(const TreePath *path, const TreeViewColumn *column, Gdk::Rectangle& rectangle) const;
	///< Fills the bounding rectangle in tree window coordinates for the cell at the row
	///< specified by <EM>path</EM> and the column specified by <EM>column</EM>. 
	///< @param path A TreePath for the row, or null to get only horizontal coordinates.
	///< @param column A TreeViewColumn for the column, or null to get only vertical coordinates.
	///< @param rectangle The rectangle to fill with cell background area.
	///<	
	///< If <EM>path</EM> is null, or points to a node not found in the tree, the y and height
	///< fields of the rectangle will be filled with 0. If <EM>column</EM> is null, the x and width
	///< fields will be filled with 0. The returned rectangle is equivalent to the background_area
	///< passed to Gtk::CellRenderer::render(). These background areas tile to cover the entire tree
	///< window (except for the area used for header buttons). Contrast with the cell_area, returned
	///< by get_cell_area(), which returns only the cell itself, excluding surrounding borders and
	///< the tree expander area.
	 
	Gdk::Rectangle get_background_area(const TreePath *path, const TreeViewColumn *column) const;
	///< Returns a rectangle filled with the bounding rectangle in tree window coordinates for
	///< the cell at the row specified by <EM>path</EM> and the column specified by <EM>column</EM>. 
	///< @param path A TreePath for the row, or null to get only horizontal coordinates. 
	///< @param column A TreeViewColumn for the column, or null to get only vertical coordinates.
	///< @return A rectangle filled with cell background area.
	///<	
	///< If <EM>path</EM> is null, or points to a node not found in the tree, the y and height
	///< fields of the rectangle will be filled with 0. If <EM>column</EM> is null, the x and width
	///< fields will be filled with 0. The returned rectangle is equivalent to the background_area
	///< passed to Gtk::CellRenderer::render(). These background areas tile to cover the entire tree
	///< window (except for the area used for header buttons). Contrast with the cell_area, returned
	///< by get_cell_area(), which returns only the cell itself, excluding surrounding borders and
	///< the tree expander area.

	void get_visible_rect(Gdk::Rectangle& visible_rect) const;
	///< Fills <EM>visible_rect</EM> with the currently visible region of the view, 
	///< in tree coordinates. 
	///< @param visible_rect The rectangle to fill.
	///<	
	///< Convert to widget coordinates with tree_to_widget_coords(). Tree coordinates start at
	///< (0,0) for row 0 of the tree, and cover the entire scrollable area of the tree.
	 
	Gdk::Rectangle get_visible_rect() const;
	///< Returns a rectangle filled with the currently visible region of the view, in tree coordinates. 
	///< @return The rectangle to fill with the visible region.
	///<	
	///< Convert to widget coordinates with tree_to_widget_coords(). Tree coordinates start at
	///< (0,0) for row 0 of the tree, and cover the entire scrollable area of the tree.

	bool get_rules_hint() const;
	///< Gets the setting set by set_rules_hint().
	///< @return <EM>true</EM> if rules are useful for the user of this tree.
	
	void get_drag_dest_row(Pointer<TreePath> *path, TreeViewDropPosition *pos) const;
	///< Gets the path and/or drop position type of a row.
	///< @param path A smart pointer to a TreePath to be filled in, or null. 
	///< @param pos The return location for the drop position type, or null.	
	
	bool get_dest_row_at_pos(int drag_x, int drag_y, Pointer<TreePath> *path, TreeViewDropPosition *pos) const;
	///< Finds the path and drop position type for the coordinates (drag_x, drag_y).
	///< @param drag_x The X coordinate.
	///< @param drag_y The Y coordinate.	
	///< @param path A smart pointer to a TreePath to be filled in, or null. 
	///< @param pos The return location for the drop position type, or null.	
	///< @return <EM>true</EM> if a row exists at the coordinates.
	///<
	///< This method is provided to allow a custom drag-and-drop implementation.
	///< See get_path_at_pos().
	
	bool get_enable_search() const;
	///< Returns whether or not the tree allows interactive searching.
	///< @return Whether or not to let the user search interactively.
	 
	int get_search_column() const;
	///< Gets the column searched on by the interactive search code.
	///< @return The column the interactive search code searches in.
	 
	bool get_fixed_height_mode() const;
	///< Determines whether fixed height mode is turned on for the tree view.
	///< @return <EM>true</EM> if the tree view is in fixed height mode.
	
	bool get_hover_selection() const;
	///< Determines whether hover selection mode is turned on for the tree view.
	///< @return <EM>true</EM> if the tree view is in hover selection mode. 
	
	bool get_hover_expand() const;
	///< Determines whether hover expansion mode is turned on for the tree view.
	///< @return <EM>true</EM> if the tree view is in hover expansion mode. 

/// @}	
/// @name Methods
/// @{
	
	void set_model(TreeModel *model);
	///< Sets the model for the tree view. 
	///< @param model The model.
	///< 	
	///< If the tree view already has a model set, it will remove it before setting
	///< the new model. If <EM>model</EM> is null, then it will unset the old model.
	 
	void set_hadjustment(Adjustment *adjustment);
	///< Sets the Adjustment for the current horizontal aspect.
	///< @param adjustment The Adjustment to set, or null.
	 
	void set_vadjustment(Adjustment *adjustment);
	///< Sets the Adjustment for the current vertical aspect.
	///< @param adjustment The Adjustment to set, or null.

	void set_headers_visible(bool headers_visible);
	///< Sets the visibility state of the headers.
	///< @param headers_visible <EM>true</EM> if the headers are visible.
	
	void columns_autosize();
	///< Resizes all columns to their optimal width. Only works after the tree view has been realized.
	
	void set_headers_clickable(bool setting);
	///< Allow the column title buttons to be clicked.
	///< @param setting <EM>true</EM> if the columns are clickable. 
	
	int append_column(TreeViewColumn& column);
	///< Appends column to the list of columns.
	///< @param column  The TreeViewColumn to add. 
	///< @return The number of columns in the tree view after appending.
	
	int append_column(const char *title, CellRenderer& cell, const CellColumnAttributes& attributes);
	int append_column(const String& title, CellRenderer& cell, const CellColumnAttributes& attributes);
	///< Creates a new TreeViewColumn and appends it to the end of the list of columns.
	///< @param title The title to set the header to. 
	///< @param cell The CellRenderer.
	///< @param attributes The tree column attributes.
	///< @return The number of columns in the tree view after insertion.
	///<	 
	///< The column is initialized with the attributes given.
	
	int append_column(const char *title, CellRenderer& cell, const CellDataSlot& data);
	int append_column(const String& title, CellRenderer& cell, const CellDataSlot& data);
	///< Convenience method that appends a new column to the tree view with the given cell renderer
	///< and a TreeViewColumn::CellDataSlot to set cell renderer attributes.
	///< @param title The column title.
	///< @param cell The cell renderer for <EM>column</EM>.
	///< @param data The callback slot to set attributes of cell renderer.
	///< @return The number of columns in the tree view post-insert
	///<	
	///< See also Gtk::TreeViewColumn::set_cell_data_func(), Gtk::TreeViewColumn::pack_start().

	int insert_column(TreeViewColumn& column, int position);
	///< This inserts the column into the tree view at <EM>position</EM>. 
	///< @param column The TreeViewColumn to be inserted. 
	///< @param position The position to insert column in. 
	///< @return The number of columns in the tree view after insertion.
	///<	
	///< If position is -1, then the column is appended to the end.
	 
	int insert_column(int position, const char *title, CellRenderer& cell, const CellColumnAttributes& attributes);
	int insert_column(int position, const String& title, CellRenderer& cell, const CellColumnAttributes& attributes);
	///< Creates a new TreeViewColumn and inserts it into the tree view at position.
	///< @param position The position to insert the new column in. 
	///< @param title The title to set the header to. 
	///< @param cell The CellRenderer. 
	///< @param attributes The tree column attributes to set.
	///< @return The number of columns in the tree view after insertion.
	///<	
	///< If position is -1, then the newly created column is appended to the end. 
	///< The column is initialized with the attributes given.
	
	int insert_column(int position, const char *title, CellRenderer& cell, const CellDataSlot& data);
	int insert_column(int position, const String& title, CellRenderer& cell, const CellDataSlot& data);
	///< Convenience method that inserts a new column into the TreeView with the given cell renderer
	///< and a TreeViewColumn::CellDataSlot to set cell renderer attributes.
	///< @param position The position to insert, or -1 to append.
	///< @param title The column title.
	///< @param cell The cell renderer for <EM>column</EM>. 
	///< @param data The callback slot to set attributes of cell renderer.
	///< @return The number of columns in the tree view post-insert
	///<
	///< See also Gtk::TreeViewColumn::set_cell_data_func(), Gtk::TreeViewColumn::pack_start().
	 
	int remove_column(TreeViewColumn& column);
	///< Removes column from the tree view.
	///< @param column The TreeViewColumn to remove. 
	///< @return The number of columns in the tree view after removing.
	 
	void move_column_after(TreeViewColumn& column, TreeViewColumn *base_column);
	///< Moves <EM>column</EM> to be after to <EM>base_column</EM>. 
	///< @param column The TreeViewColumn to be moved. 
	///< @param base_column The TreeViewColumn to be moved relative to, or null.
	///<	
	///< If <EM>base_column</EM> is null, then column is placed in the first position.
	
	void set_expander_column(TreeViewColumn *column);
	///< Sets the column to draw the expander arrow at. 
	///< @param column The column to draw the expander arrow at, or null. 
	///< 	
	///< It must be in the tree view. If <EM>column</EM> is null, then the 
	///< expander arrow is always at the first visible column.
	
	void set_column_drag_function(const ColumnDropSlot& drop);
	///< Sets a user callback slot for determining where a column may be dropped when dragged.
	///< @param drop A callback slot to determine which columns are reorderable, or null.
	///<	 
	///< This slot is called on every column pair in turn at the beginning of a column drag
	///< to determine where a drop can take place. The arguments passed to the slot method are:
	///< the tree view, the TreeViewColumn being dragged and the two TreeViewColumns determining
	///< the drop spot. If either of the TreeViewColumn arguments for the drop spot are null, 
	///< then they indicate an edge. If slot is set to be null, then tree view reverts to the
	///< default behavior of allowing all columns to be dropped everywhere.

	void scroll_to_point(int tree_x, int tree_y);
	///< Scrolls the tree view such that the top-left corner of the visible area is tree_x, tree_y,
	///< where tree_x and tree_y are specified in tree window coordinates.
	///< @param tree_x The X coordinate of new top-left pixel of visible area, or -1. 
	///< @param tree_y The Y coordinate of new top-left pixel of visible area, or -1.
	///<	 
	///< The tree view must be realized before this function is called. If it isn't, you 
	///< probably want to be using scroll_to_cell(). If either tree_x or tree_y are -1, then
	///< that direction isn't scrolled.
	 
	void scroll_to_cell(const TreePath *path, const TreeViewColumn *column);
	///< Moves the alignments of the tree view to the position specified by column and path.
	///< @param path The path of the row to move to, or null. 
	///< @param column The TreeViewColumn to move horizontally to, or null. 
	///<	
	///< If <EM>column</EM> is null, then no horizontal scrolling occurs. Likewise, if <EM>path</EM>
	///< is null no vertical scrolling occurs. At a minimum, one of <EM>column</EM> or <EM>path</EM> need
	///< to be non-null. This method has no alignment arguments. Instead the tree does the minimum amount
	///< of work to scroll the cell onto the screen. This means that the cell will be scrolled to the edge
	///< closest to it's current position. If the cell is currently visible on the screen, nothing is done. 
	///<
	///< This method only works if the model is set, and path is a valid row on the model. If the
	///< model changes before the tree view is realized, the centered path will be modified to
	///< reflect this change.
	
	void scroll_to_cell(const TreePath *path, const TreeViewColumn *column, float row_align, float col_align);
	///< Moves the alignments of the tree view to the position specified by column and path.
	///< @param path The path of the row to move to, or null. 
	///< @param column The TreeViewColumn to move horizontally to, or null. 
	///< @param row_align The vertical alignment of the row specified by path. 
	///< @param col_align The horizontal alignment of the column specified by column.
	///<	 
	///< If <EM>column</EM> is null, then no horizontal scrolling occurs. Likewise, if <EM>path</EM>
	///< is null no vertical scrolling occurs. At a minimum, one of <EM>column</EM> or <EM>path</EM> need
	///< to be non-null. <EM>row_align</EM> determines where the row is placed, and <EM>col_align</EM>
	///< determines where the column is placed. Both are expected to be between 0.0 and 1.0. 0.0 means 
	///< left/top alignment, 1.0 means right/bottom alignment, 0.5 means center. If the cell is currently
	///< visible on the screen, nothing is done. 
	///<
	///< This method only works if the model is set, and path is a valid row on the model. If the
	///< model changes before the tree view is realized, the centered path will be modified to
	///< reflect this change.
	 
	void row_activated(TreePath& path, TreeViewColumn& column);
	///< Activates the cell determined by path and column.
	///< @param path The TreePath to be activated. 
	///< @param column The TreeViewColumn to be activated. 
	
	void expand_all();
	///< Recursively expands all nodes in the tree view.
	
	void collapse_all();
	///< Recursively collapses all visible, expanded nodes in the tree view.

	void expand_to_path(const TreePath& path);
	///< Expands the row at path.
	///< @param path The path to a row.
	///<
	///< This will also expand all parent rows of <EM>path</EM> as necessary.

	bool expand_row(const TreePath& path, bool open_all);
	///< Opens the row specified by <EM>path</EM> so its children are visible.
	///< @param path The path to a row. 
	///< @param open_all Whether to recursively expand, or just expand the immediate children. 
	///< @return <EM>true</EM> if the row existed and had children.
	 
	bool collapse_row(const TreePath& path);
	///< Collapses the row specified by <EM>path</EM> hiding its child rows, if they exist.
	///< @param path The path to a row in the tree view. 
	///< @return <EM>true</EM> if the row was collapsed.
	 
	void map_expanded_rows(const MappingSlot& map);
	///< Calls the <EM>map</EM> slot on all expanded rows.
	///< @param map The callback slot to be called.
	
	void set_reorderable(bool reorderable);
	///< This function is a convenience function to allow you to reorder models that support
	///< the drag-and-drop interface; both TreeStore and ListStore support these. 
	///< @param reorderable <EM>true</EM> if the tree can be reordered.
	///<	
	///< If <EM>reorderable</EM> is true, then the user can reorder the model by dragging
	///< and dropping rows. The developer can listen to these changes by connecting to the 
	///< model's signals. This method does not give you any degree of control over the order,
	///< any reorderering is allowed. If more control is needed, you should probably handle
	///< drag and drop manually.

	void set_cursor(const TreePath& path, TreeViewColumn *focus_column, bool start_editing = false);
	///< Sets the current keyboard focus to be at path, and selects it.
	///< @param path A TreePath. 
	///< @param focus_column A TreeViewColumn, or null. 
	///< @param start_editing <EM>true</EM> if the specified cell should start being edited.
	///<	 
	///< This is useful when you want to focus the user's attention on a particular row.
	///< If <EM>focus_column</EM> is not null, then focus is given to the column specified
	///< by it. Additionally, if <EM>focus_column</EM> is specified, and start_editing is true, then
	///< editing should be started in the specified cell. This function is often followed
	///< by Gtk::Widget::grab_focus() in order to give keyboard focus to the widget. Please
	///< note that editing can only happen when the widget is realized.

	void set_cursor_on_cell(const TreePath& path, TreeViewColumn *focus_column, CellRenderer *focus_cell, bool start_editing = false);
	///< Sets the current keyboard focus to be at path, and selects it. 
	///< @param path A TreePath.
	///< @param focus_column A TreeViewColumn, or null.
	///< @param focus_cell A CellRenderer, or null.
	///< @param start_editing Set <EM>true</EM> if the specified cell should start being edited.
	///<
	///< This is useful when you want to focus the user's attention on a particular row.
	///< If <EM>focus_column</EM> is not null, then focus is given to the column specified 
	///< by it. If <EM>focus_column</EM> and <EM>focus_cell</EM> are not null, and 
	///< <EM>focus_column</EM> contains 2 or more editable or activatable cells, then focus
	///< is given to the cell specified by <EM>focus_cell</EM>. Additionally, if 
	///< <EM>focus_column</EM> is specified, and <EM>start_editing</EM> is true, then editing
	///< should be started in the specified cell. This method is often followed by 
	///< Gtk::Widget::grab_focus() in order to give keyboard focus to the tree view. Please
	///< note that editing can only happen when the widget is realized.

	void widget_to_tree_coords(int wx, int wy, int *tx, int *ty) const;
	///< Converts widget coordinates to coordinates for the tree window (the full 
	///< scrollable area of the tree).
	///< @param wx The widget X coordinate. 
	///< @param wy The widget Y coordinate. 
	///< @param tx The return location for tree X coordinate. 
	///< @param ty The return location for tree Y coordinate.
	 
	void tree_to_widget_coords(int tx, int ty, int *wx, int *wy) const;
	///< Converts tree coordinates (coordinates in the full scrollable area of the tree)
	///< to widget coordinates.
	///< @param tx The tree X coordinate. 
	///< @param ty The tree Y coordinate. 
	///< @param wx The return location for widget X coordinate. 
	///< @param wy The return location for widget Y coordinate.
	 
	void set_rules_hint(bool setting);
	///< This method tells GTK+ that the user interface for your application requires
	///< users to read across tree rows and associate cells with one another. 
	///< @param setting <EM>true</EM> if the tree requires reading across rows.
	///<	
	///< By default, GTK+ will then render the tree with alternating row colors. 
	///< Do not use it just because you prefer the appearance of the ruled tree; that's
	///< a question for the theme. Some themes will draw tree rows in alternating colors
	///< even when rules are turned off, and users who prefer that appearance all the
	///< time can choose those themes. You should call this method only as a semantic
	///< hint to the theme engine that your tree makes alternating colors useful from 
	///< a functional standpoint (since it has lots of columns, generally).

	void enable_model_drag_source(Gdk::ModifierTypeField start_button_mask, 
	                              const std::vector<TargetEntry>& targets, 
	                              Gdk::DragActionField actions);
	///< Sets up the tree view so that GTK+ will start a drag operation when the user
	///< clicks and drags on the tree view. 
	///< @param start_button_mask The bitmask of buttons that can start the drag. 
	///< @param targets The TargetEntrys for the targets the drag will support. 
	///< @param actions The bitmask of possible actions for a drag from this widget.	
	///<
	///< This method is provided for manual drag-and-drop. TreeView already provides
	///< simple drag-and-drop (see set_reorderable()). 	
	
	void enable_model_drag_dest(const std::vector<TargetEntry>& targets, Gdk::DragActionField actions);
	///< Sets the tree view as a potential drop destination. 
	///< @param targets A vector of TargetEntry indicating the drop types that this tree view will accept. 
	///< @param actions A bitmask of possible actions for a drop onto this widget.
	///<	
	///< The targets and actions fields only are used if DEST_DEFAULT_MOTION or
	///< DEST_DEFAULT_DROP are given. 
	 
	void unset_rows_drag_source();
	///< Undoes the effects of enable_model_drag_source().
	 
	void unset_rows_drag_dest();
	///< Clears information about a drop destination set with enable_model_drag_dest().
	///< The tree view will no longer receive notification of drags. 
	
	void set_drag_dest_row(const TreePath& path, TreeViewDropPosition pos);
	///< Sets where a dropped row goes.
	///< @param path A TreePath to the destination row.
	///< @param pos One of the position values in the TreeViewDropPosition enumeration.
	
	Pointer<Gdk::Pixmap> create_row_drag_icon(const TreePath& path);
	///< Creates a Gdk::Pixmap representation of the row at path; this image is used for a drag icon.
	///< @param path A TreePath in tree_view. 
	///< @return A smart pointer to a newly-allocated pixmap of the drag icon.
	
	void set_enable_search(bool enable_search);
	///< If enable_search is set, then the user can type in text to search through the tree interactively.
	///< @param enable_search <EM>true</EM> if the user can search interactively.
	
	void set_search_column(int column);
	///< Sets <EM>column</EM> as the column where the interactive search code should search in.
	///< @param column The column of the model to search in.
	///<	 
	///< Additionally, turns on interactive searching. Note that column
	///< refers to a column of the model.

	void set_fixed_height_mode(bool enable);
	///< Enables or disables the fixed height mode of the tree view. 
	///< @param enable Set to <EM>true</EM> to enable fixed height mode.
	///<	
	///< Fixed height mode speeds up Gtk::TreeView by assuming that all rows
	///< have the same height. Only enable this option if all rows are the 
	///< same height and all columns are of type Gtk::TREE_VIEW_COLUMN_FIXED.

	void set_hover_selection(bool hover);
	///< Enables or disables the hover selection mode of the tree view. 
	///< @param hover <EM>true</EM> to enable hover selection mode.
	///<	
	///< Hover selection makes the selected row follow the pointer. Currently, 
	///< this works only for the selection modes Gtk::SELECTION_SINGLE and 
	///< Gtk_SELECTION_BROWSE.
		
	void set_hover_expand(bool expand);
	///< Enables of disables the hover expansion mode of the tree view. 
	///< @param expand Set to <EM>true</EM> to enable hover expansion mode 
	///<	
	///< Hover expansion makes rows expand or collaps if the pointer moves over them.

	void  set_row_separator_func(const RowSeparatorSlot& slot);
	///< Sets the row separator function, which is used to determine
	///< whether a row should be drawn as a separator. 
	///< @param slot A RowSeparatorSlot. 

	void  unset_row_separator_func();
	///< Unsets the row separator function set by set_row_separator_func(). After calling
	///< this method no separators will be drawn. This is the default value so you only 
	///< need to call this method if you previously called set_row_separator_func().

	void set_search_equal_func(const SearchEqualSlot& search_equal);
	///< Sets the compare slot for the interactive search capabilities.
	///< @param search_equal The compare slot to call during the search. 

/// @}	
/// @name Signal Proxies
/// @{

	const SetScrollAdjustmentsSignalProxy signal_set_scroll_adjustments();
	///< Connect to the set_scroll_adjustments_signal; emitted when a tree view is added
	///< to a scrolling aware parent.

	const RowActivatedSignalProxy signal_row_activated();
	///< Connect to the row_activated_signal; emitted when a row is activated.

	const TestExpandRowSignalProxy signal_test_expand_row();
	///< Connect to the test_expand_row_signal; emitted to determine if a row has child rows
	///< and can be opened.

	const TestCollapseRowSignalProxy signal_test_collapse_row();
	///< Connect to the test_collapse_row_signal; emitted to determine if a row has visible child rows
	///< that can be collapsed.

	const RowExpandedSignalProxy signal_row_expanded();
	///< Connect to the row_expanded_signal; emitted when a row is opened so its children are visible.

	const RowCollapsedSignalProxy signal_row_collapsed();
	///< Connect to the row_collapsed_signal; emitted when a row is collapsed to hide its child rows.

	const ColumnsChangedSignalProxy signal_columns_changed();
	///< Connect to the columns_changed_signal; emitted whenever the order or number of columns
	///< in the tree view changes.

	const CursorChangedSignalProxy signal_cursor_changed();
	///< Connect to the cursor_changed_signal; emitted whenever the current keyboard focus changes.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/treeview.inl>

#endif // XFC_GTK_TREE_VIEW_HH

