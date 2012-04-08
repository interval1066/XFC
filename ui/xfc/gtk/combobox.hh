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

/// @file xfc/gtk/combobox.hh
/// @brief A GtkComboBox C++ wrapper interface.
///
/// Provides ComboBox, a widget used to choose from a list of items. 

#ifndef XFC_GTK_COMBO_BOX_HH
#define XFC_GTK_COMBO_BOX_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef XFC_GTK_CELL_LAYOUT_HH
#include <xfc/gtk/celllayout.hh>
#endif

#ifndef __GTK_COMBO_BOX_H__
#include <gtk/gtkcombobox.h>
#include <gtk/gtkcomboboxtext.h>
#endif

namespace Xfc {

namespace Atk {
class Object;
}

namespace Gtk {

/// @class ComboBox combobox.hh xfc/gtk/combobox.hh
/// @brief A GtkComboBox C++ wrapper class.
///
/// The ComboBox widget is used to choose an item from a list of items. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/combobox.html">ComboBox</A> HOWTOs and examples.

class ComboBox : public Bin, public CellLayout
{
	friend class G::Object;

	ComboBox(const ComboBox&);
	ComboBox& operator=(const ComboBox&);

protected:
/// @name Constructors
/// @{

	explicit ComboBox(GtkComboBox *combo_box, bool owns_reference = false);
	///< Construct a new ComboBox from an existing GtkComboBox.
	///< @param combo_box A pointer to a GtkComboBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>combo_box</EM> can be a newly created GtkComboBox or an existing
	///< GtkComboBox (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;
	///< Changed signal (see signal_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkComboBox CObjectType;
	
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

	ComboBox();
	///< Constructs a new combo box.
		
	ComboBox(TreeModel& model);
	///< Constructs a new combo box with the model initialized to <EM>model</EM>.
	///< @param model A Gtk::TreeModel. 
	
	virtual ~ComboBox();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkComboBox* gtk_combo_box() const;
	///< Get a pointer to the GtkComboBox structure.

	operator GtkComboBox* () const;
	///< Conversion operator; safely converts an ComboBox to a GtkComboBox pointer.

	int get_wrap_width() const;
	///< Gets the wrap width which is used to determine the number of columns for the popup menu.
	///< @return The wrap width.
	///<	 
	///< If the wrap width is larger than 1, the combo box is in grid mode.
	
	int get_row_span_column() const;
	///< Gets the column with row span information for the combo box.
	///< @return The row span column.

	int get_column_span_column() const;
	///< Gets the column with column span information for the combo box.
	///< @return The column span column.

	bool get_add_tearoffs() const;
	///< Determines whether dropdowns should have a tearoff menu item.
	///< @return <EM>true</EM> if the dropdowns have a tearoff menu item.
	
	bool get_focus_on_click() const;
	///< Determines whether the combo box grabs focus when it is clicked with the mouse (see set_focus_on_click()).
	///< @return <EM>true</EM> if the combo box grabs focus when it is clicked with the mouse. 
	
	int get_active() const;
	///< Gets the index of the currently active item, or -1 if there's no active item.
	///< @return An integer which is the index of the currently active item, or -1 if there's no active item.
	 
	bool get_active_iter(TreeIter& iter) const;
	///< Sets <EM>iter</EM> to point to the current active item, if it exists.
	///< @param iter A Gtk::TreeIter. 
	///< @return <EM>true</EM> if <EM>iter</EM> was set to point to the active item. 	

	TreeModel* get_model() const;
	///< Gets the Gtk::TreeModel which is acting as data source for the combo box.
	///< @return A Gtk::TreeModel.

	Atk::Object* get_popup_accessible() const;
	///< Gets the accessible object corresponding to the combo box's popup. 
	///< @return The accessible object corresponding to the combo box's popup. 
	///<
	///< This method is mostly intended for use by accessibility technologies; 
	///< applications should have little use for it.

/// @}
/// @name Methods
/// @{

	void set_wrap_width(int width);
	///< Sets the wrap width of the combo box to be <EM>width</EM>. 
	///< @param width The preferred number of columns.
	///<	
	///< The wrap width is basically the preferred number of columns when
	///< you want the popup to be layed out in a table.

	void set_row_span_column(int row_span);
	///< Sets the column with row span information for the combo box to be <EM>row_span</EM>. 
	///< @param row_span A column in the model passed during construction.
	///<	
	///< The row span column contains integers which indicate how many rows an item should span.
	
	void set_column_span_column(int column_span);
	///< Sets the column with column span information for the combo box to be <EM>column_span</EM>. 
	///< @param column_span A column in the model passed during construction. 
	///<	
	///< The column span column contains integers which indicate how many columns an item should span.

