/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  actiongroup.cc - GtkActionGroup C++ wrapper implementation
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

#include "actiongroup.hh"
#include "private/actiongroupclass.hh"
#include "private/marshal.hh"
#include "accelmap.hh"
#include "stock.hh"
#include "xfc/glib/quark.hh"

using namespace Xfc;

namespace { // AccelKeyQuark
 
const G::Quark AccelKeyQuark("gfc_action_accel_key");

} // namespace

/*  Gtk::ActionGroup
 */

Gtk::ActionGroup::ActionGroup(GtkActionGroup *action_group, bool owns_reference)
: G::Object((GObject*)action_group, owns_reference)
{
}

Gtk::ActionGroup::ActionGroup(const char *name)
: G::Object((GObject*)ActionGroupClass::create(name))
{
}

Gtk::ActionGroup::ActionGroup(const String& name)
: G::Object((GObject*)ActionGroupClass::create(name.c_str()))
{
}

Gtk::ActionGroup::~ActionGroup()
{
}

String
Gtk::ActionGroup::get_name() const
{
	return gtk_action_group_get_name(gtk_action_group());
}

Gtk::Action*
Gtk::ActionGroup::get_action(const char *action_name)
{
	return G::Object::wrap<Action>(gtk_action_group_get_action(gtk_action_group(), action_name));
}

Gtk::Action*
Gtk::ActionGroup::get_action(const String &action_name)
{
	return get_action(action_name.c_str());
}

