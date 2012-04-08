/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  cursor.inl - Gdk::Cursor inline functions
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

inline GdkCursor*
Xfc::Gdk::Cursor::gdk_cursor() const
{
	return reinterpret_cast<GdkCursor*>(boxed_);
}

inline Xfc::Gdk::Cursor::operator GdkCursor* () const
{
	return this ? gdk_cursor() : 0;
}

inline GdkCursorType
Xfc::Gdk::Cursor::type() const
{
	return gdk_cursor()->type;
}

