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
 
/// @file xfc/utfstring.hh
/// @brief UTF-8 string class interface.
///
/// Provides a UTF-8 standard string compatible string class with its own forward
/// and reverse string iterators that know how to count UTF-8 characters.

#ifndef XFC_UTF_STRING_HH
#define XFC_UTF_STRING_HH

#ifndef XFC_G_UNICODE_HH
#include <xfc/glib/unicode.hh>
#endif

#ifndef _CPP_STRING
#include <string>
#endif

#ifndef _CPP_IOSFWD
#include <iosfwd>
#endif

namespace Xfc {

namespace G {
class Error;
}

/// @class StringIterator utfstring.hh xfc/utfstring.hh
/// @brief UTF-8 string iterator base class.

class StringIterator
{
	StringIterator(const StringIterator&);
	StringIterator& operator=(const StringIterator&);

protected:
	char* pos_;
	///< The first byte of the UTF-8 character the iterator currently points to.

	StringIterator();
	///< Default constructor.

	StringIterator(const char *pos);
	///< Construct a new iterator that points to pos.
	///< @param pos The first byte of the UTF-8 character the new iterator is to points to.

public:
	G::Unichar operator*() const;
	///< Dereference operator.
	///< @return The UTF-8 character pointed to, as a G::Unichar character (unicode).

	const char* base() const { return pos_;	}
	///< Returns a pointer to the first byte of the UTF-8 character pointed to.
};

/// @class Forward_StringIterator utfstring.hh xfc/utfstring.hh
/// @brief A const non-random access iterator that iterates over a String in the forward direction.

class Forward_StringIterator : public StringIterator
{
public:
/// @name Construcors
/// @{

	Forward_StringIterator();
	///< Default constructor.

	Forward_StringIterator(const char *pos);
	///< Construct a new iterator that points to pos.
	///< @param pos The first byte of the UTF-8 character the new iterator is to points to.

	Forward_StringIterator(const Forward_StringIterator& src);
	///< Copy constructor.
	///< @param src The Forward_StringIterator instance to copy.

	Forward_StringIterator& operator=(const Forward_StringIterator& src);
	///< Assignment operator.
	///< @param src The Forward_StringIterator whose value is to be copied and assigned to this iterator.

/// @}
/// @name Iterate in the forward direction
/// @{

	Forward_StringIterator& operator++();
	///< Prefix increment operator.
	///< Moves the iterator so that it points to the next UTF-8 character.

	Forward_StringIterator operator++(int);
	///< Postfix increment operator.
	///< Moves the iterator so that it points to the next UTF-8 character.

/// @}
/// @name Iterate in the reverse direction
/// @{

	Forward_StringIterator& operator--();
	///< Prefix decrement operator.
	///< Moves the iterator so that it points to the previous UTF-8 character.

	Forward_StringIterator operator--(int);
	///< Postfix decrement operator.
	///< Moves the iterator so that it points to the previous UTF-8 character.
	
/// @}
};

/// @class Reverse_StringIterator utfstring.hh xfc/utfstring.hh
/// @brief A const non-random access iterator that iterates over a String in the reverse direction.

class Reverse_StringIterator : public StringIterator
{
public:
/// @name Construcors
/// @{

	Reverse_StringIterator();
	///< Default constructor.

	Reverse_StringIterator(const char *pos);
	///< Construct a new iterator that points to pos.
	///< @param pos The first byte of the UTF-8 character the new iterator is to points to.

	Reverse_StringIterator(const Reverse_StringIterator& src);
	///< Copy constructor.
	///< @param src The Reverse_StringIterator instance to copy.

	Reverse_StringIterator& operator=(const Reverse_StringIterator& src);
	///< Assignment operator.
	///< @param src The Reverse_StringIterator whose value is to be copied and assigned to this iterator.

/// @}
/// @name Iterate in the forward direction
/// @{

	Reverse_StringIterator& operator++();
	///< Prefix increment operator.
	///< Moves the iterator so that it points to the next UTF-8 character.

	Reverse_StringIterator operator++(int);
	///< Postfix increment operator.
	///< Moves the iterator so that it points to the next UTF-8 character.

/// @}
/// @name Iterate in the reverse direction
/// @{

	Reverse_StringIterator& operator--();
	///< Prefix decrement operator.
	///< Moves the iterator so that it points to the previous UTF-8 character.

	Reverse_StringIterator operator--(int);
	///< Postfix decrement operator.
	///< Moves the iterator so that it points to the previous UTF-8 character.
	
/// @}
};

/// @class String utfstring.hh xfc/utfstring.hh
/// @brief A UTF-8 standard string compatible string class.
///
/// String is a custom UTF-8 string class that provides standard string interoperability.
/// It is implemented using a standard string as an internal byte array but uses its own
/// iterators, Forward_StringIterator and Reverse_StringIterator. To keep the syntax
/// consistent with standard string the String class typedefs these iterators as iterator
/// and revervse_iterator respectively. The const prefix has been omitted since there are
/// no non-const iterators. String presents an interface similar to standard string but
/// with extra method wrappers for GLIB's UTF-8 functions. One important difference are
/// the values returned length() and size(). The <EM>length</EM> is the number of UTF-8
/// characters in the string whereas the <EM>size</EM> is the number of bytes occupied by
/// <EM>length</EM> characters. Remember, in UTF-8 strings characters can span multiple
/// bytes.

class String
{
	std::string string_;
	mutable bool is_null;

public:
	static const size_t npos = static_cast<size_t>(-1);
	///< npos is an unsigned type that is used to mean 'all of the elements'.
	
	typedef const char* const_pointer;
	///< A constant pointer to a byte within the string.

	typedef Forward_StringIterator iterator;
	///< The forward iterator; points to the first byte of a UTF-8 character.

