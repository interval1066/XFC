/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2002-2003 The XFC Development Team.
 *
 *  region.cc - GdkRegion C++ wrapper implementation
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
 
#include "region.hh"
#include "types.hh"
#include <gdk/gdk.h>

using namespace Xfc;

Gdk::Region::Region()
: region_(gdk_region_new())
{
}

Gdk::Region::Region(const std::vector<Point>& points, FillRule fill_rule)
{
	g_return_if_fail(!points.empty());
	int count = points.size();
	GdkPoint *tmp_points = new GdkPoint[count];

	int i = 0;
	while (i < count)
	{
		tmp_points[i] = *points[i].gdk_point();
		++i;
	}

	region_ = gdk_region_polygon(tmp_points, count, (GdkFillRule)fill_rule);
	delete [] tmp_points;
}

Gdk::Region::Region(const Rectangle& rectangle)
: region_(gdk_region_rectangle(rectangle.gdk_rectangle()))
{
}

Gdk::Region::Region(GdkRegion *region, bool copy)
: region_(copy ? gdk_region_copy(region) : region)
{
}

Gdk::Region::Region(const Region& src)
: region_(gdk_region_copy(src.region_))
{
}
	
Gdk::Region::~Region() 
{
	if (region_)
	{
		gdk_region_destroy(region_);
		region_ = 0;
	}
}
	
Gdk::Region& 
Gdk::Region::operator=(const Region& src)
{
	if (src.region_ == region_)
		return *this;
		
	if (region_)
		gdk_region_destroy(region_);
		
	region_ = gdk_region_copy(src.region_);
	return *this;
}

Gdk::Rectangle
Gdk::Region::get_clipbox() const
{
	GdkRectangle rectangle;
	gdk_region_get_clipbox(region_, &rectangle);
	return rectangle;
}

void
Gdk::Region::get_clipbox(Rectangle& rectangle) const
{
	gdk_region_get_clipbox(region_, rectangle.gdk_rectangle());
}

std::vector<Gdk::Rectangle>
Gdk::Region::get_rectangles() const
{
	std::vector<Rectangle> rectangles;
	GdkRectangle *tmp_rectangles = 0;
	int count = 0;

	gdk_region_get_rectangles(region_, &tmp_rectangles, &count);

	int i = 0;
	while (i < count)
	{
		rectangles.push_back(tmp_rectangles[i]);
		++i;
	}

	g_free(tmp_rectangles);
	return rectangles;
}

bool
Gdk::Region::equal(const Region& other) const
{
	return gdk_region_equal(region_, other.region_);
}

bool
Gdk::Region::point_in(const Point& point) const
{
	return gdk_region_point_in(region_, point.x(), point.y());
}

Gdk::OverlapType
Gdk::Region::rect_in(const Rectangle& rectangle) const
{
	return (OverlapType)gdk_region_rect_in(region_, rectangle.gdk_rectangle());
}

bool
Gdk::Region::operator==(const Region& other) const
{
	return gdk_region_equal(region_, other.region_) != 0;
}

bool
Gdk::Region::operator!=(const Region& other) const
{
	return gdk_region_equal(region_, other.region_) == 0;
}

void
Gdk::Region::union_with(const Rectangle& rectangle)
{
	gdk_region_union_with_rect(region_, rectangle.gdk_rectangle());
}

void
Gdk::Region::union_with(const Region& other)
{
	gdk_region_union(region_, other.region_);
}

void
Gdk::Region::intersect(const Region& other)
{
	gdk_region_intersect(region_, other.region_);
}

void
Gdk::Region::subtract(const Region& other)
{
	gdk_region_subtract(region_, other.region_);
}

void
Gdk::Region::xor_with(const Region& other)
{
	gdk_region_xor(region_, other.region_);
}

namespace { // spans_intersect_foreach_slot

void spans_intersect_foreach_slot(GdkSpan *span, gpointer data)
{
	Gdk::Region::SpansIntersectForeachSlot& slot = *static_cast<Gdk::Region::SpansIntersectForeachSlot*>(data);
	slot(span);
}

} // namespace

void	
Gdk::Region::spans_intersect_foreach(const std::vector<Span>& spans, bool sorted, const SpansIntersectForeachSlot& slot)
{
	g_return_if_fail(!spans.empty());

	int count = spans.size();
	GdkSpan *tmp_spans = new GdkSpan[count];

	int i = 0;
	while (i < count)
	{
		tmp_spans[i] = *spans[i].gdk_span();
		++i;
	}

	SpansIntersectForeachSlot tmp_slot(slot);
	gdk_region_spans_intersect_foreach(region_, tmp_spans, count, sorted, &spans_intersect_foreach_slot, &tmp_slot);
	delete [] tmp_spans;
}

