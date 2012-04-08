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
 
/// @file xfc/gtk/celllayout.hh
/// @brief A GtkCellLayout C++ wrapper interface.
///
/// Provides CellLayout, an interface implemented by all objects which want to provide
/// a Gtk::TreeViewColumn-like API for packing cells, setting attributes and data funcs.

#ifndef XFC_GTK_CELL_LAYOUT_HH
#define XFC_GTK_CELL_LAYOUT_HH

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __GTK_CELL_LAYOUT_H__
#include <gtk/gtkcelllayout.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {
class Event;
}

namespace Gtk {

class CellRenderer;
class TreeIter;
class TreeModel;

/// @class CellColumnAttributes celllayout.hh xfc/gtk/celllayout.hh
/// @brief A C++ wrapper for setting multiple attributes on a column of cells.
///
/// CellColumnAttributes is a convenience class that is used to set multiple attributes
/// on a column of cells at one time. It is dervied from Xfc::StackObject so it cannot
/// be created dynamically. CellColumnAttributes is used instead the variable argument
/// lists found in the GTK+ C API. 
///
/// To add entries to a CellColumnAttributes object call add(). There is no remove()
/// function but you can call clear() to remove all entries. You can call clear() 
/// when you want to reuse a CellColumnAttributes object.
///
/// The CellColumnAttributes object is used in the Gtk::CellLayout and Gtk::TreeViewColumn API's.
///	
/// <B>Here's a simple TreeViewColumn example:</B>
///
/// @code
/// enum { TEXT_COLUMN, COLOR_COLUMN, N_COLUMNS };
/// ...
/// Gtk::CellRendererText  *cell = new Gtk::CellRendererText();
///
/// CellColumnAttributes attributes;
/// attributes.add("text", TEXT_COLUMN);
/// attributes.add("foreground", COLOR_COLUMN);
/// Gtk::TreeViewColumn *column = new Gtk::TreeViewColumn("Title", cell, attributes);
/// @endcode

class CellColumnAttributes : public StackObject
{
	std::vector<String> attributes_;	
	std::vector<int> columns_;
	
public:	
/// @name Constructors
/// @{

	CellColumnAttributes();
	///< Constructs an empty CellColumnAttributes object.

	CellColumnAttributes(const char *attribute, int column);
	CellColumnAttributes(const String& attribute, int column);
	///< Constructs a new CellColumnAttributes object and adds the attribute entry for <EM>column</EM>.
	///< @param attribute An attribute on a cell renderer. 
	///< @param column The column position in a tree model to get the attribute from.
	
	~CellColumnAttributes();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	const std::vector<String>& get_attributes() const;
	///< Returns a const reference to the vector of attributes added.
	///< @return A vector of String. 

	const std::vector<int>& get_columns() const;
	///< Returns a const reference to the vector of columns added.
	///< @return A vector of int. 

	bool empty() const;
	///< Determines if the tree column attributes object is empty.
	///< @return <EM>true</EM> if the CellColumnAttributes object is empty.
	
	int size() const;
	///< Gets the number of entries added to the CellColumnAttributes object.
	///< @return The number of entries added.  

/// @}
/// @name Methods
/// @{
	
	void add(const char *attribute, int column);
	void add(const String& attribute, int column);
	///< Adds an attribute entry for <EM>column</EM> to the CellColumnAttributes object.
	///< @param attribute An attribute on a cell renderer. 
	///< @param column The column position in a tree model to get the attribute from.

	void clear();
	///< Removes all entries from the CellColumnAttributes object.

/// @}
};

/// @class CellLayout celllayout.hh xfc/gtk/celllayout.hh
/// @brief A GtkCellLayout C++ wrapper class.
///
/// CellLayout is an interface that can be implemented by an object that wants to provide
/// a Gtk::TreeViewColumn-like API for packing cells, setting attributes and data funcs.
///
/// CellLayout is implemented by Gtk::EntryCompletion, Gtk::TreeViewColumn, Gtk::ComboBox
/// and Gtk::ComboBoxEntry.

class CellLayout : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	CellLayout();
	///< Constructs a new CellLayout object.	
	
