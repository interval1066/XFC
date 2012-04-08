/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  texttag.inl - Gtk::TextTag and Gtk::TextTagTable inline functions
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

/*  Gtk::TextAppearance
 */

inline GtkTextAppearance*
Xfc::Gtk::TextAppearance::gtk_text_appearance() const
{
	return const_cast<GtkTextAppearance*>(&appearence_);
}

inline int
Xfc::Gtk::TextAppearance::rise() const
{
	return appearence_.rise;
}

inline Xfc::Pango::Underline
Xfc::Gtk::TextAppearance::underline() const
{
	return (Pango::Underline)appearence_.underline;
}

inline bool
Xfc::Gtk::TextAppearance::strikethrough() const
{
	return appearence_.strikethrough;
}

inline void
Xfc::Gtk::TextAppearance::set_rise(int rise)
{
	appearence_.rise = rise;
}

inline void
Xfc::Gtk::TextAppearance::set_underline(Pango::Underline underline)
{
	appearence_.underline = (unsigned int)underline;
}

inline void
Xfc::Gtk::TextAppearance::set_strikethrough(bool setting)
{
	appearence_.strikethrough = setting;
}

/*  Gtk::TextAttributes
 */

inline GtkTextAttributes*
Xfc::Gtk::TextAttributes::gtk_text_attributes() const
{
	return reinterpret_cast<GtkTextAttributes*>(boxed_);
}

inline Xfc::Gtk::TextAttributes::operator GtkTextAttributes* () const
{
	return this ? gtk_text_attributes() : 0;
}

inline Xfc::Gtk::Justification
Xfc::Gtk::TextAttributes::justification() const
{
	return (Justification)gtk_text_attributes()->justification;
}

inline Xfc::Gtk::TextDirection
Xfc::Gtk::TextAttributes::direction() const
{
	return (TextDirection)gtk_text_attributes()->direction;
}

inline double
Xfc::Gtk::TextAttributes::font_scale() const
{
	return gtk_text_attributes()->font_scale;
}

inline int
Xfc::Gtk::TextAttributes::left_margin() const
{
	return gtk_text_attributes()->left_margin;
}

inline int
Xfc::Gtk::TextAttributes::indent() const
{
	return gtk_text_attributes()->indent;
}

inline int
Xfc::Gtk::TextAttributes::right_margin() const
{
	return gtk_text_attributes()->right_margin;
}

inline int
Xfc::Gtk::TextAttributes::pixels_above_lines() const
{
	return gtk_text_attributes()->pixels_above_lines;
}

inline int
Xfc::Gtk::TextAttributes::pixels_below_lines() const
{
	return gtk_text_attributes()->pixels_below_lines;
}

inline int
Xfc::Gtk::TextAttributes::pixels_inside_wrap() const
{
	return gtk_text_attributes()->pixels_inside_wrap;
}

inline Xfc::Gtk::WrapMode
Xfc::Gtk::TextAttributes::wrap_mode() const
{
	return (WrapMode)gtk_text_attributes()->wrap_mode;
}

inline bool
Xfc::Gtk::TextAttributes::invisible() const
{
	return gtk_text_attributes()->invisible;
}

inline bool
Xfc::Gtk::TextAttributes::bg_full_height() const
{
	return gtk_text_attributes()->bg_full_height;
}

inline bool
Xfc::Gtk::TextAttributes::editable() const
{
	return gtk_text_attributes()->editable;
}

inline bool
Xfc::Gtk::TextAttributes::realized() const
{
	return gtk_text_attributes()->realized;
}

inline void
Xfc::Gtk::TextAttributes::set_justification(Justification justification)
{
	gtk_text_attributes()->justification = (GtkJustification)justification;
}

inline void
Xfc::Gtk::TextAttributes::set_direction(TextDirection direction)
{
	gtk_text_attributes()->direction = (GtkTextDirection)direction;
}

inline void
Xfc::Gtk::TextAttributes::set_left_margin(int margin)
{
	gtk_text_attributes()->left_margin = margin;
}

inline void
Xfc::Gtk::TextAttributes::set_right_margin(int margin)
{
	gtk_text_attributes()->right_margin = margin;
}

