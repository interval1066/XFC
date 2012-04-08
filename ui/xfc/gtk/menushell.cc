/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  menushell.cc - GtkMenuShell C++ wrapper implemenation
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
 
#include "menushell.hh"
#include "menushellsignals.hh"
#include "imagemenuitem.hh"
#include "menu.hh"
#include "separatormenuitem.hh"
#include "stockid.hh"
#include "private/marshal.hh"
#include "private/menushellclass.hh"

using namespace Xfc;

/*  Gtk::MenuShell
 */

Gtk::MenuShell::MenuShell(GtkMenuShell *menu_shell, bool owns_reference)
: Container((GtkContainer*)menu_shell, owns_reference)
{
}

Gtk::MenuShell::MenuShell()
: Container((GtkContainer*)MenuShellClass::create())
{
}

Gtk::MenuShell::~MenuShell()
{
}

bool
Gtk::MenuShell::children(std::vector<MenuItem*>& child_list) const
{
	g_return_val_if_fail(child_list.empty(), false);
	GList *next = gtk_menu_shell()->children;
	while (next)
	{
		child_list.push_back(G::Object::wrap<MenuItem>((GtkMenuItem*)next->data));
		next = g_list_next(next);
	}
	return !child_list.empty();
}

void
Gtk::MenuShell::append(MenuItem& item)
{
	gtk_menu_shell_insert(gtk_menu_shell(), item.gtk_widget(), -1);
}

void
Gtk::MenuShell::append(MenuItem& item, const sigc::slot<void>& callback)
{
	insert(item, -1, callback);
}

void
Gtk::MenuShell::append(MenuItem& item, const AccelKey& accel_key, const sigc::slot<void>& callback)
{
	insert(item, -1, accel_key, callback);
}
	
void
Gtk::MenuShell::append(MenuItem& item, const AccelKey& accel_key, AccelGroup& accel_group, const sigc::slot<void>& callback)
{
	insert(item, -1, accel_key, accel_group, callback);
}

void
Gtk::MenuShell::append(const StockId& stock_id, const sigc::slot<void>& callback)
{
	insert(stock_id, -1, callback);
}

void 
Gtk::MenuShell::append_separator()
{
	insert_separator(-1);
}
	
void
Gtk::MenuShell::prepend(MenuItem& item)
{
	gtk_menu_shell_insert(gtk_menu_shell(), item.gtk_widget(), 0);
}

void
Gtk::MenuShell::prepend(MenuItem& item, const sigc::slot<void>& callback)
{
	insert(item, 0, callback);
}

void
Gtk::MenuShell::prepend(MenuItem& item, const AccelKey& accel_key, const sigc::slot<void>& callback)
{
	insert(item, 0, accel_key, callback);
}
	
void
Gtk::MenuShell::prepend(MenuItem& item, const AccelKey& accel_key, AccelGroup& accel_group, const sigc::slot<void>& callback)
{
	insert(item, 0, accel_key, accel_group, callback);
}

void
Gtk::MenuShell::prepend(const StockId& stock_id, const sigc::slot<void>& callback)
{
	insert(stock_id, 0, callback);
}

void
Gtk::MenuShell::insert(MenuItem& item, int position)
{
	gtk_menu_shell_insert(gtk_menu_shell(), item.gtk_widget(), position);
}

void
Gtk::MenuShell::insert(MenuItem& item, int position, const sigc::slot<void>& callback)
{
	gtk_menu_shell_insert(gtk_menu_shell(), item.gtk_widget(), position);
	item.signal_activate().connect(callback);
}

void
Gtk::MenuShell::insert(MenuItem& item, int position, const AccelKey& accel_key, const sigc::slot<void>& callback)
{
	Menu *menu = dynamic_cast<Menu*>(this);
	if (menu)
	{
		Gtk::AccelGroup *accel_group = menu->get_accel_group();
		g_return_if_fail(accel_group != 0);
		insert(item, position, accel_key, *accel_group, callback);
		return;
	}
	insert(item, position, callback);
}

void
Gtk::MenuShell::insert(MenuItem& item, int position, const AccelKey& accel_key, AccelGroup& accel_group, const sigc::slot<void>& callback)
{
	item.add_accelerator("activate", accel_group, accel_key);
	gtk_menu_shell_insert(gtk_menu_shell(), item.gtk_widget(), position);
	item.signal_activate().connect(callback);
}

void
Gtk::MenuShell::insert(const StockId& stock_id, int position, const sigc::slot<void>& callback)
{
	Gtk::AccelGroup *accel_group = 0;
	Menu *menu = dynamic_cast<Menu*>(this);
	if (menu)
		accel_group = menu->get_accel_group();
	insert(*(new ImageMenuItem(stock_id, accel_group)), position, callback);	
}

void 
Gtk::MenuShell::insert_separator(int position)
{
	insert(*(new Gtk::SeparatorMenuItem), position);
}

void
Gtk::MenuShell::select_item(MenuItem& item)
{
	gtk_menu_shell_select_item(gtk_menu_shell(), item.gtk_widget());
}

void
Gtk::MenuShell::activate_item(MenuItem& item, bool force_deactivate)
{
	gtk_menu_shell_activate_item(gtk_menu_shell(), item.gtk_widget(), force_deactivate);
}

void 
Gtk::MenuShell::cancel()
{
	gtk_menu_shell_cancel(gtk_menu_shell());
}

/*  Gtk::MenuShellClass
 */

void
Gtk::MenuShellClass::init(GtkMenuShellClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
	g_class->deactivate = &deactivate_proxy;
	g_class->selection_done = &selection_done_proxy;
}

GtkMenuShellClass*
Gtk::MenuShellClass::get_parent_class(void *instance)
{
	return static_cast<GtkMenuShellClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::MenuShellClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_MENU_SHELL, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::MenuShellClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::MenuShellClass::deactivate_proxy(GtkMenuShell *menu_shell)
{
	MenuShellSignals *signals = dynamic_cast<MenuShellSignals*>(G::ObjectSignals::pointer((GObject*)menu_shell));
	if (signals)
		signals->on_deactivate();
	else
	{
		GtkMenuShellClass *g_class = get_parent_class(menu_shell);
		if (g_class && g_class->deactivate)
			g_class->deactivate(menu_shell);
	}
}

void
Gtk::MenuShellClass::selection_done_proxy(GtkMenuShell *menu_shell)
{
	MenuShellSignals *signals = dynamic_cast<MenuShellSignals*>(G::ObjectSignals::pointer((GObject*)menu_shell));
	if (signals)
		signals->on_selection_done();
	else
	{
		GtkMenuShellClass *g_class = get_parent_class(menu_shell);
		if (g_class && g_class->selection_done)
			g_class->selection_done(menu_shell);
	}
}

/*  Gtk::MenuShell signals
 */

const Gtk::MenuShell::DeactivateSignalType Gtk::MenuShell::deactivate_signal("deactivate", (GCallback)&G::Marshal::void_callback);

const Gtk::MenuShell::SelectionDoneSignalType Gtk::MenuShell::selection_done_signal("selection_done", (GCallback)&G::Marshal::void_callback);

