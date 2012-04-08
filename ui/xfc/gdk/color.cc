/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  color.cc - GdkColor and GdkColormap C++ wrapper implementation
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
 
#include "color.hh"
#include "screen.hh"
#include "visual.hh"
#include "private/colormapclass.hh"
#include <gtk/gtkobject.h>

using namespace Xfc;

/*  Gdk::Color
 */

Gdk::Color::Color()
: G::Boxed(GDK_TYPE_COLOR)
{
	GdkColor color = { 0, };
	copy(&color);
}

Gdk::Color::Color(const char *spec)
: G::Boxed(GDK_TYPE_COLOR)
{
	GdkColor color = { 0, };
	copy(&color);
	if (!parse(spec))
		set(0, 0, 0);
}

Gdk::Color::Color(unsigned short value)
: G::Boxed(GDK_TYPE_COLOR)
{
	GdkColor color = { 0, };
	copy(&color);
	set_grey(value);
}

Gdk::Color::Color(unsigned short r, unsigned short g, unsigned short b)
: G::Boxed(GDK_TYPE_COLOR)
{
	GdkColor color = { 0, };
	copy(&color);
	set(r, g, b);
}

Gdk::Color::Color(GdkColor *color)
: G::Boxed(GDK_TYPE_COLOR, color)
{
}

Gdk::Color::Color(GdkColor *color, bool copy)
: G::Boxed(GDK_TYPE_COLOR, color, copy)
{
}

Gdk::Color::Color(const Color& src)
: G::Boxed(GDK_TYPE_COLOR, src.g_boxed(), true)
{
}

Gdk::Color::~Color()
{
}

Gdk::Color&
Gdk::Color::operator=(const Color& src)
{
	if (!equal(src))
		copy(src);
	return *this;
}

void
Gdk::Color::get(unsigned short& r, unsigned short& g, unsigned short& b) const
{
	r = gdk_color()->red;
	g = gdk_color()->green;
	b = gdk_color()->blue;
}

bool
Gdk::Color::equal(const Color& other) const
{
	return gdk_color_equal(gdk_color(), other.gdk_color());
}

bool
Gdk::Color::operator==(const Color& other)
{
	return gdk_color_equal(gdk_color(), other.gdk_color());
}

bool
Gdk::Color::operator!=(const Color& other)
{
	return gdk_color_equal(gdk_color(), other.gdk_color()) == 0;
}

void
Gdk::Color::set_grey(unsigned short value)
{
	gdk_color()->red = gdk_color()->green = gdk_color()->blue = value;
}

void
Gdk::Color::set(unsigned short r, unsigned short g, unsigned short b)
{
	gdk_color()->red = r;
	gdk_color()->green = g;
	gdk_color()->blue = b;
}

bool
Gdk::Color::allocate(const Screen *screen)
{
	GdkScreen *tmp_screen = screen ? screen->gdk_screen() : gdk_screen_get_default();
	return gdk_colormap_alloc_color(gdk_screen_get_system_colormap(tmp_screen), gdk_color(), FALSE, TRUE);
}

void 
Gdk::Color::free(const Screen *screen)
{
	GdkScreen *tmp_screen = screen ? screen->gdk_screen() : gdk_screen_get_default();
	return gdk_colormap_free_colors(gdk_screen_get_system_colormap(tmp_screen), gdk_color(), 1);
}

/*  Gdk::Colormap
 */
 
Gdk::Colormap::Colormap(GdkColormap *colormap, bool owns_reference)
: G::Object((GObject*)colormap, owns_reference)
{
}
	
Gdk::Colormap::Colormap(const Visual& visual, bool allocate)
 : G::Object((GObject*)gdk_colormap_new(visual.gdk_visual(), allocate))
{
}

Gdk::Colormap::~Colormap()
{
}
	
Gdk::Colormap*
Gdk::Colormap::get_system(const Screen *screen)
{
	GdkScreen *tmp_screen = screen ? screen->gdk_screen() : gdk_screen_get_default();
	return G::Object::wrap<Colormap>(gdk_screen_get_system_colormap(tmp_screen));
}

const Gdk::Visual*
Gdk::Colormap::get_visual() const
{
	return G::Object::wrap<Visual>(gdk_colormap_get_visual(gdk_colormap()));
}

Gdk::Screen* 
Gdk::Colormap::get_screen() const
{
	return G::Object::wrap<Screen>(gdk_colormap_get_screen(gdk_colormap()));
}

bool
Gdk::Colormap::alloc_color(Color& color, bool best_match, bool writeable)
{
	return gdk_colormap_alloc_color(gdk_colormap(), color.gdk_color(), writeable, best_match);
}
	
int
Gdk::Colormap::alloc_colors(const std::vector<Color>& colors, std::vector<bool>& successes, bool best_match, bool writeable)
{
	g_return_val_if_fail(!colors.empty(), 0);
	
	int count = colors.size();
	g_return_val_if_fail(successes.empty(), count);

	GdkColor *tmp_colors = new GdkColor[count];
	gboolean *tmp_successes = new gboolean[count];

	int i = 0;
	while (i < count)
	{
		tmp_colors[i] = *(colors[i].gdk_color());
		++i;
	}

	int unallocated = gdk_colormap_alloc_colors(gdk_colormap(), tmp_colors, count, writeable, best_match, tmp_successes);

	if (unallocated)
	{
		i = 0;
		while (i < count)
		{
			successes.push_back(tmp_successes[i]);
			if (tmp_successes[i])
				*(colors[i].gdk_color()) = tmp_colors[i];
			++i;
		}
	}

	delete [] tmp_colors;
	delete [] tmp_successes;
	return unallocated;
}

void
Gdk::Colormap::free_color(const Color& color)
{
	gdk_colormap_free_colors(gdk_colormap(), color.gdk_color(), 1);
}

void
Gdk::Colormap::free_colors(const std::vector<Color>& colors)
{
	g_return_if_fail(!colors.empty());

	int count = colors.size();
	GdkColor *tmp_colors = new GdkColor[count];

	int i = 0;
	while (i < count)
	{
		tmp_colors[i] = *(colors[i].gdk_color());
		++i;
	}

	gdk_colormap_free_colors(gdk_colormap(), tmp_colors, count);
	delete [] tmp_colors;
}

void
Gdk::Colormap::query_color(unsigned long pixel, Color& result) const
{
	gdk_colormap_query_color(gdk_colormap(), pixel, result.gdk_color());
}

Gdk::Color
Gdk::Colormap::query_color(unsigned long pixel) const
{
	GdkColor color;
	gdk_colormap_query_color(gdk_colormap(), pixel, &color);
	return Gdk::Color(&color, true);
}

void  
Gdk::Colormap::rgb_find_color(Color& color) const
{
	gdk_rgb_find_color(gdk_colormap(), color.gdk_color());
}

/*  Gdk::ColormapClass
 */

void
Gdk::ColormapClass::init(GdkColormapClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gdk::ColormapClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_COLORMAP, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::ColormapClass::create()
{
	return g_object_new(get_type(), 0);
}


