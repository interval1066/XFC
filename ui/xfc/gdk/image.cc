/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  image.cc - GdkImage C++ wrapper implementation
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
 
#include "image.hh"
#include "color.hh"
#include "drawable.hh"
#include "visual.hh"
#include "private/imageclass.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include <gdk/gdkpixbuf.h>

using namespace Xfc;

/*  Gdk::Image
 */

Gdk::Image::Image(GdkImage *image, bool owns_reference)
: G::Object((GObject*)image, owns_reference)
{
}
	
Gdk::Image::~Image()
{
}
	
Pointer<Gdk::Image>
Gdk::Image::create(ImageType type, const Visual& visual, int width, int height)
{
	return G::Object::wrap<Image>(gdk_image_new((GdkImageType)type, visual.gdk_visual(), width, height));
}

const Gdk::Visual&
Gdk::Image::visual() const
{
	return *G::Object::wrap<Visual>(gdk_image()->visual);
}

Gdk::Colormap*
Gdk::Image::get_colormap() const
{
	GdkColormap *colormap = gdk_image_get_colormap(gdk_image());
	return colormap ? G::Object::wrap<Colormap>(colormap) : 0;
}

void
Gdk::Image::set_colormap(Colormap& colormap)
{
	gdk_image_set_colormap(gdk_image(), colormap.gdk_colormap());
}

/*  Gdk::ImageClass
 */

void
Gdk::ImageClass::init(GdkImageClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gdk::ImageClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_IMAGE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::ImageClass::create()
{
	return g_object_new(get_type(), 0);
}

