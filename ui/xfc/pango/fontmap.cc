/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  fontmap.cc - PangoFontMap C++ wrapper implementation
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
 
#include "fontmap.hh"
#include "context.hh"
#include "font.hh"
#include "fontset.hh"

using namespace Xfc;

/*  Pango::FontMap
 */

Pango::FontMap::FontMap(PangoFontMap *fontmap, bool owns_reference)
: G::Object((GObject*)fontmap, owns_reference)
{
}

Pango::FontMap::~FontMap()
{
}

Pango::Font*
Pango::FontMap::load_font(Context *context, const FontDescription& desc)
{
	PangoFont *font = pango_font_map_load_font(pango_font_map(), *context, desc.pango_font_description());
	return font ? G::Object::wrap_new<Font>(font) : 0;
}

Pango::Fontset*
Pango::FontMap::load_fontset(Context *context, const FontDescription& desc, PangoLanguage *language)
{
	PangoFontset *fontset = pango_font_map_load_fontset(pango_font_map(), *context, desc.pango_font_description(), language);
	return fontset ? G::Object::wrap_new<Fontset>(fontset) : 0;
}

bool
Pango::FontMap::list_families(std::vector<FontFamily* >& families) const
{
	g_return_val_if_fail(families.empty(), false);
	PangoFontFamily **tmp_families = 0;
	int count = 0;
	pango_font_map_list_families(pango_font_map(), &tmp_families, &count);
	families.reserve(count);

	int i = 0;
	while (i < count)
	{
		families.push_back(G::Object::wrap<FontFamily>(tmp_families[i]));
		++i;
	}

	g_free(tmp_families);
	return !families.empty();
}

