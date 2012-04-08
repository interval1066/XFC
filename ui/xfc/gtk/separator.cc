/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  separator.cc - GtkSeparator, GtkHSeparator and GtkVSeparator C++ wrapper implementation
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
 
#include "separator.hh"
#include "private/separatorclass.hh"

using namespace Xfc;

/*  Gtk::Separator
 */

Gtk::Separator::Separator(GtkSeparator *separator, bool owns_reference)
: Widget((GtkWidget*)separator, owns_reference)
{
}

Gtk::Separator::Separator()
: Widget((GtkWidget*)SeparatorClass::create())
{
}

Gtk::Separator::~Separator()
{
}

/*  Gtk::SeparatorClass
 */

void
Gtk::SeparatorClass::init(GtkSeparatorClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
}

GType
Gtk::SeparatorClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SEPARATOR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::SeparatorClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::HSeparator
 */

Gtk::HSeparator::HSeparator(GtkHSeparator *hseparator, bool owns_reference)
: Separator((GtkSeparator*)hseparator, owns_reference)
{
}

Gtk::HSeparator::HSeparator() 
: Separator((GtkSeparator*)HSeparatorClass::create())
{
}

Gtk::HSeparator::~HSeparator() 
{
}

/*  Gtk::HSeparatorClass
 */

void
Gtk::HSeparatorClass::init(GtkHSeparatorClass *g_class)
{
	SeparatorClass::init((GtkSeparatorClass*)g_class);
}

GType
Gtk::HSeparatorClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_HSEPARATOR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::HSeparatorClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::VSeparator
 */

Gtk::VSeparator::VSeparator(GtkVSeparator *vseparator, bool owns_reference)
: Separator((GtkSeparator*)vseparator, owns_reference)
{
}

Gtk::VSeparator::VSeparator() 
: Separator((GtkSeparator*)VSeparatorClass::create())
{
}

Gtk::VSeparator::~VSeparator() 
{
}

/*  Gtk::VSeparatorClass
 */

void
Gtk::VSeparatorClass::init(GtkVSeparatorClass *g_class)
{
	SeparatorClass::init((GtkSeparatorClass*)g_class);
}

GType
Gtk::VSeparatorClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_VSEPARATOR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::VSeparatorClass::create()
{
	return g_object_new(get_type(), 0);
}

