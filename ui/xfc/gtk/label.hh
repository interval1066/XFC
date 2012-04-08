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
 
/// @file xfc/gtk/label.hh
/// @brief A GtkLabel C++ wrapper interface.
///
/// Provides Label, a widget that displays a small amount of text. As the name implies,
/// most labels are used to label another widget such as a Button, a MenuItem, or an
/// OptionMenu.

#ifndef XFC_GTK_LABEL_HH
#define XFC_GTK_LABEL_HH

#ifndef XFC_GTK_MISC_HH
#include <xfc/gtk/misc.hh>
#endif

#ifndef XFC_PANGO_LAYOUT_HH
#include <xfc/pango/layout.hh>
#endif

#ifndef __GTK_LABEL_H__
#include <gtk/gtklabel.h>
#endif

namespace Xfc {

namespace Gtk {

class Menu;

/// @class Label label.hh xfc/gtk/label.hh
/// @brief A GtkLabel C++ wrapper class.
///
/// The Label widget displays a small amount of text. As the name implies, most labels
/// are used to label another widget such as a Button or a MenuItem.
///
/// <B>Mnemonics</B>
///
/// Labels may contain mnemonics. Mnemonics are underlined characters in the label, used
/// for keyboard navigation. Mnemonics are created by providing a string with an underscore
/// before the mnemonic character, such as "_File". Constructors and methods that can handle
/// mnemonics have a bool argument <EM>use_underline</EM> to indicate whether or not the
/// string has a mnemonic character. 
/// 
/// Mnemonics automatically activate any activatable widget the label is inside, such as a
/// Button; if the label is not inside the mnemonic's target widget, you have to tell the
/// label about the target using Gtk::Label::set_mnemonic_widget(). Here's a simple example
/// where the label is inside a button:
/// @code
/// // Pressing Alt+H will activate this button
/// Gtk::Button *button = new Gtk::Button("_Hello", true);
/// @endcode
///
/// To create a mnemonic for a widget alongside the label, such as an Entry, you have to point
/// the label at the entry with Gtk::Label::set_mnemonic_widget():
/// @code
/// // Pressing Alt+H will activate this button
/// Gtk::Entry *entry = new Gtk::Entry;
/// Gtk::Label *label = new Gtk::Label("_Hello", true);
/// label->set_mnemonic_widget(entry);
/// @endcode
///
/// <B>Markup (styled text)</B>
///
/// To make it easy to format text in a label (changing colors, fonts, etc.), label text can be
/// provided in a simple markup format. Here's how to create a label with a small font:
/// @code
/// Gtk::Label *label = new Gtk::Label;
/// label->set_markup("<small>Small text</small>");
/// @endcode
///
/// (See complete documentation of available tags in the Pango manual.)
/// The markup passed to set_markup() must be valid; for example, literal </>/& characters must be
/// escaped as &lt;, &gt;, and &amp;. If you pass text obtained from the user, file, or a network
/// to set_markup(), you'll want to escape it with g_markup_escape_text(). Markup strings are just
/// a convenient way to set the Pango::AttrList on a label; set_attributes() may be a simpler way to
/// set attributes in some cases. Be careful though; Pango::AttrList tends to cause internationalization
/// problems, unless you're applying attributes to the entire string (i.e. unless you set the range of
/// each attribute to [0, G_MAXINT)). The reason is that specifying the start_index and end_index for
/// a Pango::Attribute requires knowledge of the exact string being displayed, so translations will cause
/// problems.
///
/// <B>Selectable labels</B>
///
/// Labels can be made selectable with Gtk::Label::set_selectable(). Selectable labels allow the user to
/// copy the label contents to the clipboard. Only labels that contain useful-to-copy information - such
/// as error messages - should be made selectable.
///
/// <B>Text layout</B>
///
/// A label can contain any number of paragraphs, but will have performance problems if it contains more
/// than a small number. Paragraphs are separated by newlines or other paragraph separators understood by
/// Pango. Labels can automatically wrap text if you call set_line_wrap(). set_justify() sets how the 
/// lines in a label align with one another. If you want to set how the label as a whole aligns in its
/// available space, see Gtk::Misc::set_alignment().
///
/// <B>See also:</B> the <A HREF="../../howto/html/label.html">Label Widget</A> HOWTO and example.

class Label : public Misc
{
	friend class G::Object;

