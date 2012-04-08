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
 
/// @file xfc/gtk/buttonbox.hh
/// @brief A GtkButtonBox, GtkHButtonBox and GtkVButtonBox C++ wrapper interface.
/// 
/// Provides ButtonBox, HButtonBox and VButtonBox. The primary purpose of ButtonBox
/// is to keep track of the various properties of HButtonBox and VButtonBox.

#ifndef XFC_GTK_BUTTON_BOX_HH
#define XFC_GTK_BUTTON_BOX_HH

#ifndef XFC_GTK_BOX_HH
#include <xfc/gtk/box.hh>
#endif

#ifndef __GTK_HBUTTON_BOX_H__
#include <gtk/gtkhbbox.h>
#endif

#ifndef __GTK_VBUTTON_BOX_H__
#include <gtk/gtkvbbox.h>
#endif

namespace Xfc {

namespace Gtk {

/// @enum ButtonBoxStyle
/// ButtonBoxStyle is used to dictate the style that a ButtonBox uses to layout the buttons
/// it contains. (See also: VButtonBox and HButtonBox).

enum ButtonBoxStyle
{
	BUTTONBOX_DEFAULT_STYLE = GTK_BUTTONBOX_DEFAULT_STYLE, ///< Default packing.
	BUTTONBOX_SPREAD = GTK_BUTTONBOX_SPREAD, ///< Buttons are evenly spread across the ButtonBox.
	BUTTONBOX_EDGE = GTK_BUTTONBOX_EDGE, ///< Buttons are placed at the edges of the ButtonBox.
	BUTTONBOX_START = GTK_BUTTONBOX_START, ///< Buttons are grouped towards the start of ButtonBox.
	BUTTONBOX_END = GTK_BUTTONBOX_END  ///< Buttons are grouped towards the end of ButtonBox.
};

/// @class ButtonBox buttonbox.hh xfc/gtk/buttonbox.hh
/// @brief A GtkButtonBox C++ wrapper class.
///
/// The primary purpose of ButtonBox is to keep track of the various properties of the HButtonBox and
/// VButtonBox widgets. get_child_size() retrieves the minimum width and height for widgets in a given
/// button box. set_child_size() allows those properties to be changed. The internal padding of buttons
/// can be retrieved and changed per button box using get_child_ipadding() and set_child_ipadding()
/// respectively. get_spacing() and set_spacing() retrieve and change default number of pixels between
/// buttons, respectively. get_layout() and set_layout() retrieve and alter the method used to spread
/// the buttons in a button box across the container, respectively.
///
/// <B>See also:</B> the <A HREF="../../howto/html/buttonboxes.html">ButtonBox</A> HOWTO and example.

class ButtonBox : public Box
{
	friend class G::Object;

	ButtonBox(const ButtonBox&);
	ButtonBox& operator=(const ButtonBox&);

protected:
/// @name Constructors
/// @{

	explicit ButtonBox(GtkButtonBox *button_box, bool owns_reference = false);
	///< Construct a new ButtonBox from an existing GtkButtonBox.
	///< @param button_box A pointer to a GtkButtonBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>button_box</EM> can be a newly created GtkButtonBox or an existing
	///< GtkButtonBox. (see G::Object::Object).

	virtual ~ButtonBox() = 0;
	///< Destructor.
	
/// @}

public:
	typedef GtkButtonBox CObjectType;

/// @name Accessors
/// @{

	GtkButtonBox* gtk_button_box() const;
	///< Get a pointer to the GtkButtonBox structure.

	operator GtkButtonBox* () const;
	///< Conversion operator; safely converts a ButtonBox to a GtkButtonBox pointer.

	ButtonBoxStyle get_layout() const;
	///< Retrieves the method being used to arrange the buttons in a button box. 
	/// @return The method used to layout buttons in widget.

	bool get_child_secondary(const Widget& child) const;
	///< Determines whether <EM>child</EM> should appear in a secondary group of children.
 	///< @param child A child of the button box.
	///< @return Whether <EM>child</EM> should appear in a secondary group of children.

/// @}
/// @name Methods
/// @{

	void set_layout(ButtonBoxStyle layout_style);
	///< Changes the way buttons are arranged in the button box.
	///< @param layout_style The new layout style.

