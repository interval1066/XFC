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

/// @file xfc/gtk/spinbutton.hh
/// @brief A GtkSpinButton C++ wrapper interface.
///
/// Provides SpinButton, a widget that allows the user to set the value of some attribute.

#ifndef XFC_GTK_SPIN_BUTTON_HH
#define XFC_GTK_SPIN_BUTTON_HH

#ifndef XFC_GTK_ENTRY_HH
#include <xfc/gtk/entry.hh>
#endif

#ifndef __GTK_SPIN_BUTTON_H__
#include <gtk/gtkspinbutton.h>
#endif

namespace Xfc {

namespace Gtk {

/// @enum SpinType
/// SpinType defines the types of spin movement that can occur.
/// The ammount of spin is defined by the spin buttons adjustment.

enum SpinType
{
	SPIN_STEP_FORWARD = GTK_SPIN_STEP_FORWARD, ///< Spin forward by one step value.
	SPIN_STEP_BACKWARD = GTK_SPIN_STEP_BACKWARD, ///< Spin backward by one step value.
	SPIN_PAGE_FORWARD = GTK_SPIN_PAGE_FORWARD, ///< Spin forward by one page value.
	SPIN_PAGE_BACKWARD = GTK_SPIN_PAGE_BACKWARD, ///< Spin backward by one page value.
	SPIN_HOME = GTK_SPIN_HOME, ///< Spin to the minimum value.
	SPIN_END = GTK_SPIN_END, ///< Spin to maximum value.
	SPIN_USER_DEFINED = GTK_SPIN_USER_DEFINED ///< Spin by an ammount specified by the user.
};

/// @enum SpinButtonUpdatePolicy
/// SpinButtonUpdatePolicy determines how the spin button should be updated.

enum SpinButtonUpdatePolicy
{
	UPDATE_ALWAYS = GTK_UPDATE_ALWAYS, 
	///< When refreshing your SpinButton, the value is always displayed.

	UPDATE_IF_VALID = GTK_UPDATE_IF_VALID 
	///< When refreshing your SpinButton, the value is only displayed if it is valid
	///< within the bounds of the spin button's Adjustment.
};

/// @class SpinButton spinbutton.hh xfc/gtk/spinbutton.hh
/// @brief A GtkSpinButton C++ wrapper class.
///
/// A SpinButton is an ideal way to allow the user to set the value of some attribute.
/// Rather than having to directly type a number into a Entry, SpinButton allows the
/// user to click on one of two arrows to increment or decrement the displayed value.
/// A value can still be typed in, with the bonus that it can be checked to ensure it
/// is in a given range. The main properties of a SpinButton are through an Adjustment.
/// See the Adjustment section for more details about an adjustment's properties.
///
/// <B>Example 1:</B> Using a SpinButton to get an integer.
/// @code
/// #include <xfc/main.hh>
/// #include <xfc/gtk/window.hh>
/// #include <xfc/gtk/adjustment.hh>
/// #include <xfc/gtk/spinbutton.hh>
///
/// using namespace Xfc;
///
/// class Window : public Gtk::Window
/// {
/// 	Gtk::SpinButton *spinner;
/// public:
/// 	Window();
/// 	int grab_value() const;
/// };
///
/// Window::Window()
/// {
/// 	set_border_width(5);
/// 	Gtk::Adjustment *spinner_adj = new Gtk::Adjustment(50.0, 0.0, 100.0, 1.0, 5.0, 5.0);
///
/// 	// Creates the spinner, with no decimal places.
/// 	spinner = new Gtk::SpinButton(spinner_adj, 1.0, 0);
/// 	add(*spinner);
/// 	show_all();
/// }
///
/// int
/// Window::grab_value() const
/// {
/// 	return spinner->get_value_as_int();
/// }
///
/// int main (int argc, char *argv[])
/// {
/// 	using namespace Main;
///
/// 	init(&argc, &argv);
///
/// 	Window window;
/// 	window.signal_destroy().connect(slot(&Xfc::Main::quit));
///
/// 	run();
/// 	return 0;
/// }
/// @endcode
///
/// <B>Example 2:</B> Using a SpinButton to get a floating point value.
/// @code
/// #include <xfc/main.hh>
/// #include <xfc/gtk/window.hh>
/// #include <xfc/gtk/adjustment.hh>
/// #include <xfc/gtk/spinbutton.hh>
///
/// using namespace Xfc;
///
/// class Window : public Gtk::Window
/// {
/// 	Gtk::SpinButton *spinner;
/// public:
/// 	Window();
/// 	double grab_value() const;
/// };
///
/// Window::Window()
/// {
/// 	set_border_width(5);
/// 	Gtk::Adjustment *spinner_adj = new Gtk::Adjustment(2.500, 0.0, 5.0, 0.001, 0.1, 0.1);
///
/// 	// Creates the spinner, with no decimal places.
/// 	spinner = new Gtk::SpinButton(spinner_adj, 0.001, 3);
/// 	add(*spinner);
/// 	show_all();
/// }
///
/// double
/// Window::grab_value() const
/// {
/// 	return spinner->get_value();
/// }
///
/// int main (int argc, char *argv[])
/// {
/// 	using namespace Main;
///
/// 	init(&argc, &argv);
///
/// 	Window window;
/// 	window.signal_destroy().connect(slot(&Xfc::Main::quit));
///
/// 	run();
/// 	return 0;
/// }
/// @endcode
///
/// <B>See also:</B> the <A HREF="../../howto/html/spinbuttons.html">SpinButton</A> HOWTO and example.

class SpinButton : public Entry
{
	friend class G::Object;

