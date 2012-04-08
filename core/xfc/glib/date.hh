/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/glib/date.hh
/// @brief A GDate C++ wrapper interface.
///
/// Provides Date, an object that does calendar calculations.

#ifndef XFC_G_DATE_HH
#define XFC_G_DATE_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_DATE_H__
#include <glib/gdate.h>
#endif

namespace Xfc {

namespace G {

/// G::Time is a equivalent to time_t.

typedef GTime Time;

/// DateDay is an integer that represents a day of the month; between 1 and 31.
/// G::Date::BAD_DAY represents an invalid day of the month.

typedef GDateDay DateDay;

/// DateYear is an integer representing a year; DATE::BAD_YEAR is the invalid
/// value. The year must be 1 or higher; negative (BC) years are not allowed.
/// The year is represented with four digits.

typedef GDateYear DateYear;

/// @enum DateWeekday
/// Represents a day of the week.

enum DateWeekday
{
	DATE_BAD_WEEKDAY = G_DATE_BAD_WEEKDAY, ///< Invalid value.
	DATE_MONDAY = G_DATE_MONDAY, ///< Monday.
	DATE_TUESDAY = G_DATE_TUESDAY, ///< Tuesday.
	DATE_WEDNESDAY = G_DATE_WEDNESDAY, ///< Wednesday.
	DATE_THURSDAY = G_DATE_THURSDAY, ///< Thursday.
	DATE_FRIDAY = G_DATE_FRIDAY, ///< Friday.
	DATE_SATURDAY = G_DATE_SATURDAY, ///< Saturday.
	DATE_SUNDAY = G_DATE_SUNDAY ///< Sunday.
};

/// @enum DateMonth
/// Represents a month of the year.

enum DateMonth
{
	DATE_BAD_MONTH = G_DATE_BAD_MONTH, ///< Invalid value.
	DATE_JANUARY = G_DATE_JANUARY, ///< January.
	DATE_FEBRUARY = G_DATE_FEBRUARY, ///< February.
	DATE_MARCH = G_DATE_MARCH, ///< March.
	DATE_APRIL = G_DATE_APRIL, ///< April.
	DATE_MAY = G_DATE_MAY, ///< May.
	DATE_JUNE = G_DATE_JUNE, ///< June.
	DATE_JULY = G_DATE_JULY, ///< July.
	DATE_AUGUST = G_DATE_AUGUST, ///< August.
	DATE_SEPTEMBER = G_DATE_SEPTEMBER, ///< September.
	DATE_OCTOBER = G_DATE_OCTOBER, ///< October.
	DATE_NOVEMBER = G_DATE_NOVEMBER, ///< November.
	DATE_DECEMBER = G_DATE_DECEMBER ///< December.
};

/// @class Date date.hh xfc/glib/date.hh
/// @brief A GDate C++ wrapper interface.
///
/// The Date object represents a day between January 1, Year 1, and sometime
/// a few thousand years in the future (right now it will go to the year
/// 65535 or so, but set_parse() only parses up to the year 8000 or so - just
/// count on "a few thousand"). Date is meant to represent everyday dates, not
/// astronomical dates or historical dates or ISO timestamps or the like. It
/// extrapolates the current Gregorian calendar forward and backward in time;
/// there is no attempt to change the calendar to match time periods or
/// locations. Date does not store time information; it represents a day.
///
/// The Date implementation has several nice features; it is only a 64-bit
/// struct, so storing large numbers of dates is very efficient. It can keep
/// both a Julian and day-month-year representation of the date, since some
/// calculations are much easier with one representation or the other. A
/// Julian representation is simply a count of days since some fixed day in
/// the past; for Date the fixed day is January 1, 1 AD. ("Julian" dates in
/// the Date API aren't really Julian dates in the technical sense; technically,
/// Julian dates count from the start of the Julian period, Jan 1, 4713 BC).
///
/// Date is simple to use. First you need a "blank" date; you can dynamically
/// allocated date, or you can declare an automatic variable. Dates are cleared
/// on construction and therefore sane; it's safe to call set_dmy() and the
/// other mutator functions to initialize the value of a cleared date. However,
/// a cleared date is initially invalid, meaning that it doesn't represent a day
/// that exists. It is undefined to call any of the date calculation routines on
/// an invalid date. If you obtain a date from a user or other unpredictable
/// source, you should check its validity with the valid() predicate. valid() is
/// also used to check for errors with set_parse() and other functions that can
/// fail. Dates can be invalidated at any time and reused by calling clear().
///
/// It is very important to use the API to access the underlying GDate struct.
/// Often only the day-month-year or only the Julian representation is valid.
/// Sometimes neither is valid. Use the API.

class Date : public Xfc::Object
{
	GDate *date_;

public:
	static const unsigned int BAD_JULIAN = G_DATE_BAD_JULIAN;
	///< Represents an invalid Julian day number.

