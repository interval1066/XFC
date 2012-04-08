/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  expander.cc - GtkExpander C++ wrapper implementation
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

#include "expander.hh"
#include "private/expanderclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Expander
 */

Gtk::Expander::Expander(GtkExpander *expander, bool owns_reference)
: Bin((GtkBin*)expander, owns_reference)
{
}

Gtk::Expander::Expander(const char *label, bool use_underline)
: Bin((GtkBin*)ExpanderClass::create())
{
	set_label(label);
	set_use_underline(use_underline);
}

Gtk::Expander::Expander(const String& label, bool use_underline)
: Bin((GtkBin*)ExpanderClass::create())
{
	set_label(label);
	set_use_underline(use_underline);
}

Gtk::Expander::~Expander()
{
}

String 
Gtk::Expander::get_label() const
{
	return gtk_expander_get_label(gtk_expander());
}

Gtk::Widget* 
Gtk::Expander::get_label_widget() const
{
	GtkWidget *widget = gtk_expander_get_label_widget(gtk_expander());
	return widget ? G::Object::wrap<Widget>(widget) : 0;
}

void 
Gtk::Expander::set_label(const String& label)
{
	set_label(label.c_str());
}

void 
Gtk::Expander::set_label_widget(Widget *label_widget)
{
	gtk_expander_set_label_widget(gtk_expander(), *label_widget);
}

/*  Gtk::ExpanderClass
 */

void
Gtk::ExpanderClass::init(GtkExpanderClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
}

GType
Gtk::ExpanderClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_EXPANDER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ExpanderClass::create()
{
	return g_object_new(get_type(), 0);
}

