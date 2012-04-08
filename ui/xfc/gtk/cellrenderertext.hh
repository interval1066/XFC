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
 
/// @file xfc/gtk/cellrenderertext.hh
/// @brief A GtkCellRendererText C++ wrapper interface.
///
/// Provides CellRendererText, an object that renders text in a cell.

#ifndef XFC_GTK_CELL_RENDERER_TEXT_HH
#define XFC_GTK_CELL_RENDERER_TEXT_HH

#ifndef XFC_GTK_CELL_RENDERER_HH
#include <xfc/gtk/cellrenderer.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef XFC_PANGO_LAYOUT_HH
#include <xfc/pango/layout.hh>
#endif

#ifndef __GTK_CELL_RENDERER_TEXT_H__
#include <gtk/gtkcellrenderertext.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class CellRendererText cellrenderertext.hh xfc/gtk/cellrenderertext.hh
/// @brief A GtkCellRendererText C++ wrapper class.

class CellRendererText : public CellRenderer
{
	friend class G::Object;

	CellRendererText(const CellRendererText&);
	CellRendererText& operator=(const CellRendererText&);

protected:
/// @name Constructors
/// @{

	explicit CellRendererText(GtkCellRendererText *cell, bool owns_reference = false);
	///< Construct a new CellRendererText from an existing GtkCellRendererText.
	///< @param cell A pointer to a GtkCellRendererText.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>cell</EM> can be a newly created GtkCellRendererText or an existing
	///< GtkCellRendererText. (see G::Object::Object).

/// @}
/// @name Property Prototypes
/// @{

	typedef G::Property<String> TextPropertyType;
	typedef G::PropertyProxy<G::Object, TextPropertyType> TextPropertyProxy;
	static const TextPropertyType text_property;
	///< Text to render (see property_text()).

	typedef G::WritableProperty<String> MarkupPropertyType;
	typedef G::PropertyProxy<G::Object, MarkupPropertyType> MarkupPropertyProxy;
	static const MarkupPropertyType markup_property;
	///< Marked up text to render (see property_markup()).

	typedef G::Property<Pointer<Pango::AttrList> > AttributePropertyType;
	typedef G::PropertyProxy<G::Object, AttributePropertyType> AttributePropertyProxy;
	static const AttributePropertyType attribute_property;
	///< A list of style attributes to apply to the text of the renderer (see property_attribute()).

	typedef G::Property<Pointer<bool> > SingleParagraphModePropertyType;
	typedef G::PropertyProxy<G::Object, SingleParagraphModePropertyType> SingleParagraphModePropertyProxy;
	static const SingleParagraphModePropertyType single_paragraph_mode_property;
	///< Whether or not to keep all text in a single paragraph (see property_single_paragraph_mode()).	

	typedef G::Property<int> WidthCharsPropertyType;
	typedef G::PropertyProxy<G::Object, WidthCharsPropertyType> WidthCharsPropertyProxy;
	static const WidthCharsPropertyType width_chars_property;
	///< Width In Characters (see property_width_chars()).

	typedef G::WritableProperty<String> BackgroundPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundPropertyType> BackgroundPropertyProxy;
	static const BackgroundPropertyType background_property;
	///< Background color as a string (see property_background()).

	typedef G::Property<Pointer<Gdk::Color> > BackgroundGdkPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundGdkPropertyType> BackgroundGdkPropertyProxy;
	static const BackgroundGdkPropertyType background_gdk_property;
	///< Background color as a Gdk::Color (see property_background_gdk()).

	typedef G::WritableProperty<String> ForegroundPropertyType;
	typedef G::PropertyProxy<G::Object, ForegroundPropertyType> ForegroundPropertyProxy;
	static const ForegroundPropertyType foreground_property;
	///< Foreground color as a string (see property_foreground()).

	typedef G::Property<Pointer<Gdk::Color> > ForegroundGdkPropertyType;
	typedef G::PropertyProxy<G::Object, ForegroundGdkPropertyType> ForegroundGdkPropertyProxy;
	static const ForegroundGdkPropertyType foreground_gdk_property;
	///< Foreground color as a Gdk::Color (see property_foreground_gdk()).

	typedef G::Property<bool> EditablePropertyType;
	typedef G::PropertyProxy<G::Object, EditablePropertyType> EditablePropertyProxy;
	static const EditablePropertyType editable_property;
	///< Whether the text can be modified by the user (see property_editable()).

