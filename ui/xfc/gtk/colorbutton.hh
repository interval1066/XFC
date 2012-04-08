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

/// @file xfc/gtk/colorbutton.hh
/// @brief A GtkColorButton C++ wrapper interface.
///
/// Provides ColorButton, a button widget that launches a color selection dialog.

#ifndef XFC_GTK_COLOR_BUTTON_HH
#define XFC_GTK_COLOR_BUTTON_HH

#ifndef XFC_GTK_BUTTON_HH
#include <xfc/gtk/button.hh>
#endif

#ifndef __GTK_COLOR_BUTTON_H__
#include <gtk/gtkcolorbutton.h>
#endif

namespace Xfc {

namespace Gdk {
class Color;
}

namespace Gtk {

/// @class ColorButton colorbutton.hh xfc/gtk/colorbutton.hh
/// @brief A GtkColorButton C++ wrapper class.
///
/// The ColorButton object is a button which displays the currently selected color
/// and when clicked, opens a color selection dialog to change the color. It is a
/// suitable widget for selecting a color in a preference dialog. 

class ColorButton : public Button
{
	friend class G::Object;

	ColorButton(const ColorButton&);
	ColorButton& operator=(const ColorButton&);

protected:
/// @name Constructors
/// @{

	explicit ColorButton(GtkColorButton *color_button, bool owns_reference = false);
	///< Construct a new ColorButton from an existing GtkColorButton.
	///< @param color_button A pointer to a GtkColorButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>color_button</EM> can be a newly created GtkColorButton or an existing
	///< GtkColorButton (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ColorSetSignalType;
	typedef G::SignalProxy<TypeInstance, ColorSetSignalType> ColorSetSignalProxy;
	static const ColorSetSignalType color_set_signal;
	///< Color set signal (see signal_color_set()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkColorButton CObjectType;

/// @name Constructors
/// @{

	ColorButton();
	///< Constructs a new color button. This widget is a small button containing a
	///< swatch representing the current selected color. When the button is clicked,
	///< a color selection dialog will open, allowing the user to select a color. 
	///< The swatch will be updated to reflect the new color when the user finishes.
	
	explicit ColorButton(const Gdk::Color& color);
	///< Constructs a new color button. 
	///< @param color A Gdk::Color to set the current color with. 

	virtual ~ColorButton();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkColorButton* gtk_color_button() const;
	///< Get a pointer to the GtkColorButton structure.

	operator GtkColorButton* () const;
	///< Conversion operator; safely converts an ColorButton to a GtkColorButton pointer.

	Gdk::Color get_color() const;
	///< Gets the current color in the color button widget.
	///< @return A Gdk::Color filled with the current color. 

	unsigned short get_alpha() const;
	///< Gets the current alpha value.
	///< @return An integer between 0 and 65535.
	
	bool get_use_alpha() const;
	///< Determines whether the color selection dialog uses the alpha channel.
	///< @return <EM>true</EM> if the color sample uses alpha channel, <EM>false</EM> if not.

	String get_title() const;
	///< Gets the title of the color selection dialog.
	///< @return A String contining the title.

/// @}
/// @name Methods
/// @{

	void set_color(const Gdk::Color& color);
	///< Sets the current color to be color.
	///< @param color A Gdk::Color to set the current color with.
	 
	void set_alpha(unsigned short alpha);
	///< Sets the current opacity to be alpha.
	///< @param alpha An integer between 0 and 65535.
				    
	void set_use_alpha(bool use_alpha);
	///< Sets whether or not the color button should use the alpha channel.
	///< @param use_alpha Set <EM>true</EM> if the button should use the alpha channel,
	///< <EM>false</EM> if not.
	
	void set_title(const char *title);
	void set_title(const String& title);
	///< Sets the title for the color selection dialog.
	///< @param title A String containing the new window title. 
	
/// @}
/// @name Signal Proxies
/// @{

	const ColorSetSignalProxy signal_color_set();
	///< Connect to the color_set_signal; emitted when the user selects a color. When handling
	///< this signal, use get_color() and get_alpha() to find out which color was just selected.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/colorbutton.inl>

#endif // XFC_GTK_COLOR_BUTTON_HH

