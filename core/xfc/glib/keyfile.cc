/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  keyfile.cc - C++ interface for the GKeyFile configuration file parser.
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

#include "keyfile.hh"
#include "error.hh"
#include <glib/gmem.h>
#include <glib/gmessages.h>
#include <glib/gstrfuncs.h>

using namespace Xfc;

/*  G::KeyFile
 */

G::KeyFile::KeyFile()
: keyfile_(g_key_file_new())
{
}

G::KeyFile::~KeyFile()
{
	if (keyfile_)
	{
		g_key_file_free(keyfile_);
		keyfile_ = 0;
	}
}

String 
G::KeyFile::get_start_group() const
{
	char *start_group = g_key_file_get_start_group(keyfile_);
	String s(start_group);
	g_free(start_group);
	return s;
}

std::vector<String> 
G::KeyFile::get_groups() const
{
	gsize size;	
	char **tmp_groups = g_key_file_get_groups(keyfile_, &size);
	std::vector<String> groups;
	groups.reserve(size);
	
	int i = 0;	
	while (tmp_groups[i])
	{
		String s(tmp_groups[i]);
		groups.push_back(s);
		++i;
	}
	g_strfreev(tmp_groups);
	return groups;
}

std::vector<String> 
G::KeyFile::get_keys(const char *group_name, Error *error) const
{
	gsize size;	
	char **tmp_keys = g_key_file_get_keys(keyfile_, group_name, &size, *error);
	std::vector<String> keys;
	keys.reserve(size);
	
	int i = 0;	
	while (tmp_keys[i])
	{
		String s(tmp_keys[i]);
		keys.push_back(s);
		++i;
	}
	g_strfreev(tmp_keys);
	return keys;
}
	
std::vector<String> 
G::KeyFile::get_keys(const String& group_name, Error *error) const
{
	return get_keys(group_name.c_str(), error);
}

bool 
G::KeyFile::has_group(const String& group_name) const
{
	return has_group(group_name.c_str());
}

bool 
G::KeyFile::has_key(const char *group_name, const char *key, Error *error) const
{
	return g_key_file_has_key(keyfile_, group_name, key, *error);
}
	
bool 
G::KeyFile::has_key(const String& group_name, const String& key, Error *error) const
{
	return has_key(group_name.c_str(), key.c_str(), error);
}

String 
G::KeyFile::get_value(const char *group_name, const char *key, Error *error) const
{
	char *value = g_key_file_get_value(keyfile_, group_name, key, *error);
	String s(value);
	g_free(value);
	return s;
}
	
String 
G::KeyFile::get_value(const String& group_name, const String& key, Error *error) const
{
	return get_value(group_name.c_str(), key.c_str(), error);
}

String 
G::KeyFile::get_string(const char *group_name, const char *key, Error *error)  const
{
	char *value = g_key_file_get_string(keyfile_, group_name, key, *error);
	String s(value);
	g_free(value);
	return s;
}
	
String 
G::KeyFile::get_string(const String& group_name, const String& key, Error *error) const
{
	return get_string(group_name.c_str(), key.c_str(), error);
}

String 
G::KeyFile::get_string(const char *group_name, const char *key, const char *locale, Error *error) const
{
	char *value = g_key_file_get_locale_string(keyfile_, group_name, key, locale, *error);
	String s(value);
	g_free(value);
	return s;
}
	
String 
G::KeyFile::get_string(const String& group_name, const String& key, const String& locale, Error *error) const
{
	return get_string(group_name.c_str(), key.c_str(), locale.c_str(), error);
}

bool 
G::KeyFile::get_boolean(const char *group_name, const char *key, Error *error) const
{
	return g_key_file_get_boolean(keyfile_, group_name, key, *error);
}
	
bool 
G::KeyFile::get_boolean(const String& group_name, const String& key, Error *error) const
{
	return get_boolean(group_name.c_str(), key.c_str(), error);
}
	
int 
G::KeyFile::get_integer(const char *group_name, const char *key, Error *error) const
{
	return g_key_file_get_integer(keyfile_, group_name, key, *error);
}
	
int 
G::KeyFile::get_integer(const String& group_name, const String& key, Error *error) const
{
	return get_integer(group_name.c_str(), key.c_str(), error);
}

std::vector<String> 
G::KeyFile::get_string_list(const char *group_name, const char *key, Error *error) const
{
	gsize size;	
	char **tmp_strings = g_key_file_get_string_list(keyfile_, group_name, key, &size, *error);
	std::vector<String> strings;
	strings.reserve(size);
	
	int i = 0;	
	while (tmp_strings[i])
	{
		String s(tmp_strings[i]);
		strings.push_back(s);
		++i;
	}
	g_strfreev(tmp_strings);
	return strings;
}
	
std::vector<String> 
G::KeyFile::get_string_list(const String& group_name, const String& key, Error *error) const
{
	return get_string_list(group_name.c_str(), key.c_str(), error);
}

