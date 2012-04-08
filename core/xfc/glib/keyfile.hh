/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2005 The XFC Development Team.
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

/// @file xfc/glib/keyfile.hh
/// @brief A C++ interface for the GKeyFile configuarion file parser.

#ifndef XFC_G_KEY_FILE_HH
#define XFC_G_KEY_FILE_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_KEY_FILE_H__
#include <glib/gkeyfile.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {

class Error;

/// @enum KeyFileError
/// Specifies the error codes returned by key file parsing.

enum KeyFileError
{
	KEY_FILE_ERROR_UNKNOWN_ENCODING = G_KEY_FILE_ERROR_UNKNOWN_ENCODING,
	///< The text being parsed was in an unknown encoding.
	
	KEY_FILE_ERROR_PARSE = G_KEY_FILE_ERROR_PARSE,
	///< The document was ill-formed.
	
	KEY_FILE_ERROR_NOT_FOUND = G_KEY_FILE_ERROR_NOT_FOUND,
	///< The file was not found.
	
	KEY_FILE_ERROR_KEY_NOT_FOUND = G_KEY_FILE_ERROR_KEY_NOT_FOUND,
	///< A requested key was not found.
	
	KEY_FILE_ERROR_GROUP_NOT_FOUND = G_KEY_FILE_ERROR_GROUP_NOT_FOUND,
	///< A requested group was not found.
	
	KEY_FILE_ERROR_INVALID_VALUE = G_KEY_FILE_ERROR_INVALID_VALUE
	///< A value could not be parsed.
};

/// @enum KeyFileFlags
/// Specifies the flags which influence the parsing.

enum KeyFileFlags
{
	KEY_FILE_NONE = G_KEY_FILE_NONE,
	///< No flags, default behaviour.
	
	KEY_FILE_KEEP_COMMENTS = G_KEY_FILE_KEEP_COMMENTS,
	///< Use this flag if you plan to write the (possibly modified) contents of the key file back
	///< to a file; otherwise all comments will be lost when the key file is written back. 

	KEY_FILE_KEEP_TRANSLATIONS = G_KEY_FILE_KEEP_TRANSLATIONS
	///< Use this flag if you plan to write the (possibly modified) contents of the key file back
	///< to a file; otherwise only the translations for the current language will be written back. 
};

/// G::KeyFileFlagsField holds one or more bit values from the G::KeyFileFlags enumeration.

typedef unsigned int KeyFileFlagsField;

/// @class KeyFile keyfile.hh xfc/glib/keyfile.hh
/// A C++ wrapper interface for the GKeyFile configuration file parser.
///
/// KeyFile lets you parse, edit or create files containing groups of key-value pairs, which we call
/// key files for lack of a better name. Several freedesktop.org specifications use key files now,
/// e.g the Desktop Entry Specification and the Icon Theme Specification. 
///
/// The syntax of key files is described in detail in the Desktop Entry Specification, here is a
/// quick summary: Key files consists of groups of key-value pairs, interspersed with comments.
///
/// @code
/// # this is just an example
/// # there can be comments before the first group
/// 
/// [First Group]
/// 
/// Name=Key File Example\tthis value shows\nescaping
/// 
/// # localized strings are stored in multiple key-value pairs
/// Welcome=Hello
/// Welcome[de]=Hallo
/// Welcome[fr]=Bonjour
/// Welcome[it]=Ciao
/// 
/// [Another Group]
/// 
/// Numbers=2;20;-200;0
/// 
/// Booleans=true;false;true;true
/// @endcode
///
/// Lines beginning with a '#' and blank lines are considered comments. 
///
/// Groups are started by a header line containing the group name enclosed in '[' and ']', 
/// and ended implicitly by the start of the next group or the end of the file. Each 
/// key-value pair must be contained in a group. 
///
/// Key-value pairs generally have the form key=value, with the exception of localized strings,
/// which have the form key[locale]=value. Space before and after the '=' character are ignored.
/// Newline, tab, carriage return and backslash characters are escaped as \\n, \\t, \\r, and \\\\, 
/// respectively. To preserve initial and final spaces, these can also be escaped as \\s. 
///
/// Key files can store strings (possibly with localized variants), integers, booleans and lists
/// of these. Lists are separated by a separator character, typically ';' or ','. To use the list
/// separator character in a value in a list, it has to be escaped by prefixing it with a backslash. 
///
/// This syntax is obviously inspired by the ini files commonly met on Windows, but there are 
/// some important differences: 
/// <ol>
///   <li>ini files use the ';' character to begin comments, key files use the '#' character.</li> 
///   <li>Key files allow only comments before the first group.</li> 
///   <li>Key files are always encoded in UTF-8.</li>
/// </ol>

