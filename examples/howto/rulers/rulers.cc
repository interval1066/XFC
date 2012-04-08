#include "rulers.hh"
#include <xfc/gtk/box.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/table.hh>
#include <xfc/gtk/private/widgetclass.hh>

RulerWindow::RulerWindow()
{
	set_title("Ruler Example");	
	set_border_width(10);

	// Create a table for placing the ruler and the drawing area
	Gtk::Table *table = new Gtk::Table(3, 2);
	add(*table);

	Gtk::DrawingArea *area = new Gtk::DrawingArea(600, 400);
	table->attach(*area, 1, 2, 1, 2, Gtk::EXPAND | Gtk::FILL, Gtk::FILL);
	area->set_events(Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK);

	// The horizontal ruler goes on top. As the mouse moves across the drawing area,
	// a motion_notify_event is passed to the appropriate event handler for the ruler.
	Gtk::HRuler *hruler = new Gtk::HRuler;
	hruler->set_range(7, 13, 0, 20);
	table->attach(*hruler, 1, 2, 0, 1, Gtk::EXPAND | Gtk::SHRINK | Gtk::FILL, Gtk::FILL);
	
	// Some C code that connects the drawing area "motion_notify_event" directly to the hruler.	
	GCallback callback = GCallback(GTK_WIDGET_GET_CLASS(hruler->gtk_widget())->motion_notify_event);
	g_signal_connect_swapped(area->g_object(), "motion_notify_event", callback, hruler->gtk_widget());

	// The vertical ruler goes on the left. As the mouse moves across the drawing area,
	// a motion_notify_event is passed to the appropriate event handler for the ruler.
	Gtk::VRuler *vruler = new Gtk::VRuler;
	vruler->set_range(0, 400, 10, 400);
	table->attach(*vruler, 0, 1, 1, 2, Gtk::FILL, Gtk::EXPAND | Gtk::SHRINK | Gtk::FILL);
	
	// Some C code that connects the drawing area's "motion_notify_event" directly to the vruler. 	
	callback = GCallback(GTK_WIDGET_GET_CLASS(vruler->gtk_widget())->motion_notify_event);
	g_signal_connect_swapped(area->g_object(), "motion_notify_event", callback, vruler->gtk_widget());

	// Now show everything
	show_all();
}

RulerWindow::~RulerWindow()
{
}

int main (int argc, char *argv[])
{
	using namespace Main;

	init(&argc, &argv);

	RulerWindow window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));

	run();
	return 0;
}

