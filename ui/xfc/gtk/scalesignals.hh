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

/// @file xfc/gtk/scalesignals.hh
/// @brief Gtk::Scale virtual signal handlers.
///
/// Provides Gtk::ScaleSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Scale objects.

#ifndef XFC_GTK_SCALE_SIGNALS_HH
#define XFC_GTK_SCALE_SIGNALS_HH

#ifndef XFC_GTK_RANGE_SIGNALS_HH
#include <xfc/gtk/rangesignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ScaleSignals scalesignals.hh xfc/gtk/scalesignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Scale.

class ScaleSignals : public virtual RangeSignals
{
protected:
/// @name Constructors
/// @{

	ScaleSignals(Scale *scale);
	///< Constructs a new ScaleSignals object.
	///< @param scale A Scale object inheriting the ScaleSignals implementation.
	
	virtual ~ScaleSignals() = 0;

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual char* on_format_value(double value);
	///< Called to format the scale value before it gets displayed.
	///< @param value The scale value to format.
	///< @return An allocated string representing <EM>value</EM>.
	///<
	///< This signal handler allows you to change how the scale value is displayed.
	///< The return value must be an allocated string representing value. That string
	///< will then be used to display the scale's value. Here's an example signal handler
	///< which displays a value 1.0 as with "-->1.0<--".
	///<
	///< @code
	///< char*
	///< MyScale::on_format_value(double value)
	///< {
	///< 	return g_strdup_printf("-->%0.*g<--", scale->get_digits(value));
	///< }
	///< @endcode

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SCALE_SIGNALS_HH