class KeyFile : public Xfc::Object
{
	KeyFile(const KeyFile&);
	KeyFile& operator=(const KeyFile&);

	GKeyFile *keyfile_;

public:
/// @name Constructors
/// @{

	KeyFile();
	///< Construct an empty key file.

	~KeyFile();
	///< Destructor; Frees the memory allocated to the key file.

/// @}
/// @name Accessors
/// @{

	GKeyFile* g_key_file() const;
	///< Get a pointer to the GKeyFile object.

	operator GKeyFile* () const;
	///< Conversion operator; Safely converts a G::KeyFile object into a GKeyFile pointer.

	String get_start_group() const;
	///< Gets the name of the start group of the file.
	///< @return The start group of the key file.

	std::vector<String> get_groups() const;
	///< Gets all groups in the key file. 
	///< @return A vector of String holding all the group names in the key file.
	///<
	///< If there are no group names in the key file the returned vector will be empty.  	

	std::vector<String> get_keys(const char *group_name, Error *error) const;
	std::vector<String> get_keys(const String& group_name, Error *error) const;
	///< Gets all keys for the group name <EM>group_name</EM>. 
	///< @param group_name The group name to get the keys for. 
	///< @param error The return location for a G::Error, or null. 
	///< @return A vector of String holding all the keys for <EM>group_name</EM> in the key file.
	///< 	
	///< In the event that the <EM>group_name</EM> cannot be found, the returned
	///< vector will be empty and error is set to G::KEY_FILE_ERROR_GROUP_NOT_FOUND.

	bool has_group(const char *group_name) const;
	bool has_group(const String& group_name) const;
	///< Determines whether the key file has the group <EM>group_name</EM>.
	///< @param group_name A group name.
	///< @return <EM>true</EM> if <EM>group_name</EM> is a part of the key file, <EM>false</EM> otherwise.

	bool has_key(const char *group_name, const char *key, Error *error) const;
	bool has_key(const String& group_name, const String& key, Error *error) const;
	///< Determines whether the key file has the key <EM>key</EM> in the group <EM>group_name</EM>. 
	///< @param group_name A group name.
	///< @param key A key name.
	///< @param error The return location for a G::Error, or null. 
	///< @return <EM>true</EM> if <EM>key</EM> is a part of <EM>group_name</EM>, <EM>false</EM> otherwise.
	///< 	
	///< If <EM>group_name</EM> is null, the start group is used.

	String get_value(const char *group_name, const char *key, Error *error) const;
	String get_value(const String& group_name, const String& key, Error *error) const;
	///< Gets the value associated with <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name.
	///< @param key A key name.
	///< @param error The return location for a G::Error, or null. 
	///< @return The string value for <EM>key</EM>.
	///<
	///< In the event the <EM>key</EM> cannot be found, a null string is returned and
	///< <EM>error</EM> is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND. In the event that
	///< the <EM>group_name</EM> cannot be found, a null string is returned and error
	///< is set to G::KEY_FILE_ERROR_GROUP_NOT_FOUND.

	String get_string(const char *group_name, const char *key, Error *error) const;
	String get_string(const String& group_name, const String& key, Error *error) const;
	///< Gets the value associated with <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error, or null. 
	///< @return A String. 
	///<
	///< In the event the <EM>key</EM> cannot be found, a null string is returned
	///< and <EM>error</EM> is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND. In the event
	///< that the <EM>group_name</EM> cannot be found, a null string is returned and
	///< <EM>error</EM> is set to G::KEY_FILE_ERROR_GROUP_NOT_FOUND.

	String get_string(const char *group_name, const char *key, const char *locale, Error *error) const;
	String get_string(const String& group_name, const String& key, const String& locale, Error *error) const;
	///< Gets the value associated with <EM>key</EM> under <EM>group_name</EM> translated
	///< in the given locale if available. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param locale A locale, or null. 
	///< @param error The return location for a G::Error, or null. 
	///< @return A String. 
	///<	
	///< If <EM>locale</EM> is null then the current locale is assumed. If <EM>key</EM> cannot be
	///< found then a null string is returned and error is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND.
	///< If the value associated with <EM>key</EM> cannot be interpreted or no suitable translation
	///< can be found then the untranslated value is returned.

