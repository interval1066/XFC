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
 
/// @file xfc/gtk/dialog.hh
/// @brief A GtkDialog C++ wrapper interface.

#ifndef XFC_GTK_DIALOG_HH
#define XFC_GTK_DIALOG_HH

#ifndef XFC_GTK_WINDOW_HH
#include <xfc/gtk/window.hh>
#endif

#ifndef __GTK_DIALOG_H__
#include <gtk/gtkdialog.h>
#endif

namespace Xfc {

namespace Gdk {
class Screen;
}

namespace Gtk {
	
class Button;
class HButtonBox;
class VBox;

/// @enum DialogFlags
/// Construction/destruction flags.

enum DialogFlags
{
	DIALOG_MODAL = GTK_DIALOG_MODAL, ///< Calls Gtk::Window::set_modal(true).
	DIALOG_DESTROY_WITH_PARENT = GTK_DIALOG_DESTROY_WITH_PARENT, ///< Calls Gtk::Window::set_destroy_with_parent().
	DIALOG_NO_SEPARATOR = GTK_DIALOG_NO_SEPARATOR ///< No separator bar above the action buttons.
};

/// DialogFlagsField holds one or more flags from the Gdk::DialogFlags enumeration OR'd together.

typedef unsigned int DialogFlagsField;

/// @enum ResponseType
/// Used to indicate the response_id of the action widget.

enum ResponseType
{
	RESPONSE_NONE = GTK_RESPONSE_NONE, ///< The action widget has no response_id.
	RESPONSE_REJECT = GTK_RESPONSE_REJECT, ///< Returned only if passed as the response for the action widget.
	RESPONSE_ACCEPT = GTK_RESPONSE_ACCEPT, ///< Returned only if passed as the response for the action widget.
	RESPONSE_DELETE_EVENT = GTK_RESPONSE_DELETE_EVENT, ///< The dialog received a 'delete' event.
	RESPONSE_OK = GTK_RESPONSE_OK, ///< The OK response, when the action widget is clicked.
	RESPONSE_CANCEL = GTK_RESPONSE_CANCEL, ///< The cancel response, when the action widget is clicked.
	RESPONSE_CLOSE = GTK_RESPONSE_CLOSE, ///< The close response, when the action widget is clicked.
	RESPONSE_YES = GTK_RESPONSE_YES, ///< The yes response, when the action widget is clicked.
	RESPONSE_NO = GTK_RESPONSE_NO, ///< The no response, when the action widget is clicked.
	RESPONSE_APPLY = GTK_RESPONSE_APPLY, ///< The apply response, when the action widget is clicked.
	RESPONSE_HELP = GTK_RESPONSE_HELP ///< The help response, when the action widget is clicked.
};

/// @enum StockButtonType
/// Used to indicate a stock button and response_id to add to the dialog.

enum StockButtonType
{
	STOCK_BUTTON_OK, ///< A stock OK button that returns the id Gtk::RESPONSE_OK.	
	STOCK_BUTTON_CANCEL, ///< A stock CANCEL button that returns the id Gtk::RESPONSE_CANCEL.	
	STOCK_BUTTON_CLOSE, ///< A stock CLOSE button that returns the id Gtk::RESPONSE_CLOSE.	
	STOCK_BUTTON_YES, ///< A stock YES button that returns the id Gtk::RESPONSE_YES.	
	STOCK_BUTTON_NO, ///< A stock NO button that returns the id Gtk::RESPONSE_NO.	
	STOCK_BUTTON_APPLY, ///< A stock APPLY button that returns the id Gtk::RESPONSE_APPLY.	
	STOCK_BUTTON_HELP ///< A stock HELP button that returns the id Gtk::RESPONSE_HELP.
};

/// @class Dialog dialog.hh xfc/gtk/dialog.hh
/// @brief A GtkDialog C++ wrapper class.
///
/// Dialog boxes are a convenient way to prompt the user for a small amount of input, 
/// eg. to display a message, ask a question, or anything else that does not require
/// extensive effort on the user's part. GTK+ treats a dialog as a window split 
/// vertically. The top section is the client area (a VBox), and is where widgets such
/// as a Label or an Entry should be packed. The bottom area is known as the action area.
/// This is generally used for packing buttons into the dialog which may perform functions
/// such as cancel, ok, or apply. The two areas are separated by a HSeparator. They can be
/// accessed with client_area() and action_area(), as can be seen from the example below.
///
/// A 'modal' dialog (that is, one which freezes the rest of the application from user
/// input), can be created by calling Gtk::Window::set_modal() on the dialog. When 
/// constructing a dialog you can also pass the DIALOG_MODAL flag to make a dialog modal.
/// If you add buttons to the dialog, clicking the button will emit a signal called
/// "response" with a response ID that you specified. GTK+ will never assign a meaning
/// to positive response IDs; these are entirely user-defined. But for convenience, you
/// can use the response IDs in the ResponseType enumeration (these all have values less
/// than zero). If a dialog receives a delete event, the "response" signal will be emitted
/// with a response ID of RESPONSE_NONE.
///
/// If you want to block waiting for a dialog to return before returning control flow to
/// your code, you can call Gtk::Dialog::run(). This method enters a recursive main loop
/// and waits for the user to respond to the dialog, returning the response ID corresponding
/// to the button the user clicked. For the simple dialog in the following example, in 
/// reality, you'd probably use MessageDialog to save yourself some effort. But you'd need
/// to create the dialog contents manually if you had more than a simple message in the dialog.
///
/// <B>Example:</B> A function to open a simple dialog box displaying the message provided.
/// @code
/// void MyWindow::quick_message(const String& message)
/// {
/// 	using namespace Gtk;
///
/// 	// Creating the dialog on the stack is OK because it's only temporary. When finished, we dispose of it.
///	Dialog dialog("Message", this, DIALOG_DESTROY_WITH_PARENT, StockId::OK, RESPONSE_NONE, 0);
///
/// 	// Add a label to the dialog to display the message.
/// 	Label *label = new Label(message);
///  	dialog.client_area()->add(*label);
/// 	label->show();
///
/// 	// Run the dialog. You must call dispose(), not unref(), because the dialog is in a modal loop.
/// 	if (dialog.run())
/// 		dialog.dispose();
/// }
/// @endcode
///
/// <B>See also:</B> the <A HREF="../../howto/html/dialogs.html">Dialog</A> HOWTO.

class Dialog : public Window
{
	friend class G::Object;

