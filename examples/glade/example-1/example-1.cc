/* This program displays a simple window and has a simple callback for when the OK button is clicked.
 *
 * XFC translation of Example-1 from the "Developing with Gnome Tutorial, Copyright 2004" .
 */

#include "example-1.hh"
#include <xfc/gtk/button.hh>
#include <iostream>

MainWindow::MainWindow(CObjectType *object, const Glade::Xml& xml)
: Gtk::Window(object)
{
	// Retrieve a pointer to the OK button and connect it to the ok_button_clicked() handler.	
	Gtk::Button *ok_button;
	xml.get_widget("OKButton", ok_button); 		
	if (ok_button)
	{
		ok_button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::ok_button_clicked));
	}	
}

void
MainWindow::ok_button_clicked()
{
	// Print a message to stdout and exit the program	
	std::cout << "Thanks for trying out my program." << std::endl;
	Main::quit();
}

int 
main (int argc, char *argv[])
{
	using namespace Main;
	
	// Initalize GTK+ first	
	init(&argc, &argv);
		
	// Create a Xml object from the file example-1.glade. 	
	Pointer<Glade::Xml> xml = Glade::Xml::create("example-1.glade");
	if (!xml)
		return 1;
	
	// Retrieve a pointer to the main window.	
	MainWindow *window;
	if (xml->get_widget_derived("MainWindow", window))
	{
		// Connect the main window's "destroy" signal to the quit() function.	
		window->signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
		
		// Show the main window.
		window->show();
		
		// Run the program
		run();
	}
	return 0;
}

