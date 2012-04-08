/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  uimanager.cc - GtkUIManager C++ wrapper implementation
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

#include "uimanager.hh"
#include "uimanagersignals.hh"
#include "accelgroup.hh"
#include "widget.hh"
#include "private/marshal.hh"
#include "private/uimanagerclass.hh"
#include "xfc/glib/error.hh"

using namespace Xfc;

/*  Gtk::UIManager
 */

Gtk::UIManager::UIManager(GtkUIManager *ui_manager, bool owns_reference)
: G::Object((GObject*)ui_manager, owns_reference)
{
}
	
Gtk::UIManager::UIManager()
: G::Object((GObject*)UIManagerClass::create())
{
}

Gtk::UIManager::~UIManager()
{
}

bool 
Gtk::UIManager::get_action_groups(std::vector<ActionGroup*>& action_groups) const
{
	g_return_val_if_fail(action_groups.empty(), false);

	GList *first = gtk_ui_manager_get_action_groups(gtk_ui_manager());
	GList *next = first;

	while (next)
	{
		action_groups.push_back(G::Object::wrap<ActionGroup>((GtkActionGroup*)next->data));
		next = g_list_next(next);
	}

	return !action_groups.empty();
}

Gtk::AccelGroup*
Gtk::UIManager::get_accel_group() const
{
	return G::Object::wrap<AccelGroup>(gtk_ui_manager_get_accel_group(gtk_ui_manager()));
}
	
Gtk::Widget* 
Gtk::UIManager::get_widget(const char *path) const
{
	GtkWidget *widget =  gtk_ui_manager_get_widget(gtk_ui_manager(), path);
	return widget ? G::Object::wrap<Widget>(widget) : 0;
}

Gtk::Widget* 
Gtk::UIManager::get_widget(const String& path) const
{
	return get_widget(path.c_str());
}

