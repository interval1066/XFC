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
 
/// @file xfc/gdk/gc.hh
/// @brief A GdkGC C++ wrapper interface.
///
/// Provides GC, a graphics context that encapsulates drawing properties.

#ifndef XFC_GDK_GC_HH
#define XFC_GDK_GC_HH

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __GDK_GC_H__
#include <gdk/gdkgc.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {
	
class Bitmap;
class Color;
class Colormap;
class Drawable;
class Pixmap;
class Point;
class Rectangle;
class Region;
class Screen;

/// @enum CapStyle
/// Determines how the end of lines are drawn.

enum CapStyle
{
	CAP_NOT_LAST = GDK_CAP_NOT_LAST,
	///< The same as CAP_BUTT for lines of non-zero width; for zero width lines,
	///< the final point on the line will not be drawn.

	CAP_BUTT = GDK_CAP_BUTT,
	///< The ends of the lines are drawn squared off and extending to the coordinates of the end point.

	CAP_ROUND = GDK_CAP_ROUND,
	///< The ends of the lines are drawn as semicircles with the diameter equal 
	///<to the line width and centered at the end point.
	
	CAP_PROJECTING = GDK_CAP_PROJECTING
	///< The ends of the lines are drawn squared off and extending half the width
	///< of the line beyond the end point.
};

/// @enum Fill
/// Determines how primitives are drawn.

enum Fill
{
	SOLID = GDK_SOLID,
	///< Draw with the foreground color.
	
	TILED = GDK_TILED,
	///< Draw with a tiled pixmap.
	
	STIPPLED = GDK_STIPPLED,
	///< Draw using the stipple bitmap; pixels corresponding to bits in the stipple bitmap
	///< that are set will be drawn in the foreground color; pixels corresponding to bits
	///< that are not set will be left untouched.
	
	OPAQUE_STIPPLED = GDK_OPAQUE_STIPPLED
	///< Draw using the stipple bitmap; pixels corresponding to bits in the stipple bitmap
	///< that are set will be drawn in the foreground color; pixels corresponding to bits
	///< that are not set will be left untouched.
};

/// @enum Function
/// Determines how the bit values for the source pixels are combined with the bit values
/// for destination pixels to produce the final result. The sixteen values here correspond
/// to the 16 different possible 2x2 truth tables. Only a couple of these values are usually
/// useful; for colored images, only COPY, XOR and INVERT are generally useful. For bitmaps,
/// AND and OR are also useful.

enum Function
{
	COPY = GDK_COPY, ///< Overwrites destination pixels with the source pixels (GXcopy)
	INVERT = GDK_INVERT, ///< Inverts the destination pixels (GXinvert).
	XOR = GDK_XOR, ///< Xor's the destination pixels with the source pixels (GXxor).
	CLEAR = GDK_CLEAR, ///< Set pixels to 0 (GXclear).
	AND = GDK_AND, ///< Source AND destination (GXand).
	AND_REVERSE = GDK_AND_REVERSE, ///< Source AND NOT destination (GXandReverse).
	AND_INVERT = GDK_AND_INVERT, ///< NOT source AND destination (GXandInverted).
	NOOP = GDK_NOOP, ///< Destination (GXnoop).
	OR = GDK_OR, ///< Source OR destination (GXor).
	EQUIV = GDK_EQUIV, ///< NOT source XOR destination (GXequiv).
	OR_REVERSE = GDK_OR_REVERSE, ///< Source OR NOT destination (GXorReverse).
	COPY_INVERT = GDK_COPY_INVERT, ///< NOT source (GXcopyInverted).
	OR_INVERT = GDK_OR_INVERT, ///< NOT source OR destination (GXorInverted).
	NAND = GDK_NAND, ///< NOT source OR NOT destination (GXnand).
	NOR = GDK_NOR, ///< NOT source AND NOT destination (GXset).
	SET = GDK_SET ///< Set pixels to 1.
};

