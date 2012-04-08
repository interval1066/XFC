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
 
/// @file xfc/gtk/button.hh
/// @brief A GtkButton C++ wrapper interface.
///
/// Provides Button, a widget which is generally used to attach a function to that
/// is called when the button is pressed.

#ifndef XFC_GTK_BUTTON_HH
#define XFC_GTK_BUTTON_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_BUTTON_H__
#include <gtk/gtkbutton.h>
#endif

namespace Xfc {

namespace Gtk {

class Image;
class StockId;

/// @class Button button.hh xfc/gtk/button.hh
/// @brief A GtkButton C++ wrapper class.
///
/// The Button widget is generally used to attach a function to that is called when
/// the button is pressed. The Button widget can hold any valid child widget. That
/// is it can hold most any other standard Widget. The most commonly used child is
/// the Label.
///
/// <B>See also:</B> the <A HREF="../../howto/html/buttonwidget.html">Button Widget</A> HOWTOs and examples.

class Button : public Bin
{
	friend class G::Object;

	Button(const Button&);
	Button& operator=(const Button&);

protected:
/// @name Constructors
/// @{

	explicit Button(GtkButton *button, bool owns_reference = false);
	///< Construct a new Button from an existing GtkButton.
	///< @param button A pointer to a GtkButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>button</EM> can be a newly created GtkButton or an existing
	///< GtkButton. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> PressedSignalType;
	typedef G::SignalProxy<TypeInstance, PressedSignalType> PressedSignalProxy;
	static const PressedSignalType pressed_signal;
	///< Pressed signal (see signal_pressed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> ReleasedSignalType;
	typedef G::SignalProxy<TypeInstance, ReleasedSignalType> ReleasedSignalProxy;
	static const ReleasedSignalType released_signal;
	///< Released signal (see signal_released()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> ClickedSignalType;
	typedef G::SignalProxy<TypeInstance, ClickedSignalType> ClickedSignalProxy;
	static const ClickedSignalType clicked_signal;
	///< Clicked signal (see signal_clicked()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> EnterSignalType;
	typedef G::SignalProxy<TypeInstance, EnterSignalType> EnterSignalProxy;
	static const EnterSignalType enter_signal;
	///< Enter signal (see signal_enter()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> LeaveSignalType;
	typedef G::SignalProxy<TypeInstance, LeaveSignalType> LeaveSignalProxy;
	static const LeaveSignalType leave_signal;
	///< Leave signal (see signal_leave()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> ActivateSignalType;
	typedef G::SignalProxy<TypeInstance, ActivateSignalType> ActivateSignalProxy;
	static const ActivateSignalType activate_signal;
	///< Activate signal (see signal_activate()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkButton CObjectType;

/// @name Constructors
/// @{

	Button();
	///< Constructs an empty Button widget.

	explicit Button(Widget& image);
	///< Constructs a Button widget that contains an Image.
	///< @param image The image you want the Button to contain.

	explicit Button(const char *label, bool use_underline = false);
	explicit Button(const String& label, bool use_underline = false);
	///< Constructs a Button widget with a Label child containing the given label.
	///< @param label The text you want the Label to hold.
	///< @param use_underline Set <EM>true</EM> if label contains a mnemonic character.
	///<
	///< If characters in label are preceded by an underscore, they are underlined.
	///< If you need a literal underscore character in a label, use '__' (two underscores). 
	///< The first underlined character represents a keyboard accelerator called a mnemonic. 
	///< Pressing Alt and that key activates the button.

	Button(Widget& image, const char *label, bool use_underline = false);
	Button(Widget& image, const String& label, bool use_underline = false);
	///< Constructs a Button widget that contains an image and a label.
	///< @param image The image widget you want the button to display.
	///< @param label The text you want the button to display.
	///< @param use_underline Set <EM>true</EM> if an underline in the label indicates a mnemonic.
	///<
	///< This constructor lets you display an image and a label inside a button, like a
	///< toolbar button does. If <EM>horizontal</EM> is true the label is displayed beside the
	///< image. If <EM>horizontal</EM> is false the label is displayed underneath the image.
	
	explicit Button(const StockId& stock_id);
	///< Constructs a new Button containing the image and text from a stock item.
	///< @param stock_id The stock ID for a stock item.
	///<
	///< Some stock IDs are pre-registered like Gtk::StockId::OK and Gtk::StockId::APPLY.
	///< If stock_id is unknown, then it will be treated as a mnemonic label.

	virtual ~Button();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkButton* gtk_button() const;
	///< Get a pointer to the GtkButton structure.

	operator GtkButton* () const;
	///< Conversion operator; safely converts a Button to a GtkButton pointer.

	ReliefStyle get_relief() const;
	///< Returns the current relief style of the Button.

	String get_label() const;
	///< Fetches the text from the label of the button, as set by set_label().
	///< @return The text of the label widget.
	///<
	///< If the label text has not been set the return value will be a null String.
	///< This will be the case if you create an empty button to use as a container.

	bool get_use_underline() const;
	///< Returns true if an embedded underline in the button label indicates a mnemonic (see set_use_underline()).
	