	static const unsigned char BAD_DAY = G_DATE_BAD_DAY;
	///< Represents an invalid day of the month.

	static const unsigned short BAD_YEAR = G_DATE_BAD_YEAR;
	///< Represents an invalid year.

/// @name Constructors
/// @{

	Date();
	///< Constructs a date and initializes it to a sane state. The new date will be cleared
	///< (as if you'd called clear()) but invalid (it won't represent an existing day).


	Date(DateDay day, DateMonth month, DateYear year);
	///< Construct a date and set the value for the date.
	///< @param day The day of the month.
	///< @param month The month of the year.
	///< @param year The year.
	///<
	///< Assuming the day-month-year triplet you pass in represents an existing day,
	///< the date will be valid.

	Date(unsigned int julian_day);
	///< Construct a date and set the value for the date.
	///< @param julian_day The days since January 1, Year 1.
	///<
	///< Assuming the Julian day number you pass in is valid (greater than 0, less
	///< than an unreasonably large number), the date will be valid.

	Date(const GDate& date);
	///< Construct a date from an existing GDate.
	///< @param date A valid GDate.


	Date(const Date& src);
	///< Copy constructor
	///< @param src Another Date.

	virtual ~Date();
	///< Destructor.

	Date& operator=(const Date& src);
	///< Assignment operator
	///< @param src Another Date.
	///< @return A reference to the Date.

/// @}
/// @name Accessors
/// @{

	GDate* g_date() const;
	///< Get a pointer to the GDate object.

	operator GDate* () const;
	///< Conversion operator; Safely converts a G::Date object into a GDate pointer.

	bool valid() const;
	///< Determines whether the date represents an existing day.
	///< @return <EM>true</EM> if the date is valid.
	///<
	///< The date must not contain garbage; it should have been initialized
	///< with clear() if it wasn't allocated by one of the constructor variants.

	DateWeekday get_weekday() const;
	///< Gets the day of the week for the date.
	///< @return The day of the week as a G::DateWeekday.
	///<
	///< The date must be valid.

	DateDay get_day() const;
	///< Gets the day of the month.
	///< @return The day of the month.
	///<
	///< The date must be valid.

	DateMonth get_month() const;
	///< Gets the month of the year.
	///< @return The month of the year as a G::DateMonth.
	///<
	///< The date must be valid.

	DateYear get_year() const;
	///< Gets the year of the date.
	///< @return The year in which the date falls.
	///<
	///< The date must be valid.

	unsigned int get_julian() const;
	///< Returns the Julian day or "serial number" of the date.
	///< @return The Julian day.
	///<
	///< The Julian day is simply the number of days since January 1, Year 1;
	///< that is, January 1, Year 1 is Julian day 1; January 2, Year 1 is Julian
	///< day 2, etc. The date must be valid.

	unsigned int get_day_of_year() const;
	///< Gets the day of the year, where January 1 is the first day of the year.
	///< @return The day of the year.
	///<
	///< The date must be valid.

	unsigned int get_monday_week_of_year() const;
	///< Gets the week of the year, where weeks are understood to start on Monday.
	///< @return The week of the year.
	///<
	///< If the date is before the first Monday of the year, return 0.
	///< The date must be valid.

	unsigned int get_sunday_week_of_year() const;
	///< Gets the week of the year during which this date falls, if weeks
	///< are understood to being on Sunday.
	///< @return The week number.
	///<
	///< The date must be valid. This method can return 0 if the day
	///< is before the first Sunday of the year.

	bool is_first_of_month() const;
	///< Determines whether the date is on the first of a month.
	///< @return <EM>true</EM> if the date is the first of a month.
	///<
	///< The date must be valid.

	bool is_last_of_month() const;
	///< Determines whether the date is the last day of the month.
	///< @return <EM>true</EM> if the date is the last day of the month.
	///<
	///< The date must be valid.

	int compare(const Date& other) const;
	///< A qsort()-style comparsion method for dates.
	///< @param other Another Date to comare.
	///< @return 0 for equal, less than zero if this is less than <EM>other</EM>,
	///< greater than zero if this date is greater than <EM>other</EM>.
	///<
	///< Both dates must be valid.

	bool operator==(const Date& other) const;
	///< Equality operator.
	///< @return <EM>true</EM> if this date and other are equal.

