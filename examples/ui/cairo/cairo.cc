// Open an window and make a drawing a cairo canvas inside it

#include <xfc/main.hh>
#include <xfc/gtk/drawingarea.hh>
#include <xfc/gtk/style.hh>
#include <xfc/gtk/window.hh>
#include <xfc/glib/main.hh>
#include <ctime>
#include <math.h>
#include <iostream>


using namespace Xfc;
using namespace std;

class CairoWindow : public Gtk::Window
{
    Gtk::DrawingArea *m_area;
    G::TimeoutSignal m_timeout;
    double m_radius;
    double m_lineWidth;
protected:
    bool on_area_expose_event(const Gdk::EventExpose& event);
    bool on_second_elapsed(void);
public:
    CairoWindow();

    void draw( Cairo::Context cr );
};

CairoWindow::CairoWindow() : m_radius(0.42), m_lineWidth(0.05)
{
    m_area = new Gtk::DrawingArea(250, 250);
    m_area->signal_expose_event().connect(sigc::mem_fun(this, &CairoWindow::on_area_expose_event));
    add(*m_area);
    m_area->show();
    // Setup timer
    m_timeout.connect(
                sigc::mem_fun(*this, &CairoWindow::on_second_elapsed), 1000);
}

bool CairoWindow::on_area_expose_event(const Gdk::EventExpose& event)
{
    Cairo::Context cr( m_area->get_cairo_context());
    
    if( event ) {
        // clip to the area indicated by the expose event so that we only
        // redraw the portion of the window that needs to be redrawn
        cr.rectangle(event.area().x(), event.area().y(),
                event.area().width(), event.area().height() );
        cr.clip();
    }

    draw( cr );
    return true;
}

void CairoWindow::draw( Cairo::Context cr )
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.width();
    const int height = allocation.height();

    // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
    // the center of the window
    cr.scale(width, height);
    cr.translate(0.5, 0.5);
    cr.set_line_width(m_lineWidth);

    cr.save();
    cr.set_source_rgba(0.337, 0.612, 0.117, 0.9);   // green
    cr.paint();
    cr.restore();
    cr.arc(0, 0, m_radius, 0, 2 * M_PI);
    cr.save();
    cr.set_source_rgba(1.0, 1.0, 1.0, 0.8);
    cr.fill_preserve();
    cr.restore();
    cr.stroke_preserve();
    cr.clip();

    // clock ticks
    for (int i = 0; i < 12; i++) {
        double inset = 0.05;

        cr.save();
        cr.set_line_cap( Cairo::LINE_CAP_ROUND );

        if(i % 3 != 0) {
            inset *= 0.8;
            cr.set_line_width(0.03);
        }

        cr.move_to(
                (m_radius - inset) * cos (i * M_PI / 6),
                (m_radius - inset) * sin (i * M_PI / 6));
        cr.line_to (
                m_radius * cos (i * M_PI / 6),
                m_radius * sin (i * M_PI / 6));
        cr.stroke();
        cr.restore(); /* stack-pen-size */
    }

    // store the current time
    time_t rawtime;
    time(&rawtime);
    struct tm * timeinfo = localtime (&rawtime);

    // compute the angles of the indicators of our clock
    double minutes = timeinfo->tm_min * M_PI / 30;
    double hours = timeinfo->tm_hour * M_PI / 6;
    double seconds= timeinfo->tm_sec * M_PI / 30;

    cr.save();
    cr.set_line_cap(Cairo::LINE_CAP_ROUND);

    // draw the seconds hand
    cr.save();
    cr.set_line_width(m_lineWidth / 3);
    cr.set_source_rgba(0.7, 0.7, 0.7, 0.8); // gray
    cr.move_to(0, 0);
    cr.line_to(sin(seconds) * (m_radius * 0.9), 
            -cos(seconds) * (m_radius * 0.9));
    cr.stroke();
    cr.restore();

    // draw the minutes hand
    cr.set_source_rgba(0.117, 0.337, 0.612, 0.9);   // blue
    cr.move_to(0, 0);
    cr.line_to(sin(minutes + seconds / 60) * (m_radius * 0.8),
            -cos(minutes + seconds / 60) * (m_radius * 0.8));
    cr.stroke();

    // draw the hours hand
    cr.set_source_rgba(0.337, 0.612, 0.117, 0.9);   // green
    cr.move_to(0, 0);
    cr.line_to(sin(hours + minutes / 12.0) * (m_radius * 0.5),
            -cos(hours + minutes / 12.0) * (m_radius * 0.5));
    cr.stroke();
    cr.restore();

    // draw a little dot in the middle
    cr.arc(0, 0, m_lineWidth / 3.0, 0, 2 * M_PI);
    cr.fill();
}

bool CairoWindow::on_second_elapsed(void)
{
    // force our program to redraw the entire clock.
    Gdk::Window *win = m_area->get_window();
    if (win) {
        Gdk::Rectangle r(0, 0, get_allocation().width(),
                get_allocation().height());
        win->invalidate(r, false);
    }
    return true;
}

int main (int argc, char *argv[])
{
    using namespace Main;

    init(&argc, &argv);

    CairoWindow window;
    window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
    window.show();

    run();
    return 0;
}
