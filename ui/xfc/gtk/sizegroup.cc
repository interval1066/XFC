/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sizegroup.cc - GtkSizeGroup C++ wrapper implementation
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
 
#include "sizegroup.hh"
#include "widget.hh"
#include "private/sizegroupclass.hh"

using namespace Xfc;

/*  Gtk::SizeGroup
 */

Gtk::SizeGroup::SizeGroup(GtkSizeGroup *size_group, bool owns_reference)
: G::Object((GObject*)size_group, owns_reference)
{
}
	
Gtk::SizeGroup::SizeGroup(SizeGroupMode mode)
: G::Object((GObject*)SizeGroupClass::create())
{
	set_mode(mode);
}
	
Gtk::SizeGroup::~SizeGroup()
{
}
	
void
Gtk::SizeGroup::add_widget(Widget& widget)
{
	gtk_size_group_add_widget(gtk_size_group(), widget.gtk_widget());
}

void
Gtk::SizeGroup::remove_widget(Widget& widget)
{
	gtk_size_group_remove_widget(gtk_size_group(), widget.gtk_widget());
}

/*  Gtk::SizeGroupClass
 */

void
Gtk::SizeGroupClass::init(GtkSizeGroupClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::SizeGroupClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SIZE_GROUP, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::SizeGroupClass::create()
{
	return g_object_new(get_type(), 0);
}

