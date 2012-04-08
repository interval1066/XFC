/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourcestylescheme.cc - GtkSourceStyleScheme C++ wrapper implementation
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "sourcestylescheme.hh"
#include "sourcestyleschemesignals.hh"
#include "private/sourcestyleschemeclass.hh"
#include "sourcetagstyle.hh"

#include <xfc/glib/objectsignals.hh>
#include <xfc/glib/object.hh>
#include <xfc/gtk/private/marshal.hh>

using namespace Xfc;

/*  Gtk::SourceStyleScheme
 */

Gtk::SourceStyleScheme::~SourceStyleScheme()
{
}

Gtk::SourceStyleScheme::operator GtkSourceStyleScheme* () const
{
	return this ? gtk_source_style_scheme() : 0;
}

bool
Gtk::SourceStyleScheme::is_gtk_source_style_scheme() const
{
	return is_a(GTK_TYPE_SOURCE_STYLE_SCHEME);
}

Gtk::SourceStyleScheme*
Gtk::SourceStyleScheme::get_default()
{
	GtkSourceStyleScheme *scheme = gtk_source_style_scheme_get_default();
	SourceStyleScheme *tmp_scheme = 0;
	if (scheme)
	{
		G::Object *object = G::Object::pointer(G_OBJECT(scheme));
		tmp_scheme = dynamic_cast<SourceStyleScheme*>(object);
	}
	return tmp_scheme;
}

String
Gtk::SourceStyleScheme::get_name() const
{
	return gtk_source_style_scheme_get_name(gtk_source_style_scheme());
}

Gtk::SourceTagStyle*
Gtk::SourceStyleScheme::get_tag_style(const String& style_name) const
{
	GtkSourceTagStyle *style = gtk_source_style_scheme_get_tag_style(gtk_source_style_scheme(), style_name.c_str());
	return G::Boxed::wrap<SourceTagStyle>(GTK_TYPE_SOURCE_TAG_STYLE, style);
}

bool
Gtk::SourceStyleScheme::get_style_names(std::vector<String>& names) const
{
	g_return_val_if_fail(names.empty(), false);
	GSList *first = gtk_source_style_scheme_get_style_names(gtk_source_style_scheme());
	GSList *next = first;

	while (next != 0)
	{
		char *name = (char*)next->data;
		names.push_back(name);
		g_free(name);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !names.empty();
}

/*  Gtk::SourceStyleSchemeClass
 */

void
Gtk::SourceStyleSchemeClass::init(GtkSourceStyleSchemeClass *g_iface)
{
	g_iface->style_changed = &style_changed_proxy;
	g_iface->get_name = &get_name_proxy;
	g_iface->get_tag_style = &get_tag_style_proxy;
	g_iface->get_style_names = &get_style_names_proxy;
}

GtkSourceStyleSchemeClass*
Gtk::SourceStyleSchemeClass::get_parent_class(void *instance)
{
        return static_cast<GtkSourceStyleSchemeClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

void
Gtk::SourceStyleSchemeClass::style_changed_proxy(GtkSourceStyleScheme *scheme, const gchar *tag_id)
{
    SourceStyleSchemeSignals *signals = dynamic_cast<SourceStyleSchemeSignals*>(G::ObjectSignals::pointer((GObject*)scheme));

	if (signals) 
	{
		String tmp_tag_id(tag_id);
		signals->on_style_changed(tmp_tag_id);
	}
	else
	{
        GtkSourceStyleSchemeClass *g_iface = get_parent_class(scheme);
		if (g_iface->style_changed)
			g_iface->style_changed(scheme, tag_id);
	}
}

const gchar*
Gtk::SourceStyleSchemeClass::get_name_proxy(GtkSourceStyleScheme *scheme)
{
	const gchar *result = 0;
	G::ObjectSignals *object = G::ObjectSignals::pointer(G_OBJECT(scheme));
	Gtk::SourceStyleSchemeSignals *tmp_scheme = dynamic_cast<Gtk::SourceStyleSchemeSignals*>(object);
	if (tmp_scheme)
		result = tmp_scheme->do_get_name();
	else
	{
		void *tmp_iface = g_type_interface_peek_parent(GTK_SOURCE_STYLE_SCHEME_GET_CLASS(scheme));
		GtkSourceStyleSchemeClass *g_iface = static_cast<GtkSourceStyleSchemeClass*>(tmp_iface);
		if (g_iface->get_name)
			result = g_iface->get_name(scheme);
	}
	return result;
}

GtkSourceTagStyle*
Gtk::SourceStyleSchemeClass::get_tag_style_proxy(GtkSourceStyleScheme *scheme, const gchar *style_name)
{
	GtkSourceTagStyle* result = 0;
	G::ObjectSignals *object = G::ObjectSignals::pointer(G_OBJECT(scheme));
	Gtk::SourceStyleSchemeSignals *tmp_scheme = dynamic_cast<Gtk::SourceStyleSchemeSignals*>(object);
	if (tmp_scheme)
		result = tmp_scheme->do_get_tag_style(style_name);
	else
	{
		void *tmp_iface = g_type_interface_peek_parent(GTK_SOURCE_STYLE_SCHEME_GET_CLASS(scheme));
		GtkSourceStyleSchemeClass *g_iface = static_cast<GtkSourceStyleSchemeClass*>(tmp_iface);
		if (g_iface->get_tag_style)
			result = g_iface->get_tag_style(scheme, style_name);
	}
	return result;
}


//	static GSList* get_style_names_proxy(GtkSourceStyleScheme *scheme); XXX

GSList*
Gtk::SourceStyleSchemeClass::get_style_names_proxy(GtkSourceStyleScheme *scheme)
{
	GSList *result = 0;
	G::ObjectSignals *object = G::ObjectSignals::pointer(G_OBJECT(scheme));
	Gtk::SourceStyleSchemeSignals *tmp_scheme = dynamic_cast<Gtk::SourceStyleSchemeSignals*>(object);
	if (tmp_scheme)
		result = tmp_scheme->do_get_style_names();
	else
	{
		void *tmp_iface = g_type_interface_peek_parent(GTK_SOURCE_STYLE_SCHEME_GET_CLASS(scheme));
		GtkSourceStyleSchemeClass *g_iface = static_cast<GtkSourceStyleSchemeClass*>(tmp_iface);
		if (g_iface->get_style_names)
			result = g_iface->get_style_names(scheme);
	}
	return result;
}

/*  Signals
 */

const Gtk::SourceStyleScheme::StyleChangedSignalType Gtk::SourceStyleScheme::style_changed_signal("style_changed", (GCallback)&Marshal::void_string_callback);
