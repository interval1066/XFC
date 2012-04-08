/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  drawingarea.cc - GtkDrawingArea C++ wrapper implementation
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

#include "drawingarea.hh"
#include "private/drawingareaclass.hh"

using namespace Xfc;

/*  Gtk::Drawingarea
 */

Gtk::DrawingArea::DrawingArea(GtkDrawingArea *drawing_area, bool reference)
: Widget((GtkWidget*)drawing_area, reference)
{
}

Gtk::DrawingArea::DrawingArea() 
: Widget((GtkWidget*)DrawingAreaClass::create())
{
}

Gtk::DrawingArea::DrawingArea(int width, int height)
: Widget((GtkWidget*)DrawingAreaClass::create())
{
	set_size_request(width, height);
}

Gtk::DrawingArea::~DrawingArea() 
{
}

/*  Gtk::DrawingAreaClass
 */

void
Gtk::DrawingAreaClass::init(GtkDrawingAreaClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
}

GType
Gtk::DrawingAreaClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_DRAWING_AREA, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::DrawingAreaClass::create()
{
	return g_object_new(get_type(), 0);
}

