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

/// @file xfc/gtk/texttag.hh
/// @brief A GtkTextTag C++ wrapper interface.
///
/// Provides TextAppearance, TextAttributes and TextTag

#ifndef XFC_GTK_TEXT_TAG_HH
#define XFC_GTK_TEXT_TAG_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef XFC_PANGO_ATTRIBUTES_HH
#include <xfc/pango/attributes.hh>
#endif

#ifndef GTK_TEXT_TAG_H
#include <gtk/gtktexttag.h>
#endif

#ifndef GTK_TEXT_TAG_TABLE_H
#include <gtk/gtktexttagtable.h>
#endif

namespace Xfc {

namespace Pango {
class FontDescription;
class TabArray;
}

namespace Gdk {
class Color;
class Bitmap;
class Event;
class Pixmap;
}

namespace Gtk {

class TextIter;
class TextTagTable;

/// @class TextAppearance texttag.hh xfc/gtk/texttag.hh
/// @brief A GtkTextAppearance C++ wrapper class.
///
/// TextAppearance is used to describe the attributes of the some text. You can get
/// the text appearance attributes by calling Gtk::TextAttributes::appearance().

class TextAppearance
{
	GtkTextAppearance appearence_;

public:
/// @name Accessors
/// @{

	GtkTextAppearance* gtk_text_appearance() const;
	///< Get a pointer to the GtkTextAppearance structure.

	Gdk::Color bg_color() const;
	///< Gets the text background color.

	Gdk::Color fg_color() const;
	///< Gets the text forground color.

	Gdk::Bitmap* bg_stipple() const;
	///< Gets the text background stipple bitmap, or null if there isn't one.

	Gdk::Bitmap* fg_stipple() const;
	///< Gets the text forground stipple bitmap, or null if there isn't one.

	int rise() const;
	///< Gets the super/subscript rise, can be negative.

	Pango::Underline underline() const;
	///< Get the current pango underline value.

	bool strikethrough() const;
	///< Returns whether the text has strike through enabled.

/// @}
/// @name Methods
/// @{

	void set_colors(const Gdk::Color& fg_color, const Gdk::Color& bg_color);
	///< Set the text foreground and background colors.
	///< @param fg_color The foreground color.
	///< @param bg_color The background color.

	void set_bg_color(const Gdk::Color& color);
	///< Set the text background color.
	///< @param color The background color.

	void set_fg_color(const Gdk::Color& color);
	///< Set the text foreground color.
	///< @param color The foreground color.

	void set_stipple(const Gdk::Bitmap& fg_mask, const Gdk::Bitmap& bg_mask);
	///< Set the text foreground and background stipple bitmaps.
	///< @param fg_mask The foreground bitmap.
	///< @param bg_mask The background bitmap.

	void set_bg_stipple(const Gdk::Bitmap& mask);
	///< Set the text background stipple bitmap.
	///< @param mask The background bitmap.

	void set_fg_stipple(const Gdk::Bitmap& mask);
	///< Set the text foreground stipple bitmap.
	///< @param mask The foreground bitmap.

	void set_rise(int rise);
	///< Sets the super/subscript rise.
	///< @param rise The rise, can be negative.

	void set_underline(Pango::Underline underline);
	///< Sets the Pango::Underline type.
	///< @param underline One of the values from the Pango::Underline enumeration.

