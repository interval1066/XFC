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

/// @file xfc/glib/pattern.hh
/// @brief A C++ interface for GPatternSpec.
///
/// Provides PatternSpec, an object that supports Glob-style pattern matching — matches
/// strings against patterns containing '*' (wildcard) and '?' (joker).

#ifndef XFC_G_PATTERN_HH
#define XFC_G_PATTERN_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __G_PATTERN_H__
#include <glib/gpattern.h>
#endif

namespace Xfc {

namespace G {

/// @class PatternSpec pattern.hh xfc/glib/pattern.hh
/// A GPatternSpec C++ wrapper interface.
///
/// A PatternSpec is the 'compiled' form of a pattern. Its match() and match_simple()
/// methods match a string against a pattern containing '*' and '?' wildcards with
/// similar semantics as the standard glob() function: '*' matches an arbitrary,
/// possibly empty, string, '?' matches an arbitrary character.
///
/// Note that in contrast to glob(), the '/' character can be matched by the wildcards,
/// there are no '[...]' character ranges and '*' and '?' can not be escaped to include
/// them literally in a pattern.
///
/// When multiple strings must be matched against the same pattern, it is better to compile
/// the pattern to a G::PatternSpec and use match() instead of match_simple(). This
/// avoids the overhead of repeated pattern compilation.

class PatternSpec : public Xfc::Object
{
	PatternSpec(const PatternSpec&);
	PatternSpec& operator=(const PatternSpec&);

	GPatternSpec *pspec_;

public:
/// @name Constructors
/// @{

	PatternSpec(const char *pattern);
	///< Constructs a PatternSpec, the compiled form of a pattern.
	///< @param pattern A zero-terminated UTF-8 encoded string.

	PatternSpec(const String& pattern);
	///< Constructs a PatternSpec, the compiled form of a pattern.
	///< @param pattern A UTF-8 encoded string.

	~PatternSpec();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GPatternSpec* g_pattern_spec() const;
	///< Get a pointer to the GPatternSpec object.

	operator GPatternSpec* () const;
	///< Conversion operator; Safely converts a G::PatternSpec object into a GPatternSpec pointer.

	bool equal(const PatternSpec& other) const;
	///< Compares this compiled pattern spec with <EM>other</EM> and returns
	///< whether they will match the same set of strings.
	///< @param other Another PatternSpec.
	///< @returns Whether the compiled patterns are equal.

	bool operator==(const PatternSpec& other) const;
	///< Equality operator; compares this compiled pattern spec with <EM>other</EM>
	///< and returns <EM>true</EM> if they will match the same set of strings.
	///< @param other Another PatternSpec.
	///< @returns Whether the compiled patterns are equal.

	bool operator!=(const PatternSpec& other) const;
	///< Inequality operator; compares this compiled pattern spec with <EM>other</EM>
	///< and returns <EM>true</EM> if they will not match the same set of strings.
	///< @param other Another PatternSpec.
	///< @returns Whether the compiled patterns are not equal.

/// @}
/// @name Methods
/// @{

	bool match(const String& string);
	///< Matches a string against a compiled pattern.
	///< @param string The UTF-8 encoded string to match.
	///< @return <EM>true</EM> if string matches this pattern.
	///<
	///< If the string is to be matched against more than one pattern,
	///< consider using this match() method instead while supplying the reversed
	///< string. See match(const String&, const String&) for details.

	bool match(const String& string, const String& string_reversed);
	///< Matches a string against a compiled pattern.
	///< @param string The UTF-8 encoded string to match.
	///< @param string_reversed The reverse of string or null.
	///< @return <EM>true</EM> if string matches this pattern.
	///<
	///< Note that, if the user code will (possibly) match a string against a multitude
	///< of patterns containing wildcards, chances are high that some patterns will require
	///< a reversed string. In this case, it's more efficient to provide the reversed string
	///< to avoid multiple constructions thereof in the various calls to match().
	///<
	///< Note also that the reverse of a UTF-8 encoded string can in general not be obtained
	///< by g_strreverse(). This works only if the string doesn't contain any multibyte
	///< characters. Glib doesn't currently offer a function to reverse UTF-8 encoded strings.

/// @}
/// @name Methods
/// @{
	static bool match_simple(const char *pattern, const String& string);
	static bool match_simple(const String& pattern, const String& string);
	///< Matches a string against a pattern given as a string.
	///< @param pattern The UTF-8 encoded pattern.
	///< @param string The UTF-8 encoded string to match.
	///< @return <EM>true</EM> if string matches pspec.
	///<
	///< If this function is to be called in a loop, it's more efficient to construct
	///< the pattern once as a PatternSpec and call match() repetitively.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/pattern.inl>

#endif // XFC_G_PATTERN_HH

