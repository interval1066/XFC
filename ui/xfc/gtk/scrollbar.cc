/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  scrollbar.cc - GtkScrollbar, GtkHScrollbar and GtkVScrollbar C++ wrapper implementation
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
 
#include "scrollbar.hh"
#include "private/scrollbarclass.hh"

using namespace Xfc;

/*  Gtk::Scrollbar
 */

Gtk::Scrollbar::Scrollbar(GtkScrollbar *scrollbar, bool owns_reference)
: Range((GtkRange*)scrollbar, owns_reference)
{
}

Gtk::Scrollbar::~Scrollbar()
{
}

/*  Gtk::ScrollbarClass
 */

void
Gtk::ScrollbarClass::init(GtkScrollbarClass *g_class)
{
	RangeClass::init((GtkRangeClass*)g_class);
}

GType
Gtk::ScrollbarClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SCROLLBAR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ScrollbarClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::HScrollbar
 */

Gtk::HScrollbar::HScrollbar(GtkHScrollbar *hscrollbar, bool owns_reference)
: Scrollbar((GtkScrollbar*)hscrollbar, owns_reference)
{
}

Gtk::HScrollbar::HScrollbar()
: Scrollbar((GtkScrollbar*)HScrollbarClass::create())
{
}

Gtk::HScrollbar::HScrollbar(Adjustment& adjustment) 
: Scrollbar((GtkScrollbar*)HScrollbarClass::create())
{
	g_object_set(g_object(), "adjustment", adjustment.gtk_adjustment(), 0);
}

Gtk::HScrollbar::~HScrollbar() 
{
}

/*  Gtk::HScrollbarClass
 */

void
Gtk::HScrollbarClass::init(GtkHScrollbarClass *g_class)
{
	ScrollbarClass::init((GtkScrollbarClass*)g_class);
}

GType
Gtk::HScrollbarClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_HSCROLLBAR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::HScrollbarClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::VScrollbar
 */

Gtk::VScrollbar::VScrollbar(GtkVScrollbar *vscrollbar, bool owns_reference)
: Scrollbar((GtkScrollbar*)vscrollbar, owns_reference)
{
}

Gtk::VScrollbar::VScrollbar() 
: Scrollbar((GtkScrollbar*)VScrollbarClass::create())
{
}

Gtk::VScrollbar::VScrollbar(Adjustment& adjustment) 
: Scrollbar((GtkScrollbar*)VScrollbarClass::create())
{
	g_object_set(g_object(), "adjustment", adjustment.gtk_adjustment(), 0);
}

Gtk::VScrollbar::~VScrollbar() 
{
}

/*  Gtk::VScrollbarClass
 */

void
Gtk::VScrollbarClass::init(GtkVScrollbarClass *g_class)
{
	ScrollbarClass::init((GtkScrollbarClass*)g_class);
}

GType
Gtk::VScrollbarClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_VSCROLLBAR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::VScrollbarClass::create()
{
	return g_object_new(get_type(), 0);
}

