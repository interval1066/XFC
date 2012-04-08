/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourcetag.cc - GtkSourceTag, GtkSyntaxTag and GtkPatternTag C++ wrapper implementation
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

#include "sourcetag.hh"
#include "sourcetagsignals.hh"
#include "private/sourcetagclass.hh"
#include "sourcetagstyle.hh"

#include <xfc/gtk/private/marshal.hh>

using namespace Xfc;

/*  Gtk::SourceTag
 */

Gtk::SourceTag::SourceTag(GtkSourceTag *tag, bool reference)
: Gtk::TextTag((GtkTextTag*)tag, reference)
{
}

Gtk::SourceTag::~SourceTag()
{
}

Gtk::SourceTag::operator GtkSourceTag* () const
{
	return this ? gtk_source_tag() : 0;
}

bool
Gtk::SourceTag::is_gtk_source_tag() const
{
	return is_a(GTK_TYPE_SOURCE_TAG);
}

String
Gtk::SourceTag::get_id() const
{
	return gtk_source_tag_get_id(gtk_source_tag());
}

Gtk::SourceTagStyle*
Gtk::SourceTag::get_style() const
{
	return G::Boxed::wrap<SourceTagStyle>(GTK_TYPE_SOURCE_TAG_STYLE, gtk_source_tag_get_style(gtk_source_tag()), false);
}

void
Gtk::SourceTag::set_style(const SourceTagStyle& style)
{
	gtk_source_tag_set_style(gtk_source_tag(), style.gtk_source_tag_style());
}

/*  Gtk::SourceTag properties
 */

const Gtk::SourceTag::IdPropertyType Gtk::SourceTag::id_property("id");

const Gtk::SourceTag::TagStylePropertyType Gtk::SourceTag::tag_style_property("tag_style");

/*  Gtk::SyntaxTag
 */

Gtk::SyntaxTag::SyntaxTag(GtkSyntaxTag *tag, bool reference)
: Gtk::SourceTag((GtkSourceTag*)tag, reference)
{
}

Gtk::SyntaxTag::SyntaxTag(const String& id, const String& name, const char *pattern_start, const char *pattern_end)
: Gtk::SourceTag((GtkSourceTag*)gtk_syntax_tag_new(id.c_str(), name.c_str(), pattern_start, pattern_end))
{
}

Gtk::SyntaxTag::~SyntaxTag()
{
}

Gtk::SyntaxTag::operator GtkSyntaxTag* () const
{
	return this ? gtk_syntax_tag() : 0;
}

bool
Gtk::SyntaxTag::is_gtk_syntax_tag() const
{
	return is_a(GTK_TYPE_SYNTAX_TAG);
}

/*  Gtk::LineCommentTag
 */

Gtk::LineCommentTag::LineCommentTag(const String& id, const String& name, const char *pattern_start)
: Gtk::SyntaxTag((GtkSyntaxTag*)gtk_line_comment_tag_new(id.c_str(), name.c_str(), pattern_start))
{
}

/*  Gtk::StringTag
 */

Gtk::StringTag::StringTag(const String& id, const String& name, const char *pattern_start, const char *pattern_end, bool end_at_line_end)
: Gtk::SyntaxTag((GtkSyntaxTag*)gtk_string_tag_new(id.c_str(), name.c_str(), pattern_start, pattern_end, end_at_line_end))
{
}

/*  Gtk::PatternTag
 */

Gtk::PatternTag::PatternTag(GtkPatternTag *tag, bool reference)
: Gtk::SourceTag((GtkSourceTag*)tag, reference)
{
}

Gtk::PatternTag::PatternTag(const String& id, const String& name, const char *pattern)
: Gtk::SourceTag((GtkSourceTag*)gtk_pattern_tag_new(id.c_str(), name.c_str(), pattern))
{
}

Gtk::PatternTag::~PatternTag()
{
}

Gtk::PatternTag::operator GtkPatternTag* () const
{
	return this ? gtk_pattern_tag() : 0;
}

bool
Gtk::PatternTag::is_gtk_pattern_tag() const
{
	return is_a(GTK_TYPE_PATTERN_TAG);
}

/*  Gtk::KeywordListTag
 */

