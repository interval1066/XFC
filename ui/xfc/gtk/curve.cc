/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  curve.cc - GtkCurve C++ wrapper implementation
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
 
#include "curve.hh"
#include "curvesignals.hh"
#include "private/curveclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Curve
 */

Gtk::Curve::Curve(GtkCurve *curve, bool owns_reference)
: DrawingArea((GtkDrawingArea*)curve, owns_reference)
{
}
	
Gtk::Curve::Curve()
: DrawingArea((GtkDrawingArea*)CurveClass::create())
{
}

Gtk::Curve::~Curve() 
{
}
	
/*  Gtk::CurveClass
 */

void
Gtk::CurveClass::init(GtkCurveClass *g_class)
{
	DrawingAreaClass::init((GtkDrawingAreaClass*)g_class);
	g_class->curve_type_changed = &curve_type_changed_proxy;
}

GtkCurveClass*
Gtk::CurveClass::get_parent_class(void *instance)
{
	return static_cast<GtkCurveClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::CurveClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CURVE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CurveClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::CurveClass::curve_type_changed_proxy(GtkCurve *curve)
{
	CurveSignals *signals = dynamic_cast<CurveSignals*>(G::ObjectSignals::pointer((GObject*)curve));
	if (signals)
		signals->on_curve_type_changed();
	else
	{
		GtkCurveClass *g_class = get_parent_class(curve);
		if (g_class && g_class->curve_type_changed)
			g_class->curve_type_changed(curve);
	}
}

/*  Gtk::Curve signals
 */

const Gtk::Curve::CurveTypeChangedSignalType Gtk::Curve::curve_type_changed_signal("curve_type_changed", (GCallback)&G::Marshal::void_callback);

