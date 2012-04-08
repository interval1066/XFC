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

/// @file xfc/glib/spawn.hh
/// @brief A C++ interface for the GLib spawn functions.

#ifndef XFC_G_SPAWN_HH
#define XFC_G_SPAWN_HH

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef SIGCXX_SIGCXX_H
#include <sigc++/sigc++.h>
#endif

#ifndef __G_SPAWN_H__
#include <glib/gspawn.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

#ifndef _CPP_STRING
#include <string>
#endif

namespace Xfc {

namespace G {

class Error;
class SpawnData;
class SpawnSyncData;

/// @enum SpawnFlags
/// Specifies the flags that effect how a child process is spawned.

enum SpawnFlags
{
	SPAWN_LEAVE_DESCRIPTORS_OPEN = G_SPAWN_LEAVE_DESCRIPTORS_OPEN,
	///< The parent's open file descriptors will be inherited by the child;
	///< otherwise all descriptors except stdin/stdout/stderr will be closed
	///< before calling exec() in the child.

	SPAWN_DO_NOT_REAP_CHILD = G_SPAWN_DO_NOT_REAP_CHILD,
	///< The child will not be automatically reaped; you must call waitpid()
	///< or handle SIGCHLD yourself, or the child will become a zombie.

	SPAWN_SEARCH_PATH = G_SPAWN_SEARCH_PATH,
	///< argv[0] need not be an absolute path, it will be looked for in the user's PATH.

	SPAWN_STDOUT_TO_DEV_NULL = G_SPAWN_STDOUT_TO_DEV_NULL,
	///< The child's standard output will be discarded, instead of going
	///< to the same location as the parent's standard output.

	SPAWN_STDERR_TO_DEV_NULL = G_SPAWN_STDERR_TO_DEV_NULL,
	///< The child's standard error will be discarded.

	SPAWN_CHILD_INHERITS_STDIN = G_SPAWN_CHILD_INHERITS_STDIN,
	///< The child will inherit the parent's standard input (by default,
	///< the child's standard input is attached to /dev/null).

	SPAWN_FILE_AND_ARGV_ZERO = G_SPAWN_FILE_AND_ARGV_ZERO
	///< The first element of argv is the file to execute, while the remaining elements
	///< are the actual argument vector to pass to the file; Normally SpawnAsync uses
	///< argv[0] as the file to execute, and passes all of argv to the child.
};

/// SpawnFlagsField holds one or more bitflags from the G::SpawnFlags enumeration OR'd together.

typedef unsigned int SpawnFlagsField;

/// @class SpawnAsyncData spawn.hh xfc/glib/spawn.hh
/// @brief Internal data structure used by G::SpawnAsync and Gdk::Spawn.

struct SpawnAsyncData
{
	GPid child_pid;
};

/// @class Spawn spawn.hh xfc/glib/spawn.hh
/// @brief A C++ interface for the GLib spawn functions.
///
/// Rather than wrap the GLib spawn functions individually XFC wraps these
/// functions into two easy to use classes: SpawnAsync and SpawnSync.
/// SpawnAync executes a child program asynchronously (your program will
/// not block waiting for the child to exit) and SpawnSync executes a child
/// synchronously (your program waits for the child to exit before returning).
///
/// Spawn is just a convenient base class that implements the code common to
/// both SpawnAsync and SpawnSync. It derives from StackObject so you can only
/// create SpawnAsync and SpawnSync on the stack. Spawn has only two public
/// methods that can be called: set_working_directory() and set_enviroment().
/// You call set_working_directory() to set the child's current working
/// directory and you call set_enviroment() to set the child's environment. If
/// you call neither of these methods the child will inherit its parent's
/// working directory and enviroment.

class Spawn : public StackObject, protected sigc::trackable
{
	Spawn(const Spawn&);
	Spawn& operator=(const Spawn&);

	SpawnData *data_;

protected:
/// @name Constructors
/// @{

	Spawn(const std::vector<std::string>& argv, SpawnFlagsField flags);
	///< Constructs an asynchronous spawn object with the specified arguments <EM>argv</EM>
	///< and spawn <EM>flags</EM>.
	///< @param argv A reference to a vector of std::string that holds the argument strings.
	///< @param flags The G::SpawnFlags to set.

