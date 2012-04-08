/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  window.cc - GtkWindow and GtkWindowGroup C++ wrapper implementation
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

#include "window.hh"
#include "windowsignals.hh"
#include "accelgroup.hh"
#include "private/marshal.hh"
#include "private/windowclass.hh"
#include "xfc/gdk/events.hh"
#include "xfc/gdk/screen.hh"
#include "xfc/gdk/window.hh"
#include "xfc/gdk-pixbuf/pixbuf.hh"
#include "xfc/glib/error.hh"
#include "xfc/glib/quark.hh"
#include "xfc/glib/private/objectclass.hh"
#include "xfc/convert.hh"
#include <gtk/gtkaboutdialog.h>

using namespace Xfc;

/*  Gtk::Window
 */

Gtk::Window::Window(GtkWindow *window, bool owns_reference)
: Bin((GtkBin*)window, owns_reference)
{
}

Gtk::Window::Window(WindowType type)
: Bin((GtkBin*)WindowClass::create((GtkWindowType)type))
{
}

Gtk::Window::~Window()
{
	if (instance_)
	{
		remove_data(G::ObjectClass::quark());
		dispose();		
		instance_ = 0;
	}
}

String
Gtk::Window::get_title() const
{
	return gtk_window_get_title(gtk_window());
}

String
Gtk::Window::get_role() const
{
	return gtk_window_get_role(gtk_window());
}

Gtk::Widget*
Gtk::Window::get_focus() const
{
	return G::Object::wrap<Widget>(gtk_window_get_focus(gtk_window()));
}

Gtk::Window*
Gtk::Window::get_transient_for() const
{
	GtkWindow *window = gtk_window_get_transient_for(gtk_window());
	return window ? G::Object::wrap<Window>(window) : 0;
}

Gdk::WindowTypeHint
Gtk::Window::get_type_hint() const
{
	return (Gdk::WindowTypeHint)gtk_window_get_type_hint(gtk_window());
}

Gdk::Screen*
Gtk::Window::get_screen() const
{
	return G::Object::wrap<Gdk::Screen>(gtk_window_get_screen(gtk_window()));
}

String 
Gtk::Window::get_icon_name() const
{
	return gtk_window_get_icon_name(gtk_window());
}

namespace { // real_get_icon_list

bool real_get_icon_list(GtkWindow *window, std::vector<Gdk::Pixbuf*>& icons)
{
	g_return_val_if_fail(icons.empty(), false);
	
	GList *first = window ? gtk_window_get_icon_list(window) : gtk_window_get_default_icon_list();
	GList *next = first;

	while (next)
	{
		icons.push_back(G::Object::wrap<Gdk::Pixbuf>((GdkPixbuf*)next->data));
		next = g_list_next(next);
	}
	g_list_free(first);
	return !icons.empty();
}

} // real_get_icon_list

bool 
Gtk::Window::get_icon_list(std::vector<Gdk::Pixbuf*>& icons) const
{
	return real_get_icon_list(gtk_window(), icons);
}

Gdk::Pixbuf*
Gtk::Window::get_icon() const
{
	GdkPixbuf *icon = gtk_window_get_icon(gtk_window());
	return icon ? G::Object::wrap<Gdk::Pixbuf>(icon) : 0;
}

bool 
Gtk::Window::get_default_icon_list(std::vector<Gdk::Pixbuf*>& icons)
{
	return real_get_icon_list(0, icons);
}

Gdk::Point
Gtk::Window::get_position() const
{
	int root_x, root_y;
	get_position(&root_x, &root_y);
	return Gdk::Point(root_x, root_y);
}

void
Gtk::Window::set_title(const String& title)
{
	gtk_window_set_title(gtk_window(), title.c_str());
}

void
Gtk::Window::set_wmclass(const String& wmclass_name, const String& wmclass_class)
{
	gtk_window_set_wmclass(gtk_window(), wmclass_name.c_str(), wmclass_class.c_str());
}

void
Gtk::Window::set_role(const String& role)
{
	gtk_window_set_role(gtk_window(), role.c_str());
}

Gtk::AccelGroup*
Gtk::Window::add_accel_group(AccelGroup *accel_group)
{
	AccelGroup *tmp_accel_group = accel_group;
	
	if (!tmp_accel_group)
		tmp_accel_group = new Gtk::AccelGroup;

	gtk_window_add_accel_group(gtk_window(), *tmp_accel_group);
	
	if (!accel_group)
		tmp_accel_group->unref();
	
	return tmp_accel_group;
}