	bool get_boolean(const char *group_name, const char *key, Error *error) const;
	bool get_boolean(const String& group_name, const String& key, Error *error) const;
	///< Gets the value associated with <EM>key</EM> under <EM>group_name</EM> as a bool value.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error. 
	///< @return The value associated with the <EM>key</EM> as a bool. 
	///<	 
	///< If <EM>group_name</EM> is null, the start group is used. If <EM>key</EM> cannot be found then
	///< the return value is undefined and <EM>error</EM> is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND.
	///< Likewise, if the value associated with <EM>key</EM> cannot be interpreted as a bool then
	///< the return value is also undefined and <EM>error</EM> is set to G::KEY_FILE_ERROR_INVALID_VALUE.

	int get_integer(const char *group_name, const char *key, Error *error) const;
	int get_integer(const String& group_name, const String& key, Error *error) const;
	///< Gets the value associated with <EM>key</EM> under <EM>group_name</EM> as an integer.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error. 
	///< @return The value associated with the <EM>key</EM> as an integer. 
	///<	 
	///< If <EM>group_name</EM> is null, the start_group is used. If <EM>key</EM> cannot be found then
	///< the return value is undefined and <EM>error</EM> is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND.
	///< Likewise, if the value associated with <EM>key</EM> cannot be interpreted as an integer then
	///< the return value is also undefined and <EM>error</EM> is set to G::KEY_FILE_ERROR_INVALID_VALUE.

	std::vector<String> get_string_list(const char *group_name, const char *key, Error *error) const;
	std::vector<String> get_string_list(const String& group_name, const String& key, Error *error) const;
	///< Gets the string values associated with <EM>key</EM> under <EM>group_name</EM>.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error, or null. 
	///< @return A vector of String holding the values associated with <EM>key</EM>. 
	///<	
	///< In the event the <EM>key</EM> cannot be found, an empty vector is returned
	///< and <EM>error</EM> is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND. In the event
	///< that the <EM>group_name</EM> cannot be found, an empty vector is returned
	///< and <EM>error</EM> is set to G::KEY_FILE_ERROR_GROUP_NOT_FOUND.

	std::vector<String> get_string_list(const char *group_name, const char *key, const char *locale, Error *error) const;
	std::vector<String> get_string_list(const String& group_name, const String& key, const String& locale, Error *error) const;
	///< Gets the values associated with <EM>key</EM> under <EM>group_name</EM> translated
	///< in the given <EM>locale</EM> if available. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param locale A locale, such as "de", "fr",  or "it". 
	///< @param error The return location for a G::Error, or null. 
	///< @return A vector of String holding the values associated with <EM>key</EM>. 
	///<	
	///< If <EM>locale</EM> is null then the current locale is assumed. If <EM>group_name</EM> is null,
	///< then the start group is used. If <EM>key</EM> cannot be found then an empty vector is returned
	///< and <EM>error</EM> is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND. If the values associated with 
	///< <EM>key</EM> cannot be interpreted or no suitable translations can be found then the untranslated
	///< values are returned.

	std::vector<bool> get_boolean_list(const char *group_name, const char *key, Error *error) const;
	std::vector<bool> get_boolean_list(const String& group_name, const String& key, Error *error) const;
	///< Gets the values associated with <EM>key</EM> under <EM>group_name</EM> as bools.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error, or null. 
	///< @return A vector of bool holding the values associated with <EM>key</EM> as bools. 
	///<	 
	///< If <EM>group_name</EM> is null, the start_group is used. If <EM>key</EM> cannot be found then
	///< an empty vector is returned and <EM>error</EM> is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND.
	///< Likewise, if the values associated with <EM>key</EM> cannot be interpreted as bools then an
	///< empty vector is returned and error is set to G::KEY_FILE_ERROR_INVALID_VALUE.

	std::vector<int> get_integer_list(const char *group_name, const char *key, Error *error) const;
	std::vector<int> get_integer_list(const String& group_name, const String& key, Error *error) const;
	///< Gets the values associated with <EM>key</EM> under <EM>group_name</EM> as integers.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error, or null. 
	///< @return A vector of int holding the values associated with <EM>key</EM> as integers. 
	///< 	 
	///< If <EM>group_name</EM> is null, the start_group is used. If <EM>key</EM> cannot be found then 
	///< an empty vector is returned and <EM>error</EM> is set to G::KEY_FILE_ERROR_KEY_NOT_FOUND.
	///< Likewise, if the values associated with <EM>key</EM> cannot be interpreted as integers then an
	///< empty vector is returned and error is set to G::KEY_FILE_ERROR_INVALID_VALUE.

	String get_comment(const char *group_name, const char *key, Error *error) const;
	String get_comment(const String& group_name, const String& key, Error *error) const;
	///< Retreives a comment above <EM>key</EM> from group name <EM>group_name</EM>.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error, or null. 
	///< @return The comment string. 
	///<	 
	///< If <EM>key</EM> is null then <EM>comment</EM> will be read from above <EM>group_name</EM>.
	///< If both <EM>key</EM> and <EM>group_name</EM> are null, then <EM>comment</EM> will be read
	///< from above the first group in the file. 