	void set_strikethrough(bool setting);
	///< Sets whether the text should have strike through enabled.
	///< @param setting <EM>true</EM> to enable strike through.
	
/// @}
};

/// @class TextAttributes texttag.hh xfc/gtk/texttag.hh
/// @brief A GtkTextAttributes C++ wrapper class.
///
/// TextAttributes describes a set of properties on some text. Using TextAttributes directly
/// should rarely be necessary. It's primarily useful with Gtk::TextIter::get_attributes().
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class TextAttributes : public G::Boxed
{
public:
/// @name Constructors
/// @{

	TextAttributes();
	///< Constructs a TextAttributes object with a reference count of 1 that the caller owns.

	explicit TextAttributes(GtkTextAttributes *values);
	///< Constructs a TextAttributes object from an existing GtkTextAttributes.
	///< @param values A pointer to a GtkTextAttributes.
	///<
	///< The <EM>values</EM> can be a newly created GtkTextAttributes or an existing
	///< GtkTextAttributes. The TextAttributes object created is a temporary object. It
	///< doesn't take over the ownership of GtkTextAttributes and GtkTextAttributes is 
	///< not freed by the destructor. The TextAttributes object is created with a reference
	///< count of 1 that the caller owns.

	TextAttributes(GtkTextAttributes *values, bool copy);
	///< Constructs a TextAttributes from an existing GtkTextAttributes.
	///< @param values A pointer to a GtkTextAttributes.
	///< @param copy Whether the TextAttributes object should make a copy of GtkTextAttributes or not.
	///<
	///< The <EM>values</EM> can be a newly created GtkTextAttributes or an existing
	///< GtkTextAttributes. If <EM>copy</EM> is true TextAttributes will make a copy of
	///< GtkTextAttributes. If <EM>copy</EM> is false TextAttributes wont make a copy but
	///< instead takes over the ownership of GtkTextAttributes. Either way, the destructor
	///< will free GtkTextAttributes when the TextAttributes object is destroyed. This
	///< constructor is used by G::Boxed::wrap() to wrap GtkTextAttributes objects in a
	///< C++ wrapper. The TextAttributes object is created with a reference count of 1
	///< that the caller owns.

	explicit TextAttributes(const TextAttributes& src);
	///< Copy constructor.
	///< @param src The source attributes.

	~TextAttributes();
	///< Destructor.

	TextAttributes& operator=(const TextAttributes& src);
	///< Assignment operator.
	///< @param src The source attributes.

/// @}
/// @name Accessors
/// @{

	GtkTextAttributes* gtk_text_attributes() const;
	///< Get a pointer to the GtkTextAttributes structure.

	operator GtkTextAttributes* () const;
	///< Conversion operator; safely converts a TextAttributes to a GtkTextAttributes pointer.

	TextAppearance& appearance() const;
	///< Obtains the appearance attributes of some text.

	Justification justification() const;
	///< Returns the current text justification: left, right, or center.

	TextDirection direction() const;
	///< Returns the current text direction.

	Pointer<Pango::FontDescription> font() const;
	///< Gets the font description for the some text.

	double font_scale() const;
	///< Gets the font size as a scale factor relative to the default font size.

	int left_margin() const;
	///< Gets the width of the left margin in pixels.

	int indent() const;
	///< Gets the amount to indent the paragraph, in pixels.

	int right_margin() const;
	///< Gets the width of the right margin in pixels.

	int pixels_above_lines() const;
	///< Gets the number of pixels of blank space above paragraphs.

	int pixels_below_lines() const;
	///< Gets the number of pixels of blank space below paragraphs.

	int pixels_inside_wrap() const;
	///< Gets the number of pixels of blank space between wrapped lines in a paragraph.

	Pointer<Pango::TabArray> tabs() const;
	///< Gets the custom tabs for the text.

	WrapMode wrap_mode() const;
	///< Returns the current wrap mode: never, at word boundaries, or at character boundaries.

	PangoLanguage* language() const;
	///< Gets the language the text is in, as an ISO code. Pango can use this as a hint when
	///< rendering the text. If you don't understand this parameter, you probably don't need it.

	bool invisible() const;
	///< Gets whether the text is hidden. Not implemented in GTK 2.0.

	bool bg_full_height() const;
	///< Gets whether the background color fills the entire line height or only the height
	///< of the tagged characters.

	bool editable() const;
	///< Gets whether the text can be modified by the user.

	bool realized() const;
	///< Gets whether the TextAttribute's colors have been allocated.

/// @}
/// @name Methods
/// @{

	void set_justification(Justification justification);
	///< Sets the justification of the text.
	///< @param justification One of the values from the Justification enumeration.

	void set_direction(TextDirection direction);
	///< Sets the text direction.
	///< @param direction One of the values from the TextDirection enumeration.

	void set_margins(int left_margin, int right_margin);
	///< Set the text margins.
	///< @param left_margin The width of the left margin in pixels.
	///< @param right_margin The width of the right margin in pixels.

	void set_left_margin(int margin);
	///< Set the left text margin.
	///< @param margin The width of the left margin in pixels.

	void set_right_margin(int margin);
	///< Set the right text margin.
	///< @param margin The width of the right margin in pixels.

	void set_indent(int indent);
	///< Set the paragraph indent in pixels.

	void set_pixels(int pixels_above_lines, int pixels_below_lines, int pixels_inside_wrap);
	///< Sets the amount blank space in and around a paragraph.
	///< @param pixels_above_lines The number of pixels of blank space above a paragraph.
	///< @param pixels_below_lines The number of pixels of blank space below a paragraph.
	///< @param pixels_inside_wrap The number of pixels of blank space between wrapped lines in a paragraph.

	void set_pixels_above_lines(int pixels);
	///< Sets the amount blank space above a paragraph.
	///< @param pixels The number of pixels of blank space.

	void set_pixels_below_lines(int pixels);
	///< Sets the amount blank space below a paragraph.
	///< @param pixels The number of pixels of blank space.

	void set_pixels_inside_wrap(int pixels);
	///< Sets the amount blank space between wrapped lines in a paragraph.
	///< @param pixels The number of pixels of blank space.

	void set_tab_array(Pango::TabArray& tabs);
	///< Sets the custom tabs for the text.
	///< @param tabs The array of tab stops for the text.

	void set_wrap_mode(WrapMode wrap_mode);
	///< Sets the current wrap mode: never, at word boundaries, or at character boundaries.
	///< @param wrap_mode One of the values from the WrapMode enumeration.

	void set_language(PangoLanguage *language);
	///< Sets the language the text is in, as an ISO code.
	///< @param language The Pango language code.
	///< 
	///< Pango can use this as a hint when rendering the text. If you don't understand
	///< this parameter, you probably don't need it.

	void set_invisible(bool setting);
	///< Sets whether the text is hidden.
	///< @param setting <EM>true</EM> if the text is hidden.

	void set_bg_full_height(bool setting);
	///< Sets whether the background color fills the entire line height or only the height
	///< of the tagged characters.
	///< @param setting <EM>true</EM> if the background color fills the entire line height.

	void set_editable(bool setting);
	///< Sets whether the text is editable.
	
/// @}
};

/// @class TextTag texttag.hh xfc/gtk/texttag.hh
/// @brief A GtkTextTag C++ wrapper class.
///
/// Text in a buffer can be marked with tags. A tag is an attribute that can be applied
/// to some range of text. For example, a tag might be called "bold" and make the text
/// inside the tag bold. However, the tag concept is more general than that; tags don't
/// have to affect appearance. They can instead affect the behavior of mouse and key 
/// presses, "lock" a range of text so the user can't edit it, or countless other things.
///
/// A tag is represented by a TextTag object. One TextTag can be applied to any number
/// of text ranges in any number of buffers. Each tag is stored in a TextTagTable. A tag
/// table defines a set of tags that can be used together. Each buffer has one tag table
/// associated with it; only tags from that tag table can be used with the buffer. A
/// single tag table can be shared between multiple buffers, however.
///
/// Tags can have names, which is convenient sometimes (for example, you can name your tag
/// that makes things bold "bold"), but they can also be anonymous (which is convenient if
/// you're creating tags on-the-fly).
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/textview.html">TextView Widget</A> HOWTO and example.

class TextTag : public G::Object
{
	friend class G::Object;
	friend class TextTagClass;

	TextTag(const TextTag&);
	TextTag& operator=(const TextTag&);

protected:
/// @name Constructors
/// @{

