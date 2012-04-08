/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  ruler.cc - GtkRuler, GtkHRuler and GtkVRuler C++ wrapper implementation
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
 
#include "ruler.hh"
#include "private/rulerclass.hh"

using namespace Xfc;

/*  Gtk::Ruler
 */

Gtk::Ruler::Ruler(GtkRuler *ruler, bool owns_reference)
: Widget((GtkWidget*)ruler, owns_reference)
{
}
	
Gtk::Ruler::Ruler()
: Widget((GtkWidget*)RulerClass::create())
{
}

Gtk::Ruler::~Ruler()
{
}

/*  Gtk::RulerClass
 */

void
Gtk::RulerClass::init(GtkRulerClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
}

GType
Gtk::RulerClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_RULER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::RulerClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::HRuler
 */

Gtk::HRuler::HRuler(GtkHRuler *hruler, bool owns_reference)
: Ruler((GtkRuler*)hruler, owns_reference)
{
}

Gtk::HRuler::HRuler()
: Ruler((GtkRuler*)HRulerClass::create())
{
}
	
Gtk::HRuler::HRuler(MetricType metric)
: Ruler((GtkRuler*)HRulerClass::create())
{
	set_metric(metric);
}
	
Gtk::HRuler::~HRuler()
{
}
	
/*  Gtk::HRulerClass
 */

void
Gtk::HRulerClass::init(GtkHRulerClass *g_class)
{
	RulerClass::init((GtkRulerClass*)g_class);
}

GType
Gtk::HRulerClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_HRULER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::HRulerClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::VRuler
 */

Gtk::VRuler::VRuler(GtkVRuler *vruler, bool owns_reference)
: Ruler((GtkRuler*)vruler, owns_reference)
{
}
	
Gtk::VRuler::VRuler()
: Ruler((GtkRuler*)VRulerClass::create())
{
}

Gtk::VRuler::VRuler(MetricType metric)
: Ruler((GtkRuler*)VRulerClass::create())
{
	set_metric(metric);
}

Gtk::VRuler::~VRuler() 
{
}
	
/*  Gtk::VRulerClass
 */

void
Gtk::VRulerClass::init(GtkVRulerClass *g_class)
{
	RulerClass::init((GtkRulerClass*)g_class);
}

GType
Gtk::VRulerClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_VRULER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::VRulerClass::create()
{
	return g_object_new(get_type(), 0);
}

