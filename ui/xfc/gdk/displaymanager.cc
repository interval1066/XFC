/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  displaymanager.cc - GdkDisplayManager C++ wrapper interface
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
 
#include "displaymanager.hh"
#include "displaymanagersignals.hh"
#include "display.hh"
#include "private/displaymanagerclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gdk::DisplayManager
 */

Gdk::DisplayManager::DisplayManager(GdkDisplayManager *display_manager, bool owns_reference)
: G::Object((GObject*)display_manager, owns_reference)
{
}

Gdk::DisplayManager::~DisplayManager()
{
}
	
Gdk::DisplayManager*
Gdk::DisplayManager::get()
{
	return G::Object::wrap<DisplayManager>(gdk_display_manager_get());
}

Gdk::Display*
Gdk::DisplayManager::get_default_display() const
{
	return G::Object::wrap<Display>(gdk_display_manager_get_default_display(gdk_display_manager()));
}

bool 
Gdk::DisplayManager::list_displays(std::vector<Display*>& displays) const
{
	g_return_val_if_fail(displays.empty(), false);
	GSList *first = gdk_display_manager_list_displays(gdk_display_manager());
	GSList *next = first;

	while (next)
	{
		displays.push_back(G::Object::wrap<Display>((GdkDisplay*)next->data));
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !displays.empty();
}

void
Gdk::DisplayManager::set_default_display(const Display& display)
{
	gdk_display_manager_set_default_display(gdk_display_manager(), display.gdk_display());
}

/*  Gdk::DisplayManagerClass
 */

void
Gdk::DisplayManagerClass::init(GdkDisplayManagerClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->display_opened = &display_opened_proxy;
}

GdkDisplayManagerClass*
Gdk::DisplayManagerClass::get_parent_class(void *instance)
{
	return static_cast<GdkDisplayManagerClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gdk::DisplayManagerClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_DISPLAY_MANAGER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::DisplayManagerClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gdk::DisplayManagerClass::display_opened_proxy(GdkDisplayManager *display_manager, GdkDisplay *display)
{
	DisplayManagerSignals *signals = dynamic_cast<DisplayManagerSignals*>(G::ObjectSignals::pointer((GObject*)display_manager));
	if (signals)
		signals->on_display_opened(*G::Object::wrap<Display>(display));
	else
	{
		GdkDisplayManagerClass *g_class = get_parent_class(display_manager);
		if (g_class && g_class->display_opened)
			g_class->display_opened(display_manager, display);
	}
}

/*  Gdk::DisplayManager signals
 */

const Gdk::DisplayManager::DisplayOpenedSignalType Gdk::DisplayManager::display_opened_signal("display_opened", (GCallback)&Marshal::void_display_callback);