	typedef Reverse_StringIterator reverse_iterator;
	///< The reverse iterator; points to the first byte of a UTF-8 character.

/// @name Constructors
/// @{

	String();
	///< Creates an empty string.
	///< Creates an empty String with no characters. This string can be represented
	///< as "" and is therefore never <EM>null</EM>.

	String(const String& str);
	///< Copy constructor.
	///< @param str A String containing valid UTF-8 characters.
	///<
	///< Create a new String from <EM>str</EM>. This String is never <EM>null</EM>.

	String(const String& str, size_t char_pos, size_t n_chars = npos);
	///< Creates a string that is a substring of <EM>str</EM>.
	///< @param str A String containing valid UTF-8 characters.
	///< @param char_pos The starting character position.
	///< @param n_chars The maximum number of UTF-8 characters to read.
	///<
	///< Create a new String that is a substring of <EM>str</EM>. The substring
	///< begins at <EM>char_pos</EM> and contains at most <EM>n_chars</EM> characters.
	///< If n_chars is <EM>npos</EM> the substring contains all the remaining characters
	///< in <EM>str</EM>. This String is never <EM>null</EM>.

	String(const std::string& str);
	///< Creates a string that is a copy of the standard string <EM>str</EM>.
	///< @param str A standard string containing valid UTF-8 characters.
	///<
	///< Create a new String from <EM>str</EM>. This String is never <EM>null</EM>.

	String(const std::string& str, size_t n_chars);
	///< Creates a string that is a substring of the standard string <EM>str</EM>.
	///< @param str A standard string containing valid UTF-8 characters.
	///< @param n_chars The maximum number of UTF-8 characters to read.
	///<
	///< Create a new String that is a substring of <EM>str</EM>. The substring
	///< contains at most <EM>n_chars</EM> characters. If n_chars is <EM>npos</EM>
	///< the substring  contains all the characters in <EM>str</EM>. This String
	///< is never <EM>null</EM>.
	
	String(const char *s, size_t n_chars);
	///< Creates a string that is a substring of the characters in array <EM>s</EM>.
	///< @param s A UTF-8 character string.
	///< @param n_chars The maximum number of UTF-8 characters to read.
	///<
	///< Create a new String whose contents is <EM>n_chars</EM> characters pointed to
	///< by <EM>s</EM>, a UTF-8 character string. If <EM>n_chars</EM> is <EM>npos</EM> the
	///< string contains all the characters pointed to by <EM>s</EM>. This String is never
	///< <EM>null</EM>.

	String(const char *s);
	///< Creates a string that is a copy of the characters in array <EM>s</EM>.
	///< @param s A UTF-8 character string.
	///<
	///< Create a new String whose contents is equal to the array of UTF-8 characters
	///< pointed to by <EM>s</EM>. If <EM>s</EM> is a null, then the new String will be null
	///< and the null() method will return <EM>true</EM>. Calling c_str() on a null String
	///< will return a null pointer, whereas calling c_str() on an empty String will return
	///< a pointer to a character string whose only character is set to null (i.e. ""). This
	///< is the only constructor that creates a <EM>null</EM> String. The concept of a null
	///< String exists so that a C string, whose value may or may not be null, can be used
	///< to initialize a new String, preserving its null state. Then, when you pass c_str()
	///< to a C function, a null pointer is passed if the String is null, not a pointer to an
	///< empty string.

	String(size_t n, char c);
	///< Creates a string with n copies of the ascii character <EM>c</EM>.
	///< @param n The number of copies of character c.
	///< @param c An ASCII character.
	///<
	///< Create a new String with <EM>n</EM> copies of the ASCII character <EM>c</EM>.
	///< This String is never <EM>null</EM>.

	String(size_t n, gunichar c);
	///< Creates a string with n copies of the unicode character <EM>c</EM>.
	///< @param n The number of copies of character c.
	///< @param c A UCS-4 unicode character.
	///<
	///< Create a new String with <EM>n</EM> copies of the unicode character <EM>c</EM>.
	///< This String is never <EM>null</EM>.

	String(const gunichar *s, int n_chars, G::Error *error = 0);
	///< Creates a string that is a substring of the unicode string <EM>s</EM>.
	///< @param s A UCS-4 unicode character string.
	///< @param n_chars The maximum number of UCS-4 unicode characters to read.
	///< @param error return location for an allocated G::Error, or null to ignore errors.
	///< 
	///< Create a new String that is a substring of the UCS-4 unicode character string
	///< <EM>s</EM>. The substring contains at most <EM>n_chars</EM> unicode characters
	///< converted to UTF-8 characters. If n_chars is <EM>npos</EM> the substring contains
	///< all the characters in <EM>s</EM>. This String is never <EM>null</EM>.

	String(iterator first, iterator last);
	///< Creates a string with the characters in the range+ <EM>first</EM> to <EM>last</EM>.
	///< @param first An iterator pointing to the first byte of a UTF-8 character.
	///< @param last An iterator pointing to the first byte of a UTF-8 character.
	///<
	///< Create a new String by reading all the characters in the range <EM>first</EM> to
	///< <EM>last</EM>. This String is never <EM>null</EM>.

/// @}
/// @name Accessors
/// @{

	const char* data() const { return string_.data(); }
	///< Returns a constant pointer to the internal std::string data; this may or may not be null terminated.

	G::Unichar get_char(size_t char_pos) const;
	///< Converts the UTF-8 byte sequence at <EM>char_pos</EM> to a unicode character.
	///< @param char_pos The character position.
	///< @return A unicode character or (gunichar)-1 if the unicode character is invalid.

