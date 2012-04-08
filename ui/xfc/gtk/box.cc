/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  box.cc - GtkBox, GtkHBox and GtkVBox C++ wrapper implemntation
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

#include "box.hh"
#include "private/boxclass.hh"

using namespace Xfc;

/*  Gtk::Box
 */

Gtk::Box::Box(GtkBox *box, bool owns_reference)
: Container((GtkContainer*)box, owns_reference)
{
}

Gtk::Box::~Box()
{
}

bool
Gtk::Box::children(std::vector<BoxChild*>& child_list) const
{
	g_return_val_if_fail(child_list.empty(), false);
	GList *first = gtk_box()->children;
	GList *next = first;

	while (next)
	{
		child_list.push_back(reinterpret_cast<BoxChild*>(next->data));
		next = g_list_next(next);
	}
	return !child_list.empty();
}

void
Gtk::Box::pack_start(Widget& child, bool expand, bool fill, unsigned int padding)
{
	gtk_box_pack_start(gtk_box(), child.gtk_widget(), expand, fill, padding);
}

void 
Gtk::Box::pack_end(Widget& child, bool expand, bool fill, unsigned int padding)
{
	gtk_box_pack_end(gtk_box(), child.gtk_widget(), expand, fill, padding);
}

void
Gtk::Box::insert_start(Widget& child, int position, bool expand, bool fill, unsigned int padding)
{
	gtk_box_pack_start(gtk_box(), child.gtk_widget(), expand, fill, padding);
	if (position != -1)
		gtk_box_reorder_child(gtk_box(), child.gtk_widget(), position);
}

void 
Gtk::Box::insert_end(Widget& child, int position, bool expand, bool fill, unsigned int padding)
{
	gtk_box_pack_end(gtk_box(), child.gtk_widget(), expand, fill, padding);
	if (position != -1)
		gtk_box_reorder_child(gtk_box(), child.gtk_widget(), position);
}

void
Gtk::Box::reorder_child(Widget& child, int position)
{
	gtk_box_reorder_child(gtk_box(), child.gtk_widget(), position);
}

void
Gtk::Box::query_child_packing(Widget& child, bool *expand, bool *fill, unsigned int *padding, PackType *pack_type) const
{
	gtk_box_query_child_packing(gtk_box(), child.gtk_widget(), (gboolean*)expand, (gboolean*)fill, padding, (GtkPackType*)pack_type);
}

void
Gtk::Box::set_child_packing(Widget& child, bool expand, bool fill, unsigned int padding, PackType pack_type)
{
	gtk_box_set_child_packing(gtk_box(), child.gtk_widget(), expand, fill, padding, (GtkPackType)pack_type);
}

/*  Gtk::BoxClass
 */

void
Gtk::BoxClass::init(GtkBoxClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
}

GType
Gtk::BoxClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_BOX, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::BoxClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::HBox
 */

Gtk::HBox::HBox(GtkHBox *hbox, bool owns_reference)
: Box((GtkBox*)hbox, owns_reference)
{
}

Gtk::HBox::HBox(bool homogeneous, int spacing)
: Box((GtkBox*)HBoxClass::create())
{
	set_homogeneous(homogeneous);
	set_spacing(spacing);
}

Gtk::HBox::~HBox()
{
}

/*  Gtk::HBoxClass
 */

void
Gtk::HBoxClass::init(GtkHBoxClass *g_class)
{
	BoxClass::init((GtkBoxClass*)g_class);
}

GType
Gtk::HBoxClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_HBOX, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::HBoxClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::VBox
 */
 
Gtk::VBox::VBox(GtkVBox *vbox, bool owns_reference)
: Box((GtkBox*)vbox, owns_reference)
{
}

Gtk::VBox::VBox(bool homogeneous, int spacing) 
: Box((GtkBox*)VBoxClass::create())
{
	set_homogeneous(homogeneous);
	set_spacing(spacing);
}

Gtk::VBox::~VBox()
{
}

/*  Gtk::VBoxClass
 */

void
Gtk::VBoxClass::init(GtkVBoxClass *g_class)
{
	BoxClass::init((GtkBoxClass*)g_class);
}

GType
Gtk::VBoxClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_VBOX, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::VBoxClass::create()
{
	return g_object_new(get_type(), 0);
}