	Spawn(const std::string& command_line, G::Error *error);
	///< Constructs a new spawn object with the specified arguments in the <EM>command_line</EM> string.
	///< @param command_line A command line.
	///< @param error The return location for a G::Error.
	///<
	///< This method sets the G_SPAWN_SEARCH_PATH flags and unsets all others.

	virtual ~Spawn();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	const char* get_working_directory() const;
	///< Returns the current working directory, or null.

	char** get_argv() const;
	///< Returns a pointer to the argument array to pass to the child, or null.

	char** get_envp() const;
	///< Returns a pointer to the enviroment array to pass to the child, or null.

	GSpawnFlags get_flags() const;
	///< Returns the flags to pass to the child process spawned

/// @}

public:
	typedef sigc::slot<void> ChildSetupSlot;
	///< Signature of the callback slot to be called after GLib has performed
	///< all the setup it plans to perform but before calling exec().
	///<
	///< <B>Example:</B> Method signature for ChildSetupSlot.
	///< @code
	///< void method();
	///< @endcode
	///<
	///< Obviously, actions taken in this method will only affect the child,
	///< not the parent.

/// @name Methods
/// @{

	void set_working_directory(const std::string& working_directory);
	///< Sets the child's current working directory.
	///< @param working_directory The working directory to set.
	///<
	///< If not specifically set a child will inherit its parent's working directory.

	void set_enviroment(std::vector<std::string>& envp);
	///< Sets the child's enviroment.
	///< @param envp A reference to a vector of std::string that holds the child's enviroment strings.
	///<
	///< Each string in the vector must has the form KEY=VALUE. This will become
	///< the child's environment. If not specifically set a child will inherit its
	///< parent's enviroment.

/// @}
/// @name Methods
/// @{