bool
Gtk::ActionGroup::list_actions(std::vector<Action*>& actions) const
{
	g_return_val_if_fail(actions.empty(), false);
	GList *first = gtk_action_group_list_actions(gtk_action_group());
	GList *next = first;

	while (next)
	{
		actions.push_back(G::Object::wrap<Action>((GtkAction*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !actions.empty();
}

void
Gtk::ActionGroup::add_action(Action& action)
{
	gtk_action_group_add_action(gtk_action_group(), action.gtk_action());
}			

void 
Gtk::ActionGroup::add_action(Action& action, const AccelKey& accel_key)
{
	String path = "<Actions>/" + get_name() + "/" + action.get_name();	
	Gtk::AccelMap::add_entry(path, accel_key);	
	action.set_accel_path(path);
	gtk_action_group_add_action(gtk_action_group(), action.gtk_action());
}

void
Gtk::ActionGroup::add_action(Action& action, const ActivateSlot& slot)
{
	add_action(action);
	action.signal_activate().connect(slot);	
}			

void 
Gtk::ActionGroup::add_action(Action& action, const AccelKey& accel_key, const ActivateSlot& slot)
{
	add_action(action, accel_key);
	action.signal_activate().connect(slot);	
}

void 
Gtk::ActionGroup::add_action(RadioAction& action, const AccelKey& accel_key)
{
	add_action(static_cast<Action&>(action), accel_key);
}

void 
Gtk::ActionGroup::add_action(RadioAction& action, const ChangedSlot& slot)
{
	add_action(action);
	action.signal_changed().connect(slot);	
}

void 
Gtk::ActionGroup::add_action(RadioAction& action, const AccelKey& accel_key, const ChangedSlot& slot)
{
	add_action(action, accel_key);
	action.signal_changed().connect(slot);	
}

void 
Gtk::ActionGroup::add_actions(const RadioActions& group, int value, const ChangedSlot& slot)
{
	g_return_if_fail(!group.actions_.empty());
	for (unsigned int i = 0; i < group.actions_.size(); i++)
	{
		if (value == group.actions_[i]->get_value())
			group.actions_[i]->set_active(true);			
		AccelKey *accel_key = reinterpret_cast<AccelKey*>(group.actions_[i]->get_data(AccelKeyQuark));
		if (accel_key)
			add_action(*group.actions_[i], *accel_key);
		else				
			add_action(*group.actions_[i]);
	}
	group.actions_[0]->signal_changed().connect(slot);	
}
	
void
Gtk::ActionGroup::remove_action(Action& action)
{
	gtk_action_group_remove_action(gtk_action_group(), action.gtk_action());
}

Gtk::Action* 
Gtk::ActionGroup::add(const char *name, const char *label, const char *tooltip)
{
	Action *action = new Action(name, label);
	if (tooltip)
		action->set_tooltip(tooltip);
	add_action(*action);
	action->unref();
	return action;
}

Gtk::Action* 
Gtk::ActionGroup::add(const char *name, const char *label, const AccelKey& accel_key, const char *tooltip)
{
	Action *action = new Action(name, label);
	if (tooltip)
		action->set_tooltip(tooltip);
	add_action(*action, accel_key);
	action->unref();
	return action;
}

Gtk::Action* 
Gtk::ActionGroup::add(const char *name, const StockId& stock_id, const char *tooltip)
{
	return add(name, 0, stock_id, tooltip);	
}

Gtk::Action* 
Gtk::ActionGroup::add(const char *name, const StockId& stock_id, const AccelKey& accel_key, const char *tooltip)
{
	return add(name, 0, stock_id, accel_key, tooltip);
}

Gtk::Action* 
Gtk::ActionGroup::add(const char *name, const char *label, const StockId& stock_id, const char *tooltip)
{
	Action *action = new Action(name, label, stock_id);
	if (tooltip)
		action->set_tooltip(tooltip);
	add_action(*action);
	action->unref();
	return action;
}

Gtk::Action* 
Gtk::ActionGroup::add(const char *name, const char *label, const StockId& stock_id, const AccelKey& accel_key, const char *tooltip)
{
	Action *action = new Action(name, label, stock_id);
	if (tooltip)
		action->set_tooltip(tooltip);
	add_action(*action, accel_key);
	action->unref();
	return action;
}

Gtk::ToggleAction* 
Gtk::ActionGroup::add(const char *name, const char *label, bool is_active, const char *tooltip)
{
	ToggleAction *action = new ToggleAction(name, label, is_active);
	if (tooltip)
		action->set_tooltip(tooltip);
	add_action(*action);
	action->unref();
	return action;
}
	
Gtk::ToggleAction* 
Gtk::ActionGroup::add(const char *name, const char *label, const AccelKey& accel_key, bool is_active, const char *tooltip)
{
	ToggleAction *action = new ToggleAction(name, label, is_active);
	if (tooltip)
		action->set_tooltip(tooltip);
	add_action(*action, accel_key);
	action->unref();
	return action;
}
	
Gtk::ToggleAction* 
Gtk::ActionGroup::add(const char *name, const StockId& stock_id, bool is_active, const char *tooltip)
{
	return add(name, 0, stock_id, is_active, tooltip);
}
	
Gtk::ToggleAction* 
Gtk::ActionGroup::add(const char *name, const StockId& stock_id, const AccelKey& accel_key, bool is_active, const char *tooltip)
{
	return add(name, 0, stock_id, accel_key, is_active, tooltip);
}
	
Gtk::ToggleAction* 
Gtk::ActionGroup::add(const char *name, const char *label, const StockId& stock_id, bool is_active, const char *tooltip)
{
	ToggleAction *action = new ToggleAction(name, label, stock_id, is_active);
	if (tooltip)
		action->set_tooltip(tooltip);
	add_action(*action);
	action->unref();
	return action;
}
	
Gtk::ToggleAction* 
Gtk::ActionGroup::add(const char *name, const char *label, const StockId& stock_id, const AccelKey& accel_key, bool is_active, const char *tooltip)
{
	ToggleAction *action = new ToggleAction(name, label, stock_id, is_active);
	if (tooltip)
		action->set_tooltip(tooltip);
	add_action(*action, accel_key);
	action->unref();
	return action;
}

/*  Gtk::ActionGroupClass
 */

void
Gtk::ActionGroupClass::init(GtkActionGroupClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::ActionGroupClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ACTION_GROUP, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ActionGroupClass::create(const char *name)
{
	return g_object_new(get_type(), "name", name, 0);
}

/*  Gtk::ActionGroup signals
 */

const Gtk::ActionGroup::ConnectProxySignalType Gtk::ActionGroup::connect_proxy_signal("connect_proxy", (GCallback)&Marshal::void_action_widget_callback);

const Gtk::ActionGroup::DisconnectProxySignalType Gtk::ActionGroup::disconnect_proxy_signal("disconnect_proxy", (GCallback)&Marshal::void_action_widget_callback);

const Gtk::ActionGroup::PreActivateSignalType Gtk::ActionGroup::pre_activate_signal("pre_activate", (GCallback)&Marshal::void_action_callback);

const Gtk::ActionGroup::PostActivateSignalType Gtk::ActionGroup::post_activate_signal("post_activate", (GCallback)&Marshal::void_action_callback);
