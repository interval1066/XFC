/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toggletoolbutton.cc - GtkToggleToolButton C++ wrapper implementation
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

#include "toggletoolbutton.hh"
#include "toggletoolbuttonsignals.hh"
#include "stockid.hh"
#include "private/marshal.hh"
#include "private/toggletoolbuttonclass.hh"

using namespace Xfc;

/*  Gtk::ToggleToolButton
 */

Gtk::ToggleToolButton::ToggleToolButton(GtkToggleToolButton *button, bool owns_reference)
: ToolButton((GtkToolButton*)button, owns_reference)
{
}

Gtk::ToggleToolButton::ToggleToolButton()
: ToolButton((GtkToolButton*)ToggleToolButtonClass::create())
{
}	

Gtk::ToggleToolButton::ToggleToolButton(const StockId& stock_id)
: ToolButton((GtkToolButton*)ToggleToolButtonClass::create())
{
	set_stock_id(stock_id);
}

Gtk::ToggleToolButton::~ToggleToolButton()
{
}

/*  Gtk::ToggleToolButtonClass
 */

void
Gtk::ToggleToolButtonClass::init(GtkToggleToolButtonClass *g_class)
{
	ToolButtonClass::init((GtkToolButtonClass*)g_class);
	g_class->toggled = &toggled_proxy;
}

GtkToggleToolButtonClass*
Gtk::ToggleToolButtonClass::get_parent_class(void *instance)
{
	return static_cast<GtkToggleToolButtonClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ToggleToolButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TOGGLE_TOOL_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ToggleToolButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ToggleToolButtonClass::toggled_proxy(GtkToggleToolButton *button)
{
	ToggleToolButtonSignals *signals = dynamic_cast<ToggleToolButtonSignals*>(G::ObjectSignals::pointer((GObject*)button));
	if (signals)
		signals->on_toggled();
	else
	{
		GtkToggleToolButtonClass *g_class = get_parent_class(button);
		if (g_class && g_class->toggled)
			g_class->toggled(button);
	}
}

/*  Gtk::ToggleToolButton signals
 */

const Gtk::ToggleToolButton::ToggledSignalType Gtk::ToggleToolButton::toggled_signal("toggled", (GCallback)&G::Marshal::void_callback);

