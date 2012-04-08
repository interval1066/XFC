/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  calendar.inl - Gtk::Calendar inline functions
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

inline GtkCalendar*
Xfc::Gtk::Calendar::gtk_calendar() const
{
	return reinterpret_cast<GtkCalendar*>(instance_);
}

inline Xfc::Gtk::Calendar::operator GtkCalendar* () const
{
	return this ? gtk_calendar() : 0;
}

inline int
Xfc::Gtk::Calendar::year() const
{
	return gtk_calendar()->year;
}

inline int
Xfc::Gtk::Calendar::month() const
{
	return gtk_calendar()->month;
}

inline int
Xfc::Gtk::Calendar::day() const
{
	return gtk_calendar()->selected_day;
}

inline int
Xfc::Gtk::Calendar::num_marked_dates() const
{
	return gtk_calendar()->num_marked_dates;
}

inline void
Xfc::Gtk::Calendar::get_date(int *year, int *month, int *day) const
{
	gtk_calendar_get_date(gtk_calendar(), (unsigned int*)year, (unsigned int*)month, (unsigned int*)day);
}

inline Xfc::Gtk::CalendarDisplayOptionsField
Xfc::Gtk::Calendar::get_display_options() const
{
	return (CalendarDisplayOptionsField)gtk_calendar_get_display_options(gtk_calendar());
}

inline bool
Xfc::Gtk::Calendar::select_month(int month, int year)
{
	return gtk_calendar_select_month(gtk_calendar(), month, year);
}

inline void
Xfc::Gtk::Calendar::select_day(int day)
{
	gtk_calendar_select_day(gtk_calendar(), day);
}

inline bool
Xfc::Gtk::Calendar::mark_day(int day)
{
	return gtk_calendar_mark_day(gtk_calendar(), day);
}

inline bool
Xfc::Gtk::Calendar::unmark_day(int day)
{
	return gtk_calendar_unmark_day(gtk_calendar(), day);
}

inline void
Xfc::Gtk::Calendar::clear_marks()
{
	gtk_calendar_clear_marks(gtk_calendar());
}

inline void
Xfc::Gtk::Calendar::set_display_options(CalendarDisplayOptionsField flags)
{
	gtk_calendar_display_options(gtk_calendar(), (GtkCalendarDisplayOptions)flags);
}

inline void
Xfc::Gtk::Calendar::freeze()
{
	gtk_calendar_freeze(gtk_calendar());
}

inline void
Xfc::Gtk::Calendar::thaw()
{
	gtk_calendar_thaw(gtk_calendar());
}

inline const Xfc::Gtk::Calendar::MonthChangedSignalProxy
Xfc::Gtk::Calendar::signal_month_changed()
{
	return MonthChangedSignalProxy(this, &month_changed_signal);
}

inline const Xfc::Gtk::Calendar::DaySelectedSignalProxy
Xfc::Gtk::Calendar::signal_day_selected()
{
	return DaySelectedSignalProxy(this, &day_selected_signal);
}

inline const Xfc::Gtk::Calendar::DaySelectedDoubleClickSignalProxy
Xfc::Gtk::Calendar::signal_day_selected_double_click()
{
	return DaySelectedDoubleClickSignalProxy(this, &day_selected_double_click_signal);
}

inline const Xfc::Gtk::Calendar::PrevMonthSignalProxy
Xfc::Gtk::Calendar::signal_prev_month()
{
	return PrevMonthSignalProxy(this, &prev_month_signal);
}

inline const Xfc::Gtk::Calendar::NextMonthSignalProxy
Xfc::Gtk::Calendar::signal_next_month()
{
	return NextMonthSignalProxy(this, &next_month_signal);
}

inline const Xfc::Gtk::Calendar::PrevYearSignalProxy
Xfc::Gtk::Calendar::signal_prev_year()
{
	return PrevYearSignalProxy(this, &prev_year_signal);
}

inline const Xfc::Gtk::Calendar::NextYearSignalProxy
Xfc::Gtk::Calendar::signal_next_year()
{
	return NextYearSignalProxy(this, &next_year_signal);
}

