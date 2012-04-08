/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  action.cc - GtkAction C++ wrapper implementation
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

#include "action.hh"
#include "actionsignals.hh"
#include "accelgroup.hh"
#include "image.hh"
#include "menuitem.hh"
#include "stockid.hh"
#include "toolitem.hh"
#include "widget.hh"
#include "private/actionclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Action
 */

Gtk::Action::Action(GtkAction *action, bool owns_reference)
: G::Object((GObject*)action, owns_reference)
{
}

Gtk::Action::Action(const char *name, const char *label)
: G::Object((GObject*)ActionClass::create(name))
{
	g_object_set(g_object(), "label", label, 0);
}
	
Gtk::Action::Action(const String& name, const String& label)
: G::Object((GObject*)ActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "label", label.c_str(), 0);
}

Gtk::Action::Action(const char *name, const StockId& stock_id)
: G::Object((GObject*)ActionClass::create(name))
{
	g_object_set(g_object(), "stock_id", stock_id.c_str(), 0);
}
	
Gtk::Action::Action(const String& name, const StockId& stock_id)
: G::Object((GObject*)ActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "stock_id", stock_id.c_str(), 0);
}

Gtk::Action::Action(const char *name, const char *label, const StockId& stock_id)
: G::Object((GObject*)ActionClass::create(name))
{
	g_object_set(g_object(), "label", label, "stock_id", stock_id.c_str(), 0);
}
	
Gtk::Action::Action(const String& name, const String& label, const StockId& stock_id)
: G::Object((GObject*)ActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "label", label.c_str(), "stock_id", stock_id.c_str(), 0);
}

Gtk::Action::~Action()
{
}

void
Gtk::Action::block_activate_from(Widget& proxy)
{
	gtk_action_block_activate_from(gtk_action(), proxy.gtk_widget());
}

void
Gtk::Action::unblock_activate_from(Widget& proxy)
{
	gtk_action_unblock_activate_from(gtk_action(), proxy.gtk_widget());
}

void
Gtk::Action::set_accel_path(const String& accel_path)
{
	gtk_action_set_accel_path(gtk_action(), accel_path.c_str());
}

void
Gtk::Action::set_accel_group(AccelGroup *accel_group)
{
	gtk_action_set_accel_group(gtk_action(), *accel_group);
}

String
Gtk::Action::get_name() const
{
	return gtk_action_get_name(gtk_action());
}

bool
Gtk::Action::get_proxies(std::vector<Widget*>& proxies) const
{
	g_return_val_if_fail(proxies.empty(), false);
	GSList *list = gtk_action_get_proxies(gtk_action());

	while (list)
	{
		proxies.push_back(G::Object::wrap<Widget>((GtkWidget*)list->data));
		list = g_slist_next(list);
	}

	return !proxies.empty();
}

String 
Gtk::Action::get_accel_path() const
{
	return gtk_action_get_accel_path(gtk_action());
}

Gtk::Image*
Gtk::Action::create_icon(IconSize icon_size)
{
	return G::Object::wrap<Image>((GtkImage*)gtk_action_create_icon(gtk_action(), (GtkIconSize)icon_size));
}

Gtk::MenuItem*
Gtk::Action::create_menu_item()
{
	return G::Object::wrap<MenuItem>((GtkMenuItem*)gtk_action_create_menu_item(gtk_action()));
}

Gtk::ToolItem*
Gtk::Action::create_tool_item()
{
	return G::Object::wrap<ToolItem>((GtkToolItem*)gtk_action_create_tool_item(gtk_action()));
}

void
Gtk::Action::connect_proxy(Widget& proxy)
{
	gtk_action_connect_proxy(gtk_action(), proxy.gtk_widget());
}

void
Gtk::Action::disconnect_proxy(Widget& proxy)
{
	gtk_action_disconnect_proxy(gtk_action(), proxy.gtk_widget());
}

void 
Gtk::Action::set_tooltip(const String& tooltip)
{
	set_tooltip(tooltip.c_str());
}

/*  Gtk::ActionClass
 */

void
Gtk::ActionClass::init(GtkActionClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->activate = &activate_proxy;
}

GtkActionClass*
Gtk::ActionClass::get_parent_class(void *instance)
{
	return static_cast<GtkActionClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ActionClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ACTION, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ActionClass::create(const char *name)
{
	return g_object_new(get_type(), "name", name, 0);
}

void
Gtk::ActionClass::activate_proxy(GtkAction *action)
{
	ActionSignals *signals = dynamic_cast<ActionSignals*>(G::ObjectSignals::pointer((GObject*)action));
	if (signals)
		signals->on_activate();
	else
	{
		GtkActionClass *g_class = get_parent_class(action);
		if (g_class && g_class->activate)
			g_class->activate(action);
	}
}

/*  Gtk::Action properties
 */

const Gtk::Action::LabelPropertyType Gtk::Action::label_property("label");

const Gtk::Action::ShortLabelPropertyType Gtk::Action::short_label_property("short_label");

const Gtk::Action::TooltipPropertyType Gtk::Action::tooltip_property("tooltip");

const Gtk::Action::StockIdPropertyType Gtk::Action::stock_id_property("stock_id");

const Gtk::Action::IsImportantPropertyType Gtk::Action::is_important_property("is_important");

const Gtk::Action::HideIfEmptyPropertyType Gtk::Action::hide_if_empty_property("hide_if_empty");

const Gtk::Action::SensitivePropertyType Gtk::Action::sensitive_property("sensitive");

const Gtk::Action::VisiblePropertyType Gtk::Action::visible_property("visible");

const Gtk::Action::VisibleHorizontalPropertyType Gtk::Action::visible_horizontal_property("visible_horizontal");

const Gtk::Action::VisibleVerticalPropertyType Gtk::Action::visible_vertical_property("visible_vertical");

const Gtk::Action::VisibleOverflownPropertyType Gtk::Action::visible_overflown_property("visible_overflown");

/*  Gtk::Action signals
 */

const Gtk::Action::ActivateSignalType Gtk::Action::activate_signal("activate", (GCallback)&G::Marshal::void_callback);

