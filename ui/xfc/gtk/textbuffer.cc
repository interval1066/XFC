/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  textbuffer.cc - GtkTextMark, GtkTextChildAnchor and GtkTextBuffer C++ wrapper implementation
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

#include "textbuffer.hh"
#include "textbuffersignals.hh"
#include "clipboard.hh"
#include "widget.hh"
#include "private/marshal.hh"
#include "private/textbufferclass.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include <cstring>

using namespace Xfc;

/*  Gtk::TextMark
 */
 
Gtk::TextMark::TextMark(GtkTextMark *mark, bool owns_reference)
: G::Object((GObject*)mark, owns_reference)
{
}
	
Gtk::TextMark::~TextMark() 
{
}
	
String
Gtk::TextMark::get_name() const
{
	return gtk_text_mark_get_name(gtk_text_mark());
}

Gtk::TextBuffer*
Gtk::TextMark::get_buffer() const
{
	return G::Object::wrap<TextBuffer>(gtk_text_mark_get_buffer(gtk_text_mark()));
}

/*  Gtk::TextMarkClass
 */

void 
Gtk::TextMarkClass::init(GtkTextMarkClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::TextMarkClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TEXT_MARK, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TextMarkClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::TextChildAnchor
 */

Gtk::TextChildAnchor::TextChildAnchor(GtkTextChildAnchor *anchor, bool owns_reference)
: G::Object((GObject*)anchor, owns_reference)
{
}

Gtk::TextChildAnchor::TextChildAnchor()
: G::Object((GObject*)TextChildAnchorClass::create())
{
}

Gtk::TextChildAnchor::~TextChildAnchor()
{
}

bool
Gtk::TextChildAnchor::get_widgets(std::vector<Widget*>& widgets) const
{
	g_return_val_if_fail(widgets.empty(), false);
	GList *first = gtk_text_child_anchor_get_widgets(gtk_text_child_anchor());

	GList *next = first;
	while (next)
	{
		widgets.push_back(G::Object::wrap<Widget>((GtkWidget*)next->data));
		next = g_list_next(next);
	}

	g_list_free(first);
	return !widgets.empty();
}

/*  Gtk::TextChildAnchorClass
 */

void 
Gtk::TextChildAnchorClass::init(GtkTextChildAnchorClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
}

GType
Gtk::TextChildAnchorClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TEXT_CHILD_ANCHOR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TextChildAnchorClass::create()
{
	return g_object_new(get_type(), 0);
}

/*  Gtk::TextBuffer
 */

Gtk::TextBuffer::TextBuffer(GtkTextBuffer *buffer, bool owns_reference)
: G::Object((GObject*)buffer, owns_reference)
{
}
	
Gtk::TextBuffer::TextBuffer(TextTagTable *table)
: G::Object((GObject*)TextBufferClass::create(*table))
{
}

Gtk::TextBuffer::~TextBuffer()
{
}
	
Gtk::TextTagTable*
Gtk::TextBuffer::get_tag_table() const
{
	return G::Object::wrap<TextTagTable>(gtk_text_buffer_get_tag_table(gtk_text_buffer()));
}

String
Gtk::TextBuffer::get_text(const TextIter& start, const TextIter& end, bool include_hidden_chars) const
{
	char *tmp_text = gtk_text_buffer_get_text(gtk_text_buffer(), start.gtk_text_iter(), end.gtk_text_iter(), include_hidden_chars);
	String text(tmp_text);
	g_free(tmp_text);
	return text;
}

String
Gtk::TextBuffer::get_slice(const TextIter& start, const TextIter& end, bool include_hidden_chars) const
{
	char *tmp_slice = gtk_text_buffer_get_slice(gtk_text_buffer(), start.gtk_text_iter(), end.gtk_text_iter(), include_hidden_chars);
	String slice(tmp_slice);
	g_free(tmp_slice);
	return slice;
}

Gtk::TextMark*
Gtk::TextBuffer::get_mark(const char *name) const
{
	GtkTextMark *mark = gtk_text_buffer_get_mark(gtk_text_buffer(), name);
	return mark ? G::Object::wrap<TextMark>(gtk_text_buffer_get_mark(gtk_text_buffer(), name)) : 0;
}

Gtk::TextMark*
Gtk::TextBuffer::get_mark(const String& name) const
{
	return get_mark(name.c_str());
}

Gtk::TextMark*
Gtk::TextBuffer::get_insert() const
{
	return G::Object::wrap<TextMark>(gtk_text_buffer_get_insert(gtk_text_buffer()));
}

Gtk::TextMark*
Gtk::TextBuffer::get_selection_bound() const
{
	return G::Object::wrap<TextMark>(gtk_text_buffer_get_selection_bound(gtk_text_buffer()));
}

Gtk::TextIter
Gtk::TextBuffer::get_iter_at_line_offset(int line_number, int char_offset) const
{
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_line_offset(gtk_text_buffer(), &iter, line_number, char_offset);
	return TextIter(&iter, true);
}

Gtk::TextIter
Gtk::TextBuffer::get_iter_at_line_index(int line_number, int byte_index) const
{
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_line_index(gtk_text_buffer(), &iter, line_number, byte_index);
	return TextIter(&iter, true);
}

Gtk::TextIter
Gtk::TextBuffer::get_iter_at_offset(int char_offset) const
{
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_offset(gtk_text_buffer(), &iter, char_offset);
	return TextIter(&iter, true);
}

Gtk::TextIter
Gtk::TextBuffer::get_iter_at_line(int line_number) const
{
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_line(gtk_text_buffer(), &iter, line_number);
	return TextIter(&iter, true);
}

Gtk::TextIter
Gtk::TextBuffer::get_start_iter() const
{
	GtkTextIter iter;
	gtk_text_buffer_get_start_iter(gtk_text_buffer(), &iter);
	return TextIter(&iter, true);
}

Gtk::TextIter
Gtk::TextBuffer::get_end_iter() const
{
	GtkTextIter iter;
	gtk_text_buffer_get_end_iter(gtk_text_buffer(), &iter);
	return TextIter(&iter, true);
}

void
Gtk::TextBuffer::get_bounds(TextIter& start, TextIter& end) const
{
	gtk_text_buffer_get_bounds(gtk_text_buffer(), start.gtk_text_iter(), end.gtk_text_iter());
}

Gtk::TextIter
Gtk::TextBuffer::get_iter_at_mark(TextMark& mark) const
{
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_mark(gtk_text_buffer(), &iter, mark.gtk_text_mark());
	return TextIter(&iter, true);
}

Gtk::TextIter
Gtk::TextBuffer::get_iter_at_child_anchor(TextChildAnchor& anchor) const
{
	GtkTextIter iter;
	gtk_text_buffer_get_iter_at_child_anchor(gtk_text_buffer(), &iter, anchor.gtk_text_child_anchor());
	return TextIter(&iter, true);
}

bool
Gtk::TextBuffer::get_selection_bounds(TextIter *start, TextIter *end) const
{
	return gtk_text_buffer_get_selection_bounds(gtk_text_buffer(), *start, *end);
}

void
Gtk::TextBuffer::set_text(const char* text, int length)
{
	gtk_text_buffer_set_text(gtk_text_buffer(), text, length < 0 ? strlen(text) : length);
}

void
Gtk::TextBuffer::set_text(const String& text)
{
	gtk_text_buffer_set_text(gtk_text_buffer(), text.c_str(), text.size());
}

void
Gtk::TextBuffer::insert(TextIter& iter, const char *text, int length)
{
	gtk_text_buffer_insert(gtk_text_buffer(), iter.gtk_text_iter(), text, length < 0 ? strlen(text) : length);
}

void
Gtk::TextBuffer::insert(TextIter& iter, const String& text)
{
	gtk_text_buffer_insert(gtk_text_buffer(), iter.gtk_text_iter(), text.c_str(), text.size());
}

void
Gtk::TextBuffer::insert_at_cursor(const char *text, int length)
{
	gtk_text_buffer_insert_at_cursor(gtk_text_buffer(), text, length < 0 ? strlen(text) : length);
}

void
Gtk::TextBuffer::insert_at_cursor(const String& text)
{
	gtk_text_buffer_insert_at_cursor(gtk_text_buffer(), text.c_str(), text.size());
}

bool
Gtk::TextBuffer::insert_interactive(TextIter& iter, const char *text, int length, bool default_editable)
{
	return gtk_text_buffer_insert_interactive_at_cursor(gtk_text_buffer(), text, 
	                                                    length < 0 ? strlen(text) : length, 
							    default_editable);
}

bool
Gtk::TextBuffer::insert_interactive(TextIter& iter, const String& text, bool default_editable)
{
	return gtk_text_buffer_insert_interactive_at_cursor(gtk_text_buffer(), text.c_str(),
	                                                    text.size(), default_editable);
}

bool
Gtk::TextBuffer::insert_interactive_at_cursor(const char *text, int length, bool default_editable)
{
	return gtk_text_buffer_insert_interactive_at_cursor(gtk_text_buffer(), text, length, default_editable);
}

bool
Gtk::TextBuffer::insert_interactive_at_cursor(const String& text, bool default_editable)
{
	return gtk_text_buffer_insert_interactive_at_cursor(gtk_text_buffer(), text.c_str(),
	                                                    text.size(), default_editable);
}

void
Gtk::TextBuffer::insert_range(TextIter& iter, const TextIter& start, const TextIter& end)
{
	gtk_text_buffer_insert_range(gtk_text_buffer(), iter.gtk_text_iter(), start.gtk_text_iter(), 
	                             end.gtk_text_iter());
}

bool
Gtk::TextBuffer::insert_range_interactive(TextIter& iter, const TextIter& start, const TextIter& end, bool default_editable)
{
	return gtk_text_buffer_insert_range_interactive(gtk_text_buffer(), iter.gtk_text_iter(), start.gtk_text_iter(),
	                                                end.gtk_text_iter(), default_editable);
}

void
Gtk::TextBuffer::insert_with_tag(TextIter& iter, const char *text, int length, TextTag& tag)
{
	gtk_text_buffer_insert_with_tags(gtk_text_buffer(), iter.gtk_text_iter(), text, 
	                                 length < 0 ? strlen(text) : length,
	                                 tag.gtk_text_tag(), 0);
}

void
Gtk::TextBuffer::insert_with_tag(TextIter& iter, const String& text, TextTag& tag)
{
	gtk_text_buffer_insert_with_tags(gtk_text_buffer(), iter.gtk_text_iter(), text.c_str(),
	                                 text.size(), tag.gtk_text_tag(), 0);
}

void
Gtk::TextBuffer::insert_with_tags(TextIter& iter, const char *text, int length, const std::vector<TextTag*>& tags)
{
	g_return_if_fail(!tags.empty());	
	int start_offset = iter.get_offset();
	insert(iter, text, length);
	TextIter start = get_iter_at_offset(start_offset);

	unsigned int i = 0;
	while (i < tags.size())
	{
		apply_tag(*tags[i], start, iter);
		i++;
	}
}

void
Gtk::TextBuffer::insert_with_tags(TextIter& iter, const String& text, const std::vector<TextTag*>& tags)
{
	insert_with_tags(iter, text.c_str(), text.size(), tags);	
}

void
Gtk::TextBuffer::insert_with_tag_by_name(TextIter& iter, const char *text, int length, const char *tag_name)
{
	gtk_text_buffer_insert_with_tags_by_name(gtk_text_buffer(), iter.gtk_text_iter(), text, 
	                                         length < 0 ? strlen(text) : length, tag_name, 0);
}

void
Gtk::TextBuffer::insert_with_tag_by_name(TextIter& iter, const String& text, const char *tag_name)
{
	gtk_text_buffer_insert_with_tags_by_name(gtk_text_buffer(), iter.gtk_text_iter(), text.c_str(), text.size(), tag_name, 0);
}

void
Gtk::TextBuffer::insert_with_tags_by_name(TextIter& iter, const char *text, int length, const std::vector<String>& tag_names)
{
	g_return_if_fail(!tag_names.empty());	
	int start_offset = iter.get_offset();
	insert(iter, text, length);
	TextIter start = get_iter_at_offset(start_offset);

	unsigned int i = 0;
	while (i < tag_names.size())
	{
		TextTag *tag = get_tag_table()->lookup(tag_names[i]);		
		if (!tag)
		{
			g_warning("%s: no tag with name '%s'!", __FILE__ ":" G_STRINGIFY (__LINE__), tag_names[i].c_str());
			return;
		}
		apply_tag_by_name(tag_names[i], start, iter);
		i++;
	}
}

void
Gtk::TextBuffer::insert_with_tags_by_name(TextIter& iter, const String& text, const std::vector<String>& tag_names)
{
	insert_with_tags_by_name(iter, text.c_str(), text.size(), tag_names);
}

void
Gtk::TextBuffer::delete_range(TextIter& start, TextIter& end)
{
	gtk_text_buffer_delete(gtk_text_buffer(), start.gtk_text_iter(), end.gtk_text_iter());
}

bool
Gtk::TextBuffer::delete_range_interactive(TextIter& start, TextIter& end, bool default_editable)
{
	return gtk_text_buffer_delete_interactive(gtk_text_buffer(), start.gtk_text_iter(), 
	                                          end.gtk_text_iter(), default_editable);
}

void
Gtk::TextBuffer::insert_pixbuf(TextIter& iter, Gdk::Pixbuf& pixbuf)
{
	gtk_text_buffer_insert_pixbuf(gtk_text_buffer(), iter.gtk_text_iter(), pixbuf.gdk_pixbuf());
}

void
Gtk::TextBuffer::insert_child_anchor(TextIter& iter, TextChildAnchor& anchor)
{
	gtk_text_buffer_insert_child_anchor(gtk_text_buffer(), iter.gtk_text_iter(), anchor.gtk_text_child_anchor());
}

Gtk::TextChildAnchor*
Gtk::TextBuffer::create_child_anchor(TextIter& iter)
{
	GtkTextChildAnchor *anchor = gtk_text_buffer_create_child_anchor(gtk_text_buffer(), iter.gtk_text_iter());	
	return G::Object::wrap_new<TextChildAnchor>(anchor);
}

Gtk::TextMark*
Gtk::TextBuffer::create_mark(const char *mark_name, const TextIter& where, bool left_gravity)
{
	GtkTextMark *mark = gtk_text_buffer_create_mark(gtk_text_buffer(), mark_name, where.gtk_text_iter(), left_gravity);
	return G::Object::wrap_new<TextMark>(mark);
}

Gtk::TextMark*
Gtk::TextBuffer::create_mark(const String& mark_name, const TextIter& where, bool left_gravity)
{
	return create_mark(mark_name.c_str(), where, left_gravity);
}

void
Gtk::TextBuffer::move_mark(TextMark& mark, const TextIter& where)
{
	gtk_text_buffer_move_mark(gtk_text_buffer(), mark.gtk_text_mark(), where.gtk_text_iter());
}

void
Gtk::TextBuffer::move_mark_by_name(const char *name, const TextIter& where)
{
	gtk_text_buffer_move_mark_by_name(gtk_text_buffer(), name, where.gtk_text_iter());
}

void
Gtk::TextBuffer::move_mark_by_name(const String& name, const TextIter& where)
{
	move_mark_by_name(name.c_str(), where);
}

void
Gtk::TextBuffer::delete_mark(TextMark& mark)
{
	gtk_text_buffer_delete_mark(gtk_text_buffer(), mark.gtk_text_mark());
}

void
Gtk::TextBuffer::delete_mark_by_name(const String& name)
{
	gtk_text_buffer_delete_mark_by_name(gtk_text_buffer(), name.c_str());
}

void
Gtk::TextBuffer::place_cursor(const TextIter& where)
{
	gtk_text_buffer_place_cursor(gtk_text_buffer(), where.gtk_text_iter());
}

void
Gtk::TextBuffer::select_range(const TextIter& insert, const TextIter& bound)
{
	gtk_text_buffer_select_range(gtk_text_buffer(), insert.gtk_text_iter(), bound.gtk_text_iter());
}

void
Gtk::TextBuffer::apply_tag(TextTag& tag, const TextIter& start, const TextIter& end)
{
	gtk_text_buffer_apply_tag(gtk_text_buffer(), tag.gtk_text_tag(), start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::TextBuffer::remove_tag(TextTag& tag, const TextIter& start, const TextIter& end)
{
	gtk_text_buffer_remove_tag(gtk_text_buffer(), tag.gtk_text_tag(), start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::TextBuffer::apply_tag_by_name(const char *name, const TextIter& start, const TextIter& end)
{
	gtk_text_buffer_apply_tag_by_name(gtk_text_buffer(), name, start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::TextBuffer::apply_tag_by_name(const String& name, const TextIter& start, const TextIter& end)
{
	gtk_text_buffer_apply_tag_by_name(gtk_text_buffer(), name.c_str(), start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::TextBuffer::remove_tag_by_name(const char *name, const TextIter& start, const TextIter& end)
{
	gtk_text_buffer_remove_tag_by_name(gtk_text_buffer(), name, start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::TextBuffer::remove_tag_by_name(const String& name, const TextIter& start, const TextIter& end)
{
	gtk_text_buffer_remove_tag_by_name(gtk_text_buffer(), name.c_str(), start.gtk_text_iter(), end.gtk_text_iter());
}

void
Gtk::TextBuffer::remove_all_tags(const TextIter& start, const TextIter& end)
{
	gtk_text_buffer_remove_all_tags(gtk_text_buffer(), start.gtk_text_iter(), end.gtk_text_iter());
}

Gtk::TextTag*
Gtk::TextBuffer::create_tag()
{
	return create_tag(0);
}

Gtk::TextTag*
Gtk::TextBuffer::create_tag(const char *tag_name)
{
	GtkTextTag *tag = gtk_text_buffer_create_tag(gtk_text_buffer(), tag_name, 0);	
	return G::Object::wrap_new<TextTag>(tag);
}

Gtk::TextTag*
Gtk::TextBuffer::create_tag(const String& tag_name)
{
	return create_tag(tag_name.c_str());
}

void
Gtk::TextBuffer::add_selection_clipboard(Clipboard& clipboard)
{
	gtk_text_buffer_add_selection_clipboard(gtk_text_buffer(), clipboard.gtk_clipboard());
}

void
Gtk::TextBuffer::remove_selection_clipboard(Clipboard& clipboard)
{
	gtk_text_buffer_remove_selection_clipboard(gtk_text_buffer(), clipboard.gtk_clipboard());
}

void
Gtk::TextBuffer::cut_clipboard(Clipboard& clipboard, bool default_editable)
{
	gtk_text_buffer_cut_clipboard(gtk_text_buffer(), clipboard.gtk_clipboard(), default_editable);
}

void
Gtk::TextBuffer::copy_clipboard(Clipboard& clipboard)
{
	gtk_text_buffer_copy_clipboard(gtk_text_buffer(), clipboard.gtk_clipboard());
}

void
Gtk::TextBuffer::paste_clipboard(Clipboard& clipboard, TextIter *override_location, bool default_editable)
{
	gtk_text_buffer_paste_clipboard(gtk_text_buffer(), clipboard.gtk_clipboard(), *override_location, default_editable);
}

/*  Gtk::TextBufferClass
 */

void
Gtk::TextBufferClass::init(GtkTextBufferClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->insert_text = &insert_text_proxy;
	g_class->insert_pixbuf = &insert_pixbuf_proxy;
	g_class->insert_child_anchor = &insert_child_anchor_proxy;
	g_class->delete_range = &delete_range_proxy;
	g_class->changed = &changed_proxy;
	g_class->modified_changed = &modified_changed_proxy;
	g_class->mark_set = &mark_set_proxy;
	g_class->mark_deleted = &mark_deleted_proxy;
	g_class->apply_tag = &apply_tag_proxy;
	g_class->remove_tag = &remove_tag_proxy;
	g_class->begin_user_action = &begin_user_action_proxy;
	g_class->end_user_action = &end_user_action_proxy;
}

GtkTextBufferClass*
Gtk::TextBufferClass::get_parent_class(void *instance)
{
	return static_cast<GtkTextBufferClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::TextBufferClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_TEXT_BUFFER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::TextBufferClass::create(GtkTextTagTable *table)
{
	return g_object_new(get_type(), "tag_table", table, 0);
}

void
Gtk::TextBufferClass::insert_text_proxy(GtkTextBuffer *buffer, GtkTextIter *pos, const gchar *text, gint length)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextIter tmp_pos(pos);
		String tmp_text(text, length);
		static_cast<TextBufferSignals*>(ptr)->on_insert_text(tmp_pos, tmp_text);
	}
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->insert_text)
			g_class->insert_text(buffer, pos, text, length);
	}
}

void
Gtk::TextBufferClass::insert_pixbuf_proxy(GtkTextBuffer *buffer, GtkTextIter *pos, GdkPixbuf *pixbuf)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextIter tmp_pos(pos);
		static_cast<TextBufferSignals*>(ptr)->on_insert_pixbuf(tmp_pos, *G::Object::wrap<Gdk::Pixbuf>(pixbuf));
	}
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->insert_pixbuf)
			g_class->insert_pixbuf(buffer, pos, pixbuf);
	}
}

void
Gtk::TextBufferClass::insert_child_anchor_proxy(GtkTextBuffer *buffer, GtkTextIter *pos, GtkTextChildAnchor *anchor)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextChildAnchor *tmp_anchor = G::Object::wrap<TextChildAnchor>(anchor);
		TextIter tmp_pos(pos);
		static_cast<TextBufferSignals*>(ptr)->on_insert_child_anchor(tmp_pos, *tmp_anchor);
	}
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->insert_child_anchor)
			g_class->insert_child_anchor(buffer, pos, anchor);
	}
}

