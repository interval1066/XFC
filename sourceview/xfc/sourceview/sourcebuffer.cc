/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourceview.cc - GtkSourceBuffer C++ wrapper implementation
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

#include "sourcebuffer.hh"
#include "sourcebuffersignals.hh"
#include "private/sourcebufferclass.hh"

#include <xfc/gtk/private/marshal.hh>


using namespace Xfc;

/*  Gtk::SourceMarker
 */

Gtk::SourceMarker::SourceMarker(GtkSourceMarker *marker, bool reference)
: Gtk::TextMark((GtkTextMark*)marker, reference)
{
}

Gtk::SourceMarker::~SourceMarker()
{
}

Gtk::SourceMarker::operator GtkSourceMarker* () const
{
	return this ? gtk_source_marker() : 0;
}

bool
Gtk::SourceMarker::is_gtk_source_marker() const
{
	return is_a(GTK_TYPE_SOURCE_MARKER);
}

String
Gtk::SourceMarker::get_marker_type() const
{
	char *type = gtk_source_marker_get_marker_type(gtk_source_marker());
	String s(type);
	g_free(type);
	return s;
}

int
Gtk::SourceMarker::get_line() const
{
	return gtk_source_marker_get_line(gtk_source_marker());
}

String
Gtk::SourceMarker::get_name() const
{
	return gtk_source_marker_get_name(gtk_source_marker());
}

Gtk::SourceBuffer*
Gtk::SourceMarker::get_buffer() const
{
	return G::Object::wrap<SourceBuffer>(gtk_source_marker_get_buffer(gtk_source_marker()));
}

Gtk::SourceMarker*
Gtk::SourceMarker::next() const
{
	return G::Object::wrap<SourceMarker>(gtk_source_marker_next(gtk_source_marker()));
}

Gtk::SourceMarker*
Gtk::SourceMarker::prev() const
{
	return G::Object::wrap<SourceMarker>(gtk_source_marker_prev(gtk_source_marker()));
}

void
Gtk::SourceMarker::set_marker_type(const String& type)
{
	gtk_source_marker_set_marker_type(gtk_source_marker(), type.c_str());
}

/*  Gtk::SourceBuffer
 */

Gtk::SourceBuffer::SourceBuffer(GtkSourceBuffer *buffer, bool reference)
: TextBuffer((GtkTextBuffer*)buffer, reference)
{
}

Gtk::SourceBuffer::SourceBuffer(SourceTagTable *table)
: TextBuffer((GtkTextBuffer*)SourceBufferClass::create(*table))
{
}

Gtk::SourceBuffer::SourceBuffer(const SourceLanguage& language)
: TextBuffer((GtkTextBuffer*)SourceBufferClass::create(0))
{
	set_language(&language);
}

Gtk::SourceBuffer::~SourceBuffer()
{
}

Gtk::SourceBuffer::operator GtkSourceBuffer* () const
{
	return this ? gtk_source_buffer() : 0;
}

bool
Gtk::SourceBuffer::is_gtk_source_buffer() const
{
	return is_a(GTK_TYPE_SOURCE_BUFFER);
}

Gtk::SourceTagTable*
Gtk::SourceBuffer::get_source_tag_table() const
{
	return static_cast<SourceTagTable*>(get_tag_table());
}

bool
Gtk::SourceBuffer::get_check_brackets() const
{
	return gtk_source_buffer_get_check_brackets(gtk_source_buffer());
}

bool
Gtk::SourceBuffer::get_highlight() const
{
	return gtk_source_buffer_get_highlight(gtk_source_buffer());
}

int
Gtk::SourceBuffer::get_max_undo_levels() const
{
	return gtk_source_buffer_get_max_undo_levels(gtk_source_buffer());
}

Gtk::SourceLanguage*
Gtk::SourceBuffer::get_language() const
{
	return G::Object::wrap<SourceLanguage>(gtk_source_buffer_get_language(gtk_source_buffer()));
}

G::Unichar
Gtk::SourceBuffer::get_escape_char() const
{
	return gtk_source_buffer_get_escape_char(gtk_source_buffer());
}

bool
Gtk::SourceBuffer::can_undo() const
{
	return gtk_source_buffer_can_undo(gtk_source_buffer());
}

bool
Gtk::SourceBuffer::can_redo() const
{
	return gtk_source_buffer_can_redo(gtk_source_buffer());
}

