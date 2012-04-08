/* This program shows a preferences window, which contains radio buttons, 
 * a color selection widget, and a font selection widget.  It does manual
 * signal connection using libsigc++ slots, it pops up a (modal) window
 * to confirm whether the user really wants to exit, and it demonstrates
 * how to use pango markup.
 *
 * XFC translation of Example-4 from the "Developing with Gnome Tutorial, Copyright 2004" .
 */

#include "example-4.hh"
#include <iostream>

/*  ConfirmationDialog
 */

ConfirmationDialog::ConfirmationDialog(CObjectType *object, const Glade::Xml& xml)
: Gtk::Dialog(object)
{
	// Have the cancel button hide the confirmation window.
	Gtk::Button *button;
	xml.get_widget("CancelButton", button); 		
	if (button)
	{
		button->signal_clicked().connect(sigc::mem_fun(this, &Gtk::Widget::hide));
	}	
	
	// Have the "Exit anyway" button close everything.
	xml.get_widget("ExitButton", button); 		
	if (button)
	{
		button->signal_clicked().connect(sigc::ptr_fun(&Main::quit));
	}	

	// Get the warning label so we can modify it later.
	xml.get_widget("InfoLabel", warning_label); 		
	
	// Connect a slot to the "delete_event" to prevent the window manager closing the dialog.	
	signal_delete_event().connect(sigc::mem_fun(this, &ConfirmationDialog::on_delete_event));
		
	// Make the confirmation dialog start hidden.
	hide();
}

ConfirmationDialog::~ConfirmationDialog()
{
}

bool 
ConfirmationDialog::on_delete_event(const Gdk::EventAny& /*event*/)
{
	// Have the delete event (window close) do nothing.	
	return true;
}

void 
ConfirmationDialog::update_label(const char *font_name, const char *color, const char *location)
{	
	// Get the warning message, and find where we want to modify it.
	String message = warning_label->get_label();
	size_t end_span = message.rfind("span");	
	size_t beg_span = message.rfind("span", end_span - 1);	
	
	// Now, modify the string--namely the second span markup stuff.
	String s = String::format("span font_desc=\"%s\" foreground=\"%s\">%s</", font_name, color, location);
	message.replace(beg_span, end_span-beg_span, s);
		
	// Update the label
	warning_label->set_label(message);
}

/*  MainWindow
 */

MainWindow::MainWindow(CObjectType *object, const Glade::Xml& xml)
: Gtk::Window(object),
  location("undefined")
{
	// Get a pointers to the confirmation and font dialogs.
	xml.get_widget_derived("ConfirmClose", are_you_sure);
	xml.get_widget("FontSelection", font_sel); 
	
	// Keep track of when the location changes between "Here" and "There".
	Gtk::RadioButton *radio; 		
	xml.get_widget("Here", radio);
	if (radio)
	{
		radio->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &MainWindow::on_new_location_selected), radio));
	} 
	
	xml.get_widget("There", radio);
	if (radio)
	{
		radio->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &MainWindow::on_new_location_selected), radio));
	} 
	
	// Make "There" the default; note this also emits the toggled signal.
	radio->set_active(true);
	
	// Keep track of when the color changes.
	xml.get_widget("ColorSelection", color_sel);
	if (color_sel)
	{
		color_sel->signal_color_changed().connect(sigc::mem_fun(this, &MainWindow::on_new_color_selected));
	}
	
	// Set the default to whatever the ColorSelection widget defaults to.
	color = color_sel->get_current_color();
	
	// Turn off the opacity slider.
	color_sel->set_has_opacity_control(false);
	
	// Have the quit button show the confirmation window
	Gtk::Button *button; 		
	xml.get_widget("QuitButton", button);
	if (button)
	{
		button->signal_clicked().connect(sigc::mem_fun(this, &MainWindow::time_to_quit));
	}

	// Connect a slot to the "delete_event" that prevents the window manager closing the window.	
	signal_delete_event().connect(sigc::mem_fun(this, &MainWindow::on_delete_event));
}

MainWindow::~MainWindow()
{
	are_you_sure->dispose();
}

bool 
MainWindow::on_delete_event(const Gdk::EventAny& /*event*/)
{
	time_to_quit();	
	
	// Have the delete event (window close) do nothing.	
	return true;
}

void
MainWindow::on_new_location_selected(Gtk::RadioButton *button)
{
	// Copy the widget name to the location string.
	location = button->get_name();
}

void
MainWindow::on_new_color_selected()
{
	color = color_sel->get_current_color();
}

void
MainWindow::time_to_quit()
{
	// This makes the confirmation window pop up to ask the user if they really want to quit.
	// The message to the user changes slightly depending on the preferences they had set.

	// Create a color string of the form #RRGGBB, where R, G, & B are hex digits.
	String s = String::format("#%.2X%.2X%.2X", color.get_red()/256, color.get_green()/256, color.get_blue()/256);
	
	// Update the location string in the warning message with the user selected color and font.
	are_you_sure->update_label(font_sel->get_font_name().c_str(), s.c_str(), location.c_str());		
	
	// Make sure the confirmation window is shown
	are_you_sure->show();
}

int 
main (int argc, char *argv[])
{
	using namespace Main;
	
	// Initalize GTK+ first	
	init(&argc, &argv);
		
	// Create a Xml object from the file example-4.glade. 	
	Pointer<Glade::Xml> xml = Glade::Xml::create("example-4.glade");
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

