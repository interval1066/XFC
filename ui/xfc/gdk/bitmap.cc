/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  bitmap.cc - GdkBitmap C++ wrapper implementation
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
#include "window.hh"

using namespace Xfc;

Gdk::Bitmap::Bitmap(GdkBitmap *bitmap, bool owns_reference)
: Pixmap((GdkPixmap*)bitmap, owns_reference)
{
}
	
Gdk::Bitmap::Bitmap(const char *data, int width, int height)
: Pixmap((GdkPixmap*)gdk_bitmap_create_from_data(0, data, width, height))
{
}

Gdk::Bitmap::Bitmap(const Window& window, const char *data, int width, int height)
: Pixmap((GdkPixmap*)gdk_bitmap_create_from_data(window.gdk_window(), data, width, height))
{
}

Gdk::Bitmap::~Bitmap() 
{
}

