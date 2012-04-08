/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  spawn.cc - A C++ interface for the GLib spawn functions.
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

#include "spawn.hh"
#include "error.hh"
#include <glib/gmem.h>
#include <glib/gshell.h>
#include <glib/gstrfuncs.h>
#include <cstring>

namespace Xfc {

namespace G {

/*  G::SpawnData
 */

struct SpawnData
{
	char *working_directory;
	char **argv;
	char **envp;
	GSpawnFlags flags;
};

/*  G::SpawnSyncData
 */

struct SpawnSyncData
{
	char *standard_output;
	char *standard_error;
	int exit_status;
};

} // namespace G

/*  G::Spawn
 */

namespace { // spawn_init

void spawn_init(G::SpawnData **data)
{
	*data = new G::SpawnData;
	memset(*data, 0, sizeof(G::SpawnData));
}

} // namespace

G::Spawn::Spawn(const std::vector<std::string>& argv, SpawnFlagsField flags)
{
	spawn_init(&data_);

	int count = argv.size();
	data_->argv = g_new0(char*, count + 1);

	int i = 0;
	while (i < count)
	{
		data_->argv[i] = const_cast<char*>(argv[i].c_str());
		++i;
	}

	data_->flags = (GSpawnFlags)flags;
}

G::Spawn::Spawn(const std::string& command_line, G::Error *error)
{
	spawn_init(&data_);
	g_shell_parse_argv(command_line.c_str(), 0, &data_->argv, *error);
	data_->flags = G_SPAWN_SEARCH_PATH;
}

G::Spawn::~Spawn()
{
	if (data_->working_directory)
		g_free(data_->working_directory);

	g_strfreev(data_->argv);
	g_strfreev(data_->envp);
	delete data_;
}

const char*
G::Spawn::get_working_directory() const
{
	return data_->working_directory;
}

char**
G::Spawn::get_argv() const
{
	return data_->argv;
}

char**
G::Spawn::get_envp() const
{
	return data_->envp;
}

GSpawnFlags
G::Spawn::get_flags() const
{
	return data_->flags;
}

void
G::Spawn::set_working_directory(const std::string& working_directory)
{
	if (data_->working_directory)
		g_free(data_->working_directory);

	data_->working_directory = g_strndup(working_directory.c_str(), working_directory.size());
}

void
G::Spawn::set_enviroment(std::vector<std::string>& envp)
{
	int count = envp.size();
	data_->envp = g_new0(char*, count + 1);

	int i = 0;
	while (i < count)
	{
		data_->envp[i] = const_cast<char*>(envp[i].c_str());
		++i;
	}
}

/*  G::SpawnAsync
 */

namespace { // spawn_async_init

void spawn_async_init(G::SpawnAsyncData **data)
{
	*data = new G::SpawnAsyncData;
	memset(*data, 0, sizeof(G::SpawnAsyncData));
}

} // namespace

G::SpawnAsync::SpawnAsync(const std::vector<std::string>& argv, SpawnFlagsField flags)
: Spawn(argv, flags)
{
	spawn_async_init(&data_);
}

G::SpawnAsync::SpawnAsync(const std::string& command_line, G::Error *error)
: Spawn(command_line, error)
{
	spawn_async_init(&data_);
}

G::SpawnAsync::~SpawnAsync()
{
	delete data_;
}

namespace { // spawn_child_setup_slot_callback

void spawn_child_setup_slot_callback(gpointer user_data)
{
	G::Spawn::ChildSetupSlot& slot = *static_cast<G::Spawn::ChildSetupSlot*>(user_data);
	slot();
}

} // namespace

bool
G::SpawnAsync::execute(G::Error *error)
{
	return g_spawn_async_with_pipes(get_working_directory(), get_argv(), get_envp(), get_flags(),
	                                0, 0, &data_->child_pid, 0, 0, 0, *error);
}

bool
G::SpawnAsync::execute(const ChildSetupSlot& slot, G::Error *error)
{
	ChildSetupSlot tmp_slot(slot);
	return g_spawn_async_with_pipes(get_working_directory(), get_argv(), get_envp(), get_flags(),
	                                &spawn_child_setup_slot_callback, &tmp_slot, &data_->child_pid,
					0, 0, 0, *error);
}

bool
G::SpawnAsync::execute(const ChildSetupSlot& slot, int *std_input , int *std_output, int *std_error, G::Error *error)
{
	ChildSetupSlot tmp_slot(slot);
	return g_spawn_async_with_pipes(get_working_directory(), get_argv(), get_envp(), get_flags(),
	                                &spawn_child_setup_slot_callback, &tmp_slot, &data_->child_pid,
	                                (get_flags() & G_SPAWN_CHILD_INHERITS_STDIN) ? 0 : std_input,
	                                (get_flags() & G_SPAWN_STDOUT_TO_DEV_NULL) ? 0 : std_output,
	                                (get_flags() & G_SPAWN_STDERR_TO_DEV_NULL) ? 0 : std_error, *error);
}

/*  G::SpawnSync
 */

namespace { // spawn_sync_init

void spawn_sync_init(G::SpawnSyncData **data)
{
	*data = new G::SpawnSyncData;
	memset(*data, 0, sizeof(G::SpawnSyncData));
}

} // namespace

G::SpawnSync::SpawnSync(const std::vector<std::string>& argv, SpawnFlagsField flags)
: Spawn(argv, flags)
{
	spawn_sync_init(&data_);
}

G::SpawnSync::SpawnSync(const std::string& command_line, G::Error *error)
: Spawn(command_line, error)
{
	spawn_sync_init(&data_);
}

G::SpawnSync::~SpawnSync()
{
	if (data_->standard_output)
		g_free(data_->standard_output);

	if (data_->standard_error)
		g_free(data_->standard_error);

	delete data_;
}

int
G::SpawnSync::exit_status() const
{
	return data_->exit_status;
}

std::string
G::SpawnSync::standard_output() const
{
	return std::string(data_->standard_output ? data_->standard_output : "");
}

std::string
G::SpawnSync::standard_error() const
{
	return std::string(data_->standard_error ? data_->standard_error : "");
}

bool
G::SpawnSync::execute(G::Error *error)
{
	return g_spawn_sync(get_working_directory(), get_argv(), get_envp(), get_flags(), 0, 0,
	                    (get_flags() & G_SPAWN_STDOUT_TO_DEV_NULL) ? 0 : &data_->standard_output,
	                    (get_flags() & G_SPAWN_STDERR_TO_DEV_NULL) ? 0 : &data_->standard_error,
			    &data_->exit_status, *error);
}

bool
G::SpawnSync::execute(const ChildSetupSlot& slot, G::Error *error)
{
	ChildSetupSlot tmp_slot(slot);
	return g_spawn_sync(get_working_directory(), get_argv(), get_envp(), get_flags(),
	                    &spawn_child_setup_slot_callback, &tmp_slot,
	                    (get_flags() & G_SPAWN_STDOUT_TO_DEV_NULL) ? 0 : &data_->standard_output,
	                    (get_flags() & G_SPAWN_STDERR_TO_DEV_NULL) ? 0 : &data_->standard_error,
			    &data_->exit_status, *error);
}

} // namespace Xfc

