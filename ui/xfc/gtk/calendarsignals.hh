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
 
/// @file xfc/gtk/calendarsignals.hh
/// @brief Gtk::Calendar virtual signal handlers.
///
/// Provides Gtk::CalendarSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Calendar objects.

#ifndef XFC_GTK_CALENDAR_SIGNALS_HH
#define XFC_GTK_CALENDAR_SIGNALS_HH

#ifndef XFC_GTK_WIDGET_SIGNALS_HH
#include <xfc/gtk/widgetsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class CalendarSignals calendarsignals.hh xfc/gtk/calendarsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Calendar.

class CalendarSignals : public WidgetSignals
{
protected:
/// @name Constructors
/// @{

	CalendarSignals(Calendar *calendar);
	///< Construct a new CalendarSignals object.
	///< @param calendar A Calendar object inheriting the CalendarSignals implementation.

	virtual ~CalendarSignals() = 0;
	///< Destructor
	
/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_month_changed();
	///< Called when the user clicks a button to change the selected month on a calendar.

	virtual void on_day_selected();
	///< Called when the user selects a day.

	virtual void on_day_selected_double_click();
	///< Called when the user double clicks a button to select a day.

	virtual void on_prev_month();
	///< Called when the user selects the previous month.

	virtual void on_next_month();
	///< Called when the user selects the next month.

	virtual void on_prev_year();
	///< Called when the user selects the previous year.

	virtual void on_next_year();
	///< Called when the user selects the next year.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_CALENDAR_SIGNALS_HH

