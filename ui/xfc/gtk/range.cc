/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  range.cc - GtkRange C++ wrapper implmentation
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
 
#include "range.hh"
#include "rangesignals.hh"
#include "private/marshal.hh"
#include "private/rangeclass.hh"

using namespace Xfc;

/*  Gtk::Range
 */

Gtk::Range::Range(GtkRange *range, bool owns_reference)
: Widget((GtkWidget*)range, owns_reference)
{
}

Gtk::Range::Range()
: Widget((GtkWidget*)RangeClass::create())
{
}

Gtk::Range::~Range()
{
}

Gtk::UpdateType
Gtk::Range::get_policy() const
{
	return (UpdateType)gtk_range_get_update_policy(gtk_range());
}

Gtk::Adjustment*
Gtk::Range::get_adjustment() const
{
	return G::Object::wrap<Adjustment>(gtk_range_get_adjustment(gtk_range()));
}

void
Gtk::Range::set_adjustment(Adjustment *adjustment)
{
	gtk_range_set_adjustment(gtk_range(), *adjustment);
}

/*  Gtk::RangeClass
 */

void
Gtk::RangeClass::init(GtkRangeClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
	g_class->value_changed = &value_changed_proxy;
	g_class->adjust_bounds = &adjust_bounds_proxy;
}

GtkRangeClass*
Gtk::RangeClass::get_parent_class(void *instance)
{
	return static_cast<GtkRangeClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::RangeClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_RANGE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::RangeClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::RangeClass::value_changed_proxy(GtkRange *range)
{
	RangeSignals *signals = dynamic_cast<RangeSignals*>(G::ObjectSignals::pointer((GObject*)range));
	if (signals)
		signals->on_value_changed();
	else
	{
		GtkRangeClass *g_class = get_parent_class(range);
		if (g_class && g_class->value_changed)
			g_class->value_changed(range);
	}
}

void
Gtk::RangeClass::adjust_bounds_proxy(GtkRange *range, gdouble new_value)
{
	RangeSignals *signals = dynamic_cast<RangeSignals*>(G::ObjectSignals::pointer((GObject*)range));
	if (signals)
		signals->on_adjust_bounds(new_value);
	else
	{
		GtkRangeClass *g_class = get_parent_class(range);
		if (g_class && g_class->adjust_bounds)
			g_class->adjust_bounds(range, new_value);
	}
}

/*  Gtk::Range signals
 */

const Gtk::Range::ValueChangedSignalType Gtk::Range::value_changed_signal("value_changed", (GCallback)&G::Marshal::void_callback);

const Gtk::Range::AdjustBoundsSignalType Gtk::Range::adjust_bounds_signal("adjust_bounds", (GCallback)&Marshal::void_double_callback);