inline void
Xfc::Gtk::TextAttributes::set_indent(int indent)
{
	gtk_text_attributes()->indent = indent;
}

inline void
Xfc::Gtk::TextAttributes::set_pixels_above_lines(int pixels)
{
	gtk_text_attributes()->pixels_above_lines = pixels;
}

inline void
Xfc::Gtk::TextAttributes::set_pixels_below_lines(int pixels)
{
	gtk_text_attributes()->pixels_below_lines = pixels;
}

inline void
Xfc::Gtk::TextAttributes::set_pixels_inside_wrap(int pixels)
{
	gtk_text_attributes()->pixels_inside_wrap = pixels;
}

inline void
Xfc::Gtk::TextAttributes::set_wrap_mode(WrapMode wrap_mode)
{
	gtk_text_attributes()->wrap_mode = (GtkWrapMode)wrap_mode;
}

inline void
Xfc::Gtk::TextAttributes::set_invisible(bool setting)
{
	gtk_text_attributes()->invisible = setting;
}

inline void
Xfc::Gtk::TextAttributes::set_bg_full_height(bool setting)
{
	gtk_text_attributes()->bg_full_height = setting;
}

inline void
Xfc::Gtk::TextAttributes::set_editable(bool setting)
{
	gtk_text_attributes()->editable = setting;
}

/*  Gtk::TextTag
 */

inline GtkTextTag*
Xfc::Gtk::TextTag::gtk_text_tag() const
{
	return reinterpret_cast<GtkTextTag*>(instance_);
}

inline Xfc::Gtk::TextTag::operator GtkTextTag* () const
{
	return this ? gtk_text_tag() : 0;
}

inline int
Xfc::Gtk::TextTag::get_priority() const
{
	return gtk_text_tag_get_priority(gtk_text_tag());
}

inline void
Xfc::Gtk::TextTag::set_priority(int priority)
{
	gtk_text_tag_set_priority(gtk_text_tag(), priority);
}

inline const Xfc::Gtk::TextTag::NamePropertyProxy
Xfc::Gtk::TextTag::property_name()
{
	return NamePropertyProxy(this, &name_property);
}

inline const Xfc::Gtk::TextTag::BackgroundPropertyProxy
Xfc::Gtk::TextTag::property_background()
{
	return BackgroundPropertyProxy(this, &background_property);
}

inline const Xfc::Gtk::TextTag::BackgroundGdkPropertyProxy
Xfc::Gtk::TextTag::property_background_gdk()
{
	return BackgroundGdkPropertyProxy(this, &background_gdk_property);
}

inline const Xfc::Gtk::TextTag::BackgroundFullHeightPropertyProxy
Xfc::Gtk::TextTag::property_background_full_height()
{
	return BackgroundFullHeightPropertyProxy(this, &background_full_height_property);
}

inline const Xfc::Gtk::TextTag::BackgroundStipplePropertyProxy
Xfc::Gtk::TextTag::property_background_stipple()
{
	return BackgroundStipplePropertyProxy(this, &background_stipple_property);
}

inline const Xfc::Gtk::TextTag::ForegroundPropertyProxy
Xfc::Gtk::TextTag::property_foreground()
{
	return ForegroundPropertyProxy(this, &foreground_property);
}

inline const Xfc::Gtk::TextTag::ForegroundGdkPropertyProxy
Xfc::Gtk::TextTag::property_foreground_gdk()
{
	return ForegroundGdkPropertyProxy(this, &foreground_gdk_property);
}

inline const Xfc::Gtk::TextTag::ForegroundStipplePropertyProxy
Xfc::Gtk::TextTag::property_foreground_stipple()
{
	return ForegroundStipplePropertyProxy(this, &foreground_stipple_property);
}

inline const Xfc::Gtk::TextTag::DirectionPropertyProxy
Xfc::Gtk::TextTag::property_direction()
{
	return DirectionPropertyProxy(this, &direction_property);
}

inline const Xfc::Gtk::TextTag::EditablePropertyProxy
Xfc::Gtk::TextTag::property_editable()
{
	return EditablePropertyProxy(this, &editable_property);
}