void
Gtk::TextBufferClass::delete_range_proxy(GtkTextBuffer *buffer, GtkTextIter *start, GtkTextIter *end)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextIter tmp_start(start);
		TextIter tmp_end(end);
		static_cast<TextBufferSignals*>(ptr)->on_delete_range(tmp_start, tmp_end);
	}
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->delete_range)
			g_class->delete_range(buffer, start, end);
	}
}

void
Gtk::TextBufferClass::changed_proxy(GtkTextBuffer *buffer)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
		static_cast<TextBufferSignals*>(ptr)->on_changed();
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->changed)
			g_class->changed(buffer);
	}
}

void
Gtk::TextBufferClass::modified_changed_proxy(GtkTextBuffer *buffer)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
		static_cast<TextBufferSignals*>(ptr)->on_modified_changed();
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->modified_changed)
			g_class->modified_changed(buffer);
	}
}

void
Gtk::TextBufferClass::mark_set_proxy(GtkTextBuffer *buffer, const GtkTextIter *location, GtkTextMark *mark)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextIter tmp_location(const_cast<GtkTextIter*>(location));
		static_cast<TextBufferSignals*>(ptr)->on_mark_set(tmp_location, *G::Object::wrap<TextMark>(mark));
	}
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->mark_set)
			g_class->mark_set(buffer, location, mark);
	}
}