std::vector<String> 
G::KeyFile::get_string_list(const char *group_name, const char *key, const char *locale, Error *error) const
{
	gsize size;	
	char **tmp_strings = g_key_file_get_locale_string_list(keyfile_, group_name, key, locale, &size, *error);
	std::vector<String> strings;
	strings.reserve(size);
	
	int i = 0;	
	while (tmp_strings[i])
	{
		String s(tmp_strings[i]);
		strings.push_back(s);
		++i;
	}
	g_strfreev(tmp_strings);
	return strings;
}
	
std::vector<String> 
G::KeyFile::get_string_list(const String& group_name, const String& key, const String& locale, Error *error) const
{
	return get_string_list(group_name.c_str(), key.c_str(), locale.c_str(), error);
}

std::vector<bool> 
G::KeyFile::get_boolean_list(const char *group_name, const char *key, Error *error) const
{
	gsize size;	
	Error keyfile_error;	
	gboolean *tmp_values = g_key_file_get_boolean_list(keyfile_, group_name, key, &size, keyfile_error);
	std::vector<bool> values;

	if (!keyfile_error.get())
	{
		values.reserve(size);
		int i = 0;	
		while (tmp_values[i])
		{
			values.push_back(tmp_values[i]);
			++i;
		}
		g_free(tmp_values);
	}
	else
	{
		if (error)
			error->propagate(keyfile_error);
	}
	return values;
}	
	
std::vector<bool> 
G::KeyFile::get_boolean_list(const String& group_name, const String& key, Error *error) const
{
	return get_boolean_list(group_name.c_str(), key.c_str(), error);
}	

std::vector<int> 
G::KeyFile::get_integer_list(const char *group_name, const char *key, Error *error) const
{
	gsize size;	
	Error keyfile_error;	
	int *tmp_values = g_key_file_get_integer_list(keyfile_, group_name, key, &size, keyfile_error);
	std::vector<int> values;

	if (!keyfile_error.get())
	{
		values.reserve(size);
		int i = 0;	
		while (tmp_values[i])
		{
			values.push_back(tmp_values[i]);
			++i;
		}
		g_free(tmp_values);
	}
	else
	{
		if (error)
			error->propagate(keyfile_error);
	}
	return values;
}	
	
std::vector<int> 
G::KeyFile::get_integer_list(const String& group_name, const String& key, Error *error) const
{
	return get_integer_list(group_name.c_str(), key.c_str(), error);
}	

String 
G::KeyFile::get_comment(const char *group_name, const char *key, Error *error) const
{
	char *comment = g_key_file_get_comment(keyfile_, group_name, key, *error);
	String s(comment);
	g_free(comment);
	return s;
}
	
String 
G::KeyFile::get_comment(const String& group_name, const String& key, Error *error) const
{
	return get_comment(group_name.c_str(), key.c_str(), error);
}

String 
G::KeyFile::get_comment(const char *group_name, Error *error) const
{
	return get_comment(group_name, 0, error);
}
	
String 
G::KeyFile::get_comment(const String& group_name, Error *error) const
{
	return get_comment(group_name.c_str(), 0, error);
}

void 
G::KeyFile::set_list_separator(char separator)
{
	g_key_file_set_list_separator(keyfile_, separator);
}

bool 
G::KeyFile::load_from_file(const char *file, KeyFileFlagsField flags, Error *error)
{
	return g_key_file_load_from_file(keyfile_, file, (GKeyFileFlags)flags, *error);
}
	
bool 
G::KeyFile::load_from_file(const std::string& file, KeyFileFlagsField flags, Error *error)
{
	return load_from_file(file.c_str(), flags, error);
}

bool 
G::KeyFile::load_from_data(const char *data, unsigned int length, KeyFileFlagsField flags, Error *error)
{
	return g_key_file_load_from_data(keyfile_, data, length, (GKeyFileFlags)flags, *error);
}

bool 
G::KeyFile::load_from_data_dirs(const char *file, String& full_path, KeyFileFlagsField flags, Error *error)
{
	char *tmp_full_path = 0;
	bool result = g_key_file_load_from_data_dirs(keyfile_, file, &tmp_full_path, (GKeyFileFlags)flags, *error);
	if (tmp_full_path)
	{
		full_path.assign(tmp_full_path);
		g_free(tmp_full_path);
	}
	return result;
}
	
bool 
G::KeyFile::load_from_data_dirs(const String& file, String& full_path, KeyFileFlagsField flags, Error *error)
{
	return load_from_data_dirs(file.c_str(), full_path, flags, error);
}

String 
G::KeyFile::to_data(Error *error)
{
	gsize length;
	char *data = g_key_file_to_data(keyfile_, &length, *error);
	String s(data, length);
	g_free(data);
	return s;
}

void 
G::KeyFile::set_value(const String& group_name, const String& key, const String& value)
{
	set_value(group_name.c_str(), key.c_str(), value.c_str());
}

void 
G::KeyFile::set_string(const String& group_name, const String& key, const String& value)
{
	set_string(group_name.c_str(), key.c_str(), value.c_str());
}

void 
G::KeyFile::set_string(const String& group_name, const String& key, const String& locale, const String& value)
{
	set_string(group_name.c_str(), key.c_str(), locale.c_str(), value.c_str());
}
	
