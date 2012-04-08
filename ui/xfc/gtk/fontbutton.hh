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

/// @file xfc/gtk/fontbutton.hh
/// @brief A GtkFontButton C++ wrapper interface.
///
/// Provides FontButton, a button widget that launches a font selection dialog.

#ifndef XFC_GTK_FONT_BUTTON_HH
#define XFC_GTK_FONT_BUTTON_HH

#ifndef XFC_GTK_BUTTON_HH
#include <xfc/gtk/button.hh>
#endif

#ifndef __GTK_FONT_BUTTON_H__
#include <gtk/gtkfontbutton.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class FontButton fontbutton.hh xfc/gtk/fontbutton.hh
/// @brief A GtkFontButton C++ wrapper class.
///
/// The FontButton object is a button which displays the currently selected font and
/// when clicked, opens a font selection dialog to change the font. It is a suitable
/// widget for selecting a font in a preference dialog.
///
/// <B>See also:</B> the <A HREF="../../howto/html/fontselection.html">Font Selection</A> HOWTO and example.

class FontButton : public Button
{
	friend class G::Object;

	FontButton(const FontButton&);
	FontButton& operator=(const FontButton&);

protected:
/// @name Constructors
/// @{

	explicit FontButton(GtkFontButton *font_button, bool owns_reference = false);
	///< Construct a new FontButton from an existing GtkFontButton.
	///< @param font_button A pointer to a GtkFontButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>font_button</EM> can be a newly created GtkFontButton or an existing
	///< GtkFontButton (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> FontSetSignalType;
	typedef G::SignalProxy<TypeInstance, FontSetSignalType> FontSetSignalProxy;
	static const FontSetSignalType font_set_signal;
	///< Font set signal (see signal_font_set()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkFontButton CObjectType;
	
/// @name Constructors
/// @{

	FontButton();
	///< Constructs a new font picker widget.
	
	explicit FontButton(const char *fontname);
	explicit FontButton(const String& fontname);
	///< Constructs a new font picker widget.
	///< @param fontname The name of font to display in the font selection dialog.
	
	virtual ~FontButton();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkFontButton* gtk_font_button() const;
	///< Get a pointer to the GtkFontButton structure.

	operator GtkFontButton* () const;
	///< Conversion operator; safely converts an FontButton to a GtkFontButton pointer.

	String get_title() const;
	///< Retrieves the title of the font selection dialog.
	///< @return The title string.
	
	bool get_use_font() const;
	///< Determines whether the selected font is used in the label.
	///< @return Whether the selected font is used in the label. 

	bool get_use_size() const;
	///< Determines whether the selected size is used in the label.
	///< @return Whether the selected font is used in the label.
	
	String get_font_name() const;
	///< Retrieves the name of the currently selected font.
	///< @return The font name.
	
	bool get_show_style() const;
	///< Determines whether the name of the font style will be shown in the label.
	///< @return Whether the font style will be shown in the label.
	
	bool get_show_size() const;
	///< Determines whether the font size will be shown in the label.
	///< @return Whether the font size will be shown in the label. 
	
/// @}
/// @name Methods
/// @{

	void set_title(const char *title);
	void set_title(const String& title);
	///< Sets the title for the font selection dialog.
	///< @param title A string containing the font selection dialog title.
		
	void set_use_font(bool use_font);
	///< If <EM>use_font</EM> is true, the font name will be written using the selected font.
	///< @param use_font If true, the font name will be written using the font chosen.
	
	void set_use_size(bool use_size);
	///< If <EM>use_size</EM> is true, the font name will be written using the selected size.
	///< @param use_size If true, then font name will be written using the selected size.
	
	bool set_font_name(const char *fontname);
	bool set_font_name(const String& fontname);
	///< Sets or updates the currently displayed font in font picker dialog.
	///< @param fontname The name of the font to display in font selection dialog. 
	///< @return <EM>true</EM> if the font was found, otherwise <EM>false</EM>.

	void set_show_style(bool show_style);
	///< If <EM>show_style</EM> is true the font style will be displayed along with
	///< the name of the selected font.
	///< @param show_style Set <EM>true</EM> if the font style should be displayed in the label.
	
	void set_show_size(bool show_size);
	///< If <EM>show_size</EM> is true, the font size will be displayed
	///< along with the name of the selected font.
	///< @param show_size Set <EM>true</EM> if the font size should be displayed in dialog.

/// @}
/// @name Signal Proxies
/// @{

	const FontSetSignalProxy signal_font_set();
	///< Connect to the font_set_signal; emitted when the user selects a font. When handling
	///< this signal, use get_font_name() to find out which font was just selected.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/fontbutton.inl>

#endif // XFC_GTK_FONT_BUTTON_HH

