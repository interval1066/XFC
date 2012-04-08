/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  utfstring.cc - Standard string compatible UTF-8 string implementation
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
 
#include "utfstring.hh"
#include "glib/error.hh"
#include <glib/gconvert.h>
#include <glib/gmem.h>
#include <glib/gstrfuncs.h>
#include <iostream>
#include <cstring>

#define std_iterator(i) (std::string::iterator(const_cast<char*>(i.base())))

using namespace Xfc;

/*  StringIterator
 */

StringIterator::StringIterator()
: pos_(0)
{
}

StringIterator::StringIterator(const char *pos)
: pos_(const_cast<char*>(pos))
{
}

G::Unichar
StringIterator::operator*() const
{
	return g_utf8_get_char_validated(pos_, -1);
}

/*  Forward_StringIterator
 */

Forward_StringIterator::Forward_StringIterator()
{
}

Forward_StringIterator::Forward_StringIterator(const char *pos)
: StringIterator(pos)
{
}

Forward_StringIterator::Forward_StringIterator(const Forward_StringIterator& src)
: StringIterator(src.pos_)
{
}

Forward_StringIterator&
Forward_StringIterator::operator=(const Forward_StringIterator& src)
{
	pos_ = src.pos_;
	return *this;
}

Forward_StringIterator&
Forward_StringIterator::operator++()
{
	pos_ = g_utf8_next_char(pos_);
	return *this;
}

Forward_StringIterator
Forward_StringIterator::operator++(int)
{
	return Forward_StringIterator(g_utf8_next_char(pos_));
}

Forward_StringIterator&
Forward_StringIterator::operator--()
{
	pos_ = g_utf8_prev_char(pos_);
	return *this;
}

Forward_StringIterator
Forward_StringIterator::operator--(int)
{
	return Forward_StringIterator(g_utf8_prev_char(pos_));
}

/*  Reverse_StringIterator
 */

Reverse_StringIterator::Reverse_StringIterator()
{
}

Reverse_StringIterator::Reverse_StringIterator(const char *pos)
: StringIterator(pos)
{
}

Reverse_StringIterator::Reverse_StringIterator(const Reverse_StringIterator& src)
: StringIterator(src.pos_)
{
}

Reverse_StringIterator&
Reverse_StringIterator::operator=(const Reverse_StringIterator& src)
{
	pos_ = src.pos_;
	return *this;
}

Reverse_StringIterator&
Reverse_StringIterator::operator++()
{
	pos_ = g_utf8_prev_char(pos_);
	return *this;
}

Reverse_StringIterator
Reverse_StringIterator::operator++(int)
{
	return Reverse_StringIterator(g_utf8_prev_char(pos_));
}

Reverse_StringIterator&
Reverse_StringIterator::operator--()
{
	pos_ = g_utf8_next_char(pos_);
	return *this;
}

Reverse_StringIterator
Reverse_StringIterator::operator--(int)
{
	return Reverse_StringIterator(g_utf8_next_char(pos_));
}

/*  String
 */

namespace {

size_t bytes(const char *s, size_t n_chars)
{
	if (n_chars == String::npos)
		return strlen(s);

	const char *p = s;
	while (n_chars && *p)
	{
		p = g_utf8_next_char(p);
		n_chars--;
	}
	return p - s;
}

} // namespace

String::String()
: string_(), is_null(false)
{
}

String::String(const String& str)
: string_(str.string_), is_null(str.is_null)
{
}

String::String(const String& str, size_t char_pos, size_t n_chars)
: string_(str.string_, index(char_pos), bytes(str.data(), n_chars)), is_null(false)
{
}

String::String(const std::string& str)
: string_(str), is_null(false)
{
}

String::String(const std::string& str, size_t n_chars)
: string_(str, bytes(str.data(), n_chars)), is_null(false)
{
}

