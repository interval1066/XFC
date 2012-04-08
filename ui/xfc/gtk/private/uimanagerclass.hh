/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  uimanagerclass.hh - Private interface
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

#ifndef XFC_GTK_UI_MANAGER_CLASS_H
#define XFC_GTK_UI_MANAGER_CLASS_H

#include <xfc/glib/private/objectclass.hh>

namespace Xfc {

namespace Gtk {

class UIManagerClass
{
public:
	static void init(GtkUIManagerClass *g_class);

	static GtkUIManagerClass* get_parent_class(void *instance);
	
	static GType get_type();

	static void* create();

	static void add_widget_proxy(GtkUIManager *merge, GtkWidget *widget);
	
	static void actions_changed_proxy(GtkUIManager *merge);
	
	static void connect_proxy_proxy(GtkUIManager *merge, GtkAction *action, GtkWidget *proxy);
	
	static void disconnect_proxy_proxy(GtkUIManager *merge, GtkAction *action, GtkWidget *proxy);
	
	static void pre_activate_proxy(GtkUIManager *merge, GtkAction *action);
	
	static void post_activate_proxy(GtkUIManager *merge, GtkAction *action);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_UI_MANAGER_CLASS_H

