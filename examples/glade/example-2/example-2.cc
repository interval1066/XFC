/* This program displays a "pulsing" progress bar, adds a timeout function to keep
 * it updated, shows how to obtain an individual widget that libglade created, and
 * overrides the main window's "delete_event" signal handler so that a G::Timer can 
 * be attached to it to report the time wasted.
 *
 * XFC translation of Example-2 from the "Developing with Gnome Tutorial, Copyright 2004" .
 */

#include "example-2.hh"
#include <xfc/glib/main.hh>
#include <iostream>

WasteTimeWindow::WasteTimeWindow(CObjectType *object, const Glade::Xml& xml)
: Gtk::Window(object)
{
	// Connect a slot to the "delete_event" so we can calculate the time wasted.	
	signal_delete_event().connect(sigc::mem_fun(this, &WasteTimeWindow::on_delete_event));
	
	// Retrieve a pointer to the progress_bar and set it's activity mode to "pulse".	
	xml.get_widget("Progress Bar", progress_bar); 		
	if (progress_bar)
	{
		progress_bar->pulse();
	}

	// Add a timeout to update the progress bar every 100 milliseconds or so.
	timeout_connection = G::timeout_signal.connect(sigc::mem_fun(this, &WasteTimeWindow::on_timeout), 100);
	
	// Start the wasted_time_tracker timer, and connect it to the callback.
	wasted_time_tracker = new G::Timer();	
}

WasteTimeWindow::~WasteTimeWindow()
{
	// Don't forget to disconnect the timeout function.	
	timeout_connection.disconnect();
}

bool 
WasteTimeWindow::on_delete_event(const Gdk::EventAny& event)
{
	// Get the elapsed time since the timer was started.
	double time_elapsed = wasted_time_tracker->elapsed();	
	
	// Tell the user how much time they wasted.
	std::cout << "You wasted " << time_elapsed << " seconds with this program." << std::endl;
	
	// Stop the timer
	wasted_time_tracker->stop();
	
	// Return false to quit the program.
	return false;
}

bool
WasteTimeWindow::on_timeout()
{
	// Just pulse the progress bar back and forth.	
	progress_bar->pulse();

	// Return true so that the timeout function continues to get called (returning false removes the timeout). 
	return true;
}

int 
main (int argc, char *argv[])
{
	using namespace Main;
	
	// Initalize GTK+ first	
	init(&argc, &argv);
		
	// Create a Xml object from the file example-2.glade. 	
	Pointer<Glade::Xml> xml = Glade::Xml::create("example-2.glade");
	if (!xml)
		return 1;
	
	// Retrieve a pointer to the main window.	
	WasteTimeWindow *window;
	if (xml->get_widget_derived("WasteTimeWindow", window))
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

