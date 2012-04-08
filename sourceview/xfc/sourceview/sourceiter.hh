/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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

//! @file inti/gtk-sourceview/sourceiter.h
//! @brief A Gtk::TextIter extension class.
//!
//! Provides SourceIter, a Gtk::TextIter object that supports case-insensitive searching.

#ifndef XFC_GTK_SOURCE_ITER_HH
#define XFC_GTK_SOURCE_ITER_HH

#ifndef XFC_GTK_TEXT_ITER_HH
#include <xfc/gtk/textiter.hh>
#endif

#ifndef __GTK_SOURCE_ITER_H__
#include <gtksourceview/gtksourceiter.h>
#endif

namespace Xfc {

namespace G {
class Object;
}

namespace Gtk {

//! @enum SourceSearchFlags
//! Specifies how a source iterator should search through a source buffer for a text string.

enum SourceSearchFlags
{
	SOURCE_SEARCH_VISIBLE_ONLY = GTK_SOURCE_SEARCH_VISIBLE_ONLY,
	//!< The matching text may have invisible text interspersed in it, that is, the text
	//!< may possibly be a noncontiguous subsequence of the matched range.

	SOURCE_SEARCH_TEXT_ONLY = GTK_SOURCE_SEARCH_TEXT_ONLY,
	//!< The matching text may have pixbufs or child widgets mixed inside the matched range.

	SOURCE_SEARCH_CASE_INSENSITIVE = GTK_SOURCE_SEARCH_CASE_INSENSITIVE
	//!< The text will be matched regardless of what case it is in.
};

//! SourceSearchFlagsField holds one or more values from the SourceSearchFlags enumeration.

typedef unsigned int SourceSearchFlagsField;

//! @class SourceIter sourceiter.h inti/gtk-sourceview/sourceiter.h
//! @brief A GtkTextIter object that supports case-insensitive searching.
//!
//! SourceIter is a Gtk::TextIter extension that supports case-insensitive forward and backward searching.

class SourceIter : public TextIter
{
public:
//! @name Constructors
//! @{

	SourceIter();
	//!< Construct an properly initialized source iterator.

	explicit SourceIter(GtkTextIter *iter);
	//!< Construct a new source iterator from an existing GtkTextIter.
	//!< @param iter A pointer to a GtkTextIter.
	//!<
	//!< <BR>The <EM>iter</EM> can be a newly created GtkTextIter or an existing
	//!< GtkTextIter. The SourceIter object created is a temporary object. It doesn't
	//!< take over the ownership of GtkTextIter and GtkTextIter is not freed by the
	//!< destructor.

	SourceIter(GtkTextIter *iter, bool copy);
	//!< Construct a new source iterator from an existing GtkTextIter.
	//!< @param iter A pointer to a GtkTextIter.
	//!< @param copy Whether the SourceIter object should make a copy of GtkTextIter or not.
	//!<
	//!< <BR>The <EM>iter</EM> can be a newly created GtkTextIter or an existing GtkTextIter.
	//!< If <EM>copy</EM> is true SourceIter will make a copy of GtkTextIter. If <EM>copy</EM>
	//!< is false SourceIter wont make a copy but instead takes over the ownership of GtkTextIter.
	//!< Either way, the destructor will free GtkTextIter when the SourceIter object is destroyed.
	//!< This constructor is used by G::Boxed::wrap() to wrap GtkTextIter objects in a C++ wrapper.

	SourceIter(const SourceIter& src);
	//!< Copy constructor.
	//!< @param src The source iterator.

	~SourceIter();
	//!< Destructor.

	SourceIter& operator=(const SourceIter& src);
	//!< Assignment operator.
	//!< @param src The source iterator.

//! @}
//! @name Methods
//! @{

	bool forward_search(const char *str, const SourceIter *limit = 0);
	bool forward_search(const String& str, const SourceIter *limit = 0);
	//!< Do a case-sensitive search forward for <EM>str</EM>.
	//!< @param str The search string.
	//!< @param limit The bound for the search, or null for the end of the buffer.
	//!< @return Whether a match was found
	//!<
	//!< <BR>The search will not continue past <EM>limit</EM>. Note that a search is a linear
	//!< or O(n) operation, so you may wish to use limit to avoid locking up your UI on large
	//!< buffers. The Gtk::SOURCE_SEARCH_VISIBLE_ONLY flag is used so the match may have invisible text
	//!< interspersed in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence
	//!< of the matched range).


