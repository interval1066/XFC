/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourceview.cc - GtkSourceLanguage C++ wrapper implementation
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

#include "sourcelanguage.hh"
#include "sourcelanguagesignals.hh"
#include "private/sourcelanguageclass.hh"
#include "sourcestylescheme.hh"

#include <xfc/glib/unicode.hh>
#include <xfc/gtk/texttag.hh>

#include <xfc/gtk/private/marshal.hh>

using namespace Xfc;

/*  Gtk::SourceLanguage
 */

Gtk::SourceLanguage::SourceLanguage(GtkSourceLanguage *language, bool reference)
: G::Object((GObject*)language, reference)
{
}

Gtk::SourceLanguage::~SourceLanguage()
{
}

Gtk::SourceLanguage::operator GtkSourceLanguage* () const
{
	return this ? gtk_source_language() : 0;
}

bool
Gtk::SourceLanguage::is_gtk_source_language() const
{
	return is_a(GTK_TYPE_SOURCE_LANGUAGE);
}

String
Gtk::SourceLanguage::get_id() const
{
	return gtk_source_language_get_id(gtk_source_language());
}

String
Gtk::SourceLanguage::get_name() const
{
	char *name = gtk_source_language_get_name(gtk_source_language());
	String s(name);
	g_free(name);
	return s;
}

String
Gtk::SourceLanguage::get_section() const
{
	char *section = gtk_source_language_get_section(gtk_source_language());
	String s(section);
	g_free(section);
	return s;
}

bool
Gtk::SourceLanguage::get_tags(std::vector<Pointer<TextTag> >& tags) const
{
	g_return_val_if_fail(tags.empty(), false);
	GSList *first = gtk_source_language_get_tags(gtk_source_language());
	GSList *next = first;

	while (next != 0)
	{
		Pointer<TextTag> tmp_tag(G::Object::wrap<TextTag>((GtkTextTag*)next->data));
		tags.push_back(tmp_tag);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !tags.empty();
}

G::Unichar
Gtk::SourceLanguage::get_escape_char() const
{
	return gtk_source_language_get_escape_char(gtk_source_language());
}

bool
Gtk::SourceLanguage::get_mime_types(std::vector<String>& mime_types) const
{
	g_return_val_if_fail(mime_types.empty(), false);
	GSList *first = gtk_source_language_get_mime_types(gtk_source_language());
	GSList *next = first;

	while (next != 0)
	{
		char *mime_type = reinterpret_cast<char*>(next->data);
		mime_types.push_back(mime_type);
		g_free(mime_type);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !mime_types.empty();
}

Gtk::SourceStyleScheme*
Gtk::SourceLanguage::get_style_scheme() const
{
	GtkSourceStyleScheme *scheme = gtk_source_language_get_style_scheme(gtk_source_language());
	SourceStyleScheme *tmp_scheme = 0;
	if (scheme)
	{
		G::Object *object = G::Object::pointer(G_OBJECT(scheme));
		tmp_scheme = dynamic_cast<SourceStyleScheme*>(object);
	}
	return tmp_scheme;
}

Gtk::SourceTagStyle*
Gtk::SourceLanguage::get_tag_style(const String& tag_name) const
{
	GtkSourceTagStyle *tmp_style = gtk_source_language_get_tag_style(gtk_source_language(), tag_name.c_str());
	return G::Boxed::wrap<SourceTagStyle>(GTK_TYPE_SOURCE_TAG_STYLE, tmp_style, false);
}

Gtk::SourceTagStyle*
Gtk::SourceLanguage::get_tag_default_style(const String& tag_name) const
{
	GtkSourceTagStyle *style = gtk_source_language_get_tag_default_style(gtk_source_language(), tag_name.c_str());
	return G::Boxed::wrap<SourceTagStyle>(GTK_TYPE_SOURCE_TAG_STYLE, style, false);
}

void
Gtk::SourceLanguage::set_mime_types(const std::vector<String>& mime_types)
{
	g_return_if_fail(!mime_types.empty());
	GSList *tmp_mime_types = 0;
	int count = mime_types.size();

	int i = 0;
	while (i < count)
	{
		tmp_mime_types = g_slist_append(tmp_mime_types, (void*)mime_types[i].c_str());
		++i;
	}

	gtk_source_language_set_mime_types(gtk_source_language(), tmp_mime_types);
	g_slist_free(tmp_mime_types);
}

void
Gtk::SourceLanguage::set_style_scheme(SourceStyleScheme& scheme)
{
	gtk_source_language_set_style_scheme(gtk_source_language(), scheme.gtk_source_style_scheme());
}

void
Gtk::SourceLanguage::set_tag_style(const String& tag_name, const SourceTagStyle& style)
{
	gtk_source_language_set_tag_style(gtk_source_language(), tag_name.c_str(), style.gtk_source_tag_style());
}

/*  Gtk::SourceLanguageClass
 */

void
Gtk::SourceLanguageClass::init(GtkSourceLanguageClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->tag_style_changed = &tag_style_changed_proxy;
}

GType
Gtk::SourceLanguageClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SOURCE_LANGUAGE, (GClassInitFunc)init);
	}
	return type;
}

