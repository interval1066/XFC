/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2002-2003 The XFC Development Team.
 *
 *  dnd.cc - Gtk Drag and Drop wrapper component implementation
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
 
#include "dnd.hh"
#include "stockid.hh"
#include "widget.hh"
#include "../gdk/bitmap.hh"
#include "../gdk/color.hh"
#include "../gdk/pixmap.hh"
#include "../gdk-pixbuf/pixbuf.hh"

using namespace Xfc;

Gtk::DragContext::DragContext(GdkDragContext *drag_context, bool reference)
: Gdk::DragContext(drag_context, reference)
{
}
	
Gtk::DragContext::~DragContext()
{
}

Gtk::Widget* 
Gtk::DragContext::get_source_widget() const
{
	return G::Object::wrap<Widget>(gtk_drag_get_source_widget(gdk_drag_context()));
}

void
Gtk::DragContext::set_icon_widget(Widget& widget, int hot_x, int hot_y)
{
	gtk_drag_set_icon_widget(gdk_drag_context(), widget.gtk_widget(), hot_x, hot_y);
}

void
Gtk::DragContext::set_icon_pixmap(Gdk::Colormap& colormap, Gdk::Pixmap& pixmap, Gdk::Bitmap *mask, int hot_x, int hot_y)
{
	gtk_drag_set_icon_pixmap(gdk_drag_context(), colormap.gdk_colormap(), pixmap.gdk_pixmap(), *mask, hot_x, hot_y);
}

void 
Gtk::DragContext::set_icon_pixbuf(Gdk::Pixbuf& pixbuf, int hot_x, int hot_y)
{
	gtk_drag_set_icon_pixbuf(gdk_drag_context(), pixbuf.gdk_pixbuf(), hot_x, hot_y);
}

void
Gtk::DragContext::set_icon_stock(const StockId& stock_id, int hot_x, int hot_y)
{
	gtk_drag_set_icon_stock((GdkDragContext*)instance_, stock_id.c_str(), hot_x, hot_y);
}

