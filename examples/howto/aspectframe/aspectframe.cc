#include "aspectframe.hh"
#include <xfc/gtk/aspectframe.hh>
#include <xfc/gtk/drawingarea.hh>

AspectFrameWindow::AspectFrameWindow()
{
	set_title("Aspect Frame");
	set_border_width(10);

	// Create an aspect_frame and add it to our toplevel window
	Gtk::AspectFrame *aspect_frame = new Gtk::AspectFrame("2x1", 0.5, 0.5, 2);
	add(*aspect_frame);
	aspect_frame->show();

	// Now add a child widget to the aspect frame
	Gtk::DrawingArea *drawing_area = new Gtk::DrawingArea;

	// We ask for a 200x200 window but get a 200x100 window since we are forcing a 2x1 aspect ratio.
	drawing_area->set_size_request(200, 200);
	aspect_frame->add(*drawing_area);
	drawing_area->show();
}

AspectFrameWindow::~AspectFrameWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	AspectFrameWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

