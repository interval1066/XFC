/*  XFC: Xfce Foundation Classes (User Interface Library)
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

/// @file xfc/gdk/spawn.hh
/// @brief A C++ interface for the Gdk spawn functions.

#ifndef XFC_GDK_SPAWN_HH
#define XFC_GDK_SPAWN_HH

#ifndef XFC_G_SPAWN_HH
#include <xfc/glib/spawn.hh>
#endif

namespace Xfc {

namespace Gdk {

class Screen;

/// @class Spawn spawn.hh xfc/gdk/spawn.hh
/// @brief A C++ interface for the Gdk spawn functions.
///
/// Spawn executes a child program asynchronously like G::SpawnAsync except the child
/// process is spawned in such an environment that on calling Gdk::Display::open() it
/// would be returned a Gdk::Display with screen as the default screen. For more details
/// see the G::SpawnAsync class documentation.

class Spawn : public G::Spawn
{
	Spawn(const Spawn&);
	Spawn& operator=(const Spawn&);

	G::SpawnAsyncData *data_;

public:
/// @name Constructors
/// @{

	Spawn(const std::vector<std::string>& argv, G::SpawnFlagsField flags = 0);
	///< Constructs an asynchronous spawn object with the specified arguments <EM>argv</EM>
	///< and spawn <EM>flags</EM>.
	///< @param argv A reference to a vector of std::string that holds the child's argument strings.
	///< @param flags One or more bitflags from the G::SpawnFlags enumeration.
	///<
	///< The first string in argv (argv[0]) is of course the name of the program to
	///< execute. By default, the name of the program must be a full path; the PATH shell
	///< variable will only be searched if you pass the G::SPAWN_SEARCH_PATH flag.

	Spawn(const std::string& command_line, G::Error *error);
	///< Constructs an asynchronous spawn object with the specified arguments in
	///< the <EM>command_line</EM> string.
	///< @param command_line The command line string.
	///< @param error The return location for a G::Error.
	///<
	///< This constructor parses <EM>command line</EM> with g_shell_parse_argv() and passes
	///< it to GLib. If an error occurs it is set by the parsing function, and can be any of
	///< those from the G_SHELL_ERROR domain. Runs a <EM>command_line</EM> in the background.
	///< Unlike then other constructor, the G::SPAWN_SEARCH_PATH flag is enabled, other flags
	///< are not. Note that G::SPAWN_SEARCH_PATH can have security implications, so consider
	///< using the other constructor if appropriate.

	~Spawn();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GPid child_pid() const;
	///< Returns the child process ID or zero if an error occurs.

/// @}
/// @name Methods
/// @{

	bool execute(const Screen& screen, G::Error *error = 0);
	///< Executes a child program asynchronously (that is, your program
	///< will not block waiting for the child to exit).
	///< @param screen A Gdk::Screen.
	///< @param error The return location for a G::Error, or null to ignore errors.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if error is set.

	bool execute(const Screen& screen, const ChildSetupSlot& slot, G::Error *error = 0);
	///< Executes a child program asynchronously (that is, your program
	///< will not block waiting for the child to exit).
	///< @param screen A Gdk::Screen.
	///< @param slot A sigc::slot to call in the child just before exec().
	///< @param error The return location for a G::Error, or null to ignore errors.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if error is set.

	bool execute(const Screen& screen, const ChildSetupSlot& slot, int *std_input , int *std_output, int *std_error, G::Error *error = 0);
	///< Executes a child program asynchronously (that is, your program
	///< will not block waiting for the child to exit).
	///< @param screen A Gdk::Screen.
	///< @param slot A sigc::slot to call in the child just before exec().
	///< @param std_input The return location for the file descriptor to write to child's stdin.
	///< @param std_output The return location for the file descriptor to read child's stdout.
	///< @param std_error The return location for the file descriptor to read child's stderr.
	///< @param error The return location for a G::Error, or null to ignore errors.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if error is set.
	///<
	///< The file descriptors <EM>std_input</EM>, <EM>std_output</EM>, and <EM>std_error</EM>
	///< are used for writing to the child's standard input or reading from its standard output
	///< or standard error, and must be closed by calling close() when no longer required.
	///<
	///< If <EM>std_input</EM> is null the child's standard input is attached to /dev/null
	///< unless G::SPAWN_CHILD_INHERITS_STDIN is set. If <EM>std_error</EM> is null the
	///< child's standard error goes to the same location as the parent's standard error unless
	///< G::SPAWN_STDERR_TO_DEV_NULL is set. If <EM>std_output</EM> is not called the child's
	///< standard output goes to the same location as the parent's standard output unless
	///< G::SPAWN_STDOUT_TO_DEV_NULL is set.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#endif // XFC_GDK_SPAWN_HH

