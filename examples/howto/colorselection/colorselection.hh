#include <xfc/main.hh>
#include <xfc/gtk/colorselection.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/window.hh>
#include <xfc/gdk/color.hh>

using namespace Xfc;

class ColorSelectionWindow : public Gtk::Window
{
	Gdk::Color color;
	Gtk::DrawingArea *area;

protected:
	bool on_drawing_area_event(const Gdk::Event& event);
	void on_color_changed(Gtk::ColorSelection *colorsel);

public:
	ColorSelectionWindow();
	virtual ~ColorSelectionWindow();
};