	Label(const Label&);
	Label& operator=(const Label&);

protected:
/// @name Constructors
/// @{

	explicit Label(GtkLabel *label, bool owns_reference = false);
	///< Construct a new Label from an existing GtkLabel.
	///< @param label A pointer to a GtkLabel.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>label</EM> can be a newly created GtkLabel or an existing
	///< GtkLabel (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Menu&> PopulatePopupSignalType;
	typedef G::SignalProxy<TypeInstance, PopulatePopupSignalType> PopulatePopupSignalProxy;
	static const PopulatePopupSignalType populate_popup_signal;
	///< Populate popup signal (see signal_populate_popup()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Menu& menu);
	///< // menu: The popup menu.
	///< @endcode
	
/// @}

public:
	typedef GtkLabel CObjectType;

/// @name Constructors
/// @{

	Label();
	///< Construct an empty Label.

	explicit Label(const char *str, bool use_underline = false);
	explicit Label(const String& str, bool use_underline = false);
	///< Construct a new Label with <EM>str</EM> as its text.
	///< @param str The label text.
	///< @param use_underline Set to <EM>true</EM> if <EM>str</EM> contains a mnemonic character.
	
	virtual ~Label();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkLabel* gtk_label() const;
	///< Get a pointer to the GtkLabel structure.

	operator GtkLabel* () const;
	///< Conversion operator; safely converts a Label to a GtkLabel pointer.

	String get_text() const;
	///< Fetches the text from a label widget, as displayed on the screen.
	///< @return The text in the label widget.
	///<
	///< This does not include any embedded underlines indicating mnemonics or
	///< Pango markup (see get_label()).

	Pango::AttrList* get_attributes() const;
	///< Gets the attribute list that was set on the label using set_attributes(), if any.
	///< @return The attribute list, or null if none was set.
	///<
	///< This method does not reflect attributes that come from the label's markup (see set_markup()).
	///< If you want to get the effective attributes for the label, use get_layout()->get_attributes().

	String get_label() const;
	///< Fetches the text from a label widget including any embedded underlines
	///< indicating mnemonics and Pango markup (see get_text()).
	///< @return The text of the label widget. 
	
	bool get_use_markup() const;
	///< Returns whether the label's text is interpreted as marked up with the 
	///< Pango text markup language (see set_use_markup()).

	bool get_use_underline() const;
	///< Returns whether an embedded underline in the label indicates a mnemonic
	///< character key (see set_use_underline()).
	
	unsigned int get_mnemonic_keyval() const;
	///< If the label has been set so that it has an mnemonic key this function returns
	///< the keyval used for the mnemonic accelerator.
	/// @return The mnemonic accelerator if set, otherwise GDK_VoidSymbol.
	
	Widget* get_mnemonic_widget() const;
	///< Retrieves the target of the mnemonic (keyboard shortcut) of this label (see set_mnemonic_widget()).
	///< @return The target of the label's mnemonic, or null if none has been set.
	 
	Justification get_justify() const;
	///< Returns the justification of the label (see set_justify()).

	Pango::EllipsizeMode get_ellipsize() const;
	///< Gets the ellipsizing position of the label (see set_ellipsize()).
	///< @returns A Pango::EllipsizeMode.
	
	int get_width_chars() const;
	///< Retrieves the desired width of label, in characters (see set_width_chars()).
	///< @return The width of the label in characters.
	 
	int get_max_width_chars() const;
	///< Retrieves the desired maximum width of label, in characters (see set_width_chars()).
	///< @return The maximum width of the label in characters. 

	bool get_line_wrap() const;
	///< Returns whether lines in the label are automatically wrapped (see set_line_wrap()).

	bool get_selectable() const;
	///< Gets the value set by set_selectable().
	///< @return <EM>true</EM> if the user can copy text from the label.

