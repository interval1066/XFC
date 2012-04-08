/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  renderer.cc - PangoRenderer C++ wrapper implementation
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
 
#include "renderer.hh"
#include "glyph.hh"
#include "layout.hh"
#include "private/rendererclass.hh"

using namespace Xfc;

/*  Pango::Renderer
 */

Pango::Renderer::Renderer(PangoRenderer *renderer, bool owns_reference)
: G::Object((GObject*)renderer, owns_reference)
{
}

Pango::Renderer::~Renderer()
{
}

Pointer<Pango::Color> 
Pango::Renderer::get_color(RenderPart part) const
{
	PangoColor *color = pango_renderer_get_color(pango_renderer(), (PangoRenderPart)part);
	return color ? G::Boxed::wrap<Color>(PANGO_TYPE_COLOR, color) : 0;
}
 
Pango::Matrix 
Pango::Renderer::get_matrix() const
{
	return Matrix((PangoMatrix*)pango_renderer_get_matrix(pango_renderer()));
}
	
void 
Pango::Renderer::draw_layout(const Layout& layout, int x, int y)
{
	pango_renderer_draw_layout(pango_renderer(), layout.pango_layout(), x, y);
}

void 
Pango::Renderer::draw_layout_line(const LayoutLine& line, int x, int y)
{
	pango_renderer_draw_layout_line(pango_renderer(), line.pango_layout_line(), x, y);
}

void 
Pango::Renderer::draw_glyphs(const Font& font, const GlyphString& glyphs, int x, int y)
{
	pango_renderer_draw_glyphs(pango_renderer(), font.pango_font(), glyphs.pango_glyph_string(), x, y);
}

void 
Pango::Renderer::draw_rectangle(RenderPart part, const Rectangle& rectangle)
{
	draw_rectangle(part, rectangle.x(), rectangle.y(), rectangle.width(), rectangle.height());
}

void 
Pango::Renderer::draw_glyph(const Font& font, Glyph glyph, double x, double y)
{
	pango_renderer_draw_glyph(pango_renderer(), font.pango_font(), glyph, x, y);
}

void 
Pango::Renderer::set_color(RenderPart part, const Color *color)
{
	pango_renderer_set_color(pango_renderer(), (PangoRenderPart)part, *color);
}
	
void 
Pango::Renderer::set_matrix(const Matrix *matrix)
{
	pango_renderer_set_matrix(pango_renderer(), *matrix);
}

/*  Pango::RendererClass
 */

void
Pango::RendererClass::init(PangoRendererClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Pango::RendererClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(PANGO_TYPE_RENDERER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Pango::RendererClass::create()
{
	return g_object_new(get_type(), 0);
}

