/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  pixmap.c - GdkPixmap C++ wrapper implementation
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
 
#include "bitmap.hh"
#include "color.hh"
#include "display.hh"
#include "window.hh"
#include "private/pixmapclass.hh"

using namespace Xfc;

namespace {

static const char * const default_pixmap_xpm[]={
"14 16 5 1",
"b c #000000",
". c #848284",
"a c #c6c3c6",
"c c #ff0000",
"# c #ffffff",
"..............",
".###########ab",
".###########ab",
".###########ab",
".##cc####cc#ab",
".###cc##cc##ab",
".####cccc###ab",
".#####cc####ab",
".####cccc###ab",
".###cc##cc##ab",
".##cc####cc#ab",
".###########ab",
".###########ab",
".###########ab",
".aaaaaaaaaaaab",
"bbbbbbbbbbbbbb"};

GdkPixmap* create_from_xpm_d(const Gdk::Drawable& drawable, const char * const *data, Pointer<Gdk::Bitmap> *mask, GdkColor *transparent_color)
{
	GdkBitmap *transparency = 0;
	GdkPixmap *pixmap = gdk_pixmap_create_from_xpm_d(drawable.gdk_drawable(), &transparency, transparent_color, const_cast<char**>(data));
	if (mask)
		*mask = G::Object::wrap_new<Gdk::Bitmap>(transparency, true);
	return pixmap;
}

GdkPixmap* create_from_xpm(const Gdk::Drawable& drawable, const String& filename, Pointer<Gdk::Bitmap> *mask, GdkColor *transparent_color)
{
	GdkBitmap *transparency = 0;
	GdkPixmap *pixmap = gdk_pixmap_create_from_xpm(drawable.gdk_drawable(), &transparency, transparent_color, filename.c_str());
		
	if (!pixmap)
	{
		g_warning("Unable to create pixmap from file '%s' - using default pixmap.", filename.c_str());
		pixmap = create_from_xpm_d(drawable, default_pixmap_xpm, mask, transparent_color);
	}
	else if (mask)
		*mask = G::Object::wrap_new<Gdk::Bitmap>(transparency, true);
		
	return pixmap;
}

GdkPixmap* colormap_create_from_xpm_d(Gdk::Colormap* colormap, const char * const *data, Pointer<Gdk::Bitmap> *mask, GdkColor *transparent_color)
{
	GdkBitmap *transparency = 0;
	GdkPixmap *pixmap = gdk_pixmap_colormap_create_from_xpm_d(0, colormap->gdk_colormap(), &transparency, transparent_color, const_cast<char**>(data));
	if (mask)
		*mask = G::Object::wrap_new<Gdk::Bitmap>(transparency, true);
	return pixmap;
}

GdkPixmap* colormap_create_from_xpm(Gdk::Colormap *colormap, const String& filename, Pointer<Gdk::Bitmap> *mask, GdkColor *transparent_color)
{
	GdkBitmap *transparency = 0;
	GdkPixmap *pixmap = gdk_pixmap_colormap_create_from_xpm(0, colormap->gdk_colormap(), &transparency, transparent_color, filename.c_str());
		
	if (!pixmap)
	{
		g_warning("Unable to create pixmap from file '%s' - using default pixmap.", filename.c_str());
		pixmap = colormap_create_from_xpm_d(colormap, default_pixmap_xpm, mask, transparent_color);
	}
	else if (mask)
		*mask = G::Object::wrap_new<Gdk::Bitmap>(transparency, true);
		
	return pixmap;
}

} // namespace

/*  Gdk::Pixmap
 */

Gdk::Pixmap::Pixmap(GdkPixmap *pixmap, bool owns_reference)
: Drawable((GdkDrawable*)pixmap, owns_reference)
{
}

Gdk::Pixmap::Pixmap(const Drawable& drawable, int width, int height)
: Drawable((GdkDrawable*)gdk_pixmap_new(drawable.gdk_drawable(), width, height, -1))
{
}

Gdk::Pixmap::Pixmap(int width, int height, int depth) 
: Drawable((GdkDrawable*)gdk_pixmap_new(0, width, height, depth))
{
}
	
Gdk::Pixmap::Pixmap(const Drawable& drawable, const char* data, int width, int height, const Color& fg, const Color& bg)
: Drawable((GdkDrawable*)gdk_pixmap_create_from_data(drawable.gdk_drawable(), data, width, height, -1, fg.gdk_color(), bg.gdk_color()))
{
}

Gdk::Pixmap::Pixmap(const char* data, int width, int height, int depth, const Color& fg, const Color& bg)
: Drawable((GdkDrawable*)gdk_pixmap_create_from_data(0, data, width, height, depth, fg.gdk_color(), bg.gdk_color()))
{
}

Gdk::Pixmap::Pixmap(const Drawable& drawable, const String& filename, Pointer<Bitmap> *mask, const Color *transparent_color)
: Drawable((GdkDrawable*)create_from_xpm(drawable, filename.c_str(), mask, *transparent_color))
{
}

Gdk::Pixmap::Pixmap(Colormap *colormap, const String& filename, Pointer<Bitmap> *mask, const Color *transparent_color)
: Drawable((GdkDrawable*)colormap_create_from_xpm(colormap, filename.c_str(), mask, *transparent_color))
{
}

Gdk::Pixmap::Pixmap(const Drawable& drawable, const char * const *data, Pointer<Bitmap> *mask, const Color *transparent_color)
: Drawable((GdkDrawable*)create_from_xpm_d(drawable, data, mask, *transparent_color))
{
}
	
Gdk::Pixmap::Pixmap(Colormap *colormap, const char * const *data, Pointer<Bitmap> *mask, const Color *transparent_color)
: Drawable((GdkDrawable*)colormap_create_from_xpm_d(colormap, data, mask, *transparent_color))
{
}

Gdk::Pixmap::~Pixmap()
{
}

Pointer<Gdk::Pixmap>
Gdk::Pixmap::create(GdkNativeWindow anid, const Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return new Pixmap(gdk_pixmap_foreign_new_for_display(tmp_display, anid));
}

Pointer<Gdk::Pixmap>
Gdk::Pixmap::lookup(GdkNativeWindow anid, const Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return G::Object::wrap<Pixmap>(gdk_pixmap_lookup_for_display(tmp_display, anid));
}

void
Gdk::Pixmap::clear(GC& gc, const Color& color)
{
	GCValues values;
	gc.get_values(values);
	Color old_color = values.foreground();
	gc.set_foreground(color);
	int width, height;
	get_size(&width, &height);
	draw_rectangle(gc, 0, 0, width, height);
	gc.set_foreground(old_color);
}

/*  Gdk::PixmapClass
 */

void
Gdk::PixmapClass::init(GdkPixmapObjectClass *g_class)
{
	DrawableClass::init((GdkDrawableClass*)g_class);
}

GType
Gdk::PixmapClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_PIXMAP, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::PixmapClass::create()
{
	return g_object_new(get_type(), 0);
}

