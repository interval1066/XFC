/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  menu.cc - GtkMenu C++ wrapper implementation
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
 
#include "menu.hh"
#include "accelgroup.hh"
#include "menuitem.hh"
#include "private/menuclass.hh"
#include "../gdk/screen.hh"
#include "xfc/glib/private/objectclass.hh"

using namespace Xfc;

/*  Gtk::Menu
 */

Gtk::Menu::Menu(GtkMenu *menu, bool owns_reference)
: MenuShell((GtkMenuShell*)menu, owns_reference)
{
}
	
Gtk::Menu::Menu()
: MenuShell((GtkMenuShell*)MenuClass::create())
{
}

Gtk::Menu::Menu(const AccelGroup& accel_group)
: MenuShell((GtkMenuShell*)MenuClass::create())
{
	set_accel_group(&accel_group);
}

Gtk::Menu::~Menu()
{
}
	
void 
Gtk::Menu::on_menu_detach(Widget& /*attach_widget*/)
{
}

Gtk::MenuItem*
Gtk::Menu::get_active() const
{
	return G::Object::wrap<MenuItem>((GtkMenuItem*)gtk_menu_get_active(gtk_menu()));
}

Gtk::AccelGroup*
Gtk::Menu::get_accel_group() const
{
	return G::Object::wrap<AccelGroup>(gtk_menu_get_accel_group(gtk_menu()));
}

Gtk::Widget*
Gtk::Menu::get_attach_widget() const
{
	return G::Object::wrap<Widget>(gtk_menu_get_attach_widget(gtk_menu()));
}

String
Gtk::Menu::get_title() const
{
	return gtk_menu_get_title(gtk_menu());
}

std::vector<Gtk::Menu*> 
Gtk::Menu::get_for_attach_widget(Widget& widget)
{
	std::vector<Menu*> menus;	
	GList *list = gtk_menu_get_for_attach_widget(widget.gtk_widget());

	while (list)
	{
		menus.push_back(G::Object::wrap<Menu>((GtkMenu*)list->data));
		list = g_list_next(list);
	}
	return menus;
}

namespace { // menu_position_slot_callback

void menu_position_slot_callback(GtkMenu*, gint *x, gint *y, gboolean *push_in, gpointer data)
{
	Gtk::Menu::MenuPositionSlot& slot = *static_cast<Gtk::Menu::MenuPositionSlot*>(data);
	slot(x, y, (bool*)push_in);
}

} // namespace	

void
Gtk::Menu::popup(MenuShell& parent_shell, MenuItem& parent_item, unsigned int button, const MenuPositionSlot& position, unsigned int activate_time)
{
	MenuPositionSlot tmp_position(position);
	gtk_menu_popup(gtk_menu(), parent_shell.gtk_widget(), parent_item.gtk_widget(), &menu_position_slot_callback,
	               &tmp_position, button, activate_time);
}

void 
Gtk::Menu::popup(unsigned int button, const MenuPositionSlot& position, unsigned int activate_time)
{
	MenuPositionSlot tmp_position(position);
	gtk_menu_popup(gtk_menu(), 0, 0, &menu_position_slot_callback, &tmp_position, button, activate_time);
}

void
Gtk::Menu::set_accel_group(const AccelGroup *accel_group)
{
	gtk_menu_set_accel_group(gtk_menu(), *accel_group);
}

void
Gtk::Menu::set_accel_path(const String& accel_path)
{
	gtk_menu_set_accel_path(gtk_menu(), accel_path.c_str());
}

void
Gtk::Menu::attach_to_widget(Widget& attach_widget)
{
	gtk_menu_attach_to_widget(gtk_menu(), attach_widget.gtk_widget(), &MenuClass::menu_detach_callback);
}

void
Gtk::Menu::set_title(const String& title)
{
	gtk_menu_set_title(gtk_menu(), title.c_str());
}

void
Gtk::Menu::reorder_child(const MenuItem& child, int position)
{
	gtk_menu_reorder_child(gtk_menu(), child.gtk_widget(), position);
}

void 
Gtk::Menu::set_screen(const Gdk::Screen *screen)
{
	gtk_menu_set_screen(gtk_menu(), screen->gdk_screen());
}

void
Gtk::Menu::attach(MenuItem &child, unsigned int left_attach, unsigned int right_attach,
                  unsigned int  top_attach, unsigned int bottom_attach)
{
	gtk_menu_attach(gtk_menu(), child.gtk_widget(), left_attach, right_attach, top_attach, bottom_attach);
}

/*  Gtk::MenuClass
 */

void
Gtk::MenuClass::init(GtkMenuClass *g_class)
{
	MenuShellClass::init((GtkMenuShellClass*)g_class);
}

GType
Gtk::MenuClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_MENU, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::MenuClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::MenuClass::menu_detach_callback(GtkWidget *widget, GtkMenu *menu)
{
	void *ptr = g_object_get_qdata((GObject*)menu, G::ObjectClass::quark());
	if (ptr)
		static_cast<Menu*>(ptr)->on_menu_detach(*G::Object::wrap<Gtk::Widget>(widget));
}

