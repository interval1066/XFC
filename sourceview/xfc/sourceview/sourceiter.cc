/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourceiter.cc - A Gtk::TextIter object that supports case-insensitive searching.
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

#include "sourceiter.hh"

using namespace Xfc;

/*  Gtk::SourceIter
 */

Gtk::SourceIter::SourceIter()
{
}

Gtk::SourceIter::SourceIter(GtkTextIter *iter)
: Gtk::TextIter(iter)
{
}

Gtk::SourceIter::SourceIter(GtkTextIter *iter, bool copy)
: Gtk::TextIter(iter, copy)
{
}

Gtk::SourceIter::SourceIter(const SourceIter& src)
: Gtk::TextIter(src)
{
}

Gtk::SourceIter::~SourceIter()
{
}

Gtk::SourceIter&
Gtk::SourceIter::operator=(const SourceIter& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

bool
Gtk::SourceIter::forward_search(const char *str, const SourceIter *limit)
{
	return gtk_source_iter_forward_search(gtk_text_iter(), str, GTK_SOURCE_SEARCH_VISIBLE_ONLY, 0, 0, *limit);
}

bool
Gtk::SourceIter::forward_search(const String& str, const SourceIter *limit)
{
	return gtk_source_iter_forward_search(gtk_text_iter(), str.c_str(), GTK_SOURCE_SEARCH_VISIBLE_ONLY, 0, 0, *limit);
}

bool
Gtk::SourceIter::forward_search(const char *str, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit)
{
	return gtk_source_iter_forward_search(gtk_text_iter(), str, GTK_SOURCE_SEARCH_VISIBLE_ONLY,
	                                    *match_start, *match_end, *limit);
}

bool
Gtk::SourceIter::forward_search(const String& str, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit)
{
	return gtk_source_iter_forward_search(gtk_text_iter(), str.c_str(), GTK_SOURCE_SEARCH_VISIBLE_ONLY,
	                                    *match_start, *match_end, *limit);
}

bool
Gtk::SourceIter::forward_search(const char *str, SourceSearchFlagsField flags, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit)
{
	return gtk_source_iter_forward_search(gtk_text_iter(), str, (GtkSourceSearchFlags)flags,
	                                    *match_start, *match_end, *limit);
}

bool
Gtk::SourceIter::forward_search(const String& str, SourceSearchFlagsField flags, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit)
{
	return gtk_source_iter_forward_search(gtk_text_iter(), str.c_str(), (GtkSourceSearchFlags)flags,
	                                    *match_start, *match_end, *limit);
}

bool
Gtk::SourceIter::backward_search(const char *str, const SourceIter *limit)
{
	return gtk_source_iter_backward_search(gtk_text_iter(), str, GTK_SOURCE_SEARCH_VISIBLE_ONLY, 0, 0, *limit);
}

bool
Gtk::SourceIter::backward_search(const String& str, const SourceIter *limit)
{
	return gtk_source_iter_backward_search(gtk_text_iter(), str.c_str(), GTK_SOURCE_SEARCH_VISIBLE_ONLY, 0, 0, *limit);
}

bool
Gtk::SourceIter::backward_search(const char *str, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit)
{
	return gtk_source_iter_backward_search(gtk_text_iter(), str, GTK_SOURCE_SEARCH_VISIBLE_ONLY,
	                                     *match_start, *match_end, *limit);
}

bool
Gtk::SourceIter::backward_search(const String& str, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit)
{
	return gtk_source_iter_backward_search(gtk_text_iter(), str.c_str(), GTK_SOURCE_SEARCH_VISIBLE_ONLY,
	                                     *match_start, *match_end, *limit);
}

bool
Gtk::SourceIter::backward_search(const char *str, SourceSearchFlagsField flags, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit)
{
	return gtk_source_iter_backward_search(gtk_text_iter(), str, (GtkSourceSearchFlags)flags,
	                                     *match_start, *match_end, *limit);
}

bool
Gtk::SourceIter::backward_search(const String& str, SourceSearchFlagsField flags, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit)
{
	return gtk_source_iter_backward_search(gtk_text_iter(), str.c_str(), (GtkSourceSearchFlags)flags,
	                                     *match_start, *match_end, *limit);
}

bool
Gtk::SourceIter::find_matching_bracket()
{
	return gtk_source_iter_find_matching_bracket(gtk_text_iter());
}