void 
G::KeyFile::set_boolean(const String& group_name, const String& key, bool value)
{
	set_boolean(group_name.c_str(), key.c_str(), value);
}
	
void 
G::KeyFile::set_integer(const String& group_name, const String& key, int value)
{
	set_integer(group_name.c_str(), key.c_str(), value);
}

void 
G::KeyFile::set_string_list(const char *group_name, const char *key, const std::vector<String>& strings)
{
	g_return_if_fail(!strings.empty());
	int size = strings.size();
	const char **tmp_strings = new const char*[size];

	int i = 0;	
	while (i < size)
	{
		tmp_strings[i] = strings[i].c_str();
		++i;
	}

	g_key_file_set_string_list(keyfile_, group_name, key, tmp_strings, size);
	delete [] tmp_strings;
}
	
void 
G::KeyFile::set_string_list(const String& group_name, const String& key, const std::vector<String>& strings)
{
	return set_string_list(group_name.c_str(), key.c_str(), strings);
}
	
void 
G::KeyFile::set_string_list(const char *group_name, const char *key, const char *locale, const std::vector<String>& strings)
{					     
	g_return_if_fail(!strings.empty());
	int size = strings.size();
	const char **tmp_strings = new const char*[size];

	int i = 0;	
	while (i < size)
	{
		tmp_strings[i] = strings[i].c_str();
		++i;
	}

	g_key_file_set_locale_string_list(keyfile_, group_name, key, locale, tmp_strings, size);
	delete [] tmp_strings;
}					     
	
void 
G::KeyFile::set_string_list(const String& group_name, const String& key, const String& locale, const std::vector<String>& strings)
{
	return set_string_list(group_name.c_str(), key.c_str(), locale.c_str(), strings);
}
	
void 
G::KeyFile::set_boolean_list(const char *group_name, const char *key, std::vector<bool>& values)
{
	g_return_if_fail(!values.empty());
	int size = values.size();
	gboolean *tmp_values = new gboolean[size]; 

	int i = 0;	
	while (i < size)
	{
		tmp_values[i] = values[i];
		++i;
	}

	g_key_file_set_boolean_list(keyfile_, group_name, key, tmp_values, size);
	delete [] tmp_values;
}

void 
G::KeyFile::set_boolean_list(const String& group_name, const String& key, std::vector<bool>& values)
{
	set_boolean_list(group_name.c_str(), key.c_str(), values);
}
	
void 
G::KeyFile::set_integer_list(const char *group_name, const char *key, std::vector<int>& values)
{
	g_return_if_fail(!values.empty());
	int size = values.size();
	int *tmp_values = new int[size]; 

	int i = 0;	
	while (i < size)
	{
		tmp_values[i] = values[i];
		++i;
	}

	g_key_file_set_integer_list(keyfile_, group_name, key, tmp_values, size);
	delete [] tmp_values;
}
	
void 
G::KeyFile::set_integer_list(const String& group_name, const String& key, std::vector<int>& values)
{
	set_integer_list(group_name.c_str(), key.c_str(), values);
}
	
void 
G::KeyFile::set_comment(const char *group_name, const char *key, const char *comment, Error *error)
{
	g_key_file_set_comment(keyfile_, group_name, key, comment, *error);
}
	
void 
G::KeyFile::set_comment(const String& group_name, const String& key, const String& comment, Error *error)
{
	set_comment(group_name.c_str(), key.c_str(), comment.c_str(), error);
}
	
void 
G::KeyFile::set_comment(const char *group_name, const char *comment, Error *error)
{
	set_comment(group_name, 0, comment, error);
}
	
void 
G::KeyFile::set_comment(const String& group_name, const String& comment, Error *error)
{
	set_comment(group_name.c_str(), 0, comment.c_str(), error);
}
	
void 
G::KeyFile::remove_comment(const char *group_name, const char *key, Error *error)
{		
	g_key_file_remove_comment(keyfile_, group_name, key, *error);
}
	
void 
G::KeyFile::remove_comment(const String& group_name, const String& key, Error *error)
{		
	remove_comment(group_name.c_str(), key.c_str(), error);
}

void 
G::KeyFile::remove_comment(const char *group_name, Error *error)
{		
	remove_comment(group_name, 0, error);
}
	
void 
G::KeyFile::remove_comment(const String& group_name, Error *error)
{		
	remove_comment(group_name.c_str(), 0, error);
}

void 
G::KeyFile::remove_key(const char *group_name, const char *key, Error *error)
{
	g_key_file_remove_key(keyfile_, group_name, key, *error);
}
	
void 
G::KeyFile::remove_key(const String& group_name, const String& key, Error *error)
{
	remove_key(group_name.c_str(), key.c_str(), error);
}

void 
G::KeyFile::remove_group(const char *group_name, Error *error)
{
	g_key_file_remove_group(keyfile_, group_name, *error);
}
	
void 
G::KeyFile::remove_group(const String& group_name, Error *error)
{
	remove_group(group_name.c_str(), error);
}

