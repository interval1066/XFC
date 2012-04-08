/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  renderer.inl - Gtk::AboutDialog inline functions
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

inline PangoRenderer*
Xfc::Pango::Renderer::pango_renderer() const
{
	return reinterpret_cast<PangoRenderer*>(instance_);
}

inline Xfc::Pango::Renderer::operator PangoRenderer* () const
{
	return this ? pango_renderer() : 0;
}

inline void 
Xfc::Pango::Renderer::draw_rectangle(RenderPart part, int  x, int  y, int width, int height)
{
	pango_renderer_draw_rectangle(pango_renderer(), (PangoRenderPart)part, x, y, width, height);
}

inline void 
Xfc::Pango::Renderer::draw_error_underline(int x, int y, int width, int height)
{
	pango_renderer_draw_error_underline(pango_renderer(), x, y, width, height);
}

inline void 
Xfc::Pango::Renderer::draw_trapezoid(RenderPart part, double y1, double x11, double x21, double y2, double x12, double x22)
{
	pango_renderer_draw_trapezoid(pango_renderer(), (PangoRenderPart)part, y1, x11, x21, y2, x12, x22);
}

inline void 
Xfc::Pango::Renderer::activate()
{
	pango_renderer_activate(pango_renderer());
}

inline void 
Xfc::Pango::Renderer::deactivate()
{
	pango_renderer_deactivate(pango_renderer());
}

inline void 
Xfc::Pango::Renderer::part_changed(RenderPart part)
{
	pango_renderer_part_changed(pango_renderer(), (PangoRenderPart)part);
}

