/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  icontheme.cc - GtkIconTheme C++ wrapper implementation
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

#include "icontheme.hh"
#include "iconthemesignals.hh"
#include "private/iconthemeclass.hh"
#include "private/marshal.hh"
#include "../gdk/screen.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include "xfc/glib/error.hh"

using namespace Xfc;

/*  Gtk::IconInfo
 */
 
Gtk::IconInfo::IconInfo(GtkIconInfo *icon_info)
: G::Boxed(GTK_TYPE_ICON_INFO, icon_info)
{
}

Gtk::IconInfo::IconInfo(GtkIconInfo *icon_info, bool copy)
: G::Boxed(GTK_TYPE_ICON_INFO, icon_info, copy)
{
}

Gtk::IconInfo::IconInfo(const IconInfo& src)
: G::Boxed(GTK_TYPE_ICON_INFO, src.g_boxed(), true)
{
}

Gtk::IconInfo::~IconInfo()
{
}

Gtk::IconInfo&
Gtk::IconInfo::operator=(const IconInfo& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

String 
Gtk::IconInfo::get_filename() const
{
	return gtk_icon_info_get_filename(gtk_icon_info());
}

Gdk::Pixbuf* 
Gtk::IconInfo::get_builtin_pixbuf() const
{
	return G::Object::wrap<Gdk::Pixbuf>(gtk_icon_info_get_builtin_pixbuf(gtk_icon_info()));
}
	 
bool 
Gtk::IconInfo::get_embedded_rect(Gdk::Rectangle& rectangle) const
{
	return gtk_icon_info_get_embedded_rect(gtk_icon_info(), rectangle.gdk_rectangle());
}

std::vector<Gdk::Point> 
Gtk::IconInfo::get_attach_points() const
{
	GdkPoint *tmp_points = 0;
	int count = 0;
	gtk_icon_info_get_attach_points(gtk_icon_info(), &tmp_points, &count);

	std::vector<Gdk::Point> points;
	int i = 0;
	while (i < count)
	{
		points.push_back(tmp_points[i]);
		++i;
	}

	g_free(tmp_points);
	return points;
}

String 
Gtk::IconInfo::get_display_name() const
{
	return gtk_icon_info_get_display_name(gtk_icon_info());
}

Pointer<Gdk::Pixbuf> 
Gtk::IconInfo::load_icon(G::Error *error)
{
	GdkPixbuf *pixbuf = gtk_icon_info_load_icon(gtk_icon_info(), *error);
	return pixbuf ? G::Object::wrap<Gdk::Pixbuf>(pixbuf) : 0;
}
	
void 
Gtk::IconInfo::set_raw_coordinates(bool raw_coordinates)
{
	return gtk_icon_info_set_raw_coordinates(gtk_icon_info(), raw_coordinates);
}

/*  Gtk::IconTheme
 */

Gtk::IconTheme::IconTheme(GtkIconTheme *icon_theme, bool owns_reference)
: G::Object((GObject*)icon_theme, owns_reference)
{
}

Gtk::IconTheme::IconTheme()
: G::Object((GObject*)IconThemeClass::create())
{
}

Gtk::IconTheme::~IconTheme()
{
}

Gtk::IconTheme* 
Gtk::IconTheme::get_for_screen(const Gdk::Screen *screen)
{
	GdkScreen *tmp_screen = screen ? screen->gdk_screen() : gdk_screen_get_default();
	return G::Object::wrap<IconTheme>(gtk_icon_theme_get_for_screen(tmp_screen));
}

std::vector<String>
Gtk::IconTheme::get_search_path() const
{
	char **tmp_path = 0;
	gtk_icon_theme_get_search_path(gtk_icon_theme(), &tmp_path, 0);
	std::vector<String> path;
	int i = 0;	
	while (tmp_path[i])
	{
		String s(tmp_path[i]);
		path.push_back(s);
		++i;
	}
	g_strfreev(tmp_path);
	return path;
}  

String 
Gtk::IconTheme::get_example_icon_name() const
{
	char *icon_name = gtk_icon_theme_get_example_icon_name(gtk_icon_theme());
	String s(icon_name);
	g_free(icon_name);
	return s;
}

bool 
Gtk::IconTheme::has_icon(const String& icon_name) const
{
	return has_icon(icon_name.c_str());
}

std::vector<int> 
Gtk::IconTheme::get_icon_sizes(const char *icon_name) const
{
	std::vector<int> sizes;
	int *tmp_sizes = gtk_icon_theme_get_icon_sizes(gtk_icon_theme(), icon_name);
	
	int i = 0;	
	while (tmp_sizes && tmp_sizes[i] != 0)
	{
		sizes.push_back(tmp_sizes[i]);
		++i;
	}
	
	g_free(tmp_sizes);
	return sizes;
}
	
std::vector<int> 
Gtk::IconTheme::get_icon_sizes(const String& icon_name) const
{
	return get_icon_sizes(icon_name.c_str());
}

void 
Gtk::IconTheme::set_screen(Gdk::Screen *screen)
{
	gtk_icon_theme_set_screen(gtk_icon_theme(), *screen);
}

void 
Gtk::IconTheme::set_search_path(const std::vector<String>& path)
{
	g_return_if_fail(!path.empty());
	int count = path.size();
	const char **tmp_path = new const char*[count];

	int i = 0;	
	while (i < count)
	{
		tmp_path[i] = path[i].c_str();
		++i;
	}

	gtk_icon_theme_set_search_path(gtk_icon_theme(), tmp_path, count);
	delete [] tmp_path;
}

void 
Gtk::IconTheme::append_search_path(const String& path)
{
	append_search_path(path.c_str());
}

void 
Gtk::IconTheme::prepend_search_path(const String& path)
{
	prepend_search_path(path.c_str());
}

void 
Gtk::IconTheme::set_custom_theme(const String& theme_name)
{
	set_custom_theme(theme_name.c_str());
}
	
Pointer<Gtk::IconInfo> 
Gtk::IconTheme::lookup_icon(const char *icon_name, int size, IconLookupFlagsField flags)
{
	GtkIconInfo *info = gtk_icon_theme_lookup_icon(gtk_icon_theme(), icon_name, size, (GtkIconLookupFlags)flags);	
	return info ? G::Boxed::wrap<IconInfo>(GTK_TYPE_ICON_INFO, info, false) : 0;
}
	
Pointer<Gtk::IconInfo> 
Gtk::IconTheme::lookup_icon(const String& icon_name, int size, IconLookupFlagsField flags)
{
	return lookup_icon(icon_name.c_str(), size, flags);
}


Pointer<Gdk::Pixbuf> 
Gtk::IconTheme::load_icon(const char *icon_name, int size, IconLookupFlagsField flags, G::Error *error)
{
	GdkPixbuf *pixbuf = gtk_icon_theme_load_icon(gtk_icon_theme(), icon_name, size, (GtkIconLookupFlags)flags, *error);
	return pixbuf ? G::Object::wrap<Gdk::Pixbuf>(pixbuf) : 0;
}

Pointer<Gdk::Pixbuf> 
Gtk::IconTheme::load_icon(const String& icon_name, int size, IconLookupFlagsField flags, G::Error *error)
{
	return load_icon(icon_name, size, flags, error);
}

std::vector<String> 
Gtk::IconTheme::list_icons(const char *context)
{
	std::vector<String> icons;
	GList *first = gtk_icon_theme_list_icons(gtk_icon_theme(), context);
	GList *next = first;

	while (next)
	{
		char *icon_name = (char*)next->data;
		icons.push_back(icon_name);
		g_free(icon_name);
		next = g_list_next(next);
	}

	g_list_free(first);
	return icons;
}  

std::vector<String> 
Gtk::IconTheme::list_icons(const String& context)
{
	return list_icons(context.c_str());
}

void 
Gtk::IconTheme::add_builtin_icon(const char *icon_name, int size, Gdk::Pixbuf& pixbuf)
{
	gtk_icon_theme_add_builtin_icon(icon_name, size, pixbuf.gdk_pixbuf());
}

void 
Gtk::IconTheme::add_builtin_icon(const String& icon_name, int size, Gdk::Pixbuf& pixbuf)
{
	gtk_icon_theme_add_builtin_icon(icon_name.c_str(), size, pixbuf.gdk_pixbuf());
}

/*  Gtk::IconThemeClass
 */

void
Gtk::IconThemeClass::init(GtkIconThemeClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->changed = &changed_proxy;
}

GtkIconThemeClass*
Gtk::IconThemeClass::get_parent_class(void *instance)
{
	return static_cast<GtkIconThemeClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::IconThemeClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ICON_THEME, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::IconThemeClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::IconThemeClass::changed_proxy(GtkIconTheme *icon_theme)
{
	IconThemeSignals *signals = dynamic_cast<IconThemeSignals*>(G::ObjectSignals::pointer((GObject*)icon_theme));
	if (signals)
		signals->on_changed();
	else
	{
		GtkIconThemeClass *g_class = get_parent_class(icon_theme);
		if (g_class && g_class->changed)
			g_class->changed(icon_theme);
	}
}

/*  Gtk::IconTheme signals
 */

const Gtk::IconTheme::ChangedSignalType Gtk::IconTheme::changed_signal("changed", (GCallback)&G::Marshal::void_callback);