	explicit TextTag(GtkTextTag *tag, bool owns_reference = true);
	///< Construct a new TextTag from an existing GtkTextTag.
	///< @param tag A pointer to a GtkTextTag.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tag</EM> can be a newly created GtkTextTag or an existing
	///< GtkTextTag (see G::Object::Object).

/// @}
/// @name Property Prototypes
/// @{
	
	typedef G::Property<String> NamePropertyType;
	typedef G::PropertyProxy<G::Object, NamePropertyType> NamePropertyProxy;
	static const NamePropertyType name_property;
	///< The name used to refer to the text tag; null for anonymous tags (see property_name()).

	typedef G::WritableProperty<String> BackgroundPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundPropertyType> BackgroundPropertyProxy;
	static const BackgroundPropertyType background_property;
	///< The background color as a string (see property_background()).

	typedef G::Property<Pointer<Gdk::Color> > BackgroundGdkPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundGdkPropertyType> BackgroundGdkPropertyProxy;
	static const BackgroundGdkPropertyType background_gdk_property;
	///< The background color as a (possibly unallocated) Gdk::Color (see property_background_gdk()).

	typedef G::Property<bool> BackgroundFullHeightPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundFullHeightPropertyType> BackgroundFullHeightPropertyProxy;
	static const BackgroundFullHeightPropertyType background_full_height_property;
	///< Whether the background color fills the entire line height (see property_background_full_height()).

	typedef G::Property<Gdk::Bitmap*, G::Object*> BackgroundStipplePropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundStipplePropertyType> BackgroundStipplePropertyProxy;
	static const BackgroundStipplePropertyType background_stipple_property;
	///< The bitmap to use as a mask when drawing the text background (see property_background_stipple()).

	typedef G::WritableProperty<String> ForegroundPropertyType;
	typedef G::PropertyProxy<G::Object, ForegroundPropertyType> ForegroundPropertyProxy;
	static const ForegroundPropertyType foreground_property;
	///< The foreground color as a string (see property_foreground()).

	typedef G::Property<Pointer<Gdk::Color> > ForegroundGdkPropertyType;
	typedef G::PropertyProxy<G::Object, ForegroundGdkPropertyType> ForegroundGdkPropertyProxy;
	static const ForegroundGdkPropertyType foreground_gdk_property;
	///< The foreground color as a (possibly unallocated) Gdk::Color (see property_foreground_gdk()).

	typedef G::Property<Gdk::Bitmap*, G::Object*> ForegroundStipplePropertyType;
	typedef G::PropertyProxy<G::Object, ForegroundStipplePropertyType> ForegroundStipplePropertyProxy;
	static const ForegroundStipplePropertyType foreground_stipple_property;
	///< The bitmap to use as a mask when drawing the text foreground (see property_foreground_stipple()).

	typedef G::Property<TextDirection, int> DirectionPropertyType;
	typedef G::PropertyProxy<G::Object, DirectionPropertyType> DirectionPropertyProxy;
	static const DirectionPropertyType direction_property;
	///< The text direction, for example, right-to-left or left-to-right (see property_direction()).

	typedef G::Property<bool> EditablePropertyType;
	typedef G::PropertyProxy<G::Object, EditablePropertyType> EditablePropertyProxy;
	static const EditablePropertyType editable_property;
	///< Whether the text can be modified by the user (see property_editable()).

	typedef G::Property<String> FontPropertyType;
	typedef G::PropertyProxy<G::Object, FontPropertyType> FontPropertyProxy;
	static const FontPropertyType font_property;
	///< The font description as a string, e.g. "Sans Italic 12" (see property_font()).

	typedef G::Property<Pointer<Pango::FontDescription> > FontDescPropertyType;
	typedef G::PropertyProxy<G::Object, FontDescPropertyType> FontDescPropertyProxy;
	static const FontDescPropertyType font_desc_property;
	///< The font description as a Pango::FontDescription (see property_font_desc()).

	typedef G::Property<String> FamilyPropertyType;
	typedef G::PropertyProxy<G::Object, FamilyPropertyType> FamilyPropertyProxy;
	static const FamilyPropertyType family_property;
	///< The name of the font family, e.g. Sans, Helvetica, Times, Monospace (see property_family()).

	typedef G::Property<Pango::Style, int> StylePropertyType;
	typedef G::PropertyProxy<G::Object, StylePropertyType> StylePropertyProxy;
	static const StylePropertyType style_property;
	///< The font style as a Pango::Style, e.g. Pango::STYLE_ITALIC (see property_style()).

	typedef G::Property<Pango::Variant, int> VariantPropertyType;
	typedef G::PropertyProxy<G::Object, VariantPropertyType> VariantPropertyProxy;
	static const VariantPropertyType variant_property;
	///< The font variant as a Pango::Variant, e.g. Pango::VARIANT_SMALL_CAPS (see property_variant()).

	typedef G::Property<Pango::Weight, int> WeightPropertyType;
	typedef G::PropertyProxy<G::Object, WeightPropertyType> WeightPropertyProxy;
	static const WeightPropertyType weight_property;
	///< The font weight as Pango::Weight, for example, Pango::WEIGHT_BOLD (see property_weight()).

	typedef G::Property<Pango::Stretch, int> StretchPropertyType;
	typedef G::PropertyProxy<G::Object, StretchPropertyType> StretchPropertyProxy;
	static const StretchPropertyType stretch_property;
	///< The font stretch as a Pango::Stretch, e.g. Pango::STRETCH_CONDENSED (see property_stretch()).

	typedef G::Property<int> SizePropertyType;
	typedef G::PropertyProxy<G::Object, SizePropertyType> SizePropertyProxy;
	static const SizePropertyType size_property;
	///< The font size in Pango units (see property_size()).

	typedef G::Property<double> ScalePropertyType;
	typedef G::PropertyProxy<G::Object, ScalePropertyType> ScalePropertyProxy;
	static const ScalePropertyType scale_property;
	///< The font size as a scale factor relative to the default font size (see property_scale()).

