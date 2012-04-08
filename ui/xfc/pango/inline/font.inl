/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  font.inl - Pango::FontDescription, Pango::FontMetrics, Pango::FontFace, Pango::FontFamily and Pango::Font inline functions
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

/*  Pango::FontDescription
 */

inline PangoFontDescription*
Xfc::Pango::FontDescription::pango_font_description() const
{
	return reinterpret_cast<PangoFontDescription*>(boxed_);
}

inline Xfc::Pango::FontDescription::operator PangoFontDescription* () const
{
	return this ? pango_font_description() : 0;
}

inline Xfc::Pango::Style
Xfc::Pango::FontDescription::get_style() const
{
	return (Style)pango_font_description_get_style(pango_font_description());
}

inline Xfc::Pango::Variant
Xfc::Pango::FontDescription::get_variant() const
{
	return (Variant)pango_font_description_get_variant(pango_font_description());
}

inline Xfc::Pango::Weight
Xfc::Pango::FontDescription::get_weight() const
{
	return (Weight)pango_font_description_get_weight(pango_font_description());
}

inline Xfc::Pango::Stretch
Xfc::Pango::FontDescription::get_stretch() const
{
	return (Stretch)pango_font_description_get_stretch(pango_font_description());
}

inline int
Xfc::Pango::FontDescription::get_size() const
{
	return pango_font_description_get_size(pango_font_description());
}

inline bool
Xfc::Pango::FontDescription::get_size_is_absolute() const
{
	return pango_font_description_get_size_is_absolute(pango_font_description());
}

inline Xfc::Pango::FontMaskField
Xfc::Pango::FontDescription::get_set_fields() const
{
	return (FontMaskField)pango_font_description_get_set_fields(pango_font_description());
}

inline unsigned int
Xfc::Pango::FontDescription::hash() const
{
	return pango_font_description_hash(pango_font_description());
}

inline void
Xfc::Pango::FontDescription::set_family(const char *family)
{
	pango_font_description_set_family(pango_font_description(), family);
}

inline void
Xfc::Pango::FontDescription::set_style(Style style)
{
	pango_font_description_set_style(pango_font_description(), (PangoStyle)style);
}

inline void
Xfc::Pango::FontDescription::set_variant(Variant variant)
{
	pango_font_description_set_variant(pango_font_description(), (PangoVariant)variant);
}

inline void
Xfc::Pango::FontDescription::set_weight(Weight weight)
{
	pango_font_description_set_weight(pango_font_description(), (PangoWeight)weight);
}

inline void
Xfc::Pango::FontDescription::set_stretch(Stretch stretch)
{
	pango_font_description_set_stretch(pango_font_description(), (PangoStretch)stretch);
}

inline void
Xfc::Pango::FontDescription::set_size(int size)
{
	pango_font_description_set_size(pango_font_description(), size);
}

inline void 
Xfc::Pango::FontDescription::set_absolute_size(double size)
{	
	pango_font_description_set_absolute_size(pango_font_description(), size);
}

inline void
Xfc::Pango::FontDescription::unset_fields(FontMaskField to_unset)
{
	pango_font_description_unset_fields(pango_font_description(), (PangoFontMask)to_unset);
}

/*  Pango::FontMetrics
 */

inline PangoFontMetrics*
Xfc::Pango::FontMetrics::pango_font_metrics() const
{
	return reinterpret_cast<PangoFontMetrics*>(boxed_);
}

inline Xfc::Pango::FontMetrics::operator PangoFontMetrics* () const
{
	return this ? pango_font_metrics() : 0;
}

inline int
Xfc::Pango::FontMetrics::get_descent() const
{
	return pango_font_metrics_get_descent(pango_font_metrics());
}

inline int
Xfc::Pango::FontMetrics::get_approximate_char_width() const
{
	return pango_font_metrics_get_approximate_char_width(pango_font_metrics());
}

inline int
Xfc::Pango::FontMetrics::get_approximate_digit_width() const
{
	return pango_font_metrics_get_approximate_digit_width(pango_font_metrics());
}

inline int
Xfc::Pango::FontMetrics::get_underline_position() const
{
	return pango_font_metrics_get_underline_position(pango_font_metrics());
}

inline int
Xfc::Pango::FontMetrics::get_underline_thickness() const
{
	return pango_font_metrics_get_underline_thickness(pango_font_metrics());
}

inline int
Xfc::Pango::FontMetrics::get_strikethrough_position() const
{
	return pango_font_metrics_get_strikethrough_position(pango_font_metrics());
}

inline int
Xfc::Pango::FontMetrics::get_strikethrough_thickness() const
{
	return pango_font_metrics_get_strikethrough_thickness(pango_font_metrics());
}

/*  Pango::FontFace
 */

inline PangoFontFace*
Xfc::Pango::FontFace::pango_font_face() const
{
	return reinterpret_cast<PangoFontFace*>(instance_);
}

inline Xfc::Pango::FontFace::operator PangoFontFace* () const
{
	return this ? pango_font_face() : 0;
}

/*  Pango::FontFamily
 */

inline PangoFontFamily*
Xfc::Pango::FontFamily::pango_font_family() const
{
	return reinterpret_cast<PangoFontFamily*>(instance_);
}

inline Xfc::Pango::FontFamily::operator PangoFontFamily* () const
{
	return this ? pango_font_family() : 0;
}

inline bool 
Xfc::Pango::FontFamily::is_monospace() const
{
	return pango_font_family_is_monospace(pango_font_family());
}

/*  Pango::Font
 */

inline PangoFont*
Xfc::Pango::Font::pango_font() const
{
	return reinterpret_cast<PangoFont*>(instance_);
}

inline Xfc::Pango::Font::operator PangoFont* () const
{
	return this ? pango_font() : 0;
}

inline PangoEngineShape*
Xfc::Pango::Font::find_shaper(unsigned int character_code, PangoLanguage *language)
{
	return pango_font_find_shaper(pango_font(), language, character_code);
}

