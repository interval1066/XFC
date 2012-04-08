// This example is based on the POSIX thread examples in the book
// "Beginning Linux Programming" by Richard Stones and Neil Matthew.

#include <xfc/glib/thread.hh>
#include <iostream>

using namespace Xfc;

namespace {

String message("Simple Thread Test");

void
simple_thread()
{
	G::usleep(3);
	message.assign("thanks for the CPU time. Bye!");
}

} // namespace

int main (int argc, char *argv[])
{
	if (!G::Thread::supported())
		G::Thread::init();

	G::Thread *thread = G::Thread::create(sigc::ptr_fun(&simple_thread), true);
	if (!thread)
	{
		std::cout << "Thread creation failed" << std::endl;
		return 0;
	}

	std::cout << "Waiting for the second thread to finish..." << std::endl;
	thread->join();
	std::cout << "Thread joined, " << message << std::endl;
	return 0;
}