	bool forward_search(const char *str, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit = 0);
	bool forward_search(const String& str, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit = 0);
	//!< Do a case-sensitive search forward for <EM>str</EM>.
	//!< @param str The search string.
	//!< @param match_start The return location for start of match, or null.
	//!< @param match_end The return location for end of match, or null.
	//!< @param limit The bound for the search, or null for the end of the buffer.
	//!< @return Whether a match was found
	//!<
	//!< <BR>Any match is returned by setting <EM>match_start</EM> to the first character of the
	//!< match and <EM>match_end</EM> to the first character after the match. The search will
	//!< not continue past <EM>limit</EM>. Note that a search is a linear or O(n) operation,
	//!< so you may wish to use limit to avoid locking up your UI on large buffers. The
	//!< Gtk::SOURCE_SEARCH_VISIBLE_ONLY flag is used so the match may have invisible text interspersed
	//!< in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence of the matched range).

	bool forward_search(const char *str, SourceSearchFlagsField flags, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit = 0);
	bool forward_search(const String& str, SourceSearchFlagsField flags, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit = 0);
	//!< Searches forward for <EM>str</EM>.
	//!< @param str The search string.
	//!< @param flags The bitmask of flags specifying how the search is done.
	//!< @param match_start The return location for start of match, or null.
	//!< @param match_end The return location for end of match, or null.
	//!< @param limit The bound for the search, or null for the end of the buffer.
	//!< @return Whether a match was found
	//!<
	//!< <BR>Any match is returned by setting <EM>match_start</EM> to the first character of the
	//!< match and <EM>match_end</EM> to the first character after the match. The search will
	//!< not continue past <EM>limit</EM>. Note that a search is a linear or O(n) operation,
	//!< so you may wish to use limit to avoid locking up your UI on large buffers. If the
	//!< Gtk::SOURCE_SEARCH_VISIBLE_ONLY flag is present, the match may have invisible text
	//!< interspersed in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence
	//!< of the matched range). Similarly, if you specify Gtk::SOURCE_SEARCH_TEXT_ONLY, the match
	//!< may have pixbufs or child widgets mixed inside the matched range. If these flags are not
	//!< given, the match must be exact; the special 0xFFFC character in str will match embedded
	//!< pixbufs or child widgets. If you specify the Gtk::SOURCE_SEARCH_CASE_INSENSITIVE flag,
	//!< the text will be matched regardless of what case it is in.

	bool backward_search(const char *str, const SourceIter *limit = 0);
	bool backward_search(const String& str, const SourceIter *limit = 0);
	//!< Do a case-sensitive search backward for <EM>str</EM>.
	//!< @param str The search string.
	//!< @param limit The location of last possible match_start, or null for start of buffer.
	//!< @return Whether a match was found.
	//!<
	//!< <BR>The Gtk::SOURCE_SEARCH_VISIBLE_ONLY flag is used so the match may have invisible text
	//!< interspersed in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence
	//!< of the matched range).

	bool backward_search(const char * str, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit = 0);
	bool backward_search(const String& str, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit = 0);
	//!< Do a case-sensitive search backward for <EM>str</EM>.
	//!< @param str The search string.
	//!< @param match_start The return location for start of match, or null.
	//!< @param match_end The return location for end of match, or null.
	//!< @param limit The location of last possible match_start, or null for start of buffer.
	//!< @return Whether a match was found.
	//!<
	//!< <BR>The Gtk::SOURCE_SEARCH_VISIBLE_ONLY flag is used so the match may have invisible text
	//!< interspersed in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence
	//!< of the matched range).

	bool backward_search(const char *str, SourceSearchFlagsField flags, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit = 0);
	bool backward_search(const String& str, SourceSearchFlagsField flags, SourceIter *match_start, SourceIter *match_end, const SourceIter *limit = 0);
	//!< Searches backward for <EM>str</EM>.
	//!< @param str The search string.
	//!< @param flags The bitmask of flags specifying how the search is done.
	//!< @param match_start The return location for start of match, or null.
	//!< @param match_end The return location for end of match, or null.
	//!< @param limit The location of last possible match_start, or null for start of buffer.
	//!< @return Whether a match was found.

	bool find_matching_bracket();
	//!< Tries to match the bracket character currently at the iter with its opening/closing
	//!< counterpart, and if found moves iter to the position where it was found.
	//!< @return <EM>true</EM> if a matching bracket is found and the iter moved.
	//!<
	//!< <BR>If the current bracket is an opening bracket the buffer is searched in a
	//!< forward direction. If the current bracket is a closing bracket the buffer is
	//!< searched in a backward direction.

//! @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_ITER_H

