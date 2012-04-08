/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 */

/// @file xfc/gtk/drawingarea.hh
/// @brief A GtkDrawingArea C++ wrapper interface.
///
/// Provides the DrawingArea widget which is used for creating custom user interface
/// elements. It's essentially a blank widget you can draw on. After creating a 
/// drawing area, the application may want to connect to mouse and button press 
/// signals to respond to input from the user.
/// If cairo is found on the system, it will be possible to get a cairo context to
/// draw on too from this class.

#ifndef XFC_GTK_DRAWING_AREA_HH
#define XFC_GTK_DRAWING_AREA_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifdef XFC_CAIRO
#include <xfc/cairo/context.hh>
#include <xfc/gdk/window.hh>
#include <gdk/gdkcairo.h>
#endif

#ifndef __GTK_DRAWING_AREA_H__
#include <gtk/gtkdrawingarea.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class DrawingArea drawingarea.hh xfc/gtk/drawingarea.hh
/// @brief A GtkDrawingArea C++ wrapper class.
///
/// The DrawingArea widget is used for creating custom user interface elements. It's
/// essentially a blank widget you can draw on. After creating a drawing area, the
/// application may want to connect to mouse and button press signals to respond to
/// input from the user. Use Gtk::Widget::add_events() to enable events you wish to
/// receive. Connect to the "realize" signal to take any necessary actions when the
/// widget is instantiated on a particular display. (Create GDK resources in response
/// to this signal.) Connect to the "configure_event" signal to take any necessary
/// actions when the widget changes size. Connect to the "expose_event" signal to 
/// handle redrawing the contents of the widget.
///
/// The following code portion demonstrates using a drawing area to display a circle
/// in the normal widget foreground color. Note that GDK automatically clears the 
/// exposed area to the background color before sending the expose event, and that 
/// drawing is implicitly clipped to the exposed area.
///
/// <B>Example:</B> Simple DrawingArea usage.
/// @code
/// #include <xfc/main.hh>
/// #include <xfc/gtk/drawingarea.hh>
/// #include <xfc/gtk/style.hh>
/// #include <xfc/gtk/window.hh>
/// #include <xfc/gdk/window.hh>
///
/// using namespace Xfc;
///
/// class Window : public Gtk::Window
/// {
/// 	Gtk::DrawingArea *area;
/// protected:
/// 	bool on_area_expose_event(const Gdk::EventExpose& event);
/// public:
/// 	Window();
/// };
///
/// Window::Window()
/// {
/// 	area = new Gtk::DrawingArea(100, 100);
/// 	area->signal_expose_event().connect(sigc::mem_fun(this, &Window::on_area_expose_event));
/// 	add(*area);
/// 	area->show();
/// }
///
/// bool
/// Window::on_area_expose_event(const Gdk::EventExpose& event)
/// {
///	Gdk::Color color("blue");
///	area->modify_fg(area->get_state(), &color);
/// 	area->get_window()->draw_arc(*area->get_style()->fg_gc(area->get_state()), // context
/// 	                             0, 0, // x, y,
/// 				     area->get_allocation().width(), // width
/// 				     area->get_allocation().height(), // height
/// 				     0, 64 * 360); // angle1, angle2
/// 	return true;
/// }
///
/// int main (int argc, char *argv[])
/// {
/// 	using namespace Main;
///
/// 	init(&argc, &argv);
///
/// 	Window window;
/// 	window.signal_destroy().connect(sigc::ptr_fun(&Xfc::Main::quit));
/// 	window.show();
///
/// 	run();
/// 	return 0;
/// }
/// @endcode
///
/// Expose events are normally delivered when a drawing area first comes onscreen, or
/// when it's covered by another window and then uncovered (exposed). You can also 
/// force an expose event by adding to the "damage region" of the drawing area's window;
/// Gtk::Widget::queue_draw_area() and Gdk::Window::invalidate_rect() are equally good
/// ways to do this. You'll then get an expose event for the invalid region. (See also
/// Gdk::Pixbuf::render_to_drawable() for drawing a Gdk::Pixbuf.)
///
/// To receive mouse events on a drawing area, you will need to enable them with 
/// Gtk::Widget::add_events(). To receive keyboard events, you will need to set the
/// CAN_FOCUS flag on the drawing area, and should probably draw some user-visible
/// indication that the drawing area is focused. Use Gtk::Widget::has_focus() in your
/// expose event handler to decide whether to draw the focus indicator. (See 
/// Gtk::Style::draw_focus() for one way to draw the focus.)
///
/// <B>See also:</B> the <A HREF="../../howto/html/drawingarea.html">DrawingArea Widget</A> HOWTO and example.

class DrawingArea : public Widget
{
	friend class G::Object;

	DrawingArea(const DrawingArea&);
	DrawingArea& operator=(const DrawingArea&);

protected:
/// @name Constructors
/// @{

	explicit DrawingArea(GtkDrawingArea *drawing_area, bool owns_reference = false);
	///< Construct a new DrawingArea from an existing GtkDrawingArea.
	///< @param drawing_area A pointer to a GtkDrawingArea.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>drawing_area</EM> can be a newly created GtkDrawingArea or an existing
	///< GtkDrawingArea (see G::Object::Object).

/// @}

public:
	typedef GtkDrawingArea CObjectType;

/// @name Constructors
/// @{

	DrawingArea();
	///< Construct a new DrawingArea.

	DrawingArea(int width, int height);
	///< Construct a new DrawingArea with the specified width and height.
	///< @param width The width to request.
	///< @param height The height to request.

	virtual ~DrawingArea();
	///< Destructor.
	
/// @}
/// @name Accessors	
/// @{

#ifdef XFC_CAIRO
    Cairo::Context get_cairo_context( void ) const;
    ///< get a cairo context for this area
#endif

	GtkDrawingArea* gtk_drawing_area() const;
	///< Get a pointer to the GtkDrawingArea structure.

	operator GtkDrawingArea* () const;
	///< Conversion operator; safely converts a DrawingArea to a GtkDrawingArea pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/drawingarea.inl>

#endif // XFC_GTK_DRAWING_AREA_HH

