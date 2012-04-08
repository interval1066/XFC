#include <xfc/main.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/style.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gdk/window.hh>

using namespace Xfc;

class Window : public Gtk::Window
{
	Gtk::DrawingArea *area;
	
protected:
	bool on_area_expose_event(const Gdk::EventExpose& event);
	
public:
	Window();
};

Window::Window()
{
	area = new Gtk::DrawingArea(100, 100);
	area->signal_expose_event().connect(sigc::mem_fun(this, &Window::on_area_expose_event));
	add(*area);
	area->show();
 }

bool
Window::on_area_expose_event(const Gdk::EventExpose& event)
{
	Gdk::Color color("blue");
	area->modify_fg(area->get_state(), &color);
	area->get_window()->draw_arc(*area->get_style()->fg_gc(area->get_state()), // context
	                             0, 0, // x, y,
				     area->get_allocation().width(), // width
				     area->get_allocation().height(), // height
				     0, 64 * 360); // angle1, angle2
	return true;
}

int main (int argc, char *argv[])
{
	using namespace Main;
 	
	init(&argc, &argv);

	Window window;
	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
 	window.show();

	run();
 	return 0;
}

