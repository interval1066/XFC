/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/gdk/drawable.hh
/// @brief A GdkDrawable C++ wrapper interface.
///
/// Provides Drawable, a drawing primitive that provides methods for drawing points, lines, arcs, and text.

#ifndef XFC_GDK_DRAWABLE_HH
#define XFC_GDK_DRAWABLE_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GDK_GC_HH
#include <xfc/gdk/gc.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

namespace Xfc {

namespace Pango {
class Font;
class GlyphString;
class Layout;
class LayoutLine;
class Matrix;
}

namespace Gdk {

class Display;
class Image;
class Pixbuf;
class Segment;
class Screen;
class Visual;

/// @class Drawable drawable.hh xfc/gdk/drawable.hh
/// @brief A GdkDrawable C++ wrapper class.
///
/// Drawable provides support for drawing points, lines, arcs and text onto what
/// are called 'drawables'. Drawables, as the name suggests, are things which 
/// support drawing onto them, and are either Gdk::Window or Gdk::Pixmap objects.
///
/// Many of the drawing operations take a Gdk::GC argument, which represents a 
/// graphics context. This Gdk::GC contains a number of drawing attributes such
/// as foreground color, background color and line width, and is used to reduce
/// the number of arguments needed for each drawing operation. See the Graphics
/// Contexts section of the GDK reference documentationfor more information.

class Drawable : public G::Object
{
	friend class G::Object;

	Drawable(const Drawable&);
	Drawable& operator=(const Drawable&);

protected:
/// @name Constructors
/// @{

	explicit Drawable(GdkDrawable *drawable, bool owns_reference = true);
	///< Construct a new Drawable from an existing GdkDrawable.
	///< @param drawable A pointer to a GdkDrawable.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>drawable</EM> can be a newly created GdkDrawable or an existing
	///< GdkDrawable. (see G::Object::Object).

/// @}

public:
	typedef GdkDrawable CObjectType;

/// @name Constructors
/// @{

	virtual ~Drawable() = 0;
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GdkDrawable* gdk_drawable() const;
	///< Get a pointer to the GdkDrawable structure.

	operator GdkDrawable* () const;
	///< Conversion operator; safely converts a Drawable to a GdkDrawable pointer.

	void get_size(int *width, int *height) const;
	///< Fills <EM>width</EM> and <EM>height</EM> with the size of drawable; width or
	///< height can be null if you only want the other one.
	///< @param width The location to store drawable's width, or null.
	///< @param height The location to store drawable's height, or null.
	///<
	///< On the X11 platform, if drawable is a Gdk::Window, the returned size is
	///< the size reported in the most-recently-processed configure event, rather 
	///< than the current size on the X server.

	Colormap* get_colormap() const;
	///< Gets the Colormap for the drawable, if one is set; returns null otherwise.
	///< @return The colormap, or null.

	const Visual* get_visual() const;
	///< Gets the Visual describing the pixel format of the drawable.
	/// @return A Visual.

	int get_depth() const;
	///< Obtains the bit depth of the drawable, that is, the number of bits that 
	///< make up a pixel in the drawable's visual. 
	///< @return The number of bits per pixel.
	///<
	///< Examples are 8 bits per pixel, 24 bits per pixel, etc.

	Screen*	get_screen() const;
	///< Gets the Screen associated with the drawable.
	///< @return The Screen associated with the drawable.

	Display* get_display() const;
	///< Gets the Display associated with the drawable.
	///< @return The Display associated with the drawable.

