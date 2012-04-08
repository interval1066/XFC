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
 
/// @file xfc/glib/timeval.hh
/// @brief GTimeVal C++ interface.
///
/// Provides TimeVal, an object that represents a precise time, with seconds and microseconds.
/// Same as the struct timeval returned by the gettimeofday() UNIX call.

#ifndef XFC_G_TIME_VAL_HH
#define XFC_G_TIME_VAL_HH

#ifndef XFC_OBJECT_HH
#include <xfc/object.hh>
#endif

#ifndef __G_TYPES_H__
#include <glib/gtypes.h>
#endif

namespace Xfc {

namespace G {

class TimeVal;

/// @name Time Methods
/// @{

TimeVal get_current_time();
///< Equivalent to the UNIX gettimeofday() function, but portable.
///< @return A TimeVal object that stores the current time.

void usleep(unsigned long microseconds);
///< Pauses execution of the current thread for the given number of microseconds.
///< @param microseconds The number of microseconds to pause.
///<
///< There are 1 million microseconds per second (represented by the G_USEC_PER_SEC macro).
///< This method may have limited precision, depending on hardware and operating system; don't
///< rely on the exact length of the sleep.

/// @}

/// @class TimeVal timer.hh xfc/glib/timeval.hh
/// @brief A GTimeVal C++ wrapper interface.
///
/// TimeVal represents a time expressed in seconds and microseconds.
/// TimeVal uses default copy, assignment and destruction.

class TimeVal
{
	GTimeVal timeval_;

public:
/// @name Constructors
/// @{

	TimeVal();
	///< Construct an empty time value.

	TimeVal(long seconds, long microseconds);
	///< Construct a time value using the specified seconds and microseconds.
	///< @param seconds The number of seconds.
	///< @param microseconds The number of microseconds.
	///<
	///< Both <EM>seconds</EM> and <EM>microseconds</EM> can be positive or negative.
	///< If <EM>microseconds</EM> is greater than G_USEC_PER_SEC this method will calculate
	///< the number of seconds in <EM>microseconds</EM> and adjust <EM>seconds</EM>.

	TimeVal(const double& timeval);
	///< Construct a time value from a double representation.
	///< @param timeval The double time value.
	///<
	///< In <EM>timeval</EM> the whole digits represents seconds and the
	///< fractional part represents microseconds. As an example, such a double
	///< value is returned by G::Timer::elapsed().

	TimeVal(const GTimeVal& timeval);
	///< Construct a time value from a existing GTimeVal.
	///< @param timeval A reference to a GTimeVal.

/// @}
/// @name Accessors
/// @{

	GTimeVal* g_time_val() const;
	///< Get a pointer to the GTimeVal structure.

	operator GTimeVal* () const;
	///< Conversion operator; Safely converts a G::TimeVal object into a GTimeVal pointer.

	long seconds() const;
	///< Returns the number of seconds in the time value.

	long microseconds() const;
	///< Returns the number of microseconds in the time value.

	double get_double() const;
	///< Converts the time value into a double floating-point value.
	///< @return The time as a double floating-point.
	///<
	///< In the return value the whole digits represent the seconds
	///< and the the fractional part represents the microseconds.

	bool equal(const TimeVal& other) const;
	///< Tests this time value and <EM>other</EM> for equality.
	///< @param other Another TimeVal object.
	///< @return <EM>true</EM> if this time value is equal to <EM>other</EM>.

	bool operator==(const TimeVal& other);
	///< Equality operator.
	///< @param other Another TimeVal object.
	///< @returns <EM>true</EM> if this time value is equal to <EM>other</EM>.

	bool operator!=(const TimeVal& other);
	///< Inequality operator.
	///< @param other Another TimeVal object.
	///< @returns <EM>true</EM> if this time value is not equal to <EM>other</EM>.

	bool operator<(const TimeVal& other);
	///< Less-than operator.
	///< @param other Another TimeVal object.
	///< @returns <EM>true</EM> if this time value is less than <EM>other</EM>.

	bool operator<=(const TimeVal& other);
	///< Less-than-or-equal-to operator.
	///< @param other Another TimeVal object.
	///< @returns <EM>true</EM> if this time value is less than or equal to <EM>other</EM>.

	bool operator>(const TimeVal& other);
	///< Greater-than operator.
	///< @param other Another TimeVal object.
	///< @returns <EM>true</EM> if this time value is greater than <EM>other</EM>.

	bool operator>=(const TimeVal& other);
	///< Greater-than-or-equal-to operator.
	///< @param other Another TimeVal object.
	///< @returns <EM>true</EM> if this time value is greater than or equal to <EM>other</EM>.

/// @}
/// @name Methods
/// @{

	void add(long microseconds);
	///< Adds the specified number of microseconds to the time value.
	///< @param microseconds The number of microseconds to add, either positive or negative.

	void add(long seconds, long microseconds);
	///< Adds the specified number of seconds and microseconds to the time value.
	///< @param seconds The number of seconds to add.
	///< @param microseconds The number of microseconds to add.
	///<
	///< Both <EM>seconds</EM> and <EM>microseconds</EM> can be positive or negative.
	///< If <EM>microseconds</EM> is greater than G_USEC_PER_SEC this method will calculate
	///< the number of seconds in <EM>microseconds</EM> and adjust <EM>seconds</EM>.

	void add(const TimeVal& other);
	///< Adds <EM>other</EM> to this time value.
	///< @param other Another TimeVal object.

	void subtract(const TimeVal& other);
	///< Subtracts <EM>other</EM> from this time value.
	///< @param other Another TimeVal object.

	long difference(const TimeVal& other);
	///< Gets the time difference between this time value and <EM>other</EM>.
	///< @param other Another TimeVal object.
	///< @return The time difference in microseconds.

	TimeVal& operator+=(long microseconds);
	///< Adds <EM>microseconds</EM> to the time value.
	///< @param microseconds The number of microseconds to add.
	///< @return A reference to the time value.

	TimeVal& operator+=(const TimeVal& other);
	///< Adds <EM>other</EM> to the time value.
	///< @param other Another TimeVal object.
	///< @return A reference to the time value.

	TimeVal& operator-=(long microseconds);
	///< Subtracts <EM>microseconds</EM> from the time value.
	///< @param microseconds The number of microseconds to subtract.
	///< @return A reference to the time value.

	TimeVal& operator-=(const TimeVal& other);
	///< Subtract <EM>other</EM> from the time value.
	///< @param other Another TimeVal object.
	///< @return A reference to the time value.

/// @}
};

/// @name TimeVal addition operators
/// @{

inline const TimeVal
operator+(const TimeVal& lhs, long microseconds)
{
	return TimeVal(lhs) += microseconds;
}
///< Add a specified number of microseconds to the TimeVal object <EM>lhs</EM>.

inline const TimeVal
operator+(const TimeVal& lhs, const TimeVal& rhs)
{
	return TimeVal(lhs) += rhs;
}
///< Add two TimeVal objects together.

/// @}
/// @name TimeVal subtraction operators
/// @{

inline const TimeVal
operator-(const TimeVal& lhs, long microseconds)
{
	return TimeVal(lhs) -= microseconds;
}
///< Subtract a specified number of microseconds from the TimeVal object <EM>lhs</EM>.

inline const TimeVal
operator-(const TimeVal& lhs, const TimeVal& rhs)
{
	return TimeVal(lhs) -= rhs;
}
///< Subtract the TimeVal object <EM>rhs</EM> from <EM>lhs</EM>.

/// @}

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/timeval.inl>

#endif // XFC_G_TIMER_HH



