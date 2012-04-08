/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  drawable.cc - GdkDrawable C++ wrapper implementation
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
 
#include "drawable.hh"
#include "color.hh"
#include "display.hh"
#include "gc.hh"
#include "image.hh"
#include "region.hh"
#include "screen.hh"
#include "visual.hh"
#include "private/drawableclass.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include "../pango/font.hh"
#include "../pango/glyph.hh"
#include "../pango/layout.hh"
#include <gdk/gdkpixbuf.h>

using namespace Xfc;

/*  Gdk::Drawable
 */

Gdk::Drawable::Drawable(GdkDrawable *drawable, bool reference)
: G::Object((GObject*)drawable, reference)
{
}

Gdk::Drawable::~Drawable()
{
}

void
Gdk::Drawable::get_size(int *width, int *height) const
{
	gdk_drawable_get_size(gdk_drawable(), width, height);
}

Gdk::Colormap*
Gdk::Drawable::get_colormap() const
{
	GdkColormap *colormap = gdk_drawable_get_colormap(gdk_drawable());
	return colormap ? G::Object::wrap<Colormap>(colormap) : 0;
}

const Gdk::Visual*
Gdk::Drawable::get_visual() const
{
	return G::Object::wrap<Visual>(gdk_drawable_get_visual(gdk_drawable()));
}

Gdk::Screen*
Gdk::Drawable::get_screen() const
{
	return G::Object::wrap<Screen>(gdk_drawable_get_screen(gdk_drawable()));
}

Gdk::Display*
Gdk::Drawable::get_display() const
{
	return G::Object::wrap<Display>(gdk_drawable_get_display(gdk_drawable()));
}

Pointer<Gdk::Image>
Gdk::Drawable::get_image(int x, int y, int width, int height) const
{
	return G::Object::wrap_new<Image>(gdk_drawable_get_image(gdk_drawable(), x, y, width, height), true);
}
	
Pointer<Gdk::Region>
Gdk::Drawable::get_clip_region() const
{
	return new Region(gdk_drawable_get_clip_region(gdk_drawable()), false);
}

Pointer<Gdk::Region>
Gdk::Drawable::get_visible_region() const
{
	return new Region(gdk_drawable_get_visible_region(gdk_drawable()), false);
}

Pointer<Gdk::Pixbuf>
Gdk::Drawable::get_pixbuf(int x, int y, int width, int height, Colormap *colormap) const
{
	GdkPixbuf *pixbuf = gdk_pixbuf_get_from_drawable(0, gdk_drawable(), *colormap, x, y, 0, 0, width, height);
	return pixbuf ? G::Object::wrap_new<Pixbuf>(pixbuf, true) : 0;
}
	
void 
Gdk::Drawable::set_colormap(Colormap *colormap)
{
	gdk_drawable_set_colormap(gdk_drawable(), colormap->gdk_colormap());
}

void
Gdk::Drawable::copy_to_image(Image& image, int src_x, int src_y, int dest_x, int dest_y, int width, int height)
{
	gdk_drawable_copy_to_image(gdk_drawable(), image.gdk_image(), src_x, src_y, dest_x, dest_y, width, height);
}

void
Gdk::Drawable::copy_to_image(Image& image, const Rectangle& src_rect, int dest_x, int dest_y)
{
	gdk_drawable_copy_to_image(gdk_drawable(), image.gdk_image(), src_rect.x(), src_rect.y(),
	                           dest_x, dest_y, src_rect.width(), src_rect.height());
}

void
Gdk::Drawable::draw_polygon(const GC& gc, const std::vector<Point>& points, bool filled)
{
	g_return_if_fail(!points.empty());

	int count = points.size();
	GdkPoint *tmp_points = new GdkPoint[count];
	
	int i = 0;
	while (i < count)
	{
		tmp_points[i] = *points[i].gdk_point();
		++i;
	}
	
	gdk_draw_polygon(gdk_drawable(), gc.gdk_gc(), filled, tmp_points, count);
	delete [] tmp_points;
}		 

namespace {

void draw_point_array(GdkDrawable *drawable, GdkGC *gc, const std::vector<Gdk::Point>& points, bool draw_as_points)
{
	g_return_if_fail(!points.empty());

	int count = points.size();
	GdkPoint *tmp_points = new GdkPoint[count];
	
	int i = 0;
	while (i < count)
	{
		tmp_points[i] = *points[i].gdk_point();
		++i;
	}
	
	(draw_as_points ? gdk_draw_points : gdk_draw_lines)(drawable, gc, tmp_points, count);
	delete [] tmp_points;
}

} // namespace
	