	bool operator!=(const Date& other) const;
	///< Inequality operator.
	///< @return <EM>true</EM> if this date and other are not equal.

	bool operator<(const Date& other) const;
	///< Less-than operator.
	///< @return <EM>true</EM> if this date is less than other.

	bool operator<=(const Date& other) const;
	///< Less-than-or-equal-to operator.
	///< @return <EM>true</EM> if this date is less than or equal to other.

	bool operator>(const Date& other) const;
	///< Greater-than operator.
	///< @return <EM>true</EM> if this date is greater than other.

	bool operator>=(const Date& other) const;
	///< Greater-than-or-equal-to operator.
	///< @return <EM>true</EM> if this date is greater than or equal to other.

/// @}
/// @name Accessors
/// @{

	static bool valid_day(DateDay day);
	///< Determines whether the day of the month is valid.
	///< @param day The day.
	///< @return <EM>true</EM> if the day is valid.
	///<
	///< A day is valid if it's between 1 and 31 inclusive.

	static bool valid_month(DateMonth month);
	///< Determines whether the month value is valid.
	///< @param month The month.
	///< @return <EM>true</EM> if the month is valid.
	///<
	///< The 12 G::DateMonth enumeration values are the only valid months.

	static bool valid_year(DateYear year);
	///< Determines whether the year is valid.
	///< @param year The year.
	///< @return <EM>true</EM> if the year is valid.
	///<
	///< Any year greater than 0 is valid, though there is a 16-bit limit
	///< to what Date will understand.

	static bool valid_weekday(DateWeekday weekday);
	///< Determines whether the weekday is valid.
	///< @param weekday The weekday.
	///< @return <EM>true</EM> if the weekday is valid.
	///<
	///< The 7 G::DateWeekday enumeration values are the only valid weekdays.

	static bool valid_julian(unsigned int julian_date);
	///< Determines whether the Julian day is valid.
	///< @param julian_date The Julian day to check.
	///< @return <EM>true</EM> if the Julian day is valid.
	///<
	///< Anything greater than zero is basically a valid Julian, though
	///< there is a 32-bit limit.

	static bool valid_dmy(DateDay day, DateMonth month, DateYear year);
	///< Determines whether the day-month-year triplet forms a valid, existing
	///< day in the range of days Date understands (Year 1 or later, no more
	///< than a few thousand years in the future).
	///< @param day The day.
	///< @param month The month.
	///< @param year The year.
	///< @return <EM>true</EM> if the date is a valid one.

	static bool is_leap_year(DateYear year);
	///< Determines whether the year is a leap year.
	///< @param year The year to check.
	///< @return <EM>true</EM> if the year is a leap year.

	static unsigned char get_days_in_month(DateMonth month, DateYear year);
	///< Gets the number of days in a month, taking leap years into account.
	///< @param month The month.
	///< @param year The year.
	///< @return The number of days in <EM>month</EM> during the <EM>year</EM>.

	static unsigned char get_monday_weeks_in_year(DateYear year);
	///< Gets the number of weeks in the year, where weeks are taken to start on Monday.
	///< @param year A year to count weeks in.
	///< @return The number of weeks (or Mondays) in the year.
	///<
	///< The return value Will be 52 or 53. The date must be valid. (Years always have
	///< 52 7-day periods, plus 1 or 2 extra days depending on whether it's a leap year.
	///< This method is basically telling you how many Mondays are in the year, that is,
	///< there are 53 Mondays if one of the extra days happens to be a Monday.)

	static unsigned char get_sunday_weeks_in_year(DateYear year);
	///< Gets the number of weeks in the year, where weeks are taken to start on Sunday.
	///< @param year A year to count weeks in.
	///< @return The number of weeks (or Sundays) in the year.
	///<
	///< The return value will be 52 or 53. The date must be valid. (Years always have
	///< 52 7-day periods, plus 1 or 2 extra days depending on whether it's a leap year.
	///< This method is basically telling you how many Sundays are in the year, that is,
	///< there are 53 Sundays if one of the extra days happens to be a Sunday.)

/// @}
/// @name Methods
/// @{

	void clear();
	///< Clears a date. Cleared dates will not represent an existing date,
	///< but will not contain garbage. Validity can be tested with valid().

	void set_parse(const String& str);
	///< Parses the user-inputted string <EM>str</EM>, and try to figure out
	///< what date it represents, taking the current locale into account.
	///< @param str The string to parse.
	///<
	///< If the string is successfully parsed, the date will be valid after
	///< the call. Otherwise, it will be invalid. You should check using valid()
	///< to see whether the parsing succeeded. This methods not appropriate for
	///< file formats and the like; it isn't very precise, and its exact behavior
	///< varies with the locale. It's intended to be a heuristic routine that
	///< guesses what the user means by a given string (and it does work pretty
	///< well in that capacity).