	G::Unichar get_char_validated(size_t char_pos, size_t n_bytes = npos) const;
	///< Converts the UTF-8 byte sequence at <EM>p</EM> to a unicode character.
	///< @param char_pos The character position.
	///< @param n_bytes The maximum number of bytes to read, or npos, for no maximum.
	///< @return A unicode character.
	///<
	///<  This method checks for incomplete and invalid characters. It returns (gunichar)-2
	///< if the character at <EM>char_pos</EM> contains a partial byte sequence that could
	///< begin a valid character. It returns gunichar(-1) if the character at <EM>char_pos</EM>
	///< does not contain a valid UTF-8 encoded unicode character.

	size_t index(size_t char_pos) const;
	///< Converts the character offset <EM>char_pos</EM> to a integer byte index.
	///< @param char_pos The character offset.
	///< @return The integer byte index corresponding to <EM>char_pos</EM>.

	size_t offset(const_pointer p) const;
	///< Converts a constant pointer to a position within the string to a integer character offset.
	///< @param p A constant pointer to a byte position within the string.
	///< @return the integer character offset.

	const_pointer pointer(size_t char_pos) const;
	///< Converts an integer character offset to a constant pointer to a position within the string.
	///< @param char_pos The integer character offset.
	///< @return A constant pointer to a byte position within the string.

	size_t length() const;
	///< Returns the length of the string in characters.
	///< For a string containing ASCII characters, the <EM>length</EM> of the string will be the
	///< same as the <EM>size</EM> of the string. For other UTF-8 characters it will be less.

	size_t size() const { return string_.size(); }
	///< Returns the size of the string in bytes.
	///< For a string containing ASCII characters, the <EM>size</EM> of the string will be the
	///< same as the <EM>length</EM> of the string. For other UTF-8 characters it will be greater.

	size_t max_size() const { return string_.max_size(); }
	///< Returns the maximum possible size of the string in bytes.

	size_t capacity() const { return string_.capacity(); }
	///< Returns the largest number of bytes the string can hold without reallocation.

	bool empty() const { return string_.empty(); }
	///< Returns true if the string is empty.

	bool null() const { return is_null ? (is_null = size() == 0) : false; }
	///< Returns true if the String is empty and was initialized with a null pointer.

	const char* c_str() const { return null() ? (char*)0 : string_.c_str(); }
	///< Returns a null pointer if null() is true; otherwise it returns a pointer to the internal character string.

	const std::string& str() const { return string_; }
	///< Returns a const reference to the internal std::string.
	///< This method can be used to pass a String to a function expecting a standard string.

	G::Unichar at(size_t char_pos) const;
	///< Calls get_char_validated() to return the character at <EM>char_pos</EM> as unicode character.
	///< @param char_pos The integer character offset.
	///< @return The unicode character at <EM>char_pos</EM>.

	G::Unichar operator[](size_t char_pos) const;
	///< Calls get_char() to return the character at <EM>char_pos</EM> as unicode character.
	///< @param char_pos The integer character offset.
	///< @return The unicode character at <EM>char_pos</EM>.

/// @}
/// @name Accessors
/// @{

	static G::Unichar get_char(const_pointer p);
	///< Converts the UTF-8 byte sequence at <EM>p</EM> to a unicode character.
	///< @param p A constant pointer to a UTF-8 byte sequence.
	///< @return A unicode character or (gunichar)-1 if the unicode character is invalid.

	static G::Unichar get_char_validated(const_pointer p, size_t n_bytes);
	///< Converts the UTF-8 byte sequence at <EM>p</EM> to a unicode character.
	///< @param p A constant pointer to a UTF-8 byte sequence.
	///< @param n_bytes The maximum number of bytes to read, or npos, for no maximum.
	///< @return A unicode character.
	///<
	///<  This method checks for incomplete and invalid characters. It returns (gunichar)-2
	///< if the character at <EM>char_pos</EM> contains a partial byte sequence that could
	///< begin a valid character. It returns gunichar(-1) if the character at <EM>char_pos</EM>
	///< does not contain a valid UTF-8 encoded unicode character.

/// @}
/// @name Forward iterators
/// @{

	iterator begin() const;
	///< Returns an iterator that points to the first byte in the string.

	iterator end() const;
	///< Returns an iterator that points to one past the last byte in the string, usually the null terminator.

/// @}
/// @name Reverse iterators
/// @{

	reverse_iterator rbegin() const;
	///< Returns an iterator that points to the first byte in the reverse string.

	reverse_iterator rend() const;
	///< Returns an iterator that points to last byte in the reverse string.

/// @}
/// @name Append characters to the end of the string
/// @{

	String& append(const String& str);
	///< Append the characters in str to the end of the string.

	String& append(const String& str, size_t char_pos, size_t n_chars = npos);
	///< Starting at char_pos in str, append n_chars number of characters to the end of the string.

	String& append(const char *s, size_t n_chars);
	///< Append n_chars number of characters from array s to the end of the string.

	String& append(const char *s);
	///< Append the characters is array s to the end of the string.

	String& append(size_t n, char c);
	///< Append the ascii character c to the end of the string n times.

	String& append(size_t n, gunichar c);
	///< Convert the unicode character c to UTF-8 and append it to the string n times.

	String& append(const gunichar *s, int n_chars, G::Error *error = 0);
	///< Convert n_chars number of unicode characters from array s to UTF-8 and append
	///< them to the end of the string; if n_chars is -1 then s is null-terminated.

	String& append(iterator first, iterator last);
	///< Append the UTF-8 characters in the range first to last to the end of the string.

	void push_back(char c);
	///< Append the ascii character c to the end of the string.

	void push_back(gunichar c);
	///< Convert the unicode character c to UTF-8 and append it to the string.

	String& operator+=(const String& str);
	///< Append the characters in str to the end of the string.

	String& operator+=(const char *s);
	///< Append the characters in array s to the end of the string.

	String& operator+=(char c);
	///< Append the ascii character c to the end of the string.

	String& operator+=(gunichar c);
	///< Convert the unicode character c to UTF-8 and append it to the string.

