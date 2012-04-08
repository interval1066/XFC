#include <xfc/main.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/widgetsignals.hh>
#include <xfc/gtk/window.hh>

using namespace Xfc;

class DrawingArea : public Gtk::DrawingArea, protected Gtk::WidgetSignals
{
	Gdk::Pixmap *pixmap;

	void draw_brush(double x, double y);

protected:
	virtual bool on_expose_event(const Gdk::EventExpose& event);
	virtual bool on_configure_event(const Gdk::EventConfigure& event);
	virtual bool on_button_press_event(const Gdk::EventButton& event);
	virtual bool on_motion_notify_event(const Gdk::EventMotion& event);

public:
	DrawingArea();
	virtual ~DrawingArea();
};

class ScribbleWindow : public Gtk::Window
{
public:
	ScribbleWindow();
	virtual ~ScribbleWindow();
};

