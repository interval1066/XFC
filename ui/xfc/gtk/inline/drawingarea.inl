/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  drawingarea.inl - Gtk::DrawingArea inline functions
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

#ifdef XFC_CAIRO
inline Xfc::Cairo::Context
Xfc::Gtk::DrawingArea::get_cairo_context() const
{
    return Xfc::Cairo::Context( gdk_cairo_create( get_window()->gdk_window()));
}
#endif

inline GtkDrawingArea *
Xfc::Gtk::DrawingArea::gtk_drawing_area() const
{
	return reinterpret_cast<GtkDrawingArea*>(instance_);
}

inline Xfc::Gtk::DrawingArea::operator GtkDrawingArea* () const
{
	return this ? gtk_drawing_area() : 0;
}

