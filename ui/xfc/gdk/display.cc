/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  display.cc - GdkDisplay C++ wrapper interface
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
 
#include "display.hh"
#include "displaysignals.hh"
#include "input.hh"
#include "screen.hh"
#include "window.hh"
#include "private/displayclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gdk::Display
 */

Gdk::Display::Display(GdkDisplay *display, bool owns_reference)
: G::Object((GObject*)display, owns_reference)
{
}

Gdk::Display::~Display()
{
}
	
Gdk::Display*
Gdk::Display::get_default()
{
	return G::Object::wrap<Display>(gdk_display_get_default());
}

Gdk::Display*
Gdk::Display::open(const char *display_name)
{
	return G::Object::wrap<Display>(gdk_display_open(display_name));
}

Gdk::Display*
Gdk::Display::open(const String& display_name)
{
	return open(display_name.c_str());
}

String
Gdk::Display::get_name() const
{
	return gdk_display_get_name(gdk_display());
}

Gdk::Screen*
Gdk::Display::get_screen(int screen_num) const
{
	return G::Object::wrap<Screen>(gdk_display_get_screen(gdk_display(), screen_num));
}

Gdk::Screen*
Gdk::Display::get_default_screen() const
{
	return G::Object::wrap<Screen>(gdk_display_get_default_screen(gdk_display()));
}

bool
Gdk::Display::list_devices(std::vector<Device*>& devices) const
{
	g_return_val_if_fail(devices.empty(), false);

	GList *tmp_devices = gdk_display_list_devices(gdk_display());
	while (tmp_devices)
	{
		devices.push_back(G::Object::wrap<Device>((GdkDevice*)tmp_devices->data));
		tmp_devices = g_list_next(tmp_devices);
	}
	return !devices.empty();
}

Gdk::Device*
Gdk::Display::get_core_pointer() const
{
	return G::Object::wrap<Device>(gdk_display_get_core_pointer(gdk_display()));
}

void
Gdk::Display::get_pointer(Screen **screen, int *x, int *y, ModifierType *mask) const
{
	GdkScreen *tmp_screen = 0;
	gdk_display_get_pointer(gdk_display(), &tmp_screen, x, y, (GdkModifierType*)mask);
	if (screen && tmp_screen)
		*screen = G::Object::wrap<Screen>(tmp_screen);
}

void
Gdk::Display::get_pointer(Screen **screen, Point *point, ModifierType *mask) const
{
	int tmp_x, tmp_y;
	get_pointer(screen, &tmp_x, &tmp_y, mask);
	if (point)
		point->set(tmp_x, tmp_y);
}

Gdk::Point 
Gdk::Display::get_pointer(Screen **screen, ModifierType *mask) const
{
	int tmp_x, tmp_y;
	get_pointer(screen, &tmp_x, &tmp_y, mask);
	return Point(tmp_x, tmp_y);
}

Gdk::Window*
Gdk::Display::get_window_at_pointer(int *win_x, int *win_y) const
{
	GdkWindow *window = gdk_display_get_window_at_pointer(gdk_display(), win_x, win_y);
	return window ? G::Object::wrap<Window>(window) : 0;
}

Gdk::Window*
Gdk::Display::get_window_at_pointer(Point *win_origin) const
{
	int win_x, win_y;
	GdkWindow *window = gdk_display_get_window_at_pointer(gdk_display(), &win_x, &win_y);
	if (win_origin)
		win_origin->set(win_x, win_y);
	return window ? G::Object::wrap<Window>(window) : 0;
}

Gdk::Window* 
Gdk::Display::get_default_group() const
{
	GdkWindow *window = gdk_display_get_default_group(gdk_display());
	return window ? G::Object::wrap<Window>(window) : 0;
} 

Pointer<Gdk::Event>
Gdk::Display::get_event()
{
	Event *event = 0;
	GdkEvent *gdk_event = gdk_display_get_event(gdk_display());
	if (gdk_event)
		event = new Event(gdk_event, false);
	return event;
}

Pointer<Gdk::Event>
Gdk::Display::peek_event()
{
	Event *event = 0;
	GdkEvent *gdk_event = gdk_display_peek_event(gdk_display());
	if (gdk_event)
		event = new Event(gdk_event, false);
	return event;
}

void
Gdk::Display::put_event(const Gdk::Event& event)
{
	gdk_display_put_event(gdk_display(), event.gdk_event());
}

void 
Gdk::Display::store_clipboard(Window& clipboard_window, unsigned int time)
{
	gdk_display_store_clipboard(gdk_display(), clipboard_window.gdk_window(), time, 0, 0);
}

void 
Gdk::Display::store_clipboard(Window& clipboard_window, unsigned int time, const std::vector<Atom> targets)
{
	gdk_display_store_clipboard(gdk_display(), clipboard_window.gdk_window(), time, (GdkAtom*)&targets[0], targets.size());
}

/*  Gdk::DisplayClass
 */

void
Gdk::DisplayClass::init(GdkDisplayClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->closed = &closed_proxy;
}

GdkDisplayClass*
Gdk::DisplayClass::get_parent_class(void *instance)
{
	return static_cast<GdkDisplayClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gdk::DisplayClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_DISPLAY, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::DisplayClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gdk::DisplayClass::closed_proxy(GdkDisplay *display, gboolean is_error)
{
	DisplaySignals *signals = dynamic_cast<DisplaySignals*>(G::ObjectSignals::pointer((GObject*)display));
	if (signals)
		signals->on_closed(is_error);
	else
	{
		GdkDisplayClass *g_class = get_parent_class(display);
		if (g_class && g_class->closed)
			g_class->closed(display, is_error);
	}
}

/*  Gdk::Display signals
 */

const Gdk::Display::ClosedSignalType Gdk::Display::closed_signal("closed", (GCallback)&G::Marshal::void_bool_callback);

