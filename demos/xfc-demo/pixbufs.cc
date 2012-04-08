/* Pixbufs
 *
 * A Gdk::Pixbuf represents an image, normally in RGB or RGBA format.
 * Pixbufs are normally used to load files from disk and perform
 * image scaling.
 *
 * This demo is not all that educational, but looks cool. It is a C++ 
 * translation of the original written by Extreme Pixbuf Hacker 
 * Federico Mena Quintero. It also shows off how to use Gtk::DrawingArea
 * to do a simple animation.
 *
 * Look at the Image demo for additional pixbuf usage examples.
 */

#include "demowindow.hh"
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/messagedialog.hh>
#include <xfc/gtk/style.hh>
#include <xfc/gdk/window.hh>
#include <xfc/gdk-pixbuf/pixbuf.hh>
#include <xfc/glib/main.hh>
#include <cstdlib>
#include <cmath>

using namespace Xfc;

class PixbufWindow : public Gtk::Window
{
	// Current frame
	Pointer<Gdk::Pixbuf> frame;
	
	// Background image
	Pointer<Gdk::Pixbuf> background;
	int back_width;
	int back_height;
	
	// Drawing area
	Gtk::DrawingArea *da;

	// Expose callback for the drawing area
	bool on_drawing_area_expose_event(const Gdk::EventExpose& event);

	// Timeout handler to regenerate the frame
	bool on_timeout();

	// Loads the images for the demo and returns whether the operation succeeded
	bool load_pixbufs(G::Error *error);

	sigc::connection timeout_connection;

public:
	PixbufWindow();
	~PixbufWindow();
};
//!

#define FRAME_DELAY 50

#define BACKGROUND_NAME "background.jpg"

// Images
static const char *image_names[] = {
	"apple-red.png",
	"gnome-applets.png",
	"gnome-calendar.png",
	"gnome-foot.png",
	"gnome-gmush.png",
	"gnome-gimp.png",
	"gnome-gsame.png",
	"gnu-keys.png"
};

const int N_IMAGES = G_N_ELEMENTS(image_names);
Pointer<Gdk::Pixbuf> images[N_IMAGES];

PixbufWindow::PixbufWindow()
: back_width(0), back_height(0), da(0)
{
	set_title("Pixbufs");
	set_resizable(false);

	G::Error error;
	if (!load_pixbufs(&error))
	{
		Gtk::MessageDialog dialog(Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE, this);
		dialog.format_message("Failed to load an image: %s", error.message());
		dialog.set_position(Gtk::WIN_POS_CENTER);
		if (dialog.run())
			dialog.dispose();
	}
	else
	{
		set_size_request(back_width, back_height);

		frame = Gdk::Pixbuf::create(back_width, back_height, false);

		da = new Gtk::DrawingArea;
		da->signal_expose_event().connect(sigc::mem_fun(this, &PixbufWindow::on_drawing_area_expose_event));
		add(*da);

		timeout_connection = G::timeout_signal.connect(sigc::mem_fun(this, &PixbufWindow::on_timeout), FRAME_DELAY);
		show_all();
    }
}

PixbufWindow::~PixbufWindow()
{
	timeout_connection.disconnect();
}

bool 
PixbufWindow::load_pixbufs(G::Error *error)
{
	if (background)
		return true; // already loaded earlier

	// DemoWindow::find_file() looks in the the current directory first, then looks in the location where the file is installed.
	String filename = DemoWindow::find_file(BACKGROUND_NAME, error);
	if (filename.null())
		return false; // note that "error" was filled in and returned

	background = Gdk::Pixbuf::create(filename, error);
  
	if (!background)
		return false; // Note that "error" was filled with a GError

	back_width = background->get_width();
	back_height = background->get_height();

	for (int i = 0; i < N_IMAGES; i++)
	{
		filename = DemoWindow::find_file(image_names[i], error);
		if (filename.null())
			return false; // Note that "error" was filled with a GError
      
		images[i] = Gdk::Pixbuf::create(filename, error);

		if (!images[i])
			return false; // Note that "error" was filled with a GError
    }
	return true;
}

bool
PixbufWindow::on_drawing_area_expose_event(const Gdk::EventExpose& event)
{
	int rowstride = frame->get_rowstride();

	unsigned char *pixels = frame->get_pixels() + rowstride * event.area().y() + event.area().x() * 3;

	da->get_window()->draw_rgb_image_dithalign(*(da->get_style()->black_gc()),
	                                           event.area().x(), event.area().y(),
	                                           event.area().width(), event.area().height(),
	                                           Gdk::RGB_DITHER_NORMAL,
	                                           pixels, rowstride,
	                                           event.area().x(), event.area().y());
	return true;
}

#define CYCLE_LEN 60

bool
PixbufWindow::on_timeout()
{
	static int frame_num = 0;

	frame->copy_area(*background, 0, 0, back_width, back_height, 0, 0);

	double f = (double)(frame_num % CYCLE_LEN) / CYCLE_LEN;

	double xmid = back_width / 2.0;
	double ymid = back_height / 2.0;

	double radius = MIN(xmid, ymid) / 2.0;

	for (int i = 0; i < N_IMAGES; i++)
	{
		double ang = 2.0 * G_PI * (double) i / N_IMAGES - f * 2.0 * G_PI;

		int iw = images[i]->get_width();
		int ih = images[i]->get_height();

		double r = radius + (radius / 3.0) * sin(f * 2.0 * G_PI);

		int xpos = (int)floor(xmid + r * cos(ang) - iw / 2.0 + 0.5);
		int ypos = (int)floor(ymid + r * sin(ang) - ih / 2.0 + 0.5);

		double k = (i & 1) ? sin(f * 2.0 * G_PI) : cos(f * 2.0 * G_PI);
		k = 2.0 * k * k;
		k = MAX(0.25, k);

		Gdk::Rectangle r1(xpos, ypos, int(iw * k), int(ih * k));
		Gdk::Rectangle r2(0, 0, back_width, back_height);

		if (r1.intersect_with(r2))
		{
			frame->composite(*images[i], r1.x(), r1.y(), r1.width(), r1.height(),
			                 xpos, ypos, k, k, Gdk::INTERP_NEAREST,
			                 (int)((i & 1)
			                 ? MAX(127, fabs(255 * sin(f * 2.0 * G_PI)))
			                 : MAX(127, fabs(255 * cos(f * 2.0 * G_PI)))));
		}
    }

	da->queue_draw();

	frame_num++;
	return true;
}

Gtk::Window*
do_pixbufs(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new PixbufWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}
