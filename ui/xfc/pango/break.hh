/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
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
 
/// @file xfc/pango/break.hh
/// @brief A PangoLogAttr C++ wrapper interface.
///
/// Provides LogAttr, an object that stores information about the attributes of a single character.

#ifndef XFC_PANGO_BREAK_HH
#define XFC_PANGO_BREAK_HH

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __PANGO_BREAK_H__
#include <pango/pango-break.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Pango {

class Analysis;

/// @class LogAttr break.hh xfc/pango/break.hh
/// @brief A PangoLogAttr C++ wrapper class.
///
/// LogAttr stores information about the logical attributes of a single character.

class LogAttr
{
	PangoLogAttr attr_;

public:
/// @name Constructors
/// @{

	LogAttr();
	///< Constructs a new LogAttr with all fields set to false.
	
/// @}
/// @name Accessors
/// @{

	PangoLogAttr* pango_log_attr() const;
	///< Get a pointer to the PangoLogAttr structure.

	operator PangoLogAttr* () const;
	///< Conversion operator; safely converts a LogAttr to a PangoLogAttr pointer.

	bool is_line_break() const;
	///< Returns true if can break the line in front of the character.

	bool is_mandatory_break() const;
	///< Returns true if must break the line in front of the character.

	bool is_char_break() const;
	///< Returns true if can break at this character when doing character wrapping.

	bool is_white() const;
	///< Returns true if this is a whitespace character.

	bool is_cursor_position() const;
	///< Returns true if the cursor can appear in front of character (that is this
	///< is a grapheme boundary, or the first character in the text).

	bool is_word_start() const;
	///< Returns true if this is the first character in a word.

	bool is_word_end() const;
	///< Returns true if this is the first non-word character after a word.

	bool is_sentence_boundary() const;
	///< Returns true if this character is a sentence boundary.
	///< There are two ways to divide sentences. The first assigns all intersentence
	///< whitespace/control/format characters to some sentence, so all characters are
	///< in some sentence; is_sentence_boundary() denotes the boundaries there. The
	///< second way doesn't assign between-sentence spaces, etc. to any sentence, so
	///< is_sentence_start()/is_sentence_end() mark the boundaries of those sentences.

	bool is_sentence_start() const;
	///< Returns true if this character marks the start of a sentence (see is_sentence_boundary()).

	bool is_sentence_end() const;
	///< Returns true if this character marks the end of a sentence (see is_sentence_boundary()).

	bool backspace_deletes_character() const;
	///< Returns true if the backspace key deletes one character rather
	///< than the entire grapheme cluster.

/// @}
/// @name Methods
/// @{

	void set_is_line_break(bool setting);
	///< Set whether the character is a line break.
	///< @param setting The setting.

	void set_is_mandatory_break(bool setting);
	///< Set whether the character is a mandatory line break.
	///< @param setting The setting.

	void set_is_char_break(bool setting);
	///< Set whether a line can be broken at the character when wrapping characters.
	///< @param setting The setting.

	void set_is_white(bool setting);
	///< Set whether the character is white space.
	///< @param setting The setting.

	void set_is_cursor_position(bool setting);
	///< Set whether the cursor can appear in front of character (that is this is
	///< a grapheme boundary, or the first character in the text).
	///< @param setting The setting.

	void set_is_word_start(bool setting);
	///< Set whether the character is the first character in a word.
	///< @param setting The setting.

	void set_is_word_end(bool setting);
	///< Set whether the character is the first non-word character after a word.
	///< @param setting The setting.

	void set_is_sentence_boundary(bool setting);
	///< Set whether the character is a sentence boundary.
	///< @param setting The setting.

	void set_is_sentence_start(bool setting);
	///< Set whether the character marks the start of a sentence.
	///< @param setting The setting.

	void set_is_sentence_end(bool setting);
	///< Set whether the character marks the end of a sentence.
	///< @param setting The setting.

	void set_backspace_deletes_character(bool setting);
	///< Set whether the backspace key deletes one character rather than
	///< the entire grapheme cluster.
	///< @param setting The setting.

/// @}
};

/// @name Rendering Methods
/// @{

void break_text(const String& text, const Analysis& analysis, std::vector<LogAttr>& attrs);
///< Determines possible line, word, and character breaks for a string of Unicode text.
///< @param text The text to process.
///< @param analysis An Analysis structure from Pango::Context::itemize().
///< @param attrs A vector of LogAttr to store the character information in.

void find_paragraph_boundary(const String& text, int *paragraph_delimiter_index, int *next_paragraph_start);
///< Locates a paragraph boundary in text. 
///< @param text The UTF-8 text.
///< @param paragraph_delimiter_index The return location for index of delimiter.
///< @param next_paragraph_start The return location for start of next paragraph.
///<
///< A boundary is caused by delimiter characters, such as a newline, carriage return,
///< carriage return-newline pair, or Unicode paragraph separator character. The index of
///< the run of delimiters is returned in paragraph_delimiter_index. The index of the start
///< of the paragraph (index after all delimiters) is stored in next_paragraph_start. If no
///< delimiters are found, both paragraph_delimiter_index and next_paragraph_start are filled
///< with the length of text (an index one off the end).

void get_log_attrs(const String& text, PangoLanguage *language, std::vector<LogAttr>& attrs, int level = -1);
///< Computes a LogAttr for each character in <EM>text</EM>. 
///< @param text The text to process.
///< @param language The language tag.
///< @param attrs A vector of LogAttr with one LogAttr per character in text, plus one extra, to be filled in.
///< @param level The embedding level, or -1 if unknown.
///<
///< The <EM>log_attrs</EM> vector must have one LogAttr for each position in 
///< <EM>text</EM>; if text contains N characters, it has N+1 positions, including
///< the last position at the end of the text. text should be an entire paragraph;
///< logical attributes can't be computed without context (for example you need to
///< see spaces on either side of a word to know the word is a word).

/// @}

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/break.inl>

#endif // XFC_PANGO_BREAK_HH