String::String(const char *s, size_t n_chars)
: string_(s, bytes(s, n_chars)), is_null(false)
{
}

String::String(const char *s)
: string_(), is_null(s == 0)
{
	assign(is_null ? "" : s);
}

String::String(size_t n, char c)
: string_(n, c), is_null(false)
{
}

String::String(size_t n, gunichar c)
: string_(), is_null(false)
{
	assign(n, c);
}

String::String(const gunichar *s, int n_chars, G::Error *error)
: string_(), is_null(false)
{
	assign(s, n_chars, error);
}

String::String(iterator first, iterator last)
: string_(first.base(), last.base()), is_null(false)
{
}

// Accessors

G::Unichar
String::get_char(size_t char_pos) const
{
	return get_char(pointer(char_pos));
}

G::Unichar
String::get_char(const_pointer p)
{
	return g_utf8_get_char(p);
}

G::Unichar
String::get_char_validated(size_t char_pos, size_t n_bytes) const
{
	return get_char_validated(pointer(char_pos), n_bytes);
}

G::Unichar
String::get_char_validated(const_pointer p, size_t n_bytes)
{
	return g_utf8_get_char_validated(p, (gssize)n_bytes);
}

size_t
String::index(size_t char_pos) const
{
	if (char_pos == npos)
		return size();

	return char_pos ? (pointer(char_pos) - data()) : 0;
}

size_t
String::offset(const_pointer p) const
{
	return g_utf8_pointer_to_offset(data(), p);
}

String::const_pointer
String::pointer(size_t char_pos) const
{
	return g_utf8_offset_to_pointer(data(), (glong)char_pos);
}

size_t
String::length() const
{
	return g_utf8_strlen(data(), (gssize)size());
}

G::Unichar
String::at(size_t char_pos) const
{
	return get_char_validated(pointer(char_pos), npos);
}

G::Unichar
String::operator[](size_t char_pos) const
{
	return get_char(pointer(char_pos));
}

// Forward iterators

String::iterator
String::begin() const
{
	return data();
}

String::iterator
String::end() const
{
	return data() + size();
}

// Reverse iterators

String::reverse_iterator
String::rbegin() const
{
	return data() + size();
}

String::reverse_iterator
String::rend() const
{
	return data();
}

// Append

String&
String::append(const String& str)
{
	string_.append(str.string_);
	return *this;
}

String&
String::append(const String& str, size_t char_pos, size_t n_chars)
{
	string_.append(str.string_, index(char_pos), bytes(str.c_str(), n_chars));
	return *this;
}

String&
String::append(const char *s, size_t n_chars)
{
	string_.append(s, bytes(s, n_chars));
	return *this;
}

String&
String::append(const char *s)
{
	string_.append(s);
	return *this;
}

String&
String::append(size_t n, char c)
{
	string_.append(n, c);
	return *this;
}

String&
String::append(size_t n, gunichar c)
{
	size_t i = 0;
	while (i < n)
	{
		replace(npos, 0, c);
		i++;
	}
	return *this;
}

String&
String::append(const gunichar *s, int n_chars, G::Error *error)
{
	return replace(npos, 0, s, n_chars, error);
}

String&
String::append(iterator first, iterator last)
{
	string_.replace(string_.end(), string_.end(), first.base(), last.base());
	return *this;
}

void
String::push_back(char c)
{
	append(1, c);
}

void
String::push_back(gunichar c)
{
	append(1, c);
}

String&
String::operator+=(const String& str)
{
	return append(str);
}

String&
String::operator+=(const char *s)
{
	return append(s);
}

String&
String::operator+=(char c)
{
	return append(1, c);
}

String&
String::operator+=(gunichar c)
{
	return append(1, c);
}

String&
String::operator+=(const gunichar *s)
{
	return append(s, -1, 0);
}

// Assign

String&
String::assign(const String& str)
{
	string_.assign(str.string_);
	return *this;
}

