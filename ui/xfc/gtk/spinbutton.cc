/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  spinbutton.cc - GtkSpinButton C++ wrapper implementation
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
 
#include "spinbutton.hh"
#include "spinbuttonsignals.hh"
#include "private/marshal.hh"
#include "private/spinbuttonclass.hh"
#include <math.h>
#include <stdlib.h>

const int max_digits = 20;

using namespace Xfc;

/*  Gtk::SpinButton
 */

Gtk::SpinButton::SpinButton(GtkSpinButton *spin_button, bool owns_reference)
: Entry((GtkEntry*)spin_button, owns_reference)
{
}

Gtk::SpinButton::SpinButton()
: Entry((GtkEntry*)SpinButtonClass::create())
{
}

Gtk::SpinButton::SpinButton(Adjustment *adjustment, double climb_rate, unsigned int digits)
: Entry((GtkEntry*)SpinButtonClass::create())
{
	configure(adjustment, climb_rate, digits);
}

Gtk::SpinButton::SpinButton(double min, double max, double step)
: Entry((GtkEntry*)SpinButtonClass::create())
{
	g_return_if_fail(min < max);
	g_return_if_fail(step != 0.0);

	GtkObject *adjustment = gtk_adjustment_new(min, min, max, step, 10 * step, step);
	int digits;
	if (fabs(step) >= 1.0 || step == 0.0)
    	digits = 0;
  	else
	{
	    digits = abs((int)floor(log10(fabs(step))));
		if (digits > max_digits)
			digits = max_digits;
	}

	gtk_spin_button_configure(gtk_spin_button(), (GtkAdjustment*)adjustment, step, digits);
	set_numeric(true);
}

Gtk::SpinButton::~SpinButton()
{
}

Gtk::Adjustment*
Gtk::SpinButton::get_adjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_spin_button_get_adjustment(gtk_spin_button()));
}

void
Gtk::SpinButton::configure(Adjustment *adjustment, double climb_rate, unsigned int digits)
{
	gtk_spin_button_configure(gtk_spin_button(), *adjustment, climb_rate, digits);
}

void
Gtk::SpinButton::set_adjustment(Adjustment *adjustment)
{
	gtk_spin_button_set_adjustment(gtk_spin_button(), *adjustment);
}


/*  Gtk::SpinButtonClass
 */

void
Gtk::SpinButtonClass::init(GtkSpinButtonClass *g_class)
{
	EntryClass::init((GtkEntryClass*)g_class);
	g_class->input = &input_proxy;
	g_class->output = &output_proxy;
	g_class->value_changed = &value_changed_proxy;
}

GtkSpinButtonClass*
Gtk::SpinButtonClass::get_parent_class(void *instance)
{
	return static_cast<GtkSpinButtonClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::SpinButtonClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SPIN_BUTTON, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::SpinButtonClass::create()
{
	return g_object_new(get_type(), 0);
}

gint
Gtk::SpinButtonClass::input_proxy(GtkSpinButton *spin_button, gdouble *new_value)
{
	gint result = 0;
	SpinButtonSignals *signals = dynamic_cast<SpinButtonSignals*>(G::ObjectSignals::pointer((GObject*)spin_button));
	if (signals)
		result = signals->on_input(new_value);
	else
	{
		GtkSpinButtonClass *g_class = get_parent_class(spin_button);
		if (g_class && g_class->input)
			result = g_class->input(spin_button, new_value);
	}
	return result;
}

gint
Gtk::SpinButtonClass::output_proxy(GtkSpinButton *spin_button)
{
	gint result = 0;
	SpinButtonSignals *signals = dynamic_cast<SpinButtonSignals*>(G::ObjectSignals::pointer((GObject*)spin_button));
	if (signals)
		result = signals->on_output();
	else
	{
		GtkSpinButtonClass *g_class = get_parent_class(spin_button);
		if (g_class && g_class->output)
			result = g_class->output(spin_button);
	}
	return result;
}

void
Gtk::SpinButtonClass::value_changed_proxy(GtkSpinButton *spin_button)
{
	SpinButtonSignals *signals = dynamic_cast<SpinButtonSignals*>(G::ObjectSignals::pointer((GObject*)spin_button));
	if (signals)
		signals->on_value_changed();
	else
	{
		GtkSpinButtonClass *g_class = get_parent_class(spin_button);
		if (g_class && g_class->value_changed)
			g_class->value_changed(spin_button);
	}
}

/*  Gtk::SpinButton signals
 */

const Gtk::SpinButton::InputSignalType Gtk::SpinButton::input_signal("input", (GCallback)&Marshal::int_pdouble_callback);

const Gtk::SpinButton::OutputSignalType Gtk::SpinButton::output_signal("output", (GCallback)&Marshal::int_callback);

const Gtk::SpinButton::ValueChangedSignalType Gtk::SpinButton::value_changed_signal("value_changed", (GCallback)&G::Marshal::void_callback);