	Pointer<Image> get_image(int x, int y, int width, int height) const;
	///< Obtains the pixels from a server-side drawable as a client-side Gdk::Image.
	///< @param x The X coordinate on the drawable.
	///< @param y The Y coordinate on the drawable.
	///< @param width The width of the region to get.
	///< @param height The height of the region to get.
	///< @return A smart pointer to a new Gdk::Image containing the contents of the drawable.
	///<
	///< A Gdk::Image stores client-side image data (pixels). In contrast,
	///< Gdk::Pixmap and Gdk::Window are server-side objects. The format of a
	///< Gdk::Image depends on the Visual of the current display, which makes
	///< manipulating Gdk::Image extremely difficult; therefore, in most cases
	///< you should use Gdk::Pixbuf::get_from_drawable() instead of this 
	///< lower-level method. A Gdk::Pixbuf contains image data in a canonicalized
	///< RGB format, rather than a display-dependent format. Of course, there's a
	///< convenience vs. speed tradeoff here, so you'll want to think about what
	///< makes sense for your application.
	///<
	///< The x, y, width, and height arguments define the region of drawable to
	///< obtain as an image. You would usually copy image data to the client side
	///< if you intend to examine the values of individual pixels, for example to
	///< darken an image or add a red tint. It would be prohibitively slow to make
	///< a round-trip request to the windowing system for each pixel, so instead
	///< you get all of them at once, modify them, then copy them all back at once.
	///<
	///< If the X server or other windowing system backend is on the local machine,
	///< this method may use shared memory to avoid copying the image data. If the
	///< source drawable is a Gdk::Window and partially offscreen or obscured, then
	///< the obscured portions of the returned image will contain undefined data.

	Pointer<Region> get_clip_region() const;
	///< Computes the region of a drawable that potentially can be written to 
	///< by drawing primitives. 
	///< @return A smart pointer to the newly allocated Region.
	///<
	///< This region will not take into account the clip region for the GC, 
	///< and may also not take into account other factors such as if the window
	///< is obscured by other windows, but no area outside of this region will
	///< be affected by drawing primitives.

	Pointer<Region> get_visible_region() const;
	///< Computes the region of a drawable that is potentially visible.
	///< @return A smart pointer to the newly allocated Region.
	///<
	///< This does not necessarily take into account if the window is obscured
	///< by other windows, but no area outside of this region is visible.

	Pointer<Pixbuf> get_pixbuf(int x, int y, int width, int height, Colormap *colormap = 0) const;
	// Returns a new Pixbuf created from this drawable. If drawable is a pixmap a colormap must be specified.

/// @}
/// @name Methods
/// @{

	void set_colormap(Colormap *colormap);
	///< Sets the colormap associated with the drawable. 
	///< @param colormap A Colormap.
	///<
	///< Normally this will happen automatically when the drawable is created; you only need to use
	///< this method if the drawable-creating function did not have a way to determine the colormap, 
	///< and you then use drawable operations that require a colormap. The colormap for all drawables
	///< and graphics contexts you intend to use together should match. i.e. when using a GdkGC to draw
	///< to a drawable, or copying one drawable to another, the colormaps should match.

	void copy_to_image(Image& image, int src_x, int src_y, int dest_x, int dest_y, int width, int height);
	///< Copies a portion of the drawable into the specified client side <EM>image</EM>
	///< (see get_image() for further details).
	///< @param image A Gdk::Image to copy the drawable portion to.
	///< @param src_x The x coordinate on the drawable.
	///< @param src_y The y coordinate on the drawable.
	///< @param dest_x The x coordinate within the image.
	///< @param dest_y The y coordinate within the image.
	///< @param width The width of the region to get.
	///< @param height The height of the region to get.

	void copy_to_image(Image& image, const Rectangle& src_rect, int dest_x, int dest_y);
	///< Copies a portion of the drawable into the specified client side <EM>image</EM>
	///< (see get_image() for further details).
	///< @param image A Gdk::Image to copy the drawable portion to.
	///< @param src_rect The rectangular coordinates on the drawable.	
	///< @param dest_x The x coordinate within the image.
	///< @param dest_y The y coordinate within the image.

	void draw_point(const GC& gc, int x, int y);
	///< Draws a point, using the foreground color and other attributes of the GC.
	///< @param gc A GC.
	///< @param x The X coordinate of the point.
	///< @param y The y coordinate of the point.

	void draw_point(const GC& gc, const Point& point);
	///< Draws a point, using the foreground color and other attributes of the GC.
	///< @param gc A GC.
	///< @param point A Point holding the X and Y coordinates of the point.

