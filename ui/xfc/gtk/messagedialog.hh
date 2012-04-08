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

/// @file xfc/gtk/messagedialog.hh
/// @brief A GtkMessageDialog C++ wrapper interface.
///
/// Provides MessageDialog, a dialog with an image representing the type of message
/// (Error, Question, etc.) alongside some message text. It's simply a convenience
/// widget; you could construct the equivalent of MessageDialog from Dialog without
/// too much effort, but MessageDialog saves typing.

#ifndef XFC_GTK_MESSAGE_DIALOG_HH
#define XFC_GTK_MESSAGE_DIALOG_HH

#ifndef XFC_GTK_DIALOG_HH
#include <xfc/gtk/dialog.hh>
#endif

#ifndef __GTK_MESSAGE_DIALOG_H__
#include <gtk/gtkmessagedialog.h>
#endif

namespace Xfc {

namespace Gtk {

class MessageDialogClass;

/// @enum MessageType
/// The type of message being displayed in the dialog.

enum MessageType
{
	MESSAGE_INFO = GTK_MESSAGE_INFO, ///< Informational message.
	MESSAGE_WARNING = GTK_MESSAGE_WARNING, ///< Nonfatal warning message.
	MESSAGE_QUESTION = GTK_MESSAGE_QUESTION, ///< Question requiring a choice.
	MESSAGE_ERROR = GTK_MESSAGE_ERROR ///< Fatal error message.
};

/// @enum ButtonType
/// Prebuilt sets of buttons for the dialog. If none of these choices are appropriate,
/// simply use BUTTONS_NONE then call Gtk::Dialog::add_buttons().

enum ButtonType
{
	BUTTONS_NONE = GTK_BUTTONS_NONE, ///< No buttons at all.
	BUTTONS_OK = GTK_BUTTONS_OK, ///< An OK button.
	BUTTONS_CLOSE = GTK_BUTTONS_CLOSE, ///< A Close button.
	BUTTONS_CANCEL = GTK_BUTTONS_CANCEL, ///< A Cancel button.
	BUTTONS_YES_NO = GTK_BUTTONS_YES_NO, ///< Yes and No buttons.
	BUTTONS_OK_CANCEL = GTK_BUTTONS_OK_CANCEL ///< OK and Cancel buttons.
};

/// @class MessageDialog messagedialog.hh xfc/gtk/messagedialog.hh
/// @brief A GtkMessageDialog C++ wrapper class.
///
/// MessageDialog presents a dialog with an image representing the type of message
/// (Error, Question, etc.) alongside some message text. It's simply a convenience
/// widget; you could construct the equivalent of MessageDialog from Dialog without
/// too much effort, but MessageDialog saves typing. The easiest way to do a modal
/// message dialog is to use Gtk::Dialog::run(), though you can also pass in the 
/// GTK_DIALOG_MODAL flag, Gtk::Dialog::run() automatically makes the dialog modal
/// and waits for the user to respond to it. Gtk::Dialog::run() returns when any
/// dialog button is clicked.
///
/// <B>Example:</B> A modal dialog.
/// @code
/// Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
/// dialog.format_message("Error loading file '%s': %s", filename.c_str(), error.message());
/// dialog.set_position(Gtk::WIN_POS_CENTER);
/// dialog.run();
/// dialog.dispose();
/// @endcode
///
/// To create a non-modal dialog you have to construct the dialog as above but instead
/// of calling Gtk::Dialog::run(), connect a callback slot to the dialog's response 
/// signal and call Gtk::Widget::show(). After handling the user's response in your
/// response singal handler, you would either call Gtk::Widget::hide() to hide the dialog
/// or call Gtk::Object::dispose() to destroy it, depending on whether you want to
/// construct the dialog each time, or use the same dialog over again.
///
/// <B>See also:</B> the <A HREF="../../howto/html/messagedialog.html">MessageDialog</A> and 
/// <A HREF="../../howto/html/dialogs.html">Dialog</A> HOWTOs.

class MessageDialog : public Dialog
{
	friend class G::Object;

	MessageDialog(const MessageDialog&);
	MessageDialog& operator=(const MessageDialog&);

protected:
/// @name Constructors
/// @{

	explicit MessageDialog(GtkMessageDialog *dialog, bool owns_reference = false);
	///< Construct a new MessageDialog from an existing GtkMessageDialog.
	///< @param dialog A pointer to a GtkMessageDialog.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>dialog</EM> can be a newly created GtkMessageDialog or an existing
	///< GtkMessageDialog (see G::Object::Object).

/// @}

public:
	typedef GtkMessageDialog CObjectType;

/// @name Constructors
/// @{