void 
Gdk::Drawable::draw_points(const GC& gc, const std::vector<Gdk::Point>& points)
{
	draw_point_array(gdk_drawable(), gc.gdk_gc(), points, true);
}

void 
Gdk::Drawable::draw_segments(const GC& gc, const std::vector<Gdk::Segment>& segs)
{	
	g_return_if_fail(!segs.empty());

	int count = segs.size();
	GdkSegment *tmp_segs = new GdkSegment[count];
	
	int i = 0;
	while (i < count)
	{
		tmp_segs[i] = *segs[i].gdk_segment();
		++i;
	}

	gdk_draw_segments(gdk_drawable(), gc.gdk_gc(), tmp_segs, count);
	delete [] tmp_segs;
}

void 
Gdk::Drawable::draw_lines(const GC& gc, const std::vector<Gdk::Point>& points)
{	
	draw_point_array(gdk_drawable(), gc.gdk_gc(), points, false);
}

void 
Gdk::Drawable::draw_pixbuf(const GC *gc, const Pixbuf& pixbuf, int src_x, int src_y, int dest_x, int dest_y,
                           int width, int height, RgbDither dither, int x_dither, int y_dither)
{
	gdk_draw_pixbuf(gdk_drawable(), *gc, pixbuf.gdk_pixbuf(), src_x, src_y,
	                dest_x, dest_y, width, height, (GdkRgbDither)dither, x_dither, y_dither);
}

void
Gdk::Drawable::draw_point(const GC& gc, int x, int y)
{
	gdk_draw_point(gdk_drawable(), gc.gdk_gc(), x, y);
}

void 
Gdk::Drawable::draw_point(const GC& gc, const Point& point)
{
	gdk_draw_point(gdk_drawable(), gc.gdk_gc(), point.x(), point.y());
}

void 
Gdk::Drawable::draw_line(const GC& gc, int x1, int y1, int x2, int y2)
{
	gdk_draw_line(gdk_drawable(), gc.gdk_gc(), x1, y1, x2, y2);
}

void 
Gdk::Drawable::draw_line(const GC& gc, const Segment& seg)
{
	gdk_draw_line(gdk_drawable(), gc.gdk_gc(), seg.x1(), seg.y1(), seg.x2(), seg.y2());
}

void 
Gdk::Drawable::draw_rectangle(const GC& gc, int x, int y, int width, int height, bool filled)
{
	gdk_draw_rectangle(gdk_drawable(), gc.gdk_gc(), filled, x, y, width, height);
}

void 
Gdk::Drawable::draw_rectangle(const GC& gc, const Rectangle& rectangle, bool filled)
{
	gdk_draw_rectangle(gdk_drawable(), gc.gdk_gc(), filled, rectangle.x(), rectangle.y(), 
	                   rectangle.width(), rectangle.height());
}

void 
Gdk::Drawable::draw_arc(const GC& gc, int x, int y, int width, int height, int angle1, int angle2, bool filled)
{
	gdk_draw_arc(gdk_drawable(), gc.gdk_gc(), filled, x, y, width, height, angle1, angle2);
}

void 
Gdk::Drawable::draw_arc(const GC& gc, const Rectangle& rectangle, int angle1, int angle2, bool filled)
{
	gdk_draw_arc(gdk_drawable(), gc.gdk_gc(), filled, rectangle.x(), rectangle.y(), 
	             rectangle.width(), rectangle.height(), angle1, angle2);
}

void
Gdk::Drawable::draw_drawable(const GC& gc, const Drawable& src, int xsrc, int ysrc, int xdest, int ydest, int width, int height)
{
	gdk_draw_drawable(gdk_drawable(), gc.gdk_gc(), src.gdk_drawable(), xsrc, ysrc, xdest, ydest, width, height);
}

void
Gdk::Drawable::draw_drawable(const GC& gc, const Drawable& src, const Rectangle& src_rect, int xdest, int ydest)
{
	gdk_draw_drawable(gdk_drawable(), gc.gdk_gc(), src.gdk_drawable(), src_rect.x(), src_rect.y(),
	                  xdest, ydest, src_rect.width(), src_rect.height());

}

