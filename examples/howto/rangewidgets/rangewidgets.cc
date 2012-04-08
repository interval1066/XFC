#include "rangewidgets.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/menu.hh>
#include <xfc/gtk/menuitem.hh>
#include <xfc/gtk/scrollbar.hh>
#include <xfc/gtk/separator.hh>

RangeWidgets::RangeWidgets()
{
	using namespace Gtk;

	set_title("Range Widgets");

	Box *box1 = new VBox;
	add(*box1);
	box1->show();

	Box *box2 = new HBox(false, 10);
	box2->set_border_width(10);
	box1->pack_start(*box2);
	box2->show();

	// Gtk::Adjustment args: value, lower, upper, step_increment, page_increment, page_size.
	// Note that the page_size value only makes a difference for scrollbar widgets, and the
	// highest value you'll get is actually (upper - page_size).
	adj1 = new Adjustment(0.0, 0.0, 101.0, 0.1, 1.0, 1.0);

	vscale = new VScale(*adj1);
	vscale->set_update_policy(UPDATE_CONTINUOUS);
	vscale->set_digits(1);
	vscale->set_value_pos(POS_TOP);
	vscale->set_draw_value(true);
	box2->pack_start(*vscale);
	vscale->show();

	Box *box3 = new VBox(false, 10);
	box2->pack_start(*box3);
	box3->show();

	// Reuse the same adjustment
	hscale = new HScale(*adj1);
	hscale->set_size_request(200, -1);
	hscale->set_update_policy(UPDATE_CONTINUOUS);
	hscale->set_digits(1);
	hscale->set_value_pos(POS_TOP);
	hscale->set_draw_value(true);
	box3->pack_start(*hscale);
	hscale->show();

	// Reuse the same adjustment again
	HScrollbar *scrollbar = new HScrollbar(*adj1);

	// Notice how this causes the scales to always be updated continuously when the scrollbar is moved
	scrollbar->set_update_policy(UPDATE_CONTINUOUS);
	box3->pack_start(*scrollbar);
	scrollbar->show();

	box2 = new HBox(false, 10);
	box2->set_border_width(10);
	box1->pack_start(*box2);
	box2->show();

	// A checkbutton to control whether the value is displayed or not
	check_button = new CheckButton("Display value on scale widgets");
	check_button->set_active(true);
	check_button->signal_toggled().connect(sigc::mem_fun(this, &RangeWidgets::on_draw_value));
	box2->pack_start(*check_button);
	check_button->show();

	box2 = new HBox(false, 10);
	box2->set_border_width(10);

	// An option menu to change the position of the value
	Label *label = new Label("Scale Value Position:");
	box2->pack_start(*label, false, false);
	label->show();

	// Gtk::ComboBoxText replaces GtkOptionMenu used in the corresponding GTK+ example.	
	Gtk::ComboBoxText *combobox = new Gtk::ComboBoxText;
	combobox->signal_changed().connect(sigc::bind(sigc::mem_fun(this, &RangeWidgets::on_pos_menu_select), combobox));
	combobox->append("Left");	
	combobox->append("Right");	
	combobox->append("Top");	
	combobox->append("Bottom");
	combobox->set_active(2);
	box2->pack_start(*combobox);
	combobox->show();
		
	box1->pack_start(*box2);
	box2->show();

	box2 = new HBox(false, 10);
	box2->set_border_width(10);

	// Second option menu, this time for the update policy of the scale widgets
	label = new Label("Scale Update Policy:");
	box2->pack_start(*label, false, false);
	label->show();

	// Gtk::ComboBoxText replaces GtkOptionMenu used in the corresponding GTK+ example.	
	combobox = new Gtk::ComboBoxText;
	combobox->signal_changed().connect(sigc::bind(sigc::mem_fun(this, &RangeWidgets::on_update_menu_select), combobox));
	combobox->append("Continuous");	
	combobox->append("Discontinuous");	
	combobox->append("Delayed");	
	combobox->set_active(0);
	box2->pack_start(*combobox);
	combobox->show();
	
	box1->pack_start(*box2);
	box2->show();
	
	box2 = new HBox(false, 10);
	box2->set_border_width(10);

	// An HScale widget for adjusting the number of digits on the sample scales.
	label = new Label("Scale Digits:");
	box2->pack_start(*label, false, false);
	label->show();

	Adjustment *adj2 = new Adjustment(1.0, 0.0, 5.0, 1.0, 1.0, 0.0);
	adj2->signal_value_changed().connect(sigc::bind(sigc::mem_fun(this, &RangeWidgets::on_digits_scale), adj2));
	HScale *scale = new HScale(*adj2);
	scale->set_digits(0);
	box2->pack_start(*scale);
	scale->show();

	box1->pack_start(*box2);
	box2->show();

	box2 = new HBox(false, 10);
	box2->set_border_width(10);

	// And, one last HScale widget for adjusting the page size of the scrollbar.
	label = new Label("Scrollbar Page Size:");
	box2->pack_start(*label, false, false);
	label->show();

	adj2 = new Adjustment(1.0, 1.0, 101.0, 1.0, 1.0, 0.0);
	adj2->signal_value_changed().connect(sigc::bind(sigc::mem_fun(this, &RangeWidgets::on_page_size), adj2));
	scale = new HScale(*adj2);
	scale->set_digits(0);
	box2->pack_start(*scale);
	scale->show();

	box1->pack_start(*box2);
	box2->show();

	HSeparator *separator = new HSeparator;
	box1->pack_start(*separator, false);
	separator->show();

	box2 = new VBox(false, 10);
	box2->set_border_width(10);
	box1->pack_start(*box2, false);
	box2->show();

	Gtk::Button *button = new Button("Quit");
	button->signal_clicked().connect(sigc::mem_fun(this, &RangeWidgets::dispose));
	box2->pack_start(*button);
	button->set_flags(Gtk::CAN_DEFAULT);
	button->grab_default();
	button->show();
}