void
Gtk::Window::remove_accel_group(AccelGroup& accel_group)
{
	gtk_window_remove_accel_group(gtk_window(), accel_group.gtk_accel_group());
}

void
Gtk::Window::set_focus(Widget *widget)
{
	gtk_window_set_focus(gtk_window(), *widget);
}

void
Gtk::Window::set_default(Widget *default_widget)
{
	gtk_window_set_default(gtk_window(), *default_widget);
}

void
Gtk::Window::set_transient_for(Window *parent)
{
	gtk_window_set_transient_for(gtk_window(), parent->gtk_window());
}

void
Gtk::Window::set_geometry_hints(Widget *geometry_widget, const Gdk::Geometry& geometry)
{
	gtk_window_set_geometry_hints(gtk_window(), *geometry_widget, geometry.gdk_geometry(), geometry.gdk_window_hints());
}

void 
Gtk::Window::set_screen(const Gdk::Screen& screen)
{
	gtk_window_set_screen(gtk_window(), screen.gdk_screen());
}

namespace { // real_set_icon_list

void real_set_icon_list(GtkWindow *window, std::vector<Gdk::Pixbuf*>& icons)
{
	g_return_if_fail(!icons.empty());
	GList *tmp_icons = 0;
	int count = icons.size();

	int i = 0;
	while (i < count)
	{
		tmp_icons = g_list_append(tmp_icons, icons[i]->gdk_pixbuf());
		++i;
	}
 	window ? gtk_window_set_icon_list(window, tmp_icons) : gtk_window_set_default_icon_list(tmp_icons);
  	g_list_free(tmp_icons);
}

} // real_set_icon_list

void
Gtk::Window::set_icon_list(std::vector<Gdk::Pixbuf*>& icons)
{
	real_set_icon_list(gtk_window(), icons);
}

void 
Gtk::Window::set_icon(Gdk::Pixbuf& icon)
{
	gtk_window_set_icon(gtk_window(), icon.gdk_pixbuf());
}
	
bool
Gtk::Window::set_icon_from_file(const char *filename, G::Error *error)
{
	return gtk_window_set_icon_from_file(gtk_window(), filename, *error);
}

void 
Gtk::Window::set_icon_name(const String& name)
{
	set_icon_name(name.c_str());
}

bool
Gtk::Window::set_icon_from_file(const String& filename, G::Error *error)
{
	return gtk_window_set_icon_from_file(gtk_window(), filename.c_str(), *error);
}

void 
Gtk::Window::show_about_dialog(Gdk::Pixbuf *logo, const String& name, const String& version, const String& comments,
                               const String& copyright, const String& website, const std::vector<String> *authors, 
                               const std::vector<String> *documenters, const String& license)
{
	char **tmp_authors = authors ? vector_of_string_to_array(*authors) : 0;	
	char **tmp_documenters = documenters ? vector_of_string_to_array(*documenters) : 0;	

	gtk_show_about_dialog(gtk_window(), 
			      "logo", logo ? logo->gdk_pixbuf() : 0, 
	                      "name", name.c_str(), 
			      "version", version.c_str(), 
			      "copyright", copyright.c_str(), 
			      "website", website.c_str(), 
	                      "comments", comments.c_str(),
			      "authors", tmp_authors, 
			      "documenters", tmp_documenters, 
			      "license", license.c_str(),
			      0);

	if (tmp_authors)
		delete [] tmp_authors;
		
	if (tmp_documenters)
		delete [] tmp_documenters;
}

void
Gtk::Window::set_default_icon_list(std::vector<Gdk::Pixbuf*>& icons)
{
	real_set_icon_list(0, icons);
}

void
Gtk::Window::set_default_icon(Gdk::Pixbuf& icon)
{
	gtk_window_set_default_icon(icon.gdk_pixbuf());
}

void 
Gtk::Window::set_default_icon_name(const String& name)
{
	gtk_window_set_default_icon_name(name.c_str());
}

bool
Gtk::Window::set_default_icon_from_file(const String& filename, G::Error *error)
{
	return gtk_window_set_default_icon_from_file(filename.c_str(), *error);
}

