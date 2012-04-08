/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toolbar.cc - GtkToolbar C++ wrapper implementation
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
 
#include "toolbar.hh"
#include "toolbarsignals.hh"
#include "tooltips.hh"
#include "private/toolbarclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Toolbar
 */

Gtk::Toolbar::Toolbar(GtkToolbar *toolbar, bool owns_reference)
: Container((GtkContainer*)toolbar, owns_reference)
{
}

Gtk::Toolbar::Toolbar()
: Container((GtkContainer*)ToolbarClass::create())
{
}

Gtk::Toolbar::Toolbar(Orientation orientation)
: Container((GtkContainer*)ToolbarClass::create())
{
	set_orientation(orientation);
}

Gtk::Toolbar::Toolbar(Orientation orientation, ToolbarStyle style)
: Container((GtkContainer*)ToolbarClass::create())
{
	set_orientation(orientation);
	set_style(style);
}

Gtk::Toolbar::~Toolbar()
{
}
	
Gtk::ToolItem*
Gtk::Toolbar::get_nth_item(int n) const
{
	return G::Object::wrap<ToolItem>(gtk_toolbar_get_nth_item(gtk_toolbar(), n));
}

void 
Gtk::Toolbar::append(ToolItem& item, const char *tooltip)
{
	insert(item, -1, tooltip);
}
	
void 
Gtk::Toolbar::append(ToolItem& item, const String& tooltip)
{
	insert(item, -1, tooltip.c_str());
}
	
void 
Gtk::Toolbar::prepend(ToolItem& item, const char *tooltip)
{
	insert(item, 0, tooltip);
}
	
void 
Gtk::Toolbar::prepend(ToolItem& item, const String& tooltip)
{
	insert(item, 0, tooltip.c_str());
}
	
void 
Gtk::Toolbar::insert(ToolItem& item, int pos, const char *tooltip)
{
	gtk_toolbar_insert(gtk_toolbar(), item.gtk_tool_item(), pos);
	if (tooltip)
		set_tooltip(item, tooltip);
}

void 
Gtk::Toolbar::insert(ToolItem& item, int pos, const String& tooltip)
{
	insert(item, pos, tooltip.c_str());
}

void 
Gtk::Toolbar::append_separator()
{
	insert_separator(-1);
}
	
void 
Gtk::Toolbar::insert_separator(int pos)
{
	GtkToolItem *separator = gtk_separator_tool_item_new();
	gtk_toolbar_insert(gtk_toolbar(), separator, pos);
	gtk_widget_show((GtkWidget*)separator);
}
	
void
Gtk::Toolbar::set_drop_highlight_item(ToolItem& item, int index)
{
	gtk_toolbar_set_drop_highlight_item(gtk_toolbar(), item.gtk_tool_item(), index);
}

void 
Gtk::Toolbar::set_tooltip(ToolItem& item, const char *tip_text, const char *tip_private)
{
	gtk_tool_item_set_tooltip(item.gtk_tool_item(), gtk_toolbar()->tooltips, tip_text, tip_private);	
}
	
void 
Gtk::Toolbar::set_tooltip(ToolItem& item, const String& tip_text, const String& tip_private)
{
	set_tooltip(item, tip_text.c_str(), tip_private.c_str());
}

/*  Gtk::ToolbarClass
 */

void
Gtk::ToolbarClass::init(GtkToolbarClass *g_class)
{
	ContainerClass::init((GtkContainerClass*)g_class);
	g_class->orientation_changed = &orientation_changed_proxy;
	g_class->style_changed = &style_changed_proxy;
	g_class->popup_context_menu = &popup_context_menu_proxy;
}

GtkToolbarClass*
Gtk::ToolbarClass::get_parent_class(void *instance)
{
	return static_cast<GtkToolbarClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ToolbarClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TOOLBAR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ToolbarClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ToolbarClass::orientation_changed_proxy(GtkToolbar *toolbar, GtkOrientation orientation)
{
	ToolbarSignals *signals = dynamic_cast<ToolbarSignals*>(G::ObjectSignals::pointer((GObject*)toolbar));
	if (signals)
		signals->on_orientation_changed((Orientation)orientation);
	else
	{
		GtkToolbarClass *g_class = get_parent_class(toolbar);
		if (g_class && g_class->orientation_changed)
			g_class->orientation_changed(toolbar, orientation);
	}
}

void
Gtk::ToolbarClass::style_changed_proxy(GtkToolbar *toolbar, GtkToolbarStyle style)
{
	ToolbarSignals *signals = dynamic_cast<ToolbarSignals*>(G::ObjectSignals::pointer((GObject*)toolbar));
	if (signals)
		signals->on_style_changed((ToolbarStyle)style);
	else
	{
		GtkToolbarClass *g_class = get_parent_class(toolbar);
		if (g_class && g_class->style_changed)
			g_class->style_changed(toolbar, style);
	}
}

gboolean
Gtk::ToolbarClass::popup_context_menu_proxy(GtkToolbar *toolbar, gint x, gint y, gint button_number)
{
	gboolean result = FALSE;
	ToolbarSignals *signals = dynamic_cast<ToolbarSignals*>(G::ObjectSignals::pointer((GObject*)toolbar));
	if (signals)
		result = signals->on_popup_context_menu(x, y, button_number);
	else
	{
		GtkToolbarClass *g_class = get_parent_class(toolbar);
		if (g_class && g_class->popup_context_menu)
			result = g_class->popup_context_menu(toolbar, x, y, button_number);
	}
	return result;
}

/*  Gtk::Toolbar signals
 */

const Gtk::Toolbar::OrientationChangedSignalType Gtk::Toolbar::orientation_changed_signal("orientation-changed", (GCallback)&Marshal::void_orientation_callback);

const Gtk::Toolbar::StyleChangedSignalType Gtk::Toolbar::style_changed_signal("style-changed", (GCallback)&Marshal::void_toolbarstyle_callback);

const Gtk::Toolbar::PopupContextMenuSignalType Gtk::Toolbar::popup_context_menu_signal("popup_context_menu", (GCallback)&Marshal::bool_int_int_int_callback);
