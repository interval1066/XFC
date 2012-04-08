/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  checkmenuitem.cc - GtkCheckMenuItem C++ wrapper implementation
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
 
#include "checkmenuitem.hh"
#include "checkmenuitemsignals.hh"
#include "private/checkmenuitemclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

Gtk::CheckMenuItem::CheckMenuItem(GtkCheckMenuItem *check_menu_item, bool owns_reference)
: MenuItem((GtkMenuItem*)check_menu_item, owns_reference)
{
}

Gtk::CheckMenuItem::CheckMenuItem()
: MenuItem((GtkMenuItem*)CheckMenuItemClass::create())
{
}

Gtk::CheckMenuItem::CheckMenuItem(const char *label, bool use_underline)
: MenuItem((GtkMenuItem*)CheckMenuItemClass::create())
{
	add_label(label, use_underline);
}

Gtk::CheckMenuItem::CheckMenuItem(const String& label, bool use_underline)
: MenuItem((GtkMenuItem*)CheckMenuItemClass::create())
{
	add_label(label, use_underline);
}

Gtk::CheckMenuItem::~CheckMenuItem()
{
}


/*  Gtk::CheckMenuItemClass
 */

void
Gtk::CheckMenuItemClass::init(GtkCheckMenuItemClass *g_class)
{
	MenuItemClass::init((GtkMenuItemClass*)g_class);
	g_class->toggled = &toggled_proxy;
}

GtkCheckMenuItemClass*
Gtk::CheckMenuItemClass::get_parent_class(void *instance)
{
	return static_cast<GtkCheckMenuItemClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::CheckMenuItemClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CHECK_MENU_ITEM, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CheckMenuItemClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::CheckMenuItemClass::toggled_proxy(GtkCheckMenuItem *check_menu_item)
{
	CheckMenuItemSignals *signals = dynamic_cast<CheckMenuItemSignals*>(G::ObjectSignals::pointer((GObject*)check_menu_item));
	if (signals)
		signals->on_toggled();
	else
	{
		GtkCheckMenuItemClass *g_class = get_parent_class(check_menu_item);
		if (g_class && g_class->toggled)
			g_class->toggled(check_menu_item);
	}
}

/*  Gtk::CheckMenuItem signals
 */

const Gtk::CheckMenuItem::ToggledSignalType Gtk::CheckMenuItem::toggled_signal("toggled", (GCallback)&G::Marshal::void_callback);


