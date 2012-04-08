/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  radioaction.cc - GtkRadioAction C++ wrapper implementation
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

#include "radioaction.hh"
#include "radioactionsignals.hh"
#include "accelkey.hh"
#include "stockid.hh"
#include "private/marshal.hh"
#include "private/radioactionclass.hh"
#include "xfc/glib/quark.hh"

using namespace Xfc;

namespace { // AccelKeyQuark
 
const G::Quark AccelKeyQuark("gfc_action_accel_key");

} // namespace

/*  Gtk::RadioAction
 */

Gtk::RadioAction::RadioAction(GtkRadioAction *action, bool owns_reference)
: ToggleAction((GtkToggleAction*)action, owns_reference)
{
}

Gtk::RadioAction::RadioAction(const RadioAction *group, const char *name, const char *label, int value)
: ToggleAction((GtkToggleAction*)RadioActionClass::create(name))
{
	g_object_set(g_object(), "label", label, "value", value, 0);
	if (group)	
		set_group(group->get_group());
}
	
Gtk::RadioAction::RadioAction(const RadioAction *group, const String& name, const String& label, int value)
: ToggleAction((GtkToggleAction*)RadioActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "label", label.c_str(), "value", value, 0);
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioAction::RadioAction(const RadioAction *group, const char *name, const StockId& stock_id, int value)
: ToggleAction((GtkToggleAction*)RadioActionClass::create(name))
{
	g_object_set(g_object(), "stock_id", stock_id.c_str(), "value", value, 0);
	if (group)	
		set_group(group->get_group());
}
	
Gtk::RadioAction::RadioAction(const RadioAction *group, const String& name, const StockId& stock_id, int value)
: ToggleAction((GtkToggleAction*)RadioActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "stock_id", stock_id.c_str(), "value", value, 0);
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioAction::RadioAction(const RadioAction *group, const char *name, const char *label, const StockId& stock_id, int value)
: ToggleAction((GtkToggleAction*)RadioActionClass::create(name))
{
	g_object_set(g_object(), "label", label, "stock_id", stock_id.c_str(), "value", value, 0);
	if (group)	
		set_group(group->get_group());
}
	
Gtk::RadioAction::RadioAction(const RadioAction *group, const String& name, const String& label, const StockId& stock_id, int value)
: ToggleAction((GtkToggleAction*)RadioActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "label", label.c_str(), "stock_id", stock_id.c_str(), "value", value, 0);
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioAction::~RadioAction()
{
}

int 
Gtk::RadioAction::get_value() const
{
	int value;
	g_object_get(g_object(), "value", &value, 0);
	return value;
}

/*  Gtk::RadioActionClass
 */

void
Gtk::RadioActionClass::init(GtkRadioActionClass *g_class)
{
	ToggleActionClass::init((GtkToggleActionClass*)g_class);
	g_class->changed = &changed_proxy;
}

GtkRadioActionClass*
Gtk::RadioActionClass::get_parent_class(void *instance)
{
	return static_cast<GtkRadioActionClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::RadioActionClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_RADIO_ACTION, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::RadioActionClass::create(const char *name)
{
	return g_object_new(get_type(), "name", name, 0);
}

void
Gtk::RadioActionClass::changed_proxy(GtkRadioAction *action, GtkRadioAction *current)
{
	RadioActionSignals *signals = dynamic_cast<RadioActionSignals*>(G::ObjectSignals::pointer((GObject*)action));
	if (signals)
		signals->on_changed(*G::Object::wrap<RadioAction>(current));
	else
	{
		GtkRadioActionClass *g_class = get_parent_class(action);
		if (g_class && g_class->changed)
			g_class->changed(action, current);
	}
}

/*  Gtk::RadioAction signals
 */
 
const Gtk::RadioAction::ChangedSignalType Gtk::RadioAction::changed_signal("changed", (GCallback)&Marshal::void_radioaction_callback);

/*  Gtk::RadioActions
 */
 
Gtk::RadioActions::RadioActions()
: group_(0)
{
}
	
Gtk::RadioActions::~RadioActions()
{
	clear();
}

Gtk::RadioAction* 
Gtk::RadioActions::add(const char *name, const char *label, int value, const char *tooltip)
{
	RadioAction *action = new RadioAction(group_, name, label, value);
	group_ = action;
	if (tooltip)
		action->set_tooltip(tooltip);
	actions_.push_back(action);
	return action;
}
	
Gtk::RadioAction* 
Gtk::RadioActions::add(const char *name, const char *label, const AccelKey& accel_key, int value, const char *tooltip)
{
	RadioAction *action = new RadioAction(group_, name, label, value);
	group_ = action;
	if (tooltip)
		action->set_tooltip(tooltip);
	action->set_data(AccelKeyQuark, new AccelKey(accel_key));
	actions_.push_back(action);
	return action;
}
	
Gtk::RadioAction* 
Gtk::RadioActions::add(const char *name, const StockId& stock_id, int value, const char *tooltip)
{
	return add(name, 0, stock_id, value, tooltip);
}

Gtk::RadioAction* 
Gtk::RadioActions::add(const char *name, const StockId& stock_id, const AccelKey& accel_key, int value, const char *tooltip)
{
	return add(name, 0, stock_id, accel_key, value, tooltip);
}

Gtk::RadioAction* 
Gtk::RadioActions::add(const char *name, const char *label, const StockId& stock_id, int value, const char *tooltip)
{
	RadioAction *action = new RadioAction(group_, name, label, stock_id, value);
	group_ = action;
	if (tooltip)
		action->set_tooltip(tooltip);
	actions_.push_back(action);
	return action;
}
	
Gtk::RadioAction* 
Gtk::RadioActions::add(const char *name, const char *label, const StockId& stock_id, const AccelKey& accel_key, int value, const char *tooltip)
{
	RadioAction *action = new RadioAction(group_, name, label, stock_id, value);
	group_ = action;
	if (tooltip)
		action->set_tooltip(tooltip);
	action->set_data(AccelKeyQuark, new AccelKey(accel_key));
	actions_.push_back(action);
	return action;
}

void 
Gtk::RadioActions::clear()
{
	for (unsigned int i = 0; i < actions_.size(); i++)
	{ 	
		AccelKey *accel_key = reinterpret_cast<AccelKey*>(actions_[i]->get_data(AccelKeyQuark));
		if (accel_key)
			delete accel_key;		
		actions_[i]->unref();
	}
	actions_.clear();
	group_ = 0;
}

