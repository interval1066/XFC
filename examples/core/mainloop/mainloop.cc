/*  G::MainLoop test program. This program is a direct translation of the C test program mainloop-test.c
 *  in the GLib source test directory. The code is not meant to be a good example of C++ programming.
 *  Instead its only purpose is to demonstrate that the G::MainContext, G::MainLoop and G:Source classes
 *  do work correctly.
 */

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include "mainloop.hh"
#include <xfc/glib/rand.hh>
#include <xfc/utfstring.hh>
#include <glib.h>
#include <glib/gutils.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>
#include <cerrno>
#include <cstdio>

#include <xfc-config.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef G_OS_WIN32
#include <fcntl.h> // For _O_BINARY used by pipe() macro
#include <io.h>    // for _pipe()
#endif

namespace {

const unsigned int NTHREADS = 4;
const int ITERS = 10000;
const int INCREMENT = 10;
const int NCRAWLERS = 4;
const int RECURSER_TIMEOUT = 50;
const int CRAWLER_TIMEOUT_RANGE = 40;

std::vector<G::MainContext*> context_list;
G::Mutex *context_list_mutex;
G::Condition *context_list_condition;

std::vector<G::Source*> crawler_list;
G::StaticMutex crawler_list_mutex = XFC_STATIC_MUTEX_INIT;

} // namespace

struct AddrData
{
	G::MainLoop *loop;
	G::IOChannel *dest;
	int count;
};

struct TestData
{
	int current_val;
	int iters;
	G::IOChannel *in;
};

/*  MainLoopTest
 */

MainLoopTest::MainLoopTest()
{
	context_list_mutex = new G::Mutex;
	context_list_condition = new G::Condition;
}

MainLoopTest::~MainLoopTest()
{
	delete context_list_mutex;
	delete context_list_condition;
}

void
MainLoopTest::create_adder_thread()
{
	G::IOChannel *in_channels[2];
	G::IOChannel *out_channels[2];

	io_pipe(in_channels);
	io_pipe(out_channels);

	G::IOChannel **sub_channels = new G::IOChannel*[2];
	sub_channels[0] = in_channels[0];
	sub_channels[1] = out_channels[1];

	G::Error error;
	G::Thread::create(sigc::bind(sigc::mem_fun(this, &MainLoopTest::adder_thread), sub_channels), false, &error);
	if (error.get())
	{
		std::cout << "Cannot create thread: " << error.message() << std::endl;
		exit (1);
	}

	TestData *test_data = new TestData;
	test_data->in = in_channels[1];
	test_data->current_val = 0;
	test_data->iters = ITERS;

	G::io_signal.connect(*(out_channels[0]), G::IO_IN | G::IO_HUP, sigc::bind(sigc::ptr_fun(&adder_response), out_channels[0], test_data));
	do_add(test_data->in, test_data->current_val, INCREMENT);
}

void
MainLoopTest::adder_thread(G::IOChannel **channels)
{
	G::MainContext *context = new G::MainContext;
	context->ref();
	context_list_mutex->lock();
	context_list.push_back(context);
	if (context_list.size() == NTHREADS)
		context_list_condition->broadcast();
	context_list_mutex->unlock();

	AddrData addr_data;
	addr_data.dest = channels[1];
	addr_data.loop = new G::MainLoop(*context);
	addr_data.count = 0;

	G::IOConditionField condition = G::IO_IN | G::IO_HUP;
	G::IOSource *adder_source = new G::IOSource(*(channels[0]), condition, sigc::bind(sigc::ptr_fun(&adder_callback), channels[0], &addr_data));
	adder_source->attach(context);
	adder_source->unref();

	G::TimeoutSource *timeout_source = new G::TimeoutSource(sigc::bind(sigc::ptr_fun(&timeout_callback), &addr_data), 10);
	timeout_source->attach(context);
	timeout_source->unref();

	addr_data.loop->run();

	channels[0]->unref();
	channels[1]->unref();
	delete channels;
	addr_data.loop->unref();

	std::cout << "Timeout run " << addr_data.count << " times" << std::endl;
	context_list_mutex->lock();

	std::vector<G::MainContext*>::iterator i = std::find(context_list.begin(), context_list.end(), context);
	if (i != context_list.end())
	{
		context_list.erase(i);
	}

	if (context_list.size() == 0)
		quit();

	context_list_mutex->unlock();
	cleanup_crawlers (context);
}

bool
MainLoopTest::adder_response(G::IOConditionField condition, G::IOChannel *channel, TestData *test_data)
{
	char result[32];

	if (!read_all(channel, result, 32))
		return false;

	test_data->current_val = atoi(result);
	test_data->iters--;

	if (test_data->iters == 0)
	{
		if (test_data->current_val != ITERS * INCREMENT)
		{
			g_print("Addition failed: %d != %d\n", test_data->current_val, ITERS * INCREMENT);
			exit (1);
		}

		channel->unref();
		test_data->in->unref();
		delete test_data;
		return false;
	}

	do_add(test_data->in, test_data->current_val, INCREMENT);
	return true;
}

