/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  adjustment.cc - GtkAdjustment C++ wrapper implementation
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
 
#include "adjustment.hh"
#include "adjustmentsignals.hh"
#include "private/adjustmentclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Adjustment
 */

Gtk::Adjustment::Adjustment(GtkAdjustment *adjustment, bool owns_reference)
: Object((GtkObject*)adjustment, owns_reference)
{
}

Gtk::Adjustment::Adjustment()
: Object((GtkObject*)AdjustmentClass::create())
{
}

Gtk::Adjustment::Adjustment(double lower, double upper, double step_increment, double page_increment, double page_size)
: Object((GtkObject*)AdjustmentClass::create())
{
	set_range(lower, upper, step_increment, page_increment, page_size);
}

Gtk::Adjustment::Adjustment(double value, double lower, double upper, double step_increment, double page_increment, double page_size)
: Object((GtkObject*)AdjustmentClass::create())
{
	set_value(value);	
	set_range(lower, upper, step_increment, page_increment, page_size);
}

Gtk::Adjustment::~Adjustment()
{
}

void
Gtk::Adjustment::set_range(double lower, double upper, double step_increment, double page_increment, double page_size)
{
	GtkAdjustment *adjustment = gtk_adjustment();
	adjustment->lower = MIN(lower, upper);
	adjustment->upper = MAX(lower, upper);
	double range = adjustment->upper - adjustment->lower;
	adjustment->step_increment = MIN(range, step_increment);
	adjustment->page_increment = MIN(range, page_increment);
	adjustment->page_size = MIN(range, page_size);
	set_value(CLAMP(get_value(), adjustment->lower, adjustment->upper));
	changed();
}

/*  Gtk::AdjustmentClass
 */

void
Gtk::AdjustmentClass::init(GtkAdjustmentClass *g_class)
{
	ObjectClass::init((GtkObjectClass*)g_class);
	g_class->changed = &changed_proxy;
	g_class->value_changed = &value_changed_proxy;
}

GtkAdjustmentClass*
Gtk::AdjustmentClass::get_parent_class(void *instance)
{
	return static_cast<GtkAdjustmentClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::AdjustmentClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ADJUSTMENT, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::AdjustmentClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::AdjustmentClass::changed_proxy(GtkAdjustment *adjustment)
{
	AdjustmentSignals *signals = dynamic_cast<AdjustmentSignals*>(G::ObjectSignals::pointer((GObject*)adjustment));
	if (signals)
		signals->on_changed();
	else
	{
		GtkAdjustmentClass *g_class = get_parent_class(adjustment);
		if (g_class && g_class->changed)
			g_class->changed(adjustment);
	}
}

void
Gtk::AdjustmentClass::value_changed_proxy(GtkAdjustment *adjustment)
{
	AdjustmentSignals *signals = dynamic_cast<AdjustmentSignals*>(G::ObjectSignals::pointer((GObject*)adjustment));
	if (signals)
		signals->on_value_changed();
	else
	{
		GtkAdjustmentClass *g_class = get_parent_class(adjustment);
		if (g_class && g_class->value_changed)
			g_class->value_changed(adjustment);
	}
}

/*  Gtk::Adjustment signals
 */

const Gtk::Adjustment::ChangedSignalType Gtk::Adjustment::changed_signal("changed", (GCallback)&G::Marshal::void_callback);

const Gtk::Adjustment::ValueChangedSignalType Gtk::Adjustment::value_changed_signal("value_changed", (GCallback)&G::Marshal::void_callback);

