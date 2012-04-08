/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  fontbutton.cc - GtkFontButton C++ wrapper implementation
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

#include "fontbutton.hh"
#include "fontbuttonsignals.hh"
#include "private/fontbuttonclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::FontButton
 */

Gtk::FontButton::FontButton(GtkFontButton *font_button, bool owns_reference)
: Button((GtkButton*)font_button, owns_reference)
{
}

Gtk::FontButton::FontButton()
: Button((GtkButton*)FontButtonClass::create())
{
}
	
Gtk::FontButton::FontButton(const char *fontname)
: Button((GtkButton*)FontButtonClass::create())
{
	set_font_name(fontname);
}

Gtk::FontButton::FontButton(const String& fontname)
: Button((GtkButton*)FontButtonClass::create())
{
	set_font_name(fontname);
}

Gtk::FontButton::~FontButton()
{
}

String 
Gtk::FontButton::get_title() const
{
	return gtk_font_button_get_title(gtk_font_button());
}

String 
Gtk::FontButton::get_font_name() const
{
	return gtk_font_button_get_font_name(gtk_font_button());
}

void 
Gtk::FontButton::set_title(const String& title)
{
	set_title(title.c_str());
}

bool 
Gtk::FontButton::set_font_name(const String& fontname)
{
	return set_font_name(fontname.c_str());
}

/*  Gtk::FontButtonClass
 */

void
Gtk::FontButtonClass::init(GtkFontButtonClass *g_class)
{
	ButtonClass::init((GtkButtonClass*)g_class);
	g_class->font_set = &font_set_proxy;
}

GtkFontButtonClass*
Gtk::FontButtonClass::get_parent_class(void *instance)
{
	return static_cast<GtkFontButtonClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::FontButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FONT_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::FontButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::FontButtonClass::font_set_proxy(GtkFontButton *font_button)
{
	FontButtonSignals *signals = dynamic_cast<FontButtonSignals*>(G::ObjectSignals::pointer((GObject*)font_button));
	if (signals)
		signals->on_font_set();
	else
	{
		GtkFontButtonClass *g_class = get_parent_class(font_button);
		if (g_class && g_class->font_set)
			g_class->font_set(font_button);
	}
}

/*  Gtk::FontButton signals
 */

const Gtk::FontButton::FontSetSignalType Gtk::FontButton::font_set_signal("font_set", (GCallback)&G::Marshal::void_callback);

