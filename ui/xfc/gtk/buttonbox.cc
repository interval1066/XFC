/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  buttonbox.cc - GtkButtonBox, GtkHButtonBox and GtkVButtonBox C++ wrapper implementation
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
 
#include "buttonbox.hh"
#include "private/buttonboxclass.hh"

using namespace Xfc;

/*  Gtk::ButtonBox
 */

Gtk::ButtonBox::ButtonBox(GtkButtonBox *button_box, bool owns_reference)
: Box((GtkBox*)button_box, owns_reference)
{
}

Gtk::ButtonBox::~ButtonBox()
{
}

bool
Gtk::ButtonBox::get_child_secondary(const Widget& child) const
{
	return gtk_button_box_get_child_secondary(gtk_button_box(), child.gtk_widget());
}

void
Gtk::ButtonBox::set_child_secondary(Widget& child, bool is_secondary)
{
	gtk_button_box_set_child_secondary(gtk_button_box(), child.gtk_widget(), is_secondary);
}

/*  Gtk::ButtonBoxClass
 */

void
Gtk::ButtonBoxClass::init(GtkButtonBoxClass *g_class)
{
	BoxClass::init((GtkBoxClass*)g_class);
}

GType
Gtk::ButtonBoxClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_BUTTON_BOX, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ButtonBoxClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::HButtonBox
 */

Gtk::HButtonBox::HButtonBox(GtkHButtonBox *hbutton_box, bool owns_reference)
: ButtonBox((GtkButtonBox*)hbutton_box, owns_reference)
{
}

Gtk::HButtonBox::HButtonBox(ButtonBoxStyle layout, int spacing)
: ButtonBox((GtkButtonBox*)HButtonBoxClass::create())
{
	set_layout(layout);
	set_spacing(spacing);
}

Gtk::HButtonBox::~HButtonBox()
{
}

/*  Gtk::HButtonBoxClass
 */

void
Gtk::HButtonBoxClass::init(GtkHButtonBoxClass *g_class)
{
	ButtonBoxClass::init((GtkButtonBoxClass*)g_class);
}

GType
Gtk::HButtonBoxClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_HBUTTON_BOX, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::HButtonBoxClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::VButtonBox
 */

Gtk::VButtonBox::VButtonBox(GtkVButtonBox *vbutton_box, bool owns_reference)
: ButtonBox((GtkButtonBox*)vbutton_box, owns_reference)
{
}

Gtk::VButtonBox::VButtonBox(ButtonBoxStyle layout, int spacing)
: ButtonBox((GtkButtonBox*)VButtonBoxClass::create())
{
	set_layout(layout);
	set_spacing(spacing);
}

Gtk::VButtonBox::~VButtonBox()
{
}

/*  Gtk::VButtonBoxClass
 */

void
Gtk::VButtonBoxClass::init(GtkVButtonBoxClass *g_class)
{
	ButtonBoxClass::init((GtkButtonBoxClass*)g_class);
}

GType
Gtk::VButtonBoxClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_VBUTTON_BOX, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::VButtonBoxClass::create()
{
	return g_object_new(get_type(), 0);
}

