/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  types.cc - Pango types C++ wrapper implementation
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
#include "xfc/glib/unicode.hh"

using namespace Xfc;

/*  Pango::unichar_direction
 */

Pango::Direction 
Pango::unichar_direction(G::Unichar ch)
{
	return (Direction)pango_unichar_direction(ch);
}

/*  Pango::find_base_dir
 */

Pango::Direction 
Pango::find_base_dir(const char *text, int length)
{
	return (Direction)pango_find_base_dir(text, length);
}

/*  Pango::Rectangle
 */

Pango::Rectangle::Rectangle()
{
	set(0, 0, 0, 0);
}

Pango::Rectangle::Rectangle(int x, int y, int width, int height)
{
	set(x, y, width, height);
}

Pango::Rectangle::Rectangle(const PangoRectangle& rectangle)
{
	set(rectangle.x, rectangle.y, rectangle.width, rectangle.height);
}

void
Pango::Rectangle::set(int x, int y, int width, int height)
{
	rectangle_.x = x;
	rectangle_.y = y;
	rectangle_.width = width;
	rectangle_.height = height;
}

/*  Pango::Matrix
 */
 
Pango::Matrix::Matrix()
: G::Boxed(PANGO_TYPE_MATRIX)
{
	PangoMatrix matrix = PANGO_MATRIX_INIT;
	copy(&matrix);
}
	
Pango::Matrix::Matrix(double xx, double xy, double yx, double yy, double x0, double y0)
: G::Boxed(PANGO_TYPE_MATRIX)
{
	PangoMatrix matrix = { xx, xy, yx, yy, x0, y0 };
	copy(&matrix);
}

Pango::Matrix::Matrix(PangoMatrix *matrix)
: G::Boxed(PANGO_TYPE_MATRIX, matrix)
{
}

Pango::Matrix::Matrix(PangoMatrix *matrix, bool copy)
: G::Boxed(PANGO_TYPE_MATRIX, matrix, copy)
{
}

Pango::Matrix::Matrix(const Matrix& src)
: G::Boxed(PANGO_TYPE_MATRIX, src.g_boxed(), true)
{
}

Pango::Matrix::~Matrix()
{
}

Pango::Matrix& 
Pango::Matrix::operator=(const Matrix& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

void 
Pango::Matrix::set(double xx, double xy, double yx, double yy, double x0, double y0)
{
	pango_matrix()->xx = xx;
	pango_matrix()->xy = xy;
	pango_matrix()->yx = yx;
	pango_matrix()->yy = yy;
	pango_matrix()->x0 = x0;
	pango_matrix()->y0 = y0;
}

