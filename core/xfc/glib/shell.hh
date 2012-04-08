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

/// @file xfc/glib/shell.hh
/// @brief A C++ interface for the GLib shell functions.
///
/// Provides A C++ interface for the GLib shell-like commandline handling functions.

#ifndef XFC_G_SHELL_HH
#define XFC_G_SHELL_HH

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef __G_SHELL_H__
#include <glib/gshell.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace G {

class Error;

/// @name Shell Methods
/// @{

String shell_quote(const char *unquoted_string);
String shell_quote(const String& unquoted_string);
///< Quotes a string so that the shell (/bin/sh) will interpret
///< the quoted string to mean unquoted_string.
///< @param unquoted_string A literal string
///< @return The quoted string.
///<
///< If you pass a filename to the shell, for example, you should first quote
///< it with this function. The quoting style used is undefined (single or double
///< quotes may be used).

String shell_unquote(const char *quoted_string, G::Error *error = 0);
String shell_unquote(const String& quoted_string, G::Error *error = 0);
///< Unquotes a string as the shell (/bin/sh) would.
///< @param quoted_string A shell-quoted string.
///< @param error The return location for a G::Error, or null.
///< @return An unquoted string.
///<
///< Only handles quotes; if a string contains file globs, arithmetic operators,
///< variables, backticks, redirections, or other special-to-the-shell features, the
///< result will be different from the result a real shell would produce (the
///< variables, backticks, etc. will be passed through literally instead of being
///< expanded). This method is guaranteed to succeed if applied to the result of
///< shell_quote(). If it fails, it returns a null String and sets the error. The
///< quoted_string need not actually contain quoted or escaped text; shell_unquote()
///< simply goes through the string and unquotes/unescapes anything that the shell
///< would. Both single and double quotes are handled, as are escapes including
///< escaped newlines. Possible errors are in the G_SHELL_ERROR domain.
///<
///< Shell quoting rules are a bit strange. Single quotes preserve the literal string
///< exactly. Escape sequences are not allowed; not even \' - if you want a ' in the
///< quoted text, you have to do something like 'foo'\''bar'. Double quotes allow
///< $, `, ", \, and newline to be escaped with backslash. Otherwise double quotes
///< preserve things literally.

bool shell_parse_argv(const char *command_line, std::vector<String>& args, G::Error *error = 0);
bool shell_parse_argv(const String& command_line, std::vector<String>& args, G::Error *error = 0);
///< Parses a command line into an argument vector, in much the same way the
///< shell would, but without many of the expansions the shell would perform
///< (variable expansion, globs, operators, filename expansion, and the like
///< are not supported).
///< @param command_line A command line to parse.
///< @param args A reference to a vector of String to hold the argument strings.
///< @param error The return location for a G::Error, or null.
///< @return <EM>true</EM> on success, <EM>false</EM> if error was set.
///<
///< The results are defined to be the same as those you would get from a
///< UNIX98 /bin/sh, as long as the input contains none of the unsupported shell
///< expansions. If the input does contain such expansions, they are passed
///< through literally. Possible errors are those from the G_SHELL_ERROR domain.

/// @}

} // namespace G

} // namespace Xfc

#endif // XFC_G_SHELL_HH