String&
String::assign(const String& str, size_t char_pos, size_t n_chars)
{
	string_.assign(str.string_, index(char_pos), bytes(str.c_str(), n_chars));
	return *this;
}

String&
String::assign(const char *s, size_t n_chars)
{
	string_.assign(s, bytes(s, n_chars));
	return *this;
}

String&
String::assign(const char *s)
{
	string_.assign(s);
	return *this;
}

String&
String::assign(size_t n, char c)
{
	string_.assign(n, c);
	return *this;
}

String&
String::assign(size_t n, gunichar c)
{
	size_t i = 0;
	while (i < n)
	{
		replace(i, npos, c);
		i++;
	}
	return *this;
}

String&
String::assign(const gunichar *s, int n_chars, G::Error *error)
{
	return replace(0, npos, s, n_chars, error);
}

String&
String::assign(iterator first, iterator last)
{
	string_.replace(string_.begin(), string_.end(), first.base(), last.base());
	return *this;
}

String&
String::operator=(const String& str)
{
	return assign(str);
}

String&
String::operator=(const char *s)
{
	is_null = s == 0;
	return assign(is_null ? "" : s);
}

String&
String::operator=(char c)
{
	return assign(1, c);
}

String&
String::operator=(gunichar c)
{
	return assign(1, c);
}

// Compare

int
String::compare(const String& str) const
{
	return string_.compare(str.string_);
}

int
String::compare(size_t char_pos, size_t n_chars, const String& str) const
{
	return std::string(string_, index(char_pos), bytes(str.c_str(), n_chars)).compare(str.string_);
}

int
String::compare(size_t char_pos1, size_t n_chars1, const String& str, size_t char_pos2, size_t n_chars2) const
{
	std::string s1(string_, index(char_pos1), bytes(str.c_str(), n_chars1));
	std::string s2(str.string_, index(char_pos2), bytes(str.c_str(), n_chars2));
	return s1.compare(s2);
}

int
String::compare(const char *s) const
{
	return string_.compare(s);
}

int
String::compare(size_t char_pos, size_t n_chars, const char *s) const
{
	return std::string(string_, index(char_pos), bytes(s, n_chars)).compare(s);
}

int
String::compare(size_t char_pos, size_t n_chars1, const char *s, size_t n_chars2) const
{
	std::string s1(string_, index(char_pos), bytes(s, n_chars1));
	std::string s2(s, bytes(s, n_chars2));
	return s1.compare(s2);
}

// Copy

size_t
String::copy(char *s, size_t n_chars, size_t char_pos) const
{
	return string_.copy(s, bytes(c_str(), n_chars), index(char_pos));
}

size_t
String::copy(char *s, size_t n_chars) const
{
	return string_.copy(s, bytes(c_str(), n_chars), 0);
}

size_t
String::copy(gunichar **s, size_t n_bytes, iterator i, G::Error *error) const
{
	glong n_chars = 0;
	*s = error ? g_utf8_to_ucs4(i.base(), (glong)n_bytes, 0, &n_chars, *error)
	           : g_utf8_to_ucs4_fast(i.base(), (glong)n_bytes, &n_chars);
	return n_chars;
}

size_t
String::copy(gunichar2 **s, size_t n_bytes, iterator i, G::Error *error) const
{
	glong n_chars = 0;
	*s = g_utf8_to_utf16(i.base(), (glong)n_bytes, 0, &n_chars, *error);
	return (size_t)n_chars;
}

// Erase

String&
String::erase()
{
	string_.erase();
	return *this;
}

String&
String::erase(size_t char_pos, size_t n_chars)
{
	string_.erase(index(char_pos), bytes(c_str(), n_chars));
	return *this;
}

String::iterator
String::erase(iterator i)
{
	return erase(i, ++i);
}

String::iterator
String::erase(iterator first, iterator last)
{
	size_t pos = first.base() - data();
	string_.erase(pos, last.base() - first.base());
	return data() + pos;
}

