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
 
/// @file xfc/gtk/style.hh
/// @brief A GtkStyle C++ wrapper interface.
///
/// Provides Style, an object used to store a widget's style.

#ifndef XFC_GTK_STYLE_HH
#define XFC_GTK_STYLE_HH

#ifndef XFC_GDK_COLOR_HH
#include <xfc/gdk/color.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef __GTK_STYLE_H__
#include <gtk/gtkstyle.h>
#endif

namespace Xfc {
	
namespace Gdk {
class Drawable;
class GC;
class Pixbuf;
class Pixmap;
class Rectangle;
class Window;
}

namespace Pango {
class FontDescription;
class Layout;
}

namespace Gtk {

class IconSet;
class IconSource;
class StockId;
class Widget;

/// @name Drawing Methods
/// @{

	void draw_insertion_cursor
	(
		Widget& widget,
		Gdk::Drawable& drawable,
		const Gdk::Rectangle& location,
		bool is_primary,
		TextDirection direction,
		bool draw_arrow,
		const Gdk::Rectangle *area = 0
	);
	///< Draws a text caret on a drawable at the specified <EM>location</EM>. 
	///< @param widget A Gtk::Widget.
	///< @param drawable A Gdk::Drawable owned by <EM>widget</EM>.
	///< @param location The location where to draw the cursor (location.width() is ignored).
	///< @param is_primary If the cursor should be the primary cursor color. 	
	///< @param direction Whether the cursor is left-to-right or right-to-left (should never be Gtk::TEXT_DIR_NONE).  	
	///< @param draw_arrow Whether a directional arrow should be drawn on the cursor. . 
  	///< @param area The rectangle to which the output is clipped, or null if the output should not be clipped. 	
	///<
	///< This method is not a style function but merely a convenience function
	///< for drawing the standard cursor shape. The text direction should never be 
	///< Gtk::TEXT_DIR_NONE. The <EM>draw_arrow</EM> parameter should be <EM>false</EM>
	///< unless the cursor is split.

/// @}

/// @class Style style.hh xfc/gtk/style.hh
/// @brief A GtkStyle C++ wrapper class.
///
/// A Style object is used store a widget's style. It contains a variety of graphics contexts
/// available for each widget state (PRELIGHT, NORMAL, ACTIVE, SELECTED and INSENSITIVE), as
/// well as a black and a white graphics context.
///
/// The black GC (black_gc()) and the white GC (white_gc()) are graphics contexts defining the
/// drawing color of black and white, respectively, and can be used in Gdk::Drawable methods.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Style : public G::Object
{
	friend class G::Object;
	
	Style(const Style&);
	Style& operator=(const Style&);

protected:
/// @name Constructors
/// @{

	explicit Style(GtkStyle *style, bool owns_reference = true);
	///< Construct a new Style from an existing GtkStyle.
	///< @param style A pointer to a GtkStyle.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>style</EM> can be a newly created GtkStyle or an existing
	///< GtkStyle (see G::Object::Object).

/// @}
	
public:
	typedef GtkStyle CObjectType;

/// @name Constructors
/// @{

	virtual ~Style();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkStyle* gtk_style() const;
	///< Get a pointer to the GtkStyle structure.

	operator GtkStyle* () const;
	///< Conversion operator; safely converts a Style to a GtkStyle pointer.

	Gdk::Color fg(StateType state_type) const;
	///< Gets the foreground color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	Gdk::Color bg(StateType state_type) const;
	///< Gets the background color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	Gdk::Color light(StateType state_type) const;
	///< Gets the light color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	Gdk::Color dark(StateType state_type) const;
	///< Gets the dark color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	Gdk::Color mid(StateType state_type) const;
	///< Gets the mid-range color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	Gdk::Color text(StateType state_type) const;
	///< Gets the text color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	Gdk::Color base(StateType state_type) const;
	///< Gets the base color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	Gdk::Color text_aa(StateType state_type) const;
	///< Gets the text_aa color (halfway between text/base) for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The Gdk::Color for <EM>state_type</EM>.

	Gdk::Color black() const;
	///< Returns the color black.
	///< @return The Gdk::Color black.

	Gdk::Color white() const;
 	///< Returns the color white.
	///< @return The Gdk::Color white.

	Pointer<Pango::FontDescription> font_description() const;
	///< Gets the font descritpion for the style.
	///< @return A Pango::FontDescription.
	  
	Gdk::GC* black_gc() const;
	///< Gets the graphics context for black.
	///< @return The black graphics context.

	Gdk::GC* white_gc() const;
	///< Gets the graphics context for white.
	///< @return The white graphics context.

	int xthickness() const;
	///< Obtains the current value used for various horizontal padding values in GTK+,
	///< such as frame and bevel size.
	///< @return The current horizontal padding value.

	int ythickness() const;
	///< Obtains the current value used for various vertical padding values in GTK+,
	///< such as frame and bevel size.
	///< @return The current vertical padding value.
	
	Gdk::GC* fg_gc(StateType state_type) const;
	///< Gets the foreground graphics context for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The graphics context for <EM>state_type</EM>.

	Gdk::GC* bg_gc(StateType state_type) const;
	///< Gets the background graphics context for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The graphics context for <EM>state_type</EM>.

	Gdk::GC* light_gc(StateType state_type) const;
	///< Gets the light graphics context for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The graphics context for <EM>state_type</EM>.

	Gdk::GC* dark_gc(StateType state_type) const;
	///< Gets the dark graphics context for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The graphics context for <EM>state_type</EM>.

	Gdk::GC* mid_gc(StateType state_type) const;
	///< Gets the mid graphics context for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The graphics context for <EM>state_type</EM>.

	Gdk::GC* text_gc(StateType state_type) const;
	///< Gets the text graphics context for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The graphics context for <EM>state_type</EM>.

	Gdk::GC* base_gc(StateType state_type) const;
	///< Gets the base graphics context for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The graphics context for <EM>state_type</EM>.

	Gdk::GC* text_aa_gc(StateType state_type) const;
	///< Gets the text_aa graphics context for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The graphics context for <EM>state_type</EM>.

	Gdk::Pixmap* bg_pixmap(StateType state_type) const;
	///< Gets the background pixmap for <EM>state_type</EM>, if any.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @return The background pixmap if there is one, otherwise null.

/// @}
/// @name Methods
/// @{

	void attach(const Gdk::Window& window);
	///< Attaches a style to a Gdk::Window.
	///< @param window A widget's Gdk::Window.
	///<
	///< This process allocates the colors and creates the GC's for the style - specializing
	///< it to a particular visual and colormap. The process may involve the creation of a new style
	///< if the style has already been attached to a window with a different style and colormap.
	///< If a new style is created, the internal GtkStyle pointer is set to point to the new style.
	///< The original style will be dereferenced and the new style will have a reference count
	///< belonging to the caller. If you need to reuse a widget style, rather than store a pointer
	///< to it before calling this method, you should call Gtk::Widget::get_style() after calling
	///< this method.
	///<
	///< <B>Note:</B> This method is only useful when implementing a custom widget that derives directly
	///< from Gtk::Widget. It should be called from the custom widget's virtual <EM>on_realize()</EM> 
	///< method. Otherwise you should never use attach(); use Gtk::Widget::set_style() instead. There
	///< is no detach() method because you don't need to detach the style. Gtk::Widget will detach the
	///< attached style for you (see the Dial example program).

	Pointer<Style> copy() const;
	///< Returns a deep copy of this style.

	Pointer<IconSet> lookup_icon_set(const StockId& stock_id);
	///< Gets the icon set for stock_id.
	///< @param stock_id The stock ID for the icon set.

	void set_background(Gdk::Window& window, StateType state_type);
	///< Sets the background of window to the background color or pixmap specified
	///< by style for the given state.
	///< @param window A Gdk::Window.
	///< @param state_type A state.

	void set_font_description(const Pango::FontDescription& font_desc) const;
	///< Sets the font description for the style.
	///< @param font_desc The new font description.

	void set_fg(StateType state_type, const Gdk::Color& color);
 	///< Sets the foreground color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
     
	void set_bg(StateType state_type, const Gdk::Color& color);
	///< Sets the background color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
      
	void set_light(StateType state_type, const Gdk::Color& color);
	///< Sets the light color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
      
	void set_dark(StateType state_type, const Gdk::Color& color);
	///< Sets the dark color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
      
	void set_mid(StateType state_type, const Gdk::Color& color);
	///< Sets the mid color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
      
	void set_text(StateType state_type, const Gdk::Color& color);
	///< Sets the text color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
      
	void set_base(StateType state_type, const Gdk::Color& color);
	///< Sets the base color for <EM>state_type</EM>.
	///< @param state_type One of the values in the Gtk::StateType enumeration.
	///< @param color The Gdk::Color for <EM>state_type</EM>.
	
	void set_xthickness(int size);
	///< Sets the current value used for various horizontal padding values in GTK+,
	///< such as frame and bevel size
	///< @param size The new horizontal padding value.

	void set_ythickness(int size);
	///< Sets the current value used for various vertical padding values in GTK+,
	///< such as frame and bevel size
	///< @param size The new vertical padding value.
	
	void apply_default_background
	(
		Gdk::Window& window,
		bool set_bg,
		StateType state_type,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0
	);
	///< Apply the default background to <EM>window</EM>.
	///< @param window A Gdk::Window.
	///< @param set_bg <EM>true</EM> if window belongs to a widget.
	///< @param state_type A state.
	///< @param x The x origin of the rectangle to apply the backgroud to.
	///< @param y The y origin of the rectangle to apply the backgroud to.
	///< @param width The width of the rectangle to apply the backgroud to.
	///< @param height The height of the rectangle to apply the backgroud to.
	///< @param area The rectangle to which the output is clipped, or null.
	///<
	///< This method can be called to apply the default background for the current theme
	///< to the specified rectangle in window, before drawing.
	
	Pointer<Gdk::Pixbuf> render_icon
	(
		const IconSource& source,
		TextDirection direction,
		StateType state,
		IconSize size,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Renders the icon specified by source at the given size according to
	///< the given parameters and returns the result in a pixbuf.
	///< @param source The IconSource specifying the icon to render.
	///< @param direction A text direction.
	///< @param state A state.
	///< @param size The size to render the icon at.
	///< @param widget The widget.
	///< @param detail A style detail, or null.
	///< @return A newly-created Gdk::Pixbuf containing the rendered icon, or null.
	///< 
	///< A size of (Gtk::IconSize)-1 means render at the size of the source and don't scale.

	void draw_hline
	(
		Gdk::Window& window,
	 	StateType state_type,
	 	int x1,
	 	int x2,
	 	int y,
	 	const Gdk::Rectangle *area = 0,
	 	Widget *widget = 0,
	 	const char *detail = 0
	);
	///< Draws a horizontal line from (x1, y) to (x2, y) in window using the given style and state.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param x1 The starting x coordinate.
	///< @param x2 The ending x coordinate.
	///< @param y The y coordinate.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_vline
	(
		Gdk::Window& window,
		StateType state_type,
		int y1,
		int y2,
		int x,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a vertical line from (x, y1) to (x, y2) in window using the given style and state.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param y1 The starting y coordinate.
	///< @param y2 The ending y coordinate.
	///< @param x The x coordinate.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_shadow
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a shadow around the given rectangle in window using the given style and state and shadow type.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle.
	///< @param y The y origin of the rectangle.
	///< @param width The width of the rectangle.
	///< @param height The width of the rectangle.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_polygon
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		const Gdk::Point *points,
		int npoints,
		bool fill,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a polygon on window with the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param points An array of Gdk::Points.
	///< @param npoints The length of points.
	///< @param fill <EM>true</EM> if the polygon should be filled.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_arrow
	(
		Gdk::Window& window,
	 	StateType state_type,
	 	ShadowType shadow_type,
	 	ArrowType arrow_type,
	 	bool fill,
	 	int x,
	 	int y,
	 	int width,
	 	int height,
	 	const Gdk::Rectangle *area = 0,
	 	Widget *widget = 0,
	 	const char *detail = 0
	 );
	///< Draws an arrow in the given rectangle on window using the given parameters
	///< in the direction specified by <EM>arrow_type</EM>.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param arrow_type The type of arrow to draw.
	///< @param fill <EM>true</EM> if the arrow tip should be filled.
	///< @param x The x origin of the rectangle to draw the arrow in.
	///< @param y The y origin of the rectangle to draw the arrow in.
	///< @param width The width of the rectangle to draw the arrow in.
	///< @param height The height of the rectangle to draw the arrow in.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_diamond
	(
		Gdk::Window& window,
	 	StateType state_type,
	 	ShadowType shadow_type,
	 	int x,
	 	int y,
	 	int width,
	 	int height,
	 	const Gdk::Rectangle *area = 0,
	 	Widget *widget = 0,
	 	const char *detail = 0
	 );
	///< Draws a diamond in the given rectangle on window using the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle to draw the diamond in.
	///< @param y The y origin of the rectangle to draw the diamond in.
	///< @param width The width of the rectangle to draw the diamond in.
	///< @param height The height of the rectangle to draw the diamond in.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_box
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a box on window with the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the box.
	///< @param y The y origin of the box.
	///< @param width The width of the box.
	///< @param height The height of the box.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_flat_box
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a flat box on window with the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the box.
	///< @param y The y origin of the box.
	///< @param width The width of the box.
	///< @param height The height of the box.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_check
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a check button indicator in the given rectangle on window with the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle to draw the check in.
	///< @param y The y origin of the rectangle to draw the check in.
	///< @param width The width of the rectangle to draw the check in.
	///< @param height The height of the rectangle to draw the check in.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_option
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a radio button indicator in the given rectangle on window with the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle to draw the option in.
	///< @param y The y origin of the rectangle to draw the option in.
	///< @param width The width of the rectangle to draw the option in.
	///< @param height The height of the rectangle to draw the option in.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_tab
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws an option menu tab (the up and down pointing arrows) in the given rectangle
	///< on window using the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle to draw the tab in.
	///< @param y The y origin of the rectangle to draw the tab in.
	///< @param width The width of the rectangle to draw the tab in.
	///< @param height The height of the rectangle to draw the tab in.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_shadow_gap
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		PositionType gap_side,
		int gap_x,
		int gap_width,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a shadow gap around the given rectangle on window using the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle.
	///< @param y The y origin of the rectangle.
	///< @param width The width of the rectangle.
	///< @param height The height of the rectangle.
	///< @param gap_side A position.
	///< @param gap_x The x origin of the gap.
	///< @param gap_width The width of the gap.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_box_gap
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		PositionType gap_side,
		int gap_x,
		int gap_width,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a box gap around the given rectangle on window using the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle.
	///< @param y The y origin of the rectangle.
	///< @param width The width of the rectangle.
	///< @param height The height of the rectangle.
	///< @param gap_side A position.
	///< @param gap_x The x origin of the gap.
	///< @param gap_width The width of the gap.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_extension
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		PositionType gap_side,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws an extension using the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle.
	///< @param y The y origin of the rectangle.
	///< @param width The width of the rectangle.
	///< @param height The height of the rectangle.
	///< @param gap_side A position.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_focus
	(
		Gdk::Window& window,
		StateType state_type,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a focus indicator around the given rectangle on window using this style.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param x The x origin of the rectangle around which to draw a focus indicator.
	///< @param y The y origin of the rectangle around which to draw a focus indicator.
	///< @param width The width of the rectangle around which to draw a focus indicator.
	///< @param height The height of the rectangle around which to draw a focus indicator.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_slider
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		Orientation orientation,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a slider on window with the given paramters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle to draw the slider in.
	///< @param y The y origin of the rectangle to draw the slider in.
	///< @param width The width of the rectangle to draw the slider in.
	///< @param height The height of the rectangle to draw the slider in.
	///< @param orientation The orientation of the slider.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_handle
	(
		Gdk::Window& window,
		StateType state_type,
		ShadowType shadow_type,
		int x,
		int y,
		int width,
		int height,
		Orientation orientation,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a handle on window with the given paramters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param shadow_type The type of shadow to draw.
	///< @param x The x origin of the rectangle to draw the handle in.
	///< @param y The y origin of the rectangle to draw the handle in.
	///< @param width The width of the rectangle to draw the handle in.
	///< @param height The height of the rectangle to draw the handle in.
	///< @param orientation The orientation of the handle.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_expander
	(
		Gdk::Window& window,
		StateType state_type,
		int x,
		int y,
		ExpanderStyle expander_style,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws an expander on window with the given paramters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param x The x origin of the expander.
	///< @param y The y origin of the expander.
	///< @param expander_style The expander style to draw.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_layout
	(
		Gdk::Window& window,
		StateType state_type,
		bool use_text,
		int x,
		int y,
		Pango::Layout& layout,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a Pango::Layout on window with the given paramters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param use_text <EM>true</EM> to draw the layout with the text graphics context.
	///< @param x The x origin of the layout.
	///< @param y The y origin of the layout.
	///< @param layout A Pango::Layout.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.

	void draw_resize_grip
	(
		Gdk::Window& window,
		StateType state_type,
		Gdk::WindowEdge edge,
		int x,
		int y,
		int width,
		int height,
		const Gdk::Rectangle *area = 0,
		Widget *widget = 0,
		const char *detail = 0
	);
	///< Draws a resize grip in the given rectangle on window using the given parameters.
	///< @param window A Gdk::Window to draw on.
	///< @param state_type A state.
	///< @param edge The window edge in which to draw the resize grip, currently only WINDOW_EDGE_SOUTH_EAST.
	///< @param x The x origin of the rectangle in which to draw the resize grip.
	///< @param y The y origin of the rectangle in which to draw the resize grip.
	///< @param width The width of the rectangle in which to draw the resize grip.
	///< @param height The height of the rectangle in which to draw the resize grip.
	///< @param area The rectangle to which the output is clipped, or null.
	///< @param widget The widget, or null.
	///< @param detail A style detail, or null.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/style.inl>

#endif // XFC_GTK_STYLE_HH

