/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  radiotoolbutton.cc - GtkRadioToolButton C++ wrapper implementation
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

#include "radiotoolbutton.hh"
#include "stockid.hh"
#include "private/marshal.hh"
#include "private/radiotoolbuttonclass.hh"

using namespace Xfc;

/*  Gtk::RadioToolButton
 */

Gtk::RadioToolButton::RadioToolButton(GtkRadioToolButton *button, bool owns_reference)
: ToggleToolButton((GtkToggleToolButton*)button, owns_reference)
{
}

Gtk::RadioToolButton::RadioToolButton()
: ToggleToolButton((GtkToggleToolButton*)RadioToolButtonClass::create())
{
}

Gtk::RadioToolButton::RadioToolButton(const RadioToolButton *group)
: ToggleToolButton((GtkToggleToolButton*)RadioToolButtonClass::create())
{
	if (group)	
		set_group(group->get_group());
}
	
Gtk::RadioToolButton::RadioToolButton(const RadioToolButton *group, const StockId& stock_id)
: ToggleToolButton((GtkToggleToolButton*)RadioToolButtonClass::create())
{
	set_stock_id(stock_id);
	if (group)	
		set_group(group->get_group());
}
	
Gtk::RadioToolButton::~RadioToolButton()
{
}

/*  Gtk::RadioToolButtonClass
 */

void
Gtk::RadioToolButtonClass::init(GtkRadioToolButtonClass *g_class)
{
	ToggleToolButtonClass::init((GtkToggleToolButtonClass*)g_class);
}

GType
Gtk::RadioToolButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_RADIO_TOOL_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::RadioToolButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

