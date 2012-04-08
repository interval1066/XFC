#include "eventbox.hh"
#include <xfc/gtk/eventbox.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gdk/window.hh>

EventBoxWindow::EventBoxWindow()
{
	set_title("Event Box");
	set_border_width(10);

	// Create an EventBox and add it to our toplevel window
	Gtk::EventBox *event_box = new Gtk::EventBox;
	add(*event_box);
	event_box->show();

	// Create a long label
	Gtk::Label *label = new Gtk::Label("Click here to quit, quit, quit, quit, quit");
	event_box->add(*label);
	label->show();

	// Clip it short
	label->set_size_request(110, 20);

	// And bind an action to it
	event_box->set_events(Gdk::BUTTON_PRESS_MASK);
	event_box->signal_button_press_event().connect(sigc::mem_fun(this, &EventBoxWindow::on_button_press_event));

	// Yet one more thing you need an X window for ...
	event_box->realize();
	hand_cursor = new Gdk::Cursor(GDK_HAND1);
	event_box->get_window()->set_cursor(*hand_cursor);
	show();
}

EventBoxWindow::~EventBoxWindow()
{
}

bool
EventBoxWindow::on_button_press_event(const Gdk::EventButton&)
{
	dispose();
	return true;
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	EventBoxWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}

