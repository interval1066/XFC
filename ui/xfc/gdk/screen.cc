/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  screen.cc - GdkScreen C++ wrapper interface
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
 
#include "screen.hh"
#include "screensignals.hh"
#include "color.hh"
#include "display.hh"
#include "events.hh"
#include "visual.hh"
#include "window.hh"
#include "private/marshal.hh"
#include "private/screenclass.hh"
#include "xfc/glib/value.hh"

using namespace Xfc;

/*  Gdk::Screen
 */

Gdk::Screen::Screen(GdkScreen *screen, bool owns_reference)
: G::Object((GObject*)screen, owns_reference)
{
}

Gdk::Screen::~Screen()
{
}
	
Gdk::Screen*
Gdk::Screen::get_default()
{
	return G::Object::wrap<Screen>(gdk_screen_get_default());
}

Gdk::Colormap*
Gdk::Screen::get_default_colormap() const
{
	return G::Object::wrap<Colormap>(gdk_screen_get_default_colormap(gdk_screen()));
}

Gdk::Colormap* 
Gdk::Screen::get_system_colormap() const
{
	return G::Object::wrap<Colormap>(gdk_screen_get_system_colormap(gdk_screen()));
}

const Gdk::Visual* 
Gdk::Screen::get_system_visual() const
{
	return G::Object::wrap<Visual>(gdk_screen_get_system_visual(gdk_screen()));
}

Gdk::Window* 
Gdk::Screen::get_root_window() const
{
	return G::Object::wrap<Window>(gdk_screen_get_root_window(gdk_screen()));
}

Gdk::Display* 
Gdk::Screen::get_display() const
{
	return G::Object::wrap<Display>(gdk_screen_get_display(gdk_screen()));
}

bool
Gdk::Screen::list_visuals(std::vector<const Visual*>& visuals) const
{
	g_return_val_if_fail(visuals.empty(), false);
	GList *first = gdk_screen_list_visuals(gdk_screen());
	GList *next = first;

	while (next)
	{
		visuals.push_back(G::Object::wrap<Visual>((GdkVisual*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !visuals.empty();
}

bool 
Gdk::Screen::get_toplevels(std::vector<Window*>& toplevels) const
{
	g_return_val_if_fail(toplevels.empty(), false);
	GList *first = gdk_screen_get_toplevel_windows(gdk_screen());
	GList *next = first;

	while (next)
	{
		toplevels.push_back(G::Object::wrap<Window>((GdkWindow*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !toplevels.empty();
}

String 
Gdk::Screen::make_display_name() const
{
	char *name = gdk_screen_make_display_name(gdk_screen());
	String s(name);
	g_free(name);
	return s;
}

void
Gdk::Screen::get_monitor_geometry(int monitor_num, Rectangle& dest) const
{
	return gdk_screen_get_monitor_geometry(gdk_screen(), monitor_num, dest.gdk_rectangle());
}

Gdk::Rectangle
Gdk::Screen::get_monitor_geometry(int monitor_num) const
{
	GdkRectangle rectangle;
	gdk_screen_get_monitor_geometry(gdk_screen(), monitor_num, &rectangle);
	return rectangle;
}

int
Gdk::Screen::get_monitor_at_point(const Point& point) const
{
	return gdk_screen_get_monitor_at_point(gdk_screen(), point.x(), point.y());
}

int
Gdk::Screen::get_monitor_at_window(const Window& window) const
{
	return gdk_screen_get_monitor_at_window(gdk_screen(), window.gdk_window());
}

bool
Gdk::Screen::get_setting(const char *name, G::Value& value) const
{
	return gdk_screen_get_setting(gdk_screen(), name, value.g_value());
}

bool
Gdk::Screen::get_setting(const String& name, G::Value& value) const
{
	return gdk_screen_get_setting(gdk_screen(), name.c_str(), value.g_value());
}

void
Gdk::Screen::set_default_colormap(Colormap& colormap)
{
	gdk_screen_set_default_colormap(gdk_screen(), colormap.gdk_colormap());
}

void 
Gdk::Screen::broadcast_client_message(Event& event)
{
	gdk_screen_broadcast_client_message(gdk_screen(), event.gdk_event());
}

/*  Gdk::ScreenClass
 */

void
Gdk::ScreenClass::init(GdkScreenClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->size_changed = &size_changed_proxy;
}

GdkScreenClass*
Gdk::ScreenClass::get_parent_class(void *instance)
{
	return static_cast<GdkScreenClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gdk::ScreenClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_SCREEN, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::ScreenClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gdk::ScreenClass::size_changed_proxy(GdkScreen *screen)
{
	ScreenSignals *signals = dynamic_cast<ScreenSignals*>(G::ObjectSignals::pointer((GObject*)screen));
	if (signals)
		signals->on_size_changed();
	else
	{
		GdkScreenClass *g_class = get_parent_class(screen);
		if (g_class && g_class->size_changed)
			g_class->size_changed(screen);
	}
}

/*  Gdk::Screen signals
 */

const Gdk::Screen::SizeChangedSignalType Gdk::Screen::size_changed_signal("size_changed", (GCallback)&G::Marshal::void_callback);

