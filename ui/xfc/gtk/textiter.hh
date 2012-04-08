/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2002-2003 The XFC Development Team.
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
 
/// @file xfc/gtk/textiter.hh
/// @brief A GtkTextIter C++ wrapper interface.
///
/// Provides TextIter, an object that represents a position between two characters in a text buffer.

#ifndef XFC_GTK_TEXT_ITER_HH
#define XFC_GTK_TEXT_ITER_HH

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef GTK_TEXT_ITER_H
#include <gtk/gtktextiter.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {
class Unichar;
}

namespace Gdk {
class Pixbuf;
}

namespace Gtk {

class TextAttributes;
class TextBuffer;
class TextChildAnchor;
class TextMark;
class TextTag;

/// @enum TextSearchFlags
/// TextSearchFlags is used to specify how a text iterator should search through
/// a text buffer for a text string.

enum TextSearchFlags
{
	TEXT_SEARCH_VISIBLE_ONLY = GTK_TEXT_SEARCH_VISIBLE_ONLY,
	///< The matching text may have invisible text interspersed in it, that is, the text
	///< may possibly be a noncontiguous subsequence of the matched range.

	TEXT_SEARCH_TEXT_ONLY = GTK_TEXT_SEARCH_TEXT_ONLY
	///< The matching text may have pixbufs or child widgets mixed inside the matched range.
};

/// TextSearchFlagsField holds one or more values from the Gtk::TextSearchFlags enumeration.

typedef unsigned int TextSearchFlagsField;

/// @class TextIter textiter.hh xfc/gtk/textiter.hh
/// @brief A GtkTextIter C++ wrapper class.
///
/// Most text manipulation in  a TextBuffer is accomplished with iterators, represented by
/// a TextIter. An iterator represents a position between two characters in a text buffer.
/// TextIter is a class designed to be allocated on the stack; it's guaranteed to be copiable
/// by value and never contain any heap-allocated data. Iterators are not valid indefinitely;
/// whenever the buffer is modified in a way that affects the number of characters in the
/// buffer, all outstanding iterators become invalid. (Note that deleting 5 characters and
/// then reinserting 5 still invalidates iterators, though you end up with the same number
/// of characters you pass through a state with a different number). Because of this, 
/// iterators can't be used to preserve positions across buffer modifications. To preserve
/// a position you would use the TextMark object. TextIter is a StackObject and can only be
/// created on the stack.
///
/// <B>See also:</B> the <A HREF="../../howto/html/textview.html">TextView Widget</A> HOWTO and example.

class TextIter : public G::Boxed, public StackObject
{
public:
	typedef sigc::slot<bool, G::Unichar> TextCharPredicate;
	///< Signature of the callback slot to be called on each character when searching
	///< a text buffer for characters with forward_find_char() and backward_find_char().
	///< <B>Example:</B> Method signature for TextCharPredicate.
	///< @code
	///< bool method(G::UniChar ch);
	///<
	///< // ch: The Unicode character.
	///< @endcode

/// @name Constructors
/// @{

	TextIter();
	///< Construct an properly initialized text iterator.
	
	explicit TextIter(GtkTextIter *iter);
	///< Construct a new text iterator from an existing GtkTextIter.
	///< @param iter A pointer to a GtkTextIter.
	///<
	///< The <EM>iter</EM> can be a newly created GtkTextIter or an existing
	///< GtkTextIter. The TextIter object created is a temporary object. It doesn't
	///< take over the ownership of GtkTextIter and GtkTextIter is not freed by the
	///< destructor.

	TextIter(GtkTextIter *iter, bool copy);
	///< Construct a new text iterator from an existing GtkTextIter.
	///< @param iter A pointer to a GtkTextIter.
	///< @param copy Whether the TextIter object should make a copy of GtkTextIter or not.
	///<
	///< The <EM>iter</EM> can be a newly created GtkTextIter or an existing GtkTextIter.
	///< If <EM>copy</EM> is true TextIter will make a copy of GtkTextIter. If <EM>copy</EM>
	///< is false TextIter wont make a copy but instead takes over the ownership of GtkTextIter.
	///< Either way, the destructor will free GtkTextIter when the TextIter object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap GtkTextIter objects in a C++ wrapper.

	TextIter(const TextIter& src);
	///< Copy constructor.
	///< @param src The source iterator.

	~TextIter();
	///< Destructor.

	TextIter& operator=(const TextIter& src);
	///< Assignment operator.
	///< @param src The source iterator.

/// @}
/// @name Accessors
/// @{

	GtkTextIter* gtk_text_iter() const;
	///< Get a pointer to the GtkTextIter structure.

	operator GtkTextIter* () const;
	///< Conversion operator; safely converts a TextIter to a GtkTextIter pointer.

	TextBuffer* get_buffer() const;
	///< Returns the TextBuffer this iterator is associated with.

	int get_offset() const;
	///< Returns the character offset of an iterator. Each character in a TextBuffer has an offset,
	///< starting with 0 for the first character in the buffer. Use Gtk::TextBuffer::get_iter_at_offset()
	///< to convert an offset back into an iterator.