	void set_angle(double angle);
	///< Sets the angle of rotation for the label. 
	///< @param angle The angle that the baseline of the label makes with the horizontal,
	///<              in degrees, measured counterclockwise. 
	///<	
	///< An angle of 90 reads from bottom to top, an angle of 270, from top to bottom. 
	///< The angle setting for the label is ignored if the label is selectable, wrapped,
	///< or ellipsized.

	double get_angle() const;
	///< Gets the angle of rotation for the label (see set_angle()).
	///< @return The angle of rotation for the label. 
	
	bool get_selection_bounds(int *start, int *end) const;
	///< Gets the selected range of characters in the label.
	///< @param start The location for start of selection, as a character offset.
	///< @param end The location for end of selection, as a character offset.
	///< @return <EM>true</EM> if there's a selection.
	
	Pango::Layout* get_layout() const;
	///< Gets the Pango::Layout used to display the label. 
	///< @return The Pango::Layout for the Label.
	///<
	///< The layout is useful to e.g. convert text positions to pixel positions, in
	///< combination with Gtk::Label::get_layout_offsets(). The returned layout is owned
	///< by the label.

	void get_layout_offsets(int *x, int *y) const;
	///< Obtains the coordinates where the label will draw the Pango::Layout representing
	///< the text in the label. 
	///< @param x The location to store X offset of layout, or null.
	///< @param y The Location to store Y offset of layout, or null.
	///<
	///< This method is useful to convert mouse events into coordinates inside the
	///< Pango::Layout, e.g. to take some action if some part of the label is clicked.
	///< Of course you will need to create an EventBox to receive the events, and pack
	///< the label inside it, since labels are a NO_WINDOW widget. Remember when using
	///< the Pango::Layout methods you need to convert to and from pixels using 
	///< PANGO_PIXELS() or PANGO_SCALE.

	bool get_single_line_mode() const;
	///< Determines whether the label is in single line mode.
	///< @return <EM>true</EM> when the label is in single line mode.
	 
/// @}
/// @name Methods
/// @{

	void set_text(const char *str);
	void set_text(const String& str);
	///< Sets the text within the Label widget, overwriting any text that was there before.
	///< @param str The text you want to set.
	///<
	///< Note this will also clear any previously set mnemonic accelerators.
	
	void set_attributes(Pango::AttrList *attrs);
	///< Sets a Pango::AttrList; the attributes in the list are applied to the label text.
	///< @param attrs A Pango::AttrList, or null to remove any previously set attributes.
	///<
	///< The attributes set with this method will be ignored if the "use_underline" property
	///< or the "use_markup" property is <EM>true</EM>.

	void set_markup(const char *str);
	void set_markup(const String& str);
	///< Parses str which is marked up with the Pango text markup language, setting the label's
	///< text and attribute list based on the parse results.
	///< @param str A markup string (see Pango markup format).

	void set_label(const char *str);
	void set_label(const String& str);
	///< Sets the text of the label. The label is interpreted as including embedded underlines
	///< and/or Pango markup depending on the values of use_underline() and use_markup().
	///< @param str The new text to set for the label.

	void set_markup_with_mnemonic(const char *str);
	void set_markup_with_mnemonic(const String& str);
	///< Parses str which is marked up with the Pango text markup language, setting the label's
	///< text and attribute list based on the parse results. 
	///< @param str A markup string (see Pango markup format).
	///<
	///< If characters in str are preceded by an underscore, they are underlined 
	///< indicating that they represent a keyboard accelerator called a mnemonic. The
	///< mnemonic key can be used to activate another widget, chosen automatically,
	///< or explicitly using Gtk::Label::set_mnemonic_widget().

