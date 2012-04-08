/* Drawing Area
 *
 * Gtk::DrawingArea is a blank area where you can draw custom displays
 * of various kinds.
 *
 * This demo has two drawing areas. The checkerboard area shows
 * how you can just draw something; all you have to do is write
 * a signal handler for expose_event, as shown here.
 *
 * The "scribble" area is a bit more advanced, and shows how to handle
 * events such as button presses and mouse motion. Click the mouse
 * and drag in the scribble area to draw squiggles. Resize the window
 * to clear the area.
 */

#include <xfc/gtk/box.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/frame.hh>
#include <xfc/gtk/label.hh>
#include <xfc/gtk/style.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gtk/widgetsignals.hh>
#include <xfc/gdk/color.hh>
#include <xfc/gdk/gc.hh>
#include <xfc/gdk/pixmap.hh>
#include <xfc/gdk/window.hh>

using namespace Xfc;

class CheckerBoard : public Gtk::DrawingArea, protected Gtk::WidgetSignals
{
protected:
	virtual bool on_expose_event(const Gdk::EventExpose& event);

public:
	CheckerBoard();
	~CheckerBoard();
};

class Scribble : public Gtk::DrawingArea, public Gtk::WidgetSignals
{
	Gdk::Pixmap *pixmap;

	void draw_brush(double x, double y);

protected:
	virtual bool on_configure_event(const Gdk::EventConfigure& event);
	virtual bool on_expose_event(const Gdk::EventExpose& event);
	virtual bool on_button_press_event(const Gdk::EventButton& event);
	virtual bool on_motion_notify_event(const Gdk::EventMotion& event);

public:
	Scribble();
	~Scribble();
};

class DrawingAreaWindow : public Gtk::Window
{
public:
	DrawingAreaWindow();	
	~DrawingAreaWindow();
};
//!

CheckerBoard::CheckerBoard()
: Gtk::WidgetSignals(this)
{
	// set a minimum size
	set_size_request(100, 100);

	// Scribble doesn't need to connect to any signals because it overrides
	// the virtual signal handlers inherited from Gtk::WidgetSignals.
}

CheckerBoard::~CheckerBoard()
{
}

bool
CheckerBoard::on_expose_event(const Gdk::EventExpose& event)
{
#define CHECK_SIZE 10
#define SPACING 2

	// At the start of an expose handler, a clip region of event.area() is set on the window,
	// and event.area() has been cleared to the widget's background color. The docs for
	// gdk_window_begin_paint_region() give more details on how this works.

	// It would be a bit more efficient to keep these GC's around instead of recreating on each expose,
	// but this is the lazy/slow way.
	Pointer<Gdk::GC> gc1 = new Gdk::GC(*get_window());
	Gdk::Color color(30000, 0, 30000);
	gc1->set_rgb_fg_color(color);

	Pointer<Gdk::GC> gc2 = new Gdk::GC(*get_window());
	color.set(65535, 65535, 65535);
	gc2->set_rgb_fg_color(color);

	int ycount, xcount = 0;
	int j, i = SPACING;
	while (i < get_allocation().width())
	{
		j = SPACING;
		ycount = xcount % 2; // start with even/odd depending on row
		while (j < get_allocation().height())
		{
			Gdk::GC *gc = (ycount % 2) ? gc1 : gc2;

			// If we're outside event.area(), this will do nothing. It might be mildly more efficient
			// if we handled the clipping ourselves, but again we're feeling lazy.
			get_window()->draw_rectangle(*gc, i, j, CHECK_SIZE, CHECK_SIZE);

			j += CHECK_SIZE + SPACING;
			++ycount;
		}
		i += CHECK_SIZE + SPACING;
		++xcount;
	}

	// return true because we've handled this event, so no further processing is required.
	return true;
}

// Scribble implementation

Scribble::Scribble()
: Gtk::WidgetSignals(this), pixmap(0)
{
	// set a minimum size
	set_size_request(100, 100);

	// Scribble doesn't need to connect to any signals because it overrides inherited virtual signal handlers,
	// but we must ask to receive events the drawing area doesn't normally subscribe to.
	Gdk::EventMaskField flags = get_events();
	flags |= (Gdk::LEAVE_NOTIFY_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK);
	set_events(flags);
}