	static void close_pid(GPid pid);
	///< Closes the process identified by <EM>pid</EM>. 
	///< @param pid The process identifier to close.
	///<
	///< On some platforms, notably WIN32, the GPid type represents a resource 
	///< which must be closed to prevent resource leaking. close_pid() is provided
	///< for this purpose. It should be used on all platforms, even though it doesn't
	///< do anything under UNIX.

/// @}
};

/// @class SpawnAsync spawn.hh xfc/glib/spawn.hh
/// A C++ interface for the GLib asynchronous spawn functions.
///
/// SpawnAsync executes a child program asynchronously (that is, your program will not
/// block waiting for the child to exit). The child program is specified by the only
/// argument that must be provided, argv. argv should be a vector of std::strings, to
/// be passed as the argument vector for the child. The first string in argv is of
/// course the name of the program to execute. By default, the name of the program
/// must be a full path; the PATH shell variable will only be searched if you pass the
/// G::SPAWN_SEARCH_PATH flag. The first constructor takes an argv as a parameter and
/// one or more optional spawn flags. The second constructor creates the argv argument
/// for you from the passed in command line.
///
/// SpawnFlagsField should be the bitwise OR of any flags you want to affect the child's
/// behavior. On Unix, the G::SPAWN_DO_NOT_REAP_CHILD means that the child will not be
/// automatically reaped; you must call waitpid() or handle SIGCHLD yourself, or the
/// child will become a zombie. On Windows, the flag means that a handle to the child
/// will be returned child_pid. You must call CloseHandle() on it eventually (or exit
/// the process), or the child processs will continue to take up some table space even
/// after its death. Quite similar to zombies on Unix, actually.
///
/// G::SPAWN_LEAVE_DESCRIPTORS_OPEN means that the parent's open file descriptors will
/// be inherited by the child; otherwise all descriptors except stdin/stdout/stderr
/// will be closed before calling exec() in the child. G::SPAWN_SEARCH_PATH means that
/// argv[0] need not be an absolute path, it will be looked for in the user's PATH.
/// G::SPAWN_STDOUT_TO_DEV_NULL means that the child's standard output will be discarded,
/// instead of going to the same location as the parent's standard output. If you use
/// this flag, set_standard_output() is ignored. G::SPAWN_STDERR_TO_DEV_NULL means that
/// the child's standard error will be discarded, instead of going to the same location as
/// the parent's standard error. If you use this flag, set_standard_error() will be ignored.
/// G::SPAWN_CHILD_INHERITS_STDIN means that the child will inherit the parent's standard
/// input (by default, the child's standard input is attached to /dev/null). If you use
/// this flag, set_standard_input() will be ignored. G::SPAWN_FILE_AND_ARGV_ZERO means that
/// the first element of argv is the file to execute, while the remaining elements are the
/// actual argument vector to pass to the file. Normally SpawnAsync uses argv[0] as the
/// file to execute, and passes all of argv to the child.
///
/// ChildSetupSlot is a user-defined method. On POSIX platforms, the method is called in
/// the child after GLib has performed all the setup it plans to perform (including
/// creating pipes, closing file descriptors, etc.) but before calling exec(). That is,
/// the ChildSetupSlot is called just before calling exec() in the child. Obviously
/// actions taken in this method will only affect the child, not the parent. On Windows,
/// there is no separate fork() and exec() functionality. Child processes are created and
/// run right away with one API call, CreateProcess(). The ChildSetupSlot is called in
/// the parent process just before creating the child process. You should carefully consider
/// what you do in the ChildSetupSlot method if you intend your software to be portable to
/// Windows.
///
/// The process_id() method returns the child's process ID. You can use the process ID to
/// send signals to the child, or to waitpid() if you specified the G::SPAWN_DO_NOT_REAP_CHILD
/// flag. On Windows, child_pid will be filled with a handle to the child process only if
/// you specified the G::SPAWN_DO_NOT_REAP_CHILD flag. You can then access the child process
/// using the Win32 API, for example wait for its termination with the WaitFor*() functions,
/// or examine its exit code with GetExitCodeProcess(). You should close the handle with
/// CloseHandle() when you no longer need it.
///
/// A G::Error should be passed to execute() to report errors but can be null to ignore them.
/// If the G::Error is set, execute() returns false. Errors are reported even if they occur
/// in the child (for example if the executable in argv[0] is not found). Typically the
/// message field of returned errors should be displayed to users. Possible errors are those
/// from the G_SPAWN_ERROR domain. If an error occurs the standard_input, standard_output,
/// and standard_error file descriptors will not be filled with valid values, and process_id()
/// will return zero.
///
/// <B>Example:</B> A simple way to spawn an asynchronous child process.
/// @code
/// G::Error error;
/// SpawnAsync child(command_line, &error);
/// if (error.get())
/// {
/// 	// handle error
/// }
/// else
/// {
/// 	if (!child.execute(&error))
/// 	{
///		// handle error
/// 	}
/// }
/// @endcode

class SpawnAsync : public Spawn
{
	SpawnAsync(const SpawnAsync&);
	SpawnAsync& operator=(const SpawnAsync&);

	SpawnAsyncData *data_;

public:
/// @name Constructors
/// @{

	SpawnAsync(const std::vector<std::string>& argv, SpawnFlagsField flags = 0);
	///< Constructs an asynchronous spawn object with the specified arguments <EM>argv</EM>
	///< and spawn <EM>flags</EM>.
	///< @param argv A reference to a vector of std::string that holds the child's argument strings.
	///< @param flags One or more bitflags from the G::SpawnFlags enumeration.
	///<
	///< The first string in argv (argv[0]) is of course the name of the program to
	///< execute. By default, the name of the program must be a full path; the PATH shell
	///< variable will only be searched if you pass the G::SPAWN_SEARCH_PATH flag.

	SpawnAsync(const std::string& command_line, G::Error *error);
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
	
	~SpawnAsync();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GPid child_pid() const;
	///< Returns the child process ID or zero if an error occurs.
	///< @return The child process ID.

/// @}
/// @name Methods
/// @{

	bool execute(G::Error *error = 0);
	///< Executes a child program asynchronously (that is, your program
	///< will not block waiting for the child to exit).
	///< @param error The return location for a G::Error, or null to ignore errors.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if error is set.

