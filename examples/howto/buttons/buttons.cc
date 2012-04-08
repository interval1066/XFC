#include "buttons.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/image.hh>
#include <xfc/gtk/label.hh>
#include <iostream>

// ButtonWindow

ButtonWindow::ButtonWindow()
{
	set_title("Image Button!");
	set_border_width(10);

	// Create an image from an XPM file	
	Gtk::Image *image = new Gtk::Image("info.xpm");
	
	// Create a new button
	Gtk::Button *button = new Gtk::Button(*image, "cool button", false);
	
	add(*button);
	button->show();
}

ButtonWindow::~ButtonWindow()
{
}

void
ButtonWindow::on_clicked()
{
	std::cout << "Hello again - cool button was pressed" << std::endl;
}

int main(int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	ButtonWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

