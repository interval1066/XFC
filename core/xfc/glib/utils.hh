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

/// @file xfc/glib/utils.hh
/// @brief A C++ interface for the various GLib utility functions.

#ifndef XFC_G_UTILS_HH
#define XFC_G_UTILS_HH

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __G_UTILS_H__
#include <glib/gutils.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {

/// @name Miscellaneous Utility Methods
/// @{

std::string get_user_name();
///< Gets the user name of the current user. 
///< @return The user name of the current user.
///<
///< The encoding of the returned string is system defined. On Unix, it might be
///< the preferred file name encoding, or something else, and there is no guarantee
///< that it is even consistent on a machine. On Windows, it is always UTF-8. 

std::string get_real_name();
///< Gets the real name of the user. 
///< @return The user's real name.
///<
///< This usually comes from the user's entry in the passwd file. The encoding of the 
///< returned string is system defined. (On Windows, it is, however, always UTF-8.)
///< If the real user name cannot be determined, the string "Unknown" is returned. 
 
std::string get_home_dir();
///< Gets the current user's home directory.
///< @return The current user's home directory.
///<
///< Note that in contrast to traditional Unix tools, this function prefers passwd
///< entries over the HOME environment variable. 

std::string get_tmp_dir();
///< Gets the directory to use for temporary files. 
///< @return The directory to use for temporary files.
///< 
///< This is found from inspecting the environment variables TMPDIR, TMP, and TEMP
///< in that order. If none of those are defined "/tmp" is returned on UNIX and 
///< "C:\" on Windows. The encoding of the returned string is system defined. On
///< Windows, it is always UTF-8. The return value is never null. 

std::string get_prgname();
///< Gets the name of the program. 
///< @return The name of the program.
///<
///< This name should NOT be localized, contrast with get_application_name(). 
///< If you are using libXFCui the program name is set in Main::init(). The 
///< program name is found by taking the last component of argv[0].
 
void set_prgname (const char *prgname);
void set_prgname (const std::string& prgname);
///< Sets the name of the program. 
///< @param prgname The name of the program.
///< 
///< This name should NOT be localized, contrast with set_application_name(). 
///< Note that for thread-safety reasons this function can only be called once.
 
String get_application_name();
///< Gets a human-readable name for the application, as set by set_application_name().
///< @return A human-readable application name (may return a null string).
///<
///< This name should be localized if possible, and is intended for display to the user.
///< Contrast with get_prgname(), which gets a non-localized name. If set_application_name()
///< has not been called, returns the result of get_prgname() (which may be null if 
///< set_prgname() has also not been called).

void set_application_name(const char *application_name);
void set_application_name(const String& application_name);
///< Sets a human-readable name for the application. 
///< @param application_name The localized name of the application. 
///<
///< This name should be localized if possible, and is intended for display to the user.
///< Contrast with set_prgname(), which sets a non-localized name. set_prgname() will be
///< called automatically by Main::init(), but set_application_name() will not. Note that
///< for thread safety reasons, this function can only be called once. The application name
///< will be used in contexts such as error messages, or when displaying an application's
///< name in the task list.

std::string get_user_data_dir();
///< Gets the base directory in which to access application data such as icons
///< that is customized for a particular user. 
///< @return The base directory string.
///< 
///< On Unix platforms this is determined using the mechanisms described in the
///< XDG Base Directory Specification.

std::string get_user_config_dir();
///< Gets the base directory in which to store user-specific application 
///< configuration information such as user preferences and settings.
///< @return The base directory string.
///<
///< On Unix platforms this is determined using the mechanisms described in the
///< XDG Base Directory Specification.

std::string get_user_cache_dir();
///< Gets the base directory in which to store non-essential, cached data specific to particular user.
///< @return The base directory string.
///<
///< On Unix platforms this is determined using the mechanisms described in the
///< XDG Base Directory Specification.

