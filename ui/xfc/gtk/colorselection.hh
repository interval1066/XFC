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
 
/// @file xfc/gtk/colorselection.hh
/// @brief A GtkColorSelection and GtkColorSelectionDialog C++ wrapper interface.
///
/// Provides ColorSelection, a widget that is used to select a color,
/// and ColorSelectionDialog, a standard dialog that allows the user
/// to select a color much like the FileSelection provides a standard
/// dialog for file selection.

#ifndef XFC_GTK_COLOR_SELECTION_HH
#define XFC_GTK_COLOR_SELECTION_HH

#ifndef XFC_GTK_VBOX_HH
#include <xfc/gtk/box.hh>
#endif

#ifndef XFC_GTK_DIALOG_HH
#include <xfc/gtk/dialog.hh>
#endif

#ifndef __GTK_COLOR_SELECTION_H__
#include <gtk/gtkcolorsel.h>
#endif

#ifndef __GTK_COLOR_SELECTION_DIALOG_H__
#include <gtk/gtkcolorseldialog.h>
#endif

namespace Xfc {

namespace Gdk { 
class Color; 
}

namespace Gtk {

class Button;

/// @class ColorSelection colorselection.hh xfc/gtk/colorselection.hh
/// @brief A GtkColorSelection C++ wrapper class.
///
/// The ColorSelection is a widget that is used to select a color. It consists of a color wheel
/// and number of sliders and entry boxes for color parameters such as hue, saturation, value,
/// red, green, blue, and opacity. It is found in the standard color selection dialog box
/// ColorSelectionDialog.
///
/// <B>See also:</B> the <A HREF="../../howto/html/colorselection.html">ColorSelection</A> HOWTO and example.

class ColorSelection : public VBox
{
	friend class G::Object;

	ColorSelection(const ColorSelection&);
	ColorSelection& operator=(const ColorSelection&);
	
protected:
/// @name Constructors
/// @{
	
	explicit ColorSelection(GtkColorSelection *color_selection, bool owns_reference = false);
	///< Construct a new ColorSelection from an existing GtkColorSelection.
	///< @param color_selection A pointer to a GtkColorSelection.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>color_selection</EM> can be a newly created GtkColorSelection or an existing
	///< GtkColorSelection. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ColorChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ColorChangedSignalType> ColorChangedSignalProxy;
	static const ColorChangedSignalType color_changed_signal;
	///< Color changed signal (see signal_color_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkColorSelection CObjectType;

/// @name Constructors
/// @{

	ColorSelection();
	///< Construct a new ColorSelection.

	virtual ~ColorSelection();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkColorSelection* gtk_color_selection() const;
	///< Get a pointer to the GtkColorSelection structure.

	operator GtkColorSelection* () const;
	///< Conversion operator; safely converts a ColorSelection to a GtkColorSelection pointer.

	bool get_has_opacity_control() const;
	///< Returns true if the ColorSelection has an opacity control.

	bool get_has_palette() const;
	///< Returns true if the ColorSelection has a color palette.

	Gdk::Color get_current_color() const;
	///< Gets the currently selected color.

	unsigned short get_current_alpha() const;
	///< Returns the maximum number of palette colors.

	Gdk::Color get_previous_color() const;
	///< Retrieves the original color value.

	unsigned short get_previous_alpha() const;
	///< Returns the previous alpha value.

	bool is_adjusting() const;
	///< Returns true if the user is currently dragging a color around,
	///< and false if the selection has stopped.

/// @}
/// @name Methods
/// @{

	void set_has_opacity_control(bool has_opacity);
	///< Sets the ColorSelection to use or not use opacity.
	///< @param has_opacity <EM>true</EM> if the ColorSelection can set the opacity,
	///< <EM>false</EM> otherwise.
	
	void set_has_palette(bool has_palette);
	///< Shows and hides the palette based upon the value of has_palette.
	///< @param has_palette <EM>true</EM> if the palette is to be visible, <EM>false</EM> otherwise.

	void set_current_color(const Gdk::Color& color);
	///< Sets the current color to be color. 
	///< @param color A Gdk::Color to set the current color with.
	///<
	///< The first time this is called, it will also set the original color to be color too.

