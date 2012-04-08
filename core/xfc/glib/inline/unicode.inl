/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  unicode.inl - G::Unichar inline functions
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

inline bool
Xfc::G::Unichar::is_alnum() const
{
	return g_unichar_isalnum(value_);
}

inline bool
Xfc::G::Unichar::is_alpha() const
{
	return g_unichar_isalpha(value_);
}

inline bool
Xfc::G::Unichar::is_cntrl() const
{
	return g_unichar_iscntrl(value_);
}

inline bool
Xfc::G::Unichar::is_digit() const
{
	return g_unichar_isdigit(value_);
}

inline bool
Xfc::G::Unichar::is_graph() const
{
	return g_unichar_isgraph(value_);
}

inline bool
Xfc::G::Unichar::is_lower() const
{
	return g_unichar_islower(value_);
}

inline bool
Xfc::G::Unichar::is_print() const
{
	return g_unichar_isprint(value_);
}

inline bool
Xfc::G::Unichar::is_punct() const
{
	return g_unichar_ispunct(value_);
}

inline bool
Xfc::G::Unichar::is_space() const
{
	return g_unichar_isspace(value_);
}

inline bool
Xfc::G::Unichar::is_upper() const
{
	return g_unichar_isupper(value_);
}

inline bool
Xfc::G::Unichar::is_xdigit() const
{
	return g_unichar_isxdigit(value_);
}

inline bool
Xfc::G::Unichar::is_title() const
{
	return g_unichar_istitle(value_);
}

inline bool
Xfc::G::Unichar::is_defined() const
{
	return g_unichar_isdefined(value_);
}

inline bool
Xfc::G::Unichar::is_wide() const
{
	return g_unichar_iswide(value_);
}

inline GUnicodeType
Xfc::G::Unichar::type() const
{
	return g_unichar_type(value_);
}

inline GUnicodeBreakType
Xfc::G::Unichar::break_type() const
{
	return g_unichar_break_type(value_);
}

inline Xfc::G::Unichar
Xfc::G::Unichar::upper() const
{
	return g_unichar_toupper(value_);
}

inline Xfc::G::Unichar
Xfc::G::Unichar::lower() const
{
	return g_unichar_tolower(value_);
}

inline Xfc::G::Unichar
Xfc::G::Unichar::title() const
{
	return g_unichar_totitle(value_);
}

inline int
Xfc::G::Unichar::digit_value() const
{
	return g_unichar_digit_value(value_);
}

inline int
Xfc::G::Unichar::xdigit_value() const
{
	return g_unichar_xdigit_value(value_);
}

inline bool
Xfc::G::Unichar::validate() const
{
	return g_unichar_validate(value_);
}

