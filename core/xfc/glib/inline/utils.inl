/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  utils.inl - Various GLib utility inline functions
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

std::string 
Xfc::G::get_user_name()
{
	return std::string(g_get_user_name());
}

std::string 
Xfc::G::get_real_name()
{
	return std::string(g_get_real_name());
}
 
std::string 
Xfc::G::get_home_dir()
{
	return std::string(g_get_home_dir());
}

std::string 
Xfc::G::get_tmp_dir()
{
	return std::string(g_get_tmp_dir());
}

std::string 
Xfc::G::get_prgname()
{
	return std::string(g_get_prgname());
}

void 
Xfc::G::set_prgname (const char *prgname)
{
	g_set_prgname(prgname);
}

void 
Xfc::G::set_application_name(const char *application_name)
{
	g_set_application_name(application_name);
}

std::string 
Xfc::G::get_user_data_dir()
{
	return std::string(g_get_user_data_dir());
}

std::string 
Xfc::G::get_user_config_dir()
{
	return std::string(g_get_user_config_dir());
}

std::string 
Xfc::G::get_user_cache_dir()
{
	return std::string(g_get_user_cache_dir());
}

bool 
Xfc::G::path_is_absolute(const gchar *file_name)
{
	return g_path_is_absolute(file_name);
}

bool 
Xfc::G::setenv(const char *variable, const char *value, bool overwrite)
{
	return g_setenv(variable, value, overwrite);
}

void 
Xfc::G::unsetenv(const char *variable)
{
	g_unsetenv(variable);
}