	void set_add_tearoffs(bool add_tearoffs);
	///< Sets whether the popup menu should have a tearoff menu item.
	///< @param add_tearoffs Set to <EM>true</EM> to add tearoff menu items.
	
	void set_focus_on_click(bool focus_on_click);
	///< Sets whether the combo box will grab focus when it is clicked with the mouse.
	///< @param focus_on_click Set to <EM>true</EM> if the combo box grabs focus when clicked with the mouse. 
	///<	 
	///< Making mouse clicks not grab focus is useful in places like toolbarswhere you
	///< don't want the keyboard focus removed from the main area of the application.
	
	void set_active(int index);
	///< Sets the active item of the combo box to be the item at index.
	///< @param index An index in the model passed during construction, or -1 to have no active item. 
		
	void set_active_iter(const TreeIter& iter);
	///< Sets the current active item to be the one referenced by iter. 
	///< @param iter The Gtk::TreeIter. 
	///< 	
	///< <EM>iter</EM> must correspond to a path of depth one.

	void set_model(TreeModel& model);
	///< Sets the model used by the combo box to be <EM>model</EM>.
	///< @param model A Gtk::TreeModel. 
	///<	 
	///< Will unset a previously set model (if applicable).

	void  set_row_separator_func(const RowSeparatorSlot& slot);
	///< Sets the row separator function, which is used to determine
	///< whether a row should be drawn as a separator. 
	///< @param slot The RowSeparatorSlot to call.	
	///<	
	///< By default no separators are drawn

	void  unset_row_separator_func();
	///< Unsets the row separator function set by set_row_separator_func(). After calling
	///< this method no separators will be drawn. This is the default value so you only 
	///< need to call this method if you previously called set_row_separator_func().
	
	void popup();
	///< Pops up the menu or dropdown list of the combo box. This method is mostly intended
	///< for use by accessibility technologies; applications should have little use for it.
	
	void popdown();
	///< Hides the menu or dropdown list of the combo box. This method is mostly intended
	///< for use by accessibility technologies; applications should have little use for it.

/// @}
/// @name Signal Proxies
/// @{

	const ChangedSignalProxy signal_changed();
	///< Connect to the changed_signal; emitted when the active item in the combo box is changed.

/// @}
};

/// @class ComboBoxText combobox.hh xfc/gtk/combobox.hh
/// @brief A Text Gtk::ComboBox class.
///
/// ComboBoxText is a text combo box, which is a Gtk::ComboBox just displaying strings.
/// If you use this text combo box, you should only manipulate its data source with the
/// following convenience methods: append_text(), insert_text(), prepend_text() and
/// remove_text().
///
/// <B>See also:</B> the <A HREF="../../howto/html/combobox.html">ComboBox</A> HOWTOs and examples.

class ComboBoxText : public ComboBox
{
	ComboBoxText(const ComboBoxText&);
	ComboBoxText& operator=(const ComboBoxText&);

public:
/// @name Constructors
/// @{

	explicit ComboBoxText(GtkComboBoxText *combo_box, bool owns_reference = false);
	///< Construct a new ComboBox from an existing GtkComboBox.
	///< @param combo_box A pointer to a GtkComboBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>combo_box</EM> can be a newly created GtkComboBox or an existing
	///< GtkComboBox (see G::Object::Object).

public:
	typedef GtkComboBoxText CObjectType;

/// @name Constructors
/// @{

	ComboBoxText();
	///< Constructs a new text combo box.
	
	virtual ~ComboBoxText();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{
	
	String get_active_text() const;
	///< Gets the currently active string in combo box.
	///< @return A string containing the currently active text, or a null string if none is selected.

/// @}
/// @name Methods
/// @{
	
	void append(const char *text);
	void append(const String& text);
	///< Appends a string to the list of strings stored in the combo box. 
	///< @param text A text string. 

	void prepend(const char *text);
	void prepend(const String& text);
	///< Prepends a string to the list of strings stored in the combo box. 
	///< @param text A text string. 

	void insert(int position, const char *text);
	void insert(int position, const String& text);
	///< Inserts a string at <EM>position</EM> in the list of strings stored in the combo box. 
	///< @param position An index to insert text. 
	///< @param text A text string. 

	void remove(int position);
	///< Removes the string at <EM>position</EM> from the combo box. 
	///< @param position The index of the item to remove. 

	void clear();
	///< Removes all entries from the combo box

/// @}
};
		
} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/combobox.inl>

#endif // XFC_GTK_COMBO_BOX_HH

