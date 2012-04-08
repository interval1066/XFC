/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2002-2003 The XFC Development Team.
 *
 *  textiter.cc - GtkTextIter C++ wrapper implementation
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
#include "xfc/gdk-pixbuf/pixbuf.hh"
#include "xfc/glib/unicode.hh"

using namespace Xfc;

Gtk::TextIter::TextIter()
: G::Boxed(GTK_TYPE_TEXT_ITER)
{
	GtkTextIter iter = { 0, };
	copy(&iter);
}

Gtk::TextIter::TextIter(GtkTextIter *iter)
: G::Boxed(GTK_TYPE_TEXT_ITER, iter)
{
}

Gtk::TextIter::TextIter(GtkTextIter *iter, bool copy)
: G::Boxed(GTK_TYPE_TEXT_ITER, iter, copy)
{
}

Gtk::TextIter::TextIter(const TextIter& src)
: G::Boxed(GTK_TYPE_TEXT_ITER, src.g_boxed(), true)
{
}

Gtk::TextIter::~TextIter()
{
}

Gtk::TextIter&
Gtk::TextIter::operator=(const TextIter& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

Gtk::TextBuffer*
Gtk::TextIter::get_buffer() const
{
	return G::Object::wrap<TextBuffer>(gtk_text_iter_get_buffer(gtk_text_iter()));
}

G::Unichar
Gtk::TextIter::get_char() const
{
	return gtk_text_iter_get_char(gtk_text_iter());
}

G::Unichar
Gtk::TextIter::operator*() const
{
	return gtk_text_iter_get_char(gtk_text_iter());
}

String
Gtk::TextIter::get_slice(const TextIter& start, const TextIter& end)
{
	char *tmp_slice = gtk_text_iter_get_slice(start.gtk_text_iter(), end.gtk_text_iter());
	String slice(tmp_slice);
	g_free(tmp_slice);
	return slice;
}

String
Gtk::TextIter::get_text(const TextIter& start, const TextIter& end)
{
	char *tmp_text = gtk_text_iter_get_text(start.gtk_text_iter(), end.gtk_text_iter());
	String text(tmp_text);
	g_free(tmp_text);
	return text;
}

String
Gtk::TextIter::get_visible_slice(const TextIter& start, const TextIter& end)
{
	char *tmp_slice = gtk_text_iter_get_visible_slice(start.gtk_text_iter(), end.gtk_text_iter());
	String slice(tmp_slice);
	g_free(tmp_slice);
	return slice;
}

String
Gtk::TextIter::get_visible_text(const TextIter& start, const TextIter& end)
{
	char *tmp_text = gtk_text_iter_get_visible_text(start.gtk_text_iter(), end.gtk_text_iter());
	String text(tmp_text);
	g_free(tmp_text);
	return text;
}

Gdk::Pixbuf*
Gtk::TextIter::get_pixbuf() const
{
	return G::Object::wrap<Gdk::Pixbuf>(gtk_text_iter_get_pixbuf(gtk_text_iter()));
}

bool
Gtk::TextIter::get_marks(std::vector<TextMark*>& marks) const
{
	g_return_val_if_fail(marks.empty(), false);
	GSList *first = gtk_text_iter_get_marks(gtk_text_iter());
	GSList *next = first;
	while (next)
	{
		marks.push_back(G::Object::wrap<TextMark>((GtkTextMark*)next->data));
		next = g_slist_next(next);
	}
	g_slist_free(first);
	return !marks.empty();
}

Gtk::TextChildAnchor*
Gtk::TextIter::get_child_anchor() const
{
	GtkTextChildAnchor *anchor = gtk_text_iter_get_child_anchor(gtk_text_iter());
	return anchor ? G::Object::wrap<TextChildAnchor>(anchor) : 0;
}

bool
Gtk::TextIter::get_toggled_tags(std::vector<TextTag*>& tags, bool toggled_on) const
{
	g_return_val_if_fail(tags.empty(), false);
	GSList *first = gtk_text_iter_get_toggled_tags(gtk_text_iter(), toggled_on);
	GSList *next = first;
	while (next)
	{
		tags.push_back(G::Object::wrap<TextTag>((GtkTextTag*)next->data));
		next = g_slist_next(next);
	}
	g_slist_free(first);
	return !tags.empty();
}

bool
Gtk::TextIter::begins_tag(const TextTag *tag) const
{
	return gtk_text_iter_begins_tag(gtk_text_iter(), *tag);
}

bool
Gtk::TextIter::ends_tag(const TextTag *tag) const
{
	return gtk_text_iter_ends_tag(gtk_text_iter(), *tag);
}

bool
Gtk::TextIter::toggles_tag(const TextTag *tag) const
{
	return gtk_text_iter_toggles_tag(gtk_text_iter(), *tag);
}

bool
Gtk::TextIter::has_tag(const TextTag& tag) const
{
	return gtk_text_iter_has_tag(gtk_text_iter(), tag.gtk_text_tag());
}

bool
Gtk::TextIter::get_tags(std::vector<TextTag*>& tags) const
{
	g_return_val_if_fail(tags.empty(), false);
	GSList *first = gtk_text_iter_get_tags(gtk_text_iter());
	GSList *next = first;
	while (next)
	{
		tags.push_back(G::Object::wrap<TextTag>((GtkTextTag*)next->data));
		next = g_slist_next(next);
	}
	g_slist_free(first);
	return !tags.empty();
}

bool
Gtk::TextIter::get_attributes(TextAttributes& values) const
{
	return gtk_text_iter_get_attributes(gtk_text_iter(), values.gtk_text_attributes());
}

PangoLanguage*
Gtk::TextIter::get_language() const
{
	return gtk_text_iter_get_language(gtk_text_iter());
}

bool
Gtk::TextIter::equal(const TextIter& other) const
{
	return gtk_text_iter_equal(gtk_text_iter(), other.gtk_text_iter());
}

int
Gtk::TextIter::compare(const TextIter& other) const
{
	return gtk_text_iter_compare(gtk_text_iter(), other.gtk_text_iter());
}

bool
Gtk::TextIter::in_range(const TextIter& start, const TextIter& end)
{
 	return gtk_text_iter_in_range(gtk_text_iter(), start.gtk_text_iter(), end.gtk_text_iter());
}

bool
Gtk::TextIter::operator==(const TextIter& other) const
{
	return equal(other);
}

bool
Gtk::TextIter::operator!=(const TextIter& other) const
{
	return !equal(other);
}

bool
Gtk::TextIter::operator<(const TextIter& other) const
{
	return compare(other) < 0;
}

bool
Gtk::TextIter::operator>(const TextIter& other) const
{
	return compare(other) > 0;
}

bool
Gtk::TextIter::operator<=(const TextIter& other) const
{
	return compare(other) <= 0;
}

bool
Gtk::TextIter::operator>=(const TextIter& other) const
{
	return compare(other) >= 0;
}

bool
Gtk::TextIter::forward_to_tag_toggle(const TextTag *tag)
{
	return gtk_text_iter_forward_to_tag_toggle(gtk_text_iter(), *tag);
}

bool
Gtk::TextIter::backward_to_tag_toggle(const TextTag *tag)
{
	return gtk_text_iter_backward_to_tag_toggle(gtk_text_iter(), *tag);
}

namespace { // text_char_prediciate_callback

gboolean text_char_prediciate_callback(gunichar ch, gpointer data)
{
	Gtk::TextIter::TextCharPredicate& slot = *static_cast<Gtk::TextIter::TextCharPredicate*>(data);
	return slot(ch);
}

} // namespace

bool
Gtk::TextIter::forward_find_char(const TextCharPredicate& predicate, const TextIter *limit)
{
	TextCharPredicate tmp_predicate(predicate);
	return gtk_text_iter_forward_find_char(gtk_text_iter(), &text_char_prediciate_callback, &tmp_predicate, limit->gtk_text_iter());
}

bool
Gtk::TextIter::backward_find_char(const TextCharPredicate& predicate, const TextIter *limit)
{
	TextCharPredicate tmp_predicate(predicate);
	return gtk_text_iter_backward_find_char(gtk_text_iter(), &text_char_prediciate_callback, &tmp_predicate, limit->gtk_text_iter());
}

bool
Gtk::TextIter::forward_search(const String& str, const TextIter *limit)
{
	return gtk_text_iter_forward_search(gtk_text_iter(), str.c_str(), GTK_TEXT_SEARCH_VISIBLE_ONLY, 0, 0, *limit);
}

bool
Gtk::TextIter::forward_search(const char *str, const TextIter *limit)
{
	return gtk_text_iter_forward_search(gtk_text_iter(), str, GTK_TEXT_SEARCH_VISIBLE_ONLY, 0, 0, *limit);
}

bool
Gtk::TextIter::forward_search(const String& str, TextIter *match_start, TextIter *match_end, const TextIter *limit)
{
	return gtk_text_iter_forward_search(gtk_text_iter(), str.c_str(), GTK_TEXT_SEARCH_VISIBLE_ONLY,
	                                    *match_start, *match_end, *limit);
}

bool
Gtk::TextIter::forward_search(const char *str, TextIter *match_start, TextIter *match_end, const TextIter *limit)
{
	return gtk_text_iter_forward_search(gtk_text_iter(), str, GTK_TEXT_SEARCH_VISIBLE_ONLY,
	                                    *match_start, *match_end, *limit);
}

bool
Gtk::TextIter::forward_search(const String& str, TextSearchFlagsField flags, TextIter *match_start, TextIter *match_end, const TextIter *limit)
{
	return gtk_text_iter_forward_search(gtk_text_iter(), str.c_str(), (GtkTextSearchFlags)flags,
	                                    *match_start, *match_end, *limit);
}

bool
Gtk::TextIter::forward_search(const char *str, TextSearchFlagsField flags, TextIter *match_start, TextIter *match_end, const TextIter *limit)
{
	return gtk_text_iter_forward_search(gtk_text_iter(), str, (GtkTextSearchFlags)flags,
	                                    *match_start, *match_end, *limit);
}

bool
Gtk::TextIter::backward_search(const String& str, const TextIter *limit)
{
	return gtk_text_iter_backward_search(gtk_text_iter(), str.c_str(), GTK_TEXT_SEARCH_VISIBLE_ONLY, 0, 0, *limit);
}

bool
Gtk::TextIter::backward_search(const char *str, const TextIter *limit)
{
	return gtk_text_iter_backward_search(gtk_text_iter(), str, GTK_TEXT_SEARCH_VISIBLE_ONLY, 0, 0, *limit);
}

bool
Gtk::TextIter::backward_search(const String& str, TextIter *match_start, TextIter *match_end, const TextIter *limit)
{
	return gtk_text_iter_backward_search(gtk_text_iter(), str.c_str(), GTK_TEXT_SEARCH_VISIBLE_ONLY,
	                                     *match_start, *match_end, *limit);
}

bool
Gtk::TextIter::backward_search(const char *str, TextIter *match_start, TextIter *match_end, const TextIter *limit)
{
	return gtk_text_iter_backward_search(gtk_text_iter(), str, GTK_TEXT_SEARCH_VISIBLE_ONLY,
	                                     *match_start, *match_end, *limit);
}

bool
Gtk::TextIter::backward_search(const String& str, TextSearchFlagsField flags, TextIter *match_start, TextIter *match_end, const TextIter *limit)
{
	return gtk_text_iter_backward_search(gtk_text_iter(), str.c_str(), (GtkTextSearchFlags)flags,
	                                     *match_start, *match_end, *limit);
}

bool
Gtk::TextIter::backward_search(const char *str, TextSearchFlagsField flags, TextIter *match_start, TextIter *match_end, const TextIter *limit)
{
	return gtk_text_iter_backward_search(gtk_text_iter(), str, (GtkTextSearchFlags)flags,
	                                     *match_start, *match_end, *limit);
}

void
Gtk::TextIter::order(const TextIter& first, const TextIter& second)
{
	gtk_text_iter_order(first.gtk_text_iter(), second.gtk_text_iter());
}

Gtk::TextIter
Gtk::TextIter::operator+(int chars) const
{
	TextIter iter = *this;
	gtk_text_iter_forward_chars(iter.gtk_text_iter(), chars);
	return iter;
}

Gtk::TextIter
Gtk::TextIter::operator-(int chars) const
{
	TextIter iter = *this;
	gtk_text_iter_backward_chars(iter.gtk_text_iter(), chars);
	return iter;
}

Gtk::TextIter&
Gtk::TextIter::operator+=(int chars)
{
	gtk_text_iter_forward_chars(gtk_text_iter(), chars);
	return *this;
}

Gtk::TextIter&
Gtk::TextIter::operator-=(int chars)
{
	gtk_text_iter_backward_chars(gtk_text_iter(), chars);
	return *this;
}

Gtk::TextIter&
Gtk::TextIter::operator++()
{
	gtk_text_iter_forward_char(gtk_text_iter());
	return *this;
}

Gtk::TextIter&
Gtk::TextIter::operator--()
{
	gtk_text_iter_backward_char(gtk_text_iter());
	return *this;
}

Gtk::TextIter
Gtk::TextIter::operator++(int)
{
	TextIter iter = *this;
	gtk_text_iter_forward_char(iter.gtk_text_iter());
	return iter;
}

Gtk::TextIter
Gtk::TextIter::operator--(int)
{
	TextIter iter = *this;
	gtk_text_iter_backward_char(iter.gtk_text_iter());
	return *this;
}

