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
 
/// @file xfc/pango/layout.hh
/// @brief A PangoLayout C++ wrapper interface.
///
/// While complete access to the layout capabilities of Pango is provided using
/// the detailed interfaces for itemization and shaping, using that functionality
/// directly involves writing a fairly large amount of code. The objects and
/// functions in this file provide a high-level driver for formatting entire
/// paragraphs of text at once.

#ifndef XFC_PANGO_LAYOUT_HH
#define XFC_PANGO_LAYOUT_HH

#ifndef XFC_PANGO_ATTRIBUTES_HH
#include <xfc/pango/attributes.hh>
#endif

#ifndef XFC_PANGO_CONTEXT_HH
#include <xfc/pango/context.hh>
#endif

#ifndef XFC_PANGO_ITEM_HH
#include <xfc/pango/item.hh>
#endif

#ifndef XFC_PANGO_TABS_HH
#include <xfc/pango/tabs.hh>
#endif

#ifndef __PANGO_LAYOUT_H__
#include <pango/pango-layout.h>
#endif

#ifndef _CPP_UTILITY
#include <utility>
#endif

namespace Xfc {

namespace Gdk {
class Region;
}

namespace Pango {
	
class LogAttr;
class GlyphString;

/// @enum Alignment
/// Describes how to align the lines of a Layout within the available space. 
/// If the PangoLayout is set to justify using Pango::Layout::set_justify(),
/// then this only has an effect for partial lines.

enum Alignment
{
	ALIGN_LEFT = PANGO_ALIGN_LEFT, ///< Put all available space on the right.
	ALIGN_CENTER = PANGO_ALIGN_CENTER, ///< Center the line within the available space.
	ALIGN_RIGHT = PANGO_ALIGN_RIGHT ///< Put all available space on the left.
};

/// @enum WrapMode
/// Describes how to wrap the lines of a Layout to the desired width. In the
/// ellipsization process characters are removed from the text in order to 
/// make it fit to a given width and replaced with an ellipsis.

enum WrapMode
{
	WRAP_WORD = PANGO_WRAP_WORD, 
	///< Wrap lines at word boundaries.

	WRAP_CHAR = PANGO_WRAP_CHAR, 
	///< Wrap lines at character boundaries.

	WRAP_WORD_CHAR = PANGO_WRAP_WORD_CHAR
	///< Wrap lines at word boundaries, but fall back to character boundaries
	///< if there is not enought space for a full word.
};

/// @enum EllipsizeMode
/// Describes what sort of (if any) ellipsization should be applied to a line of text.

enum EllipsizeMode
{
	ELLIPSIZE_NONE = PANGO_ELLIPSIZE_NONE, ///< No ellipsization.
	ELLIPSIZE_START = PANGO_ELLIPSIZE_START, ///< Omit characters at the start of the text.
	ELLIPSIZE_MIDDLE = PANGO_ELLIPSIZE_MIDDLE, ///< Omit characters in the middle of the text.
	ELLIPSIZE_END = PANGO_ELLIPSIZE_END ///< Omit characters at the end of the text.
};

/// @class LayoutRun layout.hh xfc/pango/layout.hh
/// @brief A PangoLayoutRun C++ wrapper class.
///
/// LayoutRun is a pair of a Pango::Item and the glyphs resulting from shaping the text
/// corresponding to an item. As an example of the usage of LayoutRun, the results of
/// shaping text with Pango::Layout is a list of LayoutLine, each of which contains a
/// list of LayoutRun.

class LayoutRun
{
	PangoLayoutRun run_;

public:
/// @name Accessors
/// @{

	PangoLayoutRun* pango_layout_run() const;
	///< Get a pointer to the PangoLayoutRun structure.

	Pointer<Item> item() const;
	///< Returns a smart pointer to an Item object that provides information about a segment of text.

	Pointer<GlyphString> glyphs() const;
	///< Returns a smart pointer to a string of glyphs obtained by shaping the text corresponding to item.

/// @}
};

/// @class LayoutLine layout.hh xfc/pango/layout.hh
/// @brief A PangoLayoutLine C++ wrapper class.
///
/// LayoutLine represents one of the lines resulting from laying out a paragraph via Layout.
/// LayoutLine objects are obtained by calling Pango::Layout::get_line() and are only valid
/// until the text, attributes, or settings of the parent Layout are modified.
///
/// Routines for rendering Layout objects are provided in code specific to each rendering system.

class LayoutLine : public Xfc::Object
{
	PangoLayoutLine *layout_line_;

public:
/// @name Constructors
/// @{

