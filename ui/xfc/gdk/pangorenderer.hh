/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
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
 
/// @file xfc/gdk/pangorenderer.hh
/// @brief A C++ wrapper for GDK Pango interaction.
///
/// Pango is the text layout system used by GDK and GTK+. The functions and types module
/// are used to render Pango objects to GDK drawables, and also extend the set of Pango
/// attributes to include stippling and embossing.
///
/// Creating a Pango::Layout object is the first step in rendering text, and requires 
/// getting a handle to a Pango::Context. For GTK+ programs, you'll usually want to use 
/// Gtk::Widget::get_context(), or Gtk::Widget::create_pango_layout(), rather than using
/// the lowlevel Gdk::pango_context_get_for_screen(). Once you have a PangoLayout, you can
/// set the text and attributes of it with Pango functions like Pango::Layout::set_text()
/// and get its size with Pango::Layout::get_size(). Note that Pango uses a fixed point
/// system internally, so convert between Pango units and pixels using the PANGO_SCALE or
/// PANGO_PIXELS() macro.
///
/// Rendering a Pango layout is done most simply with Gdk::Drawable::draw_layout(); you
/// can also draw pieces of the layout with Gdk::Drawable::draw_layout() or 
/// Gdk::Drawable::draw_glyphs(). Gdk::PangoRenderer is a subclass of Pango::Renderer
/// that is used internally to implement these functions. Using it directly or subclassing
/// it can be useful in some cases. See the GdkPangoRenderer documentation for details.

#ifndef XFC_GDK_PANGO_RENDERER_HH
#define XFC_GDK_PANGO_RENDERER_HH

#ifndef XFC_PANGO_RENDERER_HH
#include <xfc/pango/renderer.hh>
#endif

#ifndef __GDK_PANGO_H__
#include <gdk/gdkpango.h>
#endif

namespace Xfc {

namespace Gdk {

class Bitmap;
class Color;
class Drawable;
class GC;
class Screen;

/// @class PangoRenderer pangorenderer.hh xfc/gdk/pangorenderer.hh
/// @brief A GdkPangoRenderer C++ wrapper class.
///
/// Gdk::PangoRenderer is a subclass of Pango::Renderer which is used for rendering 
/// Pango objects into GDK drawables. The default renderer for a particular screen
/// is obtained with get_default(); Pango functions like Pango::Renderer::draw_layout()
/// and Pango::Renderer::draw_layout_line() are then used to draw objects with the renderer. 
///
/// In most simple cases, applications can just use Gdk::Drawable::draw_layout(), and don't
/// need to directly use Gdk::PangoRenderer at all. Using the Gdk::PangoRenderer directly
/// is most useful when working with a transformation such as a rotation, because the Pango
/// drawing functions take user space coordinates (coordinates before the transformation)
/// instead of device coordinates. 

class PangoRenderer : public Pango::Renderer
{
	friend class G::Object;
	
	PangoRenderer(const PangoRenderer&);
	PangoRenderer& operator=(const PangoRenderer&);
	
protected:
/// @name Constructors
/// @{

	explicit PangoRenderer(GdkPangoRenderer *renderer, bool owns_reference = false);
	///< Construct a new PangoRenderer from an existing GdkPangoRenderer.
	///< @param renderer A pointer to a GdkPangoRenderer.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>renderer</EM> can be a newly created GdkPangoRenderer or an existing
	///< GdkPangoRenderer. (see G::Object::Object).
	
/// @}
public:
	typedef GdkPangoRenderer CObjectType;

/// @name Constructors
/// @{
	
	PangoRenderer(const Screen& screen);
	///< Constructs a new PangoRenderer for <EM>screen</EM>. 
	///< @param screen A Gdk::Screen.
	///<
	///< Normally you can use the results of get_default() rather than creating a new renderer.
	///< The PangoRenderer is created with a reference count of one that the caller owns.

	virtual ~PangoRenderer();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GdkPangoRenderer* gdk_pango_renderer() const;
	///< Get a pointer to the GdkPangoRenderer structure.

	operator GdkPangoRenderer* () const;
	///< Conversion operator; safely converts an PangoRenderer to a GdkPangoRenderer pointer.

/// @}
/// @name Accessors
/// @{

	static Gdk::PangoRenderer* get_default(const Screen& screen);
	///< Gets the default Gdk::PangoRenderer for a screen. 
	///< @param screen A Gdk::Screen.
	///< @return The default PangoRenderer for <EM>screen</EM>. 
	///<
	///< This default renderer is shared by all users of the display, so properties such
	///< as the color or transformation matrix set for the renderer may be overwritten by 
	///< functions such as Gdk::Drawable::draw_layout(). Before using the renderer, you
	///< need to call set_drawable() and set_gc() to set the drawable and graphics context
	///< to use for drawing. 
	///<
	///< Note, the renderer is owned by GTK+ and will be kept around until the screen is closed.
	 
/// @}
/// @name Methods
/// @{

	void set_drawable(Drawable *drawable);
	///< Sets the drawable the renderer draws to.
	///< @param drawable The new target drawable, or null to unset.

	void set_gc(const GC *gc);
	///< Sets the GC the renderer draws with.
	///< @param gc The new GC to use for drawing, or null to unset. 
	///< 
	///< Note that the GC must not be modified until it is unset by calling the function
	///< again with null for the gc parameter, since GDK may make internal copies of the
	///< GC which won't be updated to follow changes to the original GC.

	void set_stipple(Pango::RenderPart part, Bitmap *stipple);
	///< Sets the stipple for one render part (foreground, background, underline, etc).
	///< @param part The part to render with the stipple. 
	///< @param stipple The new stipple value, or null to unset.	
	///< 	 
	///< Note that this is overwritten when iterating through the individual styled runs
	///< of a Pango::Layout or Pango::LayoutLine. This function is thus only useful when
	///< you call low level functions like Pango::Renderer::draw_glyphs() directly.

	void set_override_color(Pango::RenderPart part, const Color *color);
	///< Sets the color for a particular render part (foreground, background, underline, etc),
	///< overriding any attributes on the layouts renderered with this renderer.
	///< @param part The part to render to set the color of. 
	///< @param color The color to use, or null to unset a previously set override color.
	
/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/pangorenderer.inl>

#endif // XFC_GDK_PANGO_RENDERER_HH