void
Gtk::TextBufferClass::mark_deleted_proxy(GtkTextBuffer *buffer, GtkTextMark *mark)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
		static_cast<TextBufferSignals*>(ptr)->on_mark_deleted(*G::Object::wrap<TextMark>(mark));
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->mark_deleted)
			g_class->mark_deleted(buffer, mark);
	}
}

void
Gtk::TextBufferClass::apply_tag_proxy(GtkTextBuffer *buffer, GtkTextTag *tag, const GtkTextIter *start_char, const GtkTextIter *end_char)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextTag *tmp_tag = G::Object::wrap<TextTag>(tag);
		TextIter tmp_start_char(const_cast<GtkTextIter*>(start_char));
		TextIter tmp_end_char(const_cast<GtkTextIter*>(end_char));
		static_cast<TextBufferSignals*>(ptr)->on_apply_tag(*tmp_tag, tmp_start_char, tmp_end_char);
	}
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->apply_tag)
			g_class->apply_tag(buffer, tag, start_char, end_char);
	}
}

void
Gtk::TextBufferClass::remove_tag_proxy(GtkTextBuffer *buffer, GtkTextTag *tag, const GtkTextIter *start_char, const GtkTextIter *end_char)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
	{
		TextTag *tmp_tag = G::Object::wrap<TextTag>(tag);
		TextIter tmp_start_char(const_cast<GtkTextIter*>(start_char));
		TextIter tmp_end_char(const_cast<GtkTextIter*>(end_char));
		static_cast<TextBufferSignals*>(ptr)->on_remove_tag(*tmp_tag, tmp_start_char, tmp_end_char);
	}
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->remove_tag)
			g_class->remove_tag(buffer, tag, start_char, end_char);
	}
}

