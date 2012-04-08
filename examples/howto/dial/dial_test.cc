#include <xfc/main.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/window.hh>
#include <cstdio>
#include <cstdlib>
#include "dial.hh"

using namespace Xfc;

class DialTest : public Gtk::Window
{
	Gtk::Adjustment *adjustment;
	Gtk::Label *label;

protected:
	void on_adjustment_value_changed();

public:
	DialTest();
	virtual ~DialTest();
};

DialTest::DialTest()
{
	set_title("Dial");
	set_border_width(10);

	Gtk::VBox *vbox = new Gtk::VBox(false, 5);
	add(*vbox);
	vbox->show();

	Gtk::Frame *frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);
	vbox->add(*frame);
	frame->show();

	adjustment = new Gtk::Adjustment(0, 0, 100, 0.01, 0.1, 0);
	Gtk::Dial *dial = new Gtk::Dial(adjustment);
	dial->set_update_policy(Gtk::UPDATE_DELAYED);

	frame->add(*dial);
	dial->show();

	label = new Gtk::Label("0.00");
	vbox->pack_end(*label, false, false);
	label->show();

	adjustment->signal_value_changed().connect(sigc::mem_fun(this, &DialTest::on_adjustment_value_changed));
	show();
}

DialTest::~DialTest()
{
}

void
DialTest::on_adjustment_value_changed()
{
	String buffer = String::format("%4.2f", adjustment->get_value());
	label->set_text(buffer);
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	DialTest window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}

