/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
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
 
/// @file xfc/gtk/iconview.hh
/// @brief A GtkIconView C++ wrapper interface.
///
/// Provides IconView, a widget which displays a list of icons in a grid.

#ifndef XFCE_GTK_ICON_VIEW_HH
#define XFC_GTK_ICON_VIEW_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_ICON_VIEW_H__
#include <gtk/gtkiconview.h>
#endif

namespace Xfc {

namespace Gtk {

class TreePath;
class TreeModel;

/// @class IconView iconview.hh xfc/gtk/iconview.hh
/// @brief A GtkIconView C++ wrapper class.
///
/// IconView provides an alternative view on a list model. It displays the model
/// as a grid of icons with labels. Like TreeView, it allows to select one or 
/// multiple items (depending on the selection mode, see set_selection_mode()).
/// In addition to selection with the arrow keys, IconView supports rubberband
/// selection, which is controlled by dragging the pointer.

class IconView : public Container
{
	friend class G::Object;
	
	IconView(const IconView&);
	IconView& operator=(const IconView&);
	
protected:
/// @name Constructors
/// @{

	explicit IconView(GtkIconView *icon_view, bool owns_reference = false);
	///< Construct a new IconView from an existing GtkIconView.
	///< @param icon_view A pointer to a GtkIconView.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>icon_view</EM> can be a newly created GtkIconView or an existing
	///< GtkIconView. (see G::Object::Object).
	
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

	typedef G::Signal<void, const TreePath&> ItemActivatedSignalType;
	typedef G::SignalProxy<TypeInstance, ItemActivatedSignalType> ItemActivatedSignalProxy;
	static const ItemActivatedSignalType item_activated_signal;
	///< Item activated signal (see signal_item_activated()). Calls a slot with the signature:
	///< @code
	///< void function(const TreePath& path);
	///< // path: The TreePath of the item being activated.
	///< @endcode

	typedef G::Signal<void> SelectionChangedSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionChangedSignalType> SelectionChangedSignalProxy;
	static const SelectionChangedSignalType selection_changed_signal;
	///< Selection changed signal (see signal_selection_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkIconView CObjectType;
	
	typedef sigc::slot<void, const TreePath&> ForeachSlot;
	///< Signature of the callback slot to be called by selected_foreach() to map all selected rows.
	///<
	///< <B>Example:</B> Method signature for ForeachSlot.
	///< @code
	///< void method(const Gtk::TreePath& path);
	///< // path: The TreePath of a selected row.
	///< @endcode
	///<
	///< The slot is called on every selected row in the icon view.

/// @name Constructors
/// @{
	
	IconView();
	///< Constructs a new IconView widget.
	
	IconView(TreeModel& model);
	///< Constructs a new IconView widget with the model <EM>model</EM>.
	///< @param model The model. 
	
	virtual ~IconView();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkIconView* gtk_icon_view() const;
	///< Get a pointer to the GtkIconView structure.

	operator GtkIconView* () const;
	///< Conversion operator; safely converts an IconView to a GtkIconView pointer.

	TreeModel *get_model() const;
	///< Gets the model the icon view is based on. 
	///< @return A Gtk::TreeModel, or null if none is currently being used.

	int get_text_column() const;
	///< Gets the column with text for icon view.
	///< @return The text column, or -1 if it's unset. 	
	
	int get_markup_column() const;
	///< Gets the column with markup text for the icon view.
	///< @return The markup column, or -1 if it's unset.

	int get_pixbuf_column() const;
	///< Gets the column with pixbufs for the icon view.
	///< @return The pixbuf column, or -1 if it's unset.	

	Orientation get_orientation() const;
	///< Gets the value of the "orientation" property which determines 
	///< whether the labels are drawn beside the icons instead of below.
	///< @return The relative position of texts and icons. 	
	
	int get_columns() const;
	///< Gets the number of columns to displayed in the icon view.	
	///< @return The number of columns.	

	int get_item_width() const;
	///< Gets the current width used for each item in the icon view.
	///< @return The item width to use.

	int get_spacing() const;
	///< Gets the space which is inserted between cells of an item.
	///< @return The space between cells of an item (e.g. pixbuf and text).

	int get_row_spacing() const;
	///< Gets the space between grid rows in the icon view.
	///< @return The space to between grid rows.

	int get_column_spacing() const;
	///< Gets the space between grid columns in the icon view.
	///< @return The space to between grid columns.
	
	int get_margin() const;
	///< Gets the space at the edges of the icon view.
	///< @return The space at the edges of the icon view.

	Pointer<TreePath> get_path_at_pos(int x, int y) const;
	///< Finds the path at the point (x, y), relative to widget coordinates.
	///< @param x The x position to be identified. 
	///< @param y The y position to be identified. 
	///< @return The TreePath corresponding to the icon, or null if no icon exists at that position.

