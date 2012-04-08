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
 
/// @file xfc/pango/types.hh
/// @brief Pango types C++ wrapper interface.
///
/// Provides common typedefs, enumerations and utility classes.

#ifndef XFC_PANGO_TYPES_HH
#define XFC_PANGO_TYPES_HH

#ifndef XFC_G_BOXED_HH
#include <xfc/glib/boxed.hh>
#endif

#ifndef __PANGO_TYPES_H__
#include <pango/pango-types.h>
#endif

namespace Xfc {

namespace G {
class Unichar;
}

namespace Pango {
	
/// Glyph is a convenient typedef for PangoGlyph. Glyph structure represents a single glyph
/// in the output form of a glyph string.

typedef PangoGlyph Glyph;

/// @enum Pango::Direction
/// The Direction type represents the direction of writing for unicode bidirectional text.
///
/// <B>Note:</B> Not every value in this enumeration makes sense for every usage of Pango::Direction.

enum Direction
{
	DIRECTION_LTR = PANGO_DIRECTION_LTR,
	///< The text is written left-to-right.

	DIRECTION_RTL = PANGO_DIRECTION_RTL,
	///< The text is written right-to-left.

	DIRECTION_TTB_LTR = PANGO_DIRECTION_TTB_LTR,
	///< The text is written vertically top-to-bottom, with the rows ordered from left to right.
	
	DIRECTION_TTB_RTL = PANGO_DIRECTION_TTB_RTL,
	///< The text is written vertically top-to-bottom, with the rows ordered from right to left.

	DIRECTION_WEAK_LTR = PANGO_DIRECTION_WEAK_LTR,
	///< A weak left-to-right direction.

	DIRECTION_WEAK_RTL = PANGO_DIRECTION_WEAK_RTL,
	///< A weak right-to-left direction .

	DIRECTION_NEUTRAL = PANGO_DIRECTION_NEUTRAL
	///< No direction specified.
};

/// @name Direction Methods
/// @{

Direction unichar_direction(G::Unichar ch);
///< Determines the direction of a character; either Pango::DIRECTION_LTR, 
///< Pango::DIRECTION_LTR, or Pango::DIRECTION_NEUTRAL. 
///< @param ch The character to examine. 
///< @return The direction of a the character, as used in the Unicode bidirectional algorithm.

Direction find_base_dir(const char *text, int length = -1);
///< Searches a string for the first character that has a strong direction, 
///< according to the Unicode bidirectional algorithm.
///< @param text The text to process. 
///< @param length The length of text in bytes, or -1 if text is null-terminated. 
///< @return The direction corresponding to the first strong character. 
///<
///< If no such character is found, then Pango::DIRECTION_NEUTRAL is returned.

/// @}

/// @class Rectangle types.hh xfc/pango/types.hh
/// @brief A PangoRectangle C++ wrapper class.
///
/// Rectangle represents a rectangle. It is frequently used to represent the logical or ink extents
/// of a single glyph or section of text (see, for instance, Pango::Font::get_glyph_extents()).

class Rectangle
{
	PangoRectangle rectangle_;

public:
/// @name Constructors
/// @{

	Rectangle();
	///< Construct a with its x, y, width and height set to 0;

	Rectangle(int x, int y, int width, int height);
	///< Construct a new rectangle.
	///< @param x The X coordinate of the rectangle.
	///< @param y The Y coordinate of the rectangle.
	///< @param width The width of the rectangle.
	///< @param height The height of the rectangle.
	
	Rectangle(const PangoRectangle& rectangle);
	///< Construct a new rectangle from an existing PangoRectangle.
	///< @param rectangle A PangoRectangle.

/// @}
/// @name Accessors
/// @{

	PangoRectangle* pango_rectangle() const;
	///< Get a pointer to the PangoRectangle structure.

	operator PangoRectangle* () const;
	///< Conversion operator; safely converts a Rectangle to a PangoRectangle pointer.

	int x() const;
	///< Returns the X coordinate of the top-left corner of the rectangle.

	int y() const;
	///< Returns the Y coordinate of the top-left corner of the rectangle.

	int width() const;
	///< Returns the width of the rectangle.
	
	int height() const;
	///< Returns the height of the rectangle.
	
	int ascent() const;
	///< Extracts the ascent from a Pango::Rectangle representing glyph extents.
	///< The ascent is the distance from the baseline to the highest point of 
	///< the character. This is positive if the glyph ascends above the baseline.

	int descent() const;
	///< Extracts the descent from a Pango::Rectangle representing glyph extents.
	///< The descent is the distance from the baseline to the lowest point of 
	///< the character. This is positive if the glyph descends below the baseline. 

	int lbearing() const;
	///< Extracts the left bearing from a Pango::Rectangle representing glyph extents.
	///< The left bearing is the distance from the horizontal origin to the farthest
	///< left point of the character. This is positive for characters drawn completely
	///< to the right of the glyph origin.

	int rbearing() const;
	///< Extracts the right bearing from a Pango::Rectangle representing glyph extents.
	///< The right bearing is the distance from the horizontal origin to the farthest
	///< right point of the character. This is positive except for characters drawn 
	///< completely to the left of the horizontal origin.

/// @}
/// @name Methods
/// @{