// Formatting methods
String
String::format(const char *message_format, ...)
{
	va_list args;
	va_start(args, message_format);
	char* msg = g_strdup_vprintf(message_format, args);
	va_end(args);
	String s(msg);
	g_free(msg);
	return s;
}

// Insert

void
String::insert(iterator i, size_t n, char c)
{
	string_.insert(std_iterator(i), n, c);
}

void
String::insert(iterator i, size_t n, gunichar c)
{
	string_.insert(std_iterator(i) - string_.begin(), String(n, c).string_);
}

void
String::insert(iterator i, iterator first, iterator last)
{
	string_.insert(std_iterator(i), first.base(), last.base());
}

String&
String::insert(size_t char_pos, const String& str)
{
	string_.insert(index(char_pos), str.string_);
	return *this;
}

String&
String::insert(size_t char_pos1, const String& str, size_t char_pos2, size_t n_chars)
{
	string_.insert(index(char_pos1), str.string_, index(char_pos2), bytes(str.c_str(), n_chars));
	return *this;
}

String&
String::insert(size_t char_pos, const char *s, size_t n_chars)
{
	return replace(char_pos, 0, s, n_chars);
}

String&
String::insert(size_t char_pos, const char *s)
{
	return replace(char_pos, 0, s);
}

String&
String::insert(size_t char_pos, size_t n, char c)
{
	return replace(char_pos, 0, n, c);
}

String&
String::insert(size_t char_pos, size_t n, gunichar c)
{
	string_.insert(index(char_pos), String(n, c).string_);
	return *this;
}

String&
String::insert(size_t char_pos, const gunichar *s, int n_chars, G::Error *error)
{
	return replace(char_pos, 0, s, n_chars, error);
}

String&
String::insert(size_t char_pos, gunichar c)
{
	return replace(char_pos, 0, c);
}

String::iterator
String::insert(iterator i, char c)
{
	size_t pos = i.base() - data();
	insert(pos, 1, c);
	return data() + pos;
}

String::iterator
String::insert(iterator i, gunichar c)
{
	size_t pos = i.base() - data();
	insert(pos, String(1, c).string_);
	return data() + pos;
}

// Replace

String&
String::replace(size_t char_pos, size_t n_chars, const String& str)
{
	string_.replace(index(char_pos), bytes(c_str(), n_chars), str.string_);
	return *this;
}

String&
String::replace(size_t char_pos1, size_t n_chars1, const String& str, size_t char_pos2, size_t n_chars2)
{
	string_.replace(index(char_pos1), bytes(c_str(), n_chars1), str.string_, index(char_pos2), bytes(str.c_str(), n_chars2));
	return *this;
}

String&
String::replace(size_t char_pos, size_t n_chars1, const char *s, size_t n_chars2)
{
	string_.replace(index(char_pos), bytes(c_str(), n_chars1), s, bytes(s, n_chars2));
	return *this;
}

String&
String::replace(size_t char_pos, size_t n_chars, const char *s)
{
	string_.replace(index(char_pos), bytes(c_str(), n_chars), s);
	return *this;
}

String&
String::replace(size_t char_pos, size_t n_chars, size_t n, char c)
{
	string_.replace(index(char_pos), bytes(c_str(), n_chars), n, c);
	return *this;
}

String&
String::replace(size_t char_pos, size_t n_chars, gunichar c)
{
	char out[6];
	int n_bytes = g_unichar_to_utf8(c, out);
	string_.replace(index(char_pos), bytes(c_str(), n_chars), out, n_bytes);
	return *this;
}

String&
String::replace(size_t char_pos, size_t n_chars1, const gunichar *s, int n_chars2, G::Error *error)
{
	glong n_bytes = 0;
	char *p = g_ucs4_to_utf8(s, (glong)n_chars2, 0, &n_bytes, *error);
	string_.replace(index(char_pos), bytes(c_str(), n_chars1), p, n_bytes);
	g_free(p);
	return *this;
}