	explicit LayoutLine(PangoLayoutLine *layout_line);
	///< Construct a new LayoutLine from an existing PangoLayoutLine.
	///< @param layout_line A pointer to a PangoLayoutLine.

	LayoutLine(const LayoutLine& src);
	///< Copy constructor.
	///< @param src The source LayoutLine.

	~LayoutLine();
	///< Destructor.

	LayoutLine& operator=(const LayoutLine& src);
	///< Assignment operator.
	///< @param src The source LayoutLine.

/// @}
/// @name Accessors
/// @{

	PangoLayoutLine* pango_layout_line() const;
	///< Get a pointer to the PangoLayoutLine structure.

	operator PangoLayoutLine* () const;
	///< Conversion operator; safely converts a LayoutLine to a PangoLayoutLine pointer.

	int start_index() const;
	///< Returns the start of line as byte index into the text of the parent layout.

	int length() const;
	///< Returns the length of line in bytes.

	bool is_paragraph_start() const;
	///< Determines whether this is the first line of a paragraph.
	///< @return <EM>true</EM> if this is the first line of a paragraph.

	std::vector<std::pair<int, int> > get_x_ranges(int start_index, int end_index) const;
	///< Get a list of visual ranges corresponding to a given logical range.
	///< @param start_index The starting byte index of the logical range.
	///< @param end_index The end byte index of the logical range.
	///< @return A vector of int/int pairs (see example below).
	///<
	///< If <EM>start_index</EM> is less than the start index for the line, then
	///< the first range will extend all the way to the leading edge of the layout.
	///< Otherwise it will start at the leading edge of the first character. If
	///< <EM>end_index</EM> is greater than the end index for the line, then the last
	///< range will extend all the way to the trailing edge of the layout. Otherwise,
	///< it will end at the trailing edge of the last character.
	///<
	///< This list is not necessarily minimal - there may be consecutive ranges which
	///< are adjacent. The ranges will be sorted from left to right. The ranges are with
	///< respect to the left edge of the entire layout, not with respect to the line.
	///<
	///< The return value is not as strange as it looks. A std::pair is a container
	///< that stores 2 values, and vector you already know, so the return value is a
	///< vector of int/int pairs. In a std::pair the first value is called <EM>first</EM>
	///< and the second value is called <EM>second</EM>. In the returned vector each pair
	///< is a range. In each pair the first value is the start of the range and the
	///< second value is the width of the range. The coordinates are relative to the
	///< layout and are in GlyphUnits. To access the values returned in the pairs you 
	///< would do something like this:
	///< @code
	///< std::vector<std::pair<int, int> > ranges = get_x_ranges(start_index, end_index);
	///< 
	///< for (int i = 0; i < ranges.size(); i++)
	///< {
	///< 	int start_of_range = ranges[i].first;
	///< 	int width_of_range = ranges[i].second;
	///< 	...
	///< }
	///< @endcode
	///< Note the space between the two \htmlonly >s; >> \endhtmlonly is the right shift operator.