inline const Xfc::Gtk::TextTag::FontPropertyProxy
Xfc::Gtk::TextTag::property_font()
{
	return FontPropertyProxy(this, &font_property);
}

inline const Xfc::Gtk::TextTag::FontDescPropertyProxy
Xfc::Gtk::TextTag::property_font_desc()
{
	return FontDescPropertyProxy(this, &font_desc_property);
}

inline const Xfc::Gtk::TextTag::FamilyPropertyProxy
Xfc::Gtk::TextTag::property_family()
{
	return FamilyPropertyProxy(this, &family_property);
}

inline const Xfc::Gtk::TextTag::StylePropertyProxy
Xfc::Gtk::TextTag::property_style()
{
	return StylePropertyProxy(this, &style_property);
}

inline const Xfc::Gtk::TextTag::VariantPropertyProxy
Xfc::Gtk::TextTag::property_variant()
{
	return VariantPropertyProxy(this, &variant_property);
}

inline const Xfc::Gtk::TextTag::WeightPropertyProxy
Xfc::Gtk::TextTag::property_weight()
{
	return WeightPropertyProxy(this, &weight_property);
}

inline const Xfc::Gtk::TextTag::StretchPropertyProxy
Xfc::Gtk::TextTag::property_stretch()
{
	return StretchPropertyProxy(this, &stretch_property);
}

inline const Xfc::Gtk::TextTag::SizePropertyProxy
Xfc::Gtk::TextTag::property_size()
{
	return SizePropertyProxy(this, &size_property);
}

inline const Xfc::Gtk::TextTag::ScalePropertyProxy
Xfc::Gtk::TextTag::property_scale()
{
	return ScalePropertyProxy(this, &scale_property);
}

inline const Xfc::Gtk::TextTag::SizePointsPropertyProxy
Xfc::Gtk::TextTag::property_size_points()
{
	return SizePointsPropertyProxy(this, &size_points_property);
}

inline const Xfc::Gtk::TextTag::JustificationPropertyProxy
Xfc::Gtk::TextTag::property_justification()
{
	return JustificationPropertyProxy(this, &justification_property);
}

inline const Xfc::Gtk::TextTag::LanguagePropertyProxy
Xfc::Gtk::TextTag::property_language()
{
	return LanguagePropertyProxy(this, &language_property);
}

inline const Xfc::Gtk::TextTag::LeftMarginPropertyProxy
Xfc::Gtk::TextTag::property_left_margin()
{
	return LeftMarginPropertyProxy(this, &left_margin_property);
}

inline const Xfc::Gtk::TextTag::RightMarginPropertyProxy
Xfc::Gtk::TextTag::property_right_margin()
{
	return RightMarginPropertyProxy(this, &right_margin_property);
}

inline const Xfc::Gtk::TextTag::IndentPropertyProxy
Xfc::Gtk::TextTag::property_indent()
{
	return IndentPropertyProxy(this, &indent_property);
}

inline const Xfc::Gtk::TextTag::RisePropertyProxy
Xfc::Gtk::TextTag::property_rise()
{
	return RisePropertyProxy(this, &rise_property);
}

inline const Xfc::Gtk::TextTag::PixelsAboveLinesPropertyProxy
Xfc::Gtk::TextTag::property_pixels_above_lines()
{
	return PixelsAboveLinesPropertyProxy(this, &pixels_above_lines_property);
}

inline const Xfc::Gtk::TextTag::PixelsBelowLinesPropertyProxy
Xfc::Gtk::TextTag::property_pixels_below_lines()
{
	return PixelsBelowLinesPropertyProxy(this, &pixels_below_lines_property);
}

inline const Xfc::Gtk::TextTag::PixelsInsideWrapPropertyProxy
Xfc::Gtk::TextTag::property_pixels_inside_wrap()
{
	return PixelsInsideWrapPropertyProxy(this, &pixels_inside_wrap_property);
}

inline const Xfc::Gtk::TextTag::StrikethroughPropertyProxy
Xfc::Gtk::TextTag::property_strikethrough()
{
	return StrikethroughPropertyProxy(this, &strikethrough_property);
}

inline const Xfc::Gtk::TextTag::UnderlinePropertyProxy
Xfc::Gtk::TextTag::property_underline()
{
	return UnderlinePropertyProxy(this, &underline_property);
}

