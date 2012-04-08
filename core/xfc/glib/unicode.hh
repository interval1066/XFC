/*  XFC: Xfce Foundation Classes (Core Library)
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
 
/// @file xfc/glib/unicode.hh
/// @brief A C++ gunichar wrapper class.

#ifndef XFC_G_UNICODE_HH
#define XFC_G_UNICODE_HH

#ifndef XFC_INTEGER_OBJECT_HH
#include <xfc/integerobject.hh>
#endif

#ifndef __G_UNICODE_H__
#include <glib/gunicode.h>
#endif

namespace Xfc {

namespace G {

/// @class Unichar unicode.hh xfc/glib/unicode.hh
/// @brief A C++ gunichar wrapper class.
///
/// Unichar provides a convenient wrapper class for gunichar and its
/// associated functions.

class Unichar : public IntegerObject<gunichar>
{
public:
/// @name Constructors
/// @{

	Unichar();
	///< Constructs a null uncicode character.

	Unichar(gunichar c);
	///< Construct a new Unichar.
	///< @param c A gunichar (a type which can hold any UCS-4 character code).
 	
	Unichar(const Unichar& src);
	///< Copy constructor.
	/// @param src The source Unichar.

	Unichar& operator=(const Unichar& src);
	///< Assignment operator
	/// @param src The source Unichar.

/// @}
/// @name Accessors
/// @{

	bool is_alnum() const;
	///< Returns true if the character is alphanumeric.

	bool is_alpha() const;
	///< Returns true if the character is alphabetic (i.e. a letter).

	bool is_cntrl() const;
	///< Returns true if the character is a control character.

	bool is_digit() const;
	///< Returns true if the character is numeric (i.e. a digit).

	bool is_graph() const;
	///< Returns true if the character is printable; returns <EM>false</EM>
	///< for control characters, format characters, and spaces.

	bool is_lower() const;
	///< Returns true if the character is a lowercase letter.

	bool is_print() const;
	///< Returns true if the character is printable; returns <EM>true</EM> for spaces.

	bool is_punct() const;
	///< Returns true if the character is punctuation or a symbol.

	bool is_space() const;
	///< Returns true if the character is a space, tab, or line separator
	///< (newline, carriage return, etc.).
	///< Note: don't use this to do word breaking; you have to use Pango or equivalent
	///< to get word breaking right, the algorithm is fairly complex.

	bool is_upper() const;
	///< Returns true if the character is uppercase.

	bool is_xdigit() const;
	///< Returns true if the character is a hexidecimal digit.

	bool is_title() const;
	///< Returns true if the character is titlecase.
	///< Some characters in Unicode which are composites, such as the DZ digraph have three
	///< case variants instead of just two. The titlecase form is used at the beginning of
	///< a word where only the first letter is capitalized. The titlecase form of the DZ 
	///< digraph is U+01F2 LATIN CAPITAL LETTTER D WITH SMALL LETTER Z.

	bool is_defined() const;
	///< Returns true if the character is assigned in the Unicode standard.

	bool is_wide() const;
	///< Returns true if the character is typically rendered in a double-width cell.

	GUnicodeType type() const;
	///< Classifies a Unicode character by type.
	///< @return the type of the character.

	GUnicodeBreakType break_type() const;
	///< Determines the break type of the unicode character.
	///< The break type is used to find word and line breaks ("text boundaries").
	///< Pango implements the Unicode boundary resolution algorithms and normally
	///< you would use a function such as Pango::break() instead of caring about
	///< break types yourself.

/// @}
/// @name Methods
/// @{

	Unichar upper() const;
	///< Converts the character to uppercase.
	///< @return The result of converting the character to uppercase.
	///<
	///< If the character is not a lowercase or titlecase character, or has
	///< no upper case equivalent the character is returned unchanged.

	Unichar lower() const;
	///< Converts the character to lower case.
	///< @return The result of converting the character to lowercase.
	///<
	///< If the character is not an upperlower or titlecase character, or has
	///< no lower case equivalent the character is returned unchanged.

	Unichar title() const;
	///< Converts the character to the titlecase.
	///< @return The result of converting the character to titlecase.
	///<
	///< If the character is not an uppercase or lowercase character,
	///< the character is returned unchanged.

	int digit_value() const;
	///< Determines the numeric value of the character as a decimal digit.
	///< @return If the character is a decimal digit (according to is_digit()),
	///< its numeric value; otherwise, -1.

	int xdigit_value() const;
	///< Determines the numeric value of the character as a hexidecimal digit.
	///< @return If the character is a hexidecimal digit (according to is_xdigit()),
	///< its numeric value; otherwise, -1.

	bool validate() const;
	///< Checks whether the character is a valid Unicode character.
	///< @return <EM>true</EM> if the character is a valid Unicode character.
	///<
	///< Some possible integer values of the character will not be valid. 0 is
	///< considered a valid character, though it's normally a string terminator.

	bool get_mirror_char(Unichar *mirrored_ch = 0);
	///< Gets the mirrored character for this character, if there is one.
	///< @param @mirrored_ch The location to store the mirrored character.
	///< @return <EM>true</EM> if this character has a mirrored character and
	///< <EM>mirrored_ch</EM> is filled in, <EM>false</EM> otherwise.
	///<
	///< In Unicode, some characters are <EM>mirrored</EM>. This means that
	///< their images are mirrored horizontally in text that is laid out from
	///< right to left. For instance, "(" would become its mirror image, ")",
	///< in right-to-left text.
	///<
	///< If this character has the Unicode mirrored property and there is another
	///< unicode character that typically has a glyph that is the mirror image
	///< this character's glyph, that character is put at the address pointed to
	///< by <EM>mirrored_ch</EM>.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/unicode.inl>

#endif // XFC_G_UNICODE_HH









