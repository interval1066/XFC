/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toolitem.cc - GtkToolItem C++ wrapper implementation
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

#include "toolitem.hh"
#include "toolitemsignals.hh"
#include "tooltips.hh"
#include "private/marshal.hh"
#include "private/toolitemclass.hh"

using namespace Xfc;

/*  Gtk::ToolItem
 */

Gtk::ToolItem::ToolItem(GtkToolItem *tool_item, bool owns_reference)
: Gtk::Bin((GtkBin*)tool_item, owns_reference)
{
}

Gtk::ToolItem::ToolItem()
: Bin((GtkBin*)ToolItemClass::create())
{
}

Gtk::ToolItem::ToolItem(Widget& widget)
: Bin((GtkBin*)ToolItemClass::create())
{
	add(widget);
}

Gtk::ToolItem::~ToolItem()
{
}

Gtk::Widget* 
Gtk::ToolItem::get_proxy_menu_item(const char *menu_item_id) const
{
	GtkWidget *proxy = gtk_tool_item_get_proxy_menu_item(gtk_tool_item(), menu_item_id);
	return proxy ? G::Object::wrap<Widget>(proxy) : 0;
}
	
Gtk::Widget* 
Gtk::ToolItem::get_proxy_menu_item(const String& menu_item_id) const
{
	return get_proxy_menu_item(menu_item_id.c_str());
}

Gtk::Widget* 
Gtk::ToolItem::retrieve_proxy_menu_item() const
{
	GtkWidget *proxy = gtk_tool_item_retrieve_proxy_menu_item(gtk_tool_item());
	return proxy ? G::Object::wrap<Widget>(proxy) : 0;
}

void 
Gtk::ToolItem::set_tooltip(Tooltips& tooltips, const char *tip_text, const char *tip_private)
{
	gtk_tool_item_set_tooltip(gtk_tool_item(), tooltips.gtk_tooltips(), tip_text, tip_private);
}
	
void 
Gtk::ToolItem::set_tooltip(Tooltips& tooltips, const String& tip_text, const String& tip_private)
{
	set_tooltip(tooltips, tip_text.c_str(), tip_private.c_str());
}

void 
Gtk::ToolItem::set_proxy_menu_item(const char *menu_item_id, Widget *menu_item)
{
	gtk_tool_item_set_proxy_menu_item(gtk_tool_item(), menu_item_id, *menu_item);
}
	
void 
Gtk::ToolItem::set_proxy_menu_item(const String& menu_item_id, Widget *menu_item)
{
	gtk_tool_item_set_proxy_menu_item(gtk_tool_item(), menu_item_id.c_str(), *menu_item);
}

/*  Gtk::ToolItemClass
 */

void
Gtk::ToolItemClass::init(GtkToolItemClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
	g_class->create_menu_proxy = &create_menu_proxy_proxy;
	g_class->toolbar_reconfigured = &toolbar_reconfigured_proxy;
	g_class->set_tooltip = &set_tooltip_proxy;
}

GtkToolItemClass*
Gtk::ToolItemClass::get_parent_class(void *instance)
{
	return static_cast<GtkToolItemClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ToolItemClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TOOL_ITEM, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ToolItemClass::create()
{
	return g_object_new(get_type(), 0);
}

gboolean 
Gtk::ToolItemClass::create_menu_proxy_proxy(GtkToolItem *tool_item)
{
	gboolean result = FALSE;	
	ToolItemSignals *signals = dynamic_cast<ToolItemSignals*>(G::ObjectSignals::pointer((GObject*)tool_item));
	if (signals)
		result = signals->on_create_menu_proxy();
	else
	{
		GtkToolItemClass *g_class = get_parent_class(tool_item);
		if (g_class && g_class->create_menu_proxy)
			result = g_class->create_menu_proxy(tool_item);
	}
	return result;
}
	
void 
Gtk::ToolItemClass::toolbar_reconfigured_proxy(GtkToolItem *tool_item)
{
	ToolItemSignals *signals = dynamic_cast<ToolItemSignals*>(G::ObjectSignals::pointer((GObject*)tool_item));
	if (signals)
		signals->on_toolbar_reconfigured();
	else
	{
		GtkToolItemClass *g_class = get_parent_class(tool_item);
		if (g_class && g_class->toolbar_reconfigured)
			g_class->toolbar_reconfigured(tool_item);
	}
}
	
	
gboolean 
Gtk::ToolItemClass::set_tooltip_proxy(GtkToolItem *tool_item, GtkTooltips *tooltips, const gchar *tip_text, const gchar *tip_private)
{
	gboolean result = FALSE;	
	ToolItemSignals *signals = dynamic_cast<ToolItemSignals*>(G::ObjectSignals::pointer((GObject*)tool_item));
	if (signals)
	{
		String s1(tip_text);
		String s2(tip_private);
		result = signals->on_set_tooltip(*G::Object::wrap<Tooltips>(tooltips), s1, s2);
	}
	else
	{
		GtkToolItemClass *g_class = get_parent_class(tool_item);
		if (g_class && g_class->set_tooltip)
			result = g_class->set_tooltip(tool_item, tooltips, tip_text, tip_private);
	}
	return result;
}
	
/*  Gtk::ToolItem signals
 */

const Gtk::ToolItem::CreateMenuProxySignalType Gtk::ToolItem::create_menu_proxy_signal("create_menu_proxy", (GCallback)&Marshal::bool_callback);

const Gtk::ToolItem::ToolbarReconfiguredSignalType Gtk::ToolItem::toolbar_reconfigured_signal("toolbar_reconfigured", (GCallback)&G::Marshal::void_callback);

const Gtk::ToolItem::SetTooltipSignalType Gtk::ToolItem::set_tooltip_signal("set_tooltip", (GCallback)&Marshal::bool_tooltips_string_string_callback);

