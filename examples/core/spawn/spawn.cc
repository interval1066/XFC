// Simple G::SpawnedAsync example that spawns a child process that calls the touch
// program to create a text file called SPAWNED, in the current parent directory. If
// you remove the comment marks set_working_directory() will cause touch to create
// the file in your home directory. If you specify a directory that doesn't exist
// the child process will not be spawned and an error message will be generated. If
// successfully spawned, the child process id is printed to stdout.

#include <xfc/glib/spawn.hh>
#include <xfc/glib/error.hh>
#include <glib/gmessages.h>
#include <glib/gutils.h>
#include <iostream>

using namespace Xfc;

void child_setup_callback()
{
	std::cout << "Inside child process setup function...\n";
}

int main(int argc, char *argv[])
{
	using namespace std;	
	
	G::Error error;
	G::SpawnAsync child("touch SPAWNED", &error);

	if (error.get())
		cout << "G::SpawnAsync failed with the error message: " << error.message() << endl;
	else
	{
		//child.set_working_directory(g_get_home_dir());
		if (!child.execute(sigc::ptr_fun(&child_setup_callback), &error))
			cout << "Child process execution failed with the error message: " << error.message() << endl;
		else
			cout << "Child process successfully executed. The process id was " << child.child_pid() << endl;
	}
	return 0;
}

