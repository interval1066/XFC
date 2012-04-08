/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toggleaction.cc - GtkToggleAction C++ wrapper implementation
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

#include "toggleaction.hh"
#include "toggleactionsignals.hh"
#include "stockid.hh"
#include "private/marshal.hh"
#include "private/toggleactionclass.hh"

using namespace Xfc;

/*  Gtk::ToggleAction
 */

Gtk::ToggleAction::ToggleAction(GtkToggleAction *action, bool owns_reference)
: Action((GtkAction*)action, owns_reference)
{
}

Gtk::ToggleAction::ToggleAction(const char *name, const char *label, bool is_active)
: Action((GtkAction*)ToggleActionClass::create(name))
{
	g_object_set(g_object(), "label", label, 0);
	set_active(is_active);
}
	
Gtk::ToggleAction::ToggleAction(const String& name, const String& label, bool is_active)
: Action((GtkAction*)ToggleActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "label", label.c_str(), 0);
	set_active(is_active);
}

Gtk::ToggleAction::ToggleAction(const char *name, const StockId& stock_id, bool is_active)
: Action((GtkAction*)ToggleActionClass::create(name))
{
	g_object_set(g_object(), "stock_id", stock_id.c_str(), 0);
	set_active(is_active);
}
	
Gtk::ToggleAction::ToggleAction(const String& name, const StockId& stock_id, bool is_active)
: Action((GtkAction*)ToggleActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "stock_id", stock_id.c_str(), 0);
	set_active(is_active);
}

Gtk::ToggleAction::ToggleAction(const char *name, const char *label, const StockId& stock_id, bool is_active)
: Action((GtkAction*)ToggleActionClass::create(name))
{
	g_object_set(g_object(), "label", label, "stock_id", stock_id.c_str(), 0);
	set_active(is_active);
}
	
Gtk::ToggleAction::ToggleAction(const String& name, const String& label, const StockId& stock_id, bool is_active)
: Action((GtkAction*)ToggleActionClass::create(name.c_str()))
{
	g_object_set(g_object(), "label", label.c_str(), "stock_id", stock_id.c_str(), 0);
	set_active(is_active);
}

Gtk::ToggleAction::~ToggleAction()
{
}

/*  Gtk::ToggleActionClass
 */

void
Gtk::ToggleActionClass::init(GtkToggleActionClass *g_class)
{
	ActionClass::init((GtkActionClass*)g_class);
	g_class->toggled = &toggled_proxy;
}

GtkToggleActionClass*
Gtk::ToggleActionClass::get_parent_class(void *instance)
{
	return static_cast<GtkToggleActionClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ToggleActionClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TOGGLE_ACTION, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ToggleActionClass::create(const char *name)
{
	return g_object_new(get_type(), "name", name, 0);
}

void
Gtk::ToggleActionClass::toggled_proxy(GtkToggleAction *action)
{
	ToggleActionSignals *signals = dynamic_cast<ToggleActionSignals*>(G::ObjectSignals::pointer((GObject*)action));
	if (signals)
		signals->on_toggled();
	else
	{
		GtkToggleActionClass *g_class = get_parent_class(action);
		if (g_class && g_class->toggled)
			g_class->toggled(action);
	}
}

/*  Gtk::ToggleAction signals
 */

const Gtk::ToggleAction::ToggledSignalType Gtk::ToggleAction::toggled_signal("toggled", (GCallback)&G::Marshal::void_callback);

