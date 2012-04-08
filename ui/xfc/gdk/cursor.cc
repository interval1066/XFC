/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  cursor.cc - GdkCursor C++ wrapper implementation
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
 
#include "cursor.hh"
#include "color.hh"
#include "display.hh"
#include "pixmap.hh"
#include "../gdk-pixbuf/pixbuf.hh"

using namespace Xfc;

Gdk::Cursor::Cursor(GdkCursorType cursor_type, const Display *display)
: G::Boxed(GDK_TYPE_CURSOR, gdk_cursor_new_for_display(display ? display->gdk_display() : gdk_display_get_default(), cursor_type), false)
{
}

Gdk::Cursor::Cursor(const Pixmap& source, const Pixmap& mask, const Color& fg, const Color& bg, int x, int y)
: G::Boxed(GDK_TYPE_CURSOR, gdk_cursor_new_from_pixmap(source.gdk_pixmap(), mask.gdk_pixmap(), fg.gdk_color(), bg.gdk_color(), x, y), false)
{
}

Gdk::Cursor::Cursor(const Pixbuf& pixbuf, int x, int y, const Display *display)
: G::Boxed(GDK_TYPE_CURSOR, gdk_cursor_new_from_pixbuf(display ? display->gdk_display() : gdk_display_get_default(), pixbuf.gdk_pixbuf(), x, y), false)
{
}

Gdk::Cursor::Cursor(GdkCursor *cursor)
: G::Boxed(GDK_TYPE_CURSOR, cursor)
{
}

Gdk::Cursor::Cursor(GdkCursor *cursor, bool copy)
: G::Boxed(GDK_TYPE_CURSOR, cursor, copy)
{
}

Gdk::Cursor::Cursor(const Cursor& src)
: G::Boxed(GDK_TYPE_CURSOR, src.gdk_cursor(), true)
{
}
	
Gdk::Cursor::~Cursor() 
{
}
	
Gdk::Cursor&
Gdk::Cursor::operator=(const Cursor& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

Gdk::Display*
Gdk::Cursor::get_display() const
{
	return G::Object::wrap<Display>(gdk_cursor_get_display(gdk_cursor()));
}

