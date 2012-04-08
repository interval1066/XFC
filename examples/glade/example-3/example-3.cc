/* This program displays a couple checkbuttons and shows how to change button labels,
 * how to make widgets sensitive or insensitive, how to determine if a checkbutton
 * is active, how to retrieve a widget pointer and connect it to a signal handler, and
 * how to manually get GTK+ to update widgets without returning to the main event loop.
 *
 * XFC translation of Example-3 from the "Developing with Gnome Tutorial, Copyright 2004" .
 */

#include "example-3.hh"
#include <xfc/gtk/label.hh>
#include <xfc/glib/main.hh>
#include <iostream>

#include <xfc-config.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

OptionWindow::OptionWindow(CObjectType *object, const Glade::Xml& xml)
: Gtk::Window(object)
{
	// Connect a slot to the "delete_event" that calls our quit function.	
	signal_delete_event().connect(sigc::mem_fun(this, &OptionWindow::on_delete_event));
	
	// Retrieve pointers to the two checkbuttons and connect the on_sensitivity_toggled() handler.	
	xml.get_widget("OohTellMe", ooh_tell_me); 		
	xml.get_widget("SensitivityCheckButton", sensitivity); 		
	if (ooh_tell_me && sensitivity)
	{
		sensitivity->signal_toggled().connect(sigc::mem_fun(this, &OptionWindow::on_sensitivity_toggled));
	}	
	
	// Retrieve a pointer to the quit_button and connect its "clicked" signal to the quit() handler. 	
	xml.get_widget("QuitButton", quit_button);
	if (quit_button)
	{
		quit_button->signal_clicked().connect(sigc::mem_fun(this, &OptionWindow::quit));
	}
}

bool 
OptionWindow::on_delete_event(const Gdk::EventAny& event)
{
	// Call our quit function.	
	quit();	
	
	// Return true to prevent the program quitting.
	return true;
}

void 
OptionWindow::on_sensitivity_toggled()
{
	// Set the sensitivity of the ooh_tell_me checkbutton.	
	ooh_tell_me->set_sensitive(sensitivity->get_active());
}		  

void
OptionWindow::quit()
{
	// If the user checked the OohTellMe button, we need to do some work.
	if (ooh_tell_me->get_active())
	{
		// Change the checkbutton's label
		ooh_tell_me->set_label("M_ock me");

		// Since we don't return to the main event loop, we have to manually tell GTK+
		// to process the label change (and any other changes that require processing).
		Pointer<G::MainContext> context = G::MainContext::get_default();
		while (context->iteration(false));

		// Mock the user and give them some time to notice the change
		std::cout << "Ha ha, you fell for it!  ";
		std::cout << "I will not tell you what that checkbutton does!" << std::endl;
		sleep (1);
	}
	Main::quit();
}

int 
main (int argc, char *argv[])
{
	using namespace Main;
	
	// Initalize GTK+ first	
	init(&argc, &argv);
		
	// Create a Xml object from the file example-3.glade. 	
	Pointer<Glade::Xml> xml = Glade::Xml::create("example-3.glade");
	if (!xml)
		return 1;
	
	// Retrieve a pointer to the main window.	
	OptionWindow *window;
	if (xml->get_widget_derived("OptionWindow", window))
	{
		// Show the main window.
		window->show();
		
		// Run the program
		run();
	}
	return 0;
}