	int get_line() const;
	///< Returns the line number containing the iterator. Lines in a TextBuffer are numbered 
	///< beginning with 0 for the first line in the buffer.

	int get_line_offset() const;
	///< Returns the character offset of the iterator, counting from the start of a newline-terminated line.
	///< @return The offset from start of line.
	///< 
	///< The first character on the line has offset 0.

	int get_line_index() const;
	///< Returns the byte index of the iterator, counting from the start of a newline-terminated line.
	///< @return The distance from start of line, in bytes.
	///<
	///< Remember that TextBuffer encodes text in UTF-8, and that characters can require a 
	///< variable number of bytes to represent them.

	int get_visible_line_offset() const;
	///< Returns the offset in characters from the start of the line to the iterator, not counting
	///< characters that are invisible due to tags with the "invisible" flag toggled on.
	///< @return The offset in visible characters from the start of the line.

	int get_visible_line_index() const;
	///< Returns the number of bytes from the start of the line to the iterator, not counting
	///< bytes that are invisible due to tags with the "invisible" flag toggled on.
	///< @return The byte index of iterator with respect to the start of the line.

	G::Unichar get_char() const;
	///< Returns the Unicode character at this iterator.
	///< @return A Unicode character, or 0 if the iterator is not dereferenceable.
	///<
	///< Equivalent to using the dereference operator on the iterator. If the element at this
	///< iterator is a non-character element, such as an image embedded in the buffer, the Unicode
	///< "unknown" character 0xFFFC is returned. If invoked on the end iterator, zero is returned;
	///< zero is not a valid Unicode character. So you can write a loop which ends when get_char()
	///< returns 0.

	G::Unichar operator*() const;
	///< The dereference operator returns the Unicode character at this iterator.
	///< @return A Unicode character, or 0 if iter is not dereferenceable.
	///<
	///< Equivalent to calling get_char() on the iterator. If the element at this iterator
	///< is a non-character element, such as an image embedded in the buffer, the Unicode
	///< "unknown" character 0xFFFC is returned. If invoked on the end iterator, zero is
	///< returned; zero is not a valid Unicode character. So you can write a loop which ends
	///< when get_char() returns 0.

	Gdk::Pixbuf* get_pixbuf() const;
	///< If the element at this iterator is a pixbuf, the pixbuf is returned 
	///< (with no new reference count added), otherwise null is returned.
	
	bool get_marks(std::vector<TextMark*>& marks) const;
	///< Retrieves a list of all TextMark at this location.
	///< @param marks A reference to a vector of TextMark* to hold the marks.
	///< @return <EM>true</EM> if any marks were retrieved.
	///<
	///< Because marks are not iterable (they don't take up any "space" in the buffer,
	///< they are just marks in between iterable locations), multiple marks can exist in 
	///< the same place. The marks retrieved are not in any meaningful order.
	
	TextChildAnchor* get_child_anchor() const;
	///< If the location at this iterator contains a child anchor, the anchor is returned
	///< (with no new reference count added), otherwise, null is returned.
	
	bool get_toggled_tags(std::vector<TextTag*>& tags, bool toggled_on) const;
	///< Retrieves a list of TextTag that are toggled on or off at this point.
	///< @param tags A reference to a vector of TextTag* to hold the tags.
	///< @param toggled_on <EM>true</EM> to get toggled-on tags.
	///< @return <EM>true</EM> if any tags are retrieved.
	///<
	///< If toggled_on is true, the list contains tags that are toggled on. If a tag
	///< is toggled on at this iterator, then some non-empty range of characters following
	///< the iterator has that tag applied to it. If a tag is toggled off, then some 
	///< non-empty range following the iterator does not have the tag applied to it.

	bool begins_tag(const TextTag *tag = 0) const;
	///< Returns true if tag is toggled on at exactly this point. 
	///< @param tag A TextTag, or null.
	///< @return Whether this iterator is the start of a range tagged with tag.
	///<
	///< If tag is null, returns true if any tag is toggled on at this point. 
	///< Note that the begins_tag() returns true if the iterator is the start of
	///< the tagged range; has_tag() tells you whether the iterator is within a
	///< tagged range.

	bool ends_tag(const TextTag *tag = 0) const;
	///< Returns true if tag is toggled off at exactly this point. 
	///< @param tag A TextTag, or null.
	///< @return Whether this iterator is the end of a range tagged with tag.
	///<
	///< If tag is null, returns true if any tag is toggled off at this point.
	///< Note that the ends_tag() returns true if iter is the end of the tagged
	///< range; has_tag() tells you whether an iterator is within a tagged range.

	bool toggles_tag(const TextTag *tag = 0) const;
	///< This is equivalent to (begins_tag() || ends_tag()), that is, it tells you
	///< whether a range with tag applied to it begins or ends at iter.
	///< @param tag A TextTag, or null.
	///< @return Whether <EM>tag</EM> is toggled on or off at this iterator.

	bool has_tag(const TextTag& tag) const;
	///< Returns true if the iterator is within a range tagged with <EM>tag</EM>.
	///< @param tag A TextTag.
	///< @return Whether this iterator is tagged with tag.