	typedef G::Property<String> FontPropertyType;
	typedef G::PropertyProxy<G::Object, FontPropertyType> FontPropertyProxy;
	static const FontPropertyType font_property;
	///< Font description as a string (see property_font()).

	typedef G::Property<Pointer<Pango::FontDescription> > FontDescPropertyType;
	typedef G::PropertyProxy<G::Object, FontDescPropertyType> FontDescPropertyProxy;
	static const FontDescPropertyType font_desc_property;
	///< Font description as a Pango::FontDescription (see property_font_desc()).

	typedef G::Property<String> FamilyPropertyType;
	typedef G::PropertyProxy<G::Object, FamilyPropertyType> FamilyPropertyProxy;
	static const FamilyPropertyType family_property;
	///< Name of the font family (see property_family()).

	typedef G::Property<Pango::Style, int> StylePropertyType;
	typedef G::PropertyProxy<G::Object, StylePropertyType> StylePropertyProxy;
	static const StylePropertyType style_property;
	///< Font style (see property_style()).

	typedef G::Property<Pango::Variant, int> VariantPropertyType;
	typedef G::PropertyProxy<G::Object, VariantPropertyType> VariantPropertyProxy;
	static const VariantPropertyType variant_property;
	///< Font variant (see property_variant()).

	typedef G::Property<Pango::Weight, int> WeightPropertyType;
	typedef G::PropertyProxy<G::Object, WeightPropertyType> WeightPropertyProxy;
	static const WeightPropertyType weight_property;
	///< Font weight (see property_weight()).

	typedef G::Property<Pango::Stretch, int> StretchPropertyType;
	typedef G::PropertyProxy<G::Object, StretchPropertyType> StretchPropertyProxy;
	static const StretchPropertyType stretch_property;
	///< Font stretch (see property_stretch()).

	typedef G::Property<int> SizePropertyType;
	typedef G::PropertyProxy<G::Object, SizePropertyType> SizePropertyProxy;
	static const SizePropertyType size_property;
	///< Font size (see property_size()).

	typedef G::Property<double> SizePointsPropertyType;
	typedef G::PropertyProxy<G::Object, SizePointsPropertyType> SizePointsPropertyProxy;
	static const SizePointsPropertyType size_points_property;
	///< Font size in points (see property_size_points()).

	typedef G::Property<double> ScalePropertyType;
	typedef G::PropertyProxy<G::Object, ScalePropertyType> ScalePropertyProxy;
	static const ScalePropertyType scale_property;
	///< Font size in points (see property_size_points()).

	typedef G::Property<int> RisePropertyType;
	typedef G::PropertyProxy<G::Object, RisePropertyType> RisePropertyProxy;
	static const RisePropertyType rise_property;
	///< Offset of text above the baseline (see property_rise()).

	typedef G::Property<String> LanguagePropertyType;
	typedef G::PropertyProxy<G::Object, LanguagePropertyType> LanguagePropertyProxy;
	static const LanguagePropertyType language_property;
	///< The language this text is in, as an ISO code (see property_language()).

	typedef G::Property<bool> StrikethroughPropertyType;
	typedef G::PropertyProxy<G::Object, StrikethroughPropertyType> StrikethroughPropertyProxy;
	static const StrikethroughPropertyType strikethrough_property;
	///< Whether to strike through the text (see property_strikethrough()).

	typedef G::Property<Pango::Underline, int> UnderlinePropertyType;
	typedef G::PropertyProxy<G::Object, UnderlinePropertyType> UnderlinePropertyProxy;
	static const UnderlinePropertyType underline_property;
	///< Style of underline for this text (see property_underline()).

	typedef G::Property<Pango::EllipsizeMode, int> EllipsizePropertyType;
	typedef G::PropertyProxy<G::Object, EllipsizePropertyType> EllipsizePropertyProxy;
	static const EllipsizePropertyType ellipsize_property;
	///< The preferred place to ellipsize the string, if the cell renderer does not have
	///< enough room to display the entire string, if at all (see property_ellipsize()).	
	
	typedef G::Property<bool> BackgroundSetPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundSetPropertyType> BackgroundSetPropertyProxy;
	static const BackgroundSetPropertyType background_set_property;
	///< Whether this tag affects the background color (see property_background_set()).

