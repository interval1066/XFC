#include "frame.hh"
#include <xfc/gtk/frame.hh>

FrameWindow::FrameWindow()
{
	set_title("Frame Example");
	set_size_request(300, 300);

	// Sets the border width of the window.
	set_border_width(10);

	// Create a Frame
	Gtk::Frame *frame = new Gtk::Frame;
	add(*frame);

	// Set the frame's label
	frame->set_label(" Gtk::Frame Widget ");

	// Align the label at the right of the frame
	frame->set_label_align(0.0, 0.5);

	// Set the style of the frame
	frame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
	frame->show();
}

FrameWindow::~FrameWindow()
{
}

XFC_MAIN(FrameWindow)

