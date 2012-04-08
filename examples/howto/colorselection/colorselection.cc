#include "colorselection.hh"

ColorSelectionWindow::ColorSelectionWindow()
{
	set_title("Color Selection Example");

	// Create drawing area
	area= new Gtk::DrawingArea(250, 200);

	// Set the initial background color	and events to receive
	color.set(0, 0, 65535);
	area->modify_bg(Gtk::STATE_NORMAL, &color);
	area->set_events(Gdk::BUTTON_PRESS_MASK);
	area->signal_event().connect(sigc::mem_fun(this, &ColorSelectionWindow::on_drawing_area_event));

	// Add drawing area to main window
	add(*area);
	area->show();
	show();
}

ColorSelectionWindow::~ColorSelectionWindow()
{
}

bool
ColorSelectionWindow::on_drawing_area_event(const Gdk::Event& event)
{
	using namespace sigc;	
	bool handled = false;

	if (event.type() == Gdk::BUTTON_PRESS)
	{
		handled = true;
		Gtk::ColorSelectionDialog *dialog = new Gtk::ColorSelectionDialog("Select background color");
		Gtk::ColorSelection *colorsel = dialog->colorsel();
		colorsel->set_previous_color(color);
		colorsel->set_current_color(color);
		colorsel->set_has_palette(true);

		// Connect to the "color_changed" signal
		colorsel->signal_color_changed().connect(bind(mem_fun(this, &ColorSelectionWindow::on_color_changed), colorsel));

		// Show the dialog
		if (dialog->run() == Gtk::RESPONSE_OK)
			color =	colorsel->get_current_color();
		else
 			area->modify_bg(Gtk::STATE_NORMAL, &color);

		dialog->dispose();
	}
	return handled;
}

void
ColorSelectionWindow::on_color_changed(Gtk::ColorSelection *colorsel)
{
	Gdk::Color new_color = colorsel->get_current_color();
	area->modify_bg(Gtk::STATE_NORMAL, &new_color);
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	ColorSelectionWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	

	run();
	return 0;
}

