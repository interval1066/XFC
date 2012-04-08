/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  iconfactory.cc - GtkIconFactory C++ wrapper implementation
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
 
#include "iconfactory.hh"
#include "settings.hh"
#include "private/iconfactoryclass.hh"

using namespace Xfc;

/*  Gtk::icon_size_lookup
 */

bool
Gtk::icon_size_lookup(IconSize size, int *width, int *height, Settings *settings)
{
	GtkSettings *tmp_settings = *settings;
	if (!tmp_settings)
	{
		GdkScreen *screen = gdk_screen_get_default();
		tmp_settings = gtk_settings_get_for_screen(screen);
	}
	return gtk_icon_size_lookup_for_settings(tmp_settings, (GtkIconSize)size, width, height);
}

/*  Gtk::icon_size_register
 */

Gtk::IconSize
Gtk::icon_size_register(const String& name, int width, int height)
{
	return (IconSize)gtk_icon_size_register(name.c_str(), width, height);
}

/*  Gtk::icon_size_register_alias
 */

void
Gtk::icon_size_register_alias(const String& alias, IconSize target)
{
	gtk_icon_size_register_alias(alias.c_str(),(GtkIconSize)target);
}

/*  Gtk::icon_size_from_name
 */

Gtk::IconSize
Gtk::icon_size_from_name(const String& name)
{
	return (IconSize)gtk_icon_size_from_name(name.c_str());
}

/*  Gtk::icon_size_get_name
 */

String
Gtk::icon_size_get_name(IconSize size)
{
	return gtk_icon_size_get_name((GtkIconSize)size);
}

/*  Gtk::IconFactory
 */

Gtk::IconFactory::IconFactory(GtkIconFactory *icon_factory, bool owns_reference)
: G::Object((GObject*)icon_factory, owns_reference)
{
}

Gtk::IconFactory::IconFactory() 
: G::Object((GObject*)IconFactoryClass::create())
{
}

Gtk::IconFactory::~IconFactory() 
{
}

void
Gtk::IconFactory::add(const StockId& stock_id, IconSet& icon_set)
{
	gtk_icon_factory_add(gtk_icon_factory(), stock_id.c_str(), icon_set.gtk_icon_set());
}

Pointer<Gtk::IconSet>
Gtk::IconFactory::lookup(const StockId& stock_id)
{
	return G::Boxed::wrap<IconSet>(GTK_TYPE_ICON_SET, gtk_icon_factory_lookup(gtk_icon_factory(), stock_id.c_str()), true);
}

Pointer<Gtk::IconSet>
Gtk::IconFactory::lookup_default(const StockId& stock_id)
{
	return G::Boxed::wrap<IconSet>(GTK_TYPE_ICON_SET, gtk_icon_factory_lookup_default(stock_id.c_str()), true);
}

/*  Gtk::IconFactoryClass
 */

void
Gtk::IconFactoryClass::init(GtkIconFactoryClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::IconFactoryClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ICON_FACTORY, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::IconFactoryClass::create()
{
	return g_object_new(get_type(), 0);
}