void
Gtk::TextBufferClass::begin_user_action_proxy(GtkTextBuffer *buffer)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
		static_cast<TextBufferSignals*>(ptr)->on_begin_user_action();
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->begin_user_action)
			g_class->begin_user_action(buffer);
	}
}

void
Gtk::TextBufferClass::end_user_action_proxy(GtkTextBuffer *buffer)
{
	void *ptr = g_object_get_qdata((GObject*)buffer, G::ObjectSignals::quark());
	if (ptr)
		static_cast<TextBufferSignals*>(ptr)->on_end_user_action();
	else
	{
		GtkTextBufferClass *g_class = get_parent_class(buffer);
		if (g_class && g_class->end_user_action)
			g_class->end_user_action(buffer);
	}
}

/*  Gtk::TextBuffer Signals
 */

const Gtk::TextBuffer::InsertTextSignalType Gtk::TextBuffer::insert_text_signal("insert_text", (GCallback)&Marshal::void_textiter_string_int_callback);

const Gtk::TextBuffer::InsertPixbufSignalType Gtk::TextBuffer::insert_pixbuf_signal("insert_pixbuf", (GCallback)&Marshal::void_textiter_gdkpixbuf_callback);

const Gtk::TextBuffer::InsertChildAnchorSignalType Gtk::TextBuffer::insert_child_anchor_signal("insert_child_anchor", (GCallback)&Marshal::void_textiter_textchildanchor_callback);

