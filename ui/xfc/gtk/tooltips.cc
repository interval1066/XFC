/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  tooltips.cc - GtkTooltips C++ wrapper implementation
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
 
#include "tooltips.hh"
#include "widget.hh"
#include "private/tooltipsclass.hh"

using namespace Xfc;

/*  Gtk::TooltipsData
 */

Gtk::Tooltips*
Gtk::TooltipsData::tooltips() const
{
	return G::Object::wrap<Tooltips>(data_.tooltips);
}

String
Gtk::TooltipsData::tip_text() const
{
	return data_.tip_text;
}

String
Gtk::TooltipsData::tip_private() const
{
	return data_.tip_private;
}

/*  Gtk::Tooltips
 */

Gtk::Tooltips::Tooltips(GtkTooltips *tooltips, bool owns_reference)
: Object((GtkObject*)tooltips,owns_reference)
{
}

Gtk::Tooltips::Tooltips() 
: Object((GtkObject*)TooltipsClass::create())
{
}

Gtk::Tooltips::~Tooltips()
{
}

Gtk::TooltipsData*
Gtk::Tooltips::data_get(Widget& widget)
{
	return reinterpret_cast<TooltipsData*>(gtk_tooltips_data_get(widget.gtk_widget()));
}

void
Gtk::Tooltips::set_tip(Widget& widget, const char *tip_text, const char *tip_private)
{
	gtk_tooltips_set_tip(gtk_tooltips(), widget.gtk_widget(), tip_text, tip_private);
}

void
Gtk::Tooltips::set_tip(Widget& widget, const String& tip_text, const String& tip_private)
{
	gtk_tooltips_set_tip(gtk_tooltips(), widget.gtk_widget(), tip_text.c_str(), tip_private.c_str());
}

void
Gtk::Tooltips::unset_tip(Widget& widget)
{
	gtk_tooltips_set_tip(gtk_tooltips(), widget.gtk_widget(), 0, 0);
}

/*  Gtk::TooltipsClass
 */

void
Gtk::TooltipsClass::init(GtkTooltipsClass *g_class)
{
	ObjectClass::init((GtkObjectClass*)g_class);
}

GType
Gtk::TooltipsClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TOOLTIPS, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TooltipsClass::create()
{
	return g_object_new(get_type(), 0);
}

