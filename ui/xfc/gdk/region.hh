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
 
/// @file xfc/gdk/region.hh
/// @brief A GdkRegion C++ wrapper interface.
///
/// Provides Region, an object that holds a set of arbitrary pixels, and is usually
/// used for clipping graphical operations (see Gdk::GC::set_clip_region()).

#ifndef XFC_GDK_REGION_HH
#define XFC_GDK_REGION_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __GDK_REGION_H__
#include <gdk/gdkregion.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {
	
class Rectangle;
class Point;
class Span;

/// @enum FillRule
/// Specifies the method for determining which pixels are included in a region, 
/// when creating a Region from a polygon. The fill rule is only relevant for 
/// polygons which overlap themselves.

enum FillRule
{
	EVEN_ODD_RULE = GDK_EVEN_ODD_RULE,
	///< Areas which are overlapped an odd number of times are included in the region,
	///< while areas overlapped an even number of times are not.

	WINDING_RULE = GDK_WINDING_RULE
	///< Overlapping areas are always included.
};

/// @enum OverlapType
/// Specifies the possible values returned by Gdk::Region::rect_in().

enum OverlapType
{
	OVERLAP_RECTANGLE_IN = GDK_OVERLAP_RECTANGLE_IN, ///< The rectangle is inside the Region.
	OVERLAP_RECTANGLE_OUT = GDK_OVERLAP_RECTANGLE_OUT, ///< The rectangle is outside the Region.
	OVERLAP_RECTANGLE_PART = GDK_OVERLAP_RECTANGLE_PART ///< The rectangle is partly inside the Region.
};

