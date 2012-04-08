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
 
/// @file xfc/gtk/calendar.hh
/// @brief A GtkCalendar C++ wrapper interface.
///
/// Provides Calendar, a widget that displays a calendar and allows the user to select a date.
///
/// <B>See also:</B> the <A HREF="../../howto/html/calendar.html">Calendar</A> HOWTO and example.

#ifndef XFC_GTK_CALENDAR_HH
#define XFC_GTK_CALENDAR_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef __GTK_CALENDAR_H__
#include <gtk/gtkcalendar.h>
#endif

namespace Xfc {

namespace Gtk {

/// @enum CalendarDisplayOptions
/// The display options that specify how the calendar itself is displayed.

enum CalendarDisplayOptions
{
	CALENDAR_SHOW_HEADING = GTK_CALENDAR_SHOW_HEADING, 
	///< Specifies that the month and year should be displayed.
	CALENDAR_SHOW_DAY_NAMES = GTK_CALENDAR_SHOW_DAY_NAMES,
	///< Specifies that three letter day descriptions should be present.
	CALENDAR_NO_MONTH_CHANGE = GTK_CALENDAR_NO_MONTH_CHANGE,
	///< Prevents the user from switching months with the calendar.
	CALENDAR_SHOW_WEEK_NUMBERS = GTK_CALENDAR_SHOW_WEEK_NUMBERS,
	///< Displays each week numbers of the current year, down the left side of the calendar.
	CALENDAR_WEEK_START_MONDAY = GTK_CALENDAR_WEEK_START_MONDAY
	///< Starts the calendar week on Monday, instead of the default Sunday.
};

/// CalendarDisplayOptionsField holds one or more values from the Gtk::CalendarDisplayOptions enumeration OR'd together.

typedef unsigned int CalendarDisplayOptionsField;

/// @class Calendar calendar.hh xfc/gtk/calendar.hh
/// @brief A GtkCalendar C++ wrapper class.
///
/// Calendar is a widget that displays a calendar, one month at a time. The month and year
/// currently displayed can be altered with select_month(). The exact day can be selected
/// from the displayed month using select_day(). To place a visual marker on a particular
/// day, use mark_day() and to remove the marker, unmark_day(). Alternative, all marks can
/// be cleared with clear_marks(). The way in which the calendar itself is displayed can
/// be altered using display_options(). The selected date can be retrieved from a Calendar
/// using get_date(). If performing many 'mark' operations, the calendar can be frozen to
/// prevent flicker, with freeze(), and 'thawed' again using thaw().

class Calendar : public Widget
{
	friend class G::Object;

	Calendar(const Calendar&);
	Calendar& operator=(const Calendar&);
	
protected:
/// @name Constructors
/// @{

	explicit Calendar(GtkCalendar *calendar, bool owns_reference = false);
	///< Construct a new Calendar from an existing GtkCalendar.
	///< @param calendar A pointer to a GtkCalendar.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>calendar</EM> can be a newly created GtkCalendar or an existing
	///< GtkCalendar. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> MonthChangedSignalType;
	typedef G::SignalProxy<TypeInstance, MonthChangedSignalType> MonthChangedSignalProxy;
	static const MonthChangedSignalType month_changed_signal;
	///< Month changed signal (see signal_month_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> DaySelectedSignalType;
	typedef G::SignalProxy<TypeInstance, DaySelectedSignalType> DaySelectedSignalProxy;
	static const DaySelectedSignalType day_selected_signal;
	///< Day selected signal (see signal_day_selected()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> DaySelectedDoubleClickSignalType;
	typedef G::SignalProxy<TypeInstance, DaySelectedDoubleClickSignalType> DaySelectedDoubleClickSignalProxy;
	static const DaySelectedDoubleClickSignalType day_selected_double_click_signal;
	///< Day selected double click signal (see signal_day_selected_double_click()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> PrevMonthSignalType;
	typedef G::SignalProxy<TypeInstance, PrevMonthSignalType> PrevMonthSignalProxy;
	static const PrevMonthSignalType prev_month_signal;
	///< Prev month signal (see signal_prev_month()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> NextMonthSignalType;
	typedef G::SignalProxy<TypeInstance, NextMonthSignalType> NextMonthSignalProxy;
	static const NextMonthSignalType next_month_signal;
	///< Next month signal (see signal_next_month()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> PrevYearSignalType;
	typedef G::SignalProxy<TypeInstance, PrevYearSignalType> PrevYearSignalProxy;
	static const PrevYearSignalType prev_year_signal;
	///< Prev year signal (see signal_prev_year()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> NextYearSignalType;
	typedef G::SignalProxy<TypeInstance, NextYearSignalType> NextYearSignalProxy;
	static const NextYearSignalType next_year_signal;
	///< Next year signal (see signal_next_year()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkCalendar CObjectType;

/// @name Constructors
/// @{

