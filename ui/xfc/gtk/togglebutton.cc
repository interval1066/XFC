/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  togglebutton.cc - GtkToggleButton C++ wrapper implementation
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
 
#include "togglebutton.hh"
#include "togglebuttonsignals.hh"
#include "private/marshal.hh"
#include "private/togglebuttonclass.hh"

using namespace Xfc;

/*  Gtk::ToggleButton
 */

Gtk::ToggleButton::ToggleButton(GtkToggleButton *toggle_button, bool owns_reference)
: Button((GtkButton*)toggle_button, owns_reference)
{
}

Gtk::ToggleButton::ToggleButton() 
: Button((GtkButton*)ToggleButtonClass::create())
{
}

Gtk::ToggleButton::ToggleButton(const char *label, bool use_underline)
: Button((GtkButton*)ToggleButtonClass::create())
{
	set_label(label);
	set_use_underline(use_underline);
}

Gtk::ToggleButton::ToggleButton(const String& label, bool use_underline)
: Button((GtkButton*)ToggleButtonClass::create())
{
	set_label(label);
	set_use_underline(use_underline);
}

Gtk::ToggleButton::~ToggleButton()
{
}

/*  Gtk::ToggleButtonClass
 */

void
Gtk::ToggleButtonClass::init(GtkToggleButtonClass *g_class)
{
	ButtonClass::init((GtkButtonClass*)g_class);
	g_class->toggled = &toggled_proxy;
}

GtkToggleButtonClass*
Gtk::ToggleButtonClass::get_parent_class(void *instance)
{
	return static_cast<GtkToggleButtonClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ToggleButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TOGGLE_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ToggleButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ToggleButtonClass::toggled_proxy(GtkToggleButton *toggle_button)
{
	ToggleButtonSignals *signals = dynamic_cast<ToggleButtonSignals*>(G::ObjectSignals::pointer((GObject*)toggle_button));
	if (signals)
		signals->on_toggled();
	else
	{
		GtkToggleButtonClass *g_class = get_parent_class(toggle_button);
		if (g_class && g_class->toggled)
			g_class->toggled(toggle_button);
	}
}

/*  Gtk::ToggleButton signals
 */

const Gtk::ToggleButton::ToggledSignalType Gtk::ToggleButton::toggled_signal("toggled", (GCallback)&G::Marshal::void_callback);

