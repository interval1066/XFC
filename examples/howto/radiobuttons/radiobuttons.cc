#include "radiobuttons.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/separator.hh>
#include <iostream>

RadioButtonWindow::RadioButtonWindow()
{
	set_title("Radio Buttons");
	set_border_width(0);

	Gtk::VBox *box1 = new Gtk::VBox;
	add(*box1);
	box1->show();

	Gtk::VBox *box2 = new Gtk::VBox(false, 10);
	box2->set_border_width(10);
	box1->pack_start(*box2);
	box2->show();

	// When adding the first radio button to a group pass null for the group paramter.
	Gtk::RadioButton *radio_button = 0;
	radio_button = new Gtk::RadioButton(radio_button, "button1");
	radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &RadioButtonWindow::on_toggled), radio_button));
	box2->pack_start(*radio_button);
	radio_button->show();

	// Then, pass a pointer to a radio button already in the group to the constructor of the other buttons.
	radio_button = new Gtk::RadioButton(radio_button, "button2");
	radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &RadioButtonWindow::on_toggled), radio_button));
	radio_button->set_active(true);
	box2->pack_start(*radio_button);
	radio_button->show();

	radio_button = new Gtk::RadioButton(radio_button, "button3");
	radio_button->signal_toggled().connect(sigc::bind(sigc::mem_fun(this, &RadioButtonWindow::on_toggled), radio_button));
	box2->pack_start(*radio_button);
	radio_button->show();

	Gtk::HSeparator *separator = new Gtk::HSeparator;
	box1->pack_start(*separator, false);
	separator->show();

	box2 = new Gtk::VBox(false, 10);
	box2->set_border_width(10);
	box1->pack_start(*box2, false);
	box2->show();

	Gtk::Button *button = new Gtk::Button("close");
	button->signal_clicked().connect(sigc::mem_fun(this, &RadioButtonWindow::dispose));
	box2->pack_start(*button);
	button->set_flags(Gtk::CAN_DEFAULT);
	button->grab_default();
	button->show();
}

RadioButtonWindow::~RadioButtonWindow()
{
}

void 
RadioButtonWindow::on_toggled(const Gtk::RadioButton *button)
{
	if (button->get_active())
		std::cout << "Selected: radio " << button->get_label() << std::endl;
		
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	RadioButtonWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

