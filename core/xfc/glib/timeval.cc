/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  timeval.cc - GTimeVal C++ wrapper implentation
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
 
#include "timeval.hh"
#include <glib/gmain.h>
#include <glib/gtimer.h>

using namespace Xfc;

/*  G::usleep
 */

void
G::usleep(unsigned long microseconds)
{
	g_usleep(microseconds);
}

/*  G::get_current_time
 */

G::TimeVal
G::get_current_time()
{
	GTimeVal tv;
	g_get_current_time(&tv);
	return TimeVal(tv);
}

/*  G::TimeVal
 */

G::TimeVal::TimeVal()
{
	timeval_.tv_sec = 0;
	timeval_.tv_usec = 0;
}

G::TimeVal::TimeVal(long seconds, long microseconds)
{
	timeval_.tv_sec = seconds;
	timeval_.tv_usec = 0;
	g_time_val_add(g_time_val(), microseconds);
}

G::TimeVal::TimeVal(const double& timeval)
{
	timeval_.tv_sec = (glong)timeval;
	timeval_.tv_usec = (glong)((timeval - ((double)timeval_.tv_sec)) * G_USEC_PER_SEC);
	if (timeval_.tv_usec >= G_USEC_PER_SEC)
	{
		timeval_.tv_sec += timeval_.tv_usec / G_USEC_PER_SEC;
		timeval_.tv_usec %= G_USEC_PER_SEC;
	}
}

G::TimeVal::TimeVal(const GTimeVal& timeval)
{
	timeval_.tv_sec = timeval.tv_sec;
	timeval_.tv_usec = timeval.tv_usec;
}

inline bool
G::TimeVal::equal(const TimeVal& other) const
{
	return timeval_.tv_sec == other.seconds() && timeval_.tv_usec == other.microseconds();
}

bool
G::TimeVal::operator<(const TimeVal& other)
{
	if (timeval_.tv_sec < other.seconds())
		return true;
	else if (timeval_.tv_sec == other.seconds() && timeval_.tv_usec < other.microseconds())
		return true;
	else
		return false;
}

bool
G::TimeVal::operator>(const TimeVal& other)
{
	if (timeval_.tv_sec > other.seconds())
		return true;
	else if (timeval_.tv_sec == other.seconds() && timeval_.tv_usec > other.microseconds())
		return true;
	else
		return false;
}

inline void
G::TimeVal::add(long microseconds)
{
	g_time_val_add(const_cast<GTimeVal*>(&timeval_), microseconds);
}

void
G::TimeVal::add(long seconds, long microseconds)
{
	timeval_.tv_sec += seconds;
	g_time_val_add(g_time_val(), microseconds);
}

void
G::TimeVal::add(const TimeVal& other)
{
	timeval_.tv_sec += other.seconds();
	g_time_val_add(g_time_val(), other.microseconds());
}

void
G::TimeVal::subtract(const TimeVal& other)
{
	timeval_.tv_sec -= other.seconds();
	if (timeval_.tv_usec < other.microseconds())
	{
		timeval_.tv_sec--;
		timeval_.tv_usec += G_USEC_PER_SEC;
	}
	timeval_.tv_usec -= other.microseconds();
}

long
G::TimeVal::difference(const TimeVal& other)
{
	return ((timeval_.tv_sec - other.seconds()) * G_USEC_PER_SEC) + (timeval_.tv_usec - other.microseconds());
}

G::TimeVal&
G::TimeVal::operator+=(long microseconds)
{
	add(microseconds);
	return *this;
}

G::TimeVal&
G::TimeVal::operator+=(const TimeVal& other)
{
	add(other);
	return *this;
}

G::TimeVal&
G::TimeVal::operator-=(long microseconds)
{
	add(-microseconds);
	return *this;
}

G::TimeVal&
G::TimeVal::operator-=(const TimeVal& other)
{
	subtract(other);
	return *this;
}