Gtk::SourceMarker*
Gtk::SourceBuffer::get_marker(const String& name) const
{
	return G::Object::wrap<SourceMarker>(gtk_source_buffer_get_marker(gtk_source_buffer(), name.c_str()));
}

std::vector<Gtk::SourceMarker*>
Gtk::SourceBuffer::get_markers(const TextIter& start, const TextIter& end) const
{
	std::vector<SourceMarker*> markers;
	GSList *first = gtk_source_buffer_get_markers_in_region(gtk_source_buffer(), start.gtk_text_iter(), end.gtk_text_iter());
	GSList *next = first;

	while (next)
	{
		markers.push_back(G::Object::wrap<SourceMarker>((GtkSourceMarker*)next->data));
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return markers;
}

Gtk::SourceMarker*
Gtk::SourceBuffer::get_first_marker() const
{
	return G::Object::wrap<SourceMarker>(gtk_source_buffer_get_first_marker(gtk_source_buffer()));
}

Gtk::SourceMarker*
Gtk::SourceBuffer::get_last_marker() const
{
	return G::Object::wrap<SourceMarker>(gtk_source_buffer_get_last_marker(gtk_source_buffer()));
}

Gtk::TextIter
Gtk::SourceBuffer::get_iter_at_marker(const SourceMarker& marker) const
{
	GtkTextIter iter;
	gtk_source_buffer_get_iter_at_marker(gtk_source_buffer(), &iter, marker.gtk_source_marker());
	return TextIter(&iter, true);
}

Gtk::SourceMarker*
Gtk::SourceBuffer::get_next_marker(TextIter& iter) const
{
	return G::Object::wrap<SourceMarker>(gtk_source_buffer_get_next_marker(gtk_source_buffer(), iter.gtk_text_iter()));
}

Gtk::SourceMarker*
Gtk::SourceBuffer::get_prev_marker(TextIter& iter) const
{
	return G::Object::wrap<SourceMarker>(gtk_source_buffer_get_prev_marker(gtk_source_buffer(), iter.gtk_text_iter()));
}

void
Gtk::SourceBuffer::set_check_brackets(bool check_brackets)
{
	gtk_source_buffer_set_check_brackets(gtk_source_buffer(), check_brackets);
}

void
Gtk::SourceBuffer::set_bracket_match_style(const SourceTagStyle& style)
{
	gtk_source_buffer_set_bracket_match_style(gtk_source_buffer(), style.gtk_source_tag_style());
}

void
Gtk::SourceBuffer::set_highlight(bool highlight)
{
	gtk_source_buffer_set_highlight(gtk_source_buffer(), highlight);
}

void
Gtk::SourceBuffer::set_max_undo_levels(int max_undo_levels)
{
	gtk_source_buffer_set_max_undo_levels(gtk_source_buffer(), max_undo_levels);
}

void
Gtk::SourceBuffer::set_language(const SourceLanguage *language)
{
	gtk_source_buffer_set_language(gtk_source_buffer(), *language);
}

void
Gtk::SourceBuffer::set_escape_char(G::Unichar escape_char)
{
	gtk_source_buffer_set_escape_char(gtk_source_buffer(), escape_char);
}

void
Gtk::SourceBuffer::undo()
{
	gtk_source_buffer_undo(gtk_source_buffer());
}

void
Gtk::SourceBuffer::redo()
{
	gtk_source_buffer_redo(gtk_source_buffer());
}

void
Gtk::SourceBuffer::begin_not_undoable_action()
{
	gtk_source_buffer_begin_not_undoable_action(gtk_source_buffer());
}

void
Gtk::SourceBuffer::end_not_undoable_action()
{
	gtk_source_buffer_end_not_undoable_action(gtk_source_buffer());
}

Gtk::SourceMarker*
Gtk::SourceBuffer::create_marker(const String& name, const String& type, const TextIter& where)
{
	GtkSourceMarker *marker = gtk_source_buffer_create_marker(gtk_source_buffer(), name.c_str(), type.c_str(), where.gtk_text_iter());
	return G::Object::wrap<SourceMarker>(marker);
}

void
Gtk::SourceBuffer::move_marker(SourceMarker& marker, const TextIter& where)
{
	gtk_source_buffer_move_marker(gtk_source_buffer(), marker.gtk_source_marker(), where.gtk_text_iter());
}

void
Gtk::SourceBuffer::delete_marker(SourceMarker& marker)
{
	gtk_source_buffer_delete_marker(gtk_source_buffer(), marker.gtk_source_marker());
}

/*  Gtk::SourceBufferClass
 */

void
Gtk::SourceBufferClass::init(GtkSourceBufferClass *g_class)
{
	TextBufferClass::init((GtkTextBufferClass*)g_class);
	g_class->can_undo = &can_undo_proxy;
	g_class->can_redo = &can_redo_proxy;
	g_class->highlight_updated = &highlight_updated_proxy;
	g_class->marker_updated = &marker_updated_proxy;
}

GtkSourceBufferClass*
Gtk::SourceBufferClass::get_parent_class(void *instance)
{
	return static_cast<GtkSourceBufferClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::SourceBufferClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SOURCE_BUFFER, (GClassInitFunc)init);
	}
	return type;
}