const Gtk::TextBuffer::DeleteRangeSignalType Gtk::TextBuffer::delete_range_signal("delete_range", (GCallback)&Marshal::void_textiter_textiter_callback);

const Gtk::TextBuffer::ChangedSignalType Gtk::TextBuffer::changed_signal("changed", (GCallback)&G::Marshal::void_callback);

const Gtk::TextBuffer::ModifiedChangedSignalType Gtk::TextBuffer::modified_changed_signal("modified_changed", (GCallback)&G::Marshal::void_callback);

const Gtk::TextBuffer::MarkSetSignalType Gtk::TextBuffer::mark_set_signal("mark_set", (GCallback)&Marshal::void_textiter_textmark_callback);

const Gtk::TextBuffer::MarkDeletedSignalType Gtk::TextBuffer::mark_deleted_signal("mark_deleted", (GCallback)&Marshal::void_textmark_callback);

const Gtk::TextBuffer::ApplyTagSignalType Gtk::TextBuffer::apply_tag_signal("apply_tag", (GCallback)&Marshal::void_textag_textiter_textiter_callback);

const Gtk::TextBuffer::RemoveTagSignalType Gtk::TextBuffer::remove_tag_signal("remove_tag", (GCallback)&Marshal::void_textag_textiter_textiter_callback);

const Gtk::TextBuffer::BeginUserActionSignalType Gtk::TextBuffer::begin_user_action_signal("begin_user_action", (GCallback)&G::Marshal::void_callback);

const Gtk::TextBuffer::EndUserActionSignalType Gtk::TextBuffer::end_user_action_signal("end_user_action", (GCallback)&G::Marshal::void_callback);