	typedef G::Property<double> SizePointsPropertyType;
	typedef G::PropertyProxy<G::Object, SizePointsPropertyType> SizePointsPropertyProxy;
	static const SizePointsPropertyType size_points_property;
	///< The font size in points (see property_size_points()).

	typedef G::Property<Justification, int> JustificationPropertyType;
	typedef G::PropertyProxy<G::Object, JustificationPropertyType> JustificationPropertyProxy;
	static const JustificationPropertyType justification_property;
	///< Left, right, or center justification (see property_justification()).

	typedef G::Property<String> LanguagePropertyType;
	typedef G::PropertyProxy<G::Object, LanguagePropertyType> LanguagePropertyProxy;
	static const LanguagePropertyType language_property;
	///< The language this text is in, as an ISO code. (see property_language()).

	typedef G::Property<int> LeftMarginPropertyType;
	typedef G::PropertyProxy<G::Object, LeftMarginPropertyType> LeftMarginPropertyProxy;
	static const LeftMarginPropertyType left_margin_property;
	///< The width of the left margin in pixels (see property_left_margin()).

	typedef G::Property<int> RightMarginPropertyType;
	typedef G::PropertyProxy<G::Object, RightMarginPropertyType> RightMarginPropertyProxy;
	static const RightMarginPropertyType right_margin_property;
	///< The width of the right margin in pixels (see property_right_margin()).

	typedef G::Property<int> IndentPropertyType;
	typedef G::PropertyProxy<G::Object, IndentPropertyType> IndentPropertyProxy;
	static const IndentPropertyType indent_property;
	///< The amount to indent the paragraph, in pixels (see property_indent()).

	typedef G::Property<int> RisePropertyType;
	typedef G::PropertyProxy<G::Object, RisePropertyType> RisePropertyProxy;
	static const RisePropertyType rise_property;
	///< The offset of text above the baseline (see property_rise()).

	typedef G::Property<int> PixelsAboveLinesPropertyType;
	typedef G::PropertyProxy<G::Object, PixelsAboveLinesPropertyType> PixelsAboveLinesPropertyProxy;
	static const PixelsAboveLinesPropertyType pixels_above_lines_property;
	///< The pixels of blank space above paragraphs (see property_pixels_above_lines()).

	typedef G::Property<int> PixelsBelowLinesPropertyType;
	typedef G::PropertyProxy<G::Object, PixelsBelowLinesPropertyType> PixelsBelowLinesPropertyProxy;
	static const PixelsBelowLinesPropertyType pixels_below_lines_property;
	///< The pixels of blank space below paragraphs (see property_pixels_below_lines()).

	typedef G::Property<int> PixelsInsideWrapPropertyType;
	typedef G::PropertyProxy<G::Object, PixelsInsideWrapPropertyType> PixelsInsideWrapPropertyProxy;
	static const PixelsInsideWrapPropertyType pixels_inside_wrap_property;
	///< The pixels of blank space between wrapped lines in a paragraph (see property_pixels_inside_wrap()).

	typedef G::Property<bool> StrikethroughPropertyType;
	typedef G::PropertyProxy<G::Object, StrikethroughPropertyType> StrikethroughPropertyProxy;
	static const StrikethroughPropertyType strikethrough_property;
	///< Whether to strike through the text (see property_strikethrough()).

	typedef G::Property<Pango::Underline, int> UnderlinePropertyType;
	typedef G::PropertyProxy<G::Object, UnderlinePropertyType> UnderlinePropertyProxy;
	static const UnderlinePropertyType underline_property;
	///< The style of underline for this text (see property_underline()).

	typedef G::Property<WrapMode, int> WrapModePropertyType;
	typedef G::PropertyProxy<G::Object, WrapModePropertyType> WrapModePropertyProxy;
	static const WrapModePropertyType wrap_mode_property;
	///< Whether to wrap lines never, at word boundaries, or at character boundaries (see property_wrap_mode()).

	typedef G::Property<Pointer<Pango::TabArray> > TabsPropertyType;
	typedef G::PropertyProxy<G::Object, TabsPropertyType> TabsPropertyProxy;
	static const TabsPropertyType tabs_property;
	///< The custom tabs for this text (see property_tabs()).

	typedef G::Property<bool> InvisiblePropertyType;
	typedef G::PropertyProxy<G::Object, InvisiblePropertyType> InvisiblePropertyProxy;
	static const InvisiblePropertyType invisible_property;
	///< Whether this text is hidden (see property_invisible()).

	typedef G::Property<bool> BackgroundSetPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundSetPropertyType> BackgroundSetPropertyProxy;
	static const BackgroundSetPropertyType background_set_property;
	///< Whether this tag affects the background color (see property_background_set()).

	typedef G::Property<bool> BackgroundFullHeightSetPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundFullHeightSetPropertyType> BackgroundFullHeightSetPropertyProxy;
	static const BackgroundFullHeightSetPropertyType background_full_height_set_property;
	///< Whether this tag affects background height (see property_background_full_height_set()).

	typedef G::Property<bool> BackgroundStippleSetPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundStippleSetPropertyType> BackgroundStippleSetPropertyProxy;
	static const BackgroundStippleSetPropertyType background_stipple_set_property;
	///< Whether this tag affects the background stipple (see property_background_stipple_set()).

	typedef G::Property<bool> ForegroundSetPropertyType;
	typedef G::PropertyProxy<G::Object, ForegroundSetPropertyType> ForegroundSetPropertyProxy;
	static const ForegroundSetPropertyType foreground_set_property;
	///< Whether this tag affects the foreground color (see property_foreground_set()).

	typedef G::Property<bool> ForegroundStippleSetPropertyType;
	typedef G::PropertyProxy<G::Object, ForegroundStippleSetPropertyType> ForegroundStippleSetPropertyProxy;
	static const ForegroundStippleSetPropertyType foreground_stipple_set_property;
	///< Whether this tag affects the foreground stipple (see property_foreground_stipple_set()).

