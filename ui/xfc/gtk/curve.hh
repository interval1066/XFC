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
 
/// @file xfc/gtk/curve.hh
/// @brief A GtkCurve C++ wrapper interface.
///
/// Provides Curve, a widget that allows the user to edit a curve covering a range of values.

#ifndef XFC_GTK_CURVE_HH
#define XFC_GTK_CURVE_HH

#ifndef XFC_GTK_DRAWING_AREA_HH
#include <xfc/gtk/drawingarea.hh>
#endif

#ifndef __GTK_CURVE_H__
#include <gtk/gtkcurve.h>
#endif

namespace Xfc {

namespace Gtk {

/// @enum CurveType
/// The type of curve. Once set the curve will remain unchanged except when changing
/// from a free curve to a linear or spline curve.

enum CurveType
{
	CURVE_TYPE_LINEAR = GTK_CURVE_TYPE_LINEAR, ///< Linear interpolation.
	CURVE_TYPE_SPLINE = GTK_CURVE_TYPE_SPLINE, ///< Spline interpolation.
	CURVE_TYPE_FREE = GTK_CURVE_TYPE_FREE ///< Free form curve.
};

/// @class Curve curve.hh xfc/gtk/curve.hh
/// @brief A GtkCurve C++ wrapper class.
///
/// Curve is a widget that allows the user to edit a curve covering a range of values.
/// It is typically used to fine-tune color balances in graphics applications like the
/// Gimp. Curve has 3 modes of operation - spline, linear and free. In spline mode the
/// user places points on the curve which are automatically connected together into a
/// smooth curve. In linear mode the user places points on the curve which are connected
/// by straight lines. In free mode the user can draw the points of the curve freely,
/// and they are not connected at all.
///
/// NOTE this widget is considered too specialized/little-used for GTK+, and will in the
/// future be moved to some other package. If your application needs this widget, feel
/// free to use it, as the widget does work and is useful in some applications; it's just
/// not of general interest.

class Curve : public DrawingArea
{
	friend class G::Object;

	Curve(const Curve&);
	Curve& operator=(const Curve&);

protected:
/// @name Constructors
/// @{

	explicit Curve(GtkCurve *curve, bool owns_reference = false);
	///< Construct a new Curve from an existing GtkCurve.
	///< @param curve A pointer to a GtkCurve.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>curve</EM> can be a newly created GtkCurve or an existing
	///< GtkCurve. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> CurveTypeChangedSignalType;
	typedef G::SignalProxy<TypeInstance, CurveTypeChangedSignalType> CurveTypeChangedSignalProxy;
	static const CurveTypeChangedSignalType curve_type_changed_signal;
	///< Curve type changed signal (see signal_curve_type_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkCurve CObjectType;

/// @name Constructors
/// @{

	Curve();
	///< Construct a new Curve.

	virtual ~Curve();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkCurve* gtk_curve() const;
	///< Get a pointer to the GtkCurve structure.

	operator GtkCurve* () const;
	///< Conversion operator; safely converts a Curve to a GtkCurve pointer.

	void get_vector(int count, float data[]) const;
	///< Returns a vector of points representing the curve.
	///< @param count The number of points to calculate. 
	///< @param data The points.

/// @}
/// @name Methods
/// @{

	void reset();
	///< Resets the curve to a straight line from the minimum x and y values to the
	///< maximum x and y values (from the bottom-left to the top-right corners);
	///< the curve type is not changed.

	void set_gamma(float gamma);
	///< Recomputes the entire curve using the given gamma value. 
	///< @param gamma The gamma value.
	///< 
	///< A gamma value of 1 results in a straight line. Values greater than 1 result
	///< in a curve above the straight line. Values less than 1 result in a curve below
	///< the straight line. The curve type is changed to CURVE_TYPE_FREE. 
	
	void set_range(float min_x, float max_x, float min_y, float max_y);
	///< Sets the minimum and maximum x and y values of the curve. 
	///< @param min_x The minimum x value.
	///< @param max_x The maximum x value.
	///< @param min_y The minimum y value.
	///< @param max_y The maximum y value.
	///<
	///< The curve is also reset with a call to reset().

	void set_vector(int count, float data[]);
	///< Sets the vector of points on the curve; the curve type is set to CURVE_TYPE_FREE.
	///< @param count The number of points.
	///< @param data The points on the curve.

	void set_curve_type(CurveType type);
	///< Sets the type of the curve. 
	///< @param type The type of the curve.
	///<
	///< The curve will remain unchanged except when changing from a free curve to a linear
	///< or spline curve, in which case the curve will be changed as little as possible.

/// @}
/// @name Signal Proxies
/// @{

	const CurveTypeChangedSignalProxy signal_curve_type_changed();
	///< Connect to the curve_type_changed_signal; emitted when the curve type changes.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/curve.inl>

#endif // XFC_GTK_CURVE_HH

