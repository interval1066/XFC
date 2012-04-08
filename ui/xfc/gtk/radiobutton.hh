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
 
/// @file xfc/gtk/radiobutton.hh
/// @brief A GtkRadioButton C++ wrapper interface.
///
/// Provides RadioButton, a widget that is a member of a group of radio buttons
/// that gives the user a choice from many options. When one radio button is 
/// selected, all other radio buttons in the same group are deselected.

#ifndef XFC_GTK_RADIO_BUTTON_HH
#define XFC_GTK_RADIO_BUTTON_HH

#ifndef XFC_GTK_CHECK_BUTTON_HH
#include <xfc/gtk/checkbutton.hh>
#endif

#ifndef __GTK_RADIO_BUTTON_H__
#include <gtk/gtkradiobutton.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class RadioButton radiobutton.hh xfc/gtk/radiobutton.hh
/// @brief A GtkRadioButton C++ wrapper class.
///
/// A single radio button performs the same basic function as a CheckButton, as it's position
/// in the object hierarchy reflects. It is only when multiple radio buttons are grouped together
/// that they become a different user interface component in their own right. 
///
/// Every radio button is a member of some group of radio buttons. When one is selected, all other
/// radio buttons in the same group are deselected. A RadioButton is one way of giving the user a
/// choice from many options.
///
/// The first radio button in a group is constructed with one of the constructors that doesn't
/// have a group argument. These are:
/// @code
/// RadioButton();
/// RadioButton(const String& label, bool use_underline = false);
/// @endcode
///
/// Then subsequent radio buttons in the group are constructed with one of the constructors that
/// requires a group. These are:
///
/// @code
/// RadioButton(const RadioButton *group, const char *label, bool use_underline = false);
/// RadioButton(const RadioButton *group, const String& label, bool use_underline = false);
/// @endcode
///
/// The group argument is a pointer to a RadioButton that already has a group assigned to it.
/// To remove a RadioButton from one group and make it part of a new one, use set_group().
///
/// <B>Example:</B> How to create a group of three radio buttons.
///
/// @code
/// #include <xfc/main.hh>
/// #include <xfc/ui.hh>
/// #include <xfc/gtk/radiobutton.hh>
/// #include <xfc/gtk/separator.hh>
///
/// using namespace Xfc;
///
/// class RadioButtonWindow : public Gtk::Window
/// {
/// public:
/// 	RadioButtonWindow();
/// };
///
/// RadioButtonWindow::RadioButtonWindow()
/// {
/// 	set_border_width(0);
///
/// 	Gtk::VBox *box1 = new Gtk::VBox;
/// 	add(*box1);
/// 	box1->show();
///
/// 	Gtk::VBox *box2 = new Gtk::VBox(false, 10);
/// 	box2->set_border_width(10);
/// 	box1->pack_start(*box2);
/// 	box2->show();
///
///	Gtk::RadioButton *radio_button = 0;
/// 	radio_button = new Gtk::RadioButton(radio_button, "button1");
/// 	box2->pack_start(*radio_button);
/// 	radio_button->show();
///
/// 	radio_button = new Gtk::RadioButton(*radio_button, "button2");
/// 	radio_button->set_active(true);
/// 	box2->pack_start(*radio_button);
/// 	radio_button->show();
///
/// 	radio_button = new Gtk::RadioButton(*radio_button, "button3");
/// 	box2->pack_start(*radio_button);
/// 	radio_button->show();
///
/// 	Gtk::HSeparator *separator = new Gtk::HSeparator;
/// 	box1->pack_start(*separator, false);
/// 	separator->show();
///
/// 	box2 = new Gtk::VBox(false, 10);
/// 	box2->set_border_width(10);
/// 	box1->pack_start(*box2, false);
/// 	box2->show();
///
/// 	Gtk::Button *button = new Gtk::Button("close");
/// 	button->signal_clicked().connect(slot(this, &RadioButtonWindow::dispose));
/// 	box2->pack_start(*button);
/// 	button->set_flags(Gtk::CAN_DEFAULT);
/// 	button->grab_default();
/// 	button->show();
/// }
///
/// int main (int argc, char *argv[])
/// {
/// 	using namespace Main;
///
/// 	init(&argc, &argv);
///
/// 	RadioButtonWindow window;
/// 	window.signal_destroy().connect(slot(&Xfc::Main::quit));
/// 	window.show();
///
/// 	run();
/// 	return 0;
/// }
/// @endcode
///
/// <B>See also:</B> the <A HREF="../../howto/html/buttonwidget.html">Button Widget</A> HOWTOs and examples.

class RadioButton : public CheckButton
{
	friend class G::Object;

	RadioButton(const RadioButton&);
	RadioButton& operator=(const RadioButton&);

protected:
/// @name Constructors
/// @{

	explicit RadioButton(GtkRadioButton *radio_button, bool owns_reference = false);
	///< Construct a new RadioButton from an existing GtkRadioButton.
	///< @param radio_button A pointer to a GtkRadioButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>radio_button</EM> can be a newly created GtkRadioButton or an existing
	///< GtkRadioButton (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> GroupChangedSignalType;
	typedef G::SignalProxy<TypeInstance, GroupChangedSignalType> GroupChangedSignalProxy;
	static const GroupChangedSignalType group_changed_signal;
	///< Group changed signal (see signal_group_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkRadioButton CObjectType;
	
	typedef GSList Group;
	///< The radio button group.

/// @name Constructors
/// @{

	RadioButton();
	///< Construct a new radio button in a new group. To be of any practical value, 
	///< a widget should then be packed into the radio button.
	
	explicit RadioButton(const RadioButton *group);
	///< Construct a new radio button, adding it to the same group as <EM>group</EM>.
	///< @param group An existing radio button, or null for the first button in a group.
	///<
	///< To be of any practical value, a widget should then be packed into the radio button.
	
	RadioButton(const RadioButton *group, const char *label, bool use_underline = false);
	RadioButton(const RadioButton *group, const String& label, bool use_underline = false);
	///< Constructs a new radio button and adds it to the same group as <EM>group</EM>.
	///< @param group An existing radio button, or null to start a new group.
	///< @param label The text label to display next to the radio button.
	///< @param use_underline Set <EM>true</EM> if label contains a mnemonic character.

	virtual ~RadioButton();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkRadioButton* gtk_radio_button() const;
	///< Get a pointer to the GtkRadioButton structure.

	operator GtkRadioButton* () const;
	///< Conversion operator; safely converts a RadioButton to a GtkRadioButton pointer.

	Group* get_group() const;
	///< Retrieves the group assigned to the radio button.
	///< @return A linked list containing all the radio buttons in the same group as this radio button.

/// @}
/// @name Methods
/// @{

	void set_group(Group *group);
	///< Sets a radio button's group.
	///< @param group An existing radio button group, such as one returned from get_group().
	///<
	///< It should be noted that this does not change the layout of your interface in any
	///< way, so if you are changing the group, it is likely you will need to re-arrange the
	///< user interface to reflect these changes.

/// @}
/// @name Signal Proxies
/// @{

	const GroupChangedSignalProxy signal_group_changed();
	///< Connect to the group_changed_signal; emitted when the group of radio buttons that
	///< a radio button belongs to changes. This can be when a radio button switches from
	///< being alone to being part of a group of 2 or more buttons, or vice-versa, and when
	///< a button is moved from one group of 2 or more buttons to a different one, but not
	///< when the composition of the group that a button belongs to changes.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/radiobutton.inl>

#endif // XFC_GTK_RADIO_BUTTON_HH

