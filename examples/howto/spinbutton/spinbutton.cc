#include "spinbutton.hh"
#include <xfc/gtk/adjustment.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/frame.hh>

SpinButtonWindow::SpinButtonWindow()
{
	set_title("Spin Button");

	Gtk::VBox *main_vbox = new Gtk::VBox(false, 5);
	main_vbox->set_border_width(10);
	add(*main_vbox);
  
	Gtk::Frame *frame = new Gtk::Frame("Not accelerated");
	main_vbox->pack_start(*frame);
  
	Gtk::VBox *vbox = new Gtk::VBox;
	vbox->set_border_width(5);
	frame->add(*vbox);

	// Day, month, year spinners
	Gtk::HBox *hbox = new Gtk::HBox;
	vbox->pack_start(*hbox, true, true, 5);

	Gtk::VBox *vbox2 = new Gtk::VBox;
	hbox->pack_start(*vbox2, true, true, 5);
  
	Gtk::Label *label = new Gtk::Label("Day :");
	label->set_alignment(0, 0.5);
	vbox2->pack_start(*label, false);
  
	Gtk::Adjustment *adj = new Gtk::Adjustment(1.0, 1.0, 31.0, 1.0, 5.0, 0.0);
	Gtk::SpinButton *spinner = new Gtk::SpinButton(adj, 0, 0);
	spinner->set_wrap(true);
	vbox2->pack_start(*spinner, false);
  
	vbox2 = new Gtk::VBox;
	hbox->pack_start(*vbox2, true, true, 5);

	label = new Gtk::Label("Month :");
	label->set_alignment(0, 0.5);
	vbox2->pack_start(*label, false);
  
	adj = new Gtk::Adjustment(1.0, 1.0, 12.0, 1.0, 5.0, 0.0);
	spinner = new Gtk::SpinButton(adj, 0, 0);
	spinner->set_wrap(true);
	vbox2->pack_start(*spinner, false);
  
	vbox2 = new Gtk::VBox;
	hbox->pack_start(*vbox2, true, true, 5);

	label = new Gtk::Label("Year :");
	label->set_alignment(0, 0.5);
	vbox2->pack_start(*label, false);
  
	adj = new Gtk::Adjustment(1998.0, 0.0, 2100.0, 1.0, 100.0, 0.0);
	spinner = new Gtk::SpinButton(adj, 0, 0);
	spinner->set_wrap(false);
	spinner->set_size_request(55, -1);
	vbox2->pack_start(*spinner, false);

	frame = new Gtk::Frame("Accelerated");
	main_vbox->pack_start(*frame);
  
	vbox = new Gtk::VBox;
	set_border_width(5);
	frame->add(*vbox);
  
	hbox = new Gtk::HBox;
	vbox->pack_start(*hbox, false, true, 5);

	vbox2 = new Gtk::VBox;
	hbox->pack_start(*vbox2, true, true, 5);

	label = new Gtk::Label("Value :");
	label->set_alignment(0, 0.5);
	vbox2->pack_start(*label, false);

	adj = new Gtk::Adjustment(0.0, -10000.0, 10000.0, 0.5, 100.0, 0.0);
	spinner1 = new Gtk::SpinButton(adj, 1.0, 2);
	spinner1->set_wrap(true);
	spinner1->set_size_request(100, -1);
	vbox2->pack_start(*spinner1, false);

	vbox2 = new Gtk::VBox;
	hbox->pack_start(*vbox2, true, true, 5);

	label = new Gtk::Label("Digits :");
	label->set_alignment(0, 0.5);
	vbox2->pack_start(*label, false);

	adj = new Gtk::Adjustment(2, 1, 5, 1, 1, 0);
	Gtk::SpinButton *spinner2 = new Gtk::SpinButton(adj, 0.0, 0);
	spinner2->set_wrap(true);
	spinner2->signal_value_changed().connect(sigc::bind(sigc::mem_fun(this, &SpinButtonWindow::on_change_digits), spinner2));
	vbox2->pack_start(*spinner2, false);

	hbox = new Gtk::HBox;
	vbox->pack_start(*hbox, false, true, 5);

	Gtk::CheckButton *check_button = new Gtk::CheckButton("Snap to 0.5-ticks");
	check_button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &SpinButtonWindow::on_toggle_snap), check_button));
	vbox->pack_start(*check_button);
	check_button->set_active(true);

	check_button = new Gtk::CheckButton("Numeric only input mode");
	check_button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &SpinButtonWindow::on_toggle_numeric), check_button));
	vbox->pack_start(*check_button);
	check_button->set_active(true);

	hbox = new Gtk::HBox;
	vbox->pack_start(*hbox, false, true, 5);
	
	Gtk::Button *button = new Gtk::Button("Value as Int");
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &SpinButtonWindow::on_get_value), true));
	hbox->pack_start(*button, true, true, 5);

	button = new Gtk::Button("Value as Float");
	button->signal_clicked().connect(sigc::bind(sigc::mem_fun(this, &SpinButtonWindow::on_get_value), false));
	hbox->pack_start(*button, true, true, 5);

	val_label = new Gtk::Label("0");
	vbox->pack_start(*val_label);

	hbox = new Gtk::HBox;
	main_vbox->pack_start(*hbox, false);

	button = new Gtk::Button("Close");
	button->signal_clicked().connect(sigc::mem_fun(this, &SpinButtonWindow::dispose));
	hbox->pack_start(*button, true, true, 5);

	show_all();
}

SpinButtonWindow::~SpinButtonWindow()
{
}

void
SpinButtonWindow::on_change_digits(Gtk::SpinButton *spin)
{
	spinner1->set_digits(spin->get_value_as_int());
}

void
SpinButtonWindow::on_toggle_snap(Gtk::CheckButton *button)
{
	spinner1->set_snap_to_ticks(button->get_active());
}

void
SpinButtonWindow::on_toggle_numeric(Gtk::CheckButton *button)
{
	spinner1->set_numeric(button->get_active());
}

void
SpinButtonWindow::on_get_value(bool value_as_int)
{
	String text;
	
	if (value_as_int)
		text = String::format("%d", spinner1->get_value_as_int());
	else
		text = String::format("%0.*f", spinner1->get_digits(), spinner1->get_value());

	val_label->set_text(text);
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	SpinButtonWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}

