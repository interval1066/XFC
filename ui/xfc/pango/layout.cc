/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  layout.cc - PangoLayout C++ wrapper implementation
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
 
#include "layout.hh"
#include "break.hh"
#include "glyph.hh"
#include "types.hh"
#include "../gdk/region.hh"
#include <gdk/gdkpango.h>
#include <cstring>

using namespace Xfc;

/*  Pango::LayoutRun
 */

Pointer<Pango::Item>
Pango::LayoutRun::item() const
{
	return new Item(run_.item, true);
}

Pointer<Pango::GlyphString>
Pango::LayoutRun::glyphs() const
{
	return G::Boxed::wrap<GlyphString>(PANGO_TYPE_GLYPH_STRING, run_.glyphs);
}

/*  Pango::LayoutLine
 */

Pango::LayoutLine::LayoutLine(PangoLayoutLine *layout_line)
: layout_line_(layout_line)
{
	if (layout_line_)
		pango_layout_line_ref(layout_line_);
}

Pango::LayoutLine::LayoutLine(const LayoutLine& src)
: layout_line_(src.pango_layout_line())
{
	if (layout_line_)
		pango_layout_line_ref(layout_line_);
}

Pango::LayoutLine::~LayoutLine()
{
	if (layout_line_)
	{
		pango_layout_line_unref(layout_line_);
		layout_line_ = 0;
	}
}

Pango::LayoutLine&
Pango::LayoutLine::operator=(const LayoutLine& src)
{
	if (src.layout_line_ == layout_line_)
		return *this;

	if (layout_line_)
		pango_layout_line_unref(layout_line_);

	layout_line_ = src.layout_line_;

	if (layout_line_)
		pango_layout_line_ref(layout_line_);
	return *this;
}

std::vector<std::pair<int, int> >
Pango::LayoutLine::get_x_ranges(int start_index, int end_index) const
{
	int *tmp_ranges = 0;
	int count = 0;
	pango_layout_line_get_x_ranges(pango_layout_line(), start_index, end_index, &tmp_ranges, &count);

	int *p = tmp_ranges;
	count /= 2;
	
	typedef std::pair<int, int> Range;
	std::vector<Range> ranges(count);
	
	for (int i = 0; i < count; i++)
	{
		ranges[i] = Range(*p, *(p + 1));
		p += 2;
	}

	g_free(tmp_ranges);
	return ranges;
}

void 
Pango::LayoutLine::get_extents(Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_layout_line_get_extents(pango_layout_line(), *ink_rect, *logical_rect);
}

void 
Pango::LayoutLine::get_pixel_extents(Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_layout_line_get_pixel_extents(pango_layout_line(), *ink_rect, *logical_rect);
}

Pointer<Gdk::Region>
Pango::LayoutLine::get_clip_region(int x_origin, int y_origin, const std::vector<std::pair<int, int> >& index_ranges) const
{
	int *tmp = reinterpret_cast<int*>(const_cast<std::pair<int, int>*>(&index_ranges[0]));	
	return new Gdk::Region(gdk_pango_layout_line_get_clip_region(pango_layout_line(), x_origin, y_origin, tmp, index_ranges.size()), false);
}

int
Pango::LayoutLine::index_to_x(int index, bool trailing)
{
	int x_pos;
	pango_layout_line_index_to_x(pango_layout_line(), index, trailing, &x_pos);
	return x_pos;
}

/*  Pango::LayoutIter
 */

Pango::LayoutIter::LayoutIter(PangoLayoutIter *iter)
: G::Boxed(PANGO_TYPE_LAYOUT_ITER, iter)
{
}

Pango::LayoutIter::LayoutIter(PangoLayoutIter *iter, bool copy)
: G::Boxed(PANGO_TYPE_LAYOUT_ITER, iter, copy)
{
}

Pango::LayoutIter::LayoutIter(const LayoutIter& src)
: G::Boxed(PANGO_TYPE_LAYOUT_ITER, src.g_boxed(), true)
{
}

Pango::LayoutIter::~LayoutIter()
{
}