/// @enum JoinStyle
/// Determines how the joins between segments of a polygon are drawn.

enum JoinStyle
{
	JOIN_MITER = GDK_JOIN_MITER,
	///< The sides of each line are extended to meet at an angle.

	JOIN_ROUND = GDK_JOIN_ROUND,
	///< The sides of the two lines are joined by a circular arc.

	JOIN_BEVEL = GDK_JOIN_BEVEL
	///< The sides of the two lines are joined by a straight line
	///< which makes an equal angle with each line.
};

/// @enum LineStyle
/// Determines how lines are drawn.

enum LineStyle
{
	LINE_SOLID = GDK_LINE_SOLID,
	///< Lines are drawn solid.
	
	LINE_ON_OFF_DASH = GDK_LINE_ON_OFF_DASH,
	///< Even segments are drawn; odd segments are not drawn.
	
	LINE_DOUBLE_DASH = GDK_LINE_DOUBLE_DASH
	///< Even segments are drawn normally. Odd segments are drawn in the background
	///< color if the fill style is SOLID, or in the background color masked
	///< by the stipple if the fill style is STIPPLED.
};

/// @enum SubwindowMode
/// Determines how drawing onto a window will affect child windows of that window.

enum SubwindowMode
{
	CLIP_BY_CHILDREN = GDK_CLIP_BY_CHILDREN, ///< Only draw onto the window itself.
	INCLUDE_INFERIORS = GDK_INCLUDE_INFERIORS ///< Draw onto the window and child windows.
};

/// @class GCValues gc.hh xfc/gdk/gc.hh
/// @brief A GdkGCValues C++ wrapper class.
///
/// A graphics context is created with a set of default values. Any of these values can be
/// set individually by calling one of the Gdk::GC methods, such as Gdk::GC::set_foreground
/// or Gdk::GC::set_fill().
///
/// The GCValues object allows you to set multiple values at once when constructing or
/// modifying a graphics context. GCValues manages the GdkGCValuesMask bit flags internally,
/// so you don't have to worry. Just set the values you want and then pass your GCValues
/// object to the Gdk::GC constructor, or the Gdk::GC::set_values method if your modifying
/// the graphics context later. You can retreive the currently set values for a Gdk::GC by
/// passing a GCValues object to Gdk::GC::get_values(). If you want to reuse the same
/// GCValues object you can unset individual values by calling the corresponding unset_()
/// method, or you reset the entire object to its gfcal state by calling reset(). This will
/// free any set pixmaps and reset the bit flags to zero.

class GCValues : public StackObject
{
	friend class GC;

	GdkGCValues values_;
	unsigned int mask_;

public:
/// @name Constructors
/// @{

	GCValues();
	///< Construct a new GCValues object.

        GCValues(const GCValues& src);
	///< Copy constructor.
	///< @param src The source GCValues.

	~GCValues ();
	///< Destructor.

	GCValues& operator=(const GCValues& src);
	///< Assignemnt operator.
	///< @param src The source GCValues.

/// @}
/// @name Accessors
/// @{

	GdkGCValues* gdk_gc_values() const;
	///< Get a pointer to the GdkGCValues structure.

	GdkGCValuesMask gdk_gc_values_mask() const;
	///< Returns the bit flags that indicate which values are currently set.

	Color foreground() const;
	///< Returns the foreground color.
	
	bool foreground_set() const;
	///< Returns true if the foreground value is set.

	Color background() const;
	///< Returns the background color.

	bool background_set() const;
	///< Returns true if the background value is set.

	Function function() const;
	///< Returns the bitwise operation used when drawing.

	bool function_set() const;
	///< Returns true if the function value is set.

	Fill fill() const;
	///< Returns the fill style.

	bool fill_set() const;
	///< Returns true if the fill value is set.

	Pixmap* tile() const;
	///< Returns the tile pixmap.