String&
String::replace(iterator first, iterator last, const String& str)
{
	string_.replace(std_iterator(first), std_iterator(last), str.string_);
	return *this;
}

String&
String::replace(iterator first, iterator last, const char *s, size_t n_chars)
{
	string_.replace(std_iterator(first), std_iterator(last), s, bytes(s, n_chars));
	return *this;
}

String&
String::replace(iterator first, iterator last, const char *s)
{
	string_.replace(std_iterator(first), std_iterator(last), s);
	return *this;
}

String&
String::replace(iterator first, iterator last, size_t n, char c)
{
	string_.replace(std_iterator(first), std_iterator(last), n, c);
	return *this;
}

String&
String::replace(iterator first, iterator last, gunichar c)
{
	char out[6];
	int n_bytes = g_unichar_to_utf8(c, out);
	string_.replace(std_iterator(first), std_iterator(last), out, n_bytes);
	return *this;
}

String&
String::replace(iterator first1, iterator last1, iterator first2, iterator last2)
{
	string_.replace(std_iterator(first1), std_iterator(last1), first2.base(), last2.base());
	return *this;
}

// Resize
void
String::resize(size_t n_bytes)
{
	string_.resize(n_bytes);
}

void
String::reserve(size_t n_bytes)
{
	string_.reserve(n_bytes);
}

void
String::clear()
{
	string_.clear();
}

// Search

size_t
String::find(const char *s, size_t byte_pos, size_t n_chars) const
{
	return string_.find(s, byte_pos, bytes(s, n_chars));
}

size_t
String::find(const String& str, size_t byte_pos) const
{
	return string_.find(str.string_, byte_pos);
}

size_t
String::find(const char *s, size_t byte_pos) const
{
	return string_.find(s, byte_pos);
}

size_t
String::find(char c, size_t byte_pos) const
{
	return string_.find(c, byte_pos);
}

size_t
String::find(gunichar c, size_t byte_pos) const
{
	char out[6];
	int n_bytes = g_unichar_to_utf8(c, out);
	return string_.find(out, byte_pos, n_bytes);
}

size_t
String::rfind(const String& str, size_t byte_pos) const
{
	return string_.rfind(str.string_, byte_pos);
}

size_t
String::rfind(const char *s, size_t byte_pos, size_t n_chars) const
{
	return string_.rfind(s, byte_pos, bytes(s, n_chars));
}

size_t
String::rfind(const char *s, size_t byte_pos) const
{
	return string_.rfind(s, byte_pos);
}

size_t
String::rfind(char c, size_t byte_pos) const
{
	return string_.rfind(c, byte_pos);
}

size_t
String::rfind(gunichar c, size_t byte_pos) const
{
	char out[6];
	int n_bytes = g_unichar_to_utf8(c, out);
	return string_.rfind(out, byte_pos, n_bytes);
}

size_t
String::find_first_of(const String& str, size_t byte_pos) const
{
	return string_.find_first_of(str.string_, byte_pos);
}

size_t
String::find_first_of(const char *s, size_t byte_pos, size_t n_chars) const
{
	return string_.find_first_of(s, byte_pos, bytes(s, n_chars));
}

size_t
String::find_first_of(const char *s, size_t byte_pos) const
{
	return string_.find_first_of(s, byte_pos);
}

size_t
String::find_first_of(char c, size_t byte_pos) const
{
	return string_.find_first_of(c, byte_pos);
}

size_t
String::find_first_of(gunichar c, size_t byte_pos) const
{
	char out[6];
	int n_bytes = g_unichar_to_utf8(c, out);
	return string_.find_first_of(out, byte_pos, n_bytes);
}

size_t
String::find_last_of(const String& str, size_t byte_pos) const
{
	return string_.find_last_of(str.string_, byte_pos);
}

