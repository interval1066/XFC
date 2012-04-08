/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  colorbutton.cc - GtkColorButton C++ wrapper implementation
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

#include "colorbutton.hh"
#include "colorbuttonsignals.hh"
#include "private/colorbuttonclass.hh"
#include "private/marshal.hh"
#include "../gdk/color.hh"

using namespace Xfc;

/*  Gtk::ColorButton
 */

Gtk::ColorButton::ColorButton(GtkColorButton *color_button, bool owns_reference)
: Button((GtkButton*)color_button, owns_reference)
{
}

Gtk::ColorButton::ColorButton()
: Button((GtkButton*)ColorButtonClass::create())
{
}
	
Gtk::ColorButton::ColorButton(const Gdk::Color& color)
: Button((GtkButton*)ColorButtonClass::create())
{
	set_color(color);
}

Gtk::ColorButton::~ColorButton()
{
}

Gdk::Color 
Gtk::ColorButton::get_color() const
{
	GdkColor color;
	gtk_color_button_get_color(gtk_color_button(), &color);
	return Gdk::Color(&color, true);
}

String 
Gtk::ColorButton::get_title() const 
{
	return gtk_color_button_get_title(gtk_color_button());
}

void 
Gtk::ColorButton::set_color(const Gdk::Color& color)
{
	gtk_color_button_set_color(gtk_color_button(), color.gdk_color());
}

void 
Gtk::ColorButton::set_title(const String& title)
{
	set_title(title.c_str());
}

/*  Gtk::ColorButtonClass
 */

void
Gtk::ColorButtonClass::init(GtkColorButtonClass *g_class)
{
	ButtonClass::init((GtkButtonClass*)g_class);
	g_class->color_set = &color_set_proxy;
}

GtkColorButtonClass*
Gtk::ColorButtonClass::get_parent_class(void *instance)
{
	return static_cast<GtkColorButtonClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ColorButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_COLOR_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ColorButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ColorButtonClass::color_set_proxy(GtkColorButton *color_button)
{
	ColorButtonSignals *signals = dynamic_cast<ColorButtonSignals*>(G::ObjectSignals::pointer((GObject*)color_button));
	if (signals)
		signals->on_color_set();
	else
	{
		GtkColorButtonClass *g_class = get_parent_class(color_button);
		if (g_class && g_class->color_set)
			g_class->color_set(color_button);
	}
}

/*  Gtk::ColorButton signals
 */

const Gtk::ColorButton::ColorSetSignalType Gtk::ColorButton::color_set_signal("color_set", (GCallback)&G::Marshal::void_callback);