	void get_extents(Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Compute the logical and ink extents of a layout line.
	///< @param ink_rect The rectangle used to store the extents of the glyph string as drawn,
	///<                 or null to indicate that the result is not needed.
	///< @param logical_rect The rectangle used to store the logical extents of the glyph string,
	///<                     or null to indicate that the result is not needed.
	///<
	///< See the documentation for Pango::Font::get_glyph_extents() for details
	///< about the interpretation of the rectangles.

	void get_pixel_extents(Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Compute the logical and ink extents of a layout line.
	///< @param ink_rect The rectangle used to store the extents of the glyph string as drawn,
	///<                 or null to indicate that the result is not needed.
	///< @param logical_rect The rectangle used to store the logical extents of the glyph string,
	///<                     or null to indicate that the result is not needed.
	///<
	///< See the documentation for Pango::Font::get_glyph_extents() for details
	///< about the interpretation of the rectangles. The returned rectangles are in
	///< device units, as opposed to get_extents(), which returns the extents in 
	///< GlyphUnits.
  	
	Pointer<Gdk::Region> get_clip_region(int x_origin, int y_origin, const std::vector<std::pair<int, int> >& index_ranges) const;
	///< Obtains a clip region which contains the areas where the given ranges
	///< of text would be drawn. 
	///< @param x_origin The X pixel where you intend to draw the layout line with this clip.
	///< @param y_origin The baseline pixel where you intend to draw the layout line with this clip.
	///< @param index_ranges A reference to a vector of int/int pairs that holds the index
	///<                     ranges. The <EM>first</EM> value of each pair is the start index
	///<                     and the <EM>second</EM> value is the end index.
	///< @return A smart pointer to a new clip region containing the given ranges.
	///<
	///< <EM>x_origin</EM> and <EM>y_origin</EM> are the same position you would pass
	///< to Gdk::Drawable::draw_layout_line(). <EM>index_ranges</EM> is a vector that
	///< should contain ranges of bytes in the layout's text as an int/int pair. The 
	///< clip region will include space to the left or right of the line (to the layout
	///< bounding box) if you have indexes above or below the indexes contained inside 
	///< the line. This is to draw the selection all the way to the side of the layout.
	///< However, the clip region is in line coordinates, not layout coordinates.
	///<
	///< See Pango::Layout::get_clip_region() for an example of how to create a vector of pair.

/// @}
/// @name Methods
/// @{

	bool x_to_index(int x_pos, int *index, int *trailing);
	///< Convert from x offset to the byte index of the corresponding character
	///< within the text of the layout. 
	///< @param x_pos The x offset (in GlyphUnits) from the left edge of the line.
	///< @param index The location to store the calculated byte offset for the grapheme
	///<              in which the user clicked.
	///< @param trailing The location to store a integer indicating where in the grapheme the user clicked.
	///< @return <EM>false</EM> if x_pos was outside the line, <EM>true</EM> if inside.
	///<
	///< If x_pos is outside the line, the start or end of the line will be stored at index.
	///< <EM>trailing</EM> will either be zero, or the number of characters in the grapheme.
	///< 0 represents the trailing edge of the cluster.

	int index_to_x(int index, bool trailing);
	///< Converts an index within a line to a X position.
	///< @param index The byte offset of a grapheme within the layout.
	///< @param trailing Whether to compute the result for the leading or trailing edge of the grapheme.
	///< @return The x_offset (in GlyphUnits).

/// @}
};

/// @class LayoutIter layout.hh xfc/pango/layout.hh
/// @brief A PangoLayoutIter C++ wrapper class.
///
/// LayoutIter can be used to iterate over the visual extents of a Layout.

class LayoutIter : public G::Boxed
{
public:
/// @name Constructors
/// @{

	explicit LayoutIter(PangoLayoutIter *iter);
	///< Construct a new LayoutIter from an existing PangoLayoutIter.
	///< @param iter A pointer to a PangoLayoutIter.
	///<
	///< LayoutIter takes over the ownership of PangoLayoutIter and frees it
	///< when it's no longer required.

	LayoutIter(PangoLayoutIter *iter, bool copy);
	///< Construct a new layout iterator from an existing PangoLayoutIter.
	///< @param iter A pointer to a PangoLayoutIter.
	///< @param copy Whether the LayoutIter object should make a copy of PangoLayoutIter or not.
	///<
	///< The <EM>iter</EM> can be a newly created PangoLayoutIter or an existing
	///< PangoLayoutIter. If <EM>copy</EM> is true LayoutIter will make a copy
	///< of PangoLayoutIter. If <EM>copy</EM> is false LayoutIter wont make a
	///< copy but instead takes over the ownership of PangoLayoutIter. Either way,
	///< the destructor will free PangoLayoutIter when the LayoutIter object is
	///< destroyed. This constructor is used by G::Boxed::wrap() to wrap PangoLayoutIter
	///< objects in a C++ wrapper.
	///<
	///< The FontDescription is created with a reference count of 1 that the caller owns.

	LayoutIter(const LayoutIter& src);
	///< Copy constructor.
	///< @param src The source LayoutIter.
	
	virtual ~LayoutIter();
	///< Destructor.

	LayoutIter& operator=(const LayoutIter& src);
	///< Assignment operator.
	///< @param src The source LayoutIter.

/// @}
/// @name Accessors
/// @{

	PangoLayoutIter* pango_layout_iter() const;
	///< Get a pointer to the PangoLayoutIter structure.

	operator PangoLayoutIter* () const;
	///< Conversion operator; safely converts a LayoutIter to a PangoLayoutIter pointer.

	int get_index() const;
	///< Gets the current byte index.
	///< @return The current byte index.
	///<
	///< Note that iterating forward by char moves in visual order, not logical order,
	///< so indexes may not be sequential. Also, the index may be equal to the length of
	///< the text in the layout, if on the null run (see get_run()).

	LayoutRun* get_run() const;
	///< Gets the current run. 
	///< @return The current run.
	///<
	///< When iterating by run, at the end of each line, there's a position with a null run,
	///< so this method can return null. The null run at the end of each line ensures that all
	///< lines have at least one run, even lines consisting of only a newline.

	Pointer<LayoutLine> get_line() const;
	///< Gets the current line.
	///< @returns A smart pointer to the current line.
	///<
	///< The layout line will become invalid if changes are made to the layout.

	bool at_last_line() const;
	///< Returns true if the iterator is on the last line of the layout.
	
	void get_char_extents(Rectangle& logical_rect) const;
	///< Gets the extents of the current character, in layout coordinates
	///< (origin is the top left of the entire layout).
	///< @param logical_rect The rectangle to fill with logical extents.
	///<
	///< Only logical extents can sensibly be obtained for characters; ink extents
	///< make sense only down to the level of clusters.
	///< @param logical_rect The rectangle to fill with logical extents.

	Rectangle get_char_extents() const;
	///< Returns the extents of the current character, in layout coordinates
	///< (see get_char_extents(Rectangle&) const).

	void get_cluster_extents(Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Gets the extents of the current cluster, in layout coordinates 
	///<(origin is the top left of the entire layout).
	///< @param ink_rect The rectangle to fill with the ink extents.
	///< @param logical_rect The rectangle to fill with the logical extents.

	void get_run_extents(Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Gets the extents of the current run in layout coordinates 
	///< (origin is the top left of the entire layout).
	///< @param ink_rect The rectangle to fill with the ink extents.
	///< @param logical_rect The rectangle to fill with the logical extents.

	void get_line_extents(Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Obtains the extents of the current line. 
	///< @param ink_rect The rectangle to fill with the ink extents.
	///< @param logical_rect The rectangle to fill with the logical extents.
	///<
	///< <EM>ink_rect</EM> or <EM>logical_rect</EM> can be null if you aren't
	///< interested in them. Extents are in layout coordinates (origin is the 
	///< top-left corner of the entire Layout). Thus the extents returned by this
	///< method will be the same width/height but not at the same x/y as the extents
	///< returned from Pango::LayoutLine::get_extents().

	void get_line_yrange(int *y0, int *y1) const;
	///< Divides the vertical space in the Layout being iterated over between the lines
	///< in the layout, and returns the space belonging to the current line. 
	///< @param y0 The start of the line.
	///< @param y1 The end of the line.
	///<
	///< A line's range includes the line's logical extents, plus half of the spacing
	///< above and below the line, if Pango::Layout::set_spacing() has been called to set
	///< layout spacing. The y positions are in layout coordinates (origin at top left of
	///< the entire layout).

	void get_layout_extents(Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Obtains the extents of the Layout being iterated over. 
	///< @param ink_rect The rectangle to fill with the ink extents.
	///< @param logical_rect The rectangle to fill with the logical extents.
	///<
	///< <EM>ink_rect</EM> or <EM>logical_rect</EM> can be null if you aren't
	///< interested in them.

	int get_baseline() const;
	///< Gets the y position of the current line's baseline, in layout coordinates
	///< (origin at top left of the entire layout).
	///< @return The baseline of the current line.

/// @}
/// @name Methods
/// @{

	bool next_char();
	///< Moves the iterator forward to the next character in visual order.
	///< @return Whether motion was possible.
	///<
	///< If the iterator was already at the end of the layout, false is returned.

	bool next_cluster();
	///< Moves the iterator forward to the next cluster in visual order.
	///< @return Whether motion was possible.
	///<
	///< If the iterator was already at the end of the layout, false is returned.

	bool next_run();
	///< Moves the iterator forward to the next run in visual order.
	///< @return Whether motion was possible.
	///<
	///< If the iterator was already at the end of the layout, false is returned.

	bool next_line();
	///< Moves the iterator forward to the next line in visual order.
	///< @return Whether motion was possible.
	///<
	///< If the iterator was already at the end of the layout, false is returned.

/// @}
};

/// @class Layout layout.hh xfc/pango/layout.hh
/// @brief A PangoLayout C++ wrapper class.
///
/// The Layout object represents and entire paragraph of text. It is initialized
/// with a Context, UTF-8 string and a set of attributes for that string. Once that
/// is done, the set of formatted lines can be extracted from the object, the 
/// layout can be rendered, and conversion between logical character positions 
/// within the layout's text, and the physical position of the resulting glyphs
/// can be made.
///
/// There are also a number of parameters to adjust the formatting of a Layout,
/// which are illustrated in Figure 1. It is possible, as well, to ignore the
/// 2-D setup, and simply treat the results of a Layout as a list of lines.
///
/// <B>Figure 1:</B> Adjustable parameters for a Layout.
/// @image html layout.png
///
/// <BR>The Layout object provides a high-level driver for formatting entire paragraphs
/// of text at once. While complete access to the layout capabilities of Pango is
/// provided using the detailed interfaces for itemization and shaping, using that
/// functionality directly involves writing a fairly large amount of code.
///
/// <B>Note:</B> <layout.hh> is the main Pango header file that your application
/// will include, so for convenience, it includes all the required header files,
/// except <break.hh> (LogAttr) and <glyph.hh> (GlyphString).
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Layout : public G::Object
{
	friend class G::Object;

	Layout(const Layout&);
	Layout& operator=(const Layout&);

protected:
/// @name Constructors
/// @{

	explicit Layout(PangoLayout *layout, bool owns_reference = true);
	///< Construct a new Layout from an existing PangoLayout.
	///< @param layout A pointer to a PangoLayout.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>layout</EM> can be a newly created PangoLayout or an existing
	///< PangoLayout. (see G::Object::Object).

/// @}

public:
	typedef PangoLayout CObjectType;

/// @name Constructors
/// @{
	
	explicit Layout(const Context& context);
	///< Construct a new layout object with attributes initialized to the
	///< default values for the <EM>context</EM>.
	///< @param context A Context.
	///<
	///< A Layout object is created with a reference count of 1 that the caller owns.

	virtual ~Layout();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	PangoLayout* pango_layout() const;
	///< Get a pointer to the PangoLayout structure.

	operator PangoLayout* () const;
	///< Conversion operator; safely converts a Layout to a PangoLayout pointer.

	Context* get_context() const;
	///< Returns the Context used for this layout. This does not have an additional
	///< reference count added, so if you want to keep a copy of this around, you 
	///< must reference it yourself, or use a smart pointer.
	
	AttrList* get_attributes() const;
	///< Gets the attribute list for the layout, if any.
	///< @returns A smart pointer to the attribute list for the layout, or null if none is in use.
	
	String get_text() const;
	///< Gets the text in the layout.
	///< @returns The text in the layout.

	Pointer<FontDescription> get_font_description() const;
	///< Gets the font description for the layout, if any.
	///< @return A smart pointer to the layout's font description.
	///<	 
	///< This method returns a null pointer if the font description from the
	///< layout's context is inherited.	

	int get_width() const;
	///< Gets the width to which the lines of the layout should be wrapped.
	///< @return The width.

	WrapMode get_wrap() const;
	///< Returns the active wrap mode for the layout.
	
	int get_indent() const;
	///< Returns the amount by which the first line should be shorter than the rest of the lines.
	
	int get_spacing() const;
	///< Gets the amount of spacing between the lines of the layout (in GlyphUnits).
	
	bool get_justify() const;
	///< Returns whether or not each complete line should be stretched to fill
	///< the entire width of the layout.

	bool get_auto_dir() const;
	///< Gets whether to calculate the bidirectional base direction for the layout 
	///< according to the contents of the layout (see set_auto_dir()).
 	///< @returns If <EM>true</EM>, the bidirectional base direction is computed from the layout's contents. 	
	
	Alignment get_alignment() const;
	///< Sets the alignment for the layout (how partial lines are positioned within
	///< the horizontal space available).
	///< @return The alignment value.

	Pointer<TabArray> get_tabs() const;
	///< Get the current TabArray used by this layout. 
	///< @return A copy of the tabs for this layout, or null.
	///<
	///< If no TabArray has been set, then the default tabs are in use and null
	///< is returned. Default tabs are every 8 spaces.
	
	bool get_single_paragraph_mode() const;
	///< Obtains the value set by set_single_paragraph_mode().
	///< @return <EM>true</EM> if the layout does not break paragraphs at paragraph separator characters.

	EllipsizeMode get_ellipsize() const;
	///< Gets the type of ellipsization being performed for layout (see set_ellipsize()).
	///< @return The current ellipsization mode for the layout.	
	
	bool get_logical_attributes(std::vector<LogAttr>& attrs) const;
	///< Retrieve a list of logical attributes for each character in the layout.
	///< @param attrs A reference to a vector of LogAttr to store the logical attributes.
 	///<
	///< When this method returns the size of the vector will be equal
	///< to the total number of characters in the layout.

	void get_cursor_pos(int index, Rectangle *strong_pos, Rectangle *weak_pos) const;
	///< Given an index within the layout, determine the positions that of the strong
	///< and weak cursors if the insertion point is at that index. 
	///< @param index The byte index of the cursor.
	///< @param strong_pos The location to store the strong cursor position (may be null).
	///< @param weak_pos The location to store the weak cursor position (may be null).
	///<
	///< The position of each cursor is stored as a zero-width rectangle. 
	///< The strong cursor location is the location where characters of the 
	///< directionality equal to the base direction of the layout are inserted.
	///< The weak cursor location is the location where characters of the 
	///< directionality opposite to the base direction of the layout are inserted.

	void get_extents(Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Compute the logical and ink extents of the layout.
	///< @param ink_rect The rectangle used to store the extents of the layout as drawn,
	///<                 or null to indicate that the result is not needed.
	///< @param logical_rect The rectangle used to store the logical extents of the layout,
	///<                 or null to indicate that the result is not needed.
	///<
	///< Logical extents are usually what you want for positioning things. 
	///< The extents are given in layout coordinates; layout coordinates begin
	///< at the top left corner of the layout.

	void get_pixel_extents(Rectangle *ink_rect, Rectangle *logical_rect) const;
	///< Compute the logical and ink extents of the layout in device units.
	///< @param ink_rect The rectangle used to store the extents of the layout as drawn,
	///<                 or null to indicate that the result is not needed.
	///< @param logical_rect The rectangle used to store the logical extents of the layout,
	///<                 or null to indicate that the result is not needed.
	///<
	///< See get_extents(); this method just calls get_extents() and then
	///< converts the extents to device units using the PANGO_SCALE factor.

	void get_size(int *width, int *height) const;
	///< Determine the logical width and height of the layout in Pango units
	///< (device units divided by PANGO_SCALE). 
	///< @param width The location to store the logical width, or null.
	///< @param height The location to store the logical height, or null.
	///<
	///< This is simply a convenience method around get_extents.

	void get_pixel_size(int *width, int *height) const;
	///< Determine the logical width and height of the layout in device units.
	///< @param width The location to store the logical width, or null.
	///< @param height The location to store the logical height, or null.
	///<
	///< get_size() returns the width and height in thousandths of a device unit.
	///< This is simply a convenience function around get_extents().
	
	int get_line_count() const;
	///< Retrieve the count of lines for the layout.
	///< @return The line count.

	Pointer<LayoutLine> get_line(int line) const;
	///< Retrieves a particular line from the layout.
	///< @param line The index of a line, which must be between 0 and get_line_count() - 1, inclusive.
	///< @return The requested LayoutLine, or null if the index is out of range. 
	///<
	///< This layout line can be retained, but will become invalid if changes are made to the layout.

	bool get_lines(std::vector<Pointer<LayoutLine> >& lines) const;
	///< Retrieves the lines of the layout.
	///< @param lines A reference to a vector of LayoutLine to hold the lines.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< This returned lines will become invalid on any change to the layout's text or properties.
  	
	Pointer<LayoutIter> get_iter() const;
	///< Obtains an iterator to iterate over the visual extents of the layout.
	///< @return A smart pointer to a new LayoutIter.

	Pointer<Gdk::Region> get_clip_region(int x_origin, int y_origin, const std::vector<std::pair<int, int> >& index_ranges) const;
	///< Obtains a clip region which contains the areas where the given ranges of text
	///< would be drawn (see Pango::LayoutLine::get_x_ranges() for more on using std::pair).
	///< @param x_origin The X pixel where you intend to draw the layout with this clip.
	///< @param y_origin The Y pixel where you intend to draw the layout with this clip.
	///< @param index_ranges A reference to a vector of int/int pairs that holds the index
	///<                     ranges. The <EM>first</EM> value of each pair is the start index
	///<                     and the <EM>second</EM> value is the end index.
	///< @return A smart pointer to a new clip region containing the given ranges.
	///<
	///< <EM>x_origin</EM> and <EM>y_origin</EM> are the same position you would pass
	///< to Gdk::Drawable::draw_layout_line(). <EM>index_ranges</EM> should contain ranges
	///< of bytes in the layout's text.
	///<
	///< Pango::LayoutLine::get_x_ranges() shows you how to access the values returned
	///< in a vector of int/int pairs. The easiest way to create a vector of int/int
	///< pairs is to assign a pair to each vector element using the subscriipt operator,
	///< something like this:
	///< @code
	///< typedef std::pair<int, int> Range;
	///< std::vector<Range> ranges(count);
	///<
	///< for (int i = 0; i < count; i++)
	///< {
	///< 	// calculate start_index and end_index here
	///< 	...
	///< 	ranges[i] = Range(start_index, end_index));
	///< 	...
	///< }
	///< layout->get_clip_region(x_origin, y_origin, ranges);
	///< @endcode

/// @}
/// @name Methods
/// @{

	void set_attributes(AttrList& attrs);
	///< Sets the text attributes for a layout object.
	///< @param attrs An AttrList the list the attributes.

	void set_text(const char *text);
	void set_text(const String& text);
	///< Set the text of the layout.
	///< @param text A UTF-8 String.

	void set_markup(const char *markup);
	void set_markup(const String& markup);
	///< Sets the layout text and attribute list from marked-up text
	///< (see markup format in the GTK+ documnetation).
	///< @param markup The marked-up text.
	///<
	///< Replaces the current text and attribute list. This method doesn't scan the
	///< text for accelerators.
	
	void set_markup(const char *markup, gunichar accel_marker, gunichar *accel_char);
	void set_markup(const String& markup, gunichar accel_marker, gunichar *accel_char);
	///< Sets the layout text and attribute list from marked-up text
	///< (see markup format in the Pango documnetation).
	///< @param markup Some marked-up text (see markup format in the GTK+ documnetation).
	///< @param accel_marker The marker for accelerators in the text.
	///< @param accel_char The return location for any located accelerators.
	///<
	///< Replaces the current text and attribute list. If accel_marker is nonzero, 
	///< the given character will mark the character following it as an accelerator.
	///< For example, the accel marker might be an ampersand or underscore. All 
	///< characters marked as an accelerator will receive a PANGO_UNDERLINE_LOW 
	///< attribute, and the first character so marked will be returned in accel_char.
	///< Two accel_marker characters following each other produce a single literal 
	///< accel_marker character.

	void set_font_description(const FontDescription *desc);
	///< Set the default font description for the layout. 
	///< @param desc The new pango font description, or null to unset the current font description.
	///<
	///< If no font description is set on the layout, the font description
	///< from the layout's context is used.
	
	void set_width(int width);
	///< Sets the width to which the lines of the layout should be wrapped.
	///< @param width The desired width, or -1 to indicate that no wrapping should be performed.

	void set_wrap(WrapMode wrap);
	///< Sets the wrap style; the wrap style only has an effect if a width
	///< is set on the layout with Pango::Layout::set_width(). 
	///< @param wrap The wrap mode.
	///<
	///< To turn off wrapping, set the width to -1.

	void set_indent(int indent);
	///< Sets the amount by which the first line should be shorter 
	///< than the rest of the lines.
	///< @param indent The amount by which to indent.
	///<
	///< The <EM>indent</EM> may be negative, in which case the subsequent lines
	///< will be shorter than the first line.

	void set_spacing(int spacing);
	///< Sets the amount of spacing between the lines of the layout.
	///< @param spacing The amount of spacing.

	void set_justify(bool justify);
	///< Sets whether or not each complete line should be stretched
	///< to fill the entire width of the layout. 
	///< @param justify Whether the lines in the layout should be justified.
	///<
	///< This stretching is typically done by adding whitespace, but for some scripts
	///< (such as Arabic), the justification is done by extending the characters.

	void set_auto_dir(bool auto_dir);
	///< Sets whether to calculate the bidirectional base direction for the layout
	///< according to the contents of the layout.
	///< @param auto_dir If <EM>true</EM>, compute the bidirectional base direction from the layout's contents.
	///<	 
	///< When this flag is on (the default), then paragraphs in the layout that
	///< begin with strong right-to-left characters (Arabic and Hebrew principally),
	///< will have right-to-left layout, paragraphs with letters from other scripts
	///< will have left-to-right layout. Paragraphs with only neutral characters get
	///< their direction from the surrounding paragraphs. 
	///<
	///< When <EM>false</EM>, the choice between left-to-right and right-to-left layout
	///< is done by according to the base direction of the layout's Pango::Context (see
	///< Pango::Context::set_base_dir()). 
	///<
	///< When the auto-computed direction or a paragraph differs from the base direction
	///< of the context, then the interpretation of Pango::ALIGN_LEFT and Pango::ALIGN_RIGHT
	///< are swapped.
	
	void set_alignment(Alignment alignment);
	///< Sets the alignment for the layout (how partial lines are positioned within
	///< the horizontal space available.)
	///< @param alignment The new alignment.

	void set_tabs(TabArray *tabs);
	///< Sets the tabs to use for the layout, overriding the default tabs (by default,
	///< tabs are every 8 spaces). 
	///< @param tabs A TabArray.
	///<
	///< If tabs is null, the default tabs are reinstated. <EM>tabs</EM> is copied
	///< into the layout so you must unreference your copy of <EM>tabs</EM> yourself, or
	///< create it using a smart pointer.

	void set_single_paragraph_mode(bool setting);
	///< If <EM>setting</EM> is <EM>true</EM>, do not treat newlines and similar characters
	///< as paragraph separators; instead, keep all text in a single paragraph, and display
	///< a glyph for paragraph separator characters. 
	///< @param setting The new setting.
	///<
	///< This is used when you want to allow editing of newlines on a single text line.

	void set_ellipsize(EllipsizeMode ellipsize);
	///< Sets the type of ellipsization being performed for the layout. 
	///< @param ellipsize The new ellipsization mode for the layout.
	///<	
	///< Depending on the ellipsization mode ellipsize text is removed from
	///< the start, middle, or end of lines so they fit within the width of
	///< layout set with set_width(). If the layout contains characters such
	///< as newlines that force it to be layed out in multiple lines, then 
	///< each line is ellipsized separately.

	void context_changed();
	///< Forces recomputation of any state in the Layout that might depend on
	///< the layout's context. This method should be called if you make changes
	///< to the context subsequent to creating the layout.
	
	void index_to_pos(int index, Rectangle& pos);
	///< Convert from an index within a layout to the onscreen position corresponding
	///< to the grapheme at that index, which is represented as a rectangle. 
	///< @param index The byte index within layout.
	///< @param pos The rectangle in which to store the position of the grapheme.
	///<
	///< Note that pos.x() is always the leading edge of the grapheme
	///< and pos.x() + pos.width() the trailing edge of the grapheme. If the
	///< directionality of the grapheme is right-to-left, then pos.width() 
	///< will be negative.

	void move_cursor_visually(bool strong, int old_index, int old_trailing, int direction, int *new_index, int *new_trailing);
	///< Computes a new cursor position from an old position and
	///< a count of positions to move visually.
	///< @param strong Whether the moving cursor is the strong cursor or the weak cursor.
	///<               The strong cursor is the cursor corresponding to text insertion in
	///<               the base direction for the layout.
	///< @param old_index The byte index of the grapheme for the old index.
	///< @param old_trailing If 0, the cursor was at the trailing edge of the grapheme
	///<               indicated by old_index, if > 0, the cursor was at the leading edge.
	///< @param direction The direction to move cursor. A negative value indicates motion to the left.
	///< @param new_index The location to store the new cursor byte index. A value of -1
	///<                  indicates that the cursor has been moved off the beginning
	///<                  of the layout. A value of G_MAXINT indicates that the cursor
	///<                  has been moved off the end of the layout.
	///< @param new_trailing The number of characters to move forward from the location
	///<                     returned for new_index to get the position where the cursor
	///<                     should be displayed. This allows distinguishing the position
	///<                     at the beginning of one line from the position at the end of
	///<                     the preceding line. <EM>new_index</EM> is always on the line
	///<                     where the cursor should be displayed.
	///<
	///< If the position count is positive, then the new strong cursor position will
	///< be one position to the right of the old cursor position. If the count is negative
	///< then the new strong cursor position will be one position to the left of the old
	///< cursor position. In the presence of bidirectional text, the correspondence 
	///< between logical and visual order will depend on the direction of the current run,
	///< and there may be jumps when the cursor is moved off of the end of a run.
	///<
	///< Motion here is in cursor positions, not in characters, so a single
	///< call to move_cursor_visually() may move the cursor over multiple 
	///< characters when multiple characters combine to form a single grapheme.

	bool xy_to_index(int x, int y, int *index, int *trailing);
	///< Convert from X and Y position within a layout to the byte index
	///< to the character at that logical position. 
	///< @param x The X offset (in GlyphUnits) from the left edge of the layout.
	///< @param y The Y offset (in GlyphUnits) from the top edge of the layout.
	///< @param index The location to store calculated byte index.
	///< @param trailing The location to store a integer indicating where in the
	///<                 grapheme the user clicked.
	///< @returns <EM>true</EM> if the coordinates were inside text.
	///<
	///< If the position is not inside the layout, the closest position
	///< is chosen (the x/y position will be clamped inside the layout). If
	///< a closest position is chosen, then the method returns false; on an
	///< exact hit, it returns true. <EM>trailing</EM> will either be zero,
	///< or the number of characters in the grapheme. 0 represents the
	///< trailing edge of the grapheme.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/layout.inl>

#endif // XFC_PANGO_LAYOUT_HH