	bool execute(const ChildSetupSlot& slot, G::Error *error = 0);
	///< Executes a child program asynchronously (that is, your program
	///< will not block waiting for the child to exit).
	///< @param slot A sigc::slot to call in the child just before exec().
	///< @param error The return location for a G::Error, or null to ignore errors.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if error is set.

	bool execute(const ChildSetupSlot& slot, int *std_input , int *std_output, int *std_error, G::Error *error = 0);
	///< Executes a child program asynchronously (that is, your program
	///< will not block waiting for the child to exit).
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

/// @class SpawnSync spawn.hh xfc/glib/spawn.hh
/// A C++ interface for the GLib synchronous spawn functions.
///
/// SpawnSync executes a child synchronously (that is, waits for the child to exit before
/// returning). All output from the child is stored in standard_output and standard_error,
/// if those parameters are set. If exit_status is set, the exit status of the child is
/// stored there as it would be returned by waitpid(); standard UNIX macros such as WIFEXITED()
/// and WEXITSTATUS() must be used to evaluate the exit status. If an error occurs, no data is
/// returned in standard_output, standard_error, or exit_status.
///
/// G::SPAWN_STDOUT_TO_DEV_NULL means that the child's standard output will be discarded,
/// instead of going to the same location as the parent's standard output. If you use
/// this flag, set_standard_output() is ignored. G::SPAWN_STDERR_TO_DEV_NULL means that
/// the child's standard error will be discarded, instead of going to the same location as
/// the parent's standard error. If you use this flag, set_standard_error() will be ignored.
/// Do not set the G::SPAWN_DO_NOT_REAP_CHILD flag on a SpawnSync object. If you do execute()
/// will fail and return false.
///
/// <B>Example:</B> A simple way to spawn a synchronous child process.
/// @code
/// G::Error error;
/// SpawnSync child(command_line, &error);
/// if (error.get())
/// {
/// 	// handle error.
/// }
/// else
/// {
/// 	if (!child.execute(&error))
/// 	{
///		// handle error
/// 	}
/// }
/// @endcode
///
/// See SpawnAsync for more details.

class SpawnSync : public Spawn
{
	SpawnSync(const SpawnSync&);
	SpawnSync& operator=(const SpawnSync&);

	SpawnSyncData *data_;

public:
/// @name Constructors
/// @{

	SpawnSync(const std::vector<std::string>& argv, SpawnFlagsField flags = 0);
	///< Constructs a synchronous spawn object with the specified arguments <EM>argv</EM>
	///< and spawn <EM>flags</EM>.
	///< @param argv A reference to a vector of std::string that holds the child's argument strings.
	///< @param flags One or more bitflags from the G::SpawnFlags enumeration.
	///<
	///< The first string in argv (argv[0]) is of course the name of the program to
	///< execute. By default, the name of the program must be a full path; the PATH shell
	///< variable will only be searched if you pass the G::SPAWN_SEARCH_PATH flag.

	SpawnSync(const std::string& command_line, G::Error *error);
	///< Constructs a synchronous spawn object with the specified arguments in
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

	virtual ~SpawnSync();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	int exit_status() const;
	///< Returns the exit status of the child, as returned by waitpid().
	///< @return The exit status.

	std::string standard_output() const;
	///< Returns the child output as a std::string.
	///< @return A std::string.
	///<
	///< If an error occurs the return string will be empty.

	std::string standard_error() const;
	/// Returns any child error messages as a std::string.
	///< @return A std::string.
	///<
	///< If an error occurs the return string will be empty.

/// @}
/// @name Methods
/// @{

	bool execute(G::Error *error = 0);
	///< Executes a child program synchronously (that is, waits for the child to exit before returning).
	///< @param error The return location for a G::Error, or null to ignore errors.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if error is set.

	bool execute(const ChildSetupSlot& slot, G::Error *error = 0);
	///< Executes a child program synchronously (that is, waits for the child to exit before returning).
	///< @param slot A sigc::slot to call in the child just before exec().
	///< @param error The return location for a G::Error, or null to ignore errors.
	///< @return <EM>true</EM> if successful, <EM>false</EM> if error is set.

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/spawn.inl>

#endif // XFC_G_SPAWN_HH

