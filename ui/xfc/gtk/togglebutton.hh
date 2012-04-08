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
 
/// @file xfc/gtk/togglebutton.hh
/// @brief A GtkToggleButton C++ wrapper interface.
///
/// Provides ToggleButton, a Button which will remain 'pressed-in' when clicked. Clicking again
/// will cause the toggle button to return to it's normal state. 

#ifndef XFC_GTK_TOGGLE_BUTTON_HH
#define XFC_GTK_TOGGLE_BUTTON_HH

#ifndef XFC_GTK_BUTTON_HH
#include <xfc/gtk/button.hh>
#endif

#ifndef __GTK_TOGGLE_BUTTON_H__
#include <gtk/gtktogglebutton.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToggleButton togglebutton.hh xfc/gtk/togglebutton.hh
/// @brief A GtkToggleButton C++ wrapper class.
///
/// A ToggleButton is a Button which will remain 'pressed-in' when clicked. Clicking again
/// will cause the toggle button to return to it's normal state. If you create an empty
/// toggle button it is advisable to pack a widget, (such as a Label and/or a Image), into
/// the toggle button container (see GtkButton for more information).
///
/// The state of a ToggleButton can be set specifically using set_active(), and retrieved 
/// using get_active(). To simply switch the state of a toggle button, use toggled.
///
/// <B>See also:</B> the <A HREF="../../howto/html/buttonwidget.html">Button Widget</A> HOWTOs and examples.
 
class ToggleButton : public Button
{
	friend class G::Object;

	ToggleButton(const ToggleButton&);
	ToggleButton& operator=(const ToggleButton&);

protected:
/// @name Constructors
/// @{

	explicit ToggleButton(GtkToggleButton *toggle_button, bool owns_reference = false);
	///< Construct a new ToggleButton from an existing GtkToggleButton.
	///< @param toggle_button A pointer to a GtkToggleButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>toggle_button</EM> can be a newly created GtkToggleButton or an existing
	///< GtkToggleButton (see G::Object::Object).
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ToggledSignalType;
	typedef G::SignalProxy<TypeInstance, ToggledSignalType> ToggledSignalProxy;
	static const ToggledSignalType toggled_signal;
	///< Toggled signal (see signal_destroy()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkToggleButton CObjectType;

/// @name Constructors
/// @{

	ToggleButton();
	///< Constructs a new toggle button. A widget should be packed into the button,
	///< such as a Label and/or Image.
	 
	explicit ToggleButton(const char *label, bool use_underline = false);
	explicit ToggleButton(const String& label, bool use_underline = false);
	///< Constructs a new toggle button with a text label. 
	///< @param label The text you want the Label to hold.
	///< @param use_underline Set <EM>true</EM> if label contains a mnemonic character.
	///<
	///< If characters in label are preceded by an underscore, they are underlined.
	///< If you need a literal underscore character in a label, use '__' (two underscores). 
	///< The first underlined character represents a keyboard accelerator called a mnemonic. 
	///< Pressing Alt and that key activates the button.
	
	virtual ~ToggleButton();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkToggleButton* gtk_toggle_button() const;
	///< Get a pointer to the GtkToggleButton structure.
	
	operator GtkToggleButton* () const;
	///< Conversion operator; safely converts a ToggleButton to a GtkToggleButton pointer.

	bool get_active() const;
	///< Queries the toggle button and returns it's current state. 
	///< @return <EM>true</EM> if the toggle button is pressed in and <EM>false</EM> if it is raised. 

	bool get_mode() const; 
	///< Retrieves whether the button is displayed as a separate indicator and label (see set_mode()).
	///< @return <EM>true</EM> if the togglebutton is drawn as a separate indicator and label.
	
	bool get_inconsistent() const;
	///< Gets the value set by set_inconsistent().
	///< @return <EM>true</EM> if the button is displayed as inconsistent, <EM>false</EM> otherwise.
	 
/// @}
/// @name Methods
/// @{
	
	void set_mode(bool draw_indicator);
	///< Sets whether the button is displayed as a separate indicator and label.
	///< @param draw_indicator If <EM>true</EM>, draw the button as a separate indicator and label;
	///< if <EM>false</EM>, draw the button like a normal button. 
	///<	 
	///< You can call this method on a checkbutton or a radiobutton with <EM>draw_indicator</EM>
	///< set to false to make the button look like a normal button. This method only effects instances
	///< of classes like CheckButton and RadioButton that< derive from ToggleButton, not instances
	///< of ToggleButton itself.

	void set_active(bool is_active);
	///< Sets the status of the toggle button.
	///< @param is_active Either true or false.
	///<
	///< Set <EM>is_active</EM> true if you want the toggle button to be 'pressed in', and false
	///< to raise it. This action causes the <EM>toggled</EM> signal to be emitted.
	
	void set_inconsistent(bool setting);
	///< If the user has selected a range of elements (such as some text or spreadsheet cells) that
	///< are affected by a toggle button, and the current values in that range are inconsistent,
	///< you may want to display the toggle in an "in between" state. 
	///< @param setting <EM>true</EM> if the state is inconsistent.
	///<	
	///< This method turns on "in between" display. Normally you would turn off the 
	///< inconsistent state again if the user toggles the toggle button. This has to be
	///< done manually, set_inconsistent() only affects visual appearance, it doesn't 
	///< affect the semantics of the button.
	
	void toggled();
	///< Emits the toggled signal on the toggle button. 

/// @}
/// @name Signal Proxies
/// @{

	const ToggledSignalProxy signal_toggled();
	///< Connect to the toggled_signal; emitted whenever the toggle button's state is changed.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/togglebutton.inl>

#endif // XFC_GTK_TOGGLE_BUTTON_HH

