/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  spawn.cc - A C++ interface for the Gdk spawn functions.
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
#include "screen.hh"
#include "xfc/glib/error.hh"
#include <glib/gmem.h>
#include <glib/gmessages.h>
#include <glib/gshell.h>
#include <glib/gstrfuncs.h>
#include <cstring>

extern char **environ;

using namespace Xfc;

/*  Gdk::Spawn
 */

namespace { // spawn_init

void spawn_init(G::SpawnAsyncData **data)
{
	*data = new G::SpawnAsyncData;
	memset(*data, 0, sizeof(G::SpawnAsyncData));
}

} // namespace

Gdk::Spawn::Spawn(const std::vector<std::string>& argv, G::SpawnFlagsField flags)
: G::Spawn(argv, flags)
{
	spawn_init(&data_);
}

Gdk::Spawn::Spawn(const std::string& command_line, G::Error *error)
: G::Spawn(command_line, error)
{
	spawn_init(&data_);
}

Gdk::Spawn::~Spawn()
{
	delete data_;
}

namespace { // make_environment_for_screen (copied from gdkspawn-x11.c)

char**
make_environment_for_screen(GdkScreen *screen, char **envp)
{
	if (!envp)
		envp = environ;
	
	int env_len;	
	int display_index = -1;
	for (env_len = 0; envp[env_len]; env_len++)
	{
		if (strncmp(envp[env_len], "DISPLAY", strlen("DISPLAY")) == 0)
			display_index = env_len;
	}
	
	char **retval = g_new(char*, env_len + 1);
	retval[env_len] = 0;
	
	char *display_name = gdk_screen_make_display_name(screen);
	
	int i;	
	for (i = 0; i < env_len; i++)
	{
		if (i == display_index)
			retval[i] = g_strconcat("DISPLAY=", display_name, NULL);
		else
			retval[i] = g_strdup(envp[i]);
	}
	
	g_assert(i == env_len);
	g_free(display_name);
	return retval;
}

} //namespace

bool
Gdk::Spawn::execute(const Screen& screen, G::Error *error)
{
	char **new_envp = make_environment_for_screen(screen.gdk_screen(), get_envp());	
	bool result = g_spawn_async_with_pipes(get_working_directory(), get_argv(), new_envp, get_flags(),
	                                       0, 0, &data_->child_pid, 0, 0, 0, *error);
	g_strfreev(new_envp);
	return result;					       
}

namespace { // spawn_child_setup_slot_callback

void spawn_child_setup_slot_callback(gpointer user_data)
{
	G::Spawn::ChildSetupSlot& slot = *static_cast<G::Spawn::ChildSetupSlot*>(user_data);
	slot();
}

} // namespace

bool
Gdk::Spawn::execute(const Screen& screen, const ChildSetupSlot& slot, G::Error *error)
{
	char **new_envp = make_environment_for_screen(screen.gdk_screen(), get_envp());	
	ChildSetupSlot tmp_slot(slot);
	bool result = g_spawn_async_with_pipes(get_working_directory(), get_argv(), new_envp, get_flags(),
	                                       &spawn_child_setup_slot_callback, &tmp_slot, &data_->child_pid,
					       0, 0, 0, *error);
	g_strfreev(new_envp);
	return result;				       
}

bool
Gdk::Spawn::execute(const Screen& screen, const ChildSetupSlot& slot, int *std_input , int *std_output, int *std_error, G::Error *error)
{
	char **new_envp = make_environment_for_screen(screen.gdk_screen(), get_envp());	
	ChildSetupSlot tmp_slot(slot);
	bool result = g_spawn_async_with_pipes(get_working_directory(), get_argv(), new_envp, get_flags(),
	                                       &spawn_child_setup_slot_callback, &tmp_slot, &data_->child_pid,
	                                       (get_flags() & G_SPAWN_CHILD_INHERITS_STDIN) ? 0 : std_input,
	                                       (get_flags() & G_SPAWN_STDOUT_TO_DEV_NULL) ? 0 : std_output,
	                                       (get_flags() & G_SPAWN_STDERR_TO_DEV_NULL) ? 0 : std_error, *error);
	g_strfreev(new_envp);
	return result;				       
}

