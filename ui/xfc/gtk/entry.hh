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
 
/// @file xfc/gtk/entry.hh
/// @brief A GtkEntry C++ wrapper interface.
///
/// Provides Entry, a single line text entry widget.

#ifndef XFC_GTK_ENTRY_HH
#define XFC_GTK_ENTRY_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef XFC_GTK_EDITABLE_HH
#include <xfc/gtk/editable.hh>
#endif

#ifndef XFC_GTK_CELL_EDITABLE_HH
#include <xfc/gtk/celleditable.hh>
#endif

#ifndef __GTK_ENTRY_H__
#include <gtk/gtkentry.h>
#endif

namespace Xfc {

namespace G {
class Unichar;
}

namespace Pango {
class Layout;
}

namespace Gtk {

class EntryCompletion;
class Menu;
class TreeModel;

/// @class Entry entry.hh xfc/gtk/entry.hh
/// @brief A GtkEntry C++ wrapper class.
///
/// The Entry widget is a single line text entry widget. A fairly large set of key bindings are
/// supported by default. If the entered text is longer than the allocation of the widget, the
/// widget will scroll so that the cursor position is visible. Entry implements the Editable and
///< CellEditable interfaces
///
/// <B>See also:</B> the <A HREF="../../howto/html/entry.html">Entry Widget</A> HOWTO and example.

class Entry : public Widget, public Editable, public CellEditable
{
	friend class G::Object;

	Entry(const Entry&);
	Entry& operator=(const Entry&);
	
protected:
/// @name Constructors
/// @{

	explicit Entry(GtkEntry *entry, bool owns_reference = false);
	///< Construct a new Entry from an existing GtkEntry.
	///< @param entry A pointer to a GtkEntry.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>entry</EM> can be a newly created GtkEntry or an existing
	///< GtkEntry (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Menu&> PopulatePopupSignalType;
	typedef G::SignalProxy<TypeInstance, PopulatePopupSignalType> PopulatePopupSignalProxy;
	static const PopulatePopupSignalType populate_popup_signal;
	///< Populate popup signal (see signal_populate_popup()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Menu& menu);
	///< // menu: The popup menu.
	///< @endcode

	typedef G::Signal<void> ActviateSignalType;
	typedef G::SignalProxy<TypeInstance, ActviateSignalType> ActviateSignalProxy;
	static const ActviateSignalType activate_signal;
	///< Actviate signal (see signal_activate()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
	typedef G::Signal<void, const String&> InsertAtCursorSignalType;
	typedef G::SignalProxy<TypeInstance, InsertAtCursorSignalType> InsertAtCursorSignalProxy;
	static const InsertAtCursorSignalType insert_at_cursor_signal;
	///< Insert at cursor signal (see signal_insert_at_cursor()). Calls a slot with the signature:
	///< @code
	///< void function(const String& text);
	///< // text: The new text to insert.
	///< @endcode
	
/// @}

public:
	typedef GtkEntry CObjectType;

/// @name Constructors
/// @{

	Entry();
	///< Construct a new Entry.

	explicit Entry(int max_length);
	///< Construct a new Entry that accepts at most max_length characters.
	///< @param max_length The maximum length of the entry, or 0 for no maximum.
	///<
	///< The value passed <EM>max_length</EM> in will be clamped to the range 0-65536.

	virtual ~Entry();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkEntry* gtk_entry() const;
	///< Get a pointer to the GtkEntry structure.

	operator GtkEntry* () const;
	///< Conversion operator; safely converts an Entry to a GtkEntry pointer.

	String get_text() const;
	///< Retrieves the contents of the widget (see also Gtk::Editable::get_chars()).
	///< @return A String that contains the contents of the widget.

	bool get_visibility() const;
	///< Returns true if the text in the widget is visible (see set_visibility()).
	
	G::Unichar get_invisible_char() const;
	///< Retrieves the character displayed in place of the real characters for entries with
	///< visisbility set to false (see set_invisible_char()).
	///< @return The current invisible char, or 0, if the entry does not show invisible text at all.

	bool get_has_frame() const;
	///< Returns true if the entry has a beveled frame (see set_has_frame()).

	bool get_activates_default() const;
	///< Returns true if the entry will activate the default widget (see set_activates_default()).

	int get_width_chars() const;
	///< Retrieves the number of chars to request space for, or negative if unset (see set_width_chars()).

	int get_max_length() const;
	///< Returns the maximum allowed length of the text in the Entry, or 0 if there is no maximum
	///< (see set_max_length()).
	
	Pango::Layout* get_layout() const;
	///< Gets the Pango::Layout used to display the entry. 
	///< @return The PangoLayout for this entry.
	///<
	///< The layout is useful to e.g. convert text positions to pixel positions, in
	///< combination with get_layout_offsets(). The returned layout is owned by the entry
	///< and must not be unreferenced by the caller.