	bool get_tags(std::vector<TextTag*>& tags) const;
	///< Retrieves a list of tags that apply to this iterator, in ascending order
	///< of priority (highest-priority tags are last).
	///< @param tags A reference to a vector of TextTag* to hold the tags.
	///< @return <EM>true</EM> if any tags were retrieved.
	///<
	///< The TextTag in the vector don't have a reference added.

	bool editable(bool default_setting) const;
	///< Returns whether the character at the iterator is within an editable region of text.
	///< @param default_setting <EM>true</EM> if text is editable by default.
	///< @return Whether the iterator is inside an editable range.
	///<
	///< Non-editable text is "locked" and can't be changed by the user via TextView.
	///< This method is simply a convenience wrapper around get_attributes(). If no tags
	///< applied to this text affect editability, <EM>default_setting</EM> will be returned.
	///< 
	///< You don't want to use this method to decide whether text can be inserted at the
	///< iterator, because for insertion you don't want to know whether the char at the 
	///< iterator is inside an editable range, you want to know whether a new character 
	///< inserted at the iterator would be inside an editable range. Use can_insert() to
	///< handle this case.

	bool can_insert(bool default_editability) const;
	///< Considering the default editability of the buffer, and tags that affect editability,
	///< determines whether text inserted at this iterator would be editable.
	///< @param default_editability <EM>true</EM> if text is editable by default.
	///< @return Whether text inserted at the iterator would be editable.
	///<
	///< If text inserted at the iterator would be editable then the user should be
	///< allowed to insert text at the iterator. Gtk::TextBuffer::insert_interactive()
	///< uses this method to decide whether insertions are allowed at a given position.

	bool starts_word() const;
	///< Determines whether the iterator begins a natural-language word.
	///< @return <EM>true</EM> if the iterator is at the start of a word.
	///<
	///< Word breaks are determined by Pango and should be correct for nearly any language
	///< (if not, the correct fix would be to the Pango word break algorithms).

	bool ends_word() const;
	///< Determines whether the iterator ends a natural-language word.
	///< @return <EM>true</EM> if the iterator is at the end of a word.
	///<
	///< Word breaks are determined by Pango and should be correct for nearly any language
	///< (if not, the correct fix would be to the Pango word break algorithms).

	bool inside_word() const;
	///< Determines whether the iterator is inside a natural-language word (as opposed to say
	///< inside some whitespace). 
	///< @return <EM>true</EM> if the iterator is inside a word.
	///<
	///< Word breaks are determined by Pango and should be correct for nearly any language
	///< (if not, the correct fix would be to the Pango word break algorithms).

	bool starts_sentence() const;
	///< Determines whether the iterator begins a sentence.
	///< @return <EM>true</EM> if the iterator is at the start of a sentence.
	///<
	///< Sentence boundaries are determined by Pango and should be correct for nearly any
	///< language (if not, the correct fix would be to the Pango text boundary algorithms).

	bool ends_sentence() const;
	///< Determines whether the iterator ends a sentence.
	///< @return <EM>true</EM> if the iterator is at the end of a sentence.
	///<
	///< Sentence boundaries are determined by Pango and should be correct for nearly any
	///< language (if not, the correct fix would be to the Pango text boundary algorithms).

	bool inside_sentence() const;
	///< Determines whether the iterator is inside a sentence (as opposed to in between two sentences,
	///< for example, after a period and before the first letter of the next sentence).
	///< @return <EM>true</EM> if the iterator is inside a sentence.
	///<
	///< Sentence boundaries are determined by Pango and should be correct for nearly any
	///< language (if not, the correct fix would be to the Pango text boundary algorithms).

	bool starts_line() const;
	///< Returns true if the iterator begins a paragraph, that is, if get_line_offset() would return 0.
	///< @return Whether the iterator begins a line.
	///<
	///< This method is potentially more efficient than get_line_offset() because
	///< it doesn't have to compute the offset, it just has to see whether it's 0.

	bool ends_line() const;
	///< Returns true if the iterator points to the start of the paragraph delimiter
	///< characters for a line.
	///< @return Whether the iterator is at the end of a line.
	///<
	///< Delimiters will be either a newline, a carriage return, a carriage return followed
	///< by a newline, or a Unicode paragraph separator character. Note that an iterator pointing
	///< to the \\n of a \\r\\n pair will not be counted as the end of a line, the line ends before
	///< the \\r. The end iterator is considered to be at the end of a line, even though there are
	///< no paragraph delimiter chars there.

	bool is_cursor_position() const;
	///< Returns <EM>true</EM> if the cursor can be placed at this iterator. See
	///< forward_cursor_position() or PangoLogAttr or pango_break() for details
	///< on what a cursor position is.

	int get_chars_in_line() const;
	///< Returns the number of characters in the line containing this iterator,
	///< including the paragraph delimiters.

	int get_bytes_in_line() const;
	///< Returns the number of bytes in the line containing this iterator, 
	///< including the paragraph delimiters.

