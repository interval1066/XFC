// This example creates multiple threads and waits for each one to finish executing.

#include <xfc/glib/thread.hh>
#include <xfc/glib/timer.hh>
#include <iostream>
#include <vector>

using namespace Xfc;

namespace {

const int NUM_THREADS = 10;

void
muiltple_thread(int thread_number)
{
	std::cout << "Thread " << thread_number << " running..." << std::endl;

	// Sleep for thread_number seconds to verify G::Thread::join().
	G::usleep(G_USEC_PER_SEC / 5);

	std::cout << "Thread " << thread_number << " finished..." << std::endl;
}

} // namespace

int main (int argc, char *argv[])
{
	if (!G::Thread::supported())
		G::Thread::init();

	std::vector<G::Thread*> threads;

	// Create the threads
	for (int i = 0; i < NUM_THREADS; i++)
	{
		G::Thread *thread = G::Thread::create(sigc::bind<1>(sigc::ptr_fun(&muiltple_thread), i), true);
		if (!thread)
			std::cout << "Thread " << i << " creation failed" << std::endl;
		else
			threads.push_back(thread);
	}

	if (threads.empty())
		return 0;

	// Execute each thread in turn, until they're all finished.
	for (int i = 0; i < NUM_THREADS; i++)
	{
		threads[i]->join();
	}

	std::cout << "All threads have finished executing..." << std::endl;
	std::cout << "Thanks for the CPU time. Bye!" << std::endl;
	return 0;
}