inline const Xfc::Gtk::TextTag::WrapModePropertyProxy
Xfc::Gtk::TextTag::property_wrap_mode()
{
	return WrapModePropertyProxy(this, &wrap_mode_property);
}

inline const Xfc::Gtk::TextTag::TabsPropertyProxy
Xfc::Gtk::TextTag::property_tabs()
{
	return TabsPropertyProxy(this, &tabs_property);
}

inline const Xfc::Gtk::TextTag::InvisiblePropertyProxy
Xfc::Gtk::TextTag::property_invisible()
{
	return InvisiblePropertyProxy(this, &invisible_property);
}

inline const Xfc::Gtk::TextTag::BackgroundSetPropertyProxy
Xfc::Gtk::TextTag::property_background_set()
{
	return BackgroundSetPropertyProxy(this, &background_set_property);
}

inline const Xfc::Gtk::TextTag::BackgroundFullHeightSetPropertyProxy
Xfc::Gtk::TextTag::property_background_full_height_set()
{
	return BackgroundFullHeightSetPropertyProxy(this, &background_full_height_set_property);
}

inline const Xfc::Gtk::TextTag::BackgroundStippleSetPropertyProxy
Xfc::Gtk::TextTag::property_background_stipple_set()
{
	return BackgroundStippleSetPropertyProxy(this, &background_stipple_set_property);
}

inline const Xfc::Gtk::TextTag::ForegroundSetPropertyProxy
Xfc::Gtk::TextTag::property_foreground_set()
{
	return ForegroundSetPropertyProxy(this, &foreground_set_property);
}

inline const Xfc::Gtk::TextTag::ForegroundStippleSetPropertyProxy
Xfc::Gtk::TextTag::property_foreground_stipple_set()
{
	return ForegroundStippleSetPropertyProxy(this, &foreground_stipple_set_property);
}

inline const Xfc::Gtk::TextTag::EditableSetPropertyProxy
Xfc::Gtk::TextTag::property_editable_set()
{
	return EditableSetPropertyProxy(this, &editable_set_property);
}

inline const Xfc::Gtk::TextTag::FamilySetPropertyProxy
Xfc::Gtk::TextTag::property_family_set()
{
	return FamilySetPropertyProxy(this, &family_set_property);
}

inline const Xfc::Gtk::TextTag::StyleSetPropertyProxy
Xfc::Gtk::TextTag::property_style_set()
{
	return StyleSetPropertyProxy(this, &style_set_property);
}

inline const Xfc::Gtk::TextTag::VariantSetPropertyProxy
Xfc::Gtk::TextTag::property_variant_set()
{
	return VariantSetPropertyProxy(this, &variant_set_property);
}

inline const Xfc::Gtk::TextTag::WeightSetPropertyProxy
Xfc::Gtk::TextTag::property_weight_set()
{
	return WeightSetPropertyProxy(this, &weight_set_property);
}

inline const Xfc::Gtk::TextTag::StretchSetPropertyProxy
Xfc::Gtk::TextTag::property_stretch_set()
{
	return StretchSetPropertyProxy(this, &stretch_set_property);
}

inline const Xfc::Gtk::TextTag::SizeSetPropertyProxy
Xfc::Gtk::TextTag::property_size_set()
{
	return SizeSetPropertyProxy(this, &size_set_property);
}

inline const Xfc::Gtk::TextTag::ScaleSetPropertyProxy
Xfc::Gtk::TextTag::property_scale_set()
{
	return ScaleSetPropertyProxy(this, &scale_set_property);
}

inline const Xfc::Gtk::TextTag::JustificationSetPropertyProxy
Xfc::Gtk::TextTag::property_justification_set()
{
	return JustificationSetPropertyProxy(this, &justification_set_property);
}

inline const Xfc::Gtk::TextTag::LanguageSetPropertyProxy
Xfc::Gtk::TextTag::property_language_set()
{
	return LanguageSetPropertyProxy(this, &language_set_property);
}