	typedef G::Property<bool> EditableSetPropertyType;
	typedef G::PropertyProxy<G::Object, EditableSetPropertyType> EditableSetPropertyProxy;
	static const EditableSetPropertyType editable_set_property;
	///< Whether this tag affects text editability (see property_editable_set()).

	typedef G::Property<bool> FamilySetPropertyType;
	typedef G::PropertyProxy<G::Object, FamilySetPropertyType> FamilySetPropertyProxy;
	static const FamilySetPropertyType family_set_property;
	///< Whether this tag affects the font family (see property_editable_set()).

	typedef G::Property<bool> StyleSetPropertyType;
	typedef G::PropertyProxy<G::Object, StyleSetPropertyType> StyleSetPropertyProxy;
	static const StyleSetPropertyType style_set_property;
	///< Whether this tag affects the font style (see property_style_set()).

	typedef G::Property<bool> VariantSetPropertyType;
	typedef G::PropertyProxy<G::Object, VariantSetPropertyType> VariantSetPropertyProxy;
	static const VariantSetPropertyType variant_set_property;
	///< Whether this tag affects the font variant (see property_variant_set()).

	typedef G::Property<bool> WeightSetPropertyType;
	typedef G::PropertyProxy<G::Object, WeightSetPropertyType> WeightSetPropertyProxy;
	static const WeightSetPropertyType weight_set_property;
	///< Whether this tag affects the font weight (see property_weight_set()).

	typedef G::Property<bool> StretchSetPropertyType;
	typedef G::PropertyProxy<G::Object, StretchSetPropertyType> StretchSetPropertyProxy;
	static const StretchSetPropertyType stretch_set_property;
	///< Whether this tag affects the font stretch (see property_stretch_set()).

	typedef G::Property<bool> SizeSetPropertyType;
	typedef G::PropertyProxy<G::Object, SizeSetPropertyType> SizeSetPropertyProxy;
	static const SizeSetPropertyType size_set_property;
	///< Whether this tag affects the font size (see property_size_set()).

	typedef G::Property<bool> ScaleSetPropertyType;
	typedef G::PropertyProxy<G::Object, ScaleSetPropertyType> ScaleSetPropertyProxy;
	static const ScaleSetPropertyType scale_set_property;
	///< Whether this tag scales the font size by a factor (see property_scale_set()).

	typedef G::Property<bool> JustificationSetPropertyType;
	typedef G::PropertyProxy<G::Object, JustificationSetPropertyType> JustificationSetPropertyProxy;
	static const JustificationSetPropertyType justification_set_property;
	///< Whether this tag affects paragraph justification (see property_justification_set()).

	typedef G::Property<bool> LanguageSetPropertyType;
	typedef G::PropertyProxy<G::Object, LanguageSetPropertyType> LanguageSetPropertyProxy;
	static const LanguageSetPropertyType language_set_property;
	///< Whether this tag affects the language the text is rendered in (see property_language_set()).

	typedef G::Property<bool> LeftMarginSetPropertyType;
	typedef G::PropertyProxy<G::Object, LeftMarginSetPropertyType> LeftMarginSetPropertyProxy;
	static const LeftMarginSetPropertyType left_margin_set_property;
	///< Whether this tag affects the left margin (see property_left_margin_set()).

	typedef G::Property<bool> IndentSetPropertyType;
	typedef G::PropertyProxy<G::Object, IndentSetPropertyType> IndentSetPropertyProxy;
	static const IndentSetPropertyType indent_set_property;
	///< Whether this tag affects indentation (see property_indent_set()).

	typedef G::Property<bool> RiseSetPropertyType;
	typedef G::PropertyProxy<G::Object, RiseSetPropertyType> RiseSetPropertyProxy;
	static const RiseSetPropertyType rise_set_property;
	///< Whether this tag affects the rise (see property_rise_set()).

	typedef G::Property<bool> PixelsAboveLinesSetPropertyType;
	typedef G::PropertyProxy<G::Object, PixelsAboveLinesSetPropertyType> PixelsAboveLinesSetPropertyProxy;
	static const PixelsAboveLinesSetPropertyType pixels_above_lines_set_property;
	///< Whether this tag affects the number of pixels above lines (see property_pixels_above_lines_set()).

	typedef G::Property<bool> PixelsBelowLinesSetPropertyType;
	typedef G::PropertyProxy<G::Object, PixelsBelowLinesSetPropertyType> PixelsBelowLinesSetPropertyProxy;
	static const PixelsBelowLinesSetPropertyType pixels_below_lines_set_property;
	///< Whether this tag affects the number of pixels below lines (see property_pixels_below_lines_set()).

	typedef G::Property<bool> PixelsInsideWrapSetPropertyType;
	typedef G::PropertyProxy<G::Object, PixelsInsideWrapSetPropertyType> PixelsInsideWrapSetPropertyProxy;
	static const PixelsInsideWrapSetPropertyType pixels_inside_wrap_set_property;
	///< Whether this tag affects the number of pixels between wrapped lines (see property_pixels_inside_wrap_set()).

	typedef G::Property<bool> StrikethroughSetPropertyType;
	typedef G::PropertyProxy<G::Object, StrikethroughSetPropertyType> StrikethroughSetPropertyProxy;
	static const StrikethroughSetPropertyType strikethrough_set_property;
	///< Whether this tag affects strikethrough (see property_strikethrough_set()).

	typedef G::Property<bool> RightMarginSetPropertyType;
	typedef G::PropertyProxy<G::Object, RightMarginSetPropertyType> RightMarginSetPropertyProxy;
	static const RightMarginSetPropertyType right_margin_set_property;
	///< Whether this tag affects the right margin (see property_right_margin_set()).

