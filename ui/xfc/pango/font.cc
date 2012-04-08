/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  font.cc - PangoFontDescription, PangoFontMetrics, PangoFontFace, PangoFontFamily and PangoFont C++ wrapper implementation
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
 
#include "font.hh"
#include "coverage.hh"

using namespace Xfc;

/*  Pango::FontDescription
 */

Pango::FontDescription::FontDescription()
: G::Boxed(PANGO_TYPE_FONT_DESCRIPTION, pango_font_description_new(), false)
{
}

Pango::FontDescription::FontDescription(const String& desc)
: G::Boxed(PANGO_TYPE_FONT_DESCRIPTION, pango_font_description_from_string(desc.c_str()), false)
{
}

Pango::FontDescription::FontDescription(const String& family, int size, Style style, Weight weight)
: G::Boxed(PANGO_TYPE_FONT_DESCRIPTION, pango_font_description_new(), false)
{
	set_family(family);
	set_size(size);
	set_style(style);
	set_weight(weight);
}

Pango::FontDescription::FontDescription(PangoFontDescription *desc)
: G::Boxed(PANGO_TYPE_FONT_DESCRIPTION, desc)
{
}

Pango::FontDescription::FontDescription(PangoFontDescription *desc, bool copy)
: G::Boxed(PANGO_TYPE_FONT_DESCRIPTION, desc, copy)
{
}

Pango::FontDescription::FontDescription(const FontDescription& src)
: G::Boxed(PANGO_TYPE_FONT_DESCRIPTION, src.g_boxed(), true)
{
}

Pango::FontDescription::~FontDescription() 
{
}

Pango::FontDescription&
Pango::FontDescription::operator=(const FontDescription& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

String
Pango::FontDescription::get_family() const
{
	return pango_font_description_get_family(pango_font_description());
}

bool
Pango::FontDescription::equal(const FontDescription& other) const
{
	return pango_font_description_equal(pango_font_description(), other.pango_font_description());
}

bool
Pango::FontDescription::operator==(const FontDescription& other) const
{
	return equal(other);
}

bool
Pango::FontDescription::operator!=(const FontDescription& other) const
{
	return !equal(other);
}

String
Pango::FontDescription::to_string() const
{
	return pango_font_description_to_string(pango_font_description());
}

String
Pango::FontDescription::to_filename() const 
{
	return pango_font_description_to_filename(pango_font_description());
}

void
Pango::FontDescription::set_family(const String& family)
{
	pango_font_description_set_family(pango_font_description(), family.c_str());
}

void
Pango::FontDescription::merge(const FontDescription& desc_to_merge, bool replace_existing)
{
	pango_font_description_merge(pango_font_description(), desc_to_merge.pango_font_description(), replace_existing);
}

bool
Pango::FontDescription::better_match(const FontDescription& new_match, const FontDescription *old_match) const
{
	return pango_font_description_better_match(pango_font_description(), *old_match, new_match.pango_font_description());
}

/*  Pango::FontMetrics
 */
 
Pango::FontMetrics::FontMetrics(PangoFontMetrics *metrics)
: G::Boxed(PANGO_TYPE_FONT_METRICS, metrics)
{
}

Pango::FontMetrics::FontMetrics(PangoFontMetrics *metrics, bool copy)
: G::Boxed(PANGO_TYPE_FONT_METRICS, metrics, copy)
{
}

Pango::FontMetrics::FontMetrics(const FontMetrics& src)
: G::Boxed(PANGO_TYPE_FONT_METRICS, src.g_boxed(), true)
{
}

Pango::FontMetrics::~FontMetrics()
{
}

Pango::FontMetrics&
Pango::FontMetrics::operator=(const FontMetrics& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

int
Pango::FontMetrics::get_ascent() const
{
	return pango_font_metrics_get_ascent(pango_font_metrics());
}

/*  Pango::FontFace
 */
 
Pango::FontFace::FontFace(PangoFontFace *face, bool owns_reference)
: G::Object((GObject*)face, owns_reference)
{
}

Pango::FontFace::~FontFace()
{
}

Pointer<Pango::FontDescription>
Pango::FontFace::describe() const
{
	return G::Boxed::wrap<FontDescription>(PANGO_TYPE_FONT_DESCRIPTION, pango_font_face_describe(pango_font_face()), false);
}

String
Pango::FontFace::get_face_name() const
{
	return pango_font_face_get_face_name(pango_font_face());
}

bool 
Pango::FontFace::list_sizes(std::vector<int>& sizes) const
{
	g_return_val_if_fail(sizes.empty(), false);
	int *tmp_sizes = 0;
	int count = 0;
	pango_font_face_list_sizes(pango_font_face(), &tmp_sizes, &count);
	sizes.reserve(count);	

	int i = 0;
	while (i < count)
	{
		sizes.push_back(tmp_sizes[i]);
		++i;
	}

	g_free(tmp_sizes);
	return !sizes.empty();
}

/*  Pango::FontFamily
 */
 
Pango::FontFamily::FontFamily(PangoFontFamily *family, bool owns_reference)
: G::Object((GObject*)family, owns_reference)
{
}

Pango::FontFamily::~FontFamily()
{
}

String
Pango::FontFamily::get_name() const
{
	return pango_font_family_get_name(pango_font_family());
}

bool
Pango::FontFamily::list_faces(std::vector<FontFace*>& faces) const
{
	g_return_val_if_fail(faces.empty(), false);
	PangoFontFace **tmp_faces = 0;
	int count = 0;
	pango_font_family_list_faces(pango_font_family(), &tmp_faces, &count);
	faces.reserve(count);	

	int i = 0;
	while (i < count)
	{
		faces.push_back(G::Object::wrap<FontFace>(tmp_faces[i]));
		++i;
	}

	g_free(tmp_faces);
	return !faces.empty();
}

/*  Pango::Font
 */

Pango::Font::Font(PangoFont *font, bool owns_reference)
: G::Object((GObject*)font, owns_reference)
{
}
	
Pango::Font::~Font()
{
}
	
Pointer<Pango::FontDescription>
Pango::Font::describe() const
{
	return G::Boxed::wrap<FontDescription>(PANGO_TYPE_FONT_DESCRIPTION, pango_font_describe(pango_font()), false);
}

Pointer<Pango::Coverage>
Pango::Font::get_coverage(PangoLanguage *language) const
{
	return new Coverage(pango_font_get_coverage(pango_font(), language));
}

Pointer<Pango::FontMetrics>
Pango::Font::get_metrics(PangoLanguage *language) const
{
	return G::Boxed::wrap<FontMetrics>(PANGO_TYPE_FONT_METRICS, pango_font_get_metrics(pango_font(), language), false);
}

void 
Pango::Font::get_glyph_extents(Glyph glyph, Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_font_get_glyph_extents(pango_font(), glyph, *ink_rect, *logical_rect);
}