	Dialog(const Dialog&);
	Dialog& operator=(const Dialog&);

protected:
/// @name Constructors
/// @{

	explicit Dialog(GtkDialog *dialog, bool owns_reference = false);
	///< Construct a new Dialog from an existing GtkDialog.
	///< @param dialog A pointer to a GtkDialog.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>dialog</EM> can be a newly created GtkDialog or an existing
	///< GtkDialog. (see G::Object::Object).

/// @}
/// @name Methods
/// @{

	void construct(const char *title, Gtk::Window *parent, Gtk::DialogFlagsField flags);
	///< Construction method that sets the title, parent and dialog flags. 
	///< @param title The dialiog box title.
	///< @param parent A pointer to the parent for the dialog box, or null for no parent.
	///< @param flags The Gdk::DialogFlags to set.
	///<
	///< This is a convenience method that can be called from dialog box constructors
	///< to set the dialog box title, parent and flags in one call. It is used internally 
	///< by Gtk::Dialog. If parent is set, the dialog is set transient for that parent.

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, int> ResponseSignalType;
	typedef G::SignalProxy<TypeInstance, ResponseSignalType> ResponseSignalProxy;
	static const ResponseSignalType response_signal;
	///< Response signal (see signal_response()). Calls a slot with the signature:
	///< @code
	///< void function(int response_id);
	///< // response_id: The response ID of the action widget.
	///< @endcode