/// @class Region region.hh xfc/gdk/region.hh
/// @brief A GdkRegion C++ wrapper class.
///
/// Region is an object that represents an arbitrary set of pixels on the screen, and
/// is usually used for clipping graphical operations (see Gdk::GC::set_clip(const Region&)).
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class Region : public Xfc::Object
{
	GdkRegion *region_;

public:
	typedef sigc::slot<void, GdkSpan*> SpansIntersectForeachSlot;
	///< Signature of the callback slot to be called on each span in the
	///< intersection of a region and an array of spans.
	///< <B>Example:</B> Method signature for SpansIntersectForeachSlot.
	///< @code
	///< void method(GdkSpan *span);
	///<
	///< // span: A GdkSpan.
	///< @endcode
	///< This is the type of slot passed to spans_intersect_foreach().

/// @name Constructors
/// @{

	Region();
	///< Constructs a new empty region with a reference count of 1 that the caller owns.

	Region(const std::vector<Point>& points, FillRule fill_rule);
	///< Construct a new region using the polygon defined by a number of points.
	///< @param points A reference to a vector of Point that holds the points defining the polygon.
	///< @param fill_rule Specifies which pixels are included in the region when the polygon overlaps itself.
	///<
	///< The region is created with a reference count of 1 that the caller owns.

	Region(const Rectangle& rectangle);
	///< Constructs a new region containing the area <EM>rectangle</EM>.
	///< @param rectangle A Gdk::Rectangle.
	///<
	///< The region is created with a reference count of 1 that the caller owns.

	Region(GdkRegion *region, bool copy);
	///< Construct a new region from an existing GdkRegion.
	///< @param region A pointer to a GdkRegion.
	///< @param copy Set <EM>true</EM> if <EM>region</EM> should be copied.	
	///<
	///< If <EM>copy</EM> is false the Region takes over the reference count
	///< of <EM>region</EM>. The new Region created has a reference count of 1
	///< that the caller owns.
	
	Region(const Region& src);
	///< Copy constructor.
	///< @param src The source region.

	virtual ~Region();
	///< Destructor.

	Region& operator=(const Region& src);
	///< Assignment operator.
	///< @param src The source region.

/// @}
/// @name Accessors
/// @{

	GdkRegion* gdk_region() const;
	///< Get a pointer to the GdkRegion structure.

	operator GdkRegion* () const;
	///< Conversion operator; safely converts a Region to a GdkRegion pointer.

	Rectangle get_clipbox() const;
	///< Gets the smallest rectangle which includes the entire region.
	///< @return The smallest rectangle which includes all of the region.

	void get_clipbox(Rectangle& rectangle) const;
	///< Gets the smallest rectangle which includes the entire region.
	///< @param rectangle The location to store the smallest rectangle
	///< which includes all of the region.

	std::vector<Rectangle> get_rectangles() const;
	///< Obtains the area covered by the region as a list of rectangles.
	///< @return A vector of Rectangle that holds the list of rectangles.

	bool empty() const;
	///< Returns true if the region is empty.
	
	bool equal(const Region& other) const;
	///< Returns true if this region and other are the same.
	
	bool point_in(int x, int y) const;
	///< Returns true if a point is in the region.
	///< @param x The X coordinate of a point.
	///< @param y The Y coordinate of a point.
	///< @return <EM>true</EM> if the point is in the region.

	bool point_in(const Point& point) const;
	///< Returns true if a point is in the region.
	///< @param point The Point to test.
	///< @return <EM>true</EM> if the point is in the region.

	OverlapType rect_in(const Rectangle& rectangle) const;
	///< Tests whether a rectangle is within a region.
	///< @param rectangle A Gdk::Rectangle.
	///< @return OVERLAP_RECTANGLE_IN, OVERLAP_RECTANGLE_OUT, or OVERLAP_RECTANGLE_PART, depending 
	///< on whether the rectangle is inside, outside, or partly inside the Region, respectively.

	bool operator==(const Region& other) const;
	///< Equality operator; compares this region with <EM>other</EM>.
	///< @param other The region to compare.
	///< @return <EM>true</EM> if the two regions compare equal.

	bool operator!=(const Region& other) const;
	///< Inequality operator; compares this region with <EM>other</EM>.
	///< @param other The region to compare.
	///< @return <EM>true</EM> if the two regions compare unequal.

/// @}
/// @name Methods
/// @{

	void offset(int dx, int dy);
	///< Moves a region the specified distance.
	///< @param dx The distance to move the region horizontally.
	///< @param dy The distance to move the region vertically.

	void shrink(int dx, int dy);
	///< Resizes a region by the specified amount.
	///< @param dx The number of pixels to shrink the region horizontally.
	///< @param dy The number of pixels to shrink the region vertically.
	///<
	///< Positive values shrink the region. Negative values expand it.

	void union_with(const Rectangle& rectangle);
	///< Sets the area of the region to the union of the areas of the region and <EM>rectangle</EM>.
	///< @param rectangle A Gdk::Rectangle.
	///<
	///< The resulting area is the set of pixels contained in either region or rect.
	
	void union_with(const Region& other);
	///< Sets the area of the region to the union of the areas of the region and <EM>other</EM>.
	///< @param other A Region.
	///<
	///< The resulting area is the set of pixels contained in either the region or <EM>other</EM>.
	
	void intersect(const Region& other);
	///< Sets the area of the region to the intersection of the areas of the region and <EM>other</EM>.
	///< @param other A Region.
	///<
	///< The resulting area is the set of pixels contained in both the region and <EM>other</EM>.

	void subtract(const Region& other);
	///< Subtracts the area of the region from the area <EM>other</EM>.
	///< @param other A Region.
	///<
	///< The resulting area is the set of pixels contained in the region but not in <EM>other</EM>.
	
	void xor_with(const Region& other);
	///< Sets the area of the region to the exclusive-OR of the areas of the region and <EM>other</EM>.
	///< @param other A Region.
	///<
	///< The resulting area is the set of pixels contained in the region or <EM>other</EM>, but not in both.

	void spans_intersect_foreach(const std::vector<Span>& spans, bool sorted, const SpansIntersectForeachSlot& slot);
	///< Calls <EM>slot</EM> on each span in the intersection of the region and <EM>spans</EM>.
	///< @param spans A reference to a vector of Span that holds the list of Span to test.
	///< @param sorted Set <EM>true</EM> if spans is sorted wrt. the y coordinate.
	///< @param slot The slot to call on each span in the intersection.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/region.inl>

#endif // XFC_GDK_REGION_HH