	bool tile_set() const;
	///< Returns true if the tile pixmap is set.

	Bitmap* stipple() const;
	///< Returns the stipple bitmap.

	bool stipple_set () const;
	///< Returns true if the stipple bitmap is set.

	Bitmap* clip_mask() const;
	///< Returns the clip mask bitmap.

	bool clip_mask_set() const;
	///< Returns true if the clip_mask bitmap is set.

	SubwindowMode subwindow_mode() const;
	///< Returns the subwindow mode.

	bool subwindow_mode_set() const;
	///< Returns true if the subwindow_mode value is set.

	int ts_x_origin() const;
	///< Returns the x origin of the tile or stipple.

	bool ts_x_origin_set() const;
	///< Returns true if the ts_x_origin value is set.

	int ts_y_origin() const;
	///< Returns the y origin of the tile or stipple.

	bool ts_y_origin_set() const;
	///< Returns true if the ts_y_origin value is set.

	int clip_x_origin() const;
	///< Returns the x origin of the clip mask.

	bool clip_x_origin_set() const;
	///< Returns true if the clip_x_origin value is set.

	int clip_y_origin() const;
	///< Returns the y origin of the clip mask.

	bool clip_y_origin_set () const;
	///< Returns true if the clip_y_origin value is set.

	bool graphics_exposures() const;
	///< Returns true graphics exposures are enabled.

	bool graphics_exposures_set() const;
	///< Returns true if the graphics_exposures value is set.

	int line_width() const;
	///< Returns the line width.

	bool line_width_set() const;
	///< Returns true if the line_width value is set.

	LineStyle line_style() const;
	///< Returns the way dashed lines are drawn.

	bool line_style_set() const;
	///< Returns true if the line_style value is set.

	CapStyle cap_style () const;
	///< Returns the way the ends of lines are drawn.

	bool cap_style_set() const;
	///< Returns true if the cap_style value is set.

	JoinStyle join_style() const;
	///< Returns the way joins between lines are drawn.

	bool join_style_set() const;
	///< Returns true if the join_style value is set.

/// @}
/// @name Methods
/// @{

	void reset();
	///< Resets the object, freeing any pixmaps and setting the bit flag mask to zero.

	void set_foreground(const Color& color);
	///< Sets the foreground color for a graphics context.
	///< @param color The new foreground color.

	void unset_foreground();
	///< Unsets the foreground bit flag.

	void set_background(const Color& color);
	///< Sets the background color for a graphics context.
	///< @param color The new background color.

	void unset_background();
	///< Unsets the background bit flag.

	void set_function(Function function);
	///< Determines how the current pixel values and the pixel values being drawn
	///< are combined to produce the final pixel values.
	///< @param function The bitwise operation to use when drawing.

	void unset_function();
	///< Unsets the function bit flag.

	void set_fill(Fill fill);
	///< Set the fill mode for a graphics context.
	///< @param fill The new fill mode.

	void unset_fill();
	///< Unsets the fill bit flag.

	void set_tile(Pixmap& tile);
	///< Set a tile pixmap for a graphics context.
	///< @param tile The new tile pixmap.
	///<
	///< This will only be used if the fill mode is Gdk::TILED.

	void unset_tile();
	///< Unsets the tile bit flag.

	void set_stipple(Bitmap& stipple);
	///< Set the stipple bitmap for a graphics context.
	///< @param stipple The new stipple bitmap.
	///<
	///< The stipple will only be used if the fill mode is Gdk::STIPPLED or Gdk::OPAQUE_STIPPLED.

	void unset_stipple();
	///< Unsets the stipple bit flag.

	void set_clip_mask(Bitmap& mask);
	///< Sets the clip mask for a graphics context from a bitmap.
	///< @param mask A bitmap.
	///<
	///< The clip mask is interpreted relative to the clip origin (see Gdk::GC::set_clip_origin()).

	void unset_clip_mask();
	///< Unsets the clip_mask bit flag.

