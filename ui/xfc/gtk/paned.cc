/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  paned.cc - GtkPaned, GtkHPaned and GtkVPaned C++ wrapper implementation
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
 
#include "paned.hh"
#include "private/panedclass.hh"
#include "../gdk/window.hh"

using namespace Xfc;

/*  Gtk::Paned
 */

Gtk::Paned::Paned(GtkPaned *paned, bool owns_reference)
: Container((GtkContainer*)paned, owns_reference)
{
}

Gtk::Paned::Paned()
: Container((GtkContainer*)PanedClass::create())
{
}

Gtk::Paned::~Paned()
{
}

Gdk::Window*
Gtk::Paned::handle() const
{
	return G::Object::wrap<Gdk::Window>(gtk_paned()->handle);
}

Gtk::Widget*
Gtk::Paned::get_child1() const
{
	GtkWidget *child = gtk_paned_get_child1(gtk_paned());	
	return child ? G::Object::wrap<Widget>(child) : 0;
}

Gtk::Widget*
Gtk::Paned::get_child2() const
{
	GtkWidget *child = gtk_paned_get_child2(gtk_paned());	
	return child ? G::Object::wrap<Widget>(child) : 0;
}

void
Gtk::Paned::add1(Widget& child)
{
	gtk_paned_add1(gtk_paned(), child.gtk_widget());
}

void
Gtk::Paned::add2(Widget& child)
{
	gtk_paned_add2(gtk_paned(), child.gtk_widget());
}


void 
Gtk::Paned::pack1(Widget& child, bool resize, bool shrink)
{
	gtk_paned_pack1(gtk_paned(), child.gtk_widget(), resize, shrink);
}

void 
Gtk::Paned::pack2(Widget& child, bool resize, bool shrink)
{
	gtk_paned_pack2(gtk_paned(), child.gtk_widget(), resize, shrink);
}

/*  Gtk::PanedClass
 */

void
Gtk::PanedClass::init(GtkPanedClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
}

GType
Gtk::PanedClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_PANED, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::PanedClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::HPaned
 */

Gtk::HPaned::HPaned(GtkHPaned *hpaned, bool owns_reference)
: Paned((GtkPaned*)hpaned, owns_reference)
{
}

Gtk::HPaned::HPaned()
: Paned((GtkPaned*)HPanedClass::create())
{
}

Gtk::HPaned::~HPaned()
{
}

/*  Gtk::HPanedClass
 */

void
Gtk::HPanedClass::init(GtkHPanedClass *g_class)
{
	PanedClass::init((GtkPanedClass*)g_class);
}

GType
Gtk::HPanedClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_HPANED, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::HPanedClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::VPaned
 */

Gtk::VPaned::VPaned(GtkVPaned *vpaned, bool owns_reference)
: Paned((GtkPaned*)vpaned, owns_reference)
{
}

Gtk::VPaned::VPaned() 
: Paned((GtkPaned*)VPanedClass::create())
{
}

Gtk::VPaned::~VPaned()
{
}

/*  Gtk::VPanedClass
 */

void
Gtk::VPanedClass::init(GtkVPanedClass *g_class)
{
	PanedClass::init((GtkPanedClass*)g_class);
}

GType
Gtk::VPanedClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_VPANED, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::VPanedClass::create()
{
	return g_object_new(get_type(), 0);
}