	void draw_points(const GC& gc, const std::vector<Point>& points);
	///< Draws a number of points, using the foreground color and other attributes of the GC.
	///< @param gc A GC.
	///< @param points A reference to a vector of Point holding the points to draw.

	void draw_line(const GC& gc, int x1, int y1, int x2, int y2);
	///< Draws a line, using the foreground color and other attributes of the GC.
	///< @param gc A GC.
	///< @param x1 The X coordinate of the start point.
	///< @param y1 The y coordinate of the start point.
	///< @param x2 The X coordinate of the end point.
	///< @param y2 The y coordinate of the end point.

	void draw_line(const GC& gc, const Segment& seg);
	///< Draws a line, using the foreground color and other attributes of the GC.
	///< @param gc A GC.
	///< @param seg A Segment that holds the start and end coordinates of the line.

	void draw_lines(const GC& gc, const std::vector<Point>& points);
	///< Draws a series of lines connecting the given points. 
	///< @param gc A GC.
	///< @param points A reference to a vector of Point holding the endpoints of the lines.
	///<
	///< The way in which joins between lines are drawn is determined by the 
	///< CapStyle value in the GC. This can be set with Gdk::GC::set_line_attributes().

	void draw_segments(const GC& gc, const std::vector<Segment>& segs);
	///< Draws a number of unconnected lines.
	///< @param gc A GC.
	///< @param segs A reference to a vector of Segment specifying the start and end points of the lines.
	
	void draw_rectangle(const GC& gc, int x, int y, int width, int height, bool filled = true);
	///< Draws a rectangular outline or filled rectangle, using the foreground color
	///< and other attributes of the GC.
	///< @param gc A GC.
	///< @param x The X coordinate of the left edge of the rectangle.
	///< @param y The Y coordinate of the top edge of the rectangle.
	///< @param width The width of the rectangle.
	///< @param height The height of the rectangle.
	///< @param filled Set <EM>true</EM> if the rectangle should be filled.
	///<
	///< A rectangle drawn filled is 1 pixel smaller in both dimensions than a
	///< rectangle outlined. Calling window->draw_rectangle(gc, 0, 0, 20, 20, true)
	///< results in a filled rectangle 20 pixels wide and 20 pixels high. Calling
	///< window->gdk_draw_rectangle(gc, 0, 0, 20, 20, false) results in an outlined
	///< rectangle with corners at (0, 0), (0, 20), (20, 20), and (20, 0), which
	///< makes it 21 pixels wide and 21 pixels high.

	void draw_rectangle(const GC& gc, const Rectangle& rectangle, bool filled = true);
	///< Draws a rectangular outline or filled rectangle, using the foreground color
	///< and other attributes of the GC.
	///< @param gc A GC.
	///< @param rectangle A Rectangle holding the position and size of the rectangle to draw.
	///< @param filled Set <EM>true</EM> if the rectangle should be filled.
	///<
	///< A rectangle drawn filled is 1 pixel smaller in both dimensions than a
	///< rectangle outlined. Calling window->draw_rectangle(gc, 0, 0, 20, 20, true)
	///< results in a filled rectangle 20 pixels wide and 20 pixels high. Calling
	///< window->gdk_draw_rectangle(gc, 0, 0, 20, 20, false) results in an outlined
	///< rectangle with corners at (0, 0), (0, 20), (20, 20), and (20, 0), which
	///< makes it 21 pixels wide and 21 pixels high.

	void draw_arc(const GC& gc, int x, int y, int width, int height, int angle1, int angle2, bool filled = true);
	///< Draws an arc or a filled 'pie slice'.
	///< @param gc A GC.
	///< @param x The X coordinate of the left edge of the bounding rectangle.
	///< @param y The Y coordinate of the top edge of the bounding rectangle.
	///< @param width The width of the bounding rectangle.
	///< @param height The height of the bounding rectangle.
	///< @param angle1 The start angle of the arc, relative to the 3 o'clock position,
	///<               counter-clockwise, in 1/64ths of a degree.
	///< @param angle2 The end angle of the arc, relative to angle1, in 1/64ths of a degree.
	///< @param filled Set <EM>true</EM> if the arc should be filled, producing a 'pie slice'.
	///<
	///< The arc is defined by the bounding rectangle of the entire ellipse, and the
	///< start and end angles of the part of the ellipse to be drawn.

