#include "textview.hh"
#include <xfc/gtk/textview.hh>
#include <xfc/gdk/color.hh>

TextViewWindow::TextViewWindow()
{
	set_title("TextView Example");

	// Create text view widget
	Gtk::TextView *view = new Gtk::TextView;
	add(*view);

	// Get a pointer to the default buffer
	Gtk::TextBuffer *buffer = view->get_buffer();
	buffer->set_text ("Hello, this is some text");

	// Change default font throughout the widget
	Pointer<Pango::FontDescription> font_desc = new Pango::FontDescription("Serif 15");
	view->modify_font(font_desc);

	// Change default color throughout the widget
	Gdk::Color color("green");
	view->modify_text(Gtk::STATE_NORMAL, &color);

	// Change left margin throughout the widget
	view->set_left_margin(30);

	// Use a tag to change the color for just one part of the widget
	Gtk::TextTag *tag = buffer->create_tag("blue_foreground");
	tag->property_foreground() = String("blue");
	Gtk::TextIter start = buffer->get_iter_at_offset(7);
	Gtk::TextIter end = buffer->get_iter_at_offset(12);
	buffer->apply_tag(*tag, start, end);
	
	view->show();
}

TextViewWindow::~TextViewWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	TextViewWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