	void set_time(Time time);
	///< Sets the value of a date from a G::Time (time_t) value.
	///< @param time The Time value to set.
	///<
	///< <B>Example:</B>To set the value of a date to the current day, you could write:
	///< @code
	///< date->set_time(Time(0));
	///< @endcode

	void set_day(DateDay day);
	///< Sets the day of the month for the date.
	///< @param day The day to set.
	///<
	///< If the resulting day-month-year triplet is invalid, the date will be invalid.

	void set_month(DateMonth month);
	///< Sets the month for the date.
	///< @param month The month to set.
	///<
	///< If the resulting day-month-year triplet is invalid, the date will be invalid.

	void set_year(DateYear year);
	///< Sets the year for the date.
	///< @param year The year to set.
	///<
	///< If the resulting day-month-year triplet is invalid, the date will be invalid.

	void set_dmy(DateDay day, DateMonth month, DateYear year);
	///< Sets the value of the date from a day, month, and year.
	///< @param day The day to set.
	///< @param month The month to set.
	///< @param year The year to set.
	///<
	///< The day-month-year triplet must be valid; if you aren't sure it is,
	///< call valid_dmy() to check before you set it.

	void set_julian(unsigned int julian_date);
	///< Sets the value of the date from a Julian day number.
	///< @param julian_date The Julian day number (days since January 1, Year 1).

	void add_days(unsigned int n_days);
	///< Increments the date some number of days.
	///< @param n_days The number of days to move the date forward.
	///<
	///< To move forward by weeks, add weeks*7 days. The date must be valid.

	void subtract_days(unsigned int n_days);
	///< Moves the date some number of days into the past.
	///< @param n_days The number of days to move.
	///<
	///< To move by weeks, just move by weeks*7 days. The date must be valid.

	void add_months(unsigned int n_months);
	///< Increments the date by some number of months.
	///< @param n_months The number of months to move forward.
	///<
	///< If the day of the month is greater than 28, this routine may change
	///< the day of the month (because the destination month may not have the
	///< current day in it). The date must be valid.

	void subtract_months(unsigned int n_months);
	///< Moves the date some number of months into the past.
	///< @param n_months The number of months to move.
	///<
	///< If the current day of the month doesn't exist in the destination month,
	///< the day of the month may change. The date must be valid.

	void add_years(unsigned int n_years);
	///< Increments the date by some number of years.
	///< @param n_years The number of years to move forward.
	///<
	///< If the date is February 29, and the destination year is not a leap year,
	///< the date will be changed to February 28. The date must be valid.

	void subtract_years(unsigned int n_years);
	///< Moves a date some number of years into the past.
	///< @param n_years The number of years to move.
	///<
	///< If the current day doesn't exist in the destination year (that is, it's
	///< February 29 and you move to a non-leap-year) then the day is changed to
	///< February 28. The date must be valid.

	int days_between(const Date& date1, const Date& date2);
	///< Computes the number of days between two dates.
	///< @param date1 The first date.
	///< @param date2 The second date.
	///< @return The number of days between date1 and date2.
	///<
	///< If date2 is prior to date1, the returned value is negative. Both dates must be valid.

	void to_struct_tm(struct tm *tm);
	///< Fills in the date-related bits of a <EM>struct tm</EM> using the date value.
	///< @param tm The struct tm to fill.
	///<
	///< Initializes the non-date parts with something sane but meaningless.

	void clamp(const Date *min_date, const Date *max_date);
	///< If the date is prior to min_date, sets date equal to min_date; If date
	///< falls after max_date, sets date equal to max_date.
	///< @param min_date The minimum accepted value for the date, or null.
	///< @param max_date The maximum accepted value for the date, or null.
	///<
	///< Either min_date and max_date may be null. All non-null dates must be valid.

	void order(Date& other);
	///< Checks if the date is less than or equal to <EM>other</EM>, and swap the values
	///< if this is not the case.
	///< @param other Another date.

	String format(const String& date_format);
	///< Generates a printed representation of the date, in a locale-specific way.
	///< @param date_format The date-related only format string.
	///< @return The formatted string representation of the date.
	///<
	///< Works just like the standard C strftime() function, but only accepts date-related
	///< formats; time-related formats give undefined results. The date must be valid.

/// @}
};

#include <xfc/glib/inline/date.inl>

} // namespace G

} // namespace Xfc

#endif // XFC_G_DATE_HH

