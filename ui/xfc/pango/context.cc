/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  context.cc - PangoContext C++ wrapper implementation
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

#include "context.hh"
#include "attributes.hh"
#include "font.hh"
#include "fontmap.hh"
#include "fontset.hh"
#include "item.hh"
#include "../gdk/color.hh"
#include "../gdk/screen.hh"
#include <gdk/gdkpango.h>

using namespace Xfc;

Pango::Context::Context(PangoContext *context, bool owns_reference)
: G::Object((GObject*)context, owns_reference)
{
}

Pango::Context::~Context()
{
}

Pointer<Pango::Context>
Pango::Context::get(const Gdk::Screen *screen)
{
	GdkScreen *tmp_screen = screen ? screen->gdk_screen() : gdk_screen_get_default();
	return G::Object::wrap_new<Context>(gdk_pango_context_get_for_screen(tmp_screen), true);
}

Pango::FontMap* 
Pango::Context::get_font_map() const
{
	return G::Object::wrap<FontMap>(pango_context_get_font_map(pango_context()));
}

Pointer<Pango::FontMetrics>
Pango::Context::get_metrics(const FontDescription& desc, PangoLanguage *language) const
{
	PangoFontMetrics *metrics = pango_context_get_metrics(pango_context(), desc.pango_font_description(), language);
	return G::Boxed::wrap<FontMetrics>(PANGO_TYPE_FONT_METRICS, metrics, true);
}

Pointer<Pango::FontDescription>
Pango::Context::get_font_description() const
{
	return G::Boxed::wrap<FontDescription>(PANGO_TYPE_FONT_DESCRIPTION, pango_context_get_font_description(pango_context()));
}
	
Pointer<Pango::Matrix> 
Pango::Context::get_matrix() const
{
	return G::Boxed::wrap<Matrix>(PANGO_TYPE_MATRIX, (PangoMatrix*)pango_context_get_matrix(pango_context()));
}

bool
Pango::Context::list_families(std::vector<FontFamily*>& families) const
{
	g_return_val_if_fail(families.empty(), false);
	PangoFontFamily **tmp_families = 0;
	int count = 0;
	pango_context_list_families(pango_context(), &tmp_families, &count);
	families.reserve(count);

	int i = 0;
	while (i < count)
	{
		families.push_back(G::Object::wrap<FontFamily>(tmp_families[i]));
		g_free(tmp_families[i]);
		++i;
	}

 	g_free(tmp_families);
	return !families.empty();
}

Pango::Font*
Pango::Context::load_font(const FontDescription& desc) const
{
	return G::Object::wrap<Font>(pango_context_load_font(pango_context(), desc.pango_font_description()));
}

Pango::Fontset*
Pango::Context::load_fontset(const FontDescription& desc, PangoLanguage *language) const
{
	return G::Object::wrap<Fontset>(pango_context_load_fontset(pango_context(), desc.pango_font_description(), language));
}

void
Pango::Context::set_font_description(const FontDescription& desc)
{
	pango_context_set_font_description(pango_context(), desc.pango_font_description());
}

void 
Pango::Context::set_matrix(const Matrix *matrix)
{
	pango_context_set_matrix(pango_context(), *matrix);
}

std::vector<Pointer<Pango::Item> >
Pango::Context::itemize(const String& text, const AttrList& attrs, AttrIterator *cached_iter) const
{
	return itemize(get_base_dir(), text.c_str(), 0, text.size(), attrs, cached_iter);
}

std::vector<Pointer<Pango::Item> >
Pango::Context::itemize(const char *text, int start_index, int length, const AttrList& attrs, AttrIterator *cached_iter) const
{
	return itemize(get_base_dir(), text, start_index, length, attrs, cached_iter);
}


std::vector<Pointer<Pango::Item> >
Pango::Context::itemize(Direction direction, const String& text, const AttrList& attrs, AttrIterator *cached_iter) const
{
	return itemize(direction, text.c_str(), 0, text.size(), attrs, cached_iter);
}

std::vector<Pointer<Pango::Item> >
Pango::Context::itemize(Direction direction, const char *text, int start_index, int length, 
                        const AttrList& attrs, AttrIterator *cached_iter) const
{
	GList *first = pango_itemize_with_base_dir(pango_context(), (PangoDirection)direction, text, start_index,
	                                           length, attrs.pango_attr_list(), *cached_iter);
	GList *next = first;
	std::vector<Pointer<Item> > items;

	while (next)
	{
		Pointer<Item> item(new Item((PangoItem*)next->data, false));
		items.push_back(item);
		next = g_list_next(next);
	}

	g_list_free(first);
	return items;
}

void
Pango::Context::set_colormap(const Gdk::Colormap& colormap)
{
	gdk_pango_context_set_colormap(pango_context(), colormap.gdk_colormap());
}