	void draw_arc(const GC& gc, const Rectangle& rectangle, int angle1, int angle2, bool filled = true);
	///< Draws an arc or a filled 'pie slice'.
	///< @param gc A GC.
	///< @param rectangle A Rectangle holding the position and size of the bounding rectangle of the ellipse.
	///< @param angle1 The start angle of the arc, relative to the 3 o'clock position,
	///<               counter-clockwise, in 1/64ths of a degree.
	///< @param angle2 The end angle of the arc, relative to angle1, in 1/64ths of a degree.
	///< @param filled Set <EM>true</EM> if the arc should be filled, producing a 'pie slice'.
	///<
	///< The arc is defined by the bounding rectangle of the entire ellipse, and the
	///< start and end angles of the part of the ellipse to be drawn.

	void draw_polygon(const GC& gc, const std::vector<Point>& points, bool filled = true);
	///< Draws an outlined or filled polygon.
	///< @param gc A GC.
	///< @param points A reference to a vector of Point specifying the points making up the polygon.
	///< @param filled Set <EM>true</EM> if the polygon should be filled.
	///<
	///< The polygon is closed automatically, connecting the last point to the first point if necessary.

	void draw_drawable(const GC& gc, const Drawable& src, int xsrc, int ysrc, int xdest, int ydest, int width, int height);
	///< Copies the <EM>width</EM> x <EM>height</EM> region of src at coordinates (xsrc, ysrc)
	///< to coordinates (xdest, ydest) in the drawable.
	///< @param gc A GC sharing the drawable's visual and colormap.
	///< @param src Another Drawable.
	///< @param xsrc The X position in <EM>src</EM> of the rectangle to draw.
	///< @param ysrc The Y position in <EM>src</EM> of the rectangle to draw.
	///< @param xdest The X position in the drawable where the rectangle should be drawn.
	///< @param ydest The Y position in the drawable where the rectangle should be drawn.
	///< @param width The width of rectangle to draw, or -1 for entire src width.
	///< @param height The height of rectangle to draw, or -1 for entire src height.
	///<
	///< The <EM>width</EM> and/or <EM>height</EM> may be given as -1, in which case
	///< the entire src drawable will be copied. Most fields in gc are not used for this
	///< operation, but notably the clip mask or clip region will be honored. The source
	///< and destination drawables must have the same visual and colormap, or errors will
	///< result. (On X11, failure to match visual/colormap results in a BadMatch error
	///< from the X server.) A common cause of this problem is an attempt to draw a bitmap
	///< to a color drawable. The way to draw a bitmap is to set the bitmap as a clip mask
	///< on your GC, then use draw_rectangle() to draw a rectangle clipped to the bitmap.

	void draw_drawable(const GC& gc, const Drawable& src, const Rectangle& src_rect, int xdest, int ydest);
	///< Copies the <EM>dest.width</EM> x <EM>dest.height</EM> region of src at coordinates (xsrc, ysrc)
	///< to coordinates (dest.x, dest.y) in the drawable.
	///< @param gc A GC sharing the drawable's visual and colormap.
	///< @param src Another Drawable.
	///< @param src_rect A rectangle holding the position and size of the <EM>src</EM> region to draw in the drawable.
	///< @param xdest The X position in the drawable where the rectangle should be drawn.
	///< @param ydest The Y position in the drawable where the rectangle should be drawn.
	///<
	///< Most fields in <EM>gc</EM> are not used for this operation, but notably the
	///< clip mask or clip region will be honored. The source and destination drawables
	///< must have the same visual and colormap, or errors will result. (On X11, failure
	///< to match visual and colormap results in a BadMatch error from the X server.) A
	///< common cause of this problem is an attempt to draw a bitmap to a color drawable.
	///< The way to draw a bitmap is to set the bitmap as a clip mask on your GC, then
	///< use draw_rectangle() to draw a rectangle clipped to the bitmap.