	typedef G::Signal<void> CloseSignalType;
	typedef G::SignalProxy<TypeInstance, CloseSignalType> CloseSignalProxy;
	static const CloseSignalType close_signal;
	///< Close signal (see signal_close()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkDialog CObjectType;

/// @name Constructors
/// @{

	Dialog();
	///< Construct a new Dialog.
	///< Widgets should not be packed into this window directly, but into the client area
	///< and action area, as described above. You can add one or more buttons with add_button()
	///< or add_buttons().

	Dialog(const char *title, Window *parent = 0, DialogFlagsField flags = DIALOG_DESTROY_WITH_PARENT);
	Dialog(const String& title, Window *parent = 0, DialogFlagsField flags = DIALOG_DESTROY_WITH_PARENT);
	///< Construct a new Dialog with the specified title, parent and creation flags.
	///< @param title The title of the dialog.
	///< @param parent Transient parent of the dialog, or null.
	///< @param flags One or more Gdk::DialogFlags OR'd together.
	///<
	///< Widgets should not be packed into this window directly, but into the client area
	///< and action area, as described above. You can add one or more buttons with add_button()
	///< or add_buttons(). The flags argument can be used to make the dialog modal (DIALOG_MODAL)
	///< and/or to have it destroyed along with its transient parent (DIALOG_DESTROY_WITH_PARENT).

	virtual ~Dialog();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkDialog* gtk_dialog() const;
	///< Get a pointer to the GtkDialog structure.

	operator GtkDialog* () const;
	///< Conversion operator; safely converts a Dialog to a GtkDialog pointer.

	VBox* client_area() const;
	///< Returns the VBox which is the client area of the dialog box. You pack your widgets into
	///< this box.

	HButtonBox* action_area() const;
	///< Returns the HButtonBox which is the action area packed below the dividing HSeparator
	///< in the dialog. It is treated exactly the same as any other HButtonBox. You add your
	///< action widgets, usually buttons, to this area.

	bool get_has_separator() const;
	///< Returns true if the dialog has a separator.

/// @}
/// @name Accessors
/// @{

	static bool alternative_button_order(const Gdk::Screen *screen = 0);
	///< Determines whether dialogs are expected to use an alternative button order on <EM>screen</EM>.
	///< @param screen A Gdk::Screen, or null to use the default screen.
	///< @return <EM>true</EM> if the dialogs are expected to use an alternative button order.
	///<
	///< If you need to use this function, you should probably connect to the G::Object 
	///< "notify_signal::gtk-alternative-button-order" signal on the GtkSettings object 
	///< associated to screen, in order to be notified if the button order setting changes.
	///< See set_alternative_button_order() for more details about alternative button order.

/// @}
/// @name Methods
/// @{

	void add_action_widget(Widget& child, int response_id);
	///< Adds an activatable widget to the action area of a Dialog, connecting a signal handler
	///< that will emit the "response" signal on the dialog when the widget is activated.
	///< @param child An activatable widget.
	///< @param response_id The response ID for child.
	///<
	///< The widget is appended to the end of the dialog's action area. If you want to add
	///< a non-activatable widget, simply pack it into the action_area of the Dialog.

	Button* add_button(const char *button_text, int response_id);
	Button* add_button(const String& button_text, int response_id);
	///< Adds a button with the given text and sets things up so that clicking the button 
	///< will emit a "response" signal with the given response_id.
	///< @param button_text The text of the button.
	///< @param response_id The response ID for the button.
	///< @return The button widget that was added.
	///<
	///< The button is appended to the end of the dialog's action area. The button widget
	///< is returned, but usually you don't need it.

	Button* add_button(const StockId& stock_id, int response_id);
	///< Adds a stock button and sets things up so that clicking the button will emit a 
	///< "response" signal with the given response_id.
	///< @param stock_id The ID of the stock item.
	///< @param response_id The response ID for the button.
	///< @return The button widget that was added.
	///<
	///< The button is appended to the end of the dialog's action area. The button widget
	///< is returned, but usually you don't need it.
	
