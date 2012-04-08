/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  scale.cc - GtkScale, GtkHScale and GtkVScale C++ wrapper implementation
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
 
#include "scale.hh"
#include "scalesignals.hh"
#include "adjustment.hh"
#include "private/marshal.hh"
#include "private/scaleclass.hh"
#include "../pango/layout.hh"
#include <math.h>
#include <stdlib.h>

using namespace Xfc;

/*  Gtk::Scale
 */
 
Gtk::Scale::Scale(GtkScale *scale, bool owns_reference)
: Range((GtkRange*)scale, owns_reference)
{
}

Gtk::Scale::Scale()
: Range((GtkRange*)ScaleClass::create())
{
}

Gtk::Scale::~Scale()
{
}

Pango::Layout* 
Gtk::Scale::get_layout() const
{
	return G::Object::wrap<Pango::Layout>(gtk_scale_get_layout(gtk_scale()));
}

/*  Gtk::ScaleClass
 */

void
Gtk::ScaleClass::init(GtkScaleClass *g_class)
{
	RangeClass::init((GtkRangeClass*)g_class);
	g_class->format_value = &format_value_proxy;
}

GtkScaleClass*
Gtk::ScaleClass::get_parent_class(void *instance)
{
	return static_cast<GtkScaleClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ScaleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SCALE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ScaleClass::create()
{
	return g_object_new(get_type(), 0);
}

gchar*
Gtk::ScaleClass::format_value_proxy(GtkScale *scale, gdouble value)
{
	gchar *fmt = 0;
	ScaleSignals *signals = dynamic_cast<ScaleSignals*>(G::ObjectSignals::pointer((GObject*)scale));
	if (signals)
		fmt = signals->on_format_value(value);
	else
	{
		GtkScaleClass *g_class = get_parent_class(scale);
		if (g_class && g_class->format_value)
			fmt = g_class->format_value(scale, value);
	}
	return fmt;
}

/*  Gtk::Scale signals
 */

const Gtk::Scale::FormatValueSignalType Gtk::Scale::format_value_signal("format_value", (GCallback)&Marshal::pchar_double_callback);

namespace {

void construct_scale_with_range(GtkScale *scale, gdouble min, gdouble max, gdouble step)
{
	g_return_if_fail(min < max);
	g_return_if_fail(step != 0.0);

	GtkObject *adjustment = gtk_adjustment_new (min, min, max, step, 10 * step, 0);
	g_object_set(scale, "adjustment", adjustment, 0);

	gint digits;
	if (fabs(step) >= 1.0 || step == 0.0)
    	digits = 0;
  	else
	{
	    digits = abs((gint)floor(log10(fabs(step))));
		if (digits > 5)
			digits = 5;
	}
	gtk_scale_set_digits(scale, digits);
}

} // namespace

/*  Gtk::HScale
 */
 
Gtk::HScale::HScale(GtkHScale *hscale, bool owns_reference)
: Scale((GtkScale*)hscale, owns_reference)
{
}

Gtk::HScale::HScale()
: Scale((GtkScale*)HScaleClass::create())
{
}

Gtk::HScale::HScale(Adjustment& adjustment)
: Scale((GtkScale*)HScaleClass::create())
{
	g_object_set(g_object(), "adjustment", adjustment.gtk_adjustment(), 0);
}

Gtk::HScale::HScale(double min, double max, double step)
: Scale((GtkScale*)HScaleClass::create())
{
	construct_scale_with_range(gtk_scale(), min, max, step);
}

Gtk::HScale::~HScale()
{
}

/*  Gtk::HScaleClass
 */

void
Gtk::HScaleClass::init(GtkHScaleClass *g_class)
{
	ScaleClass::init((GtkScaleClass*)g_class);
}

GType
Gtk::HScaleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_HSCALE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::HScaleClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::VScale
 */

Gtk::VScale::VScale(GtkVScale *vscale, bool owns_reference)
: Scale((GtkScale*)vscale, owns_reference)
{
}

Gtk::VScale::VScale()
: Scale((GtkScale*)VScaleClass::create())
{
}

Gtk::VScale::VScale(Adjustment& adjustment)
: Scale((GtkScale*)VScaleClass::create())
{
	g_object_set(g_object(), "adjustment", adjustment.gtk_adjustment(), 0);
}

Gtk::VScale::VScale(double min, double max, double step)
: Scale((GtkScale*)VScaleClass::create())
{
	construct_scale_with_range(gtk_scale(), min, max, step);
}

Gtk::VScale::~VScale()
{
}

/*  Gtk::VScaleClass
 */

void
Gtk::VScaleClass::init(GtkVScaleClass *g_class)
{
	ScaleClass::init((GtkScaleClass*)g_class);
}

GType
Gtk::VScaleClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_VSCALE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::VScaleClass::create()
{
	return g_object_new(get_type(), 0);
}

