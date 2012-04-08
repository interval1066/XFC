#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <xfc/glib/thread.hh>
#include <xfc/glib/threadpool.hh>
#include <xfc/glib/rand.hh>
#include <iostream>

using namespace Xfc;

namespace {

G::StaticMutex mutex = XFC_STATIC_MUTEX_INIT;
unsigned long abs_thread_counter = 0;
unsigned long running_thread_counter = 0;
const int RUNS = 100;

void thread_pool_counter()
{
	mutex.lock();
	abs_thread_counter++;
	running_thread_counter++;
	mutex.unlock();

	G::usleep(G::random_int_range(0, 4000));

	mutex.lock();
	running_thread_counter--;
	mutex.unlock();
}

} // namespace

int main(int argc, char *argv[])
{
	// Only run the test, if threads are enabled and a default thread implementation is available.
	if (!G::Thread::supported())
	{
		G::Thread::init();

		std::cout << "Running thread test..." << std::endl;

		// ThreadPools can be created dynamically or on the stack. Here there created on the stack.
		// If you create them dynamically use a smart pointer so you don't have to call unref().
		G::ThreadPool pool1(3);
		G::ThreadPool pool2(5, true);
		G::ThreadPool pool3(7, true);

		for (int i = 0; i < RUNS; i++)
		{
			pool1.push(sigc::ptr_fun(&thread_pool_counter));
			pool2.push(sigc::ptr_fun(&thread_pool_counter));
			pool3.push(sigc::ptr_fun(&thread_pool_counter));

		}

		// You have to call free() to shut down a thread pool. At each free() call the program
		// waits for that thread pool to finish running all tasks before moving on to the next.
		pool1.free();
		pool2.free();
		pool3.free();

		if (RUNS * 3 == abs_thread_counter && running_thread_counter == 0)
			std::cout << "Thread test completed... OK!" << std::endl;
		else
			std::cout << "An error occurred during the thread test." << std::endl;
	}
	return 0;
}

