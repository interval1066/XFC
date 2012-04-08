/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  types.cc - GdkPoint, GdkRectangle, GdkSegment and GdkSpan C++ wrapper implementation
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

#include "types.hh"
#include <algorithm>
#include <gdk/gdk.h>

using namespace Xfc;

/*  Gdk::Point
 */

Gdk::Point::Point()
{
	set(0, 0);
}

Gdk::Point::Point(int x, int y)
{
	set(x, y);
}

Gdk::Point::Point(double x, double y)
{
	set(x, y);
}

Gdk::Point::Point(const GdkPoint& point)
{
	set(point.x, point.y);
}

bool
Gdk::Point::operator==(const Point& other) const
{
	return point_.x == other.x() && point_.y == other.y();
}

bool
Gdk::Point::operator!=(const Point& other) const
{
	return point_.x != other.x() && point_.y != other.y();
}

void
Gdk::Point::set(int x, int y)
{
	point_.x = x;
	point_.y = y;
}

void
Gdk::Point::set(double x, double y)
{
	point_.x = (int)x;
	point_.y = (int)y;
}

Gdk::Point&
Gdk::Point::offset(int dx, int dy)
{
	point_.x += dx;
	point_.y += dy;
	return *this;
}

Gdk::Point&
Gdk::Point::operator+=(int increment)
{
	point_.x += increment;
	point_.y += increment;
	return *this;
}

Gdk::Point&
Gdk::Point::operator+=(const Point& other)
{
	point_.x += other.x();
	point_.y += other.y();
	return *this;
}

Gdk::Point&
Gdk::Point::operator-=(int increment)
{
	point_.x -= increment;
	point_.y -= increment;
	return *this;
}

Gdk::Point&
Gdk::Point::operator-=(const Point& other)
{
	point_.x -= other.x();
	point_.y -= other.y();
	return *this;
}

Gdk::Point&
Gdk::Point::operator++()
{
	++point_.x;
	++point_.y;
	return *this;
}

Gdk::Point&
Gdk::Point::operator--()
{
	--point_.x;
	--point_.y;
	return *this;
}

Gdk::Point 
Gdk::Point::offset_by(int dx, int dy)
{
	return Point(point_.x + dx, point_.y + dy);
}

Gdk::Point 
Gdk::Point::operator+(const Point& other) const
{
	return Point(point_.x + other.x(), point_.y + other.y());
}

Gdk::Point
Gdk::Point::operator-(const Point& other) const
{
	return Point(point_.x - other.x(), point_.y - other.y());
}

/*  Gdk::Rectangle
 */

Gdk::Rectangle::Rectangle()
{
	set(0, 0, 0, 0);
}

Gdk::Rectangle::Rectangle(int x, int y, int width, int height)
{
	set(x, y, width, height);
}

Gdk::Rectangle::Rectangle(const Point& point, int width, int height)
{
	set(point.x(), point.y(), width, height);
}

