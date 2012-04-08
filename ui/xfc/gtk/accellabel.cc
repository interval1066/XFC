/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  accellabel.cc - GtkAccelLabel C++ wrapper implementation
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
 
#include "accellabel.hh"
#include "private/accellabelclass.hh"

using namespace Xfc;

/*  Gtk::AccelLabel
 */

Gtk::AccelLabel::AccelLabel(GtkAccelLabel *accel_label, bool owns_reference)
: Label((GtkLabel*)accel_label, owns_reference)
{
}

Gtk::AccelLabel::AccelLabel()
: Label((GtkLabel*)AccelLabelClass::create())
{
}

Gtk::AccelLabel::AccelLabel(const char *str, bool use_underline)
: Label((GtkLabel*)AccelLabelClass::create())
{
	set_text(str);
	set_use_underline(use_underline);
}

Gtk::AccelLabel::AccelLabel(const String& str, bool use_underline)
: Label((GtkLabel*)AccelLabelClass::create())
{
	set_text(str.c_str());
	set_use_underline(use_underline);
}

Gtk::AccelLabel::~AccelLabel()
{
}

Gtk::Widget*
Gtk::AccelLabel::get_accel_widget() const
{
	return G::Object::wrap<Widget>(gtk_accel_label_get_accel_widget(gtk_accel_label()));
}

void
Gtk::AccelLabel::set_accel_widget(Widget& accel_widget)
{
	gtk_accel_label_set_accel_widget(gtk_accel_label(), accel_widget.gtk_widget());
}

/*  Gtk::AccelLabelClass
 */

void
Gtk::AccelLabelClass::init(GtkAccelLabelClass *g_class)
{
	LabelClass::init((GtkLabelClass*)g_class);
}

GType
Gtk::AccelLabelClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ACCEL_LABEL, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::AccelLabelClass::create()
{
	return g_object_new(get_type(), 0);
}