RangeWidgets::~RangeWidgets()
{
}

void
RangeWidgets::on_draw_value()
{
	// Turn the value display on the scale widgets off or on depending on the state of the checkbutton
	hscale->set_draw_value(check_button->get_active());
	vscale->set_draw_value(check_button->get_active());
}

void
RangeWidgets::on_pos_menu_select(Gtk::ComboBox *combobox)
{
	Gtk::PositionType pos = static_cast<Gtk::PositionType>(combobox->get_active());	
	
	// Set the value position on both scale widgets
	hscale->set_value_pos(pos);
	vscale->set_value_pos(pos);
}

void
RangeWidgets::on_update_menu_select(Gtk::ComboBox *combobox)
{
	Gtk::UpdateType policy = static_cast<Gtk::UpdateType>(combobox->get_active());	
	
	// Set the update policy for both scale widgets
	hscale->set_update_policy(policy);
	vscale->set_update_policy(policy);
}

void
RangeWidgets::on_digits_scale(Gtk::Adjustment *adj)
{
	// Set the number of decimal places to which adj->value is rounded
	hscale->set_digits((int)adj->get_value());
	vscale->set_digits((int)adj->get_value());
}

void
RangeWidgets::on_page_size(Gtk::Adjustment *adj)
{
	// Set the page size and page increment size of the sample adjustment
	// to the value specified by the "Page Size" scale
	adj1->gtk_adjustment()->page_size = adj->get_value();
	adj1->gtk_adjustment()->page_increment = adj->get_value();

	// This sets the adjustment and makes it emit the "changed" signal to
	// reconfigure all the widgets that are attached to this signal.
	adj1->set_value(CLAMP(adj1->get_value(), adj1->lower(), (adj1->upper() - adj1->page_size())));
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	RangeWidgets window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