	typedef G::Property<bool> UnderlineSetPropertyType;
	typedef G::PropertyProxy<G::Object, UnderlineSetPropertyType> UnderlineSetPropertyProxy;
	static const UnderlineSetPropertyType underline_set_property;
	///< Whether this tag affects underlining (see property_underline_set()).

	typedef G::Property<bool> WrapModeSetPropertyType;
	typedef G::PropertyProxy<G::Object, WrapModeSetPropertyType> WrapModeSetPropertyProxy;
	static const WrapModeSetPropertyType wrap_mode_set_property;
	///< Whether this tag affects line wrap mode (see property_wrap_mode_set()).

	typedef G::Property<bool> TabsSetPropertyType;
	typedef G::PropertyProxy<G::Object, TabsSetPropertyType> TabsSetPropertyProxy;
	static const TabsSetPropertyType tabs_set_property;
	///< Whether this tag affects tabs (see property_tabs_set()).

	typedef G::Property<bool> InvisibleSetPropertyType;
	typedef G::PropertyProxy<G::Object, InvisibleSetPropertyType> InvisibleSetPropertyProxy;
	static const InvisibleSetPropertyType invisible_set_property;
	///< Whether this tag affects text visibility (see property_invisible_set()).
	
/// @}
/// @name Signal Prototypes
/// @{
	
	typedef G::Signal<bool, G::Object&, Gdk::Event&, const TextIter&> EventSignalType;
	typedef G::SignalProxy<TypeInstance, EventSignalType> EventSignalProxy;
	static const EventSignalType event_signal;
	///< Event signal (see signal_event()). Calls a slot with the signature:
	///< @code
	///< bool function(G::Object& event_object, Gdk::Event& event, const TextIter& iter);
	///< // event_object: The object that received the event, such as a widget.
	///< // event: The event.
	///< // iter: The location where the event was received.
	///< // return: true if the event was handled, false if it wasn't handled.
	///< @endcode
	
/// @}

public:
	typedef GtkTextTag CObjectType;

/// @name Constructors
/// @{

	TextTag();
	///< Constructs a new anonymous text tag with a reference count of 1 that the caller owns.

	explicit TextTag(const char *name);
	explicit TextTag(const String& name);
	///< Constructs a new text tag with a reference count of 1 that the caller owns.
	///< @param name The name for the text tag.

	virtual ~TextTag();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkTextTag* gtk_text_tag() const;
	///< Get a pointer to the GtkTextTag structure.

	operator GtkTextTag* () const;
	///< Conversion operator; safely converts a TextTag to a GtkTextTag pointer.

	TextTagTable* table() const;
	///< Returns the tag table for the tag.
	///< @return The tag table.

	Pointer<TextAttributes> values() const;
	///< Returns a smart pointer to the TextAttributes the tag uses for displaying text.
	///< The information specified acts an override on information specified by
	///< lower-priority tags. If no value is specified, then the next-lower-priority
	///< tag on the text determines the value. The text widget itself provides defaults
	///< if no tag specifies an override.

	int get_priority() const;
	///< Gets the tag priority.
	///< @return The tag's priority.

/// @}
/// @name Methods
/// @{

	void set_priority(int priority);
	///< Sets the priority of the TextTag.
	///< @param priority The new priority.
	///<
	///< Valid priorities are start at 0 and go to one less than Gtk::TextTagTable::get_size().
	///< Each tag in a table has a unique priority; setting the priority of one tag shifts the 
	///< priorities of all the other tags in the table to maintain a unique priority for each tag.
	///< Higher priority tags "win" if two tags both set the same text attribute. When adding a 
	///< tag to a tag table, it will be assigned the highest priority in the table by default; 
	///< so normally the precedence of a set of tags is the order in which they were added to the
	///< table, or created with gtk_text_buffer_create_tag(), which adds the tag to the buffer's
	///< table automatically.

	bool event(G::Object& event_object, Gdk::Event& event, const TextIter& iter);
	///< Emits the <EM>event</EM> signal on the TextTag.
	///< @param event_object The object that received the event, such as a widget.
	///< @param event The event.
	///< @param iter The location where the event was received.
	///< @return The result of signal emission (whether the event was handled).
	
/// @}
/// @name Property Proxies
/// @{
	
	const NamePropertyProxy property_name();
	///< The name used to refer to the text tag; null for anonymous tags
	///< (String : Read / Write / Construct Only).

	const BackgroundPropertyProxy property_background();
	///< The background color as a string (String : Write).

	const BackgroundGdkPropertyProxy property_background_gdk();
	///< The background color as a (possibly unallocated) Gdk::Color (Pointer<Gdk::Color> : Read / Write).

	const BackgroundFullHeightPropertyProxy property_background_full_height();
	///< Whether the background color fills the entire line height or only the height
	///< of the tagged characters (bool : Read / Write).

	const BackgroundStipplePropertyProxy property_background_stipple();
	///< The bitmap to use as a mask when drawing the text background (Gdk::Bitmap* : Read / Write).

	const ForegroundPropertyProxy property_foreground();
	///< The foreground color as a string (String : Write).

	const ForegroundGdkPropertyProxy property_foreground_gdk();
	///< The foreground color as a (possibly unallocated) Gdk::Color (Pointer<Gdk::Color> : Read / Write).

	const ForegroundStipplePropertyProxy property_foreground_stipple();
	///< The bitmap to use as a mask when drawing the text foreground (Gdk::Bitmap* : Read / Write).

	const DirectionPropertyProxy property_direction();
	///< The text direction, for example, right-to-left or left-to-right (TextDirection : Read / Write).

	const EditablePropertyProxy property_editable();
	///< Whether the text can be modified by the user (bool : Read / Write).

	const FontPropertyProxy property_font();
	///< The font description as a string, e.g. "Sans Italic 12" (String : Read / Write).

	const FontDescPropertyProxy property_font_desc();
	///< The font description as a Pango::FontDescription (Pointer<Pango::FontDescription> : Read / Write).

