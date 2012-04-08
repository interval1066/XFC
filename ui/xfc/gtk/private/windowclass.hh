/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  window_p.h - Private interface
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

#ifndef XFC_GTK_WINDOW_CLASS_H
#define XFC_GTK_WINDOW_CLASS_H

#include <xfc/gtk/private/binclass.hh>

namespace Xfc {

namespace Gtk {

/*  Gtk::WindowClass
 */

class WindowClass
{
public:
	static void init(GtkWindowClass *g_class);

	static GtkWindowClass* get_parent_class(void *instance);

	static GType get_type();

	static void* create(GtkWindowType type);

	static void set_focus_proxy(GtkWindow *window, GtkWidget *focus);

	static gboolean frame_event_proxy(GtkWindow *window, GdkEvent *event);

	static void keys_changed_proxy(GtkWindow *window);
};

/*  Gtk::WindowGroupClass
 */

class WindowGroupClass
{
public:
	static void init(GtkWindowGroupClass *g_class);
	
	static GType get_type();

	static void* create();
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_WINDOW_CLASS_H