Gdk::Rectangle::Rectangle(const GdkRectangle& rectangle)
{
	set(rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

Gdk::Point
Gdk::Rectangle::center() const
{
	return Point(rectangle_.x + rectangle_.width / 2, rectangle_.y + rectangle_.height / 2);
}

bool
Gdk::Rectangle::contains(const Point& point) const
{
	return point.x() >= rectangle_.x && point.x() <= (rectangle_.x + rectangle_.width) &&
	       point.y() >= rectangle_.y && point.y() <= (rectangle_.y + rectangle_.height);
}

bool
Gdk::Rectangle::contains(int x, int y) const
{
	return x >= rectangle_.x && x <= (rectangle_.x + rectangle_.width) &&
	       y >= rectangle_.y && y <= (rectangle_.y + rectangle_.height);
}

bool
Gdk::Rectangle::equal(const Rectangle& other) const
{
	return rectangle_.x == other.x() && rectangle_.y == other.y() &&
	       rectangle_.width == other.width() && rectangle_.height == other.height();
}

bool
Gdk::Rectangle::intersect(const Rectangle& other) const
{
	GdkRectangle tmp_rectangle;
	return gdk_rectangle_intersect(gdk_rectangle(), other.gdk_rectangle(), &tmp_rectangle);
}

Gdk::Point&
Gdk::Rectangle::position() const
{
	return *((Point*)this);
}

bool
Gdk::Rectangle::operator==(const Rectangle& other) const
{
	return equal(other);
}

bool
Gdk::Rectangle::operator!=(const Rectangle& other) const
{
	return !equal(other);
}

void
Gdk::Rectangle::set(int x, int y, int width, int height)
{
	rectangle_.x = x;
	rectangle_.y = y;
	rectangle_.width = width;
	rectangle_.height = height;
}

void
Gdk::Rectangle::set_empty()
{
	set_size(0, 0);
}

void
Gdk::Rectangle::set_null()
{
	set(0, 0, 0, 0);
}

void
Gdk::Rectangle::set_position(int x, int y)
{
	rectangle_.x = x;
	rectangle_.y = y;
}

void
Gdk::Rectangle::set_position(const Point& point)
{
	rectangle_.x = point.x();
	rectangle_.y = point.y();
}

void
Gdk::Rectangle::set_size(int width, int height)
{
	rectangle_.width = width;
	rectangle_.height = height;
}

void
Gdk::Rectangle::capture(Point& point) const
{
	int x = std::min(std::max(point.x(), rectangle_.x), (rectangle_.x + rectangle_.width) - 1);
	int y = std::min(std::max(point.y(), rectangle_.y), (rectangle_.y + rectangle_.height) - 1);
	point.set(x, y);
}

Gdk::Rectangle&
Gdk::Rectangle::inflate(int dx, int dy)
{
	set(rectangle_.x - dx, rectangle_.y - dy, rectangle_.width + dx * 2, rectangle_.height + dy * 2);
	return *this;
}

bool
Gdk::Rectangle::intersect_with(const Rectangle& other)
{
	return gdk_rectangle_intersect(gdk_rectangle(), other.gdk_rectangle(), gdk_rectangle());
}

Gdk::Rectangle&
Gdk::Rectangle::offset(int dx, int dy)
{
	set_position(rectangle_.x + dx, rectangle_.y + dy);
	return *this;
}

void
Gdk::Rectangle::union_with(const Rectangle& other)
{
	gdk_rectangle_union(gdk_rectangle(), other.gdk_rectangle(), gdk_rectangle());
}

Gdk::Rectangle&
Gdk::Rectangle::operator+=(int increment)
{
	return inflate(increment, increment);
}

Gdk::Rectangle&
Gdk::Rectangle::operator+=(const Point& point)
{
	return offset(point.x(), point.y());
}

Gdk::Rectangle&
Gdk::Rectangle::operator-=(int increment)
{
	return inflate(-increment, -increment);
}

Gdk::Rectangle&
Gdk::Rectangle::operator-=(const Point& point)
{
	return offset(-point.x(), -point.y());
}

Gdk::Rectangle&
Gdk::Rectangle::operator++()
{
	return inflate(1, 1);
}

Gdk::Rectangle&
Gdk::Rectangle::operator--()
{
	return inflate(-1, -1);
}

bool
Gdk::Rectangle::operator&=(const Rectangle& other)
{
	return intersect_with(other);
}

void
Gdk::Rectangle::operator|=(const Rectangle& other)
{
	return union_with(other);
}

Gdk::Rectangle
Gdk::Rectangle::inflate_by(int dx, int dy) const
{
	return Rectangle(rectangle_.x - dx, rectangle_.y - dy, rectangle_.width + dx * 2, rectangle_.height + dy * 2);
}

Gdk::Rectangle
Gdk::Rectangle::offset_by(int dx, int dy) const
{
	return Rectangle(rectangle_.x + dx, rectangle_.y + dy, rectangle_.width, rectangle_.height);
}

/*  Gdk::Segment
 */

Gdk::Segment::Segment()
{
	set(0, 0, 0, 0);
}

Gdk::Segment::Segment(int x1, int y1, int x2, int y2)
{
	set(x1, y1, x2, y2);
}

Gdk::Segment::Segment(const Point& start, const Point& end)
{
	set(start, end);
}

bool
Gdk::Segment::equal(const Segment& segment) const
{
	return segment.x1() == segment_.x1 && segment.y1() == segment_.y1 &&
	       segment.x2() == segment_.x2 && segment.y2() == segment_.y2;
}

bool 
Gdk::Segment::operator==(const Segment& segment) const
{
	return equal(segment);
}

bool 
Gdk::Segment::operator!=(const Segment& segment) const
{
	return !equal(segment);
}

void 
Gdk::Segment::set(int x1, int y1, int x2, int y2)
{
	segment_.x1 = x1;
	segment_.y1 = y1;
	segment_.x2 = x2;
	segment_.y2 = y2;
}

void 
Gdk::Segment::set(const Point& start, const Point& end)
{
	set(start.x(), start.y(), end.x(), end.y());
}

void
Gdk::Segment::set_start(int x, int y)
{
	segment_.x1 = x;
	segment_.y1 = y;
}

void 
Gdk::Segment::set_start(const Point& point)
{
	segment_.x1 = point.x();
	segment_.y1 = point.y();
}

void 
Gdk::Segment::set_end(int x, int y)
{
	segment_.x2 = x;
	segment_.y2 = y;
}	
	
void 
Gdk::Segment::set_end(const Point& point)
{
	segment_.x2 = point.x();
	segment_.y2 = point.y();
}

/*  Gdk::Span
 */
 
Gdk::Span::Span()
{
	set(0, 0, 0);
}

Gdk::Span::Span(int x, int y, int width)
{
	set(x, y, width);
}

Gdk::Span::Span(const Point& first, int width)
{
	set(first, width);
}

bool
Gdk::Span::equal(const Span& other) const
{
	return span_.x == other.x() && span_.y == other.y() && span_.width == other.width();
}

bool
Gdk::Span::operator==(const Span& other) const
{
	return equal(other);
}

bool 
Gdk::Span::operator!=(const Span& other) const
{
	return !equal(other);
}

void
Gdk::Span::set(int x, int y)
{
	span_.x = x;
	span_.y = y;
}

void
Gdk::Span::set(const Point& first)
{
	span_.x = first.x();
	span_.y = first.y();
}

void
Gdk::Span::set(int x, int y, int width)
{
	span_.x = x;
	span_.y = y;
	span_.width = width;
}

void
Gdk::Span::set(const Point& first, int width)
{
	set(first.x(), first.y(), width);
}

/*  Gdk::Trapezopid
 */
 
Gdk::Trapezoid::Trapezoid()
{
	set(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

Gdk::Trapezoid::Trapezoid(double y1, double x11, double x21, double y2, double x12, double x22)
{
	set(y1, x11, x21, y2, x21, x22);
}

void 
Gdk::Trapezoid::set(double y1, double x11, double x21, double y2, double x12, double x22)
{
	trapezoid_.y1 = y1;
	trapezoid_.x11 = x11;
	trapezoid_.x21 = x21;
	trapezoid_.y2 = y2;
	trapezoid_.x21 = x21;
	trapezoid_.x22 = x22;
}