bool
MainLoopTest::adder_callback(G::IOConditionField condition, G::IOChannel *channel, AddrData *addr_data)
{
	char buffer1[32];
	char buffer2[32];
	char result[32];

	if (!read_all(channel, buffer1, 32) || !read_all(channel, buffer2, 32))
	{
		addr_data->loop->quit();
  		return false;
	}

	sprintf (result, "%d", atoi(buffer1) + atoi(buffer2));
	write_all(addr_data->dest, result, 32);
	return true;
}

bool
MainLoopTest::timeout_callback(AddrData *addr_data)
{
	addr_data->count++;
	return true;
}

void
MainLoopTest::io_pipe(G::IOChannel **channels)
{
	int fds[2];

	if (pipe(fds) < 0)
	{
		std::cout << "Cannot create pipe " << g_strerror(errno) << std::endl;
		exit(1);
	}

	channels[0] = G::IOChannel::create(fds[0], true).release();
	channels[1] = G::IOChannel::create(fds[1], true).release();
}

void
MainLoopTest::do_add(G::IOChannel *in, int a, int b)
{
	char buffer1[32];
	char buffer2[32];

	sprintf(buffer1, "%d", a);
	sprintf(buffer2, "%d", b);

	write_all(in, buffer1, 32);
	write_all(in, buffer2, 32);
}

void
MainLoopTest::create_crawler()
{
	G::TimeoutSource *source = new G::TimeoutSource(G::random_int_range(0, CRAWLER_TIMEOUT_RANGE));
	source->connect(sigc::bind(sigc::ptr_fun(&crawler_callback), source));
	crawler_list_mutex.lock();
	crawler_list.push_back(source);
	context_list_mutex->lock();
	source->attach(context_list[g_random_int_range(0, context_list.size())]);
	context_list_mutex->unlock();
	crawler_list_mutex.unlock();
}

int
MainLoopTest::crawler_callback(G::Source* source)
{
	crawler_list_mutex.lock();

	std::vector<G::Source*>::iterator i = std::find(crawler_list.begin(), crawler_list.end(), source);
	if (i != crawler_list.end())
	{
		crawler_list.erase(i);
	}
	else
		remove_crawler();

	remove_crawler();
	crawler_list_mutex.unlock();
	create_crawler();
	create_crawler();
	return false;
}

void
MainLoopTest::cleanup_crawlers(G::MainContext *context)
{
	crawler_list_mutex.lock();

	std::vector<G::Source*>::iterator i = crawler_list.begin();
	while (i != crawler_list.end())
	{
		if ((*i)->is_attached(*context))
		{
			(*i)->destroy();
			crawler_list.erase(i);
			break;
		}
		++i;
	}
	crawler_list_mutex.unlock();
}


void
MainLoopTest::remove_crawler()
{
	if (crawler_list.size() > 0)
	{
		G::Source *other_source = crawler_list[g_random_int_range (0, crawler_list.size())];
		std::vector<G::Source*>::iterator i = std::find(crawler_list.begin(), crawler_list.end(), other_source);
		if (i != crawler_list.end())
		{
			(*i)->destroy();
			crawler_list.erase(i);
		}
	}
}

bool
MainLoopTest::recurser_idle(G::MainContext *context)
{
	for (int i = 0; i < 10; i++)
		context->iteration(false);
	return false;
}

bool
MainLoopTest::recurser_start()
{
	context_list_mutex->lock();
	G::MainContext *context = context_list[G::random_int_range(0, context_list.size())];
	G::IdleSource *source = new G::IdleSource(sigc::bind(sigc::ptr_fun(&recurser_idle), context));
	source->attach(context);
	source->unref();
	context_list_mutex->unlock();
	return true;
}

bool
MainLoopTest::read_all(G::IOChannel *channel, char *buffer, gsize length)
{
	gsize bytes_read = 0;
	gsize count;

	while (bytes_read < length)
	{
		GIOError error = g_io_channel_read(channel->g_io_channel(), buffer + bytes_read, length - bytes_read, &count);
		if (error)
		{
			if (error != G_IO_ERROR_AGAIN)
					return false;
		}
		else if (count == 0)
		{
			return false;
		}

		bytes_read += count;
	}
	return true;
}

bool
MainLoopTest::write_all(G::IOChannel *channel, char *buffer, gsize length)
{
	gsize bytes_written = 0;
	gsize count;

	while (bytes_written < length)
	{
		GIOError error = g_io_channel_write(channel->g_io_channel(), buffer + bytes_written, length - bytes_written, &count);
		if (error && error != G_IO_ERROR_AGAIN)
		{
			return false;
		}
		bytes_written += count;

	}
	return true;
}

int main(int argc, char *argv[])
{
// Only run the test, if threads are enabled and a default thread implementation is available.
#if defined(G_THREADS_ENABLED) && ! defined(G_THREADS_IMPL_NONE)

	if (!G::Thread::supported())
		G::Thread::init();

	MainLoopTest main_loop;

	for (unsigned int i = 0; i < NTHREADS; i++)
		main_loop.create_adder_thread();

	// Wait for all threads to start
	context_list_mutex->lock();

	if (context_list.size() < NTHREADS)
		context_list_condition->wait(*context_list_mutex);

	context_list_mutex->unlock();

	for (int i = 0; i < NCRAWLERS; i++)
		main_loop.create_crawler();

	G::timeout_signal.connect(sigc::ptr_fun(&MainLoopTest::recurser_start), RECURSER_TIMEOUT);
	main_loop.run();

#endif
	return 0;
}

