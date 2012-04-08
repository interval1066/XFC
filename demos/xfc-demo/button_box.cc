/* Button Boxes
 *
 * The Button Box widgets are used to arrange buttons with padding.
 */

#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/buttonbox.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/stockid.hh>

using namespace Xfc;

class ButtonBoxFrame : public Gtk::Frame
{
public:
	ButtonBoxFrame(bool horizontal, const char *title, int spacing, Gtk::ButtonBoxStyle layout);
	~ButtonBoxFrame();
};

class ButtonBoxWindow : public Gtk::Window
{
public:
	ButtonBoxWindow();
	~ButtonBoxWindow();
};
//!

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
    
	ButtonBoxFrame *button_box_frame = new ButtonBoxFrame(true, "Spread", 40, Gtk::BUTTONBOX_SPREAD);
	box->pack_start(*button_box_frame);
	button_box_frame = new ButtonBoxFrame(true, "Edge", 40, Gtk::BUTTONBOX_EDGE);
	box->pack_start(*button_box_frame, true, true, 5);
	button_box_frame = new ButtonBoxFrame(true, "Start", 40, Gtk::BUTTONBOX_START);
	box->pack_start(*button_box_frame, true, true, 5);
	button_box_frame = new ButtonBoxFrame(true, "End", 40, Gtk::BUTTONBOX_END);
	box->pack_start(*button_box_frame, true, true, 5);

	// Vertical Button Boxes
	frame = new Gtk::Frame("Vertical Button Boxes");
	main_vbox->pack_start(*frame, true, true, 10);

	box = new Gtk::HBox;
	box->set_border_width(10);
	frame->add(*box);

	button_box_frame = new ButtonBoxFrame(false, "Spread", 30, Gtk::BUTTONBOX_SPREAD);
	box->pack_start(*button_box_frame);
	button_box_frame = new ButtonBoxFrame(false, "Edge", 30, Gtk::BUTTONBOX_EDGE);
	box->pack_start(*button_box_frame, true, true, 5);
	button_box_frame = new ButtonBoxFrame(false, "Start", 30, Gtk::BUTTONBOX_START);
	box->pack_start(*button_box_frame, true, true, 5);
	button_box_frame = new ButtonBoxFrame(false, "End", 30, Gtk::BUTTONBOX_END);
	box->pack_start(*button_box_frame, true, true, 5);

	show_all();
}

ButtonBoxWindow::~ButtonBoxWindow()
{
}

Gtk::Window*
do_button_box(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new ButtonBoxWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}