	Calendar();
	///< Construct a new calendar, with the current date being selected.

	explicit Calendar(CalendarDisplayOptionsField flags);
	///< Construct a new calendar, with the specified display options and current date selected.
	///< @param flags One or more values from the Gtk::CalendarDisplayOptions enum OR'd together.
	///<
	///< This is a convenience constructor that lets you specifiy the display options.

	virtual ~Calendar();
	///< Destructor
	
/// @}
/// @name Accessors
/// @{

	GtkCalendar* gtk_calendar() const;
	///< Get a pointer to the GtkCalendar structure.

	operator GtkCalendar* () const;
	///< Conversion operator; safely converts a Calendar to a GtkCalendar pointer.

	int year() const;
	///< Returns the currently visible year.

	int month() const;
	///< Returns the currently visible month as a zero-based integer.

	int day() const;
	///< Returns the currently selected day as a one-based integer (allowed values are 1-31).

	int num_marked_dates() const;
	///< Returns the number of days that have a mark over them.

	std::vector<bool> marked_date() const;
	///< Returns a vector containing the day numbers that currently have a mark over them.

	void get_date(int *year, int *month, int *day) const;
	///< Obtains the selected date from a Calendar.
	///< @param year Location to store the year number.
	///< @param month Location to store the month number.
	///< @param day Location to store the day number.

	CalendarDisplayOptionsField get_display_options() const;
	///< Obtains the current display options of the calendar.
	///< @return The Gtk::CalendarDisplayOptions.

/// @}
/// @name Methods
/// @{

	bool select_month(int month, int year);
	///< Shifts the calendar to a different month. 
	///< @param month A month number between 0 and 11.
	///< @param year The year the month is in.
	///< @return Always <EM>true</EM>.
	
	void select_day(int day);
	///< Selects a day from the current month.
	///< @param day The day number between 1 and 31, or 0 to unselect the currently selected day.

	bool mark_day(int day);
	///< Places a visual marker on a particular day.
	///< @param day The day number to mark between 1 and 31.
	///< @return Always <EM>true</EM>.

	bool unmark_day(int day);
	///< Removes the visual marker from a particular day.
	///< @param day The day number to unmark between 1 and 31.
	///< @return <EM>true</EM>.
	
	void clear_marks();
	///< Remove all visual markers. 

	void set_display_options(CalendarDisplayOptionsField flags);
	///< Sets the display options (whether to display the year and month headings).
	///< @param flags One or more values from the Gtk::CalendarDisplayOptions enum OR'd together.

	void freeze();
	///< Locks the display of the calendar until it is thawed with thaw().

	void thaw();
	///< Defrosts a calendar; all the changes made since the last freeze() are displayed. 

/// @}
/// @name Signal Proxies
/// @{

	const MonthChangedSignalProxy signal_month_changed();
	///< Connect to the month_changed_signal; emitted when the user clicks a button to change the selected month.

	const DaySelectedSignalProxy signal_day_selected();
	///< Connect to the day_selected_signal; emitted when the user selects a day.

	const DaySelectedDoubleClickSignalProxy signal_day_selected_double_click();
	///< Connect to the day_selected_double_click_signal; emitted when the user selects a day with a double click.

	const PrevMonthSignalProxy signal_prev_month();
	///< Connect to the prev_month_signal; emitted when the user selects the previous month.

	const NextMonthSignalProxy signal_next_month();
	///< Connect to the next_month_signal; emitted when the user selects the next month.

	const PrevYearSignalProxy signal_prev_year();
	///< Connect to the prev_year_signal; emitted when the user selects the previous year.

	const NextYearSignalProxy signal_next_year();
	///< Connect to the next_year_signal; emitted when the user selects the next year.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/calendar.inl>

#endif // XFC_GTK_CALENDAR_HH