	const FamilyPropertyProxy property_family();
	///< The name of the font family, e.g. Sans, Helvetica, Times, Monospace (String : Read / Write).

	const StylePropertyProxy property_style();
	///< The font style as a Pango::Style, e.g. Pango::STYLE_ITALIC (Pango::Style : Read / Write).

	const VariantPropertyProxy property_variant();
	///< The font variant as a Pango::Variant, e.g. Pango::VARIANT_SMALL_CAPS (Pango::Variant : Read / Write).

	const WeightPropertyProxy property_weight();
	///< The font weight as Pango::Weight, for example, Pango::WEIGHT_BOLD (Pango::Weight : Read / Write).

	const StretchPropertyProxy property_stretch();
	///< The font stretch as a Pango::Stretch, e.g. Pango::STRETCH_CONDENSED (Pango::Stretch : Read / Write).

	const SizePropertyProxy property_size();
	///< The font size in Pango units (int : Read / Write).

	const ScalePropertyProxy property_scale();
	///< The font size as a scale factor relative to the default font size. This properly
	///< adapts to theme changes etc. so is recommended. Pango predefines some scales such
	///< as PANGO_SCALE_X_LARGE (double : Read / Write).

	const SizePointsPropertyProxy property_size_points();
	///< The font size in points (double : Read / Write).

	const JustificationPropertyProxy property_justification();
	///< Left, right, or center justification (Justification : Read / Write).

	const LanguagePropertyProxy property_language();
	///< The language this text is in, as an ISO code. Pango can use this as a hint when
	///< rendering the text. If you don't understand this parameter, you probably don't
	///< need it  (String : Read / Write).

	const LeftMarginPropertyProxy property_left_margin();
	///< The width of the left margin in pixels (int : Read / Write).

	const RightMarginPropertyProxy property_right_margin();
	///< The width of the right margin in pixels (int : Read / Write).

	const IndentPropertyProxy property_indent();
	///< The amount to indent the paragraph, in pixels (int : Read / Write).

	const RisePropertyProxy property_rise();
	///< The offset of text above the baseline (below the baseline if rise is negative)
	///< in pixels (int : Read / Write).

	const PixelsAboveLinesPropertyProxy property_pixels_above_lines();
	///< The pixels of blank space above paragraphs (int : Read / Write).

	const PixelsBelowLinesPropertyProxy property_pixels_below_lines();
	///< The pixels of blank space below paragraphs (int : Read / Write).

	const PixelsInsideWrapPropertyProxy property_pixels_inside_wrap();
	///< The pixels of blank space between wrapped lines in a paragraph (int : Read / Write).

	const StrikethroughPropertyProxy property_strikethrough();
	///< Whether to strike through the text (bool : Read / Write).

	const UnderlinePropertyProxy property_underline();
	///< The style of underline for this text (Pango::Underline : Read / Write).

	const WrapModePropertyProxy property_wrap_mode();
	///< Whether to wrap lines never, at word boundaries, or at character boundaries 
	///< (WrapMode : Read / Write).

	const TabsPropertyProxy property_tabs();
	///< The custom tabs for this text (Pointer<Pango::TabArray> : Read / Write).

	const InvisiblePropertyProxy property_invisible();
	///< Whether this text is hidden. Not implemented in GTK 2.0 (bool : Read / Write).

	const BackgroundSetPropertyProxy property_background_set();
	///< Whether this tag affects the background color (bool : Read / Write).

	const BackgroundFullHeightSetPropertyProxy property_background_full_height_set();
	///< Whether this tag affects background height (bool : Read / Write).

	const BackgroundStippleSetPropertyProxy property_background_stipple_set();
	///< Whether this tag affects the background stipple (bool : Read / Write).

	const ForegroundSetPropertyProxy property_foreground_set();
	///< Whether this tag affects the foreground color (bool : Read / Write).

	const ForegroundStippleSetPropertyProxy property_foreground_stipple_set();
	///< Whether this tag affects the foreground stipple (bool : Read / Write).

	const EditableSetPropertyProxy property_editable_set();
	///< Whether this tag affects text editability (bool : Read / Write).

	const FamilySetPropertyProxy property_family_set();
	///< Whether this tag affects the font family (bool : Read / Write).

	const StyleSetPropertyProxy property_style_set();
	///< Whether this tag affects the font style (bool : Read / Write).

	const VariantSetPropertyProxy property_variant_set();
	///< Whether this tag affects the font variant (bool : Read / Write).

	const WeightSetPropertyProxy property_weight_set();
	///< Whether this tag affects the font weight (bool : Read / Write).

	const StretchSetPropertyProxy property_stretch_set();
	///< Whether this tag affects the font stretch (bool : Read / Write).

	const SizeSetPropertyProxy property_size_set();
	///< Whether this tag affects the font size (bool : Read / Write).

	const ScaleSetPropertyProxy property_scale_set();
	///< Whether this tag scales the font size by a factor (bool : Read / Write).

	const JustificationSetPropertyProxy property_justification_set();
	///< Whether this tag affects paragraph justification (bool : Read / Write).

	const LanguageSetPropertyProxy property_language_set();
	///< Whether this tag affects the language the text is rendered in (bool : Read / Write).

	const LeftMarginSetPropertyProxy property_left_margin_set();
	///< Whether this tag affects the left margin (bool : Read / Write).

	const IndentSetPropertyProxy property_indent_set();
	///< Whether this tag affects indentation (bool : Read / Write).

	const RiseSetPropertyProxy property_rise_set();
	///< Whether this tag affects the rise (bool : Read / Write).

	const PixelsAboveLinesSetPropertyProxy property_pixels_above_lines_set();
	///< Whether this tag affects the number of pixels above lines (bool : Read / Write).

	const PixelsBelowLinesSetPropertyProxy property_pixels_below_lines_set();
	///< Whether this tag affects the number of pixels below lines (bool : Read / Write).

