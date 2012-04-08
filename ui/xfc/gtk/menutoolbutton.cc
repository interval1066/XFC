/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  menutoolbutton.cc - GtkMenuToolButton C++ wrapper implementation
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
 
#include "menutoolbutton.hh"
#include "menu.hh"
#include "tooltips.hh"
#include "private/menutoolbuttonclass.hh"

using namespace Xfc;

/*  Gtk::MenuToolButton
 */

Gtk::MenuToolButton::MenuToolButton(GtkMenuToolButton *button, bool owns_reference)
: ToolButton((GtkToolButton*)button, owns_reference)
{
}

Gtk::MenuToolButton::MenuToolButton()
: ToolButton((GtkToolButton*)MenuToolButtonClass::create())
{
}	

Gtk::MenuToolButton::MenuToolButton(Widget& icon_widget)
: ToolButton((GtkToolButton*)MenuToolButtonClass::create())
{
	set_icon_widget(&icon_widget);
}	
	
Gtk::MenuToolButton::MenuToolButton(const char *label, bool use_underline)
: ToolButton((GtkToolButton*)MenuToolButtonClass::create())
{
	set_label(label, use_underline);
}
	
Gtk::MenuToolButton::MenuToolButton(const String& label, bool use_underline)
: ToolButton((GtkToolButton*)MenuToolButtonClass::create())
{
	set_label(label, use_underline);
}	
	
Gtk::MenuToolButton::MenuToolButton(Widget& icon_widget, const char *label, bool use_underline)
: ToolButton((GtkToolButton*)MenuToolButtonClass::create())
{
	set_contents(icon_widget, label, use_underline);
}

Gtk::MenuToolButton::MenuToolButton(Widget& icon_widget, const String& label, bool use_underline)
: ToolButton((GtkToolButton*)MenuToolButtonClass::create())
{
	set_contents(icon_widget, label, use_underline);
}	
	
Gtk::MenuToolButton::MenuToolButton(const StockId& stock_id)
: ToolButton((GtkToolButton*)MenuToolButtonClass::create())
{
	set_stock_id(stock_id);
}

Gtk::MenuToolButton::~MenuToolButton()
{
}

Gtk::Menu* 
Gtk::MenuToolButton::get_menu() const
{
	return G::Object::wrap<Menu>((GtkMenu*)gtk_menu_tool_button_get_menu(gtk_menu_tool_button()));
}

void 
Gtk::MenuToolButton::set_menu(Menu *menu)
{
	gtk_menu_tool_button_set_menu(gtk_menu_tool_button(), *menu);
}

void 
Gtk::MenuToolButton::set_arrow_tooltip(Tooltips& tooltips, const char *tip_text, const char *tip_private)
{
	gtk_menu_tool_button_set_arrow_tooltip(gtk_menu_tool_button(), tooltips.gtk_tooltips(), tip_text, tip_private);
}
	
void 
Gtk::MenuToolButton::set_arrow_tooltip(Tooltips& tooltips, const String& tip_text, const String& tip_private)
{
	set_arrow_tooltip(tooltips, tip_text.c_str(), tip_private.c_str());
}

/*  Gtk::MenuToolButtonClass
 */

void
Gtk::MenuToolButtonClass::init(GtkMenuToolButtonClass *g_class)
{
	ToolButtonClass::init((GtkToolButtonClass*)g_class);
}

GType
Gtk::MenuToolButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_MENU_TOOL_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::MenuToolButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

