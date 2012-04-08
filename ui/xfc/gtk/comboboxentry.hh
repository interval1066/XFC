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

/// @file xfc/gtk/comboboxentry.hh
/// @brief A GtkComboBoxEntry C++ wrapper interface.
///
/// Provides ComboBoxEntry, a widget with a text entry field with a dropdown list. 

#ifndef XFC_GTK_COMBO_BOX_ENTRY_HH
#define XFC_GTK_COMBO_BOX_ENTRY_HH

#ifndef XFC_GTK_COMBO_BOX_HH
#include <xfc/gtk/combobox.hh>
#endif

#ifndef __GTK_COMBO_BOX_ENTRY_H__
#include <gtk/gtkcomboboxentry.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class ComboBoxEntry comboboxentry.hh xfc/gtk/comboboxentry.hh
/// @brief A GtkComboBoxEntry C++ wrapper class.
///
/// ComboBoxEntry is a widget with a text entry field with a dropdown list.
///
/// <B>See also:</B> the <A HREF="../../howto/html/combobox.html">ComboBox</A> HOWTOs and examples.

class ComboBoxEntry : public ComboBox
{
	friend class G::Object;

	ComboBoxEntry(const ComboBoxEntry&);
	ComboBoxEntry& operator=(const ComboBoxEntry&);

protected:
/// @name Constructors
/// @{

	explicit ComboBoxEntry(GtkComboBoxEntry *entry_box, bool owns_reference = false);
	///< Construct a new ComboBoxEntry from an existing GtkComboBoxEntry.
	///< @param entry_box A pointer to a GtkComboBoxEntry.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>entry_box</EM> can be a newly created GtkComboBoxEntry or an existing
	///< GtkComboBoxEntry (see G::Object::Object).

/// @}

public:
	typedef GtkComboBoxEntry CObjectType;

/// @name Constructors
/// @{

	ComboBoxEntry();
	///< Constructs a new ComboBoxEntry which has an Entry widget as child. 
	///< After construction, you should set a model using Gtk::ComboBbox::set_model()
	///< and a text_column using set_text_column().

	ComboBoxEntry(TreeModel& model, int text_column);
	///< Constructs a new ComboBoxEntry which has an Entry widget and a popup list of strings. 
	///< @param model A Gtk::TreeModel.
	///< @param text_column A column in model to get the strings from. 
	///<	
	///< You can get the Entry widget from a ComboBoxEntry by casting
	///< Gtk::Bin::get_child() to an Entry. To add and remove strings from
	///< the list, just modify <EM>model</EM> using its data manipulation API.
	
	virtual ~ComboBoxEntry();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkComboBoxEntry* gtk_combo_box_entry() const;
	///< Get a pointer to the GtkComboBoxEntry structure.

	operator GtkComboBoxEntry* () const;
	///< Conversion operator; safely converts an ComboBoxEntry to a GtkComboBoxEntry pointer.
	
	String get_text() const;
	///< Retrieves the contents of the entry widget (see also Gtk::Entry::get_text()).
	///< @return A String that contains the contents of the entry widget.

	int get_text_column() const;
	///< Gets the column which the entry box is using to get the strings from.
	///< @return A column in the data source model of the entry box. 

/// @}
/// @name Methods
/// @{

	void set_text_column(int text_column);
	///< Sets the model column which the entry box should use to get strings from to be <EM>text_column</EM>.
	///< @param text_column A column in model to get the strings from. 

/// @}
};

/// @class ComboBoxEntryText comboboxentry.hh xfc/gtk/comboboxentry.hh
/// @brief A Text Gtk::ComboBoxEntry class.
///
/// ComboBoxEntryText is an editable text combo box, which is a Gtk::ComboBoxEntry
/// just displaying strings. If you use this text combo box, you should only manipulate
/// its data source with the following convenience methods: append_text(), insert_text(),
/// prepend_text() and remove_text().
///
/// <B>See also:</B> the <A HREF="../../howto/html/combobox.html">ComboBox</A> HOWTOs and examples.

class ComboBoxEntryText : public ComboBoxEntry
{
	ComboBoxEntryText(const ComboBoxEntryText&);
	ComboBoxEntryText& operator=(const ComboBoxEntryText&);

public:
/// @name Constructors
/// @{

	ComboBoxEntryText();
	///< Constructs a new editable text ComboBox widget.
	
	virtual ~ComboBoxEntryText();
	///< Destructor.
	
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

/// @}
};
		
} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/comboboxentry.inl>

#endif // XFC_GTK_COMBO_BOX_ENTRY_HH

