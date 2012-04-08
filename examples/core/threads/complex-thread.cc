// This example is based on the POSIX thread examples in the book
// "Beginning Linux Programming" by Richard Stones and Neil Matthew.

#include <xfc/glib/thread.hh>
#include <iostream>

using namespace Xfc;

namespace {

G::StaticMutex mutex = XFC_STATIC_MUTEX_INIT;
bool time_to_exit = false;
std::string buffer;

void
static_mutex_thread()
{
	G::usleep(1);
	mutex.lock();
	while (buffer.compare(0, 3, "end") != 0)
	{
		std::cout << "You input " << buffer.length() << " characters" << std::endl;
		buffer.assign("");
		mutex.unlock();
		G::usleep(1);
		mutex.lock();
		while (buffer.empty())
		{
			mutex.unlock();
			G::usleep(1);
			mutex.lock();
		}
	}

	time_to_exit = true;
	buffer.assign("");
	mutex.unlock();
}

} // namespace

int main (int argc, char *argv[])
{
	if (!G::Thread::supported())
		G::Thread::init();

	G::Thread *thread = G::Thread::create(sigc::ptr_fun(&static_mutex_thread), true);
	if (!thread)
	{
		std::cout << "Thread creation failed" << std::endl;
		return 0;
	}

	mutex.lock();
	std::cout << "Input some text and press the Enter key. Enter 'end' to finish..." << std::endl;
	while (!time_to_exit)
	{
		std::getline(std::cin, buffer);
		mutex.unlock();
		while (1)
		{
			mutex.lock();
			if (!buffer.empty())
			{
				mutex.unlock();
				G::usleep(1);
			}
			else
				break;
		}
	}

	mutex.unlock();
	std::cout << "Waiting for the second thread to finish..." << std::endl;
	thread->join();
	std::cout << "Thread joined, thanks for the CPU time. Bye!" << std::endl;
	return 0;
}