	String& operator+=(const gunichar *s);
	///< Convert unicode characters in array s to UTF-8 and append them to the end of
	///< the string; the string is assumed to be null terminated.

/// @}
/// @name Assign a new value to the string
/// @{

	String& assign(const String& str);
	///< Replace all the characters in the string with the characters in str.

	String& assign(const String& str, size_t char_pos, size_t n_chars = npos);
	///< Starting at char_pos in str, Replace all the characters in the string with n_chars number of characters.

	String& assign(const char *s, size_t n_chars);
	///< Replace all the characters in the string with n_chars number of characters from array s.

	String& assign(const char *s);
	///< Replace all the characters in the string with the characters is array s.

	String& assign(size_t n, char c);
	///< Replace all the characters in the string with the ascii character c, n times.

	String& assign(size_t n, gunichar c);
	///< Convert the unicode character c to UTF-8 and replace all the characters in the string with it n times.

	String& assign(const gunichar *s, int n_chars, G::Error *error = 0);
	///< Convert n_chars number of unicode characters from array s to UTF-8 and assign them to the string;
	///< if n_chars is -1 then s is null-terminated.

	String& assign(iterator first, iterator last);
	///< Replace all the characters in the string with the UTF-8 characters in the range first to last.

	String& operator=(const String& str);
	///< Replace all the characters in the string with the characters in str.

	String& operator=(const char *s);
	///< Replace all the characters in the string with the characters is array s.

	String& operator=(char c);
	///< Replace all the characters in the string with the ascii character c.

	String& operator=(gunichar c);
	///< Convert the unicode character c to UTF-8 and assign it to the string.

/// @}
/// @name Compare two strings
/// The compare methods return 0 it the two strings are the same, a negative number if 
/// this string is lexicographically before the comparison string and a positive number
/// otherwise.
/// @{

	int compare(const String& str) const;
	///< Compare the contents of the string with str.

	int compare(size_t char_pos, size_t n_chars, const String& str) const;
	///< Starting at char_pos in the string, compare n_chars number of characters in the string with str.

	int compare(size_t char_pos1, size_t n_chars1, const String& str, size_t char_pos2, size_t n_chars2) const;
	///< Starting at char_pos1 in the string and char_pos2 in str, compare n_chars1 number of characters
	///< in the string with n_chars2 number of characters in str.

	int compare(const char *s) const;
	///< Compare the contents of the string with the characters in the array s.

	int compare(size_t char_pos, size_t n_chars, const char *s) const;
	///< Starting at char_pos in the string, compare n_chars number of characters in the string with
	///< the characters in array s.

	int compare(size_t char_pos, size_t n_chars1, const char *s, size_t n_chars2) const;
	///< Starting at char_pos in the string, compare n_chars1 number of characters in the string
	///< with n_chars2 number of characters in the array s.

/// @}
/// @name Copy the contents of the string into a buffer.
/// The copy methods return the number of bytes copied into the buffer.
/// @{

	size_t copy(char *s, size_t n_chars, size_t char_pos) const;
	///< Starting at char_pos in the string, copy n_chars characters into buffer s.

	size_t copy(char *s, size_t n_chars) const;
	///< Starting at the beginning of the string, copy n_chars characters into buffer s.

	size_t copy(gunichar **s, size_t n_bytes, iterator i, G::Error *error = 0) const;
	///< Starting at the position in the string pointed by i, convert n_bytes to UCS-4 characters
	///< and copy them into a new buffer pointed to by s; this buffer must be freed with g_free().

	size_t copy(gunichar2 **s, size_t n_bytes, iterator i, G::Error *error = 0) const;
	///< Starting at the position in the string pointed by i, convert n_bytes to UTF-16 characters
	///< and copy them into a new buffer pointed to by s; this buffer must be freed with g_free().

/// @}
/// @name Erase characters from the string
/// The iterator returned by the erase methods points to the character one past the last character removed.
/// @{

	String& erase();
	///< Remove all the characters from the string.

	String& erase(size_t char_pos, size_t n_chars = npos);
	///< Starting at char_pos, remove n_chars number of characters from the string.

	iterator erase(iterator i);
	///< Remove the character pointed to by i from the string.

	iterator erase(iterator first, iterator last);
	///< Remove the characters in the range first to last from the string.

/// @}
/// @name Format a new value for the string
/// @{

	static String format(const char *message_format, ...);
	///< Convenience method that does sprintf-style string formatting.
	///< @param message_format The format string (see the printf() documentation).
	///< @param ... A variable list of arguments to insert in the output.
	///< @returns A String that holds the formatted output.
	///<
	///< <B>Example:</B> Formatting a string.
	///< @code
	///< String str = String::format("This is a %s string.", "formatted");
	///< @endcode

/// @}
/// @name Insert characters into the string
/// @{

	void insert(iterator i, size_t n, char c);
	///< Starting at the position in the string pointed to by i, insert the ascii character c n times.

	void insert(iterator i, size_t n, gunichar c);
	///< Starting at the position in the string pointed to by i, convert the unicode character c to UTF-8
	///< and insert it n times.

	void insert(iterator i, iterator first, iterator last);
	///< Insert the characters in the range first to last at the position in the string pointed to by i.

	String& insert(size_t char_pos, const String& str);
	///< Insert str into the string at char_pos.

	String& insert(size_t char_pos1, const String& str, size_t char_pos2, size_t n_chars = npos);
	///< Starting at char_pos2 in str, insert n_chars number of characters from str into the string at char_pos1.

	String& insert(size_t char_pos, const char *s, size_t n_chars);
	///< Insert n_chars number of characters in array s into the string at char_pos.

	String& insert(size_t char_pos, const char *s);
	///< Insert the characters in array s into the string at char_pos.

	String& insert(size_t char_pos, size_t n, char c);
	///< Starting at char_pos in the string, insert the ascii character c n times.