	bool get_attributes(TextAttributes& values) const;
	///< Computes the effect of any tags applied to this spot in the text.
	///< @param values A TextAttributes to be filled in.
	///< @return <EM>true</EM> if values was modified.
	///<
	///< The values parameter should be initialized to the default settings
	///< you wish to use if no tags are in effect. You'd typically obtain the 
	///< defaults from Gtk::TextView::get_default_attributes().
	///<
	///< get_attributes() will modify values, applying the effects of any tags 
	///< present at the iterator. If any tags affected values, the function 
	///< returns true.

	PangoLanguage* get_language() const;
	///< A convenience wrapper around get_attributes(), which returns the language
	///< in effect at this iterator.
	///< @return The language in effect at the iterator.
	///<
	///< If no tags affecting language apply to the iterator, the return value
	///< is identical to that of gtk_get_default_language().

	bool is_end() const;
	///< Returns true if this iterator is the end iterator, that is, one past the last
	///< dereferenceable iterator in the buffer.
	///< @return Whether the iterator is the end iterator.
	///<
	///< is_end() is the most efficient way to check whether an iterator is the end iterator.

	bool is_start() const;
	///< Returns true if this iterator is the first iterator in the buffer, that is,
	///< if iter has a character offset of 0.
	///< @return Whether the iterator is the first in the buffer.

	bool equal(const TextIter& other) const;
	///< Tests whether two iterators are equal, using the fastest possible mechanism.
	///< @param other Another TextIter.
	///< @return <EM>true</EM> if the iterators point to the same place in the buffer.
	///<
	///< This method is very fast; you can expect it to perform better than for example,
	///< getting the character offset for each iterator and comparing the offsets yourself.
	///< Also, it's a bit faster than compare().

	int compare(const TextIter& other) const;
	///< A qsort()-style method that returns negative if this iterator is less than <EM>other</EM>,
	///< positive if it's greater than <EM>other</EM>, and 0 it's equal to <EM>other</EM>.
	///< @param other Another TextIter.
	///< @return -1 if this iterator is less than other, 1 if it's greater, 0 if they are equal.
	///<
	///< Ordering is in character offset order, that is, the first character in the buffer
	///< is less than the second character in the buffer.

	bool in_range(const TextIter& start, const TextIter& end);
	///< Checks whether this iterator falls in the range (start, end); 
	///< start and end must be in ascending order.
	///< @param start The start of range.
	///< @param end The end of range.
	///< @return <EM>true</EM> if this iterator is in the range.

	bool operator==(const TextIter& other) const;
	///< Returns true if this iterator is equal to other.
	///< @param other Another TextIter.

	bool operator!=(const TextIter& other) const;
	///< Returns true if this iterator is not equal to other.
	///< @param other Another TextIter.

	bool operator<(const TextIter& other) const;
	///< Returns true if this iterator is less than other.
	///< @param other Another TextIter.

	bool operator>(const TextIter& other) const;
	///< Returns true if this iterator is greater than other.
	///< @param other Another TextIter.

	bool operator<=(const TextIter& other) const;
	///< Returns true if this iterator is less than or equal to other.
	///< @param other Another TextIter.

	bool operator>=(const TextIter& other) const;
	///< Returns true if this iterator is greater than or equal to other.
	///< @param other Another TextIter.

/// @}
/// @name Accessors
/// @{

	static String get_slice(const TextIter& start, const TextIter& end);
	///< Returns the text in the given range.
	///< @param start The iterator at start of a range.
	///< @param end The iterator at end of a range.
	///< @return A slice of text from the buffer.
	///<
	///< A "slice" is an array of characters encoded in UTF-8 format, including the Unicode
	///< "unknown" character 0xFFFC for iterable non-character elements in the buffer, such as
	///< images. Because images are encoded in the slice, byte and character offsets in the
	///< returned String will correspond to byte offsets in the text buffer. Note that 0xFFFC
	///< can occur in normal text as well, so it is not a reliable indicator that a pixbuf or
	///< widget is in the buffer.

	static String get_text(const TextIter& start, const TextIter& end);
	///< Returns the text in the given range.
	///< @param start The iterator at start of a range.
	///< @param end The iterator at end of a range.
	///< @return A String containing the characters from the buffer.
	///<
	///< If the range contains non-text elements such as images, the character and byte offsets
	///< in the returned string will not correspond to character and byte offsets in the buffer.
	///< If you want offsets to correspond, get_slice().

	static String get_visible_slice(const TextIter& start, const TextIter& end);
	///< Like get_slice(), but invisible text is not included. 
	///< @param start The iterator at start of a range.
	///< @param end The iterator at end of a range.
	///< @return A slice of text from the buffer.
	///<
	///< Invisible text is usually invisible because a TextTag with the "invisible" attribute
	///< turned on has been applied to it.

	static String get_visible_text(const TextIter& start, const TextIter& end);
	///< Like get_text(), but invisible text is not included.
	///< @param start The iterator at start of a range.
	///< @param end The iterator at end of a range.
	///< @return A String containing visible text in the range.
	///<
	///< Invisible text is usually invisible because a TextTag with the "invisible" attribute
	///< turned on has been applied to it.

/// @}
/// @name Methods
/// @{

