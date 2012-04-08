/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toolbutton.cc - GtkToolButton C++ wrapper implementation
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

#include "toolbutton.hh"
#include "toolbuttonsignals.hh"
#include "stockid.hh"
#include "widget.hh"
#include "private/marshal.hh"
#include "private/toolbuttonclass.hh"

using namespace Xfc;

/*  Gtk::ToolButton
 */

Gtk::ToolButton::ToolButton(GtkToolButton *tool_button, bool owns_reference)
: ToolItem((GtkToolItem*)tool_button, owns_reference)
{
}

Gtk::ToolButton::ToolButton()
: ToolItem((GtkToolItem*)ToolButtonClass::create())
{
}	

Gtk::ToolButton::ToolButton(Widget& icon_widget)
: ToolItem((GtkToolItem*)ToolButtonClass::create())
{
	set_icon_widget(&icon_widget);
}	
	
Gtk::ToolButton::ToolButton(const char *label, bool use_underline)
: ToolItem((GtkToolItem*)ToolButtonClass::create())
{
	set_label(label, use_underline);
}
	
Gtk::ToolButton::ToolButton(const String& label, bool use_underline)
: ToolItem((GtkToolItem*)ToolButtonClass::create())
{
	set_label(label, use_underline);
}	
	
Gtk::ToolButton::ToolButton(Widget& icon_widget, const char *label, bool use_underline)
: ToolItem((GtkToolItem*)ToolButtonClass::create())
{
	set_contents(icon_widget, label, use_underline);
}
	
Gtk::ToolButton::ToolButton(Widget& icon_widget, const String& label, bool use_underline)
: ToolItem((GtkToolItem*)ToolButtonClass::create())
{
	set_contents(icon_widget, label, use_underline);
}	
 	
Gtk::ToolButton::ToolButton(const StockId& stock_id)
: ToolItem((GtkToolItem*)ToolButtonClass::create())
{
	set_stock_id(stock_id);
}

Gtk::ToolButton::~ToolButton()
{
}

String 
Gtk::ToolButton::get_label() const
{
	return gtk_tool_button_get_label(gtk_tool_button());
}

String 
Gtk::ToolButton::get_stock_id() const
{
	return gtk_tool_button_get_stock_id(gtk_tool_button());
}
	
Gtk::Widget* 
Gtk::ToolButton::get_icon_widget() const
{
	GtkWidget *widget = gtk_tool_button_get_icon_widget(gtk_tool_button());
	return widget ? G::Object::wrap<Widget>(widget) : 0;
}
	
Gtk::Widget* 
Gtk::ToolButton::get_label_widget() const
{
	GtkWidget *widget = gtk_tool_button_get_label_widget(gtk_tool_button());
	return widget ? G::Object::wrap<Widget>(widget) : 0;
}

void 
Gtk::ToolButton::set_label(const char *label, bool use_underline)
{
	gtk_tool_button_set_label(gtk_tool_button(), label);
	if (use_underline)
		set_use_underline(use_underline);
}

void 
Gtk::ToolButton::set_label(const String& label, bool use_underline)
{
	set_label(label.c_str(), use_underline);
}

void 
Gtk::ToolButton::set_stock_id(const StockId& stock_id)
{
	gtk_tool_button_set_stock_id(gtk_tool_button(), stock_id);
}

void 
Gtk::ToolButton::set_icon_widget(Widget *icon_widget)
{
	gtk_tool_button_set_icon_widget(gtk_tool_button(), icon_widget->gtk_widget());
}

void 
Gtk::ToolButton::set_label_widget(Widget *label_widget)
{
	gtk_tool_button_set_label_widget(gtk_tool_button(), label_widget->gtk_widget());
}

void 
Gtk::ToolButton::set_contents(Widget& icon_widget, const char *label, bool use_underline)
{
	set_label(label, use_underline);	
	set_icon_widget(&icon_widget);
	icon_widget.show();	
}
	
void 
Gtk::ToolButton::set_contents(Widget& icon_widget, const String& label, bool use_underline)
{
	set_contents(icon_widget, label.c_str(), use_underline);	
}

/*  Gtk::ToolButtonClass
 */

void
Gtk::ToolButtonClass::init(GtkToolButtonClass *g_class)
{
	ToolItemClass::init((GtkToolItemClass*)g_class);
	g_class->clicked = &clicked_proxy;
}

GtkToolButtonClass*
Gtk::ToolButtonClass::get_parent_class(void *instance)
{
	return static_cast<GtkToolButtonClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ToolButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TOOL_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ToolButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ToolButtonClass::clicked_proxy(GtkToolButton *tool_button)
{
	ToolButtonSignals *signals = dynamic_cast<ToolButtonSignals*>(G::ObjectSignals::pointer((GObject*)tool_button));
	if (signals)
		signals->on_clicked();
	else
	{
		GtkToolButtonClass *g_class = get_parent_class(tool_button);
		if (g_class && g_class->clicked)
			g_class->clicked(tool_button);
	}
}

/*  Gtk::ToolButton signals
 */

const Gtk::ToolButton::ClickedSignalType Gtk::ToolButton::clicked_signal("clicked", (GCallback)&G::Marshal::void_callback);

