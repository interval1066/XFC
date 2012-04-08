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
 
/// @file xfc/gtk/fontselection.hh
/// @brief A GtkFontSelection and GtkFontSelectionDiaog C++ wrapper interface.
///
/// Provides FontSelection, a widget that lists the available fonts, styles and sizes,
/// allowing the user to select a font, and FontSelectionDialog, a dialog box for
/// selecting fonts.

#ifndef XFC_GTK_FONT_SELECTION_HH
#define XFC_GTK_FONT_SELECTION_HH

#ifndef XFC_GTK_VBOX_HH
#include <xfc/gtk/box.hh>
#endif

#ifndef XFC_GTK_DIALOG_HH
#include <xfc/gtk/dialog.hh>
#endif

#ifndef __GTK_FONTSEL_H__
#include <gtk/gtkfontsel.h>
#endif

namespace Xfc {

namespace Pango {
class FontFace;
class FontFamily;
}

namespace Gtk {
	
class Button;
class Entry;
class Label;

/// @class FontSelection fontselection.hh xfc/gtk/fontselection.hh
/// @brief A GtkFontSelection C++ wrapper class.
///
/// The FontSelection widget lists the available fonts, styles and sizes, allowing the user
/// to select a font. It is used in the FontSelectionDialog widget to provide a dialog box
/// for selecting fonts.
///
/// To set the font which is initially selected, use set_font_name(). To get the selected font
/// use get_font_name(). To change the text which is shown in the preview area,
/// use set_preview_text().
///
/// <B>See also:</B> the <A HREF="../../howto/html/fontselection.html">Font Selection</A> HOWTO and example.

class FontSelection : public VBox
{
	friend class G::Object;

	FontSelection(const FontSelection&);
	FontSelection& operator=(const FontSelection&);
	
protected:
/// @name Constructors
/// @{

	explicit FontSelection(GtkFontSelection *font_selection, bool owns_reference = false);
	///< Construct a new FontSelection from an existing GtkFontSelection.
	///< @param font_selection A pointer to a GtkFontSelection.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>font_selection</EM> can be a newly created GtkFontSelection or an existing
	///< GtkFontSelection (see G::Object::Object).

/// @}

public:
	typedef GtkFontSelection CObjectType;

/// @name Constructors
/// @{

	FontSelection();
	///< Construct a new FontSelection.

	virtual ~FontSelection();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkFontSelection* gtk_font_selection() const;
	///< Get a pointer to the GtkFontSelection structure.

	operator GtkFontSelection* () const;
	///< Conversion operator; safely converts a FontSelection to a GtkFontSelection pointer.

	Entry* size_entry() const;
	///< Returns a pointer to the font size Entry.

	Entry* preview_entry() const;
	///< Returns a pointer to the preview text Entry.

	Pango::FontFamily* get_font_family() const;
	///< Gets the current font family.

	Pango::FontFace* get_font_face() const;
	///< Gets the current font face.

	String get_font_name() const;
	///< Gets the currently selected font name.

	String get_preview_text() const;
	///< Gets the text displayed in the preview area.

/// @}
/// @name Methods
/// @{

	bool set_font_name(const char *fontname);
	bool set_font_name(const String& fontname);
	///< Sets the currently selected font.
	///< @param fontname A fontname.
	///< @return <EM>true</EM> if the font was found.

	void set_preview_text(const char *text);
	void set_preview_text(const String& text);
	///< Sets the text displayed in the preview area.
	///< @param text The text to display in the preview area.

/// @}
};

/// @class FontSelectionDialog fontselection.hh xfc/gtk/fontselection.hh
/// @brief A GtkFontSelectionDialog C++ wrapper class.
///
/// The FontSelectionDialog widget is a dialog box for selecting a font. To set the font
/// which is initially selected, use set_font_name(). To get the selected font use 
/// get_font_name(). To change the text which is shown in the preview area, use 
/// set_preview_text().

class FontSelectionDialog : public Dialog
{
	friend class G::Object;

	FontSelectionDialog(const FontSelectionDialog&);
	FontSelectionDialog& operator=(const FontSelectionDialog&);
	
protected:
/// @name Constructors
/// @{

	explicit FontSelectionDialog(GtkFontSelectionDialog *font_selection_dialog, bool owns_reference = false);
	///< Construct a new FontSelectionDialog from an existing GtkFontSelectionDialog.
	///< @param font_selection_dialog A pointer to a GtkFontSelectionDialog.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>font_selection_dialog</EM> can be a newly created GtkFontSelectionDialog or an existing
	///< GtkFontSelectionDialog (see G::Object::Object).

/// @}
	
public:
	typedef GtkFontSelectionDialog CObjectType;

/// @name Constructors
/// @{

	FontSelectionDialog();
	///< Construct a new FontSelectionDialog with the default title.

	explicit FontSelectionDialog(const char *title);
	explicit FontSelectionDialog(const String& title);
	///< Construct a new FontSelectionDialog with the specified title.
	///< @param title The title of the dialog box.

	virtual ~FontSelectionDialog();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkFontSelectionDialog* gtk_font_selection_dialog() const;
	///< Get a pointer to the GtkFontSelectionDialog structure.

	operator GtkFontSelectionDialog* () const;
	///< Conversion operator; safely converts a FontSelectionDialog to a GtkFontSelectionDialog pointer.

	FontSelection* fontsel() const;
	///< Returns a pointer to the FontSelection widget.

	Button* ok_button() const;
	///< Gets a pointer to the "OK" button.

	Button* apply_button() const;
	///< Gets a pointer to the "Apply" button (not shown by default but you can show/hide it).

	Button* cancel_button() const;
	///< Get a pointer to the "Cancel" button.

	String get_font_name() const; 
	///< Gets the currently-selected font name or a null String if no font is selected.

	String get_preview_text() const;
	///< Gets the text displayed in the preview area.

/// @}
/// @name Methods
/// @{

	bool set_font_name(const char *fontname);
	bool set_font_name(const String& fontname);
	///< Sets the currently selected font.
	///< @param fontname A fontname.
	///< @return <EM>true</EM> if the font was found.

	void set_preview_text(const char *text);
	void set_preview_text(const String& text);
	///< Sets the text displayed in the preview area.
	///< @param text The text to display in the preview area.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/fontselection.inl>

#endif // XFC_GTK_FONT_SELECTION_HH

