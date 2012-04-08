/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  pixbuf-loadersignals.cc - Gdk::PixbufLoader virtual signal handlers
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
 
#include "pixbuf-loader.hh"
#include "pixbuf-loadersignals.hh"
#include "private/pixbuf-loaderclass.hh"

using namespace Xfc;

/*  Gdk::PixbufLoaderSignals
 */

Gdk::PixbufLoaderSignals::PixbufLoaderSignals(PixbufLoader *pixbuf_loader)
: G::ObjectSignals(pixbuf_loader)
{
}
	
Gdk::PixbufLoaderSignals::~PixbufLoaderSignals()
{
}

void
Gdk::PixbufLoaderSignals::on_size_prepared(int width, int height)
{
	GdkPixbufLoaderClass *g_class = PixbufLoaderClass::get_parent_class(instance_);
	if (g_class && g_class->size_prepared)
		g_class->size_prepared((GdkPixbufLoader*)instance_, width, height);
}

void
Gdk::PixbufLoaderSignals::on_area_prepared()
{
	GdkPixbufLoaderClass *g_class = PixbufLoaderClass::get_parent_class(instance_);
	if (g_class && g_class->area_prepared)
		g_class->area_prepared((GdkPixbufLoader*)instance_);
}

void
Gdk::PixbufLoaderSignals::on_area_updated(int x, int y, int width, int height)
{
	GdkPixbufLoaderClass *g_class = PixbufLoaderClass::get_parent_class(instance_);
	if (g_class && g_class->area_updated)
		g_class->area_updated((GdkPixbufLoader*)instance_, x, y, width, height);
}

void
Gdk::PixbufLoaderSignals::on_closed()
{
	GdkPixbufLoaderClass *g_class = PixbufLoaderClass::get_parent_class(instance_);
	if (g_class && g_class->closed)
		g_class->closed((GdkPixbufLoader*)instance_);
}

