/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  radiomenuitem.cc - GtkRadioMenuItem C++ wrapper implementation
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
 
#include "radiomenuitem.hh"
#include "radiomenuitemsignals.hh"
#include "private/radiomenuitemclass.hh"
#include "xfc/glib/private/marshal.hh"

using namespace Xfc;

/*  Gtk::RadioMenuItem
 */

Gtk::RadioMenuItem::RadioMenuItem(GtkRadioMenuItem *radio_menu_item, bool owns_reference)
: CheckMenuItem((GtkCheckMenuItem*)radio_menu_item, owns_reference)
{
}

Gtk::RadioMenuItem::RadioMenuItem()
: CheckMenuItem((GtkCheckMenuItem*)RadioMenuItemClass::create())
{
}

Gtk::RadioMenuItem::RadioMenuItem(const RadioMenuItem *group)
: CheckMenuItem((GtkCheckMenuItem*)RadioMenuItemClass::create())
{
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioMenuItem::RadioMenuItem(const RadioMenuItem *group, const char *label, bool use_underline)
: CheckMenuItem((GtkCheckMenuItem*)RadioMenuItemClass::create())
{
	add_label(label, use_underline);
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioMenuItem::RadioMenuItem(const RadioMenuItem *group, const String& label, bool use_underline)
: CheckMenuItem((GtkCheckMenuItem*)RadioMenuItemClass::create())
{
	add_label(label, use_underline);
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioMenuItem::~RadioMenuItem()
{
}

/*  Gtk::RadioMenuItemClass
 */

void
Gtk::RadioMenuItemClass::init(GtkRadioMenuItemClass *g_class)
{
	CheckMenuItemClass::init((GtkCheckMenuItemClass*)g_class);
	g_class->group_changed = &group_changed_proxy;
}

GtkRadioMenuItemClass*
Gtk::RadioMenuItemClass::get_parent_class(void *instance)
{
	return static_cast<GtkRadioMenuItemClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::RadioMenuItemClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_RADIO_MENU_ITEM, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::RadioMenuItemClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::RadioMenuItemClass::group_changed_proxy(GtkRadioMenuItem *radio_menu_item)
{
	RadioMenuItemSignals *signals = dynamic_cast<RadioMenuItemSignals*>(G::ObjectSignals::pointer((GObject*)radio_menu_item));
	if (signals)
		signals->on_group_changed();
	else
	{
		GtkRadioMenuItemClass *g_class = get_parent_class(radio_menu_item);
		if (g_class && g_class->group_changed)
			g_class->group_changed(radio_menu_item);
	}
}

/*  Gtk::RadioMenuItem signals
 */

const Gtk::RadioMenuItem::GroupChangedSignalType Gtk::RadioMenuItem::group_changed_signal("group-changed", (GCallback)&G::Marshal::void_callback);