std::vector<std::string> get_system_data_dirs();
///< Gets an ordered list of base directories in which to access system-wide application data.
///< @return A vector of std::string holding the ordered list of base directories.
///<
///< On Unix platforms this is determined using the mechanisms described 
///< in the XDG Base Directory Specification.

std::vector<std::string> get_system_config_dirs();
///< Gets an ordered list of base directories in which to access system-wide configuration information.
///< @return A vector of std::string holding the list of base directories.
///<  
///< On Unix platforms this is determined using the mechanisms described
///< in the XDG Base Directory Specification

bool path_is_absolute(const gchar *file_name);
bool path_is_absolute(const std::string& file_name);
///< Determines whether the given <EM>file_name</EM> is an absolute file name.
///< @param file_name A file name. 
///< @return <EM>true</EM> if file_name is an absolute path.
///<
///< A file name is <EM>absolute</EM> if it contains a full path from the root directory
///< such as "/usr/local" on UNIX or "C:\windows" on Windows systems.
 
std::string path_skip_root(const char *file_name);
std::string path_skip_root(const std::string& file_name);
///< Gets a pointer into file_name after the root component, that is, after the
///< "/" in UNIX or "C:\' under Windows. 
///< @param file_name A file name. 
///< @return A pointer into file_name after the root component. 
///<
///< If <EM>file_name</EM> is not an absolute path it returns an empty string.

std::string get_current_dir();
///< Gets the current directory. 
///< @return The current directory.
///<
///< The encoding of the returned string is system defined. On Windows, it is always UTF-8. 

std::string path_get_basename(const char *file_name);
std::string path_get_basename(const std::string& file_name);
///< Gets the last component of the filename. 
///< @param file_name The name of the file. 
///< @return A string containing the last component of the filename.
///<
///< If <EM>file_name</EM> ends with a directory separator it gets the component
///< before the last slash. If <EM>file_name</EM> consists only of directory 
///< separators (and on Windows, possibly a drive letter), a single separator is
///< returned. If <EM>file_name</EM> is empty, "." is returned.

std::string path_get_dirname(const char *file_name);
std::string path_get_dirname(const std::string& file_name);
///< Gets the directory components of a file name. 
///< @param file_name The name of the file. 
///< @return The directory components of the file.
///<
///< If the file name has no directory components "." is returned.

std::string getenv(const char *variable);
std::string getenv(const std::string& variable);
///< Gets the value of an environment variable.
///< @param variable The environment variable to get. 
///< @return The value of the environment variable, or an empty string if <EM>variable</EM> is not found.
///<
///< The returned string may be overwritten by the next call to getenv(), setenv() or unsetenv().

bool setenv(const char *variable, const char *value, bool overwrite);
bool setenv(const std::string& variable, const std::string& value, bool overwrite);
///< Sets the value of an environment variable.
///< @param variable The environment variable to set, must not contain "=". 
///< @param value The value to set for the variable. 
///< @param overwrite Whether to change the variable if it already exists.
///< @return <EM>false</EM> if the environment variable couldn't be set.
///<
///< Note that on some systems, the memory used for the variable and its value can't be reclaimed.
 
void unsetenv(const char *variable);
void unsetenv(const std::string& variable);
///< Removes an environment variable from the environment. 
///< @param variable The environment variable to remove, must not contain "=". 
///<
///< Note that on some systems, the memory used for the variable and its value can't be reclaimed. 
///< Furthermore, this function can't be guaranteed to operate in a threadsafe way.

std::string find_program_in_path(const char *program);
std::string find_program_in_path(const std::string& program);
///< Locates the first executable named program in the user's path, in the same way that execvp() locates it.
///< @param program A program name.
///< @return A string with the absolute path name, or an empty string if the program is not found in the path.
///<
///< If program is already an absolute path, returns a copy of program if program exists
///< and is executable, and an empty string otherwise. On Windows, if program does not 
///< have a file type suffix, tries to append the suffixes in the PATHEXT environment
///< variable (if that doesn't exists, the suffixes .com, .exe, and .bat) in turn, and
///< then look for the resulting file name in the same way as CreateProcess() would. 
///< This means first in the directory where the program was loaded from, then in the
///< current directory, then in the Windows 32-bit system directory, then in the Windows
///< directory, and finally in the directories in the PATH environment variable. If the
///< program is found, the return value contains the full name including the type suffix.

