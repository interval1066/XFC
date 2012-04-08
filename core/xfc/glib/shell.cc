/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  shell.cc - A C++ interface for the GLib shell-like commandline handling functions.
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

#include "shell.hh"
#include "error.hh"
#include <glib/gmem.h>
#include <glib/gmessages.h>
#include <glib/gstrfuncs.h>

using namespace Xfc;

/*  G::shell_quote
 */

String
G::shell_quote(const char *unquoted_string)
{
	char *quoted_string = g_shell_quote(unquoted_string);
	String s(quoted_string);
	g_free(quoted_string);
	return s;
}

String
G::shell_quote(const String& unquoted_string)
{
	return shell_quote(unquoted_string.c_str());

}

/*  G::shell_unquote
 */

String
G::shell_unquote(const char *quoted_string, G::Error *error)
{
	char *unquoted_string = g_shell_unquote(quoted_string, *error);
	String s(unquoted_string);
	g_free(unquoted_string);
	return s;
}

String
G::shell_unquote(const String& quoted_string, G::Error *error)
{
	return shell_unquote(quoted_string.c_str(), error);
}

/*  G::shell_parse_argv
 */

bool
G::shell_parse_argv(const char *command_line, std::vector<String>& args, G::Error *error)
{
	g_return_val_if_fail(args.empty(), false);
	int argcp = 0;
	char **argvp = 0;
	bool result = g_shell_parse_argv(command_line, &argcp, &argvp, *error);

	int i = 0;
	while (i < argcp)
	{
		args.push_back(argvp[i]);
		++i;
	}

	g_strfreev(argvp);
	return result;
}

bool
G::shell_parse_argv(const String& command_line, std::vector<String>& args, G::Error *error)
{
	return shell_parse_argv(command_line.c_str(), args, error);
}