	void set_current_alpha(unsigned short alpha);
	///< Sets the current opacity to be alpha.
	///< @param alpha An integer between 0 and 65535.
	///<
	///< The first time this is called, it will also set the original opacity to be alpha too.

	void set_previous_color(const Gdk::Color& color);
	///< Sets the 'previous' color to be color. 
	///< @param color A Gdk::Color to set the previous color with.
	///<
	///< This method should be called with some hesitations, as it might seem confusing to 
	///< have that color change. Calling set_current_color() will also set this color the first
	///< time it is called.

	void set_previous_alpha(unsigned short alpha);
	///< Sets the 'previous' alpha to be alpha. 
	///< @param alpha An integer between 0 and 65535.
	///<
	///< This method should be called with some hesitations, as it might seem confusing to
	///< have that alpha change.
	
/// @}
/// @name Methods
/// @{
	static bool palette_from_string(const String& str, std::vector<Gdk::Color>& colors);
	///< Parses a color palette string; the string is a colon-separated list of color names
	///< readable by Gdk::Color::parse().
	///< @param str A String encoding a color palette.
	///< @param colors A vector of Gdk::Color to fill with the newly allocated colors.
	///< @return <EM>true</EM> if a palette was successfully parsed.

	static String palette_to_string(const std::vector<Gdk::Color>& colors);
	///< Encodes a palette as a string, useful for persistent storage.
	///< @param colors A vector of Gdk::Color objects.
	///< @return A String encoding the palette.

/// @}
/// @name Signal Proxies
/// @{

	const ColorChangedSignalProxy signal_color_changed();
	///< Connect to the color_changed_signal; emitted when the color changes in the
	///< ColorSelection according to its update policy.

/// @}
};

/// @class ColorSelectionDialog colorselection.hh xfc/gtk/colorselection.hh
/// @brief A GtkColorSelectionDialog C++ wrapper class.
/// 
/// The ColorSelectionDialog provides a standard dialog which allows the user to select a
/// color much like the FileSelection provides a standard dialog for file selection.

class ColorSelectionDialog : public Dialog
{
	friend class G::Object;

	ColorSelectionDialog(const ColorSelectionDialog&);
	ColorSelectionDialog& operator=(const ColorSelectionDialog&);
	
protected:
/// @name Constructors
/// @{

	explicit ColorSelectionDialog(GtkColorSelectionDialog *color_selection_dialog, bool owns_reference = false);
	///< Construct a new ColorSelectionDialog from an existing GtkColorSelectionDialog.
	///< @param color_selection_dialog A pointer to a GtkColorSelectionDialog.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>color_selection_dialog</EM> can be a newly created GtkColorSelectionDialog
	///< or an existing GtkColorSelectionDialog. (see G::Object::Object).

/// @}
	
public:
	typedef GtkColorSelectionDialog CObjectType;

/// @name Constructors
/// @{

	ColorSelectionDialog();
	///< Construct a new ColorSelectionDialog with the default title.

	explicit ColorSelectionDialog(const char *title);
	explicit ColorSelectionDialog(const String& title);
	///< Construct a new ColorSelectionDialog with the specified title.
	///< @param title A String containing the title text for the dialog.

	virtual ~ColorSelectionDialog();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkColorSelectionDialog* gtk_color_selection_dialog() const;
	///< Get a pointer to the GtkColorSelectionDialog structure.

	operator GtkColorSelectionDialog* () const;
	///< Conversion operator; safely converts a ColorSelectionDialog to a GtkColorSelectionDialog pointer.

	ColorSelection* colorsel() const;
	///< Returns the ColorSelection widget contained within the dialog.
	///< Use this widget and its get_current_color() method to gain access to the selected color.
	///< Connect a slot to this widget's color_changed_signal, to be notify when the color changes.

	Button* ok_button() const;
	///< Returns the OK button widget contained within the dialog. Connect a slot for the clicked_signal.

	Button* cancel_button() const;
	///< Returns the cancel button widget contained within the dialog. Connect a slot for the clicked_signal.

	Button* help_button() const;
	///< Returns the help button widget contained within the dialog. Connect a slot for the clicked_signal.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/colorselection.inl>

#endif // XFC_GTK_COLOR_SELECTION_HH

