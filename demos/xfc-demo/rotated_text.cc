/* Rotated Text
 *
 * This demo shows how to use GDK and Pango to draw rotated and transformed
 * text. The use of Gdk::PangoRenderer in this example is a somewhat advanced
 * technique; most applications can simply use Gdk::Drawable::draw_layout(). 
 * We use it here mostly because that allows us to work in user coordinates,
 * that is, coordinates prior to the application of the transformation matrix,
 * rather than device coordinates.
 *
 * As of GTK+-2.6, the ability to draw transformed and anti-aliased graphics
 * as shown in this example is only present for text. With GTK+-2.8, a new
 * graphics system called "Cairo" will be introduced that provides these
 * capabilities and many more for all types of graphics.
 */

#include "demowindow.hh"
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/style.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gdk/color.hh>
#include <xfc/gdk/pangorenderer.hh>
#include <xfc/gdk/window.hh>
#include <xfc/pango/pango.hh>
#include <algorithm>
#include <cmath>

using namespace Xfc;
 
class RotatedTextWindow : public Gtk::Window
{
	Gtk::DrawingArea *da;
	
protected:
	bool on_expose_event(const Gdk::EventExpose& event_);

public:
	RotatedTextWindow();
	virtual ~RotatedTextWindow();
};
//!

const int RADIUS = 150;
const int N_WORDS = 10;

RotatedTextWindow::RotatedTextWindow()
{
	set_title("Rotated Text");
	
	da = new Gtk::DrawingArea;
	add(*da);

	// This overrides the background color from the theme
	const Gdk::Color white(65535);	
	da->modify_bg(Gtk::STATE_NORMAL, &white);

	da->signal_expose_event().connect(sigc::mem_fun(this, &RotatedTextWindow::on_expose_event));
	set_default_size(2 * RADIUS, 2 * RADIUS);
	show_all();
}

RotatedTextWindow::~RotatedTextWindow()
{
}

bool
RotatedTextWindow::on_expose_event(const Gdk::EventExpose& /*event*/)
{
	int width = get_allocation().width();
	int height = get_allocation().height();
	double device_radius;
	
	// Get the default renderer for the screen, and set it up for drawing
	Gdk::PangoRenderer *renderer = Gdk::PangoRenderer::get_default(*da->get_screen());
	renderer->set_drawable(da->get_window());
	renderer->set_gc(da->get_style()->black_gc());
	
	// Set up a transformation matrix so that the user space coordinates for the centered square
	// where we draw are [-RADIUS, RADIUS], [-RADIUS, RADIUS]. We first center, then change the scale.
	device_radius = std::min(width, height) / 2.0;
	Pango::Matrix matrix;
	matrix.translate(device_radius + (width - 2 * device_radius) / 2, device_radius + (height - 2 * device_radius) / 2);
	matrix.scale(device_radius / RADIUS, device_radius / RADIUS);
	
	// Create a Pango::Layout and set the font and text
	Pointer<Pango::Context> context = da->create_pango_context();
	Pointer<Pango::Layout> layout = new Pango::Layout(*context);
	layout->set_text("Text");
	Pointer<Pango::FontDescription> desc = new Pango::FontDescription("Sans Bold 27");
	layout->set_font_description(desc);
	
	// Draw the layout N_WORDS times in a circle
	for (int i = 0; i < N_WORDS; i++)
	{
		/* Gradient from red at angle == 60 to blue at angle == 300 */
		Gdk::Color color;
		double angle = (360. * i) / N_WORDS;
		double value = (1 + cos((angle - 60) * G_PI / 180.)) / 2;
		color.red(value);
		color.blue(1 - value);
		
		renderer->set_override_color(Pango::RENDER_PART_FOREGROUND, &color);
							
		Pango::Matrix rotated_matrix(matrix);
		rotated_matrix.rotate(angle);
		
		context->set_matrix(&rotated_matrix);
		
		// Inform Pango to re-layout the text with the new transformation matrix
		layout->context_changed();
		
		layout->get_size(&width, &height);
		renderer->draw_layout(*layout, - width / 2, - RADIUS * PANGO_SCALE);
	}
	
	// Clean up default renderer, since it is shared
	renderer->set_override_color(Pango::RENDER_PART_FOREGROUND, 0);
	renderer->set_drawable(0);
	renderer->set_gc(0);
	return false;
}

Gtk::Window*
do_rotated_text(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new RotatedTextWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}

