/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  gc.cc - GdkGCValues and GdkGC C++ wrapper implementation
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
 
#include "gc.hh"
#include "color.hh"
#include "bitmap.hh"
#include "region.hh"
#include "screen.hh"
#include "private/gcclass.hh"

using namespace Xfc;

/* Gdk::GCValues
 */

Gdk::GCValues::GCValues()
: mask_(0)
{
	values_.tile = 0;
	values_.stipple = 0;
	values_.clip_mask = 0;
}

Gdk::GCValues::GCValues(const GCValues& src)
: values_(src.values_), mask_(src.mask_)
{
	if (src.tile_set() && src.values_.tile)
		g_object_ref(src.values_.tile);

	if (src.stipple_set() && src.values_.stipple)
		g_object_ref(src.values_.stipple);

	if (src.clip_mask_set() && src.values_.clip_mask)
		g_object_ref(src.values_.clip_mask);
}

Gdk::GCValues::~GCValues()
{
	unset_tile();
	unset_stipple();
	unset_clip_mask();
}

Gdk::GCValues& 
Gdk::GCValues::operator=(const GCValues& src)
{
	if (src.tile_set() && src.values_.tile)
		g_object_ref(src.values_.tile);

	if (src.stipple_set() && src.values_.stipple)
		g_object_ref(src.values_.stipple);

	if (src.clip_mask_set() && src.values_.clip_mask)
		g_object_ref(src.values_.clip_mask);

	unset_tile();
	unset_stipple();
	unset_clip_mask();

	values_ = src.values_;
	mask_ = src.mask_;
	return *this;
}

GdkGCValues*
Gdk::GCValues::gdk_gc_values() const
{
	return const_cast<GdkGCValues*>(&values_);
}

GdkGCValuesMask 
Gdk::GCValues::gdk_gc_values_mask() const
{
	return (GdkGCValuesMask)mask_;
}

Gdk::Color 
Gdk::GCValues::foreground() const
{
	return Color(const_cast<GdkColor*>(&values_.foreground));
}

Gdk::Color
Gdk::GCValues::background() const
{
	return Color(const_cast<GdkColor*>(&values_.background));
}

Gdk::Pixmap*
Gdk::GCValues::tile() const
{
	return tile_set() ? G::Object::wrap<Pixmap>(values_.tile) : 0;
}

Gdk::Bitmap*
Gdk::GCValues::stipple() const
{
	return stipple_set() ? G::Object::wrap<Bitmap>(values_.stipple) : 0;
}

Gdk::Bitmap*
Gdk::GCValues::clip_mask() const
{
	return clip_mask_set() ? G::Object::wrap<Bitmap>(values_.clip_mask) : 0;
}

void
Gdk::GCValues::reset()
{
	unset_tile();
	unset_stipple();
	unset_clip_mask();
	mask_ = 0;
}

void
Gdk::GCValues::set_foreground(const Color& color)
{
	values_.foreground = *color.gdk_color();
	mask_ |= GDK_GC_FOREGROUND;
}

void
Gdk::GCValues::set_background(const Color& color)
{
	values_.background = *color.gdk_color();
	mask_ |= GDK_GC_BACKGROUND;
}

void
Gdk::GCValues::set_tile(Pixmap& tile)
{
	unset_tile();
	values_.tile = tile.gdk_pixmap();
	tile.ref();
	mask_ |= GDK_GC_TILE;
}

void
Gdk::GCValues::unset_tile()
{
	if (tile_set())
	{
		g_object_unref(values_.tile);
		mask_ &= ~GDK_GC_TILE;
		values_.tile = 0;
	}
}

void
Gdk::GCValues::set_stipple(Bitmap& stipple)
{
	unset_stipple();
	values_.stipple = stipple.gdk_pixmap();
	stipple.ref();
	mask_ |= GDK_GC_STIPPLE;
}

void
Gdk::GCValues::unset_stipple()
{
	if (stipple_set())
	{
		g_object_unref(values_.stipple);
		mask_ &= ~GDK_GC_STIPPLE;
		values_.stipple = 0;
	}
}

void
Gdk::GCValues::set_clip_mask(Bitmap& mask)
{
	unset_clip_mask();
	values_.clip_mask = mask.gdk_pixmap();
	mask.ref();
	mask_ |= GDK_GC_CLIP_MASK;
}

void
Gdk::GCValues::unset_clip_mask()
{
	if (clip_mask_set())
	{
		g_object_unref(values_.clip_mask);
		mask_ &= ~GDK_GC_CLIP_MASK;
		values_.clip_mask = 0;
	}
}

void
Gdk::GCValues::set_ts_origin(int x_origin, int y_origin)
{
	set_ts_x_origin(x_origin);
	set_ts_y_origin(y_origin);
}

void
Gdk::GCValues::set_clip_origin(int x_origin, int y_origin)
{
	set_clip_x_origin(x_origin);
	set_clip_y_origin(y_origin);
}

/*  Gdk::GC
 */

Gdk::GC::GC(GdkGC *gc, bool owns_reference)
: G::Object((GObject*)gc, owns_reference)
{
}

Gdk::GC::GC(Drawable& drawable)
: G::Object((GObject*)gdk_gc_new(drawable.gdk_drawable()))
{
}

Gdk::GC::GC(Drawable& drawable, const GCValues& values)
: G::Object((GObject*)gdk_gc_new_with_values(drawable.gdk_drawable(), values.gdk_gc_values(), values.gdk_gc_values_mask()))
{
}

