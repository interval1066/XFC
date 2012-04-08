/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  gammacurve.cc - GtkGammaCurve C++ wrapper implementation
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
 
#include "gammacurve.hh"
#include "private/gammacurveclass.hh"

using namespace Xfc;

/*  Gtk::GammaCurve
 */

Gtk::GammaCurve::GammaCurve(GtkGammaCurve *gamma_curve, bool owns_reference)
: VBox((GtkVBox*)gamma_curve, owns_reference)
{
}
	
Gtk::GammaCurve::GammaCurve()
: VBox((GtkVBox*)GammaCurveClass::create())
{
}

Gtk::GammaCurve::~GammaCurve() 
{
}
	
/*  Gtk::GammaCurveClass
 */

void
Gtk::GammaCurveClass::init(GtkGammaCurveClass *g_class)
{
	VBoxClass::init((GtkVBoxClass*)g_class);
}

GType
Gtk::GammaCurveClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_GAMMA_CURVE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::GammaCurveClass::create()
{
	return g_object_new(get_type(), 0);
}