size_t
String::find_last_of(const char *s, size_t byte_pos, size_t n_chars) const
{
	return string_.find_last_of(s, byte_pos, bytes(s, n_chars));
}

size_t
String::find_last_of(const char *s, size_t byte_pos) const
{
	return string_.find_last_of(s, byte_pos);
}

size_t
String::find_last_of(char c, size_t byte_pos) const
{
	return string_.find_last_of(c, byte_pos);
}

size_t
String::find_last_of(gunichar c, size_t byte_pos) const
{
	char out[6];
	int n_bytes = g_unichar_to_utf8(c, out);
	return string_.find_last_of(out, byte_pos, n_bytes);
}

size_t
String::find_first_not_of(const String& str, size_t byte_pos) const
{
	return string_.find_first_not_of(str.string_, byte_pos);
}

size_t
String::find_first_not_of(const char *s, size_t byte_pos, size_t n_chars) const
{
	return string_.find_first_not_of(s, byte_pos, bytes(s, n_chars));
}

size_t
String::find_first_not_of(const char *s, size_t byte_pos) const
{
	return string_.find_first_not_of(s, byte_pos);
}

size_t
String::find_first_not_of(char c, size_t byte_pos) const
{
	return string_.find_first_not_of(c, byte_pos);
}

size_t
String::find_first_not_of(gunichar c, size_t byte_pos) const
{
	char out[6];
	int n_bytes = g_unichar_to_utf8(c, out);
	return string_.find_first_not_of(out, byte_pos, n_bytes);
}

size_t
String::find_last_not_of(const String& str, size_t byte_pos) const
{
	return string_.find_last_not_of(str.string_, byte_pos);
}

size_t
String::find_last_not_of(const char *s, size_t byte_pos, size_t n_chars) const
{
	return string_.find_last_not_of(s, byte_pos, bytes(s, n_chars));
}

size_t
String::find_last_not_of(const char *s, size_t byte_pos) const
{
	return string_.find_last_not_of(s, byte_pos);
}

size_t
String::find_last_not_of(char c, size_t byte_pos) const
{
	return string_.find_last_not_of(c, byte_pos);
}

size_t
String::find_last_not_of(gunichar c, size_t byte_pos) const
{
	char out[6];
	int n_bytes = g_unichar_to_utf8(c, out);
	return string_.find_last_not_of(out, byte_pos, n_bytes);
}

// Substr

String
String::substr(size_t char_pos, size_t n_chars) const
{
	return string_.substr(index(char_pos), bytes(c_str(), n_chars));
}

// Swap

void
String::swap(String& str)
{
	string_.swap(str.string_);
}

// UTF-8 methods

String
String::upper()
{
	return upper(0);
}

String
String::upper(size_t char_pos, size_t n_bytes)
{
	char *p = g_utf8_strup(data() + char_pos, (gssize)(n_bytes == npos ? size() - char_pos : n_bytes));
	String str(p);
	g_free(p);
	return str;
}

String
String::lower()
{
	return lower(0);
}

String
String::lower(size_t char_pos, size_t n_bytes)
{
	char *p = g_utf8_strdown(data() + char_pos, (gssize)(n_bytes == npos ? size() - char_pos : n_bytes));
	String str(p);
	g_free(p);
	return str;
}

String
String::casefold(size_t n_bytes)
{
	char *p = g_utf8_casefold(data(), (gssize)(n_bytes ==npos ? size() : n_bytes));
	String str(p);
	g_free(p);
	return str;
}

String
String::normalize(GNormalizeMode mode, size_t n_bytes)
{
	char *p = g_utf8_normalize(data(), (gssize)(n_bytes==npos ? size() : n_bytes), mode);
	String str(p);
	g_free(p);
	return str;
}

int
String::collate(const String& str)
{
	return g_utf8_collate(data(), str.data());
}