Pango::LayoutIter&
Pango::LayoutIter::operator=(const LayoutIter& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

Pango::LayoutRun*
Pango::LayoutIter::get_run() const
{
	return reinterpret_cast<LayoutRun*>(pango_layout_iter_get_run(pango_layout_iter()));
}

Pointer<Pango::LayoutLine>
Pango::LayoutIter::get_line() const
{
	return new LayoutLine(pango_layout_iter_get_line(pango_layout_iter()));
}

void
Pango::LayoutIter::get_char_extents(Rectangle& logical_rect) const
{
	pango_layout_iter_get_char_extents(pango_layout_iter(), logical_rect.pango_rectangle());
}

Pango::Rectangle
Pango::LayoutIter::get_char_extents() const
{
	PangoRectangle rectangle;
	pango_layout_iter_get_char_extents(pango_layout_iter(), &rectangle);
	return rectangle;
}

void
Pango::LayoutIter::get_cluster_extents(Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_layout_iter_get_cluster_extents(pango_layout_iter(), *ink_rect, *logical_rect);
}

void 
Pango::LayoutIter::get_run_extents(Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_layout_iter_get_run_extents(pango_layout_iter(), *ink_rect, *logical_rect);
}

void 
Pango::LayoutIter::get_line_extents(Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_layout_iter_get_line_extents(pango_layout_iter(), *ink_rect, *logical_rect);
}

void
Pango::LayoutIter::get_layout_extents(Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_layout_iter_get_layout_extents(pango_layout_iter(), *ink_rect, *logical_rect);
}

/*  Pango::Layout
 */

Pango::Layout::Layout(PangoLayout *layout, bool owns_reference)
: G::Object((GObject*)layout, owns_reference)
{
}

Pango::Layout::Layout(const Context& context)
: G::Object((GObject*)pango_layout_new(context.pango_context()))
{
}

Pango::Layout::~Layout()
{
}

Pango::Context*
Pango::Layout::get_context() const
{
	return G::Object::wrap<Context>(pango_layout_get_context(pango_layout()));
}

Pango::AttrList*
Pango::Layout::get_attributes() const
{
	return G::Boxed::wrap<AttrList>(PANGO_TYPE_ATTR_LIST, pango_layout_get_attributes(pango_layout()));
}

String
Pango::Layout::get_text() const
{
	return pango_layout_get_text(pango_layout());
}

Pointer<Pango::FontDescription> 
Pango::Layout::get_font_description() const
{
	PangoFontDescription *desc = const_cast<PangoFontDescription*>(pango_layout_get_font_description(pango_layout()));
	return desc ? G::Boxed::wrap<FontDescription>(PANGO_TYPE_FONT_DESCRIPTION, desc) : 0;
}

Pointer<Pango::TabArray>
Pango::Layout::get_tabs() const
{
	PangoTabArray *tabs = pango_layout_get_tabs(pango_layout());
	return tabs ? G::Boxed::wrap<TabArray>(PANGO_TYPE_TAB_ARRAY, tabs, false) : 0;
}

bool
Pango::Layout::get_logical_attributes(std::vector<LogAttr>& attrs) const
{
	g_return_val_if_fail(attrs.empty(), false);
	PangoLogAttr *tmp_attrs = 0;
	int count = 0;
	pango_layout_get_log_attrs(pango_layout(), &tmp_attrs, &count);
	attrs.reserve(count);
	LogAttr *mem = &attrs[0];
	memcpy((void*)mem, (void*)tmp_attrs, sizeof(PangoLogAttr) * count);
	attrs.resize(count);
	g_free(tmp_attrs);
	return !attrs.empty();
}

void
Pango::Layout::get_cursor_pos(int index, Rectangle *strong_pos, Rectangle *weak_pos) const
{
	pango_layout_get_cursor_pos(pango_layout(), index, *strong_pos, *weak_pos);
}

void
Pango::Layout::get_extents(Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_layout_get_extents(pango_layout(), *ink_rect, *logical_rect);
}

void
Pango::Layout::get_pixel_extents(Rectangle *ink_rect, Rectangle *logical_rect) const
{
	pango_layout_get_pixel_extents(pango_layout(), *ink_rect, *logical_rect);
}

Pointer<Pango::LayoutLine>
Pango::Layout::get_line(int line) const
{
	PangoLayoutLine *layout_line = pango_layout_get_line(pango_layout(), line);
	return layout_line ? new LayoutLine(layout_line) : 0;
}

bool
Pango::Layout::get_lines(std::vector<Pointer<LayoutLine> >& lines) const
{
	g_return_val_if_fail(lines.empty(), false);
	GSList *first = pango_layout_get_lines(pango_layout());
	GSList *next = first;

	while (next)
	{
		Pointer<LayoutLine> line(new LayoutLine((PangoLayoutLine*)next->data));
		lines.push_back(line);
		next = g_slist_next(next);
	}
	return !lines.empty();
}

Pointer<Pango::LayoutIter>
Pango::Layout::get_iter() const
{
	return new LayoutIter(pango_layout_get_iter(pango_layout()));
}

Pointer<Gdk::Region>
Pango::Layout::get_clip_region(int x_origin, int y_origin, const std::vector<std::pair<int, int> >& index_ranges) const
{
	int *tmp = reinterpret_cast<int*>(const_cast<std::pair<int, int>*>(&index_ranges[0]));	
	return new Gdk::Region(gdk_pango_layout_get_clip_region(pango_layout(),  x_origin, y_origin, tmp, index_ranges.size()), false);
}

void
Pango::Layout::set_attributes(AttrList& attrs)
{
	pango_layout_set_attributes(pango_layout(), attrs.pango_attr_list());
}

void
Pango::Layout::set_text(const String& text)
{
	pango_layout_set_text(pango_layout(), text.c_str(), text.size());
}

void
Pango::Layout::set_markup(const String& markup)
{
	pango_layout_set_markup(pango_layout(), markup.c_str(), markup.size());
}

void
Pango::Layout::set_markup(const String& markup, gunichar accel_marker, gunichar *accel_char)
{
	pango_layout_set_markup_with_accel(pango_layout(), markup.c_str(), markup.size(), accel_marker, accel_char);
}

void
Pango::Layout::set_font_description(const FontDescription *desc)
{	
	pango_layout_set_font_description(pango_layout(), *desc);
}

void
Pango::Layout::set_tabs(TabArray *tabs)
{
	pango_layout_set_tabs(pango_layout(), *tabs);
}

void
Pango::Layout::index_to_pos(int index, Rectangle& pos)
{
	pango_layout_index_to_pos(pango_layout(), index, pos.pango_rectangle());
}

void 
Pango::Layout::move_cursor_visually(bool strong, int old_index, int old_trailing, int direction, int *new_index, int *new_trailing)
{
	pango_layout_move_cursor_visually(pango_layout(), strong, old_index, old_trailing, direction, new_index, new_trailing);
}

