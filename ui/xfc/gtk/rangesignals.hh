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

/// @file xfc/gtk/rangesignals.hh
/// @brief Gtk::Range virtual signal handlers.
///
/// Provides Gtk::RangeSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Range objects.

#ifndef XFC_GTK_RANGE_SIGNALS_HH
#define XFC_GTK_RANGE_SIGNALS_HH

#ifndef XFC_GTK_WIDGET_SIGNALS_HH
#include <xfc/gtk/widgetsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class RangeSignals rangesignals.hh xfc/gtk/rangesignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Range.

class RangeSignals : public WidgetSignals
{
protected:
/// @name Constructors
/// @{

	RangeSignals(Range *range);
	///< Constructs a new RangeSignals object.
	///< @param range A Range object inheriting the RangeSignals implementation.

	virtual ~RangeSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_value_changed();
	///< Called when the range value changes.

	virtual void on_adjust_bounds(double new_value);
	///< Called when the bounds of the range might need adjusting when a new range value is set.
	///< @param new_value The new range value.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_RANGE_SIGNALS_HH