	void get_layout_offsets(int *x, int *y) const;
	///< Obtains the position of the Pango::Layout used to render text in the entry,
	///< in widget coordinates. 
	///< @param x The location to store the X offset of the layout, or null.
	///< @param y The location to store the Y offset of the layout, or null.
	///<
	///< Useful if you want to line up the text in an entry with some other text, e.g.
	///< when using the entry to implement editable cells in a sheet widget. Also useful
	///< to convert mouse events into coordinates inside the Pango::Layout, e.g. to take
	///< some action if some part of the entry text is clicked.

	float get_alignment() const;
	///< Gets the value set by set_alignment().
	///< @return The alignment.	
	
	EntryCompletion* get_completion() const;
	///< Gets the auxiliary completion object currently in use by the entry.
	///< @return The auxiliary completion object currently in use by entry.

/// @}
/// @name Methods
/// @{

	EntryCompletion* create_completion(TreeModel& model);
	///< Convenience method that creates an EntryCompletion object using the specified model
	///< and sets it to be the auxillary completion object for the entry.
	///< @param model The model for the entry completion.
	///< @return The new EntryCompletion object.
	///<
	///< The returned completion object is owned by the entry widget and should not be
	///< unreferenced. Calling this method is equivalent to creating an entry completion 
	///< yourself and calling set_completion().
	
	void set_completion(EntryCompletion *completion);
	///< Sets <EM>completion</EM> to be the auxiliary completion object to use with the entry.
	///< @param completion The EntryCompletion.
	///<
	///< All further configuration of the completion mechanism is done on
	///< <EM>completion</EM> using the Gtk::EntryCompletion API.
	
	int layout_index_to_text_index(int layout_index);
	///< Converts from a position in the entry contents (returned by get_text())
	///< to a position in the entry's PangoLayout (returned by get_layout(), with
	///< text retrieved via Pango::Layout::get_text()).
	///< @param layout_index The byte index into the entry layout text. 
	///< @return The byte index into the entry contents.
	
	int text_index_to_layout_index(int text_index);
	///< Converts from a position in the entry's Pango::Layout (returned by get_layout())
	///< to a position in the entry contents (returned by get_text()).
	///< @param text_index The byte index into the entry contents. 
	///< @return The byte index into the entry layout text.
	
	void set_visibility(bool visible);
	///< Sets whether the contents of the entry are visible or not. 
	///< @param visible <EM>true</EM> if the contents of the entry are displayed as plain text.
	///<
	///< When visibility is set to false, characters are displayed as the invisible
	///< char, and will also appear that way when the text in the entry widget is copied
	///< elsewhere. The default invisible char is the asterisk '*', but it can be changed
	///< with set_invisible_char().
	
	void set_invisible_char(G::Unichar ch);
	///< Sets the character to use in place of the actual text when set_visibility() has been
	///< called to set text visibility to false.
	///< @param ch A Unicode character.
	///<
	///< The <EM>ch</EM> character is used in "password mode" to show the user how many
	///< characters have been typed. The default invisible char is an asterisk ('*'). If
	///< you set the invisible char to 0, then the user will get no feedback at all; there
	///< will be no text on the screen as they type.
	
	void set_has_frame(bool setting);
	///< Sets whether the entry has a beveled frame around it.
	///< @param setting The new value.
	
	void set_max_length(int max);
	///< Sets the maximum allowed length of the contents of the widget. 
	///< @param max The maximum length of the entry, or 0 for no maximum.
	///<
	///< The value passed in will be clamped to the range 0-65536. If the current contents
	///< are longer than the given length, then they will be truncated to fit.

	void set_text(const char *text);
	void set_text(const String& text);
	///< Sets the text in the widget to the given value, replacing the current contents.
	///< @param text The new text.

	void set_alignment(float xalign);
	///< Sets the alignment for the contents of the entry. 
	///< @param xalign The horizontal alignment, from 0 (left) to 1 (right).
	///<	
	///< This controls the horizontal positioning of the contents when the displayed text
	///< is shorter than the width of the entry. The alignment is reversed for RTL layouts.
		
	void set_activates_default(bool setting);
	///< If setting is true, pressing Enter in the entry will activate the default widget
	///< for the window containing the entry.
	///< @param setting <EM>true</EM> to activate the default widget on Enter keypress.
	///<
	///< If setting is true, this usually means that the dialog box containing the entry
	///< will be closed, since the default widget is usually one of the dialog buttons.

	void set_width_chars(int n_chars);
	///< Changes the size request of the entry to be about the right size for n_chars characters.
	///< @param n_chars The width in chars.
	///<
	///< Note that this method changes the size request, the size can still be affected by how
	///< you pack the widget into containers. If n_chars is -1, the size reverts to the default
	///< entry size.

/// @}
/// @name Signal Proxies
/// @{

	const PopulatePopupSignalProxy signal_populate_popup();
	///< Connect to the populate_popup_signal; emitted when the Entry displays its context-sensitive menu.

	const ActviateSignalProxy signal_activate();
	///< Connect to the activate_signal; emitted when the Entry is activated by pressing the enter key.

	const InsertAtCursorSignalProxy signal_insert_at_cursor();
	///< Connect to the insert_at_cursor_signal; emitted when text is inserted into the Entry at the
	///< current cursor position.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/entry.inl>

#endif // XFC_GTK_ENTRY_HH