	SpinButton(const SpinButton&);
	SpinButton& operator=(const SpinButton&);

protected:
/// @name Constructors
/// @{

	explicit SpinButton(GtkSpinButton *spin_button, bool owns_reference = false);
	///< Construct a new SpinButton from an existing GtkSpinButton.
	///< @param spin_button A pointer to a GtkSpinButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>spin_button</EM> can be a newly created GtkSpinButton or an existing
	///< GtkSpinButton (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<int, double*> InputSignalType;
	typedef G::SignalProxy<TypeInstance, InputSignalType> InputSignalProxy;
	static const InputSignalType input_signal;
	///< Input signal (see signal_input()). Calls a slot with the signature:
	///< @code
	///< int function(double *new_value);
	///< // new_value: The new value of the spin button.
	///< // return: -1 if an error occurs, otherwise 0.
	///< @endcode

	typedef G::Signal<int> OutputSignalType;
	typedef G::SignalProxy<TypeInstance, OutputSignalType> OutputSignalProxy;
	static const OutputSignalType output_signal;
	///< Output signal (see signal_output()). Calls a slot with the signature:
	///< @code
	///< int function();
	///< @endcode

	typedef G::Signal<void> ValueChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ValueChangedSignalType> ValueChangedSignalProxy;
	static const ValueChangedSignalType value_changed_signal;
	///< Value changed signal (see signal_value_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkSpinButton CObjectType;

/// @name Constructors
/// @{

	SpinButton();
	///< Construct a new spin button.

	SpinButton(Adjustment *adjustment, double climb_rate, unsigned int digits);
	///< Construct a new spin button with the specified Adjustment, climb_rate and digits.
	///< @param adjustment The Adjustment object that this spin button should use.
	///< @param climb_rate Specifies how much the spin button changes when an arrow is clicked on.
	///< @param digits The number of decimal places to display.

	SpinButton(double min, double max, double step = 1.0);
	///< Construct a new spin button without specifying an Adjustment.
	///< @param min The minimum allowable value.
	///< @param max The maximum allowable value.
	///< @param step The increment added or subtracted by spinning the widget.
	///<
	///< This is a convenience constructor that allows creation of a numeric SpinButton
	///< without manually creating an adjustment. The value is initially set to the minimum
	///< value and a page increment of 10 * step is the default. The precision of the 
	///< spinbutton is equivalent to the precision of step.

	virtual ~SpinButton();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkSpinButton* gtk_spin_button() const;
	///< Get a pointer to the GtkSpinButton structure.

	operator GtkSpinButton* () const;
	///< Conversion operator; safely converts a SpinButton to a GtkSpinButton pointer.

	Adjustment* get_adjustment() const;
	///< Get the adjustment associated with the SpinButton.

	unsigned int get_digits() const;
	///< Fetches the precision of the spin button (see set_digits()).
	///< @return The current precision.

	void get_increments(double *step, double *page) const;
	///< Gets the current step and page the increments used by the spin button (see set_increments()).
	///< @param step The location to store step increment, or null.
	///< @param page The location to store page increment, or null.