bool
Gtk::Window::list_toplevels(std::vector<Widget*>& toplevels)
{
	g_return_val_if_fail(toplevels.empty(), false);
	GList *first = gtk_window_list_toplevels();
	GList *next = first;

	while (next)
	{
		toplevels.push_back(G::Object::wrap<Widget>((GtkWidget*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !toplevels.empty();
}

void
Gtk::Window::add_mnemonic(unsigned int keyval, Widget& target)
{
	gtk_window_add_mnemonic(gtk_window(), keyval, target.gtk_widget());	
}		

void 
Gtk::Window::remove_mnemonic(unsigned int keyval, Widget& target)
{
	gtk_window_remove_mnemonic(gtk_window(), keyval, target.gtk_widget());
}

bool 
Gtk::Window::activate_key(const Gdk::EventKey& event)
{
	return gtk_window_activate_key(gtk_window(), event.gdk_event_key());
}

bool 
Gtk::Window::propagate_key_event(const Gdk::EventKey& event)
{
	return gtk_window_propagate_key_event(gtk_window(), event.gdk_event_key());
}

void
Gtk::Window::move(const Gdk::Point& point)
{
	move(point.x(), point.y());
}

bool
Gtk::Window::parse_geometry(const String& geometry)
{
	return gtk_window_parse_geometry(gtk_window(), geometry.c_str());
}

/*  Gtk::WindowClass
 */

void
Gtk::WindowClass::init(GtkWindowClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
	g_class->set_focus = &set_focus_proxy;
	g_class->frame_event = &frame_event_proxy;
	g_class->keys_changed = &keys_changed_proxy;
}

GtkWindowClass*
Gtk::WindowClass::get_parent_class(void *instance)
{
	return static_cast<GtkWindowClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::WindowClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_WINDOW, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::WindowClass::create(GtkWindowType type)
{
	return g_object_new(get_type(), "type", type, 0);
}

void
Gtk::WindowClass::set_focus_proxy(GtkWindow *window, GtkWidget *focus)
{
	WindowSignals *signals = dynamic_cast<WindowSignals*>(G::ObjectSignals::pointer((GObject*)window));
	if (signals)
		signals->on_set_focus(G::Object::wrap<Gtk::Widget>(focus));
	else
	{
		GtkWindowClass *g_class = get_parent_class(window);
		if (g_class && g_class->set_focus)
			g_class->set_focus(window, focus);
	}
}

gboolean
Gtk::WindowClass::frame_event_proxy(GtkWindow *window, GdkEvent *event)
{
	gboolean result = FALSE;
	WindowSignals *signals = dynamic_cast<WindowSignals*>(G::ObjectSignals::pointer((GObject*)window));
	if (signals)
	{
		Gdk::Event tmp_event(event);
		signals->on_frame_event(tmp_event);
	}
	else
	{
		GtkWindowClass *g_class = get_parent_class(window);
		if (g_class && g_class->frame_event)
			result = g_class->frame_event(window, event);
	}
	return result;
}

void
Gtk::WindowClass::keys_changed_proxy(GtkWindow *window)
{
	WindowSignals *signals = dynamic_cast<WindowSignals*>(G::ObjectSignals::pointer((GObject*)window));
	if (signals)
		signals->on_keys_changed();
	else
	{
		GtkWindowClass *g_class = get_parent_class(window);
		if (g_class && g_class->keys_changed)
			g_class->keys_changed(window);
	}
}

/*  Gtk::Window signals
 */

const Gtk::Window::SetFocusSignalType Gtk::Window::set_focus_signal("set_focus", (GCallback)&Marshal::void_widget_callback1);

const Gtk::Window::FrameEventSignalType Gtk::Window::frame_event_signal("frame_event", (GCallback)&Marshal::bool_event_callback);

const Gtk::Window::KeysChangedSignalType Gtk::Window::keys_changed_signal("keys_changed", (GCallback)&G::Marshal::void_callback);

/*  Gtk::WindowGroup
 */
 
Gtk::WindowGroup::WindowGroup(GtkWindowGroup *group, bool owns_reference)
: G::Object((GObject*)group, owns_reference)
{
}
	
Gtk::WindowGroup::WindowGroup()
: G::Object((GObject*)WindowGroupClass::create())
{
}

Gtk::WindowGroup::~WindowGroup() 
{
}

void
Gtk::WindowGroup::add_window(Window& window)
{
	gtk_window_group_add_window(gtk_window_group(), window.gtk_window());
}

void
Gtk::WindowGroup::remove_window(Window& window)
{
	gtk_window_group_remove_window(gtk_window_group(), window.gtk_window());
}

/*  Gtk::WindowGroupClass
 */

void
Gtk::WindowGroupClass::init(GtkWindowGroupClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::WindowGroupClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_WINDOW_GROUP, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::WindowGroupClass::create()
{
	return g_object_new(get_type(), 0);
}