	String& insert(size_t char_pos, size_t n, gunichar c);
	///< Starting char_pos in the string, convert the unicode character c to UTF-8 and insert it n times.

	String& insert(size_t char_pos, const gunichar *s, int n_chars, G::Error *error = 0);
	///< Convert n_chars number of unicode characters from array s to UTF-8 and insert them into the string
	///< at char_pos; if n_chars is -1 then s is null-terminated.

	String& insert(size_t char_pos, gunichar c);
	///< Convert the unicode character c to UTF-8 and insert it into the string at char_pos.

	iterator insert(iterator i, char c);
	///< Insert the ascii character c into the string at the position pointed to by i.

	iterator insert(iterator i, gunichar c);
	///< Convert the unicode character c to UTF-8 and insert it into the string at the position pointed to by i.

/// @}
/// @name Replace characters in the string
/// @{

	String& replace(size_t char_pos, size_t n_chars, const String& str);
	///< Starting at char_pos in the string, replace n_chars number of characters with str.

	String& replace(size_t char_pos1, size_t n_chars1, const String& str, size_t char_pos2, size_t n_chars2 = npos);
	///< Starting at char_pos1 in the string and char_pos2 in str, replace n_chars1 number of characters
	///< in the string with n_chars2 number of characters from str.

	String& replace(size_t char_pos, size_t n_chars1, const char *s, size_t n_chars2);
	///< Starting at char_pos in the string, replace n_chars1 number of characters in the string
	///< with n_chars2 number of characters in array s.

	String& replace(size_t char_pos, size_t n_chars, const char *s);
	///< Starting at char_pos in the string, replace n_chars number of characters with the characters
	///< in array s.

	String& replace(size_t char_pos, size_t n_chars, size_t n, char c);
	///< Starting at char_pos in the string, replace n_chars number of characters with n copies of the
	///< ascii character c.

	String& replace(size_t char_pos, size_t n_chars, size_t n, gunichar c);
	///< Starting at char_pos in the string, replace n_chars number of characters with n copies of the
	///< unicode character c coverted to UTF-8.

	String& replace(size_t char_pos, size_t n_chars, gunichar c);
	///< Starting at char_pos in the string, replace n_chars number of characters with the unicode
	///< character c coverted to UTF-8.

	String& replace(size_t char_pos, size_t n_chars1, const gunichar *s, int n_chars2, G::Error *error = 0);
	///< Starting at char_pos in the string, replace n_chars1 number of characters with n_chars2 number 
	///< of characters in unicode array s converted to UTF-8; if n_chars2 is -1	then s is null-terminated.

	String& replace(iterator first, iterator last, const String& str);
	///< Replace the characters in the string in the range first to last with str.

	String& replace(iterator first, iterator last, const char *s, size_t n_chars);
	///< Replace the characters in the string in the range first to last with n_chars characters in array s.

	String& replace(iterator first, iterator last, const char *s);
	///< Replace the characters in the string in the range first to last with the characters in array s.

	String& replace(iterator first, iterator last, size_t n, char c);
	///< Replace the characters in the string in the range first to last with n copies of the ascii characters c.

	String& replace(iterator first, iterator last, gunichar c);
	///< Replace the characters in the string in the range first to last with the unicode character c
	///< converted to UTF-8.

	String& replace(iterator first1, iterator last1, iterator first2, iterator last2);
	///< Replace the characters in the string in the range first1 to last1 with the characters 
	///< in another string in the range first2 to last2.

/// @}
/// @name Resize the string
/// @{

	void resize(size_t n_bytes);
	///< Resize the string to hold n_bytes extra.

	void reserve(size_t n_bytes = 0);
	///< Reserve n_bytes to be allocated at the next reallocation;

	void clear();
	///< Erase all the characters in the string.

/// @}
/// @name Search the string for a subsequence
/// The find methods search the string for a subsequence and if successful return the byte index
/// of the first occurrence found, otherwise npos is returned.
/// @{

	size_t find(const char *s, size_t byte_pos, size_t n_chars) const;
	///< Starting at byte_pos in the string, search n_chars number of characters for the first occurrence of s.

