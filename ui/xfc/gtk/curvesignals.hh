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
 
/// @file xfc/gtk/curvesignals.hh
/// @brief Gtk::Curve virtual signal handlers.
///
/// Provides Gtk::CurveSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Curve objects.

#ifndef XFC_GTK_CURVE_SIGNALS_HH
#define XFC_GTK_CURVE_SIGNALS_HH

#ifndef XFC_GTK_WIDGET_SIGNALS_HH
#include <xfc/gtk/widgetsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class CurveSignals curvesignals.hh xfc/gtk/curvesignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Curve.

class CurveSignals : public WidgetSignals
{
protected:
/// @name Constructors
/// @{

	CurveSignals(Curve *curve);
	///< Construct a new CurveSignals object.
	///< @param curve A Curve object inheriting the CurveSignals implementation.

	virtual ~CurveSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_curve_type_changed();
	///< Called when the curve type changes.
	///< The curve type can be changed explicitly with a call to set_curve_type(). It is also changed
	///< as a side-effect of calling reset() or set_gamma().

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_CURVE_SIGNALS_HH

