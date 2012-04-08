#include "sourceview.hh"
#include <xfc/sourceview/sourceview.hh>
#include <xfc/gdk/color.hh>

SourceViewWindow::SourceViewWindow()
{
	set_title("SourceView Example");

	// Create text view widget
	Gtk::SourceView *view = new Gtk::SourceView;
	add(*view);

	// Get a pointer to the default buffer
	Gtk::SourceBuffer *buffer = view->get_source_buffer();
	buffer->set_text ("Hello, this is some source code text");

	// Change default font throughout the widget
	Pointer<Pango::FontDescription> font_desc = new Pango::FontDescription("monospace");
	view->modify_font(font_desc);

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

SourceViewWindow::~SourceViewWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	SourceViewWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