	void set(int x, int y, int width, int height);
	///< Sets the position and size of the rectangle.
	///< @param x The new X coordinate of the rectangle.
	///< @param y The new Y coordinate of the rectangle.
	///< @param width The new width of the rectangle.
	///< @param height The new height of the rectangle.
	
/// @}
};

/// @class Matrix types.hh xfc/pango/types.hh
/// @brief A PangoMatrix C++ wrapper class.
///
/// Matrix specifies a transformation between user-space coordinates and device coordinates.
/// The transformation is given by:
///
/// @code
/// x_device = x_user * matrix->xx() + y_user * matrix->xy() + matrix->x0();
/// y_device = x_user * matrix->yx() + y_user * matrix->yy() + matrix->y0();
/// @endcode

class Matrix : public G::Boxed
{
public:
/// @name Constructors
/// @{

	Matrix();
	///< Creates a new Matrix initialized to the identity transform.
	///<
	///< @code
	///< Pango::Matrix matrix;
	///< matrix.rotate(45.);
	///< @endcode
	
	Matrix(double xx, double xy, double yx, double yy, double x0 = 0.0, double y0 = 0.0);
	///< Creates a new Matrix initialized with the specified values .
	///< @param xx The first component of the transformation matrix.
	///< @param xy The second component of the transformation matrix.
	///< @param yx The third component of the transformation matrix.
	///< @param yy The fourth component of the transformation matrix.
	///< @param x0 The x translation.
	///< @param y0 The y translation.
	
	explicit Matrix(PangoMatrix *matrix);
	///< Construct a new matrix from an existing PangoMatrix.
	///< @param matrix A pointer to a PangoMatrix.
	///<
	///< The <EM>matrix</EM> can be a newly created PangoMatrix or an existing
	///< PangoMatrix. The Matrix object created is a temporary object. It doesn't
	///< take over the ownership of PangoMatrix and PangoMatrix is not freed by the
	///< destructor. Matrix is created with a reference count of 1 that the caller owns.

	Matrix(PangoMatrix *matrix, bool copy);
	///< Construct a new matrix from an existing PangoMatrix.
	///< @param matrix A pointer to a PangoMatrix.
	///< @param copy Whether the Matrix object should make a copy of PangoMatrix or not.
	///<
	///< The <EM>matrix</EM> can be a newly created PangoMatrix or an existing PangoMatrix.
	///< If <EM>copy</EM> is true Matrix will make a copy of PangoMatrix. If <EM>copy</EM>
	///< is false Matrix wont make a copy but instead takes over the ownership of PangoMatrix.
	///< Either way, the destructor will free PangoMatrix when the Matrix object is destroyed.
	///< This constructor is used by G::Boxed::wrap() to wrap PangoMatrix objects in a
	///< C++ wrapper. Matrix is created with a reference count of 1 that the caller owns.

	Matrix(const Matrix& src);
	///< Copy constructor.
	///< @param src The source matrix.

	~Matrix();
	///< Destructor.

	Matrix& operator=(const Matrix& src);
	///< Assignment operator.
	///< @param src The source matrix.

/// @}
/// @name Accessors
/// @{

	PangoMatrix* pango_matrix() const;
	///< Get a pointer to the PangoMatrix structure.

	operator PangoMatrix* () const;
	///< Conversion operator; safely converts a Matrix to a PangoMatrix pointer.

	double xx() const;
	///< Gets the first component of the transformation matrix.
	///< @return The first component.
	
	double xy() const;
	///< Gets the second component of the transformation matrix.
	///< @return The second component.
	
	double yx() const;
	///< Gets the third component of the transformation matrix.
	///< @return The third component.
	
	double yy() const;
	///< Gets the fourth component of the transformation matrix.
	///< @return The fourth component.
	
	double x0() const;
	///< Gets the x translation.
	///< @return The x translation.
	
	double y0() const;
	///< Gets the y translation.
	///< @return The y translation.

/// @}
/// @name Methods
/// @{

	void set(double xx, double xy, double yx, double yy, double x0 = 0.0, double y0 = 0.0);
	///< Initializes the matrix with the specified values.
	///< @param xx The first component of the transformation matrix.
	///< @param xy The second component of the transformation matrix.
	///< @param yx The third component of the transformation matrix.
	///< @param yy The fourth component of the transformation matrix.
	///< @param x0 The x translation.
	///< @param y0 The y translation.
	
	void set_x0(double x0);
	///< Sets the x translation.
	///< @param x0 The x translation.
	
	void set_y0(double y0);
	///< Sets the y translation.
	///< @param y0 The y translation.
	
	void set_translation(double x0, double y0);
	///< Sets the x and y translation.
	///< @param x0 The x translation.
	///< @param y0 The y translation.

	void translate(double tx, double ty);
	///< Changes the transformation represented by matrix to be the transformation given
	///< by first translating by (tx, ty) then applying the original transformation.
	///< @param tx The amount to translate in the X direction. 
	///< @param ty The amount to translate in the Y direction.
	
	void scale(double scale_x, double scale_y);
	///< Changes the transformation represented by matrix to be the transformation given by first scaling
	///< by sx in the X direction and sy in the Y direction then applying the original transformation.
	///< @param scale_x The amount to scale by in X direction. 
	///< @param scale_y The amount to scale by in Y direction.
	
	void rotate(double degrees);
	///< Changes the transformation represented by matrix to be the transformation given by first
	///< rotating by <EM>degrees</EM> degrees counter-clokwise then applying the original transformation.
	///< @param degrees The degrees to rotate counter-clockwise.

	void concat(const Matrix& new_matrix);
	///< Changes the transformation represented by matrix to be the transformation given by first
	///< applying transformation given by new_matrix then applying the original transformation.
	///< @param new_matrix A Pango::Matrix.

/// @}
};

} // namespace Pango

} // namespace Xfc

#include <xfc/pango/inline/types.inl>

#endif // XFC_PANGO_TYPES_HH

