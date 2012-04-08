/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  pattern.cc - A C++ interface for GPatternSpec.
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

#include "pattern.hh"

using namespace Xfc;

/*  G::PatternSpec
 */

G::PatternSpec::PatternSpec(const char *pattern)
: pspec_(g_pattern_spec_new(pattern))
{
}

G::PatternSpec::PatternSpec(const String& pattern)
: pspec_(g_pattern_spec_new(pattern.c_str()))
{
}

G::PatternSpec::~PatternSpec()
{
	if (pspec_)
	{
		g_pattern_spec_free(pspec_);
		pspec_ = 0;
	}
}

bool
G::PatternSpec::equal(const PatternSpec& other) const
{
	return g_pattern_spec_equal(pspec_, other.g_pattern_spec());
}

bool
G::PatternSpec::operator==(const PatternSpec& other) const
{
	return equal(other);
}

bool
G::PatternSpec::operator!=(const PatternSpec& other) const
{
	return !equal(other);
}

bool
G::PatternSpec::match(const String& string)
{
	return g_pattern_match(pspec_, string.size(), string.c_str(), 0);
}

bool
G::PatternSpec::match(const String& string, const String& string_reversed)
{
	return g_pattern_match(pspec_, string.size(), string.c_str(), string_reversed.c_str());
}

bool
G::PatternSpec::match_simple(const char *pattern, const String& string)
{
	return g_pattern_match_simple(pattern, string.c_str());
}

bool
G::PatternSpec::match_simple(const String& pattern, const String& string)
{
	return g_pattern_match_simple(pattern.c_str(), string.c_str());
}