int
String::collate_key(const String& str, size_t n_bytes)
{
	char *p1 = g_utf8_collate_key(data(), size());
	char *p2 = g_utf8_collate_key(str.data(), (gssize)(n_bytes == npos ? str.size() : n_bytes));
	int result = strcmp(p1, p2);
	g_free(p1);
	g_free(p2);
	return result;
}

std::string
String::convert(const char *to_codeset, G::Error *error)
{
	gsize bytes_written = 0;
	char *s = g_convert(data(), (gssize)size(), to_codeset, "UTF-8", 0, &bytes_written, *error);
	std::string tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

String
String::convert(const std::string& str, const char *from_codeset, G::Error *error)
{
	gsize bytes_written = 0;
	char *s = g_convert(str.c_str(), (gssize)str.size(), "UTF-8", from_codeset, 0, &bytes_written, *error);
	String tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

std::string
String::convert_with_fallback(const char *to_codeset, G::Error *error)
{
	gsize bytes_written = 0;
	char *s = g_convert_with_fallback(data(), (gssize)size(), to_codeset, "UTF-8", 0, 0, &bytes_written, *error);
	std::string tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

std::string
String::convert_with_fallback(const char *to_codeset, const char *fallback, G::Error *error)
{
	gsize bytes_written = 0;
	char *s = g_convert_with_fallback(data(), (gssize)size(), to_codeset, "UTF-8", const_cast<char*>(fallback), 0, &bytes_written, *error);
	std::string tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

String
String::convert_with_fallback(const std::string& str, const char *from_codeset, G::Error *error)
{
	gsize bytes_written = 0;
	char *s = g_convert_with_fallback(str.c_str(), (gssize)str.size(), "UTF-8", from_codeset, 0, 0, &bytes_written, *error);
	String tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

String
String::convert_with_fallback(const std::string& str, const char *from_codeset, const char *fallback, G::Error *error)
{
	gsize bytes_written = 0;
	char *s = g_convert_with_fallback(str.c_str(), (gssize)str.size(), "UTF-8", from_codeset, const_cast<char*>(fallback), 0, &bytes_written, *error);
	String tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

String
String::from_locale(const std::string& opsysstring, G::Error *error)
{
	gsize bytes_written = 0;
	char *s = g_locale_to_utf8(opsysstring.data(), (gssize)opsysstring.size(), 0, &bytes_written, *error);
	String tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

std::string
String::to_locale(G::Error *error) const
{
	gsize bytes_written = 0;
	char *s = g_locale_from_utf8(data(), (gssize)size(), 0, &bytes_written, *error);
	std::string tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

String
String::from_filename(const std::string& opsysstring, G::Error *error)
{
	gsize bytes_written = 0;
	char *s = g_filename_to_utf8(opsysstring.data(), (gssize)opsysstring.size(), 0, &bytes_written, *error);
	String tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

std::string
String::to_filename(G::Error *error) const
{
	gsize bytes_written = 0;
	char *s = g_filename_from_utf8(data(), (gssize)size(), 0, &bytes_written, *error);
	std::string tmp_str(s, bytes_written);
	g_free(s);
	return tmp_str;
}

// Validate

bool 
String::validate(size_t& byte_pos) const
{
	const char *end = 0;
	bool result = g_utf8_validate(data(), (gssize)size(), &end) != 0;
	if (end)
		byte_pos = end - data();
	return result;
}	

bool 
String::validate(const_pointer *end) const
{
	return g_utf8_validate(data(), (gssize)size(), end) != 0;
}	

/*  Standard stream i/o operators
 */

std::istream& 
Xfc::operator>>(std::istream& is, String& str)
{
	std::string tmp_str;
	is >> tmp_str;
	str = String::from_locale(tmp_str);
	return is;
}

std::ostream& 
Xfc::operator<<(std::ostream& os, const String& str)
{
	os << str.to_locale();
	return os;
}

