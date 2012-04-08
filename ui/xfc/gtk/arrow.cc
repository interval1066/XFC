/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  arrow.cc - GtkArrow C++ wrapper implementation
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
 
#include "arrow.hh"
#include "private/arrowclass.hh"

using namespace Xfc;

/*  Gtk::Arrow
 */

Gtk::Arrow::Arrow(GtkArrow *arrow, bool owns_reference)
: Misc((GtkMisc*)arrow, owns_reference)
{
}

Gtk::Arrow::Arrow()
: Misc((GtkMisc*)ArrowClass::create())
{
}

Gtk::Arrow::Arrow(ArrowType arrow_type, ShadowType shadow_type)
: Misc((GtkMisc*)ArrowClass::create())
{
	set(arrow_type, shadow_type);
}

Gtk::Arrow::~Arrow()
{
}

/*  Gtk::ArrowClass
 */

void
Gtk::ArrowClass::init(GtkArrowClass *g_class)
{
	MiscClass::init((GtkMiscClass*)g_class);
}

GType
Gtk::ArrowClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ARROW, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ArrowClass::create()
{
	return g_object_new(get_type(), 0);
}