	void set_subwindow_mode(SubwindowMode mode);
	///< Sets how drawing with this graphics context on a window will affect child windows of that window.
	///< @param mode The subwindow mode.

	void unset_subwindow_mode();
	///< Unsets the subwindow_mode bit flag.

	void set_ts_origin(int x, int y);
	///< Set the origin when using tiles or stipples with the graphics context.
	///< @param x The X coordinate of the origin.
	///< @param y The Y coordinate of the origin.
	///<
	///< The tile or stipple will be aligned such that the upper left corner
	///< of the tile or stipple will coincide with this point.

	void set_ts_x_origin(int x);
	///< Set the x coordinate of the origin when using tiles or stipples with the graphics context.
	///< @param x The X coordinate of the origin.
	///<
	///< The tile or stipple will be aligned such that the upper left corner
	///< of the tile or stipple will coincide with this x coordinate.

	void unset_ts_x_origin();
	///< Unsets the ts_x_origin bit flag.

	void set_ts_y_origin(int y);
	///< Set the y coordinate of the origin when using tiles or stipples with the graphics context.
	///< @param y The Y coordinate of the origin.
	///<
	///< The tile or stipple will be aligned such that the upper left corner
	///< of the tile or stipple will coincide with this y coordinate.

	void unset_ts_y_origin();
	///< Unsets the ts_y_origin bit flag.

	void set_clip_origin(int x, int y);
	///< Sets the origin of the clip mask.
	///< @param x The X coordinate of the origin.
	///< @param y The Y coordinate of the origin.
	///<
	///< The coordinates are interpreted relative to the upper-left corner
	///< of the destination drawable of the current operation.

	void set_clip_x_origin(int x);
	///< Sets the x coordinate of the origin of the clip mask.
	///< @param x The X coordinate of the origin.
	///<
	///< The x coordinate is interpreted relative to the upper-left corner
	///< of the destination drawable of the current operation.

	void unset_clip_x_origin();
	///< Unsets the clip_x_origin bit flag.

	void set_clip_y_origin(int y);
	///< Sets the y coordinate of the origin of the clip mask.
	///< @param y The Y coordinate of the origin.
	///<
	///< The y coordinate is interpreted relative to the upper-left corner
	///< of the destination drawable of the current operation.

	void unset_clip_y_origin();
	///< Unsets the clip_y_origin bit flag.

	void set_graphics_exposures(bool exposures);
	///< Sets whether copying non-visible portions of a drawable using a graphics context
	///< generates exposure events for the corresponding regions of the destination
	///< drawable (see Gdk::Drawable::draw_drawable()).
	///< @param exposures If <EM>true</EM>, exposure events will be generated.

	void unset_graphics_exposures();
	///< Unsets the graphics_exposures bit flag.

	void set_line_width(int width);
	///< Sets the line width.
	///< @param width The width of lines.

	void unset_line_width();
	///< Unsets the line_width bit flag.

	void set_line_style(LineStyle style);
	///< Sets the way dashed lines are drawn.
	///< @param style The dash-style for lines.

	void unset_line_style();
	///< Unsets the line_style bit flag.

	void set_cap_style(CapStyle style);
	///< Sets the way the ends of lines are drawn.
	///< @param style The manner in which the ends of lines are drawn.

	void unset_cap_style();
	///< Unsets the cap_style bit flag.

	void set_join_style(JoinStyle style);
	///< Sets the way joins between lines are drawn.
	///< @param style The manner in which lines are joined together.

	void unset_join_style();
	///< Unsets the join_style bit flag.

/// @}
};