	virtual ~CellLayout() = 0;
	///< Destructor.
	
/// @}

public:
	typedef sigc::slot<void, CellRenderer&, const TreeModel&, const TreeIter&> CellDataSlot;
	///< Signature of the callback slot to be called to set the attributes of a cell's cell
	///< renderers, instead of just using the straight mapping between the cell and the model.
	///<
	///< <B>Example:</B> Method signature for CellDataSlot.
	///< @code
	///< void method(CellRenderer& cell, const TreeModel& tree_model, const TreeIter& iter);
	///< // cell: The cell renderer whose value is to be set.
	///< // tree_model: The TreeModel being rendered.
	///< // iter: A TreeIter indicating the row to set the value for.
	///< @endcode
	///< This is useful for customizing the cell renderer. For example, a function
	///< might get an integer from the tree_model, and render it to the "text"
	///< attribute of "cell" by converting it to its written equivilent. This is set
	///< by calling set_cell_data_func().

/// @name Accessors
/// @{

	GtkCellLayout* gtk_cell_layout() const;
	///< Get a pointer to the GtkCellLayout structure.

	operator GtkCellLayout* () const;
	///< Conversion operator; safely converts a CellLayout to a GtkCellLayout pointer.

/// @}
/// @name Methods
/// @{

	void pack_start(CellRenderer& cell, bool expand = true);
	///< Packs the cell into the beginning of the cell layout. 
	///< @param cell A Gtk::CellRenderer. 
	///< @param expand Set <EM>true</EM> if <EM>cell</EM> is to be given extra space allocated to cell_layout. 
	///<	
	///< If <EM>expand</EM> is false, then the cell is allocated no more space
	///< than it needs. Any unused space is divided evenly between cells for which
	///< <EM>expand</EM> is true.

	void  pack_end(CellRenderer& cell, bool expand = true);
	///< Adds the cell to the end of the cell layout. 
	///< @param cell A Gtk::CellRenderer. 
	///< @param expand Set <EM>true</EM> if <EM>cell</EM> is to be given extra space allocated to cell_layout. 
	///<	
	///< If <EM>expand</EM> is false, then the cell is allocated no more space
	///< than it needs. Any unused space is divided evenly between cells for which
	///< <EM>expand</EM> is true.

	void add_attribute(CellRenderer& cell, const char *attribute, int column);
	void add_attribute(CellRenderer& cell, const String& attribute, int column);
	///< Adds an attribute mapping to the list in the cell layout. 
	///< @param cell A Gtk::CellRenderer. 
	///< @param attribute An attribute on the renderer. 
	///< @param column The column position in the model to get the attribute from.
 	///<	
	///< The <EM>column</EM> is the column of the model to get a value from, 
	///< and the <EM>attribute</EM> is the parameter on cell to be set from the
	///< value. So for example if column 2 of the model contains strings, you 
	///< could have the "text" attribute of a Gtk::CellRendererText get its 
	///< values from column 2.
	
	void set_attributes(CellRenderer& cell, const CellColumnAttributes& attributes);
	///< Sets the attributes in the CellColumnAttributes object as the attributes of the cell layout. 
	///< @param cell The CellRenderer. 
	///< @param attributes The attributes to set on the column of cells.
	///<	
	///< All existing attributes are removed, and replaced with the new attributes.
	///<
	///< <B>Here's a simple TreeViewColumn example:</B>
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

	void set_cell_data_func(CellRenderer& cell, const CellDataSlot& slot);
	///< Sets the CellDataSlot to use for the cell layout. 
	///< @param cell A Gtk::CellRenderer. 
	///< @param slot The CellDataSlot to use. 
	///<	
	///< The CellDataSlot is used instead of the standard attributes mapping
	///< for setting the column value, and should set the value of cell_layout's
	///< cell renderer(s) as appropriate.

	void remove_cell_data_func(CellRenderer& cell);
	///< Removes the current CellDataSlot used for the cell layout. 
	///< @param cell A Gtk::CellRenderer. 

	void reorder(CellRenderer& cell, int position);
	///< Re-inserts cell at <EM>position</EM>. 
	///< @param cell A GtkCellRenderer to reorder. 
	///< @param position The new position to insert <EM>cell</EM> at. 
	///<	
	///< Note that <EM>cell</EM> must already be packed into the cell layout
	///< for this method to function properly.
	
	void clear_attributes(CellRenderer& cell);
	///< Clears all existing attributes previously set with set_attributes().
	///< @param cell A Gtk::CellRenderer to clear the attribute mapping on. 

	void clear();
	///< Unsets all the mappings on all renderers on the cell layout.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/celllayout.inl>

#endif // XFC_GTK_CELL_LAYOUT_HH