	size_t find(const String& str, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first occurrence of str.

	size_t find(const char *s, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first occurrence of s.

	size_t find(char c, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first occurrence of the ascii character c.

	size_t find(gunichar c, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first occurrence of the unicode character c.

	size_t rfind(const String& str, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first occurrence str.

	size_t rfind(const char *s, size_t byte_pos, size_t n_chars) const;
	///< Starting at byte_pos in the string, search backwards n_chars number of characters for 
	///< the first occurrence of s.

	size_t rfind(const char *s, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search bacwards for the first occurrence of s.

	size_t rfind(char c, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first occurrence of the ascii character c.

	size_t rfind(gunichar c, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first occurrence of the unicode character c.

	size_t find_first_of(const String& str, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first occurrence of any character in str.

	size_t find_first_of(const char *s, size_t byte_pos, size_t n_chars) const;
	///< Starting at byte_pos in the string, search n_chars number of characters for the first occurrence
	///< of any character in s.

	size_t find_first_of(const char *s, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first occurrence of any character in s.

	size_t find_first_of(char c, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first character matching the ascii character c.

	size_t find_first_of(gunichar c, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first character matching the unicode character c.

	size_t find_last_of(const String& str, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first occurrence of any character in str.

	size_t find_last_of(const char *s, size_t byte_pos, size_t n_chars) const;
	///< Starting at byte_pos in the string, search backwards n_chars number of characters for the first
	///< occurrence of any character in s.

	size_t find_last_of(const char *s, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first occurrence of any character in s.

	size_t find_last_of(char c, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first character matching
	///< the ascii character c.

	size_t find_last_of(gunichar c, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first character matching
	///< the unicode character c.

	size_t find_first_not_of(const String& str, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first occurrence of any character not in str.

	size_t find_first_not_of(const char *s, size_t byte_pos, size_t n_chars) const;
	///< Starting at byte_pos in the string, search n_chars number of characters for the first occurrence
	///< of any character not in s.

	size_t find_first_not_of(const char *s, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first occurrence of any character not in s.

	size_t find_first_not_of(char c, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first character not matching the ascii character c.

	size_t find_first_not_of(gunichar c, size_t byte_pos = 0) const;
	///< Starting at byte_pos in the string, search for the first character not matching the unicode character c.

	size_t find_last_not_of(const String& str, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first occurrence of any character not in str.

	size_t find_last_not_of(const char *s, size_t byte_pos, size_t n_chars) const;
	///< Starting at byte_pos in the string, search backwards n_chars number of characters for the first
	///< occurrence of any character not in s.

	size_t find_last_not_of(const char *s, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first occurrence of any character not in s.

	size_t find_last_not_of(char c, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first character not matching
	///< the ascii character c.

	size_t find_last_not_of(gunichar c, size_t byte_pos = npos) const;
	///< Starting at byte_pos in the string, search backwards for the first character not matching
	///< the unicode character c.

/// @}
/// @name Select a substring
/// @{

	String substr(size_t char_pos = 0, size_t n_chars = npos) const;
	///< Starting at char_pos, return n_chars number of characters as a new string.

/// @}
/// @name Swap strings
/// @{

	void swap(String& str);
	///< Swap the contents of the string with the contents of str.

/// @}
/// @name Case conversion
/// @{

	String upper();
	///< Convert all the characters in the string to upper case.

	String upper(size_t char_pos, size_t n_bytes = npos);
	///< Starting at char_pos, convert n_bytes in the string to upper case.

	String lower();
	///< Convert all the characters in the string to lower case.

	String lower(size_t char_pos, size_t n_bytes = npos);
	///< Starting at char_pos, convert n_bytes in the string to lower case.

	String casefold(size_t n_bytes = npos);
	///< Converts a string into a form that is independent of case.
	///< @param n_bytes The length in bytes, or npos for the entire string.
	///< @return A new string, that is a case independent form of the string.
	///<
	///< The result will not correspond to any particular case, but can be compared for equality
	///< or ordered with the results of calling casefold() on other strings. Note that calling casefold()
	///< followed by collate() is only an approximation to the correct linguistic case insensitive 
	///< ordering, though it is a fairly good one. Getting this exactly right would require a more 
	///< sophisticated collation function that takes case sensitivity into account. Currently, such a
	///< function is not provided.

/// @}
/// @name UTF-8 methods
/// @{

	String normalize(GNormalizeMode mode, size_t n_bytes = npos);
	///< Converts a string into canonical form.
	///< @param mode The type of normalization to perform.
	///< @param n_bytes The length in bytes, or npos for the entire string.
	///< @return A new string, that is the normalized form of the string.
	///<
	///< Converts a string into canonical form, standardizing such issues as whether a character
	///< with an accent is represented as a base character and combining accent or as a single precomposed
	///< character. You should generally call normalize() before comparing two Unicode strings. The 
	///< normalization mode G_NORMALIZE_DEFAULT only standardizes differences that do not affect the text
	///< content, such as the above-mentioned accent representation. G_NORMALIZE_ALL also standardizes the
	///< "compatibility" characters in Unicode, such as SUPERSCRIPT THREE to the standard forms (in this 
	///< case DIGIT THREE). Formatting information may be lost but for most text operations such characters
	///< should be considered the same. For example, collate() normalizes with G_NORMALIZE_ALL as its first
	///< step. G_NORMALIZE_DEFAULT_COMPOSE and G_NORMALIZE_ALL_COMPOSE are like G_NORMALIZE_DEFAULT and
	///< G_NORMALIZE_ALL, but returned a result with composed forms rather than a maximally decomposed form.
	///< This is often useful if you intend to convert the string to a legacy encoding or pass it to a 
	///< system with less capable Unicode handling.
	
	int collate(const String& str);
	///< Compare the string and str for ordering using the linguistically correct rules for the current locale.
	///< @param str A UTF-8 encoded string.
	///< @return -1 if the string compares before str, 0 if they compare equal, 1 if string compares after str.
	///<
	///< When sorting a large number of strings, it will be significantly faster to comapre them with
	///< collate_key() when sorting.

	int collate_key(const String& str, size_t n_bytes = npos);
	///< Converts the string and str into collation keys and compares them using strcmp().
	///< @param str A UTF-8 encoded string.
	///< @param n_bytes The length in bytes, or npos for the entire string.
	///< @return -1 if the string compares before str, 0 if they compare equal, 1 if string compares after str.
	///<
	///< The results of comparing the two strings with collate_key will always be the same as comparing
	///< the two strings with collate().

	std::string convert(const char *to_codeset, G::Error *error = 0);
	///< Converts the string from UTF-8 to another character set.
	///< @param to_codeset The character set to convert the string to.
	///< @param error The location to store any error, or null to ignore errors.
	///< @return The converted string if successful, otherwise an empty string and error will be set.
	///<
	///< Any of the errors in GConvertError may occur.

	std::string convert_with_fallback(const char *to_codeset, G::Error *error = 0);
	///< Converts the string from UTF-8 to another character set, possibly including
	///< fallback sequences for characters not representable in the output.
	///< @param to_codeset The character set of convert the string to.
	///< @param error The location to store any error, or null to ignore errors.
	///< @return The converted string if successful, otherwise an empty string and error will be set.
	///<
	///< This method uses a default fallback string in place of a character not present
	///< in the target encoding. Characters not in the target encoding are represented as
	///< Unicode escapes \\x{XXXX} or \\x{XXXXXX}. Note that it is not guaranteed that the
	///< specification for the fallback sequences will be honored. Some systems may do an
	///< approximate conversion from <EM>from_codeset</EM> to UTF-8 in their iconv() functions,
	///< in which case GLib will simply return that approximate conversion.
	///<
	///< Any of the errors in GConvertError may occur.

	std::string convert_with_fallback(const char *to_codeset, const char *fallback, G::Error *error = 0);
	///< Converts the string from UTF-8 to another character set, possibly including
	///< fallback sequences for characters not representable in the output.
	///< @param to_codeset The character set of convert the string to.
	///< @param fallback A UTF-8 string to use in place of a character not present in the target encoding.
	///< @param error The location to store any error, or null to ignore errors.
	///< @return The converted string if successful, otherwise an empty string and error will be set.
	///<
	///< The <EM>fallback</EM> string must be in the target encoding. Characters not
	///< in the target encoding are represented as Unicode escapes \\x{XXXX} or \\x{XXXXXX}.
	///< Note that it is not guaranteed that the specification for the fallback sequences
	///< will be honored. Some systems may do an approximate conversion from <EM>from_codeset</EM>
	///< to UTF-8 in their iconv() functions, in which case GLib will simply return that
	///< approximate conversion.
	///<
	///< Any of the errors in GConvertError may occur.

	std::string to_locale(G::Error *error = 0) const;
	///< Converts the string from UTF-8 to the encoding used by the C runtime for the current locale.
	///< @param error Location to store the error occuring, or null to ignore errors.
	///< @return The converted string.
	///<
	///< Any of the errors in GConvertError may occur.

	std::string to_filename(G::Error *error = 0) const;
	///< Converts a string from UTF-8 to the encoding used for filenames.
	///< @param error Location to store the error occuring, or null to ignore errors.
	///< @return The converted string.
	///<
	///< Any of the errors in GConvertError may occur.

/// @}
/// @name UTF-8 filename conversion methods
/// @{

	static String from_locale(const std::string& opsysstring, G::Error *error = 0);
	///< Convert the opsysstring from the current locale's encoding used by the C runtime into a UTF-8 string.
	///< @param opsysstring A string in the encoding of the current locale.
	///< @param error Location to store the error occuring, or null to ignore errors.
	///< @return The converted String.
	///<
	///< Any of the errors in GConvertError may occur.

	static String from_filename(const std::string& opsysstring, G::Error *error = 0);
	///< Converts a string from the encoding used for filenames into a UTF-8 string.
	///< @param opsysstring A string in the encoding for filenames.
	///< @param error Location to store the error occuring, or null to ignore errors.
	///< @return The converted String.
	///<
	///< Any of the errors in GConvertError may occur.

/// @}
/// @name UTF-8 character set conversion methods
/// @{

	static String convert(const std::string& str, const char *from_codeset, G::Error *error = 0);
	///< Converts a string from one character set to UTF-8.
	///< @param str The string to convert.
	///< @param from_codeset The character set of <EM>str</EM>.
	///< @param error The location to store any error, or null to ignore errors.
	///< @return The converted String if successful, otherwise a null string and error will be set.
	///<
	///< Any of the errors in GConvertError may occur.

	static String convert_with_fallback(const std::string& str, const char *from_codeset, G::Error *error = 0);
	///< Converts a string from one character set to UTF-8, possibly including
	///< fallback sequences for characters not representable in the output.
	///< @param str The string to convert.
	///< @param from_codeset The character set of <EM>str</EM>.
	///< @param error The location to store any error, or null to ignore errors.
	///< @return The converted String if successful, otherwise a null string and error will be set.
	///<
	///< This method uses a default fallback string in place of a character not present
	///< in the target encoding. Characters not in the target encoding are represented as
	///< Unicode escapes \\x{XXXX} or \\x{XXXXXX}. Note that it is not guaranteed that the
	///< specification for the fallback sequences will be honored. Some systems may do an
	///< approximate conversion from <EM>from_codeset</EM> to UTF-8 in their iconv() functions,
	///< in which case GLib will simply return that approximate conversion.
	///<
	///< Any of the errors in GConvertError may occur.

	static String convert_with_fallback(const std::string& str, const char *from_codeset, const char *fallback, G::Error *error = 0);
	///< Converts a string from one character set to UTF-8, possibly including
	///< fallback sequences for characters not representable in the output.
	///< @param str The string to convert.
	///< @param from_codeset The character set of <EM>str</EM>.
	///< @param fallback A UTF-8 string to use in place of a character not present in the target encoding
	///< @param error The location to store any error, or null to ignore errors.
	///< @return The converted String if successful, otherwise a null string and error will be set.
	///<
	///< The <EM>fallback</EM> string must be in the target encoding. Characters not
	///< in the target encoding are represented as Unicode escapes \\x{XXXX} or \\x{XXXXXX}.
	///< Note that it is not guaranteed that the specification for the fallback sequences
	///< will be honored. Some systems may do an approximate conversion from <EM>from_codeset</EM>
	///< to UTF-8 in their iconv() functions, in which case GLib will simply return that
	///< approximate conversion.
	///<
	///< Any of the errors in GConvertError may occur.

/// @}
/// @name Validate the characters in the string.
/// @{

	bool validate(size_t& byte_pos) const;
	///< Validates UTF-8 encoded text.
	///< @param byte_pos The location to store the byte index of the first invalid byte.
	///< @return <EM>true</EM> if all of str was valid.
	///<
	///< Many routines require valid UTF-8 as input; so data read from a file or the network
	///< should be checked with validate() before doing anything else with it.

	bool validate(const_pointer *end = 0) const;
	///< Validates UTF-8 encoded text.
	///< @param end On returning points to the first invalid byte or the end of the string.
	///< @return <EM>true</EM> if all of str was valid.
	///<
	///< Many routines require valid UTF-8 as input; so data read from a file or the network
	///< should be checked with validate() before doing anything else with it.
	
/// @}
};

/// @name String i/o stream operators
/// @{

std::istream& operator>>(std::istream& is, String& str);
///< Read a whitespace-terminated word from an istream to the string str.

std::ostream& operator<<(std::ostream& os, const String& str);
///< Write the string str to an ostream.

/// @}
/// @name StringIterator comparison operators
/// @{

inline bool
operator==(const StringIterator& lhs, const StringIterator& rhs)
{
	return lhs.base() == rhs.base();
}
///< Returns true if the string iterators lhs and rhs point to the same character.

inline bool
operator!=(const StringIterator& lhs, const StringIterator& rhs)
{
	return !(lhs == rhs);
}
///< Returns true if the string iterators lhs and rhs do not point to the same character.

inline bool
operator<(const StringIterator& lhs, const StringIterator& rhs)
{
	return lhs.base() < rhs.base();
}
///< Returns true if lhs points to a character in a string that is before the character pointed to by rhs.

inline bool
operator>(const StringIterator& lhs, const StringIterator& rhs)
{
	return rhs < lhs;
}
///< Returns true if lhs points to a character in a string that is after the character pointed to by rhs.

inline bool
operator<=(const StringIterator& lhs, const StringIterator& rhs)
{
	return !(rhs < lhs);
}
///< Returns true if lhs points to a character in a string that is before the character or is the same
///< character pointed to by rhs.

inline bool
operator>=(const StringIterator& lhs, const StringIterator& rhs)
{
	return !(lhs < rhs);
}
///< Returns true if lhs points to a character in a string that is the same character or after the
///< character pointed to by rhs.

/// @}
/// @name String concatenation operators
/// @{

inline String
operator+(const String& lhs, const String& rhs)
{
	String str(lhs);
	str.append(rhs);
	return str;
}
///< Append the string rhs to the end of the string lhs and return the result as a new String.

inline String 
operator+(const char *lhs, const String& rhs)
{
	String str(lhs);
	str.append(rhs);
	return str;
}
///< Append the string rhs to the end of the character array lhs and return the result as a new String.

inline String
operator+(char c, const String& rhs)
{
	String str(1, c);
	str.append(rhs);
	return str;
}
///< Append the string rhs to the character c and return the result as a new String.

inline String 
operator+(const String& lhs, const char *rhs)
{
	String str(lhs);
	str.append(rhs);
	return str;
}
///< Append the character array rhs to the end of the string lhs and return the result as a new String.

inline String 
operator+(const String& lhs, char c)
{
	String str(lhs);
	str.append(1, c);
	return str;
}
///< Append the character c to the end of the string lhs and return the result as a new String.

/// @}
/// @name String comparison operators
/// @{

inline bool 
operator==(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) == 0;
}
///< Returns true if the string lhs and the string rhs are characterwise equal.

inline bool 
operator==(const char *lhs, const String& rhs)
{
	return rhs.compare(lhs) == 0;
}
///< Returns true if the character array lhs and the string rhs are characterwise equal.

inline bool 
operator==(const String& lhs, const char *rhs)
{
	return lhs.compare(rhs) == 0;
}
///< Returns true if the string lhs and the character array rhs are characterwise equal.

inline bool
operator!= (const char *lhs, const String& rhs)
{
	return rhs.compare(lhs) != 0;
}
///< Returns true if the character array lhs and the string rhs are not characterwise equal.

inline bool 
operator!=(const String& lhs, const char *rhs)
{
	return lhs.compare(rhs) != 0;
}
///< Returns true if the string lhs and the character array rhs are not characterwise equal.

inline bool 
operator<(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) < 0;
}
///< Returns true if the string lhs is lexicographically before the string rhs.

inline bool 
operator<(const char *lhs, const String& rhs)
{
	return rhs.compare(lhs) > 0;
}
///< Returns true if the character array lhs is lexicographically before the string rhs.

inline bool 
operator<(const String& lhs, const char *rhs)
{
	return lhs.compare (rhs) < 0;
}
///< Returns true if the string lhs is lexicographically before the character array rhs.

inline bool 
operator>(const char *lhs, const String& rhs)
{
	return rhs.compare (lhs) < 0;
}
///< Returns true if the character array lhs is lexicographically greater the string rhs.

inline bool 
operator>(const String& lhs, const char *rhs)
{
	return lhs.compare(rhs) > 0;
}
///< Returns true if the string lhs is lexicographically greater the character array rhs.

inline bool 
operator<=(const char *lhs, const String& rhs)
{
	return rhs.compare(lhs) >= 0;
}
///< Returns true if the character array lhs is lexicographically before or equal to the string rhs.

inline bool 
operator<=(const String& lhs, const char *rhs)
{
	return lhs.compare(rhs) <= 0;
}
///< Returns true if the string lhs is lexicographically before or equal to the character array rhs.

inline bool 
operator>=(const char *lhs, const String& rhs)
{
	return rhs.compare(lhs) <= 0;
}
///< Returns true if the character array lhs is lexicographically greater or equal to the string rhs.

inline bool 
operator>=(const String& lhs, const char *rhs)
{
	return lhs.compare(rhs) >= 0;
}
///< Returns true if the string lhs is lexicographically greater or equal to the character array rhs.

inline bool 
operator!=(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) != 0;
}
///< Returns true if the string lhs and the string rhs are not characterwise equal.

inline bool 
operator>(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) > 0;
}
///< Returns true if the string lhs is lexicographically greater the string rhs.

inline bool 
operator<=(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) <= 0;
}
///< Returns true if the string lhs is lexicographically before or equal to the string rhs.

inline bool 
operator>=(const String& lhs, const String& rhs)
{
	return lhs.compare(rhs) >= 0;
}
///< Returns true if the string lhs is lexicographically greater or equal to the string rhs.

/// @}

} // namespace Xfc

#endif // XFC_UTF_STRING_HH