void
Gdk::Drawable::draw_image(const GC& gc, const Image& image, int xsrc, int ysrc, int xdest, int ydest, int width, int height)
{
	gdk_draw_image(gdk_drawable(), gc.gdk_gc(), image.gdk_image(), xsrc, ysrc, xdest, ydest, width, height);
}

void 
Gdk::Drawable::draw_trapezoids(const GC& gc, std::vector<Trapezoid>& trapezoids)
{
	gdk_draw_trapezoids(gdk_drawable(), gc.gdk_gc(), (GdkTrapezoid*)&trapezoids[0], trapezoids.size());
}

void 
Gdk::Drawable::draw_glyphs(const GC& gc, const Pango::Font& font, int x, int y, const Pango::GlyphString& glyphs,
                           const Pango::Matrix *matrix)
{
	gdk_draw_glyphs_transformed(gdk_drawable(), gc.gdk_gc(), *matrix, font.pango_font(), x, y,
	                            glyphs.pango_glyph_string());
}	

void
Gdk::Drawable::draw_layout_line(const GC& gc, int x, int y, const Pango::LayoutLine& line,
                                            const Color *foreground, const Color *background)
{
	gdk_draw_layout_line_with_colors(gdk_drawable(), gc.gdk_gc(), x, y, line.pango_layout_line(),
	                                 *foreground, *background);
}

void 
Gdk::Drawable::draw_layout(const GC& gc, int x, int y, const Pango::Layout& layout,
                                       const Color *foreground, const Color *background)
{
	gdk_draw_layout_with_colors(gdk_drawable(), gc.gdk_gc(), x, y, layout.pango_layout(),
	                            *foreground, *background);
}

void 
Gdk::Drawable::draw_rgb_image(const GC& gc, int x, int y, int width, int height, RgbDither dith,
                              unsigned char *rgb_buf, int rowstride)
{
 	gdk_draw_rgb_image(gdk_drawable(), gc.gdk_gc(), x, y, width, height, (GdkRgbDither)dith, rgb_buf, rowstride);
}

void 
Gdk::Drawable::draw_rgb_image_dithalign(const GC& gc, int x, int y, int width, int height, RgbDither dith,
                                        unsigned char *rgb_buf, int rowstride, int xdith, int ydith)
{
	gdk_draw_rgb_image_dithalign(gdk_drawable(), gc.gdk_gc(), x, y, width, height, (GdkRgbDither)dith, rgb_buf,
	                             rowstride, xdith, ydith);
}

void 
Gdk::Drawable::draw_rgb_32_image(const GC& gc, int x, int y, int width, int height, RgbDither dith,
                                 unsigned char *buf, int rowstride)
{
	gdk_draw_rgb_32_image(gdk_drawable(), gc.gdk_gc(), x, y, width, height, (GdkRgbDither)dith, buf, rowstride);
}

void 
Gdk::Drawable::draw_rgb_32_image_dithalign(const GC& gc, int x, int y, int width, int height, RgbDither dith,
                                           unsigned char *buf, int rowstride, int xdith, int ydith)
{
	gdk_draw_rgb_32_image_dithalign(gdk_drawable(), gc.gdk_gc(), x, y, width, height, (GdkRgbDither)dith, buf,
	                                rowstride, xdith, ydith);
}

void 
Gdk::Drawable::draw_gray_image(const GC& gc, int x, int y, int width, int height, RgbDither dith,
                               unsigned char *buf, int rowstride)
{
	gdk_draw_gray_image(gdk_drawable(), gc.gdk_gc(), x, y, width, height, (GdkRgbDither)dith, buf, rowstride);
}

void 
Gdk::Drawable::draw_indexed_image(const GC& gc, int x, int y, int width, int height, RgbDither dith,
                                  unsigned char *buf, int rowstride, GdkRgbCmap *cmap)
{
	gdk_draw_indexed_image(gdk_drawable(), gc.gdk_gc(), x, y, width, height, (GdkRgbDither)dith, buf, rowstride, cmap);
}

/*  Gdk::DrawableClass
 */

void
Gdk::DrawableClass::init(GdkDrawableClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gdk::DrawableClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_DRAWABLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::DrawableClass::create()
{
	return g_object_new(get_type(), 0);
}