namespace { // create_keyword_list_tag

GtkTextTag*
create_keyword_list_tag(const String& id, const String& name, std::vector<String>& keywords, bool case_sensitive,
	                bool match_empty_string_at_beginning, bool match_empty_string_at_end,
		        const char *beginning_regex, const char *end_regex)
{
	GSList *tmp_keywords = 0;
	int count = keywords.size();

	int i = 0;
	while (i < count)
	{
		tmp_keywords = g_slist_append(tmp_keywords, (void*)keywords[i].c_str());
		++i;
	}

	GtkTextTag *tag = gtk_keyword_list_tag_new(id.c_str(), name.c_str(), tmp_keywords, case_sensitive,
	                                           match_empty_string_at_beginning,
	                                           match_empty_string_at_end,
	                                           beginning_regex, end_regex);
	g_slist_free(tmp_keywords);
	return tag;
}

} // namespace

Gtk::KeywordListTag::KeywordListTag(const String& id, const String& name, std::vector<String>& keywords, bool case_sensitive,
                                    bool match_empty_string_at_beginning, bool match_empty_string_at_end,
                                    const char *beginning_regex, const char *end_regex)
: Gtk::PatternTag((GtkPatternTag*)create_keyword_list_tag(id, name, keywords, case_sensitive,
  match_empty_string_at_beginning, match_empty_string_at_end, beginning_regex, end_regex))
{
}

/*  Gtk::SourceTagTable
 */

Gtk::SourceTagTable::SourceTagTable(GtkSourceTagTable *table, bool reference)
: Gtk::TextTagTable((GtkTextTagTable*)table, reference)
{
}

Gtk::SourceTagTable::SourceTagTable()
: Gtk::TextTagTable((GtkTextTagTable*)SourceTagTableClass::create())
{
}

Gtk::SourceTagTable::~SourceTagTable()
{
}

Gtk::SourceTagTable::operator GtkSourceTagTable* () const
{
	return this ? gtk_source_tag_table() : 0;
}

bool
Gtk::SourceTagTable::is_gtk_source_tag_table() const
{
	return is_a(GTK_TYPE_SOURCE_TAG_TABLE);
}

void
Gtk::SourceTagTable::add_tags(const std::vector<TextTag*>& tags)
{
	g_return_if_fail(!tags.empty());
	GSList *tmp_tags = 0;
	int count = tags.size();

	int i = 0;
	while (i < count)
	{
		tmp_tags = g_slist_append(tmp_tags, (void*)tags[i]->gtk_text_tag());
		++i;
	}

	gtk_source_tag_table_add_tags(gtk_source_tag_table(), tmp_tags);
	g_slist_free(tmp_tags);
}

void
Gtk::SourceTagTable::remove_source_tags()
{
	gtk_source_tag_table_remove_source_tags(gtk_source_tag_table());
}

/*  Gtk::SourceTagTableClass
 */

void
Gtk::SourceTagTableClass::init(GtkSourceTagTableClass *g_class)
{
	TextTagTableClass::init((GtkTextTagTableClass*)g_class);
	g_class->changed = &changed_proxy;
}

GType
Gtk::SourceTagTableClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SOURCE_TAG_TABLE, (GClassInitFunc)init);
	}
	return type;
}

void*
Gtk::SourceTagTableClass::create()
{
	return g_object_new(get_type(), 0);
}

GtkSourceTagTableClass*
Gtk::SourceTagTableClass::get_parent_class(void *instance)
{
        return static_cast<GtkSourceTagTableClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

void
Gtk::SourceTagTableClass::changed_proxy(GtkSourceTagTable *table)
{
    void *ptr = g_object_get_qdata((GObject*)table, G::ObjectSignals::quark());
    if (ptr)
        static_cast<SourceTagTableSignals*>(ptr)->on_changed();
    else
    {
        GtkSourceTagTableClass *g_class = get_parent_class(table);
		if (g_class->changed)
			g_class->changed(table);
	}
}

/*  Gtk::SourceTagTable signals
 */

const Gtk::SourceTagTable::ChangedSignalType Gtk::SourceTagTable::changed_signal("changed", (GCallback)&G::Marshal::void_callback);

