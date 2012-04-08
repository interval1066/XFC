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
 
/// @file xfc/gtk/gammacurve.hh
/// @brief A GtkGammaCurve C++ wrapper interface.
///
/// Provides GammaCurve, a widget that is a variant of Curve specifically for editing
/// gamma curves, which are used in graphics applications such as the Gimp.

#ifndef XFC_GTK_GAMMA_CURVE_HH
#define XFC_GTK_GAMMA_CURVE_HH

#ifndef XFC_GTK_BOX_HH
#include <xfc/gtk/box.hh>
#endif

#ifndef __GTK_GAMMA_CURVE_H__
#include <gtk/gtkgamma.h>
#endif

namespace Xfc {

namespace Gtk {

class GammaCurveClass;

/// @class GammaCurve gammacurve.hh xfc/gtk/gammacurve.hh
/// @brief A GtkGammaCurve C++ wrapper class.
///
/// The GammaCurve widget is a variant of Curve specifically for editing gamma curves,
/// which are used in graphics applications such as the Gimp. The GammaCurve widget
/// shows a curve which the user can edit with the mouse just like a Curve widget.
/// On the right of the curve it also displays 5 buttons, 3 of which change between
/// the 3 curve modes (spline, linear and free), and the other 2 set the curve to a
/// particular gamma value, or reset it to a straight line.
///
/// NOTE this widget is considered too specialized/little-used for GTK+, and will in
/// the future be moved to some other package. If your application needs this widget,
/// feel free to use it, as the widget does work and is useful in some applications;
/// it's just not of general interest.

class GammaCurve : public VBox
{
	friend class G::Object;

	GammaCurve(const GammaCurve&);
	GammaCurve& operator=(const GammaCurve&);
	
protected:
/// @name Constructors
/// @{

	explicit GammaCurve(GtkGammaCurve *gamma_curve, bool owns_reference = false);
	///< Construct a new GammaCurve from an existing GtkGammaCurve.
	///< @param gamma_curve A pointer to a GtkGammaCurve.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>gamma_curve</EM> can be a newly created GtkGammaCurve or an existing
	///< GtkGammaCurve (see G::Object::Object).

/// @}

public:
	typedef GtkGammaCurve CObjectType;

/// @name Constructors
/// @{

	GammaCurve();
	///< Construct a new GammaCurve.

	virtual ~GammaCurve();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkGammaCurve* gtk_gamma_curve() const;
	///< Get a pointer to the GtkGammaCurve structure.

	operator GtkGammaCurve* () const;
	///< Conversion operator; safely converts a GammaCurve to a GtkGammaCurve pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/gammacurve.inl>

#endif // XFC_GTK_GAMMA_CURVE_HH