	void set_mnemonic_widget(Widget *widget);
	///< If the label has been set so that it has an mnemonic key (using the constructor, 
	///< set_markup_with_mnemonic(), set_text_with_mnemonic(), or the "use_underline" property)
	///< the label can be associated with a widget that is the target of the mnemonic. 
	///< @param widget The target Widget.
	///<
	///< When the label is inside a widget (like a Button or a Notebook tab) it is
	///< automatically associated with the correct widget, but sometimes (i.e. when the
	///< target is a Entry next to the label) you need to set it explicitly using this
	///< method. The target widget will be accelerated by emitting "mnemonic_activate"
	///< on it. The default handler for this signal will activate the widget if there
	///< are no mnemonic collisions and toggle focus between the colliding widgets
	///< otherwise.

	void set_text_with_mnemonic(const char *str);
	void set_text_with_mnemonic(const String& str);
	///< Sets the label's text from the string <EM>str</EM>.
	///< @param str A string.
	///<
	///< If characters in str are preceded by an underscore, they are underlined indicatin
	///< that they represent a keyboard accelerator called a mnemonic. The mnemonic key can be
	///< used to activate another widget, chosen automatically, or explicitly using 
	///< set_mnemonic_widget().

	void set_justify(Justification jtype);
	///< Sets the alignment of the lines in the text of the label relative to each other.
	///< @param jtype A Justification.
	///< JUSTIFY_LEFT is the default value when the widget is first created. If you instead
	///< want to set the alignment of the label as a whole, use Gtk::Misc::set_alignment()
	///< instead. set_justify() has no effect on labels containing only a single line.

	void set_ellipsize(Pango::EllipsizeMode mode);
	///< Sets the mode used to ellipsize (add an ellipsis: "...") the text
	///< if there is not enough space to render the entire string.
	///< @param mode A Pango::EllipsizeMode.
	
	void set_width_chars(int n_chars);
	///< Sets the desired width in characters of label to <EM>n_chars</EM>.
	///< @param n_chars The new desired width, in characters.
	
	void set_max_width_chars(int n_chars);
	///< Sets the desired maximum width in characters of label to <EM>n_chars</EM>.
	///< @param n_chars The new desired maximum width, in characters.
	
	void set_pattern(const char *pattern);
	void set_pattern(const String& pattern);
	///< The pattern of underlines you want under the existing text within the Label widget.
	///< @param pattern The pattern string as described below.
	///<
	///< For example, if the current text of the label says "FooBarBaz" passing a pattern
	///< of "___ ___" will underline "Foo" and "Baz" but not "Bar".
	
	void set_line_wrap(bool wrap);
	///< Toggles line wrapping within the Label widget. 
	///< @param wrap The setting.
	///<
	///< If wrap is <EM>true</EM> lines are broken if text exceeds the widget's size.
	///< If wrap is <EM>false</EM> the text will get cut off by the edge of the widget if
	///< it exceeds the widget size.

	void set_selectable(bool setting);
	///< Selectable labels allow the user to select text from the label, for copy-and-paste.
	///< @param setting <EM>true</EM> to allow selecting text in the label.

	void select_region(int start_offset, int end_offset);
	///< Selects a range of characters in the label, if the label is selectable (see set_selectable()).
	///< @param start_offset The start offset (in characters not bytes).
	///< @param end_offset The end offset (in characters not bytes).
	///<
	///< If the label is not selectable, this function has no effect. If start_offset
	///< or end_offset are -1, then the end of the label will be substituted.
	
	void set_use_markup(bool setting);
	///< Sets whether the text of the label contains markup in Pango's text markup language (see set_markup()).
	///< @param setting <EM>true</EM> if the label's text should be parsed for markup.

	void set_use_underline(bool setting);
	///< If <EM>setting</EM> is true, an underline in the text indicates the next character
	///< should be used for the mnemonic accelerator key.
	///< @param setting <EM>true</EM> if underlines in the text indicate mnemonics.

	void set_single_line_mode(bool single_line_mode);
	///< Sets whether the label is in single line mode.
	///< @param single_line_mode Set to <EM>true</EM> if the label should be in single line mode.

/// @}
/// @name Signal Proxies
/// @{

	const PopulatePopupSignalProxy signal_populate_popup();
	///< Connect to the populate_popup_signal; emitted just before the popup menu is displayed in
	///< response the a right-click on a selectable label.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/label.inl>

#endif // XFC_GTK_LABEL_HH


