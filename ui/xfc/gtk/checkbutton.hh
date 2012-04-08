 /* XFC: Xfce Foundation Classes (User Interface Library)
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
 
/// @file xfc/gtk/checkbutton.hh
/// @brief A GtkCheckButton C++ wrapper interface.
///
/// Provides CheckButton, a widget with a discrete toggle button.

#ifndef XFC_GTK_CHECK_BUTTON_HH
#define XFC_GTK_CHECK_BUTTON_HH

#ifndef XFC_GTK_TOGGLE_BUTTON_HH
#include <xfc/gtk/togglebutton.hh>
#endif

#ifndef __GTK_CHECK_BUTTON_H__
#include <gtk/gtkcheckbutton.h>
#endif

namespace Xfc {

namespace Gtk {

class CheckButtonClass;

/// @class CheckButton checkbutton.hh xfc/gtk/checkbutton.hh
/// @brief A GtkCheckButton C++ wrapper class.
///
/// A CheckButton places a discrete ToggleButton next to a widget, (usually a Label). See 
/// the section on ToggleButton widgets for more information about toggle/check buttons.
/// The important signal "toggled" is also inherited from ToggleButton.
///
/// <B>See also:</B> the <A HREF="../../howto/html/buttonwidget.html">Button Widget</A> HOWTOs and examples.

class CheckButton : public ToggleButton
{
	friend class G::Object;

	CheckButton(const CheckButton&);
	CheckButton& operator=(const CheckButton&);

protected:
/// @name Constructors
/// @{

	explicit CheckButton(GtkCheckButton *check_button, bool owns_reference = false);
	///< Construct a new CheckButton from an existing GtkCheckButton.
	///< @param check_button A pointer to a GtkCheckButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>check_button</EM> can be a newly created GtkCheckButton or an existing
	///< GtkCheckButton. (see G::Object::Object).

/// @}

public:
	typedef GtkCheckButton CObjectType;

/// @name Constructors
/// @{

	CheckButton();
	///< Construct a new CheckButton.

	explicit CheckButton(const char *label, bool use_underline = false);
	explicit CheckButton(const String& label, bool use_underline = false);
	///< Construct a new CheckButton with a Label to its right.
	///< @param label The text for the check button.
	///< @param use_underline <EM>true</EM> if the label contains an underscore, indicating a mnemonic.
	///<
	///< If <EM>use_underline</EM> is true an underscore in label indicates that the next
	///< character is the mnemonic accelerator for the checkbutton.

 	virtual ~CheckButton();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkCheckButton* gtk_check_button() const;
	///< Get a pointer to the GtkCheckButton structure.

	operator GtkCheckButton* () const;
	///< Conversion operator; safely converts a CheckButton to a GtkCheckButton pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/checkbutton.inl>

#endif // XFC_GTK_CHECK_BUTTON_HH