	Button* add_button(StockButtonType button_type);
	///< Adds the stock button <EM>button_type</EM> and sets things up so that clicking the
	///< button will emit a "response" signal with the associated response_id.
	///< @param button_type The Gtk::StockButtonType.
	///<
	///< The <EM>button_type</EM> specifies the stock button to add and the repsonse id
	///< to return when the stock button is clicked. This is a convenience method that is 
	///< eqivalent to calling add_button(const StockId&, int). 
	
	void set_response_sensitive(int response_id, bool setting);
	///< Calls Gtk::Widget::set_sensitive(setting) for each widget in the dialog's action area
	///< with the given response_id. 
	///< @param response_id A response ID.
	///< @param setting <EM>true</EM> for sensitive.
	///<
	///< A convenient way to sensitize/desensitize dialog buttons.
	
	void set_default_response(int response_id);
	///< Sets the last widget in the dialog's action area with the given response_id as the default
	///< widget for the dialog.
	///< @param response_id A response ID.
	///<
	///< Pressing "Enter" normally activates the default widget.

	void response(int response_id);
	///< Emits the "response" signal with the given response ID.
	///< @param response_id A response ID.
	///<
	///< Used to indicate that the user has responded to the dialog in some way; typically either
	///< you, or run() will be monitoring the "response" signal and take appropriate action.
	
	int run();
	///< Blocks in a recursive main loop until the dialog either emits the response signal, or is
	///< destroyed. 
	///< @return Response ID
	///<
	///< If the dialog is destroyed during the call to run(), run() returns RESPONSE_NONE. Otherwise,
	///< it returns the response ID from the "response" signal emission. Before entering the recursive
	///< main loop, run() calls Gtk::Widget::show() on the dialog for you. Note that you still need to
	///< show any children of the dialog yourself.
	///< 
	///< During run(), the default behavior of "delete_event" is disabled; if the dialog receives
	///< a "delete_event", it will not be destroyed as windows usually are, and run() will return
	///< RESPONSE_DELETE_EVENT. Also, during run() the dialog will be modal. You can force run()
	///< to return at any time by calling response() to emit the "response" signal. Destroying the
	///< dialog during run() is a very bad idea, because your post-run code won't know whether the
	///< dialog was destroyed or not. After run() returns, you are responsible for hiding or 
	///< destroying the dialog if you wish to do so.
	///<
	///< <B>Example:</B> Typical usage of this method might be
	///< @code
	///< int result = dialog->run();
	///< switch (result)
	///< {
	///< case RESPONSE_ACCEPT:
	///< 	do_application_specific_something();
 	///< 	break;
	///< default:
	///< 	do_nothing_since_dialog_was_cancelled();
	///< 	break;
	///< }
	///< dialog->dispose();
	///< @endcode
	
	void set_has_separator(bool setting);
	///< Sets whether the dialog has a separator above the buttons; <EM>true</EM> by default.
	///< @param setting <EM>true</EM> to have a separator.

	void set_alternative_button_order(int n_params, int *new_order);
	///< Sets an alternative button order. 
	///< @param n_params The number of response ids in <EM>new_order</EM>. 
	///< @param new_order An array of response ids of the dialog's buttons.
	///<	
	///< If the "gtk-alternative-button-order" setting is set to true, the dialog buttons
	///< are reordered according to the order of the response ids in <EM>new_order</EM>.
	///< Call this method after adding all the buttons to your dialog. 

/// @}
/// @name Signal Proxies
/// @{

	const ResponseSignalProxy signal_response();
	///< Connect to the response_signal; emmitted when an action widget is activated, the
	///< dialog receives a delete event, or the application programmer calls response().

	const CloseSignalProxy signal_close();
	///< Connect to the close_signel; emitted when the user closes the dialog box by pressing
	///< the escape key (GDK_Escape).

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/dialog.inl>

#endif // XFC_GTK_DIALOG_HH

