/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  date.inl - G::Date inline functions
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

inline GDate*
Xfc::G::Date::g_date() const
{
	return date_;
}

inline Xfc::G::Date::operator GDate* () const
{
	return this ? date_ : 0;
}

inline bool
Xfc::G::Date::valid() const
{
	return g_date_valid(date_);
}

inline Xfc::G::DateWeekday
Xfc::G::Date::get_weekday() const
{
	return (DateWeekday)g_date_get_weekday(date_);
}

inline Xfc::G::DateDay
Xfc::G::Date::get_day() const
{
	return g_date_get_day(date_);
}

inline Xfc::G::DateMonth
Xfc::G::Date::get_month() const
{
	return (DateMonth)g_date_get_month(date_);
}

inline Xfc::G::DateYear
Xfc::G::Date::get_year() const
{
	return g_date_get_year(date_);
}

inline unsigned int
Xfc::G::Date::get_julian() const
{
	return g_date_get_julian(date_);
}

inline unsigned int
Xfc::G::Date::get_day_of_year() const
{
	return g_date_get_day_of_year(date_);
}

inline unsigned int
Xfc::G::Date::get_monday_week_of_year() const
{
	return g_date_get_monday_week_of_year(date_);
}

inline unsigned int
Xfc::G::Date::get_sunday_week_of_year() const
{
	return g_date_get_sunday_week_of_year(date_);
}

inline bool
Xfc::G::Date::is_first_of_month() const
{
	return g_date_is_first_of_month(date_);
}

inline bool
Xfc::G::Date::is_last_of_month() const
{
	return g_date_is_last_of_month(date_);
}

inline bool
Xfc::G::Date::valid_day(DateDay day)
{
	return g_date_valid_day(day);
}

inline bool
Xfc::G::Date::valid_month(DateMonth month)
{
	return g_date_valid_month((GDateMonth)month);
}

inline bool
Xfc::G::Date::valid_year(DateYear year)
{
	return g_date_valid_year(year);
}

inline bool
Xfc::G::Date::valid_weekday(DateWeekday weekday)
{
	return g_date_valid_weekday((GDateWeekday)weekday);
}

inline bool
Xfc::G::Date::valid_julian(unsigned int julian_date)
{
	return g_date_valid_julian(julian_date);
}

inline bool
Xfc::G::Date::valid_dmy(DateDay day, DateMonth month, DateYear year)
{
	return g_date_valid_dmy(day, (GDateMonth)month, year);
}

inline bool
Xfc::G::Date::is_leap_year(DateYear year)
{
	return g_date_is_leap_year(year);
}

inline unsigned char
Xfc::G::Date::get_days_in_month(DateMonth month, DateYear year)
{
	return g_date_get_days_in_month((GDateMonth)month, year);
}

inline unsigned char
Xfc::G::Date::get_monday_weeks_in_year(DateYear year)
{
	return g_date_get_monday_weeks_in_year(year);
}

inline unsigned char
Xfc::G::Date::get_sunday_weeks_in_year(DateYear year)
{
	return g_date_get_sunday_weeks_in_year(year);
}

inline void
Xfc::G::Date::clear()
{
	g_date_clear(date_, 1);
}

inline void
Xfc::G::Date::set_time(Time time)
{
	g_date_set_time(date_, time);
}

inline void
Xfc::G::Date::set_day(DateDay day)
{
	g_date_set_day(date_, day);
}

inline void
Xfc::G::Date::set_month(DateMonth month)
{
	g_date_set_month(date_, (GDateMonth)month);
}

inline void
Xfc::G::Date::set_year(DateYear year)
{
	g_date_set_year(date_, year);
}

inline void
Xfc::G::Date::set_dmy(DateDay day, DateMonth month, DateYear year)
{
	g_date_set_dmy(date_, day, (GDateMonth)month, year);
}

inline void
Xfc::G::Date::set_julian(unsigned int julian_date)
{
	g_date_set_julian(date_, julian_date);
}

inline void
Xfc::G::Date::add_days(unsigned int n_days)
{
	g_date_add_days(date_, n_days);
}

inline void
Xfc::G::Date::subtract_days(unsigned int n_days)
{
	g_date_subtract_days(date_, n_days);
}

inline void
Xfc::G::Date::add_months(unsigned int n_months)
{
	g_date_add_months(date_, n_months);
}

inline void
Xfc::G::Date::subtract_months(unsigned int n_months)
{
	g_date_subtract_months(date_, n_months);
}

inline void
Xfc::G::Date::add_years(unsigned int n_years)
{
	g_date_add_years(date_, n_years);
}

inline void
Xfc::G::Date::subtract_years(unsigned int n_years)
{
	g_date_subtract_years(date_, n_years);
}

inline void
Xfc::G::Date::to_struct_tm(struct tm *tm)
{
	g_date_to_struct_tm(date_, tm);
}

