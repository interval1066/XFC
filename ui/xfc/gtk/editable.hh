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
 
/// @file xfc/gtk/editable.hh
/// @brief A GtkEditable C++ wrapper interface.

#ifndef XFC_GTK_EDITABLE_HH
#define XFC_GTK_EDITABLE_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __GTK_EDITABLE_H__
#include <gtk/gtkeditable.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Editable editable.hh xfc/gtk/editable.hh
/// @brief A GtkDrawingArea C++ wrapper class.
///
/// The Editable class is a base interface class for widgets editing text, such as
/// Entry. It cannot be instantiated by itself. The editable class contains methods
/// for generically manipulating an editable widget, a large number of action signals
/// used for key bindings, and several signals that an application can connect to to
/// modify the behavior of a widget.
///
/// As an example of the latter usage, by connecting the following handler to "insert_text",
/// an application can convert all entry into a widget into uppercase.
///
/// <B>Example:</B> Forcing entry to uppercase.
/// @code
/// #include <xfc/main.hh>
/// #include <xfc/core.hh>
/// #include <xfc/gtk/entry.hh>
///
/// using namespace Xfc;
///
/// class EntryWindow : public Gtk::Window
/// {
/// 	Gtk::Entry *entry;
/// 	Connection connection;
/// protected:
/// 	void on_entry_insert_text(const String& text, int* position);
/// public:
/// 	EntryWindow();
/// };
///
/// EntryWindow::EntryWindow()
/// {
/// 	set_title("Entry");
///	set_size_request(200, 100);
///
/// 	entry = new Gtk::Entry;
/// 	connection = entry->signal_insert_text().connect(slot(this, &EntryWindow::on_entry_insert_text));
/// 	entry->set_text("hello world");
/// 	entry->select_region(0, entry->gtk_entry()->text_length);
/// 	add(*entry);
/// 	entry->show();
/// }
///
/// void
/// EntryWindow::on_entry_insert_text(const String& text, int* position)
/// {
/// 	connection.block();
/// 	entry->insert_text(s.upper(), *position);
/// 	connection.unblock();
/// 	entry->stop_emission_by_name("insert_text");
/// }
///
/// int main(int argc, char *argv[])
/// {
/// 	using namespace Main;
///
/// 	init(&argc, &argv);
///
/// 	EntryWindow window;
/// 	window.signal_destroy().connect(slot(&Xfc::Main::quit));
/// 	window.show();
///
///	run();
/// 	return 0;
/// }
/// @endcode

class Editable : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	Editable();
	///< Constructs a new Editable object.	
	
	virtual ~Editable() = 0;
	///< Destructor.

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, const String&, int*> InsertTextSignalType;
	typedef G::SignalProxy<TypeInstance, InsertTextSignalType> InsertTextSignalProxy;
	static const InsertTextSignalType insert_text_signal;
	///< Insert text signal (see signal_insert_text()). Calls a slot with the signature:
	///< @code
	///< void function(const String& text, int *position);
	///< // text: The new text to insert.
	///< // position: The position at which to insert the new text.
	///< @endcode

	typedef G::Signal<void, int, int> DeleteTextSignalType;
	typedef G::SignalProxy<TypeInstance, DeleteTextSignalType> DeleteTextSignalProxy;
	static const DeleteTextSignalType delete_text_signal;
	///< Delete text signal (see signal_delete_text()). Calls a slot with the signature:
	///< @code
	///< void function(int start_pos, int end_pos);
	///< // start_pos: The starting position.
	///< // end_pos: The end position.
	///< @endcode

	typedef G::Signal<void> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;
	///< Changed signal (see signal_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
