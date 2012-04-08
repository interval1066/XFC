/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  types.inl - Gdk::Point, Gdk::Rectangle, Gdk::Segment and Gdk::Span inline functions
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

/*  Keyboard/Pointer ungrab
 */

inline void
Xfc::Gdk::keyboard_ungrab(unsigned int time)
{
	gdk_keyboard_ungrab(time);
}

inline bool
Xfc::Gdk::pointer_is_grabbed()
{
	return gdk_pointer_is_grabbed();
}

inline void
Xfc::Gdk::pointer_ungrab(unsigned int time)
{
	gdk_pointer_ungrab(time);
}

/*  Gdk::Flush
 */

inline void
Xfc::Gdk::flush()
{
	gdk_flush();
}

/*  Gdk::Mutex
 */

inline void
Xfc::Gdk::Mutex::lock()
{
	gdk_threads_enter();
}

inline void
Xfc::Gdk::Mutex::unlock()
{
	gdk_threads_leave();
}

/*  Gdk::Point
 */

inline GdkPoint*
Xfc::Gdk::Point::gdk_point() const
{
	return const_cast<GdkPoint*>(&point_);
}

inline Xfc::Gdk::Point::operator GdkPoint* () const
{
	return this ? const_cast<GdkPoint*>(&point_) : 0;
}

inline int
Xfc::Gdk::Point::x() const
{
	return point_.x;
}

inline int
Xfc::Gdk::Point::y() const
{
	return point_.y;
}

inline void
Xfc::Gdk::Point::set_x(int x)
{
	point_.x = x;
}

inline void
Xfc::Gdk::Point::set_x(double x)
{
	point_.x = (int)x;
}

inline void
Xfc::Gdk::Point::set_y(int y)
{
	point_.y = y;
}

inline void
Xfc::Gdk::Point::set_y(double y)
{
	point_.y = (int)y;
}

/*  Gdk::Rectangle
 */

inline GdkRectangle*
Xfc::Gdk::Rectangle::gdk_rectangle() const
{
	return const_cast<GdkRectangle*>(&rectangle_);
}

inline Xfc::Gdk::Rectangle::operator GdkRectangle* () const
{
	return this ? const_cast<GdkRectangle*>(&rectangle_) : 0;
}

inline int
Xfc::Gdk::Rectangle::x() const
{
	return rectangle_.x;
}

inline int
Xfc::Gdk::Rectangle::y() const
{
	return rectangle_.y;
}

inline int
Xfc::Gdk::Rectangle::width() const
{
	return rectangle_.width;
}

inline int
Xfc::Gdk::Rectangle::height() const
{
	return rectangle_.height;
}

inline long
Xfc::Gdk::Rectangle::area() const
{
	return ((long)rectangle_.width) * ((long)rectangle_.height);
}

inline bool
Xfc::Gdk::Rectangle::empty() const
{
	return rectangle_.width == 0 || rectangle_.height == 0;
}

inline bool
Xfc::Gdk::Rectangle::null() const
{
	return rectangle_.x == 0 && rectangle_.y == 0 && rectangle_.width == 0 && rectangle_.height == 0;
}

/*  Gdk::Segment
 */

inline GdkSegment*
Xfc::Gdk::Segment::gdk_segment() const
{
	return const_cast<GdkSegment*>(&segment_);
}

inline Xfc::Gdk::Segment::operator GdkSegment* () const
{
	return this ? const_cast<GdkSegment*>(&segment_) : 0;
}

inline int
Xfc::Gdk::Segment::x1() const
{
	return segment_.x1;
}

inline int
Xfc::Gdk::Segment::y1() const
{
	return segment_.y1;
}

inline int
Xfc::Gdk::Segment::x2() const
{
	return segment_.x2;
}

inline int
Xfc::Gdk::Segment::y2() const
{
	return segment_.y2;
}

/*  Gdk::Span
 */

inline GdkSpan*
Xfc::Gdk::Span::gdk_span() const
{
	return const_cast<GdkSpan*>(&span_);
}

inline Xfc::Gdk::Span::operator GdkSpan* () const
{
	return this ? const_cast<GdkSpan*>(&span_) : 0;
}

inline int
Xfc::Gdk::Span::x() const
{
	return span_.x;
}

inline int
Xfc::Gdk::Span::y() const
{
	return span_.y;
}

inline int
Xfc::Gdk::Span::width() const
{
	return span_.width;
}

