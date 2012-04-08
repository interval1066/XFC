/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  misc.cc - GtkMisc C++ wrapper implementation
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
 
#include "misc.hh"
#include "private/miscclass.hh"

using namespace Xfc;

/*  Gtk::Misc
 */

Gtk::Misc::Misc(GtkMisc *misc, bool owns_reference)
:  Widget((GtkWidget*)misc, owns_reference)
{
}

Gtk::Misc::Misc()
: Widget((GtkWidget*)MiscClass::create())
{
}

Gtk::Misc::~Misc()
{
}

/*  Gtk::MiscClass
 */

void
Gtk::MiscClass::init(GtkMiscClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
}

GType
Gtk::MiscClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_MISC, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::MiscClass::create()
{
	return g_object_new(get_type(), 0);
}

