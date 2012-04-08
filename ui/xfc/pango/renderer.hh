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
 
/// @file xfc/pango/renderer.hh
/// @brief A PangoRenderer C++ wrapper interface.
///
/// Provides Renderer, a base class for objects that are used to render Pango
/// objects such as Pango::GlyphString and Pango::Layout.

#ifndef XFC_PANGO_RENDERER_HH
#define XFC_PANGO_RENDERER_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_PANGO_TYPES_HH
#include <xfc/pango/types.hh>
#endif

#ifndef __PANGO_RENDERER_H__
#include <pango/pango-renderer.h>
#endif

namespace Xfc {

namespace Pango {

class Color;
class Font;
class GlyphString;
class Layout;
class LayoutLine;
class Rectangle;
class Matrix;

/// @enum RenderPart
/// Defines different items to render for such purposes as setting colors.

enum RenderPart
{
	RENDER_PART_FOREGROUND = PANGO_RENDER_PART_FOREGROUND, ///< The text itself.
	RENDER_PART_BACKGROUND = PANGO_RENDER_PART_BACKGROUND, ///< The area behind the text.
	RENDER_PART_UNDERLINE = PANGO_RENDER_PART_UNDERLINE, ///< Underlines.
	RENDER_PART_STRIKETHROUGH = PANGO_RENDER_PART_STRIKETHROUGH ///< Strikethrough lines.
};

/// @class Renderer renderer.hh xfc/pango/renderer.hh
/// @brief A PangoRenderer C++ wrapper class.
///
/// Pango::Renderer is a base class for objects that are used to render
/// Pango objects such as Pango::GlyphString and Pango::Layout.

class Renderer : public G::Object
{
	friend class G::Object;
	
	Renderer(const Renderer&);
	Renderer& operator=(const Renderer&);
	
protected:
/// @name Constructors
/// @{

	explicit Renderer(PangoRenderer *renderer, bool owns_reference = false);
	///< Construct a new Renderer from an existing PangoRenderer.
	///< @param renderer A pointer to a PangoRenderer.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>renderer</EM> can be a newly created PangoRenderer or an existing
	///< PangoRenderer. (see G::Object::Object).
	
/// @}
public:
	typedef PangoRenderer CObjectType;

/// @name Constructors
/// @{
	virtual ~Renderer();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	PangoRenderer* pango_renderer() const;
	///< Get a pointer to the PangoRenderer structure.

	operator PangoRenderer* () const;
	///< Conversion operator; safely converts an Renderer to a PangoRenderer pointer.

	Pointer<Color> get_color(RenderPart part) const;
	///< Gets the current rendering color for the specified <EM>part</EM>.
	///< @param part The part to get the color for.
	///< @return The color for the specified part, or a null pointer.
	///<
	///< The method returns null if the color for the specified <EM>part</EM> hasn't
	///< been set and should be inherited from the environment.
 
	Matrix get_matrix() const;
	///< Gets the transformation matrix that will be applied when rendering (see set_matrix()).
	///< @return The matrix, or null if no matrix has been set (which is the same as the identity matrix). 

/// @}
/// @name Methods
/// @{

	void draw_layout(const Layout& layout, int x, int y);
	///< Draws <EM>layout</EM> with the renderer.
	///< @param layout A Pango::Layout.
	///< @param x The X position of left edge of baseline, in user space coordinates in Pango units.
	///< @param y The Y position of left edge of baseline, in user space coordinates in Pango units.

	void draw_layout_line(const LayoutLine& line, int x, int y);
	///< Draws <EM>line</EM> with the renderer.
	///< @param line A Pango::LayoutLine.
	///< @param x The X position of left edge of baseline, in user space coordinates in Pango units.
	///< @param y The Y position of left edge of baseline, in user space coordinates in Pango units.

	void draw_glyphs(const Font& font, const GlyphString& glyphs, int x, int y);
	///< Draws the glyphs in <EM>glyphs</EM> with the renderer.
	///< @param font A Pango::Font.
	///< @param glyphs A Pango::GlyphString.
	///< @param x The X position of left edge of baseline, in user space coordinates in Pango units.
	///< @param y The Y position of left edge of baseline, in user space coordinates in Pango units.