	const PixelsInsideWrapSetPropertyProxy property_pixels_inside_wrap_set();
	///< Whether this tag affects the number of pixels between wrapped lines (bool : Read / Write).

	const StrikethroughSetPropertyProxy property_strikethrough_set();
	///< Whether this tag affects strikethrough (bool : Read / Write).

	const RightMarginSetPropertyProxy property_right_margin_set();
	///< Whether this tag affects the right margin (bool : Read / Write).

	const UnderlineSetPropertyProxy property_underline_set();
	///< Whether this tag affects underlining (bool : Read / Write).

	const WrapModeSetPropertyProxy property_wrap_mode_set();
	///< Whether this tag affects line wrap mode (bool : Read / Write).

	const TabsSetPropertyProxy property_tabs_set();
	///< Whether this tag affects tabs (bool : Read / Write).

	const InvisibleSetPropertyProxy property_invisible_set();
	///< Whether this tag affects text visibility (bool : Read / Write).

/// @}
/// @name Signal Proxies
/// @{

	const EventSignalProxy signal_event();
	///< Connect to the event_signal; emitted when the text tag receives a motion, button, or key event signal.

/// @}
};

/// @class TextTagTable texttag.hh xfc/gtk/texttag.hh
/// @brief A GtkTextTagTable C++ wrapper class.
///
/// TextTags are stored in a TexTagTable. A tag table defines a set of tags
/// that can be used together. Each buffer has one tag table associated with
/// it; only tags from that tag table can be used with the buffer. A single
/// tag table can be shared between multiple buffers, however.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/textview.html">TextView Widget</A> HOWTO and example.

class TextTagTable : public G::Object
{
	friend class G::Object;

	TextTagTable(const TextTagTable&);
	TextTagTable& operator=(const TextTagTable&);

protected:
/// @name Constructors
/// @{

	explicit TextTagTable(GtkTextTagTable *table, bool owns_reference = true);
	///< Construct a new TextTagTable from an existing GtkTextTagTable.
	///< @param table A pointer to a GtkTextTagTable.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>table</EM> can be a newly created GtkTextTagTable or an existing
	///< GtkTextTagTable (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, TextTag&, bool> TagChangedSignalType;
	typedef G::SignalProxy<TypeInstance, TagChangedSignalType> TagChangedSignalProxy;
	static const TagChangedSignalType tag_changed_signal;
	///< Tag changed signal (see signal_tag_changed()). Calls a slot with the signature:
	///< @code
	///< void function(TextTag& tag, bool size_changed);
	///< // tag: The tag whose property was changed.
	///< // size_changed: true if the changed property resulted in a change to the text display size.
	///< @endcode

	typedef G::Signal<void, TextTag&> TagAddedSignalType;
	typedef G::SignalProxy<TypeInstance, TagAddedSignalType> TagAddedSignalProxy;
	static const TagAddedSignalType tag_added_signal;
	///< Tag added signal (see signal_tag_added()). Calls a slot with the signature:
	///< @code
	///< void function(TextTag& tag);
	///< // tag: The tag being added to the table.
	///< @endcode

	typedef G::Signal<void, TextTag&> TagRemovedSignalType;
	typedef G::SignalProxy<TypeInstance, TagRemovedSignalType> TagRemovedSignalProxy;
	static const TagRemovedSignalType tag_removed_signal;
	///< Tag removed signal (see signal_tag_removed()). Calls a slot with the signature:
	///< @code
	///< void function(TextTag& tag);
	///< // tag: The tag being removed to the table.
	///< @endcode
	
/// @}

public:
	typedef GtkTextTagTable CObjectType;
	
	typedef sigc::slot<void, TextTag&> ForeachSlot;
	///< Signature of the callback slot to be called on each tag in the table.
	///< <B>Example:</B> Method signature for ForeachSlot.
	///< @code
	///< void method(TextTag& tag);
	///<
	///< // tag: A text tag.
	///< @endcode

/// @name Constructors
/// @{

	TextTagTable();
	///< Construct a new TextTagTable with a reference count of 1 that the caller owns.
	///< The table contains no tags by default.

	virtual ~TextTagTable();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkTextTagTable* gtk_text_tag_table() const;
	///< Get a pointer to the GtkTextTagTable structure.

	operator GtkTextTagTable* () const;
	///< Conversion operator; safely converts a TextTagTable to a GtkTextTagTable pointer.

	int get_size() const;
	///< Returns the size of the table (number of tags)
	///< @return The number of tags in the table.

	TextTag* lookup(const char *name);
	TextTag* lookup(const String& name);
	///< Look up a named tag.
	///< @param name The name of a tag.
	///< @return The tag, or null if none by that name is in the table.

/// @}
/// @name Methods
/// @{

	void add(TextTag& tag);
	///< Add a tag to the table. 
	///< @param tag A TextTag.
	///<
	///< The tag is assigned the highest priority in the table. <EM>tag</EM> must not be
	///< in a tag table already, and may not have the same name as an already-added tag.

	void remove(TextTag& tag);
	///< Remove a tag from the table. 
	///< @param tag A TextTag.
	///<
	///< This will remove the table's reference to the tag, so be careful - the tag will
	///< end up destroyed if you don't have a reference to it.

	void foreach(const ForeachSlot& each);
	///< Calls <EM>each</EM> on each tag in table.
	///< @param each The callback slot to call on each tag.

/// @}
/// @name Signal Proxies
/// @{

	const TagChangedSignalProxy signal_tag_changed();
	///< Connect to the tag_changed_signal; emitted whenever a tag property is changed.

	const TagAddedSignalProxy signal_tag_added();
	///< Connect to the tag_added_signal; emitted whenever a tag is added to the table.

	const TagRemovedSignalProxy signal_tag_removed();
	///< Connect to the tag_removed_signal; emitted whenever a tag is removed from the table.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/texttag.inl>

#endif // XFC_GTK_TEXT_TAG_HH