	String get_comment(const char *group_name, Error *error) const;
	String get_comment(const String& group_name, Error *error) const;
	///< Retreives a comment from above group name <EM>group_name</EM>.
	///< @param group_name A group name. 
	///< @param error The return location for a G::Error, or null. 
	///< @return The group comment string. 
	///<	 
	///< If <EM>group_name</EM> is null, then <EM>comment</EM> will be read
	///< from above the first group in the file. 

/// @}
/// @name Methods
/// @{

	void set_list_separator(char separator);
	///< Sets the character which is used to separate values in lists. 
	///< @param separator The separator.
	///<
	///< Typically ';' or ',' are used as separators. The default list separator is ';'.

	bool load_from_file(const char *file, KeyFileFlagsField flags, Error *error);
	bool load_from_file(const std::string& file, KeyFileFlagsField flags, Error *error);
	///< Loads a key file into an empty KeyFile object. 
	///< @param file The path of the filename to load, in the GLib file name encoding. 
	///< @param flags One or more flags from G::KeyFileFlags enumeration. 
	///< @param error The return location for a G::Error, or null. 
	///< @return <EM>true</EM> if the key file could be loaded, <EM>false</EM> otherwise. 
	///<	
	///< To get the file name encoding call Xfc::String::to_filename(). If the file could
	///< not be loaded then error is set to either a G::FileError or G::KeyFileError.

	bool load_from_data(const char *data, unsigned int length, KeyFileFlagsField flags, Error *error);
	///< Loads a key file from memory into an empty KeyFile object. 
	///< @param data A key file loaded in memory. 
	///< @param length The length of <EM>data</EM> in bytes. 
	///< @param flags One or more flags from G::KeyFileFlags enumeration. 
	///< @param error The return location for a G::Error, or null. 
	///< @return <EM>true</EM> if the key file could be loaded, <EM>false</EM> otherwise. 
	///<	
	///< If the object cannot be created then <EM>error</EM> is set to a G::KeyFileError.

	bool load_from_data_dirs(const char *file, String& full_path, KeyFileFlagsField flags, Error *error);
	bool load_from_data_dirs(const String& file, String& full_path, KeyFileFlagsField flags, Error *error);
	///< This method looks for a key file named <EM>file</EM> in the paths returned from
	///< g_get_user_data_dir() and g_get_system_data_dirs(), loads the file into the 
	///< key_file and returns the file's full path in <EM>full_path</EM>. 
	///< @param file A relative path to a filename to open and parse. 
	///< @param full_path The return location for a string containing the full path of the file. 
	///< @param flags One or more flags from G::KeyFileFlags enumeration. 
	///< @param error The return location for a G::Error, or null. 
	///< @return <EM>true</EM> if the key file could be loaded, <EM>false</EM> otherwise. 
	///<	
	///< If the file could not be loaded <EM>error</EM> is set to either a 
	///< G::FileError or G::KeyFileError.

	String to_data(Error *error);
	///< This method outputs the key file as a string.
	///< @param error The return location for a G::Error, or null. 
	///< @return A String holding the contents of the key file

	void set_value(const char *group_name, const char *key, const char *value);
	void set_value(const String& group_name, const String& key, const String& value);
	///< Associates a new value with <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param value A string value.
	///<	
	///< If <EM>key</EM> cannot be found then it is created. If <EM>group_name</EM>
	///< cannot be found then it is created.

	void set_string(const char *group_name, const char *key, const char *value);
	void set_string(const String& group_name, const String& key, const String& value);
	///< Associates a new string value with <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param value A String.
	///<	
	///< If <EM>key</EM> cannot be found then it is created. If <EM>group_name</EM>
	///< cannot be found then it is created.

	void set_string(const char *group_name, const char *key, const char *locale, const char *value);
	void set_string(const String& group_name, const String& key, const String& locale, const String& value);
	///< Associates a string value for <EM>key</EM> and <EM>locale</EM> under <EM>group_name</EM>.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param locale A locale, such as "de", "fr",  or "it". 
	///< @param value A String.
	///<	
	///< If the translation for <EM>key</EM> cannot be found then it is created.

	void set_boolean(const char *group_name, const char *key, bool value);
	void set_boolean(const String& group_name, const String& key, bool value);
	///< Associates a new bool value with <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param value A new bool value to associate with <EM>key</EM>. 
	///<	
	///< If <EM>key</EM> cannot be found then it is created. If <EM>group_name</EM> is null, 
	///< the start group is used.
	
