/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  glyph.cc - PangoGlyphString C++ wrapper implementation
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
 
#include "glyph.hh"
#include "font.hh"
#include "types.hh"
#include "item.hh"
#include <cstring>

using namespace Xfc;

/*  Pango::GlyphInfo
 */

const Pango::GlyphGeometry&
Pango::GlyphInfo::geometry() const
{
	return reinterpret_cast<const GlyphGeometry&>(info_.geometry);
}

const Pango::GlyphVisAttr&
Pango::GlyphInfo::attr() const
{
	return reinterpret_cast<const GlyphVisAttr&>(info_.attr);
}

/*  Pango::GlyphString
 */

Pango::GlyphString::GlyphString()
: G::Boxed(PANGO_TYPE_GLYPH_STRING, pango_glyph_string_new(), false)
{
}

Pango::GlyphString::GlyphString(const char *text, int length, const Analysis& analysis)
: G::Boxed(PANGO_TYPE_GLYPH_STRING, pango_glyph_string_new(), false)
{
	pango_shape(text, length, analysis.pango_analysis(), pango_glyph_string());
}

Pango::GlyphString::GlyphString(const String& text, const Analysis& analysis)
: G::Boxed(PANGO_TYPE_GLYPH_STRING, pango_glyph_string_new(), false)
{
	pango_shape(text.c_str(), text.size(), analysis.pango_analysis(), pango_glyph_string());
}

Pango::GlyphString::GlyphString(PangoGlyphString *string)
: G::Boxed(PANGO_TYPE_GLYPH_STRING, string)
{
}

Pango::GlyphString::GlyphString(PangoGlyphString *string, bool copy)
: G::Boxed(PANGO_TYPE_GLYPH_STRING, string, copy)
{
}

Pango::GlyphString::GlyphString(const GlyphString& src)
: G::Boxed(PANGO_TYPE_GLYPH_STRING, src.g_boxed(), true)
{
}

Pango::GlyphString::~GlyphString()
{
}

Pango::GlyphString&
Pango::GlyphString::operator=(const GlyphString& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

std::vector<Pango::GlyphInfo>
Pango::GlyphString::glyphs() const
{
	int count = size();
	std::vector<GlyphInfo> tmp_glyphs(count);
	GlyphInfo *mem = &tmp_glyphs[0];
	memcpy((void*)mem, (void*)pango_glyph_string()->glyphs, sizeof(PangoGlyphInfo) * count);
	return tmp_glyphs;
}

void
Pango::GlyphString::extents(const Font& font, Rectangle *ink_rect, Rectangle *logical_rect, int start, int end) const
{
	pango_glyph_string_extents_range(pango_glyph_string(), start, (end == -1) ? size() : end,
	                                 font.pango_font(), *ink_rect, *logical_rect);
}

void
Pango::GlyphString::get_logical_widths(const char *text, int length, int embedding_level, std::vector<int>& logical_widths) const
{
	logical_widths.reserve(length);
	pango_glyph_string_get_logical_widths(pango_glyph_string(), text, length, embedding_level, &logical_widths[0]);
	logical_widths.resize(length);
}

void
Pango::GlyphString::get_logical_widths(const String& text, int embedding_level, std::vector<int>& logical_widths) const
{
	get_logical_widths(text.c_str(), text.size(), embedding_level, logical_widths);
}

int
Pango::GlyphString::index_to_x(const char *text, int length, const Analysis& analysis, int index, bool trailing)
{
	int x_pos;
	pango_glyph_string_index_to_x(pango_glyph_string(), const_cast<char*>(text), length,
	                              analysis.pango_analysis(), index, trailing, &x_pos);
	return x_pos;
}

int
Pango::GlyphString::index_to_x(const String& text, const Analysis& analysis, int index, bool trailing)
{
	return index_to_x(text.c_str(), text.size(), analysis, index, trailing);
}

void
Pango::GlyphString::x_to_index(const char *text, int length, const Analysis& analysis, int x_pos, int *index, bool *trailing)
{
	pango_glyph_string_x_to_index(pango_glyph_string(), const_cast<char*>(text), length,
	                              analysis.pango_analysis(), x_pos, index, (gboolean*)trailing);
}

void
Pango::GlyphString::x_to_index(const String& text, const Analysis& analysis, int x_pos, int *index, bool *trailing)
{
	x_to_index(text.c_str(), text.size(), analysis, x_pos, index, trailing);
}