	bool forward_char();
	///< Moves the iterator forward by one character offset.
	///< @return Whether the iterator moved and is dereferenceable.
	///<
	///< Note that images embedded in the buffer occupy 1 character slot, so forward_char() may
	///< actually move onto an image instead of a character, if you have images in your buffer. If
	///< the iterator is the end iterator or one character before it, the iterator will now point at
	///< the end iterator, and forward_char() returns false for convenience when writing loops.

	bool backward_char();
	///< Moves backward by one character offset. 
	///< @return <EM>true</EM> if movement was possible.
	///<
	///< If the iterator was the first in the buffer (character offset 0), backward_char()
	///< returns false for convenience when writing loops.
	
	bool forward_chars(int count);
	///< Moves <EM>count</EM> characters if possible (if count would move past the start or end
	///< of the buffer, moves to the start or end of the buffer). 
	///< @param count The number of characters to move, may be negative.
	///< @return Whether the iterator moved and is dereferenceable.
	///<
	///< The return value indicates whether the new position of the iterator is different
	///< from its original position, and dereferenceable (the last iterator in the buffer is
	///< not dereferenceable). If <EM>count</EM> is 0, the function does nothing and returns false.

	bool backward_chars(int count);
	///< Moves <EM>count</EM> characters backward, if possible (if count would move past the start or end
	///< of the buffer, moves to the start or end of the buffer).
	///< @param count The number of characters to move, may be negative.
	///< @return Whether the iterator moved and is dereferenceable.
	///<
	///< The return value indicates whether the iterator moved onto a dereferenceable position;
	///< if the iterator didn't move, or moved onto the end iterator, then false is returned. If
	///< <EM>count</EM> is 0, the function does nothing and returns false.
	
	bool forward_line();
	///< Moves the iterator to the start of the next line. 
	///< @return Whether the iterator can be dereferenced.
	///<
	///< Returns true if there was a next line to move to, and false if the iterator was simply moved
	///< to the end of the buffer and is now not dereferenceable, or if the iterator was already at the 
	///< end of the buffer.

	bool backward_line();
	///< Moves the iterator to the start of the previous line. 
	///< @return Whether the iterator moved.
	///<
	///< Returns true if the iterator could be moved; that is, if the iterator was at character offset
	///< 0, this method returns false. Therefore if the iterator was already on line 0, but not at the
	///< start of the line, the iterator is snapped to the start of the line and the method returns true.
	///< (Note that this implies that in a loop calling this method, the line number may not change on
	///< every iteration, if your first iteration is on line 0.)

	bool forward_lines(int count);
	///< Moves <EM>count</EM> lines forward, if possible (if count would move past the start or end
	///< of the buffer, moves to the start or end of the buffer). 
	///< @param count The number of lines to move forward.
	///< @return Whether the iterator moved and is dereferenceable.
	///<
	///< The return value indicates whether the iterator moved onto a dereferenceable position; if the
	///< iterator didn't move, or moved onto the end iterator, then false is returned. If <EM>count</EM>
	///< is 0, the method does nothing and returns false. If <EM>count</EM> is negative, the iterator
	///< moves backward by 0 - <EM>count</EM> lines.

	bool backward_lines(int count);
	///< Moves <EM>count</EM> lines backward, if possible (if count would move past the start or end
	///< of the buffer, moves to the start or end of the buffer). 
	///< @param count The number of lines to move backward.
	///< @return Whether iter moved and is dereferenceable.
	///<
	///< The return value indicates whether the iterator moved onto a dereferenceable position; if the
	///< iterator didn't move, or moved onto the end iterator, then false is returned. If <EM>count</EM>
	///< is 0, the method does nothing and returns false. If <EM>count</EM> is negative, moves forward
	///< by 0 - <EM>count</EM> lines.

	bool forward_word_end();
	///< Moves forward to the next word end. 
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.
	///<
	///< If the iterator is currently on a word end, it moves forward to the next one after that.
	///< Word breaks are determined by Pango and should be correct for nearly any language (if not,
	///< the correct fix would be to the Pango word break algorithms).

	bool backward_word_start();
	///< Moves backward to the previous word start. 
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.
	///<
	///< If iter is currently on a word start, moves backward to the next one after that. Word breaks
	///< are determined by Pango and should be correct for nearly any language (if not, the correct fix
	///< would be to the Pango word break algorithms).

	bool forward_word_ends(int count);
	///< Calls forward_word_end() up to <EM>count</EM> times.
	///< @param count The number of times to move.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.

	bool backward_word_starts(int count);
	///< Calls backward_word_start() up to <EM>count</EM> times.
	///< @param count The number of times to move.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.

	bool forward_visible_word_end();
	///< Moves forward to the next visible word end.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.
	///<
	///< If the iterator is currently on a word end, moves forward to the next one after that.
	///< Word breaks are determined by Pango and should be correct for nearly any language (if not,
	///< the correct fix would be to the Pango word break algorithms).

