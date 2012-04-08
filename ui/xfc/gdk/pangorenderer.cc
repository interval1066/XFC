/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  pangorenderer.cc - GdkPangoRenderer C++ wrapper implementation
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
 
#include "pangorenderer.hh"
#include "bitmap.hh"
#include "color.hh"
#include "drawable.hh"
#include "screen.hh"
#include "private/pangorendererclass.hh"

using namespace Xfc;

/*  Gdk::PangoRenderer
 */

Gdk::PangoRenderer::PangoRenderer(GdkPangoRenderer *renderer, bool owns_reference)
: Pango::Renderer((::PangoRenderer*)renderer, owns_reference)
{
}

Gdk::PangoRenderer::PangoRenderer(const Screen& screen)
: Pango::Renderer((::PangoRenderer*)PangoRendererClass::create(screen.gdk_screen()))
{
}

Gdk::PangoRenderer::~PangoRenderer()
{
}

Gdk::PangoRenderer* 
Gdk::PangoRenderer::get_default(const Screen& screen)
{
	return G::Object::wrap<Gdk::PangoRenderer>((GdkPangoRenderer*)gdk_pango_renderer_get_default(screen.gdk_screen()));
}

void 
Gdk::PangoRenderer::set_drawable(Drawable *drawable)
{
	gdk_pango_renderer_set_drawable(gdk_pango_renderer(), *drawable);
}

void 
Gdk::PangoRenderer::set_gc(const GC *gc)
{
	gdk_pango_renderer_set_gc(gdk_pango_renderer(), *gc);
}

void 
Gdk::PangoRenderer::set_stipple(Pango::RenderPart part, Bitmap *stipple)
{
	gdk_pango_renderer_set_stipple(gdk_pango_renderer(), (PangoRenderPart)part, *stipple);
}

void 
Gdk::PangoRenderer::set_override_color(Pango::RenderPart part, const Color *color)
{
	gdk_pango_renderer_set_override_color(gdk_pango_renderer(), (PangoRenderPart)part, *color);
}

/*  Gdk::PangoRendererClass
 */

void
Gdk::PangoRendererClass::init(GdkPangoRendererClass *g_class)
{
	Pango::RendererClass::init((::PangoRendererClass*)g_class);
}

GType
Gdk::PangoRendererClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_PANGO_RENDERER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::PangoRendererClass::create(GdkScreen *screen)
{
	return g_object_new(get_type(), "screen", screen, 0);
}