GtkSourceLanguageClass*
Gtk::SourceLanguageClass::get_parent_class(void *instance)
{
        return static_cast<GtkSourceLanguageClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

void*
Gtk::SourceLanguageClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::SourceLanguageClass::tag_style_changed_proxy(GtkSourceLanguage *language, const gchar *name)
{
    void *ptr = g_object_get_qdata((GObject*)language, G::ObjectSignals::quark());
	if (ptr) 
	{
		String tmp_name(name);
		static_cast<SourceLanguageSignals*>(ptr)->on_tag_style_changed(name);
	}
	else
	{
        GtkSourceLanguageClass *g_class = get_parent_class(language);
		if (g_class->tag_style_changed)
			g_class->tag_style_changed(language, name);
	}
}

/*  Gtk::SourceLanguage signals
 */

const Gtk::SourceLanguage::TagStyleChangedSignalType Gtk::SourceLanguage::tag_style_changed_signal("tag_style_changed", (GCallback)&G::Marshal::void_callback );

/*  Gtk::SourceLanguagesManager
 */

Gtk::SourceLanguagesManager::SourceLanguagesManager(GtkSourceLanguagesManager *lm, bool reference)
: G::Object((GObject*)lm, reference)
{
}

Gtk::SourceLanguagesManager::SourceLanguagesManager()
: G::Object((GObject*)SourceLanguagesManagerClass::create())
{
}

Gtk::SourceLanguagesManager::~SourceLanguagesManager()
{
}

Gtk::SourceLanguagesManager::operator GtkSourceLanguagesManager* () const
{
	return this ? gtk_source_languages_manager() : 0;
}

bool
Gtk::SourceLanguagesManager::is_gtk_source_languages_manager() const
{
	return is_a(GTK_TYPE_SOURCE_LANGUAGES_MANAGER);
}

bool
Gtk::SourceLanguagesManager::get_available_languages(std::vector<SourceLanguage*>& languages) const
{
	g_return_val_if_fail(languages.empty(), false);
	const GSList *list = gtk_source_languages_manager_get_available_languages(gtk_source_languages_manager());

	while (list != 0)
	{
		languages.push_back(G::Object::wrap<SourceLanguage>((GtkSourceLanguage*)list->data));
		list = g_slist_next(list);
	}

	return !languages.empty();
}

Gtk::SourceLanguage*
Gtk::SourceLanguagesManager::get_language_from_mime_type(const String& mime_type) const
{
	GtkSourceLanguage *language = gtk_source_languages_manager_get_language_from_mime_type(gtk_source_languages_manager(), mime_type.c_str());
	return G::Object::wrap<SourceLanguage>(language);
}

Gtk::SourceLanguage*
Gtk::SourceLanguagesManager::get_language_from_name(const String& language) const
{
	std::vector<Gtk::SourceLanguage*> languages;
	get_available_languages(languages);
	int count = languages.size();
	for (int i = 0; i < count; i++)
	{
		String name = languages[i]->get_name();
		if (name.compare(language) == 0)
			return languages[i];
	}
	return 0;
}

bool
Gtk::SourceLanguagesManager::get_lang_files_dirs(std::vector<String>& dirs) const
{
	g_return_val_if_fail(dirs.empty(), false);
	const GSList *list = gtk_source_languages_manager_get_lang_files_dirs(gtk_source_languages_manager());

	while (list != 0)
	{
		dirs.push_back((char*)list->data);
		list = g_slist_next(list);
	}

	return !dirs.empty();
}

/*  Gtk::SourceLanguagesManagerClass
 */

void
Gtk::SourceLanguagesManagerClass::init(GtkSourceLanguagesManagerClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::SourceLanguagesManagerClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SOURCE_LANGUAGES_MANAGER, (GClassInitFunc)init);
	}
	return type;
}

void*
Gtk::SourceLanguagesManagerClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::SourceLanguagesManager properties
 */

const Gtk::SourceLanguagesManager::LangSpecsDirsPropertyType Gtk::SourceLanguagesManager::lang_specs_dirs_property("lang_files_dirs");