	typedef G::Property<bool> ForegroundSetPropertyType;
	typedef G::PropertyProxy<G::Object, ForegroundSetPropertyType> ForegroundSetPropertyProxy;
	static const ForegroundSetPropertyType foreground_set_property;
	///< Whether this tag affects the foreground color (see property_foreground_set()).

	typedef G::Property<bool> EditableSetPropertyType;
	typedef G::PropertyProxy<G::Object, EditableSetPropertyType> EditableSetPropertyProxy;
	static const EditableSetPropertyType editable_set_property;
	///< Whether this tag affects text editability (see property_editable_set()).

	typedef G::Property<bool> FamilySetPropertyType;
	typedef G::PropertyProxy<G::Object, FamilySetPropertyType> FamilySetPropertyProxy;
	static const FamilySetPropertyType family_set_property;
	///< Whether this tag affects the font family (see property_family_set()).

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

	typedef G::Property<bool> RiseSetPropertyType;
	typedef G::PropertyProxy<G::Object, RiseSetPropertyType> RiseSetPropertyProxy;
	static const RiseSetPropertyType rise_set_property;
	///< Whether this tag scales the font size by a factor (see property_rise_set()).

	typedef G::Property<bool> StrikethroughSetPropertyType;
	typedef G::PropertyProxy<G::Object, StrikethroughSetPropertyType> StrikethroughSetPropertyProxy;
	static const StrikethroughSetPropertyType strikethrough_set_property;
	///< Whether this tag affects strikethrough (see property_strikethrough_set()).

	typedef G::Property<bool> UnderlineSetPropertyType;
	typedef G::PropertyProxy<G::Object, UnderlineSetPropertyType> UnderlineSetPropertyProxy;
	static const UnderlineSetPropertyType underline_set_property;
	///< Whether this tag affects underlining (see property_underline_set()).

	typedef G::Property<bool> LanguageSetPropertyType;
	typedef G::PropertyProxy<G::Object, LanguageSetPropertyType> LanguageSetPropertyProxy;
	static const LanguageSetPropertyType language_set_property;
	///< Whether this tag affects the language the text is rendered as (see property_language_set()).

	typedef G::Property<bool> EllipsizeSetPropertyType;
	typedef G::PropertyProxy<G::Object, EllipsizeSetPropertyType> EllipsizeSetPropertyProxy;
	static const EllipsizeSetPropertyType ellipsize_set_property;
	///< Whether this tag affects the ellipsize mode (see property_ellipsize_set()).	
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, const String&, const String&> EditedSignalType;
	typedef G::SignalProxy<TypeInstance, EditedSignalType> EditedSignalProxy;
	static const EditedSignalType edited_signal;
	///< Edited signal (see signal_edited()). Calls a slot with the signature:
	///< @code
	///< void function(const String& path, const String& new_text);
	///< // path: Widget-dependent string representation of the event location;
	///<          e.g. for TreeView, a string representation of TreePath.
	///< // new_text: The newly edited text.
	///< @endcode
	
/// @}

public:
	typedef GtkCellRendererText CObjectType;

/// @name Constructors
/// @{

	CellRendererText();
	///< Construct a new CellRendererText. 
	///< You can adjust how text is drawn using object properties. Also, with TreeViewColumn,
	///< you can bind a property to a value in a TreeModel. For example, you can bind the 
	///< "text" property on the cell renderer to a string value in the model, thus rendering
	///< a different string in each row of the TreeView.

	virtual ~CellRendererText();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkCellRendererText* gtk_cell_renderer_text() const;
	///< Get a pointer to the GtkCellRendererText structure.

	operator GtkCellRendererText* () const;
	///< Conversion operator; safely converts a CellRendererText to a GtkCellRendererText pointer.

/// @}
/// @name Methods
/// @{

 	void set_fixed_height_from_font(int number_of_rows);
	///< Sets the height of a renderer to explicitly be determined by the "font" and
	///< the "y_pad" property set on it.
	///< @param number_of_rows Number of rows of text each cell renderer is allocated, or -1
	///<
	///< Further changes in these properties do not affect the height, so they must
	///< be accompanied by a subsequent call to this function. Using this function is
	///< unflexible, and should really only be used if calculating the size of a cell
	///< is too slow (ie, a massive number of cells displayed). If number_of_rows is -1,
	///< then the fixed height is unset, and the height is determined by the properties
	///< again.

/// @}
/// @name Property Proxies
/// @{

