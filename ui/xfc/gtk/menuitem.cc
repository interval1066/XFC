/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  menuitem.cc - GtkMenuItem C++ wrapper implementation
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
 
#include "menuitem.hh"
#include "menuitemsignals.hh"
#include "accellabel.hh"
#include "box.hh"
#include "image.hh"
#include "menu.hh"
#include "private/marshal.hh"
#include "private/menuitemclass.hh"

using namespace Xfc;

/*  Gtk::MenuItem
 */

Gtk::MenuItem::MenuItem(GtkMenuItem *menu_item, bool owns_reference)
: Item((GtkItem*)menu_item, owns_reference)
{
}

Gtk::MenuItem::MenuItem()
: Item((GtkItem*)MenuItemClass::create())
{
}

Gtk::MenuItem::MenuItem(const char *label, bool use_underline)
: Item((GtkItem*)MenuItemClass::create())
{
	add_label(label, use_underline);
}

Gtk::MenuItem::MenuItem(const String& label, bool use_underline)
: Item((GtkItem*)MenuItemClass::create())
{
	add_label(label, use_underline);
}

Gtk::MenuItem::MenuItem(const char *label, Menu& submenu, bool use_underline)
: Item((GtkItem*)MenuItemClass::create())
{
	add_label(label, use_underline);
	set_submenu(submenu);
}

Gtk::MenuItem::MenuItem(const String& label, Menu& submenu, bool use_underline)
: Item((GtkItem*)MenuItemClass::create())
{
	add_label(label, use_underline);
	set_submenu(submenu);
}

Gtk::MenuItem::~MenuItem()
{
}

void
Gtk::MenuItem::add_label(const char *label, bool use_underline)
{
	AccelLabel *accel_label = new AccelLabel(label, use_underline);
	accel_label->set_alignment(0.0, 0.5);
	add(*accel_label);
	accel_label->set_accel_widget(*this);
	accel_label->show();
}

void
Gtk::MenuItem::add_label(const String& label, bool use_underline)
{
	add_label(label.c_str(), use_underline);
}

Gtk::Menu*
Gtk::MenuItem::get_submenu() const
{
	return gtk_menu_item()->submenu ? G::Object::wrap<Menu>((GtkMenu*)gtk_menu_item()->submenu) : 0;
}

void
Gtk::MenuItem::set_label(const char *label, bool use_underline)
{
	std::vector<Widget*> children;
	if (get_children(children))
	{
		int count = children.size();
		for (int i = 0; i < count; i++)
		{
			AccelLabel *accel_label = dynamic_cast<AccelLabel*>(children[i]);
			if (accel_label)
			{
				accel_label->set_text(label);
				accel_label->set_use_underline(use_underline);
				break;
			}
		}
	}
	else
		add_label(label, use_underline);
}

void
Gtk::MenuItem::set_label(const String& label, bool use_underline)
{
	set_label(label.c_str(), use_underline);
}

void
Gtk::MenuItem::set_submenu(Menu& submenu)
{
	gtk_menu_item_set_submenu(gtk_menu_item(), submenu.gtk_widget());
}

void
Gtk::MenuItem::set_accel_path(const String& accel_path)
{
	gtk_menu_item_set_accel_path(gtk_menu_item(), accel_path.c_str());
}

/*  Gtk::MenuItemClass
 */

void
Gtk::MenuItemClass::init(GtkMenuItemClass *g_class)
{
 	ItemClass::init((GtkItemClass*)g_class);
	g_class->activate = &activate_proxy;
	g_class->activate_item = &activate_item_proxy;
	g_class->toggle_size_request = &toggle_size_request_proxy;
	g_class->toggle_size_allocate = &toggle_size_allocate_proxy;
}

GtkMenuItemClass*
Gtk::MenuItemClass::get_parent_class(void *instance)
{
	return static_cast<GtkMenuItemClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::MenuItemClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_MENU_ITEM, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::MenuItemClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::MenuItemClass::activate_proxy(GtkMenuItem *menu_item)
{
	MenuItemSignals *signals = dynamic_cast<MenuItemSignals*>(G::ObjectSignals::pointer((GObject*)menu_item));
	if (signals)
		signals->on_activate();
	else
	{
		GtkMenuItemClass *g_class = get_parent_class(menu_item);
		if (g_class && g_class->activate)
			g_class->activate(menu_item);
	}
}

void
Gtk::MenuItemClass::activate_item_proxy(GtkMenuItem *menu_item)
{
	MenuItemSignals *signals = dynamic_cast<MenuItemSignals*>(G::ObjectSignals::pointer((GObject*)menu_item));
	if (signals)
		signals->on_activate_item();
	else
	{
		GtkMenuItemClass *g_class = get_parent_class(menu_item);
		if (g_class && g_class->activate_item)
			g_class->activate_item(menu_item);
	}
}

void
Gtk::MenuItemClass::toggle_size_request_proxy(GtkMenuItem *menu_item, gint *requisition)
{
	MenuItemSignals *signals = dynamic_cast<MenuItemSignals*>(G::ObjectSignals::pointer((GObject*)menu_item));
	if (signals)
		signals->on_toggle_size_request(requisition);
	else
	{
		GtkMenuItemClass *g_class = get_parent_class(menu_item);
		if (g_class && g_class->toggle_size_request)
			g_class->toggle_size_request(menu_item, requisition);
	}
}

void
Gtk::MenuItemClass::toggle_size_allocate_proxy(GtkMenuItem *menu_item, gint allocation)
{
	MenuItemSignals *signals = dynamic_cast<MenuItemSignals*>(G::ObjectSignals::pointer((GObject*)menu_item));
	if (signals)
		signals->on_toggle_size_allocate(allocation);
	else
	{
		GtkMenuItemClass *g_class = get_parent_class(menu_item);
		if (g_class && g_class->toggle_size_allocate)
			g_class->toggle_size_allocate(menu_item, allocation);
	}
}

/*  Gtk::MenuItem signals
 */

const Gtk::MenuItem::ActivateSignalType Gtk::MenuItem::activate_signal("activate", (GCallback)&G::Marshal::void_callback);

const Gtk::MenuItem::ActivateItemSignalType Gtk::MenuItem::activate_item_signal("activate_item", (GCallback)&G::Marshal::void_callback);

const Gtk::MenuItem::ToggleSizeRequestSignalType Gtk::MenuItem::toggle_size_request_signal("toggle_size_request", (GCallback)&Marshal::void_pint_callback);

const Gtk::MenuItem::ToggleSizeAllocateSignalType Gtk::MenuItem::toggle_size_allocate_signal("toggle_size_allocate", (GCallback)&G::Marshal::void_int_callback);

