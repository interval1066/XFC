/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  utils.cc - C++ interface for the various GLib utility functions.
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

#include "utils.hh"
#include "error.hh"
#include <glib/gmem.h>
#include <glib/gfileutils.h>

using namespace Xfc;

/*  G::set_prgname
 */

void 
G::set_prgname (const std::string& prgname)
{
	set_prgname(prgname.c_str());
}
 
/*  G::get_application_name
 */

String 
G::get_application_name()
{
	return g_get_application_name();
}

/*  G::set_application_name
 */

void 
G::set_application_name(const String& application_name)
{
	set_application_name(application_name.c_str());
}

/*  G::get_system_data_dirs
 */

std::vector<std::string> 
G::get_system_data_dirs()
{
	std::vector<std::string> dirs;

	int i = 0;
	const char *const *tmp_dirs = g_get_system_data_dirs();
	
	while (tmp_dirs[i] && *tmp_dirs[i])
	{
		std::string s(tmp_dirs[i]);
		dirs.push_back(s);
		++i;
	}
	return dirs;
}

/*  G::get_system_config_dirs
 */

std::vector<std::string> 
G::get_system_config_dirs()
{
	std::vector<std::string> dirs;

	int i = 0;
	const char *const *tmp_dirs = g_get_system_config_dirs();
	
	while (tmp_dirs[i] && *tmp_dirs[i])
	{
		std::string s(tmp_dirs[i]);
		dirs.push_back(s);
		++i;
	}
	return dirs;
}

/*  G::path_is_absolute
 */

bool 
G::path_is_absolute(const std::string& file_name)
{
	return path_is_absolute(file_name.c_str());
}
 
/*  G::path_skip_root
 */

std::string 
G::path_skip_root(const char *file_name)
{
	const char *ptr = g_path_skip_root(file_name);
	return ptr ? std::string(ptr) : std::string();
}

std::string 
G::path_skip_root(const std::string& file_name)
{
	return path_skip_root(file_name.c_str());
}

/*  G::get_current_dir
 */

std::string 
G::get_current_dir()
{
	char *dir = g_get_current_dir();
	std::string s(dir);
	g_free(dir);
	return s;
}

/*  G::path_get_basename
 */

std::string 
G::path_get_basename(const char *file_name)
{
	char *dir = g_path_get_basename(file_name);
	std::string s(dir ? dir : "");
	g_free(dir);
	return s;
}

std::string 
G::path_get_basename(const std::string& file_name)
{
	return path_get_basename(file_name.c_str());
}

/*  G::path_get_dirname
 */

std::string 
G::path_get_dirname(const char *file_name)
{
	char *dir = g_path_get_dirname(file_name);
	std::string s(dir ? dir : "");
	g_free(dir);
	return s;
}

std::string 
G::path_get_dirname(const std::string& file_name)
{
	return path_get_dirname(file_name.c_str());
}

/*  G::getenv
 */

std::string 
G::getenv(const char *variable)
{
	const char *tmp_variable = g_getenv(variable);
	return tmp_variable ? std::string(tmp_variable) : std::string();
}

std::string 
G::getenv(const std::string& variable)
{
	return getenv(variable.c_str());
}

/*  G::setenv
 */

bool 
G::setenv(const std::string& variable, const std::string& value, bool overwrite)
{
	return setenv(variable.c_str(), value.c_str(), overwrite);
}
 
/*  G::unsetenv
 */

void 
G::unsetenv(const std::string& variable)
{
	unsetenv(variable.c_str());
}

/*  G::find_program_in_path
 */

std::string 
G::find_program_in_path(const char *program)
{
	char *path = g_find_program_in_path(program);
	std::string s(path ? path : "");
	g_free(path);
	return s;
}	

std::string 
G::find_program_in_path(const std::string& program)
{
	return find_program_in_path(program.c_str());
}	

/*  G::build_filename
 */

std::string 
G::build_filename(const std::string& s1, const std::string& s2)
{
	char *result = g_build_filename(s1.c_str(), s2.c_str(), NULL);
	std::string s(result);
	g_free(result);
	return s;
}

std::string 
G::build_filename(const std::string& s1, const std::string& s2, const std::string& s3)
{
	char *result = g_build_filename(s1.c_str(), s2.c_str(), s3.c_str(), NULL);
	std::string s(result);
	g_free(result);
	return s;
}

std::string 
G::build_filename(const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4)
{
	char *result = g_build_filename(s1.c_str(), s2.c_str(), s3.c_str(), s4.c_str(), NULL);
	std::string s(result);
	g_free(result);
	return s;
}

/*  G::build_path
 */

std::string 
G::build_path(const std::string& separator, const std::string& s1, const std::string& s2)
{
	char *result = g_build_path(separator.c_str(), s1.c_str(), s2.c_str(), NULL);
	std::string s(result);
	g_free(result);
	return s;
}

std::string 
G::build_path(const std::string& separator, const std::string& s1, const std::string& s2, const std::string& s3)
{
	char *result = g_build_path(separator.c_str(), s1.c_str(), s2.c_str(), s3.c_str(), NULL);
	std::string s(result);
	g_free(result);
	return s;
}

std::string 
G::build_path(const std::string& separator, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4)
{
	char *result = g_build_path(separator.c_str(), s1.c_str(), s2.c_str(), s3.c_str(), s4.c_str(), NULL);
	std::string s(result);
	g_free(result);
	return s;
}