/// @class GC gc.hh xfc/gdk/gc.hh
/// @brief A GdkGC C++ wrapper class.
///
/// All drawing operations in GDK take a graphics context (GC) argument. A graphics context
/// encapsulates information about the way things are drawn, such as the foreground color
/// or line width. By using graphics contexts, the number of arguments to each drawing call
/// is greatly reduced, and communication overhead is minimized, since identical arguments
/// do not need to be passed repeatedly.
///
/// Most values of a graphics context can be set at creation time by using a GCValues object,
/// or can be set one-by-one using functions such as set_foreground(). A few of the values
/// in the GC, such as the dash pattern, can only be set by the latter method.
///
/// Graphics contexts are created with the following default values:
/// - foreground = 0 (first entry in colormap - usually black)
/// - background = 1 (last entry in colormap - usually white)
/// - font = unused
/// - function = GC_COPY
/// - fill = SOLID
/// - tile = foreground fill pixmap
/// - stipple = Pixmap filled with 1s
/// - clip_mask = none
/// - subwindow_mode = CLIP_BY_CHILDREN
/// - ts_x_origin = 0
/// - ts_y_origin = 0
/// - clip_x_origin = 0
/// - clip_y_origin = 0
/// - graphics_exposure = true
/// - line_width = 0
/// - line_style = LINE_SOLID
/// - cap_style = CAP_BUTT
/// - join_style = JOIN_MITIR
///
/// As a rule it is not a good idea to modify the GC's retrieved from a widget style (see Gtk::Style).
/// Widget's rely on these GC's and modifying them could modify the appearence of the widget. The best
/// thing to do is the create your own and change one or more of the default values, either at
/// construction time or later with one of the set_() methods.
///
/// GC's are not added to any other widget so you need to manage its memory allocation yourself. This
/// means that you need to call unref() on the GC when you're finished with it. If you created the GC
/// using a smart pointer, the smart pointer will call unref() for you when it goes out of scope.
///
/// The GCValues object allows you to set multiple values at once when constructing or modifying a
/// graphics context. Just set the values you want and then pass your GCValues object to the Gdk::GC
/// constructor or the Gdk::GC::set_values method if your modifying the graphics context later. You
/// can retreive all the currently set values for a Gdk::GC by calling get_values.

class GC : public G::Object
{
	friend class G::Object;

	GC(const GC&);
	GC& operator=(const GC&);

protected:
/// @name Constructors
/// @{

	explicit GC(GdkGC *gc, bool owns_reference = true);
	///< Construct a new GC from an existing GdkGC.
	///< @param gc A pointer to a GdkGC.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>gc</EM> can be a newly created GdkGC or an existing
	///< GdkGC. (see G::Object::Object).

/// @}

public:
	typedef GdkGC CObjectType;

/// @name Constructors
/// @{

	explicit GC(Drawable& drawable);
	///< Construct a new graphics context with default values.
	///< @param drawable A Drawable.
	///<
	///< <B>Note:</B> The created GC must always be used with drawables
	///< of the same depth as <EM>drawable</EM>. GC is created with a reference
	///< count of 1 that the caller owns.

	GC(Drawable& drawable, const GCValues& values);
	///< Construct a new graphics context with the given initial values.
	///< @param drawable A Drawable.
	///< @param values A GCValues object containing the initial values for the graphics context.
	///<
	///< GC is created with a reference count of 1 that the caller owns.
	
	virtual ~GC();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GdkGC* gdk_gc() const;
	///< Get a pointer to the GdkGC structure.

	operator GdkGC* () const;
	///< Conversion operator; safely converts a GC to a GdkGC pointer.

	int ts_x_origin() const;
	///< Returns the x origin of the tile or stipple.

	int ts_y_origin() const;
	///< Returns the y origin of the tile or stipple.

	int clip_x_origin() const;
	///< Returns the x origin of the clip mask.

	int clip_y_origin() const;
	///< Returns the y origin of the clip mask.

	void get_values(GCValues& values) const;
	///< Retrieves the current values from a graphics context.
	///< @param values The GCValues object in which to store the results.