inline const Xfc::Gtk::TextTag::LeftMarginSetPropertyProxy
Xfc::Gtk::TextTag::property_left_margin_set()
{
	return LeftMarginSetPropertyProxy(this, &left_margin_set_property);
}

inline const Xfc::Gtk::TextTag::IndentSetPropertyProxy
Xfc::Gtk::TextTag::property_indent_set()
{
	return IndentSetPropertyProxy(this, &indent_set_property);
}

inline const Xfc::Gtk::TextTag::RiseSetPropertyProxy
Xfc::Gtk::TextTag::property_rise_set()
{
	return RiseSetPropertyProxy(this, &rise_set_property);
}

inline const Xfc::Gtk::TextTag::PixelsAboveLinesSetPropertyProxy
Xfc::Gtk::TextTag::property_pixels_above_lines_set()
{
	return PixelsAboveLinesSetPropertyProxy(this, &pixels_above_lines_set_property);
}

inline const Xfc::Gtk::TextTag::PixelsBelowLinesSetPropertyProxy
Xfc::Gtk::TextTag::property_pixels_below_lines_set()
{
	return PixelsBelowLinesSetPropertyProxy(this, &pixels_below_lines_set_property);
}

inline const Xfc::Gtk::TextTag::PixelsInsideWrapSetPropertyProxy
Xfc::Gtk::TextTag::property_pixels_inside_wrap_set()
{
	return PixelsInsideWrapSetPropertyProxy(this, &pixels_inside_wrap_set_property);
}

inline const Xfc::Gtk::TextTag::StrikethroughSetPropertyProxy
Xfc::Gtk::TextTag::property_strikethrough_set()
{
	return StrikethroughSetPropertyProxy(this, &strikethrough_set_property);
}

inline const Xfc::Gtk::TextTag::RightMarginSetPropertyProxy
Xfc::Gtk::TextTag::property_right_margin_set()
{
	return RightMarginSetPropertyProxy(this, &right_margin_set_property);
}

inline const Xfc::Gtk::TextTag::UnderlineSetPropertyProxy
Xfc::Gtk::TextTag::property_underline_set()
{
	return UnderlineSetPropertyProxy(this, &underline_set_property);
}

inline const Xfc::Gtk::TextTag::WrapModeSetPropertyProxy
Xfc::Gtk::TextTag::property_wrap_mode_set()
{
	return WrapModeSetPropertyProxy(this, &wrap_mode_set_property);
}

inline const Xfc::Gtk::TextTag::TabsSetPropertyProxy
Xfc::Gtk::TextTag::property_tabs_set()
{
	return TabsSetPropertyProxy(this, &tabs_set_property);
}

inline const Xfc::Gtk::TextTag::InvisibleSetPropertyProxy
Xfc::Gtk::TextTag::property_invisible_set()
{
	return InvisibleSetPropertyProxy(this, &invisible_set_property);
}

inline const Xfc::Gtk::TextTag::EventSignalProxy
Xfc::Gtk::TextTag::signal_event()
{
	return EventSignalProxy(this, &event_signal);
}

/*  Gtk::TextTagTable
 */

inline GtkTextTagTable*
Xfc::Gtk::TextTagTable::gtk_text_tag_table() const
{
	return reinterpret_cast<GtkTextTagTable*>(instance_);
}

inline Xfc::Gtk::TextTagTable::operator GtkTextTagTable* () const
{
	return this ? gtk_text_tag_table() : 0;
}

inline int
Xfc::Gtk::TextTagTable::get_size() const
{
	return gtk_text_tag_table_get_size(gtk_text_tag_table());
}

inline const Xfc::Gtk::TextTagTable::TagChangedSignalProxy
Xfc::Gtk::TextTagTable::signal_tag_changed()
{
	return TagChangedSignalProxy(this, &tag_changed_signal);
}

inline const Xfc::Gtk::TextTagTable::TagAddedSignalProxy
Xfc::Gtk::TextTagTable::signal_tag_added()
{
	return TagAddedSignalProxy(this, &tag_added_signal);
}

inline const Xfc::Gtk::TextTagTable::TagRemovedSignalProxy
Xfc::Gtk::TextTagTable::signal_tag_removed()
{
	return TagRemovedSignalProxy(this, &tag_removed_signal);
}

