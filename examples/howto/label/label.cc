#include "label.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/label.hh>

LabelWindow::LabelWindow()
{
	set_title("Label");
	Gtk::VBox *vbox = new Gtk::VBox(false, 5);
	Gtk::HBox *hbox = new Gtk::HBox(false, 5);
	add(*hbox);
	hbox->pack_start(*vbox, false, false);
	set_border_width(5);

	Gtk::Frame *frame = new Gtk::Frame("Normal Label");
	Gtk::Label *label = new Gtk::Label("This is a Normal label");
	frame->add(*label);
	vbox->pack_start(*frame, false, false);

	frame = new Gtk::Frame("Multi-line Label");
	label = new Gtk::Label("This is a Multi-line label.\nSecond line\nThird line");
	frame->add(*label);
	vbox->pack_start(*frame, false, false);

	frame = new Gtk::Frame("Left Justified Label");
	label = new Gtk::Label("This is a Left-Justified\n Multi-line label.\nThird line");
	label->set_justify(Gtk::JUSTIFY_LEFT);
	frame->add(*label);
	vbox->pack_start(*frame, false, false);

	frame = new Gtk::Frame("Right Justified Label");
	label = new Gtk::Label("This is a Right-Justified\nMulti-line label.\nFourth line, (j/k)");
	label->set_justify(Gtk::JUSTIFY_RIGHT);
	frame->add(*label);
	vbox->pack_start(*frame, false, false);

	vbox = new Gtk::VBox(false, 5);
	hbox->pack_start(*vbox, false, false);
	frame = new Gtk::Frame("Line wrapped label");
	label = new Gtk::Label("This is an example of a line-wrapped label. It should not be taking up the "\
	                       "entire           /* big space to test spacing */  width allocated to it, "\
						   "but automatically wraps the words to fit. The time has come, for all good men, "\
						   "to come to the aid of their party. The sixth sheik's six sheep's sick.\n"\
	                       "     It supports multiple paragraphs correctly,  and   correctly      adds "\
	                       "      many          extra  spaces. ");
	label->set_line_wrap(true);
	frame->add(*label);
	vbox->pack_start(*frame, false, false);

	frame = new Gtk::Frame("Filled, wrapped label");
	label = new Gtk::Label("This is an example of a line-wrapped, filled label. " \
                           "It should be taking "\
	                       "up the entire              width allocated to it.  " \
	                       "Here is a sentence to prove "\
	                       "my point.  Here is another sentence. "\
	                       "Here comes the sun, do de do de do.\n"\
	                       "    This is a new paragraph.\n"\
	                       "    This is another newer, longer, better " \
	                       "paragraph.  It is coming to an end, "\
                           "unfortunately.");
	label->set_justify(Gtk::JUSTIFY_FILL);
	label->set_line_wrap(true);
	frame->add(*label);
	vbox->pack_start(*frame, false, false);

	frame = new Gtk::Frame("Underlined label");
	label = new Gtk::Label("This label is underlined!\n"
	                       "This one is underlined in quite a funky fashion");
	label->set_justify(Gtk::JUSTIFY_LEFT);
	label->set_pattern("_________________________ _ _________ _ ______     __ _______ ___");
	frame->add(*label);
	vbox->pack_start(*frame, false, false);
	show_all();
}

LabelWindow::~LabelWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	LabelWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}