	Colormap* get_colormap() const;
	///< Retrieves the colormap for a given GC, if it exists.
	///< @return A Colormap.
	///<
	///< A GC will have a colormap if the drawable for which it was created has a colormap,
	///< or if a colormap was set explicitely with set_colormap.

	Screen* get_screen() const;
	///< Gets the Screen for which the graphics context was created.
	///< @return The GdkScreen for the graphics context.

/// @}
/// @name Methods
/// @{

	void set_values(const GCValues& values);
	///< Sets attributes of a graphics context in bulk. 
	///< @param values A GCValues object containing the new values.
	///<
	///< Only the values explicity set in <EM>values</EM> will be read and set
	///< as the new value for the graphics context. If you're only setting a few 
	///< values on gc, calling individual "setter" methods is likely more convenient.

	void set_foreground(const Color& color);
	///< Sets the foreground color for the graphics context.
	///< @param color The new foreground color.

	void set_background(const Color& color);
 	///< Sets the background color for the graphics context.
	///< @param color The new background color.

	void set_function(Function function);
	///< Determines how the current pixel values and the pixel values being drawn
	///< are combined to produce the final pixel values.
	///< @param function The bitwise operation to use when drawing.

	void set_fill(Fill fill);
	///< Set the fill mode for the graphics context.
	///< @param fill The new fill mode.

	void set_tile(Pixmap& tile);
	///< Set a tile pixmap for the graphics context.
	///< @param tile The new tile pixmap.
	///<
	///< This will only be used if the fill mode is GDK_TILED.

	void set_stipple(Pixmap& stipple);
	///< Set the stipple bitmap for the graphics context.
	///< @param stipple The new stipple bitmap.
	///<
	///< The stipple will only be used if the fill mode is Gdk::STIPPLED or Gdk::OPAQUE_STIPPLED.

	void set_ts_origin(int x, int y);
	///< Set the origin when using tiles or stipples with the graphics context.
	///< @param x The X coordinate of the origin.
	///< @param y The Y coordinate of the origin.
	///<
	///< The tile or stipple will be aligned such that the upper left corner
	///< of the tile or stipple will coincide with this point.

	void set_ts_origin(const Point& point);
	///< Set the origin when using tiles or stipples with the graphics context.
	///< @param point A Point holding the x, y coordinates of the origin.
	///<
	///< The tile or stipple will be aligned such that the upper left corner
	///< of the tile or stipple will coincide with this point.

	void set_clip_origin(int x, int y);
	///< Sets the origin of the clip mask.
	///< @param x The X coordinate of the origin.
	///< @param y The Y coordinate of the origin.
	///<
	///< The coordinates are interpreted relative to the upper-left corner
	///< of the destination drawable of the current operation.

	void set_clip_origin(const Point& point);
	///< Sets the origin of the clip mask.
	///< @param point A Point holding the x, y coordinates of the origin.
	///<
	///< The coordinates are interpreted relative to the upper-left corner
	///< of the destination drawable of the current operation.

	void set_clip_mask(Bitmap& mask);
	///< Sets the clip mask for a graphics context from a bitmap.
	///< @param mask A bitmap.
	///<
	///< The clip mask is interpreted relative to the clip origin (see set_clip_origin()).

	void set_clip(int x, int y, int width, int height);
	///< Sets the clip mask for a graphics context from a rectangle.
	///< @param x The X coordinate of the upper-left corner of the rectangle to clip to.
	///< @param y The Y coordinate of the upper-left corner of the rectangle to clip to.
	///< @param width The width of the rectangle to clip to.
	///< @param height The height of the rectangle to clip to.
	///<
	///< The clip mask is interpreted relative to the clip origin (see set_clip_origin()).

	void set_clip(const Rectangle& rectangle);
	///< Sets the clip mask for a graphics context from a rectangle.
	///< @param rectangle The rectangle to clip to.
	///<
	///< The clip mask is interpreted relative to the clip origin (see set_clip_origin()).

