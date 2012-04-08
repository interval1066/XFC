#include "buttonbox.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/stockid.hh>

// ButtonBoxFrame

ButtonBoxFrame::ButtonBoxFrame(bool horizontal, const char *title, int spacing, Gtk::ButtonBoxStyle layout)
{
	set_label(title);

	Gtk::ButtonBox *bbox;
	if (horizontal)
		bbox = new Gtk::HButtonBox;
	else
		bbox = new Gtk::VButtonBox;

	bbox->set_border_width(5);
	add(*bbox);
	bbox->set_layout(layout);
	bbox->set_spacing(spacing);

	Gtk::Button *button = new Gtk::Button(Gtk::StockId::OK);
	bbox->add(*button);
  
	button = new Gtk::Button(Gtk::StockId::CANCEL);
	bbox->add(*button);

	button = new Gtk::Button(Gtk::StockId::HELP);
	bbox->add(*button);
}

ButtonBoxFrame::~ButtonBoxFrame()
{
}

// ButtonBoxWindow

ButtonBoxWindow::ButtonBoxWindow()
{
	set_title("Button Boxes");
	set_border_width(10);

	Gtk::VBox *main_vbox = new Gtk::VBox;
	add(*main_vbox);

	// Horizontal Button Boxes
	Gtk::Frame *frame = new Gtk::Frame("Horizontal Button Boxes");
	main_vbox->pack_start(*frame, true, true, 10);

	Gtk::Box *box = new Gtk::VBox;
	box->set_border_width(10);
	frame->add(*box);
    
	ButtonBoxFrame *button_box_frame = new ButtonBoxFrame(true, "Spread (spacing 40)", 40, Gtk::BUTTONBOX_SPREAD);
	box->pack_start(*button_box_frame);
	button_box_frame = new ButtonBoxFrame(true, "Edge (spacing 30)", 30, Gtk::BUTTONBOX_EDGE);
	box->pack_start(*button_box_frame, true, true, 5);
	button_box_frame = new ButtonBoxFrame(true, "Start (spacing 20)", 20, Gtk::BUTTONBOX_START);
	box->pack_start(*button_box_frame, true, true, 5);
	button_box_frame = new ButtonBoxFrame(true, "End (spacing 10)", 10, Gtk::BUTTONBOX_END);
	box->pack_start(*button_box_frame, true, true, 5);

	// Vertical Button Boxes
	frame = new Gtk::Frame("Vertical Button Boxes");
	main_vbox->pack_start(*frame, true, true, 10);

	box = new Gtk::HBox;
	box->set_border_width(10);
	frame->add(*box);

	button_box_frame = new ButtonBoxFrame(false, "Spread (spacing 5)", 5, Gtk::BUTTONBOX_SPREAD);
	box->pack_start(*button_box_frame);
	button_box_frame = new ButtonBoxFrame(false, "Edge (spacing 30)", 30, Gtk::BUTTONBOX_EDGE);
	box->pack_start(*button_box_frame, true, true, 5);
	button_box_frame = new ButtonBoxFrame(false, "Start (spacing 20)", 20, Gtk::BUTTONBOX_START);
	box->pack_start(*button_box_frame, true, true, 5);
	button_box_frame = new ButtonBoxFrame(false, "End (spacing 20)", 20, Gtk::BUTTONBOX_END);
	box->pack_start(*button_box_frame, true, true, 5);

	show_all();
}

ButtonBoxWindow::~ButtonBoxWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	ButtonBoxWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}


