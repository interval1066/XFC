/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  scrolledwindow.cc - GtkScrolledWindow C++ wrapper implementation
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
 
#include "scrolledwindow.hh"
#include "scrollbar.hh"
#include "private/scrolledwindowclass.hh"

using namespace Xfc;

Gtk::ScrolledWindow::ScrolledWindow(GtkScrolledWindow *scrolled_window, bool owns_reference)
: Bin((GtkBin*)scrolled_window, owns_reference)
{
}

Gtk::ScrolledWindow::ScrolledWindow() 
: Bin((GtkBin*)ScrolledWindowClass::create())
{
}

Gtk::ScrolledWindow::ScrolledWindow(Adjustment *hadjustment, Adjustment *vadjustment)
: Bin((GtkBin*)ScrolledWindowClass::create())
{
	set_hadjustment(hadjustment);
	set_vadjustment(vadjustment);
}

Gtk::ScrolledWindow::~ScrolledWindow()
{
}

Gtk::HScrollbar*
Gtk::ScrolledWindow::hscrollbar() const
{
	return G::Object::wrap<HScrollbar>((GtkHScrollbar*)gtk_scrolled_window()->hscrollbar);
}

Gtk::VScrollbar*
Gtk::ScrolledWindow::vscrollbar() const
{
	return G::Object::wrap<VScrollbar>((GtkVScrollbar*)gtk_scrolled_window()->vscrollbar);
}

Gtk::Adjustment*
Gtk::ScrolledWindow::get_hadjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_scrolled_window_get_hadjustment(gtk_scrolled_window()));
}

Gtk::Adjustment*
Gtk::ScrolledWindow::get_vadjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_scrolled_window_get_vadjustment(gtk_scrolled_window()));
}

void
Gtk::ScrolledWindow::set_hadjustment(Adjustment *hadjustment)
{
	gtk_scrolled_window_set_hadjustment(gtk_scrolled_window(), *hadjustment);
}

void
Gtk::ScrolledWindow::set_vadjustment(Adjustment *vadjustment)
{
	gtk_scrolled_window_set_vadjustment(gtk_scrolled_window(), *vadjustment);
}

void
Gtk::ScrolledWindow::add_with_viewport(Widget& child)
{
	gtk_scrolled_window_add_with_viewport(gtk_scrolled_window(), child.gtk_widget());
}

/*  Gtk::ScrolledWindowClass
 */

void
Gtk::ScrolledWindowClass::init(GtkScrolledWindowClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
}

GType
Gtk::ScrolledWindowClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SCROLLED_WINDOW, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ScrolledWindowClass::create()
{
	return g_object_new(get_type(), 0);
}