Gdk::GC::~GC()
{
}

void
Gdk::GC::get_values(GCValues& values) const
{
	values.unset_clip_mask();
	values.unset_stipple();
	values.unset_tile();

	GdkGCValues *tmp_values = values.gdk_gc_values();
	gdk_gc_get_values(gdk_gc(), tmp_values);

	values.mask_ = GDK_GC_FOREGROUND | GDK_GC_BACKGROUND | GDK_GC_FONT |
	               GDK_GC_FUNCTION | GDK_GC_FILL | GDK_GC_SUBWINDOW |
	               GDK_GC_TS_X_ORIGIN | GDK_GC_TS_Y_ORIGIN | GDK_GC_CLIP_X_ORIGIN |
	               GDK_GC_CLIP_Y_ORIGIN | GDK_GC_EXPOSURES | GDK_GC_LINE_WIDTH |
	               GDK_GC_LINE_STYLE | GDK_GC_CAP_STYLE | GDK_GC_JOIN_STYLE;

	if (tmp_values->stipple)
	{
		g_object_ref(tmp_values->stipple);
		values.mask_ |= GDK_GC_STIPPLE;
    	}

	if (tmp_values->tile)
	{
		g_object_ref(tmp_values->tile);
		values.mask_ |= GDK_GC_TILE;
    	}

	if (tmp_values->clip_mask)
	{
		g_object_ref(tmp_values->clip_mask);
		values.mask_ |= GDK_GC_CLIP_MASK;
	}
}

Gdk::Colormap*
Gdk::GC::get_colormap() const
{
	GdkColormap *colormap = gdk_gc_get_colormap(gdk_gc());
	return colormap ? G::Object::wrap<Colormap>(colormap) : 0;
}

Gdk::Screen* 
Gdk::GC::get_screen() const
{
	return G::Object::wrap<Screen>(gdk_gc_get_screen(gdk_gc()));
}

void
Gdk::GC::set_values(const GCValues& values)
{
	gdk_gc_set_values(gdk_gc(), values.gdk_gc_values(), values.gdk_gc_values_mask());
}

void 
Gdk::GC::set_foreground(const Color& color)
{
	gdk_gc_set_foreground(gdk_gc(), color.gdk_color());
}

void
Gdk::GC::set_background(const Color& color)
{
	gdk_gc_set_background(gdk_gc(), color.gdk_color());
}
 
void
Gdk::GC::set_tile(Pixmap& tile)
{
	gdk_gc_set_tile(gdk_gc(), tile.gdk_pixmap());
}

void
Gdk::GC::set_stipple(Pixmap& stipple)
{
	gdk_gc_set_stipple(gdk_gc(), stipple.gdk_pixmap());
}

void
Gdk::GC::set_ts_origin(const Point& point)
{
	set_ts_origin(point.x(), point.y());
}

void
Gdk::GC::set_clip_origin(const Point& point)
{
	set_clip_origin(point.x(), point.y());
}

void
Gdk::GC::set_clip_mask(Bitmap& mask)
{
	gdk_gc_set_clip_mask(gdk_gc(), mask.gdk_pixmap());
}

void
Gdk::GC::set_clip(const Rectangle& rectangle)
{
	gdk_gc_set_clip_rectangle(gdk_gc(), rectangle.gdk_rectangle());
}

void 
Gdk::GC::set_clip(const Region& region)
{
	gdk_gc_set_clip_region(gdk_gc(), region.gdk_region());
}

void
Gdk::GC::set_dashes(int dash_offset, gint8 *dash_list, int n)
{
	gdk_gc_set_dashes(gdk_gc(), dash_offset, dash_list, n);
}

void
Gdk::GC::set_colormap(Colormap *colormap)
{
	gdk_gc_set_colormap(gdk_gc(), colormap->gdk_colormap());
}

void
Gdk::GC::set_rgb_fg_color(const Color& color)
{
	return gdk_gc_set_rgb_fg_color(gdk_gc(), color.gdk_color());
}

void
Gdk::GC::set_rgb_bg_color(const Color& color)
{
	return gdk_gc_set_rgb_bg_color(gdk_gc(), color.gdk_color());
}

void
Gdk::GC::set_clip(int x, int y, int width, int height)
{
	Rectangle rectangle(x, y, width, height);
	set_clip(rectangle);
}

void
Gdk::GC::set_line_width(int line_width)
{
	GdkGCValues values;
	values.line_width = line_width;
	gdk_gc_set_values(gdk_gc(), &values, GDK_GC_JOIN_STYLE);
}

void
Gdk::GC::set_line_style(LineStyle line_style)
{
	GdkGCValues values;
	values.line_style = (GdkLineStyle)line_style;
	gdk_gc_set_values(gdk_gc(), &values, GDK_GC_JOIN_STYLE);
}

void
Gdk::GC::set_cap_style(CapStyle cap_style)
{
	GdkGCValues values;
	values.cap_style = (GdkCapStyle)cap_style;
	gdk_gc_set_values(gdk_gc(), &values, GDK_GC_JOIN_STYLE);
}

void
Gdk::GC::set_join_style(JoinStyle join_style)
{
	GdkGCValues values;
	values.join_style = (GdkJoinStyle)join_style;
	gdk_gc_set_values(gdk_gc(), &values, GDK_GC_JOIN_STYLE);
}

/*  Gdk::GCClass
 */

void
Gdk::GCClass::init(GdkGCClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gdk::GCClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_GC, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::GCClass::create()
{
	return g_object_new(get_type(), 0);
}