/// @name Accessors
/// @{

	GtkEditable* gtk_editable() const;
	///< Get a pointer to the GtkEditable structure.

	operator GtkEditable* () const;
	///< Conversion operator; safely converts an Editable to a GtkEditable pointer.

	bool get_selection_bounds(int *start, int *end) const;
	///< Gets the current selection bounds, if there is a selection.
	///< @param start The location to store the starting position, or null.
	///< @param end The location to store the end position, or null.
	///< @return <EM>true</EM> if there is a selection.

	String get_chars(int start_pos, int end_pos) const;
	///< Retrieves a sequence of characters. 
	///< @param start_pos The starting position.
	///< @param end_pos The end position.
	///< @return The characters in the indicated region.
	///<
	///< The characters that are retrieved are those characters at positions from start_pos up
	///< to, but not including end_pos. If end_pos is negative, then the the characters retrieved
	///< will be those characters from start_pos to the end of the text.

	int get_position() const;
	///< Retrieves the current cursor position.
	///< @return The position of the cursor. 
	///<
	///< The cursor is displayed before the character with the given (zero-based) index in the
	///< widget. The value will be less than or equal to the number of characters in the widget.
	///< Note that this position is in characters, not in bytes.

	bool get_editable() const;
	///< Retrieves whether the Editable is editable (see set_editable()).
	///< @return <EM>true</EM> if the editable is editable.

/// @}
/// @name Methods
/// @{

	void select_region(int start, int end);
	///< Selects a region of text. 
	///< @param start The starting position.
	///< @param end The end position.
	///<
	///< The characters that are selected are those characters at positions from start_pos up
	///< to, but not including end_pos. If end_pos is negative, then the the characters selected
	///< will be those characters from start_pos to the end of the text.

	void insert_text(const char *new_text, int& position);
	void insert_text(const String& new_text, int& position);
	///< Inserts text at a given position.
	///< @param new_text The text to insert.
	///< @param position An in/out parameter.
	///<
	///< The caller initializes <EM>position</EM> to the position at which to insert the text.
	///< After the call it points at the position after the newly inserted text.

	void delete_text(int start_pos, int end_pos);
	///< Deletes a sequence of characters. 
	///< @param start_pos The starting position.
	///< @param end_pos The end position.
	///<
	///< The characters that are deleted are those characters at positions from start_pos up to,
	///< but not including end_pos. If end_pos is negative, then the the characters deleted will be
	///< those characters from start_pos to the end of the text.

	void cut_clipboard();
	///< Causes the characters in the current selection to be copied to the clipboard and then
	///< deleted from the widget.

	void copy_clipboard();
	///< Causes the characters in the current selection to be copied to the clipboard.

	void paste_clipboard();
	///< Causes the contents of the clipboard to be pasted into the given widget at the current
	///< cursor position.

	void delete_selection();
	///< Deletes the current contents of the widget's selection and disclaims the selection.
	
	void set_position(int position);
	///< Sets the cursor position. 
	///< @param position The position of the cursor. 
	///<
	///< The cursor is displayed before the character with the given (zero-baseed) index in the
	///< widget. The value must be less than or equal to the number of characters in the widget. A
	///< value of -1 indicates that the position should be set after the last character in the 
	///< entry. Note that this position is in characters, not in bytes.

	void set_editable(bool is_editable);
	///< Determines if the user can edit the text in the editable widget or not.
	///< @param is_editable <EM>true</EM> if the user is allowed to edit the text in the widget.

/// @}
/// @name Signal Proxies
/// @{

	const InsertTextSignalProxy signal_insert_text();
	///< Connect to the insert_text_signal; emitted when text is inserted into the widget by the user.
	///< The default handler for this signal will normally be responsible for inserting
	///< the text, so by connecting to this signal and then stopping the signal with
	///< G::Object::stop_emission_by_name(), it is possible to modify the inserted text,
	///< or prevent it from being inserted entirely.

	const DeleteTextSignalProxy signal_delete_text();
	///< Connect to the delete_text_signal; emitted when text is deleted from the widget by the user.
	///< The default handler for this signal will normally be responsible for deleting
	///< the text, so by connecting to this signal and then stopping the signal with
	///< G::Object::stop_emission_by_name(), it is possible to modify the deleted text,
	///< or prevent it from being deleted entirely. The start_pos and end_pos parameters
	///< are interpreted as for delete_text().

	const ChangedSignalProxy signal_changed();
	///< Connect to the changed_signal; emitted when the user changes the contents of the widget.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/editable.inl>

#endif // XFC_GTK_EDITABLE_HH

