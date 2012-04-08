/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  radiobutton.cc - GtkRadioButton C++ wrapper implementation
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
 
#include "radiobutton.hh"
#include "radiobuttonsignals.hh"
#include "private/radiobuttonclass.hh"
#include "xfc/glib/private/marshal.hh"

using namespace Xfc;

/*  Gtk::RadioButton
 */

Gtk::RadioButton::RadioButton(GtkRadioButton *radio_button, bool owns_reference)
: CheckButton((GtkCheckButton*)radio_button, owns_reference)
{
}

Gtk::RadioButton::RadioButton()
: CheckButton((GtkCheckButton*)RadioButtonClass::create())
{
}

Gtk::RadioButton::RadioButton(const RadioButton *group)
: CheckButton((GtkCheckButton*)RadioButtonClass::create())
{
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioButton::RadioButton(const RadioButton *group, const char *label, bool use_underline)
: CheckButton((GtkCheckButton*)RadioButtonClass::create())
{
	set_label(label);
	set_use_underline(use_underline);
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioButton::RadioButton(const RadioButton *group, const String& label, bool use_underline)
: CheckButton((GtkCheckButton*)RadioButtonClass::create())
{
	set_label(label);
	set_use_underline(use_underline);
	if (group)	
		set_group(group->get_group());
}

Gtk::RadioButton::~RadioButton()
{
}

/*  Gtk::RadioButtonClass
 */

void
Gtk::RadioButtonClass::init(GtkRadioButtonClass *g_class)
{
	CheckButtonClass::init((GtkCheckButtonClass*)g_class);
	g_class->group_changed = &group_changed_proxy;
}

GtkRadioButtonClass*
Gtk::RadioButtonClass::get_parent_class(void *instance)
{
	return static_cast<GtkRadioButtonClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::RadioButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_RADIO_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::RadioButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::RadioButtonClass::group_changed_proxy(GtkRadioButton *radio_button)
{
	RadioButtonSignals *signals = dynamic_cast<RadioButtonSignals*>(G::ObjectSignals::pointer((GObject*)radio_button));
	if (signals)
		signals->on_group_changed();
	else
	{
		GtkRadioButtonClass *g_class = get_parent_class(radio_button);
		if (g_class && g_class->group_changed)
			g_class->group_changed(radio_button);
	}
}

/*  Gtk::RadioButton signals
 */

const Gtk::RadioButton::GroupChangedSignalType Gtk::RadioButton::group_changed_signal("group-changed", (GCallback)&G::Marshal::void_callback);