void*
Gtk::SourceBufferClass::create(GtkSourceTagTable *table)
{
	return g_object_new(get_type(), "tag_table", table,  0);
}

void
Gtk::SourceBufferClass::can_undo_proxy(GtkSourceBuffer *buffer, gboolean can_undo)
{
    void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr) 
    {
		static_cast<SourceBufferSignals*>(ptr)->on_can_undo(can_undo);
    }
	else
	{
		GtkSourceBufferClass *g_class = get_parent_class(buffer);
		if (g_class->can_undo)
			g_class->can_undo(buffer, can_undo);
	}
}

void
Gtk::SourceBufferClass::can_redo_proxy(GtkSourceBuffer *buffer, gboolean can_redo)
{
    void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
    {
        static_cast<SourceBufferSignals*>(ptr)->on_can_redo(can_redo);
    }
	else
	{
        GtkSourceBufferClass *g_class = get_parent_class(buffer);
		if (g_class->can_redo)
			g_class->can_redo(buffer, can_redo);
	}
}

void
Gtk::SourceBufferClass::highlight_updated_proxy(GtkSourceBuffer *buffer, GtkTextIter *start, GtkTextIter *end)
{
    void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextIter tmp_start(start);
		TextIter tmp_end(end);
		static_cast<SourceBufferSignals*>(ptr)->on_highlight_updated(tmp_start, tmp_end);
	}
	else
	{
        GtkSourceBufferClass *g_class = get_parent_class(buffer);
		if (g_class->highlight_updated)
			g_class->highlight_updated(buffer, start, end);
	}
}

void
Gtk::SourceBufferClass::marker_updated_proxy(GtkSourceBuffer *buffer, GtkTextIter *where)
{
    void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextIter tmp_where(where);
		static_cast<SourceBufferSignals*>(ptr)->on_marker_updated(tmp_where);
	}
	else
	{
        GtkSourceBufferClass *g_class = get_parent_class(buffer);
		if (g_class->marker_updated)
			g_class->marker_updated(buffer, where);
	}
}

/*  Gtk::Sourcebuffer properties
 */

const Gtk::SourceBuffer::EscapeCharPropertyType Gtk::SourceBuffer::escape_char_property("escape_char");

const Gtk::SourceBuffer::CheckBracketsPropertyType Gtk::SourceBuffer::check_brackets_property("check_brackets");

const Gtk::SourceBuffer::HighlightPropertyType Gtk::SourceBuffer::highlight_property("highlight");

const Gtk::SourceBuffer::MaxUndoLevelsPropertyType Gtk::SourceBuffer::max_undo_levels_property("max_undo_levels");

const Gtk::SourceBuffer::LanguagePropertyType Gtk::SourceBuffer::language_property("language");

/*  Gtk::SourceBuffer signals
 */

const Gtk::SourceBuffer::CanUndoSignalType Gtk::SourceBuffer::can_undo_signal("can_undo", (GCallback)&G::Marshal::void_bool_callback);

const Gtk::SourceBuffer::CanRedoSignalType Gtk::SourceBuffer::can_redo_signal("can_redo", (GCallback)&G::Marshal::void_bool_callback);

const Gtk::SourceBuffer::HighlightUpdatedSignalType Gtk::SourceBuffer::highlight_updated_signal("highlight_updated", (GCallback)&Marshal::void_textiter_textiter_callback);

const Gtk::SourceBuffer::MarkerUpdatedSignalType Gtk::SourceBuffer::marker_updated_signal("marker_updated", (GCallback)&Marshal::void_textiter_callback);

