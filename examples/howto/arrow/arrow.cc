#include "arrow.hh"
#include <xfc/gtk/box.hh>

// ArrowButton

ArrowButton::ArrowButton(Gtk::ArrowType  arrow_type, Gtk::ShadowType shadow_type)
{
	// Create an Arrow widget with the specified parameters and pack it into the button.
	Gtk::Arrow *arrow = new Gtk::Arrow(arrow_type, shadow_type);
	add(*arrow);
}

ArrowButton::~ArrowButton()
{
}

// ArrowWindow

ArrowWindow::ArrowWindow()
{
	set_title("Arrow Buttons");
	set_border_width(10);

	// Create a box to hold the arrows/buttons
	Gtk::HBox *hbox = new Gtk::HBox;
	hbox->set_border_width(2);
	add(*hbox);

	// Pack and show all the widgets.
	ArrowButton *button = new ArrowButton(Gtk::ARROW_UP, Gtk::SHADOW_IN);
	hbox->pack_start(*button, false, false, 3);

	button = new ArrowButton(Gtk::ARROW_DOWN, Gtk::SHADOW_OUT);
	hbox->pack_start(*button, false, false, 3);

	button = new ArrowButton(Gtk::ARROW_LEFT, Gtk::SHADOW_ETCHED_IN);
	hbox->pack_start(*button, false, false, 3);

	button = new ArrowButton(Gtk::ARROW_RIGHT, Gtk::SHADOW_ETCHED_OUT);
	hbox->pack_start(*button, false, false, 3);
	hbox->show_all();
}

ArrowWindow::~ArrowWindow()
{
}

// Convenience macro for a simple main function

XFC_MAIN(ArrowWindow)