bool 
Gtk::UIManager::get_toplevels(std::vector<Widget*>& toplevels, UIManagerItemTypeField types) const
{
	g_return_val_if_fail(toplevels.empty(), false);

	GSList *first = gtk_ui_manager_get_toplevels(gtk_ui_manager(), (GtkUIManagerItemType)types);
	GSList *next = first;

	while (next)
	{
		toplevels.push_back(G::Object::wrap<Widget>((GtkWidget*)next->data));
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !toplevels.empty();
}

Gtk::Action* 
Gtk::UIManager::get_action(const char *path) const
{
	GtkAction *action = gtk_ui_manager_get_action(gtk_ui_manager(), path);
	return action ? G::Object::wrap<Action>(action) : 0;
}

String 
Gtk::UIManager::get_ui() const
{
	char *merged_ui = gtk_ui_manager_get_ui(gtk_ui_manager());
	String s(merged_ui);
	g_free(merged_ui);
	return s;
}
	
void 
Gtk::UIManager::insert_action_group(ActionGroup& action_group, int pos)
{
	gtk_ui_manager_insert_action_group(gtk_ui_manager(), action_group.gtk_action_group(), pos);
}
	
void 
Gtk::UIManager::remove_action_group(ActionGroup& action_group)
{
	gtk_ui_manager_remove_action_group(gtk_ui_manager(), action_group.gtk_action_group());
}

unsigned int 
Gtk::UIManager::add_ui_from_string(const char *buffer, int length, G::Error *error)
{
	return gtk_ui_manager_add_ui_from_string(gtk_ui_manager(), buffer, (gssize)length, *error);
}
	
unsigned int 
Gtk::UIManager::add_ui_from_string(const String& buffer, G::Error *error)
{
	return add_ui_from_string(buffer.c_str(), buffer.size(), error);
}

unsigned int 
Gtk::UIManager::add_ui_from_file(const char *filename, G::Error *error)
{
	return gtk_ui_manager_add_ui_from_file(gtk_ui_manager(), filename, *error);
}
	
unsigned int 
Gtk::UIManager::add_ui_from_file(const String& filename, G::Error *error)
{
	return add_ui_from_file(filename.c_str(), error);
}

void 
Gtk::UIManager::add_ui(unsigned int merge_id, const char *path, const char *name, const char *action, UIManagerItemType type, bool top)
{
	gtk_ui_manager_add_ui(gtk_ui_manager(), merge_id, path, name, action, (GtkUIManagerItemType)type, top);
}
	
void 
Gtk::UIManager::add_ui(unsigned int merge_id, const String& path, const String& name, const String& action, UIManagerItemType type, bool top)
{
	add_ui(merge_id, path.c_str(), name.c_str(), action.c_str(), type, top);
}
	
void 
Gtk::UIManager::add_ui_separator(unsigned int merge_id, const char *path, const char *name, bool top)
{
	gtk_ui_manager_add_ui(gtk_ui_manager(), merge_id, path, name, 0, (GtkUIManagerItemType)0, top);

}
	
void 
Gtk::UIManager::add_ui_separator(unsigned int merge_id, const String& path, const String& name, bool top)
{
	add_ui_separator(merge_id, path.c_str(), name.c_str(), top);

}

void 
Gtk::UIManager::remove_ui(unsigned int merge_id)
{
	gtk_ui_manager_remove_ui(gtk_ui_manager(), merge_id);
}

void 
Gtk::UIManager::ensure_update()
{
	gtk_ui_manager_ensure_update(gtk_ui_manager());
}

unsigned int 
Gtk::UIManager::new_merge_id()
{
	return gtk_ui_manager_new_merge_id(gtk_ui_manager());
}

/*  Gtk::UIManagerClass
 */

void
Gtk::UIManagerClass::init(GtkUIManagerClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->add_widget = &add_widget_proxy;
	g_class->actions_changed = &actions_changed_proxy;
	g_class->connect_proxy = &connect_proxy_proxy;
	g_class->disconnect_proxy = &disconnect_proxy_proxy;
	g_class->pre_activate = &pre_activate_proxy;
	g_class->post_activate = &post_activate_proxy;
}

GtkUIManagerClass*
Gtk::UIManagerClass::get_parent_class(void *instance)
{
	return static_cast<GtkUIManagerClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::UIManagerClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_UI_MANAGER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::UIManagerClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::UIManagerClass::add_widget_proxy(GtkUIManager *merge, GtkWidget *widget)
{
	UIManagerSignals *signals = dynamic_cast<UIManagerSignals*>(G::ObjectSignals::pointer((GObject*)merge));
	if (signals)
		signals->on_add_widget(*G::Object::wrap<Widget>(widget));
	else
	{
		GtkUIManagerClass *g_class = get_parent_class(merge);
		if (g_class && g_class->add_widget)
			g_class->add_widget(merge, widget);
	}
}
	
void
Gtk::UIManagerClass::actions_changed_proxy(GtkUIManager *merge)
{
	UIManagerSignals *signals = dynamic_cast<UIManagerSignals*>(G::ObjectSignals::pointer((GObject*)merge));
	if (signals)
		signals->on_actions_changed();
	else
	{
		GtkUIManagerClass *g_class = get_parent_class(merge);
		if (g_class && g_class->actions_changed)
			g_class->actions_changed(merge);
	}
}
	
void
Gtk::UIManagerClass::connect_proxy_proxy(GtkUIManager *merge, GtkAction *action, GtkWidget *proxy)
{
	UIManagerSignals *signals = dynamic_cast<UIManagerSignals*>(G::ObjectSignals::pointer((GObject*)merge));
	if (signals)
		signals->on_connect_proxy(*G::Object::wrap<Action>(action), *G::Object::wrap<Widget>(proxy));
	else
	{
		GtkUIManagerClass *g_class = get_parent_class(merge);
		if (g_class && g_class->connect_proxy)
			g_class->connect_proxy(merge, action, proxy);
	}
}
	
void
Gtk::UIManagerClass::disconnect_proxy_proxy(GtkUIManager *merge, GtkAction *action, GtkWidget *proxy)
{
	UIManagerSignals *signals = dynamic_cast<UIManagerSignals*>(G::ObjectSignals::pointer((GObject*)merge));
	if (signals)
		signals->on_disconnect_proxy(*G::Object::wrap<Action>(action), *G::Object::wrap<Widget>(proxy));
	else
	{
		GtkUIManagerClass *g_class = get_parent_class(merge);
		if (g_class && g_class->disconnect_proxy)
			g_class->disconnect_proxy(merge, action, proxy);
	}
}
	
void
Gtk::UIManagerClass::pre_activate_proxy(GtkUIManager *merge, GtkAction *action)
{
	UIManagerSignals *signals = dynamic_cast<UIManagerSignals*>(G::ObjectSignals::pointer((GObject*)merge));
	if (signals)
		signals->on_pre_activate(*G::Object::wrap<Action>(action));
	else
	{
		GtkUIManagerClass *g_class = get_parent_class(merge);
		if (g_class && g_class->pre_activate)
			g_class->pre_activate(merge, action);
	}
}
	
void
Gtk::UIManagerClass::post_activate_proxy(GtkUIManager *merge, GtkAction *action)
{
	UIManagerSignals *signals = dynamic_cast<UIManagerSignals*>(G::ObjectSignals::pointer((GObject*)merge));
	if (signals)
		signals->on_post_activate(*G::Object::wrap<Action>(action));
	else
	{
		GtkUIManagerClass *g_class = get_parent_class(merge);
		if (g_class && g_class->post_activate)
			g_class->post_activate(merge, action);
	}
}

/*  Gtk::UIManager signals
 */

const Gtk::UIManager::AddWidgetSignalType Gtk::UIManager::add_widget_signal("add_widget", (GCallback)&Marshal::void_widget_callback2);

const Gtk::UIManager::ActionsChangedSignalType Gtk::UIManager::actions_changed_signal("actions_changed", (GCallback)&G::Marshal::void_callback);

const Gtk::UIManager::ConnectProxySignalType Gtk::UIManager::connect_proxy_signal("connect_proxy", (GCallback)&Marshal::void_action_widget_callback);

const Gtk::UIManager::DisconnectProxySignalType Gtk::UIManager::disconnect_proxy_signal("disconnect_proxy", (GCallback)&Marshal::void_action_widget_callback);

const Gtk::UIManager::PreActivateSignalType Gtk::UIManager::pre_activate_signal("pre_activate", (GCallback)&Marshal::void_action_callback);

const Gtk::UIManager::PostActivateSignalType Gtk::UIManager::post_activate_signal("post_activate", (GCallback)&Marshal::void_action_callback);
	