	void draw_image(const GC& gc, const Image& image, int xsrc, int ysrc, int xdest, int ydest, int width, int height);
	///< Draws an Image onto the drawable. 
	///< @param gc A GC.
	///< @param image The Gdk::Image to draw.
	///< @param xsrc The left edge of the source rectangle within the image.
	///< @param ysrc The top of the source rectangle within the image.
	///< @param xdest The x coordinate of the destination within the drawable.
	///< @param ydest The y coordinate of the destination within the drawable.
	///< @param width The width of the area to be copied, or -1 to make the area
	///<              extend to the right edge of image.
	///< @param height The height of the area to be copied, or -1 to make the area
	///<               extend to the bottom edge of image.
	///<
	///< The depth of the Image must match the depth of the Drawable.

	void draw_trapezoids(const GC& gc, std::vector<Trapezoid>& trapezoids);
	///< Draws a set of anti-aliased trapezoids. 
	///< @param gc A GC.
	///< @param trapezoids A vector of Trapezoid
	///<	
	///< The trapezoids are combined using saturation addition, then drawn over the background
	///< as a set. This is low level functionality used internally to implement rotated underlines
	///< and backgrouds when rendering a Pango::Layout and is likely not useful for applications.
	
	void draw_glyphs
	(
		const GC& gc, 
		const Pango::Font& font, 
		int x, 
		int y, 
		const Pango::GlyphString& glyphs,
		const Pango::Matrix *matrix = 0
	);
	///< Renders a Pango::GlyphString onto a drawable, possibly transforming the layed-out coordinates
	///< through a transformation matrix. 
	///< @param gc A GC.
	///< @param font The font in which to draw the string.
	///< @param x The X coordinate of the start of the string (in Pango units in user space coordinates). 
	///< @param y The Y coordinate of the baseline (in Pango units in user space coordinates).
	///< @param glyphs The glyph string to draw.
	///< @param matrix A Pango::Matrix, or null.
	///<
	///< A glyph is a character in a font. This method draws a sequence of glyphs. To obtain
	///< a sequence of glyphs you have to understand a lot about internationalized text 
	///< handling, which you don't want to understand; thus, use draw_layout() instead
	///< of this method, draw_layout() handles the details.
	///<	
	///< Note that the transformation matrix for font is not changed, so to produce correct
	///< rendering results, the font must have been loaded using a Pango::Context with an
	///< identical transformation matrix to that passed in to this method. This is a low-level
	///< method; 99% of text rendering should be done using draw_layout() instead.
	
	void draw_layout_line
	(
		const GC& gc,
		int x,
		int y,
		const Pango::LayoutLine& line,
		const Color *foreground = 0,
		const Color *background = 0
	);
	///< Render a Pango::LayoutLine onto the drawable.
	///< @param gc The base graphics context to use.
	///< @param x The X position of the start of string (in pixels).
	///< @param y The Y position of the baseline (in pixels).
	///< @param line A Pango::LayoutLine.
	///< @param foreground The foreground override color, or null for none.
	///< @param background The background override color, or null for none
 	///<
	///< If foreground and/or background colors are specified these will override
	///< the layout's normal colors. The colors need not be allocated.

	void draw_layout
	(
		const GC& gc,
		int x,
		int y,
		const Pango::Layout& layout,
		const Color *foreground = 0,
		const Color *background = 0
	);
	///< Render a Pango::Layout onto the drawable.
	///< @param gc The base graphics context to use.
	///< @param x The X position of the left of the layout (in pixels).
	///< @param y The Y position of the top of the layout (in pixels).
	///< @param layout A Pango::Layout
	///< @param foreground The foreground override color, or null for none.
	///< @param background The background override color, or null for none
 	///<
	///< If foreground and/or background colors are specified these will override
	///< the layout's normal colors. The colors need not be allocated.