	SelectionMode get_selection_mode() const;
	///< Gets the selection mode of the icon view.
	///< @return The current selection mode.
	
	bool path_is_selected(const TreePath& path) const;
	///< Determines whether the icon pointed to by <EM>path</EM> is currently selected.
	///< @param path A TreePath to check selection on. 
	///< @return <EM>true</EM> if the path is selected.
	///< 
	///< If icon does not point to a valid location, <EM>false</EM> is returned.

	bool get_selected_items(std::vector<TreePath>& items) const;
	///< Fills a vector of TreePath with a list of the paths of all selected items. 
	///< @param items The vector of TreePath that will hold the list of paths.
	///< @returns <EM>true</EM> if the vector is not empty.
	///<	
	///< Additionally, if you are planning on modifying the model after calling this function,
	///< you may want to convert the returned list into a list of Gtk::TreeRowReferences. To
	///< do this use the constructor TreeRowReference(G::Object&, TreeModel&, const TreePath&).
	
/// @}
/// @name Methods
/// @{

	void set_model(TreeModel *model);
	///< Sets the model for the icon view. 
	///< @param model The model.
	///<	
	///< If the icon view already has a model set, it will remove it before setting
	///< the new model. If model is null, then it will unset the old model.

	void set_text_column(int column);
	///< Sets the column with text for the icon view to be column. 
	///< @param column A column in the currently used model.	
	///< 	
	///< The text column must be of type G_TYPE_STRING.

	void set_markup_column(int column);
	///< Sets the column with markup information for the icon view to be <EM>column</EM>.
	///< @param column A column in the currently used model.
	///<	 
	///< The markup column must be of type G_TYPE_STRING. If the markup column is set
	///< to something, it overrides the text column set by set_text_column().

	void set_pixbuf_column(int column);
	///< Sets the column with pixbufs for the icon view to be <EM>column</EM>. 
	///< @param column A column in the currently used model.	
	///< 	
	///< The pixbuf column must be of type GDK_TYPE_PIXBUF.

	void set_orientation(Orientation orientation);
	///< Sets the "orientation" property which determines whether the labels
	///< are drawn beside the icons instead of below.
	///< @param orientation The relative position of texts and icons.

	void set_columns(int columns);
	///< Sets the number of columns to display in the icon view.	
	///< @param columns The number of columns.	

	void set_item_width(int item_width);
	///< Sets the width used for each item in the icon view.
	///< @param item_width The item width to use.

	void set_spacing(int spacing);
	///< Sets the space which is inserted between the cells of an item in the icon view.
	///< @param spacing The space to insert between cells (e.g. pixbuf and text).

	void set_row_spacing(int row_spacing);
	///< Sets the space which is inserted between grid rows in the icon view.
	///< @param row_spacing The space to insert between grid rows.
	
	void set_column_spacing(int column_spacing);
	///< Sets the space which is inserted between grid columns in the icon view.
	///< @param column_spacing The space to insert between grid columns.

	void set_margin(int margin);
	///< Sets the space which is inserted at the edges of the icon view.
	///< @param margin The space inserted at the edges of the icon view

	void selected_foreach(const ForeachSlot& each);
	///< Calls the ForeachSlot for each selected icon. 
	///< @param each The callback slot to call for each selected icon. 
	///<	
	///< Note that the model or selection cannot be modified from within this function.

	void set_selection_mode(SelectionMode mode);
	///< Sets the selection mode of the icon view.
	///< @param mode The selection mode.
	 
	void select_path(const TreePath& path);
	///< Selects the row at <EM>path</EM>.
	///< @param path The TreePath to be selected.
		
	void unselect_path(const TreePath& path);
	///< Unselects the row at <EM>path</EM>.
	///< @param path The TreePath to be unselected.

	void select_all();
	///< Selects all the icons. The icon view must have its selection mode set to Gtk::SELECTION_MULTIPLE.
	
	void unselect_all();
	///< Unselects all the icons.

	void item_activated(const TreePath& path);
	///< Activates the item determined by path.
	///< @param path The TreePath to be activated.

/// @}
/// @name Signal Proxies
/// @{
	
	const SetScrollAdjustmentsSignalProxy signal_set_scroll_adjustments();
	///< Connect to the set_scroll_adjustments_signal; emitted when an icon view is added
	///< to a scrolling aware parent.

	const ItemActivatedSignalProxy signal_item_activated();
	///< Connect to the item_activated_signal; emitted when an item is activated.
	
	const SelectionChangedSignalProxy signal_selection_changed();
	///< Connect to the selection_changed_signal; emitted when the selection in the icon view changes.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/iconview.inl>

#endif // XFC_GTK_ICON_VIEW_HH