	bool backward_visible_word_start();
	///< Moves backward to the previous visible word start.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.
	///<
	///< If the iterator is currently on a word start, moves backward to the next one after that.
	///< Word breaks are determined by Pango and should be correct for nearly any language (if not,
	///< the correct fix would be to the Pango word break algorithms).

	bool forward_visible_word_ends(int count);
	///< Calls forward_visible_word_end() up to count times.
	///< @param count The number of times to move.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.

	bool backward_visible_word_starts(int count);
	///< Calls backward_visible_word_start() up to count times.
	///< @param count The number of times to move.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.

	bool forward_sentence_end();
	///< Moves forward to the next sentence end.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.
	///<
	///< If the iterator is at the end of a sentence, moves to the next end of sentence.
	///< Sentence boundaries are determined by Pango and should be correct for nearly any
	///< language (if not, the correct fix would be to the Pango text boundary algorithms).

	bool backward_sentence_start();
	///< Moves backward to the previous sentence start.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.
	///<
	///< If the iterator is already at the start of a sentence, moves backward to the next one.
	///< Sentence boundaries are determined by Pango and should be correct for nearly any language
	///< (if not, the correct fix would be to the Pango text boundary algorithms).

	bool forward_sentence_ends(int count);
	///< Calls forward_sentence_end() <EM>count</EM> times (or until forward_sentence_end() returns false).
	///< @param count The number of sentences to move.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.
	///<
	///< If count is negative, the iterator moves backward instead of forward.

	bool backward_sentence_starts(int count);
	///< Calls backward_sentence_start() up to <EM>count</EM> times, or until it returns false.
	///< @param count The number of sentences to move.
	///< @return <EM>true</EM> if the iterator moved and is not the end iterator.
	///<
	///< If <EM>count</EM> is negative, the iterator moves forward instead of backward.

	bool forward_cursor_position();
	///< Moves the iterator forward by a single cursor position.
	///< @return <EM>true</EM> if we moved and the new position is dereferenceable.
	///<
	///< Cursor positions are (unsurprisingly) positions where the cursor can appear.
	///< Perhaps surprisingly, there may not be a cursor position between all characters.
	///< The most common example for European languages would be a carriage return/newline
	///< sequence. For some Unicode characters, the equivalent of say the letter "a" with
	///< an accent mark will be represented as two characters, first the letter then a 
	///< "combining mark" that causes the accent to be rendered; so the cursor can't go 
	///< between those two characters. See also the PangoLogAttr structure and pango_break()
	///< function. 

	bool backward_cursor_position();
	///< Like forward_cursor_position(), but moves backward.
	///< @return <EM>true</EM> if we moved.

	bool forward_cursor_positions(int count);
	///< Moves up to <EM>count</EM> cursor positions (see forward_cursor_position() for details).
	///< @param count The number of positions to move.
	///< @return <EM>true</EM> if we moved and the new position is dereferenceable.

	bool backward_cursor_positions(int count);
	///< Moves up to <EM>count</EM> cursor positions backwards (see forward_cursor_position() for details).
	///< @param count The number of positions to move.
	///< @return <EM>true</EM> if we moved and the new position is dereferenceable.
	
	bool forward_visible_cursor_position();
	///< Moves the iterator forward to the next visible cursor position
	///< (see forward_cursor_position() for details).
	///< @return <EM>true</EM> if the iterator moved and the new position is dereferenceable.

	bool backward_visible_cursor_position();
	///< Moves the iterator backward to the previous visible cursor position
	///< (see backward_cursor_position() for details).
	///< @return <EM>true</EM> if the iterator moved and the new position is dereferenceable.

	bool forward_visible_cursor_positions(int count);
	///< Moves the iterator up to count visible cursor positions
	///< (see forward_cursor_position() for details).
	///< @param count The number of positions to move.
	///< @return <EM>true</EM> if the iterator moved and the new position is dereferenceable.

	bool backward_visible_cursor_positions(int count);
	///< Moves the iterator up to count visible cursor positions
	///< (see forward_cursor_position() for details).
	///< @param count The number of positions to move.
	///< @return <EM>true</EM> if the iterator moved and the new position is dereferenceable.

	void set_offset(int char_offset);
	///< Sets the iterator to point to <EM>char_offset</EM>.
	///< @param char_offset A character number.
	///< 
	///< <EM>char_offset</EM> counts from the start of the entire text buffer, starting with 0.

	void set_line(int line_number);
	///< Moves the iterator to the start of the line <EM>line_number</EM>. 
	///< @param line_number The line number (counted from 0).
	///<
	///< If line_number is negative or larger than the number of lines in the buffer,
	///< moves iter to the start of the last line in the buffer.

	void set_line_offset(int char_on_line);
	///< Moves the iterator within a line, to a new character (not byte) offset.
	///< @param char_on_line A character offset relative to the start of iter's current line.
	///<
	///< The given character offset must be less than or equal to the number of characters
	///< in the line; if equal, the iterator moves to the start of the next line. See 
	///< set_line_index() if you have a byte index rather than a character offset.

