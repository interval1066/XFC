/*  XFC threads example.
 *
 *  Based on the GTK threads example in the GTK+ FAQ sheet
 *  Copyright (C) 1999, Erik Mouw, <J.A.K.Mouwits.tudelft.nl>
 */

#include "thread.hh"
#include <xfc/glib/rand.hh>
#include <xfc/glib/thread.hh>
#include <cstdlib>

using namespace Xfc;

namespace {

G::StaticMutex mutex = XFC_STATIC_MUTEX_INIT;
const int YES_IT_IS = 1;
const int NO_IT_IS_NOT = 0;

} // namespace

volatile int Window::yes_or_no = YES_IT_IS;

Window::Window()
{
	set_title("Thread Example");
	set_border_width(10);

	// create a label
	label = new Gtk::Label("And now for something completely different ...");
	add(*label);
	label->show();

	// init random number generator
	G::random_set_seed((unsigned int)time(0));

	// create the threads
	G::Thread *thread = G::Thread::create(sigc::bind(sigc::mem_fun(this, &Window::on_argument), YES_IT_IS), false);
	thread = G::Thread::create(sigc::bind(sigc::mem_fun(this, &Window::on_argument), NO_IT_IS_NOT), false);

	show();
}

Window::~Window()
{
}

void
Window::on_argument(int what)
{
	bool say_something;

	for (;;)
	{
		// sleep for  while
		G::usleep((G::random_int() / (RAND_MAX / 3) + 1) * (G_USEC_PER_SEC / 2));

		// lock the yes_or_no_variable
		mutex.lock();

		// do we have to say something?
		say_something = (yes_or_no != what);

		if (say_something)
		{
			// set the variable
			yes_or_no = what;
		}

		// unlock the yes_or_no variable
		mutex.unlock();

		if (say_something)
		{
			// lock the GTK thread
			Gdk::Mutex::lock();

			// set the label text
			if(what == YES_IT_IS)
				label->set_text("Oh yes, it is!");
			else
				label->set_text("Oh no, it isn't!");

			// unlock the GTK thread
			Gdk::flush();
 			Gdk::Mutex::unlock();
		}
	}
}

int main (int argc, char *argv[])
{
	using namespace Main;

	// init thread support
	threads_init();

	// init GTK+
	init(&argc, &argv);

	// create a window
 	Window window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	// enter the main loop
	Gdk::Mutex::lock();
	run();
	Gdk::Mutex::unlock();

	return 0;
}

