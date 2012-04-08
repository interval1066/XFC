/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  dnd.cc - GdkDragContext C++ wrapper implementation
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
 
#include "dnd.hh"
#include "display.hh"
#include "screen.hh"
#include "window.hh"
#include "private/dndclass.hh"

using namespace Xfc;

/*  Gdk::DragContext
 */

Gdk::DragContext::DragContext(GdkDragContext *drag_context, bool owns_reference)
: G::Object((GObject*)drag_context, owns_reference)
{
}

Gdk::DragContext::DragContext()
: G::Object((GObject*)DragContextClass::create())
{
}

Gdk::DragContext::~DragContext()
{
}
	
Pointer<Gdk::DragContext>
Gdk::DragContext::drag_begin(const Window& window, const std::vector<Atom>& targets)
{
	g_return_val_if_fail(!targets.empty(), 0);
	GList *tmp_targets = 0;
	int count = targets.size();

	int i = 0;
	while (i < count)
	{
		tmp_targets = g_list_append(tmp_targets, GINT_TO_POINTER(targets[i]));
		++i;
	}

	GdkDragContext *context = gdk_drag_begin(window.gdk_window(), tmp_targets);
	g_list_free(tmp_targets);
	return G::Object::wrap<DragContext>(context);
}

Gdk::DragProtocol
Gdk::DragContext::protocol() const
{
	return (DragProtocol)gdk_drag_context()->protocol;
}

Gdk::Window*
Gdk::DragContext::source_window() const
{
	return G::Object::wrap<Window>(gdk_drag_context()->source_window);
}
	
Gdk::Window*
Gdk::DragContext::dest_window() const
{
	return G::Object::wrap<Window>(gdk_drag_context()->dest_window);
}

bool 
Gdk::DragContext::targets(std::vector<Atom>& target_list) const
{
	g_return_val_if_fail(target_list.empty(), false);

	GList *next = gdk_drag_context()->targets;
	while (next)
	{
		target_list.push_back((GdkAtom)GPOINTER_TO_INT(next->data));
		next = g_list_next(next);
	}

	return !target_list.empty();
}

unsigned int
Gdk::DragContext::drag_get_protocol(unsigned int xid, DragProtocol *protocol, const Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
 	return gdk_drag_get_protocol_for_display(tmp_display, xid, (GdkDragProtocol*)protocol);
}

void
Gdk::DragContext::find_window(int x_root, int y_root, Window **dest_window, DragProtocol *protocol, const Screen *screen)
{
	GdkScreen *tmp_screen = screen ? screen->gdk_screen() : gdk_drawable_get_screen(gdk_drag_context()->source_window);

	GdkWindow *tmp_window = 0;
	gdk_drag_find_window_for_screen(gdk_drag_context(), 0, tmp_screen, x_root, y_root, &tmp_window, (GdkDragProtocol*)protocol);

	if (tmp_window)
		*dest_window = G::Object::wrap<Window>(tmp_window);
}
	
bool
Gdk::DragContext::drag_motion(const Window& dest_window, DragProtocol protocol, int x_root, int y_root,
	                 DragActionField suggested_action, DragActionField possible_actions, unsigned int time)
{
	return gdk_drag_motion(gdk_drag_context(), dest_window.gdk_window(), (GdkDragProtocol)protocol, x_root,
	                       y_root, (GdkDragAction)suggested_action, (GdkDragAction)possible_actions, time);
}


/*  Gdk::DragContextClass
 */

void
Gdk::DragContextClass::init(GdkDragContextClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gdk::DragContextClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_DRAG_CONTEXT, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::DragContextClass::create()
{
	return g_object_new(get_type(), 0);
}

