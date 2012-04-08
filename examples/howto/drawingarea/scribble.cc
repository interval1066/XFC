#include "scribble.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/button.hh>
#include <xfc/gtk/style.hh>
#include <xfc/gdk/color.hh>
#include <xfc/gdk/gc.hh>
#include <xfc/gdk/pixmap.hh>
#include <xfc/gdk/window.hh>

// DrawingArea

DrawingArea::DrawingArea()
: Gtk::WidgetSignals(this),
  pixmap(0)
{
	set_size_request(200, 200);
	set_double_buffered(false);
	Gdk::EventMaskField flags = get_events();
	flags |= (Gdk::LEAVE_NOTIFY_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK);
	set_events(flags);
}

DrawingArea::~DrawingArea()
{
	if (pixmap)
		pixmap->unref();
}

bool
DrawingArea::on_expose_event(const Gdk::EventExpose& event)
{
	// Redraw the screen from the backing pixmap
	get_window()->draw_drawable(*(get_style()->fg_gc(get_state())), *pixmap, event.area(), event.area().x(), event.area().y());
	return false;
}

bool 
DrawingArea::on_configure_event(const Gdk::EventConfigure& event)
{
	// Create a new backing pixmap of the appropriate size
	if (pixmap)
    		pixmap->unref();

	pixmap = new Gdk::Pixmap(*get_window(), get_allocation().width(), get_allocation().height());
	pixmap->draw_rectangle(*(get_style()->white_gc()), 0, 0, get_allocation().width(), get_allocation().height());
	return true;
}

bool 
DrawingArea::on_button_press_event(const Gdk::EventButton& event)
{
	if (event.button() == 1 && pixmap)
		draw_brush(event.x(), event.y());

	return true;
}

bool
DrawingArea::on_motion_notify_event(const Gdk::EventMotion& event)
{
	int x, y;
	Gdk::ModifierTypeField state;
	
	if (event.is_hint())
	 	event.window()->get_pointer(&x, &y, &state);
	else
	{
		x = (int)event.x();
		y = (int)event.y();
		state = event.state();
	}

	if (state & Gdk::BUTTON1_MASK && pixmap)
		draw_brush(x, y);

	return true;
}

void
DrawingArea::draw_brush(double x, double y)
{
	// Draw a rectangle on the screen
	Gdk::Rectangle update_rect((int)x - 5, (int)y - 5, 10, 10);
	pixmap->draw_rectangle(*(get_style()->black_gc()), update_rect);
	queue_draw_area(update_rect);
}

// ScribbleWindow

ScribbleWindow::ScribbleWindow()
{
	set_name("Test Input");

	Gtk::VBox *vbox = new Gtk::VBox;
	add(*vbox);
	vbox->show();

	// Create the drawing area
	DrawingArea *drawing_area = new DrawingArea;
	vbox->pack_start(*drawing_area);
	drawing_area->show();

	// And a quit button
	Gtk::Button *button = new Gtk::Button("Quit");
	vbox->pack_start(*button, false, false);
	button->signal_clicked().connect(sigc::mem_fun(this, &ScribbleWindow::dispose));
	button->show();
}

ScribbleWindow::~ScribbleWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	ScribbleWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
	window.show();

	run();
	return 0;
}