	const TextPropertyProxy property_text();
	///< Text to render (String : Read / Write).

	const MarkupPropertyProxy property_markup();
	///< Marked up text to render (String : Write).

	const AttributePropertyProxy property_attribute();
	///< A list of style attributes to apply to the text of the renderer
	///< (Pointer<Pango::AttrList> : Read / Write).

	const SingleParagraphModePropertyProxy property_single_paragraph_mode();
	///< Whether or not to keep all text in a single paragraph (bool : Read / Write).	
	
	const WidthCharsPropertyProxy property_width_chars();
	///< The desired width of the label, in characters (int : Read / Write).
	
	const BackgroundPropertyProxy property_background();
	///< Background color as a string (String : Write).

	const BackgroundGdkPropertyProxy property_background_gdk();
	///< Background color as a Gdk::Color (Pointer<Gdk::Color> : Read / Write).

	const ForegroundPropertyProxy property_foreground();
	///< Foreground color as a string (String : Write).

	const ForegroundGdkPropertyProxy property_foreground_gdk();
	///< Foreground color as a Gdk::Color (Pointer<Gdk::Color> : Read / Write).

	const EditablePropertyProxy property_editable();
	///< Whether the text can be modified by the user (bool : Read / Write).

	const FontPropertyProxy property_font();
	///< Font description as a string (String : Read / Write).

	const FontDescPropertyProxy property_font_desc();
	///< Font description as a Pango::FontDescription (Pointer<Pango::FontDescription> : Read / Write).

	const FamilyPropertyProxy property_family();
	///< Name of the font family, e.g. Sans, Helvetica, Times, Monospace (String : Read / Write).

	const StylePropertyProxy property_style();
	///< Font style (Pango::Style : Read / Write).

	const VariantPropertyProxy property_variant();
	///< Font variant (Pango::Variant : Read / Write).

	const WeightPropertyProxy property_weight();
	///< Font weight (int : Read / Write).

	const StretchPropertyProxy property_stretch();
	///< Font stretch (Pango::Stretch : Read / Write).

	const SizePropertyProxy property_size();
	///< Font size (int : Read / Write).

	const SizePointsPropertyProxy property_size_points();
	///< Font size in points (double : Read / Write).

	const ScalePropertyProxy property_scale();
	///< Font scaling factor (double : Read / Write).

	const RisePropertyProxy property_rise();
	///< Offset of text above the baseline (below the baseline if rise is negative) (int : Read / Write).

	const LanguagePropertyProxy property_language();
	///< The language this text is in, as an ISO code (String : Read / Write). Pango can use this
	///< as a hint when rendering the text. If you don't understand this property, you probably
	///< don't need it.
		
	const StrikethroughPropertyProxy property_strikethrough();
	///< Whether to strike through the text (bool : Read / Write).

	const UnderlinePropertyProxy property_underline();
	///< Style of underline for this text (Pango::Underline : Read / Write).

	const EllipsizePropertyProxy property_ellipsize();
	///< The preferred place to ellipsize the string, if the cell renderer
	///< does not have enough room to display the entire string, if at all.							
	
	const BackgroundSetPropertyProxy property_background_set();
	///< Whether this tag affects the background color (bool : Read / Write).

	const ForegroundSetPropertyProxy property_foreground_set();
	///< Whether this tag affects the foreground color (bool : Read / Write).

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

	const RiseSetPropertyProxy property_rise_set();
	///< Whether this tag scales the font size by a factor (bool : Read / Write).

	const StrikethroughSetPropertyProxy property_strikethrough_set();
	///< Whether this tag affects strikethrough (bool : Read / Write).

	const UnderlineSetPropertyProxy property_underline_set();
	///< Whether this tag affects underlining (bool : Read / Write).

	const LanguageSetPropertyProxy property_language_set();
	///< Whether this tag affects the language the text is rendered as (bool : Read / Write).

	const EllipsizeSetPropertyProxy property_ellipsize_set();
	///< Whether this tag affects the ellipsize mode.							

/// @}
/// @name Signal Proxies
/// @{

	const EditedSignalProxy signal_edited();
	///< Connect to the editing_done_signal; emitted when the user has finished editing the cell text.

///, @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/cellrenderertext.inl>

#endif // XFC_GTK_CELL_RENDERER_TEXT_HH