	void set_line_index(int byte_on_line);
	///< Same as set_line_offset(), but works with a byte index. 
	///< @param byte_on_line A byte index relative to the start of iter's current line.
	///<
	///< The given byte index must be at the start of a character, it can't be in the 
	///< middle of a UTF-8 encoded character.

	void set_visible_line_offset(int char_on_line);
	///< Like set_line_offset(), but the offset is in visible characters, that is, text with a tag
	///< making it invisible is not counted in the offset.
	///, @param char_on_line A character offset.

	void set_visible_line_index(int byte_on_line);
	///< Like set_line_index(), but the index is in visible bytes, that is, text with a tag
	///< making it invisible is not counted in the index.
	///< @param byte_on_line A byte index.

	void forward_to_end();
	///< Moves the iterator forward to the "end iterator", which points one past the last
	///< valid character in the buffer. Note get_char() called on the end iterator returns 0,
	///< which is convenient for writing loops.

	bool forward_to_line_end();
	///< Moves the iterator to point to the paragraph delimiter characters, which will be 
	///< either a newline, a carriage return, a carriage return/newline in sequence, or 
	///< the Unicode paragraph separator character. 
	///< @return <EM>true</EM> if we moved and the new location is not the end iterator.
	///<
	///< If the iterator is already at the paragraph delimiter characters, it moves 
	///< to the paragraph delimiter characters for the next line. If the iterator is on
	///< the last line in the buffer, which does not end in paragraph delimiters, it moves
	///< to the end iterator (end of the last line), and returns false.

	bool forward_to_tag_toggle(const TextTag *tag = 0);
	///< Moves forward to the next toggle (on or off) of the TextTag <EM>tag</EM>, or to 
	///< the next toggle of any tag if <EM>tag</EM> is null.
	///< @param tag A TextTag, or null.
	///< @return Whether we found a tag toggle after the iterator.
	///<
	///< If no matching tag toggles are found, returns false, otherwise true. Does not
	///< return toggles located at the iterator, only toggles after the iterator. Sets the 
	///< iterator to the location of the toggle, or to the end of the buffer if no toggle
	///< is found.
	
	bool backward_to_tag_toggle(const TextTag *tag = 0);
	///< Moves backward to the next toggle (on or off) of the TextTag <EM>tag</EM>, or to
	///< the next toggle of any tag if <EM>tag</EM> is null. 
	///< @param tag A TextTag, or null.
	///< @return Whether we found a tag toggle before the iterator.
	///<
	///< If no matching tag toggles are found, returns false, otherwise true. Does not
	///< return toggles located at the iterator, only toggles before the iterator. Sets the
	///< iterator to the location of the toggle, or the start of the buffer if no toggle is
	///< found.

	bool forward_find_char(const TextCharPredicate& predicate, const TextIter *limit = 0);
	///< Advances the iterator, calling <EM>predicate</EM> on each character.
	///< @param predicate A callback slot to be called on each character.
	///< @param limit The search limit, or null for none.
	///< @return Whether a match was found.
	///<
	///< If <EM>predicate</EM> returns true, returns true and stops scanning. 
	///< If <EM>predicate</EM> never returns true, the iterator is set to 
	///< <EM>limit</EM> if limit is non-null, otherwise to the end iterator.

	bool backward_find_char(const TextCharPredicate& predicate, const TextIter *limit = 0);
	///< Same as forward_find_char(), but goes backward from the iterator.
	///< @param predicate A callback slot to be called on each character.
	///< @param limit The search limit, or null for none.
	///< @return Whether a match was found.

	bool forward_search(const char *str, const TextIter *limit = 0);
	bool forward_search(const String& str, const TextIter *limit = 0);
	///< Searches forward for <EM>str</EM>.
	///< @param str A search string.
	///< @param limit The bound for the search, or null for the end of the buffer.
	///< @return Whether a match was found
	///<
	///< The search will not continue past <EM>limit</EM>. Note that a search is a linear
	///< or O(n) operation, so you may wish to use limit to avoid locking up your UI on large
	///< buffers. The TEXT_SEARCH_VISIBLE_ONLY flag is used so the match may have invisible text
	///< interspersed in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence
	///< of the matched range).

	bool forward_search(const char *str, TextIter *match_start, TextIter *match_end, const TextIter *limit = 0);
	bool forward_search(const String& str, TextIter *match_start, TextIter *match_end, const TextIter *limit = 0);
	///< Searches forward for <EM>str</EM>.
	///< @param str A search string.
	///< @param match_start The return location for start of match, or null.
	///< @param match_end The return location for end of match, or null.
	///< @param limit The bound for the search, or null for the end of the buffer.
	///< @return Whether a match was found
	///<
	///< Any match is returned by setting <EM>match_start</EM> to the first character of the
	///< match and <EM>match_end</EM> to the first character after the match. The search will
	///< not continue past <EM>limit</EM>. Note that a search is a linear or O(n) operation,
	///< so you may wish to use limit to avoid locking up your UI on large buffers. The
	///< TEXT_SEARCH_VISIBLE_ONLY flag is used so the match may have invisible text interspersed
	///< in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence of the matched range).