	void draw_pixbuf
	(
		const GC *gc,
		const Pixbuf& pixbuf,
		int src_x,
		int src_y,
		int dest_x,
		int dest_y,
		int width,
		int height,
		RgbDither dither,
		int x_dither,
		int y_dither
	);
	///< Renders a rectangular portion of a pixbuf to a drawable. 
	///< @param gc A GC, used for clipping, or null.
	///< @param pixbuf A Pixbuf.
	///< @param src_x The source X coordinate within pixbuf.
	///< @param src_y The source Y coordinates within pixbuf.
	///< @param dest_x The destination X coordinate within drawable.
	///< @param dest_y The destination Y coordinate within drawable.
	///< @param width The width of region to render, in pixels, or -1 to use pixbuf width.
	///< @param height The height of region to render, in pixels, or -1 to use pixbuf height.
	///< @param dither The dithering mode for GdkRGB.
	///< @param x_dither The X offset for dither.
	///< @param y_dither The Y offset for dither.
	///<
	///< The destination drawable must have a colormap. All windows have a colormap, 
	///< however, pixmaps only have colormap by default if they were created with a non-null
	///< window argument. Otherwise a colormap must be set on them with set_colormap().
	///< On older X servers, rendering pixbufs with an alpha channel involves round trips
	///< to the X server, and may be somewhat slow.

/// @}
/// @name RGB Methods
/// @{

	void draw_rgb_image
	(
		const GC& gc,
		int x, 
		int y, 
		int width,
		int height,
		RgbDither dith,
		unsigned char *rgb_buf, 
		int rowstride
	);
	///< Draws an RGB image in the drawable. 
	///< @param gc The graphics context.
	///< @param x The X coordinate of the top-left corner in the drawable.
	///< @param y The Y coordinate of the top-left corner in the drawable.
	///< @param width The width of the rectangle to be drawn.
	///< @param height The height of the rectangle to be drawn.
	///< @param dith An RgbDither value, selecting the desired dither mode.
	///< @param rgb_buf The pixel data, represented as packed 24-bit data.
	///< @param rowstride The number of bytes from the start of one row in rgb_buf to the start of the next.
	///<
	///< This is the core GdkRGB method, and likely the only one you will need to use. 
	///< The <EM>rowstride</EM> parameter allows for lines to be aligned more flexibly.
	///< For example, lines may be allocated to begin on 32-bit boundaries, even if the
	///< width of the rectangle is odd. Rowstride is also useful when drawing a subrectangle
	///< of a larger image in memory. Finally, to replicate the same line a number of times,
	///< the trick of setting rowstride to 0 is allowed.
	///<
	///< In general, for 0 <= i < width and 0 <= j < height, the pixel (x + i, y + j) is colored with 
	///< red value rgb_buf[j * rowstride + i * 3], green value rgb_buf[j * rowstride + i * 3 + 1],
	///< and blue value rgb_buf[j * rowstride + i * 3 + 2].

	void draw_rgb_image_dithalign
	(
		const GC& gc,
		int x,
		int y,
		int width,
		int height,
		RgbDither dith,
		unsigned char *rgb_buf,
		int rowstride,
		int xdith,
		int ydith
	);
	///< Draws an RGB image in the drawable, with an adjustment for dither alignment.
	///< @param gc The graphics context.
	///< @param x The X coordinate of the top-left corner in the drawable.
	///< @param y The Y coordinate of the top-left corner in the drawable.
	///< @param width The width of the rectangle to be drawn.
	///< @param height The height of the rectangle to be drawn.
	///< @param dith An RgbDither value, selecting the desired dither mode.
	///< @param rgb_buf The pixel data, represented as packed 24-bit data.
	///< @param rowstride The number of bytes from the start of one row in rgb_buf to the start of the next.
	///< @param xdith An x offset for dither alignment.
	///< @param ydith A y offset for dither alignment.
	///<
	///< This method is useful when drawing dithered images into a window that may
	///< be scrolled. Pixel (x, y) will be drawn dithered as if its actual location is
	///< (x + xdith, y + ydith). Thus, if you draw an image into a window using zero
	///< dither alignment, then scroll up one pixel, subsequent draws to the window
	///< should have ydith = 1. Setting the dither alignment correctly allows updating
	///< of small parts of the screen while avoiding visible "seams" between the
	///< different dither textures.