	void set_child_secondary(Widget& child, bool is_secondary);
	///< Sets whether child should appear in a secondary group of children. 
	///< @param child A child of widget.
	///< @param is_secondary If <EM>true</EM>, the child appears in a secondary group.
	///<
	///< A typical use of a secondary child is the help button in a dialog. This group
	///< appears after the other children if the style is BUTTONBOX_START, BUTTONBOX_SPREAD 
	///< or BUTTONBOX_EDGE, and before the other children if the style is BUTTONBOX_END. 
	///< For horizontal button boxes, the definition of before/after depends on direction
	///< of the widget (see Gtk::Widget::set_direction()). If the style is BUTTONBOX_START
	///< or BUTTONBOX_END, then the secondary children are aligned at the other end of the
	///< button box from the main children. For the other styles, they appear immediately
	///< next to the main children.

/// @}
};

/// @class HButtonBox buttonbox.hh xfc/gtk/buttonbox.hh
/// @brief A GtkHButtonBox C++ wrapper class.
///
/// A button box should be used to provide a consistent layout of buttons throughout your application.
/// The layout/spacing can be altered by the programmer, or if desired, by the user to alter the 'feel'
/// of a program to a small degree.
///
/// Buttons are packed into a button box the same way widgets are added to any other container, using
/// Gtk::Container::add(). You can also use Gtk::Box::pack_start() or Gtk::Box::pack_end(), but for
/// button boxes both these functions work just like Gtk::Container::add(), ie., they pack the button
/// in a way that depends on the current layout style, and on whether set_child_secondary() has been
/// called on it. The spacing between buttons can be set with Gtk::Box::set_spacing(). The arrangement
/// and layout of the buttons can be changed with Gtk::ButtonBox::set_layout().
///
/// <B>See also:</B> the <A HREF="../../howto/html/buttonboxes.html">ButtonBox</A> HOWTO and example.

class HButtonBox : public ButtonBox
{
	friend class G::Object;

	HButtonBox(const HButtonBox&);
	HButtonBox& operator=(const HButtonBox&);
	
protected:
/// @name Constructors
/// @{

	explicit HButtonBox(GtkHButtonBox *hbutton_box, bool owns_reference = false);
	///< Construct a new HButtonBox from an existing GtkHButtonBox.
	///< @param hbutton_box A pointer to a GtkHButtonBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>hbutton_box</EM> can be a newly created GtkHButtonBox or an existing
	///< GtkHButtonBox. (see G::Object::Object).

/// @}
	
public:
	typedef GtkHButtonBox CObjectType;

/// @name Constructors
/// @{

	explicit HButtonBox(ButtonBoxStyle layout = BUTTONBOX_DEFAULT_STYLE, int spacing = 0);
	///< Construct a new HButtonBox with the specified layout and spacing.
	/// @param layout The way buttons are arranged in the button box.
	/// @param spacing The number of pixels to place between children of the button box.

	virtual ~HButtonBox();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkHButtonBox* gtk_hbutton_box() const;
	///< Get a pointer to the GtkHButtonBox structure.

	operator GtkHButtonBox* () const;
	///< Conversion operator; safely converts a HButtonBox to a GtkHButtonBox pointer.

/// @}
};

/// @class VButtonBox buttonbox.hh xfc/gtk/buttonbox.hh
/// @brief A GtkVButtonBox C++ wrapper class.
///
/// A button box should be used to provide a consistent layout of buttons throughout your application.
/// The layout/spacing can be altered by the programmer, or if desired, by the user to alter the 'feel'
/// of a program to a small degree.
///
/// Buttons are packed into a button box the same way widgets are added to any other container, using
/// Gtk::Container::add(). You can also use Gtk::Box::pack_start() or Gtk::Box::pack_end(), but for
/// button boxes both these functions work just like Gtk::Container::add(), ie., they pack the button
/// in a way that depends on the current layout style, and on whether set_child_secondary() has been
/// called on it. The spacing between buttons can be set with Gtk::Box::set_spacing(). The arrangement
/// and layout of the buttons can be changed with Gtk::ButtonBox::set_layout().
///
/// <B>See also:</B> the <A HREF="../../howto/html/buttonboxes.html">ButtonBox</A> HOWTO and example.

class VButtonBox : public ButtonBox
{
	friend class G::Object;

	VButtonBox(const VButtonBox&);
	VButtonBox& operator=(const VButtonBox&);
	
protected:
/// @name Constructors
/// @{
	
	explicit VButtonBox(GtkVButtonBox *vbutton_box, bool owns_reference = false);
	///< Construct a new VButtonBox from an existing GtkVButtonBox.
	///< @param vbutton_box A pointer to a GtkVButtonBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>vbutton_box</EM> can be a newly created GtkVButtonBox or an existing
	///< GtkVButtonBox. (see G::Object::Object).
	
/// @}

public:
	typedef GtkVButtonBox CObjectType;

/// @name Constructors
/// @{
	explicit VButtonBox(ButtonBoxStyle layout = BUTTONBOX_DEFAULT_STYLE, int spacing = 0);
	///< Construct a new VButtonBox with the specified layout and spacing.
	/// @param layout The way buttons are arranged in the button box.
	/// @param spacing The number of pixels to place between children of the button box.


	virtual ~VButtonBox();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkVButtonBox* gtk_vbutton_box() const;
	///< Get a pointer to the GtkVButtonBox structure.

	operator GtkVButtonBox* () const;
	///< Conversion operator; safely converts a VButtonBox to a GtkVButtonBox pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/buttonbox.inl>

#endif // XFC_GTK_BUTTON_BOX_HH