std::string build_filename(const std::string& s1, const std::string& s2);
///< Creates a filename from 2 elements using the correct separator for filenames. 
///< @param s1 The first element in the filename. 
///< @param s2 The second element in the filename. 
///< @return The resulting filename.
///<
///< On Unix, this function behaves identically to G::build_path() with G_DIR_SEPARATOR_S
///< set as the separator. On Windows, it takes into account that either the backslash
///< "\" or slash "/" can be used as separator in filenames, but otherwise behaves as on
///< Unix. When file pathname separators need to be inserted, the one that last previously
///< occurred in the parameters (reading from left to right) is used. No attempt is made 
///< to force the resulting filename to be an absolute path. If the first element is a 
///< relative path, the result will be a relative path.

std::string build_filename(const std::string& s1, const std::string& s2, const std::string& s3);
///< Creates a filename from 3 elements using the correct separator for filenames 
///< (see build_filename(const std::string&, const std::string&).
///< @param s1 The first element in the filename. 
///< @param s2 The second element in the filename. 
///< @param s3 The third element in the filename. 
///< @return The resulting filename.

std::string build_filename(const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4);
///< Creates a filename from 4 elements using the correct separator for filenames
///< (see build_filename(const std::string&, const std::string&).
///< @param s1 The first element in the filename. 
///< @param s2 The second element in the filename. 
///< @param s3 The third element in the filename. 
///< @param s4 The fourth element in the filename.
///< @return The resulting filename.

std::string build_path(const std::string& separator, const std::string& s1, const std::string& s2);
///< Creates a path from 2 elements using <EM>separator</EM> as the separator between elements.
///< @param separator A string used to separator the elements of the path. 
///< @param s1 The first element in the path. 
///< @param s2 The second element in the path. 
///< @return The resulting path.
///< 
///< At the boundary between two elements, any trailing occurrences of separator in the first element,
///< or leading occurrences of separator in the second element are removed and exactly one copy of the
///< separator is inserted. Empty elements are ignored.
///< 
///< The number of leading copies of the separator on the result is the same as the number of leading
///< copies of the separator on the first non-empty element. The number of trailing copies of the 
///< separator on the result is the same as the number of trailing copies of the separator on the 
///< last non-empty element. (Determination of the number of trailing copies is done without stripping
///< leading copies, so if the separator is ABA, ABABA has 1 trailing copy.) 
///<
///< If there is only a single non-empty element, and there are no characters in that element not part
///< of the leading or trailing separators, then the result is exactly the original value of that element. 
///< Other than for determination of the number of leading and trailing copies of the separator, elements
///< consisting only of copies of the separator are ignored.

std::string build_path(const std::string& separator, const std::string& s1, const std::string& s2, const std::string& s3);
///< Creates a path from 3 elements using <EM>separator</EM> as the separator between elements
///< (see build_path(const std::string&, const std::string&, const std::string&).
///< @param separator A string used to separator the elements of the path. 
///< @param s1 The first element in the path. 
///< @param s2 The second element in the path. 
///< @param s3 The third element in the path. 
///< @return The resulting path.

std::string build_path(const std::string& separator, const std::string& s1, const std::string& s2, const std::string& s3, const std::string& s4);
///< Creates a path from 4 elements using <EM>separator</EM> as the separator between elements
///< (see build_path(const std::string&, const std::string&, const std::string&).
///< @param separator A string used to separator the elements of the path. 
///< @param s1 The first element in the path. 
///< @param s2 The second element in the path. 
///< @param s3 The third element in the path. 
///< @param s4 The fourth element in the path.
///< @return The resulting path.

/// @}

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/utils.inl>

#endif // XFC_G_UTILS_HH