	void get_range(double *min, double *max) const;
	///< Gets the range allowed for the spin button (see set_range()).
	///< @param min The location to store minimum allowed value, or null.
	///< @param max The location to store maximum allowed value, or null.

	double get_value() const;
	///< Get the value in the spin button.
	
	int get_value_as_int() const;
	///< Get the value of the spin button represented as an integer.
	///< @return The value of the spin button.

	SpinButtonUpdatePolicy get_update_policy() const;
	///< Gets the update behavior of the spin button (see set_update_policy()).
	///< @return The current update policy.

	bool get_numeric() const;
	///< Returns whether non-numeric text can be typed into the spin button (see set_numeric()).
	///< @return <EM>true</EM> if only numeric text can be entered.

	bool get_wrap() const;
	///< Returns whether the spin button's value wraps around to the opposite limit
	///< when the upper or lower limit of the range is exceeded (see set_wrap()).
	///< @return <EM>true</EM> if the spin button wraps around.

	bool get_snap_to_ticks() const;
	///< Returns whether the values are corrected to the nearest step (see set_snap_to_ticks()).
	///< @return <EM>true</EM> if values are snapped to the nearest step.

/// @}
/// @name Methods
/// @{

	void configure(Adjustment *adjustment, double climb_rate, unsigned int digits);
	///< Changes the properties of an existing spin button.
	///< @param adjustment The new Adjustment object this spin button should use.
	///< @param climb_rate How much the spin button changes when an arrow is clicked on.
	///< @param digits The number of decimal places to display in the spin button.
	///<
	///< The adjustment, climb rate, and number of decimal places are all changed accordingly,
	///< after this function call.

	void set_adjustment(Adjustment *adjustment);
	///< Replaces the Adjustment associated with the spin button.
	///< @param adjustment An Adjustment to replace the existing adjustment.

	void set_digits(unsigned int digits);
	///< Set the precision to be displayed by the spin button.
	///< @param digits The number of digits to be displayed for the spin button's value.
	///<
	///< Up to 20 digit precision is allowed.

	void set_increments(double step, double page);
	///< Sets the step and page increments for the spin button.
	///< @param step The increment applied for a button 1 press.
	///< @param page The increment applied for a button 2 press.
	///<
	///< This affects how quickly the value changes when the spin button's arrows are activated.

	void set_range(double min, double max);
	///< Sets the minimum and maximum allowable values for the spin button.
	///< @param min The minimum allowable value.
	///< @param max The maximum allowable value.

	void set_value(double value);
	///< Set the value of the spin button.
	///< @param value The new value.

	void set_update_policy(SpinButtonUpdatePolicy policy);
	///< Sets the update behavior of the spin button. 
	///< @param policy A SpinButtonUpdatePolicy value.
	///<
	///< This determines whether the spin button is always updated or only when a valid value is set.

	void set_numeric(bool numeric);
	///< Sets the flag that determines if non-numeric text can be typed into the spin button.
	///< @param numeric <EM>true</EM> if only numeric entry is allowed.

	void spin(SpinType direction, double increment);
	///< Increment or decrement a spin button's value in a specified direction by a specified amount.
	///< @param direction A SpinType indicating the direction to spin.
	///< @param increment The step increment to apply in the specified direction.
	
	void set_wrap(bool wrap);
	///< Sets the flag that determines if a spin button value wraps around to the opposite limit
	///< when the upper or lower limit of the range is exceeded.
	///< @param wrap <EM>true</EM> if wrapping behavior is performed.

	void set_snap_to_ticks(bool snap_to_ticks);
	///< Sets the policy as to whether values are corrected to the nearest step increment
	///< when a spin button is activated after providing an invalid value.
	///< @param snap_to_ticks A flag indicating if invalid values should be corrected.

	void update();
	///< Manually force an update of the spin button.

/// @}
/// @name Signal Proxies
/// @{

	const InputSignalProxy signal_input();
	///< Connect to the input_signal; emitted when a new value is displayed in the spin button.

	const OutputSignalProxy signal_output();
	///< Connect to the output_signal; emitted to display the new value in the spin button.

	const ValueChangedSignalProxy signal_value_changed();
	///< Connect to the value_changed_signal; emitted when the value has changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/spinbutton.inl>

#endif // XFC_GTK_SPIN_BUTTON_HH