	bool get_use_stock() const;
	///< Returns whether the button label is a stock item.
	///< @return <EM>true</EM> if the button label is used to select a stock item
	///<         instead of being used directly as the label text.

	bool get_focus_on_click() const;
	///< Determines whether the button grabs focus when it is clicked with the mouse.
	///< @return <EM>true</EM> if the button grabs focus when it is clicked with the mouse.

	void get_alignment(float *xalign, float *yalign);
	///< Gets the alignment of the child in the button.
	///< @param xalign The return location for horizontal alignment.
	///< @param yalign The return location for vertical alignment.

	Widget* get_image() const;
	///< Gets the widget that is currenty set as the image of the button.
	///< @return The image widget.
	///<	
	///< This may have been explicitly set by set_image() or constructed from as stock image.
	
/// @}
/// @name Methods
/// @{

	void pressed();
	///< Emits a Button::pressed_signal to the calling Button.

	void released();
	///< Emits a Button::released_signal to the calling Button.

	void clicked();
	///< Emits a Button::clicked_signal to the calling Button.

	void enter();
	///< Emits a Button::enter_signal to the calling Button.

	void leave();
	///< Emits a Button::leave_signal to the calling Button.

	void set_relief(ReliefStyle newstyle);
	///< Sets the relief style of the edges of the Button.
	///< @param newstyle The ReliefStyle to set.
	///<
	///< Three styles exist, RELIEF_NORMAL, RELIEF_HALF, RELIEF_NONE. The default style is,
	///< as one can guess, RELIEF_NORMAL.

	void set_label(const char *label);
	void set_label(const String& label);
	///< Sets the text of the label of the button to label.
	///< @param label A String.
	///<
	///< This method will clear any previously set label. The text is also used to select
	///< the stock item if set_use_stock() is used.

	void set_stock_id(const StockId& stock_id);
	///< Sets the button image and text from a stock item.
	///< @param stock_id The stock ID for a stock item.
	///<
	///< This is a convenience method for setting a stock item and is equivalent to
	///< calling set_label(), set_use_stock() and set_use_underline(). Some stock IDs are 
	///< pre-registered like Gtk::StockId::OK and Gtk::StockId::APPLY. If <EM>stock_id</EM>
	///< is unknown, then it will be treated as a mnemonic label.
	
	void set_use_underline(bool use_underline);
	///< Sets whether an underline in the text of the button label indicates the next character
	///< should be used for the mnemonic accelerator key.
	///< @param use_underline Set <EM>true</EM> if an underline in the text indicates a mnemonic.

	void set_use_stock(bool use_stock);
	///< Sets whether the label set on the button is used as a stock id to select
	///< the stock item for the button.
	///< @param use_stock Set <EM>true</EM> if the button should use a stock item.

	void set_image(Widget& image);
	///< Set the image of the button to the given widget. 
	///< @param image The Image you want the button to display.
	///<
	///< For this method to work the button label must be set first. 

	void set_image(Widget& image, const char *label, bool use_underline = false);
	void set_image(Widget& image, const String& label, bool use_underline = false);
	///< Set the image of the button to the given widget, and the label to <EM>label</EM>. 
	///< @param image The Image you want the button to display.
	///< @param label The text you want the button to display.
	///< @param use_underline Set <EM>true</EM> if an underline in the label indicates a mnemonic.
	
	void set_focus_on_click(bool focus_on_click);
	///< Sets whether the button will grab focus when it is clicked with the mouse.
	///< @param focus_on_click Whether the button grabs the focus when clicked with the mouse.
	///<
	///< Making mouse clicks not grab focus is useful in places like toolbars where
	///< you don't want the keyboard focus removed from the main area of the application.

	void set_alignment(float xalign, float yalign);
	///< Sets the alignment of the child.
	///< @param xalign The horizontal position of the child, 0.0 is left aligned, 1.0 is right aligned.
	///< @param yalign The vertical position of the child, 0.0 is top aligned, 1.0 is bottom aligned.
	///<
	///< This method has no effect unless the child is of type GTK_TYPE_MISC
	///< or GTK_TYPE_ALIGNMENT.

/// @}
/// @name Signal Proxies
/// @{

	const PressedSignalProxy signal_pressed();
	///< Connect to the pressed_signal; emitted when the button is initially pressed.

	const ReleasedSignalProxy signal_released();
	///< Connect to the released_signal; emitted when a button which is pressed is released,
	///< no matter where the mouse cursor is.

	const ClickedSignalProxy signal_clicked();
	///< Connect to the clicked_signal; emitted when a button clicked on by the mouse
	///< and the cursor stays on the button. If the cursor is not on the button when
	///< the mouse button is released, the signal is not emitted.

	const EnterSignalProxy signal_enter();
	///< Connect to the enter_signal; emitted when the mouse cursor enters the region of the button.

	const LeaveSignalProxy signal_leave();
	///< Connect to the leave_signal; emitted when the mouse cursor leaves the region of the button.

	const ActivateSignalProxy signal_activate();
	///< Connect to the activate_signal; emitted when the button is activated.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/button.inl>

#endif // XFC_GTK_BUTTON_HH

