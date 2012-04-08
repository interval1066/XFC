#include "hellobuttons.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <iostream>

HelloButtons::HelloButtons()
{
	// This is a new call, which just sets the title of our new window to "Hello Buttons!"
	set_title("Hello Buttons");

	// Set the default size	of the window 
	set_default_size(200, -1);
	
	// Sets the border width of the window.
	set_border_width(10);

	// We create a box to pack widgets into. The box is not really visible, it is just used
	// as a tool to arrange widgets.
	Gtk::HBox *box = new Gtk::HBox;

	// Put the box into the main window.
	add(*box);

	// Creates a new button with the label "Button 1".
	Gtk::Button *button = new Gtk::Button("Button 1");

	// Now when the button is clicked, we call the slot function with a pointer to "button 1" bound to it.
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &HelloButtons::on_clicked), "button 1"));

	// Instead of Gtk::Container::add, we pack this button into the invisible box, which has been added to the window.
	box->pack_start(*button);

	// Always remember this step, this tells XFC that our preparation for this button is complete,
	// and it can now be displayed.
	button->show();

	// Do these same steps again to create a second button
	button = new Gtk::Button("Button 2");

	// Call the same slot function with a different argument, passing a pointer to "button 2" instead.
 	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &HelloButtons::on_clicked), "button 2"));
	box->pack_start(*button);

	// The order we show the buttons is not really important, but I recommend always showing the window last,
	// so it all pops up at once.
	button->show();
	box->show();
}

HelloButtons::~HelloButtons()
{
}

void
HelloButtons::on_clicked(const char *text)
{
	std::cout << "Hello again" << " - " << text << " " << "was pressed" << std::endl;
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	HelloButtons window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}