Scribble::~Scribble()
{
	if (pixmap)
		pixmap->unref();
}

bool
Scribble::on_configure_event(const Gdk::EventConfigure& event)
{
	// Create a new pixmap of the appropriate size to store our scribbles
	if (pixmap)
    	pixmap->unref();

	pixmap = new Gdk::Pixmap(*get_window(), get_allocation().width(), get_allocation().height());

	// Initialize the pixmap to white
	pixmap->draw_rectangle(*(get_style()->white_gc()), 0, 0, get_allocation().width(), get_allocation().height());
	return true;
}

bool
Scribble::on_expose_event(const Gdk::EventExpose& event)
{
	// Redraw the screen from the pixmap, copying only the area that was exposed. We use the "foreground GC"
	// for the widget since it already exists, but any GC would work. The only thing to worry about is whether
	// the GC has an inappropriate clip region set.
	get_window()->draw_drawable(*(get_style()->fg_gc(get_state())), *pixmap, event.area(), event.area().x(), event.area().y());
	return false;
}

bool
Scribble::on_button_press_event(const Gdk::EventButton& event)
{
	// paranoia check, in case we haven't gotten a configure event
	if (!pixmap)
		return false;

	if (event.button() == 1)
		draw_brush(event.x(), event.y());

	//We've handled the event, stop processing
	return true;
}

bool
Scribble::on_motion_notify_event(const Gdk::EventMotion& event)
{
	// paranoia check, in case we haven't gotten a configure event
	if (!pixmap)
		return false;

	// This call is very important; it requests the next motion event. If you don't call
	// Gdk::Window::get_pointer() you'll only get a single motion event. The reason is that
	// we specified Gdk::POINTER_MOTION_HINT_MASK to Gtk::Widget::set_events(). If we hadn't
	// specified that, we could just use event.x(), event.y() as the pointer location. But we'd
	// also get deluged in events. By requesting the next event as we handle the current one,
	// we avoid getting a huge number of events faster than we can cope.

	int x, y;
	Gdk::ModifierTypeField state;
	event.window()->get_pointer(&x, &y, &state);

	if (state & Gdk::BUTTON1_MASK)
		draw_brush(x, y);

	// We've handled it, stop processing
	return true;
}

void
Scribble::draw_brush(double x, double y)
{
	// Draw a rectangle on the screen
	Gdk::Rectangle update_rect((int)x - 3, (int)y - 3, 6, 6);

	// Paint to the pixmap, where we store our state
	pixmap->draw_rectangle(*(get_style()->black_gc()), update_rect);

	// Now invalidate the affected region of the drawing area.
	get_window()->invalidate(update_rect, false);
}

// DrawingAreaWindow implementation

DrawingAreaWindow::DrawingAreaWindow()
{
	set_title("Drawing Area");
	set_border_width(8);

	Gtk::VBox *vbox = new Gtk::VBox(false, 8);
	vbox->set_border_width(8);
	add(*vbox);

	// Create the checkerboard area
	Gtk::Label *label = new Gtk::Label;
	label->set_markup("<u>Checkerboard pattern</u>");
	vbox->pack_start(*label, false, false);

	Gtk::Frame *frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);
	vbox->pack_start(*frame);

	Gtk::DrawingArea *da = new CheckerBoard;
	frame->add(*da);

	// Create the scribble area
	label = new Gtk::Label;
	label->set_markup("<u>Scribble area</u>");
	vbox->pack_start(*label, false, false);

	frame = new Gtk::Frame;
	frame->set_shadow_type(Gtk::SHADOW_IN);
	vbox->pack_start(*frame);

	da = new Scribble;
	frame->add(*da);
	show_all();
}

DrawingAreaWindow::~DrawingAreaWindow()
{
}

Gtk::Window*
do_drawingarea(Gtk::Widget *do_widget)
{
	static Gtk::Window *window = 0;

	if (!window)
	{
		window = new DrawingAreaWindow;
		window->set_screen(*do_widget->get_screen());
	}
	else
	{
		window->dispose();
		window = 0;
	}
	return window;
}
