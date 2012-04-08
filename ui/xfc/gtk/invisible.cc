/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  invisible.cc - GtkInvisible C++ wrapper implementation
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
 
#include "invisible.hh"
#include "private/invisibleclass.hh"
#include "../gdk/screen.hh"

using namespace Xfc;

/*  Gtk::Invisible
 */

Gtk::Invisible::Invisible(GtkInvisible *invisible, bool owns_reference)
: Widget((GtkWidget*)invisible, owns_reference)
{
}

Gtk::Invisible::Invisible()
: Widget((GtkWidget*)InvisibleClass::create())
{
}

Gtk::Invisible::Invisible(const Gdk::Screen& screen)
: Widget((GtkWidget*)InvisibleClass::create())
{
	set_screen(screen);
}

Gtk::Invisible::~Invisible()
{
}

Gdk::Screen*
Gtk::Invisible::get_screen() const
{
	return G::Object::wrap<Gdk::Screen>(gtk_invisible_get_screen(gtk_invisible()));
}

void
Gtk::Invisible::set_screen(const Gdk::Screen& screen)
{
	gtk_invisible_set_screen(gtk_invisible(), screen.gdk_screen());
}

/*  Gtk::InvisibleClass
 */

void
Gtk::InvisibleClass::init(GtkInvisibleClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
}

GType
Gtk::InvisibleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_INVISIBLE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::InvisibleClass::create()
{
	return g_object_new(get_type(), 0);
}