	void draw_rectangle(RenderPart part, int  x, int  y, int width, int height);
	///< Draws an axis-aligned rectangle in user space coordinates with the renderer.
	///< @param part The type of object this rectangle is part of.
	///< @param x The x position at which to draw the rectangle, in user space coordinates in Pango units.
	///< @param y The y position at which to draw the rectangle, in user space coordinates in Pango units.
	///< @param width The width of rectangle in PangoUnits in user space coordinates.
	///< @param height The height of rectangle in PangoUnits in user space coordinates.

	void draw_rectangle(RenderPart part, const Rectangle& rectangle);
	///< Draws an axis-aligned rectangle in user space coordinates with the renderer.
	///< @param part The type of object this rectangle is part of.
	///< @param rectangle The rectangle to draw, in user space coordinates in Pango units.

	void draw_error_underline(int x, int y, int width, int height);
	///< Draw a squiggly line that approximately covers the given rectangle
	///< in the style of an underline used to indicate a spelling error.
	///< @param x The X coordinate of underline, in Pango units in user coordinate system.
	///< @param y The Y coordinate of underline, in Pango units in user coordinate system.
	///< @param width The width of underline, in Pango units in user coordinate system.
	///< @param height The height of underline, in Pango units in user coordinate system.
	///< 
	///< The width of the underline is rounded to an integer number of up/down 
	///< segments and the resulting rectangle is centered in the original rectangle.

	void draw_trapezoid(RenderPart part, double y1, double x11, double x21, double y2, double x12, double x22);
	///< Draws a trapezoid with the parallel sides aligned with the X axis using
	///< the given renderer (coordinates are in device space).
	///< @param part The type of object this trapezoid is part of.
	///< @param y1 The Y coordinate of top of trapezoid.
	///< @param x11 The X coordinate of left end of top of trapezoid.
	///< @param x21 The X coordinate of right end of top of trapezoid.
	///< @param y2 The Y coordinate of bottom of trapezoid.
	///< @param x12: X coordinate of left end of bottom of trapezoid.
	///< @param x22: X coordinate of right end of bottom of trapezoid.

	void draw_glyph(const Font& font, Glyph glyph, double x, double y);
	///< Draws a single glyph with coordinates in device space.
	///< @param font A Pango::Font.
	///< @param glyph The glyph index of a single glyph.
	///< @param x The X coordinate of left edge of baseline of glyph.
	///< @param y The Y coordinate of left edge of baseline of glyph.

	void activate();
	///< Does initial setup before rendering operations on the renderer.
	///< deactivate() should be called when done drawing. Calls such as
	///< draw_layout() automatically activate the layout before drawing
	///< on it. Calls to activate() and deactivate() can be nested and
	///< the renderer will only be initialized and deinitialized once.

	void deactivate();
	///< Cleans up after rendering operations on the renderer (see activate() for details).

	void part_changed(RenderPart part);
	///< Informs Pango that the way that the renderering is done for <EM>part</EM> has changed
	///< in a way that would prevent multiple pieces being joined together into one drawing call.
	///< @param part The part for which rendering has changed.
	///<	 
	///< For instance, if a subclass of Renderer was to add a stipple option for drawing underlines,
	///< it needs to call:
	///<
	///< @code
	///< renderer->part_changed(Pango::RENDER_PART_UNDERLINE);
	///< @endcode
	///<
	///< when the stipple changes or underlines with different stipples might be joined together.
	///< Pango automatically calls this method for changes to colors (see set_color()).

	void set_color(RenderPart part, const Color *color);
	///< Sets the color for <EM>part</EM> of the rendering.
	///< @param part The <EM>part</EM> to change the color of.
	///< @param color The new color or null to unset the current color.

	void set_matrix(const Matrix *matrix);
	///< Sets the transformation matrix that will be applied when rendering.	
	///< @param matrix A Pango::Matrix, or null to unset any existing matrix.
	///<
	///< No matrix set is the same as setting the identity matrix.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/renderer.inl>

#endif // XFC_PANGO_RENDERER_HH