	void set_clip(const Region& region);
	///< Sets the clip mask for a graphics context from a region.
	///< @param region The Region.
	///<
	///< The clip mask is interpreted relative to the clip origin (see set_clip_origin()).

	void set_subwindow(SubwindowMode mode);
	///< Sets how drawing with this graphics context on a window will affect child windows of that window.
	///< @param mode The subwindow mode.

	void set_exposures(bool exposures);
	///< Sets whether copying non-visible portions of a drawable using a graphics context
	///< generates exposure events for the corresponding regions of the destination
	///< drawable (see Gdk::Drawable::draw_drawable()).
	///< @param exposures If <EM>true</EM>, exposure events will be generated.

	void set_line_attributes(int line_width, LineStyle line_style, CapStyle cap_style, JoinStyle join_style);
	///< Sets various attributes of how lines are drawn.
	///< @param line_width The width of lines.
	///< @param line_style The dash-style for lines.
	///< @param cap_style The manner in which the ends of lines are drawn.
	///< @param join_style The manner in which lines are joined together.
	///<
	///< See the corresponding members of GCValues for full explanations of the arguments.

	void set_line_width(int line_width);
	///< Sets the line width.
	///< @param line_width The width of lines.

	void set_line_style(LineStyle line_style);
	///< Sets the way dashed lines are drawn.
	///< @param line_style The dash-style for lines.

	void set_cap_style(CapStyle cap_style);
	///< Sets the way the ends of lines are drawn.
	///< @param cap_style The manner in which the ends of lines are drawn.

	void set_join_style(JoinStyle join_style);
	///< Sets the way joins between lines are drawn.
	///< @param join_style The manner in which lines are joined together.

	void set_dashes(int dash_offset, gint8 *dash_list, int n);
	///< Sets the way dashed-lines are drawn.
	///< @param dash_offset The dash offset.
	///< @param dash_list An array of dash lengths.
	///< @param n The number of elements in <EM>dash_list</EM>.
	///<
	///< Lines will be drawn with alternating on and off segments of the lengths specified in
	///< <EM>dash_list</EM>. The manner in which the on and off segments are drawn is determined by
	///< the line_style value of the graphics context (This can be changed with set_line_attributes()).

	void offset(int x_offset, int y_offset);
	///< Offset attributes such as the clip and tile-stipple origins of the GC so that
	///< drawing at x - x_offset, y - y_offset with the offset GC has the same effect
	///< as drawing at x, y with the original GC.
	///< @param x_offset The amount by which to offset the GC in the X direction.
	///< @param y_offset The amount by which to offset the GC in the Y direction.

	void set_colormap(Colormap *colormap);
	///< Sets the colormap for the GC to the given colormap. 
	///< @param colormap A Colormap.
	///<
	///< The depth of the colormap's visual must match the depth
	///< of the drawable for which the GC was created.

	void set_rgb_fg_color(const Color& color);
	///< Set the foreground color of a GC using an unallocated color.
	///< @param color An unallocated GdkColor.
	///<
	///< The pixel value for the color will be determined using GdkRGB. If the colormap
	///< for the GC has not previously been initialized for GdkRGB, then for pseudo-color
	///< colormaps (colormaps with a small modifiable number of colors), a colorcube will
	///< be allocated in the colormap.
	///<
	///< <B>Note:</B> Calling this function for a GC without a colormap is an error.

	void set_rgb_bg_color(const Color& color);
	///< Set the background color of a GC using an unallocated color.
	///< @param color An unallocated GdkColor.
	///<
	///< The pixel value for the color will be determined using GdkRGB. If the colormap
	///< for the GC has not previously been initialized for GdkRGB, then for pseudo-color
	///< colormaps (colormaps with a small modifiable number of colors), a colorcube will
	///< be allocated in the colormap.
	///<
	///< <B>Note:</B> Calling this method for a GC without a colormap is an error.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/gc.inl>

#endif // XFC_GDK_GC_HH


