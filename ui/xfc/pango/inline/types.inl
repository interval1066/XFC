/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  types.inl - Pango types inline functions
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

/*  Pango::Rectangle
 */

inline PangoRectangle*
Xfc::Pango::Rectangle::pango_rectangle() const
{
	return const_cast<PangoRectangle*>(&rectangle_);
}

inline Xfc::Pango::Rectangle::operator PangoRectangle* () const
{
	return this ? pango_rectangle() : 0;
}

inline int
Xfc::Pango::Rectangle::x() const
{
	return rectangle_.x;
}

inline int
Xfc::Pango::Rectangle::y() const
{
	return rectangle_.y;
}

inline int
Xfc::Pango::Rectangle::width() const
{
	return rectangle_.width;
}

inline int
Xfc::Pango::Rectangle::height() const
{
	return rectangle_.height;
}

inline int
Xfc::Pango::Rectangle::ascent() const
{
	return PANGO_ASCENT(*pango_rectangle());
}

inline int
Xfc::Pango::Rectangle::descent() const
{
	return PANGO_DESCENT(*pango_rectangle());
}

inline int
Xfc::Pango::Rectangle::lbearing() const
{
	return PANGO_LBEARING(*pango_rectangle());
}

inline int
Xfc::Pango::Rectangle::rbearing() const
{
	return PANGO_RBEARING(*pango_rectangle());
}

/*  PangoMatrix
 */
 
inline PangoMatrix*
Xfc::Pango::Matrix::pango_matrix() const
{
	return reinterpret_cast<PangoMatrix*>(boxed_);
}

inline Xfc::Pango::Matrix::operator PangoMatrix* () const
{
	return this ? pango_matrix() : 0;
}

inline double 
Xfc::Pango::Matrix::xx() const
{
	return pango_matrix()->xx;
}

inline double 
Xfc::Pango::Matrix::xy() const
{
	return pango_matrix()->xy;
}

inline double 
Xfc::Pango::Matrix::yx() const
{
	return pango_matrix()->yx;
}

inline double 
Xfc::Pango::Matrix::yy() const
{
	return pango_matrix()->yy;
}

inline double 
Xfc::Pango::Matrix::x0() const
{
	return pango_matrix()->x0;
}

inline double 
Xfc::Pango::Matrix::y0() const
{
	return pango_matrix()->y0;
}

inline void
Xfc::Pango::Matrix::set_x0(double x0)
{
	pango_matrix()->x0 = x0;
}
	
inline void
Xfc::Pango::Matrix::set_y0(double y0)
{
	pango_matrix()->y0 = y0;
}
	
inline void
Xfc::Pango::Matrix::set_translation(double x0, double y0)
{
	set_x0(x0);
	set_y0(y0);
}

inline void 
Xfc::Pango::Matrix::translate(double tx, double ty)
{
	pango_matrix_translate(pango_matrix(), tx, ty);
}
	
inline void 
Xfc::Pango::Matrix::scale(double scale_x, double scale_y)
{
	pango_matrix_scale(pango_matrix(), scale_x, scale_y);
}
	
inline void 
Xfc::Pango::Matrix::rotate(double degrees)
{
	pango_matrix_rotate(pango_matrix(), degrees);
}

inline void 
Xfc::Pango::Matrix::concat(const Matrix& new_matrix)
{
	pango_matrix_concat(pango_matrix(), new_matrix.pango_matrix());
}