	bool forward_search(const char *str, TextSearchFlagsField flags, TextIter *match_start, TextIter *match_end, const TextIter *limit = 0);
	bool forward_search(const String& str, TextSearchFlagsField flags, TextIter *match_start, TextIter *match_end, const TextIter *limit = 0);
	///< Searches forward for <EM>str</EM>.
	///< @param str A search string.
	///< @param flags The Gtk::TextSearchFlags affecting how the search is done.
	///< @param match_start The return location for start of match, or null.
	///< @param match_end The return location for end of match, or null.
	///< @param limit The bound for the search, or null for the end of the buffer.
	///< @return Whether a match was found
	///<
	///< Any match is returned by setting <EM>match_start</EM> to the first character of the
	///< match and <EM>match_end</EM> to the first character after the match. The search will
	///< not continue past <EM>limit</EM>. Note that a search is a linear or O(n) operation,
	///< so you may wish to use limit to avoid locking up your UI on large buffers. If the
	///< TEXT_SEARCH_VISIBLE_ONLY flag is present, the match may have invisible text
	///< interspersed in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence
	///< of the matched range). Similarly, if you specify TEXT_SEARCH_TEXT_ONLY, the match may
	///< have pixbufs or child widgets mixed inside the matched range. If these flags are not
	///< given, the match must be exact; the special 0xFFFC character in str will match embedded
	///< pixbufs or child widgets.

	bool backward_search(const char * str, const TextIter *limit = 0);
	bool backward_search(const String& str, const TextIter *limit = 0);
	///< Same as forward_search(), but moves backward.
	///< @param str The search string.
	///< @param limit The location of last possible match_start, or null for start of buffer.
	///< @return Whether a match was found.
	///<
	///< The TEXT_SEARCH_VISIBLE_ONLY flag is used so the match may have invisible text
	///< interspersed in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence
	///< of the matched range).

	bool backward_search(const char * str, TextIter *match_start, TextIter *match_end, const TextIter *limit = 0);
	bool backward_search(const String& str, TextIter *match_start, TextIter *match_end, const TextIter *limit = 0);
	///< Same as forward_search(), but moves backward.
	///< @param str The search string.
	///< @param match_start The return location for start of match, or null.
	///< @param match_end The return location for end of match, or null.
	///< @param limit The location of last possible match_start, or null for start of buffer.
	///< @return Whether a match was found.
	///<
	///< The TEXT_SEARCH_VISIBLE_ONLY flag is used so the match may have invisible text
	///< interspersed in <EM>str</EM> (i.e. str will be a possibly-noncontiguous subsequence
	///< of the matched range).
	
	bool backward_search(const char *str, TextSearchFlagsField flags, TextIter *match_start, TextIter *match_end, const TextIter *limit = 0);
	bool backward_search(const String& str, TextSearchFlagsField flags, TextIter *match_start, TextIter *match_end, const TextIter *limit = 0);
	///< Same as forward_search(), but moves backward.
	///< @param str The search string.
	///< @param flags The bitmask of Gtk::TextSearchFlags affecting the search.
	///< @param match_start The return location for start of match, or null.
	///< @param match_end The return location for end of match, or null.
	///< @param limit The location of last possible match_start, or null for start of buffer.
	///< @return Whether a match was found.
	
	TextIter operator+(int chars) const;
	///< Returns a TextIter to the position <EM>chars</EM> characters from this iterator
	///< in a forward direction.
	///< @param chars The number of characters from this iterator.
	///< @return A TextIter to the new position.

	TextIter operator-(int chars) const;
	///< Returns a TextIter to the position <EM>chars</EM> characters from this iterator
	///< in a backward direction.
	///< @param chars The number of characters from this iterator.
	///< @return A TextIter to the new position.

	TextIter& operator+=(int chars);
	///< Calls forward_chars() to move this iterator forward <EM>chars</EM> characters.
	///< @param chars The number of characters to move this iterator.
	///< @return A reference to the iterator.

	TextIter& operator-=(int chars);
	///< Calls backward_chars() to move this iterator backward <EM>chars</EM> characters.
	///< @param chars The number of characters to move this iterator.
	///< @return A reference to the iterator.

	TextIter& operator++();
	///< Calls forward_char() to move this iterator forward one character.

	TextIter& operator--();
	///< Calls backward_char() to move this iterator back one character.

	TextIter operator++(int);
	///< Calls forward_char() to move this iterator forward one character.

	TextIter operator--(int);
	///< Calls backward_char() to move this iterator back one character.

/// @}
/// @name Methods
/// @{
	
	static void order(const TextIter& first, const TextIter& second);
	///< Swaps the value of first and second if second comes before first in the buffer. 
	///< @param first A TextIter.
	///< @param second Another TextIter.
	///<
	///< This method ensures that first and second are in sequence. Most text buffer functions
	///< that take a range call this automatically on your behalf, so there's no real reason to 
	///< call it yourself in those cases. There are some exceptions, such as in_range(), that expect
	///< a pre-sorted range.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/textiter.inl>

#endif // XFC_GTK_TEXT_ITER_HH