	void set_integer(const char *group_name, const char *key, int value);
	void set_integer(const String& group_name, const String& key, int value);
	///< Associates a new integer value with <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param value A new integer value to associate with <EM>key</EM>. 
	///<	
	///< If <EM>key</EM> cannot be found then it is created. If <EM>group_name</EM> is null,
	///< the start group is used.

	void set_string_list(const char *group_name, const char *key, const std::vector<String>& strings);
	void set_string_list(const String& group_name, const String& key, const std::vector<String>& strings);
	///< Associates a list of string values for <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param strings A vector of String holding the list of string values. 
	///<	
	///< If <EM>key</EM> cannot be found then it is created. If <EM>group_name</EM> 
	///< cannot be found then it is created.
	
	void set_string_list(const char *group_name, const char *key, const char *locale, const std::vector<String>& strings);
	void set_string_list(const String& group_name, const String& key, const String& locale, const std::vector<String>& strings);
	///< Associates a list of string values for <EM>key</EM> and <EM>locale</EM> under <EM>group_name</EM>.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param locale A locale, such as "de", "fr",  or "it". 
	///< @param strings A vector of String holding the list of locale string values. 
	///<
	///< If the translation for <EM>key</EM> cannot be found then it is created. If <EM>group_name</EM>
	///< is null, the start group is used.

	void set_boolean_list(const char *group_name, const char *key, std::vector<bool>& values);
	void set_boolean_list(const String& group_name, const String& key, std::vector<bool>& values);
	///< Associates a list of bool values with <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param values A vector of bool holding the list of bool values. 
	///<	
	///< If <EM>key</EM> cannot be found then it is created. If <EM>group_name</EM> is null,
	///< the start_group is used.

	void set_integer_list(const char *group_name, const char *key, std::vector<int>& values);
	void set_integer_list(const String& group_name, const String& key, std::vector<int>& values);
	///< Associates a list of integer values with <EM>key</EM> under <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param values A vector of int holding the list of integer values. 
	///<	
	///< If <EM>key</EM> cannot be found then it is created. If <EM>group_name</EM> is null,
	///< the start_group is used.
	
	void set_comment(const char *group_name, const char *key, const char *comment, Error *error);
	void set_comment(const String& group_name, const String& key, const String& comment, Error *error);
	///< Places a comment above <EM>key</EM> from group name <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param comment A comment string. 
	///< @param error The return location for a G::Error, or null. 
	///<	
	///< If <EM>key</EM> is null then <EM>comment</EM> will be written above <EM>group_name</EM>. 
	///< If both <EM>key</EM> and <EM>group_name</EM> are null, then comment will be written
	///< above the first group in the file.
	
	void set_comment(const char *group_name, const char *comment, Error *error);
	void set_comment(const String& group_name, const String& comment, Error *error);
	///< Places a comment above group name <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param comment A comment string. 
	///< @param error The return location for a G::Error. 
	///<	
	///< If <EM>group_name</EM> is null, then comment will be written above the first group in the file.
	
	void remove_comment(const char *group_name, const char *key, Error *error);
	void remove_comment(const String& group_name, const String& key, Error *error);
	///< Removes a comment above <EM>key</EM> from group name <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error. 
	///<	
	///< If <EM>key</EM> is null then <EM>comment</EM> will be removed from above <EM>group_name</EM>. 
	///< If both <EM>key</EM> and <EM>group_name</EM> are null, then <EM>comment</EM> will be removed
	///< from above the first group in the file.

	void remove_comment(const char *group_name, Error *error);
	void remove_comment(const String& group_name, Error *error);
	///< Removes a comment from above group name <EM>group_name</EM>. 
	///< @param group_name A group name. 
	///< @param error The return location for a G::Error. 
	///<	
	///< If <EM>group_name</EM> is null, then <EM>comment</EM> will be removed
	///< from above the first group in the file.

	void remove_key(const char *group_name, const char *key, Error *error);
	void remove_key(const String& group_name, const String& key, Error *error);
	///< Removes <EM>key</EM> in <EM>group_name</EM> from the key file.
	///< @param group_name A group name. 
	///< @param key A key. 
	///< @param error The return location for a G::Error. 

	void remove_group(const char *group_name, Error *error);
	void remove_group(const String& group_name, Error *error);
	///< Removes the specified group, <EM>group_name</EM>, from the key file.
	///< @param group_name A group name. 
	///< @param error The return location for a G::Error. 

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/keyfile.inl>

#endif // XFC_G_KEY_FILE_HH














