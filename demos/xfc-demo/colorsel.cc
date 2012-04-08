/* Color Selector
 *
 * Gtk::ColorSelection lets the user choose a color. Gtk::ColorSelectionDialog is
 * a prebuilt dialog containing a Gtk::ColorSelection.
 */

#include <xfc/gtk/alignment.hh>
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/colorselection.hh>
#include <xfc/gtk/dialog.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gdk/color.hh>

using namespace Xfc;

class ColorSelWindow : public Gtk::Window
{
	Gdk::Color color;
	Gtk::DrawingArea *da;
	
	void on_change_color();

public:
	ColorSelWindow();
	~ColorSelWindow();
};
//!

ColorSelWindow::ColorSelWindow()
{
	set_title("Color Selection");
	set_border_width(8);
	
	Gtk::VBox *vbox = new Gtk::VBox(false, 8);
	vbox->set_border_width(8);
	add(*vbox);

	// Create the color swatch area
	Gtk::Frame *frame = new Gtk::Frame(Gtk::SHADOW_IN);
	vbox->pack_start(*frame);
      
	// Set a minimum size
	da = new Gtk::DrawingArea;
	da->set_size_request(200, 200);

	// Set the color
	color.set_blue(65535);
	da->modify_bg(Gtk::STATE_NORMAL, &color);
	frame->add(*da);

	Gtk::Alignment *alignment = new Gtk::Alignment(1.0, 0.5, 0.0, 0.0);
	Gtk::Button *button = new Gtk::Button("_Change the above color", true);
 	button->signal_clicked().connect(sigc::mem_fun(this, &ColorSelWindow::on_change_color));
	alignment->add(*button);
	vbox->pack_start(*alignment, false, false);

	show_all();
}
	
ColorSelWindow::~ColorSelWindow()
{
}	
	
void
ColorSelWindow::on_change_color()
{
	Gtk::ColorSelectionDialog *dialog = new Gtk::ColorSelectionDialog("Changing color");

	dialog->set_transient_for(this);

	Gtk::ColorSelection *colorsel = dialog->colorsel();
	colorsel->set_previous_color(color);
	colorsel->set_current_color(color);
	colorsel->set_has_palette(true);

	if (dialog->run() == Gtk::RESPONSE_OK)
	{
		color =	colorsel->get_current_color();
 		da->modify_bg(Gtk::STATE_NORMAL, &color);
	}
	dialog->dispose();
}

Gtk::Window*
do_colorsel(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new ColorSelWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