	MessageDialog(Window *parent = 0, DialogFlagsField flags = DIALOG_DESTROY_WITH_PARENT);
	///< Construct a new message dialog with the specified parent and dialog flags.
	///< @param parent The transient parent, or null for none.
	///< @param flags The dialog creation flags.
	///<
	///< If you call this constructor you must call property_buttons() to set the buttons
	///< to show in the dialog. For example, property_buttons().set(Gtk::BUTTONS_CLOSE); You
	///< must also call property_message_type() to set the type of message. For example,
	///< property_message_type().set(Gtk::MESSAGE_ERROR); You must call set_message() to
	///< set the message text.

	MessageDialog(MessageType type, ButtonType buttons, Window *parent = 0, DialogFlagsField flags = DIALOG_DESTROY_WITH_PARENT);
	///< Constructs a new message dialog, which is a simple dialog with an icon indicating
	///< the dialog type (error, warning, etc).
	///< @param type The type of message.
	///< @param buttons The set of buttons to use.
	///< @param parent The transient parent, or null for none.
	///< @param flags The dialog creation flags.
	///<
	///< If you call this constructor you must call set_message() to set the message text.
	///< When the user clicks a button a "response" signal is emitted with response IDs from
	///< the Gtk::ResponseType enumeration (see Gtk::Dialog for more details).

	MessageDialog(MessageType type, ButtonType buttons, const String& message, Window *parent = 0, DialogFlagsField flags = DIALOG_DESTROY_WITH_PARENT);
	///< Constructs a new message dialog, which is a simple dialog with an icon indicating
	///< the dialog type (error, warning, etc.) and some text the user may want to see.
	///< @param type The type of message.
	///< @param buttons The set of buttons to use.
	///< @param message The message string.
	///< @param parent The transient parent, or null for none.
	///< @param flags The dialog creation flags.
	///<
	///< When the user clicks a button a "response" signal is emitted with response IDs
	///< from the Gtk::ResponseType enumeration(see Gtk::Dialog for more details).
	
	virtual ~MessageDialog();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkMessageDialog* gtk_message_dialog() const;
	///< Get a pointer to the GtkMessageDialog structure.

	operator GtkMessageDialog* () const;
	///< Conversion operator; safely converts a MessageDialog to a GtkMessageDialog pointer.

/// @}
/// @name Methods
/// @{

	void set_message(const char *message);
	void set_message(const String& message);
	///< Sets the message text displayed by the message dialog.
	///< @param message The message string.

	void format_message(const char *message_format, ...);
	///< Formats the message text displayed by the message dialog.
	///< @param message_format A printf()-style format string.
	///< @param ... The arguments for message_format.
	
	void set_markup(const char *message);
	void set_markup(const String& message);
	///< Parses <EM>message</EM> which is marked up with the Pango text markup
	///< language, setting the message text displayed based on the parse results.
	///< @param message A markup string.

	void format_markup(const char *message_format, ...);
	///< Parses <EM>message_format</EM> which is marked up with the Pango text markup
	///< language, setting the message text displayed based on the parse results.
	///< @param message_format A printf()-style format string.
	///< @param ... The arguments for message_format.

	void set_secondary_text(const char *message);
	void set_secondary_text(const String& message);
	///< Sets the secondary text of the message dialog to be <EM>message</EM>. 
	///< @param message The message string. 
	///<
	///< Note that setting a secondary text makes the primary text become bold, 
	///< unless you have provided explicit markup.
	
	void format_secondary_text(const char *message_format, ...);
	///< Sets the secondary text of the message dialog to be <EM>message_format</EM> (with printf()-style). 
	///< @param message_format printf()-style format string. 
	///< @param ... The arguments for message_format.
	///<
	///< Note that setting a secondary text makes the primary text become bold, 
	///< unless you have provided explicit markup.

	void set_secondary_markup(const char *message);
	void set_secondary_markup(const String& message);
	///< Sets the secondary text of the message dialog to be <EM>message</EM>, 
	///< which is marked up with the Pango text markup language. 
	///< @param message A markup string (see Pango markup format); 
	///<	
	///< Note that setting a secondary text makes the primary text become bold, 
	///< unless you have provided explicit markup.

	void format_secondary_markup(const char *message_format, ...);
	///< Sets the secondary text of the message dialog to be <EM>message_format</EM>
	///< (with printf()-style), which is marked up with the Pango text markup language. 
	///< @param message_format A printf()-style markup string (see Pango markup format). 
	///< @param ... The arguments for message_format.
	///<	
	///< Note that setting a secondary text makes the primary text become bold, 
	///< unless you have provided explicit markup.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/messagedialog.inl>

#endif // XFC_GTK_MESSAGE_DIALOG_HH

