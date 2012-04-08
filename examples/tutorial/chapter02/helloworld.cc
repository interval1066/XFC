#include "helloworld.hh"
#include <xfc/gtk/button.hh>
#include <iostream>

HelloWorld::HelloWorld()
: Gtk::WidgetSignals(this)
{
	// Sets the title of the window
	set_title("Hello World");
	
	// Set the default size	of the window 
	set_default_size(200, -1);
	
	// Sets the border width of the window. 
	set_border_width(10);

	// Creates a new button with the label "Hello World".
	Gtk::Button *button = new Gtk::Button("Click me...");

	// When the button receives the "clicked" signal, it calls the on_hello() slot.
	button->signal_clicked().connect(sigc::mem_fun(this, &HelloWorld::on_hello));

	// This will cause the window to be destroyed by calling HelloWindow's inherited dispose method.
	button->signal_clicked().connect(sigc::mem_fun(this, &HelloWorld::dispose));

	// This packs the button into the window (a Gtk::Container).
	add(*button);

	// The final step is to display this newly created widget.
	button->show();
}

HelloWorld::~HelloWorld()
{
}

bool
HelloWorld::on_delete_event(const Gdk::EventAny& event)
{
	// When the window is given the "delete_event" signal (this is given by the window manager,
	// usually by the "close" option, or on the titlebar), the on_delete_event() slot is called.
	// If you return false a "destroy" signal is emitted. Returning true means you don't want
	// the window to be destroyed. This is useful for popping up 'are you sure you want to quit?'
	// type dialogs.
	std::cout << "delete event occurred" << '\n';
	return true;
}

void
HelloWorld::on_hello()
{
	std::cout << "Hello World" << std::endl;
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	HelloWorld window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