	void draw_rgb_32_image
	(
		const GC& gc,
		int x,
		int y,
		int width,
		int height,
		RgbDither dith,
		unsigned char *buf,
		int rowstride
	);
	///< Draws a padded RGB image in the drawable. 
	///< @param gc The graphics context.
	///< @param x The X coordinate of the top-left corner in the drawable.
	///< @param y The Y coordinate of the top-left corner in the drawable.
	///< @param width The width of the rectangle to be drawn.
	///< @param height The height of the rectangle to be drawn.
	///< @param dith A RgbDither value, selecting the desired dither mode.
	///< @param buf The pixel data, represented as padded 32-bit data.
	///< @param rowstride The number of bytes from the start of one row in buf to the start of the next.
	///<
	///< The image is stored as one pixel per 32-bit word. It is laid out as a red byte,
	///< a green byte, a blue byte, and a padding byte. It's unlikely that this method will
	///< give significant performance gains in practice. In my experience, the performance
	///< gain from having pixels aligned to 32-bit boundaries is cancelled out by the 
	///< increased memory bandwidth.

	void draw_rgb_32_image_dithalign
	(
		const GC& gc,
		int x,
		int y,
		int width,
		int height,
		RgbDither dith,
		unsigned char *buf,
		int rowstride,
		int xdith,
		int ydith
	);
	///< Like draw_rgb_32_image(), but allows you to specify the dither offsets (see dar_rgb_image_dithalign()).
	///< @param gc A gaphics context.
	///< @param x The X coordinate on drawable where image should go.
	///< @param y The Y coordinate on drawable where image should go.
	///< @param width The width of area of image to draw.
	///< @param height The height of area of image to draw.
	///< @param dith The dithering mode.
	///< @param buf The RGB image data.
	///< @param rowstride The rowstride of the RGB image data.
	///< @param xdith The X dither offset.
	///< @param ydith The Y dither offset.

	void draw_gray_image
	(
		const GC& gc,
		int x,
		int y,
		int width,
		int height,
		RgbDither dith,
		unsigned char *buf,
		int rowstride
	);
	///< Draws a grayscale image in the drawable.
	///< @param gc The graphics context.
	///< @param x The X coordinate of the top-left corner in the drawable.
	///< @param y The Y coordinate of the top-left corner in the drawable.
	///< @param width The width of the rectangle to be drawn.
	///< @param height The height of the rectangle to be drawn.
	///< @param dith A RgbDither value, selecting the desired dither mode.
	///< @param buf The pixel data, represented as 8-bit gray values.
	///< @param rowstride The number of bytes from the start of one row in buf to the start of the next.

	void draw_indexed_image
	(
		const GC& gc,
		int x,
		int y,
		int width,
		int height,
		RgbDither dith,
		unsigned char *buf,
		int rowstride,
		GdkRgbCmap *cmap
	);
	///< Draws an indexed image in the drawable, using a GdkRgbCmap to assign actual colors to the color indices.
	///< @param gc The graphics context.
	///< @param x The X coordinate of the top-left corner in the drawable.
	///< @param y The Y coordinate of the top-left corner in the drawable.
	///< @param width The width of the rectangle to be drawn.
	///< @param height The height of the rectangle to be drawn.
	///< @param dith A RgbDither value, selecting the desired dither mode.
	///< @param buf The pixel data, represented as 8-bit color indices.
	///< @param rowstride The number of bytes from the start of one row in buf to the start of the next.
	///< @param cmap The GdkRgbCmap used to assign colors to the color indices.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/drawable.inl>

#endif // XFC_GDK_DRAWABLE_HH

