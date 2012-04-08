/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  keyfile.inl - G::KeyFile inline functions
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

inline GKeyFile*
Xfc::G::KeyFile::g_key_file() const
{
	return keyfile_;
}

inline Xfc::G::KeyFile::operator GKeyFile* () const
{
	return this ? keyfile_ : 0;
}

bool 
Xfc::G::KeyFile::has_group(const char *group_name) const
{
	return g_key_file_has_group(keyfile_, group_name);
}
	
void 
Xfc::G::KeyFile::set_value(const char *group_name, const char *key, const char *value)
{
	g_key_file_set_value(keyfile_, group_name, key, value);
}
	
void 
Xfc::G::KeyFile::set_string(const char *group_name, const char *key, const char *value)
{
	g_key_file_set_string(keyfile_, group_name, key, value);
}
	
void 
Xfc::G::KeyFile::set_string(const char *group_name, const char *key, const char *locale, const char *value)
{
	g_key_file_set_locale_string(keyfile_, group_name, key, locale, value);
}
	
void 
Xfc::G::KeyFile::set_boolean(const char *group_name, const char *key, bool value)
{
	g_key_file_set_boolean(keyfile_, group_name, key, value);
}
	
void 
Xfc::G::KeyFile::set_integer(const char *group_name, const char *key, int value)
{
	g_key_file_set_integer(keyfile_, group_name, key, value);
}
	
