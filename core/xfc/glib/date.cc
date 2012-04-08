/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  date.cc - A GDate C++ wrapper implementation
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

#include "date.hh"
#include <glib/gmem.h>

using namespace Xfc;

/*  G::Date
 */

G::Date::Date()
: date_(g_date_new())
{
}

G::Date::Date(DateDay day, DateMonth month, DateYear year)
: date_(g_date_new_dmy(day, (GDateMonth)month, year))
{
}

G::Date::Date(unsigned int julian_day)
: date_(g_date_new_julian(julian_day))
{
}

G::Date::Date(const GDate& date)
: date_(g_date_new())
{
	*date_ = date;
}

G::Date::Date(const Date& src)
: date_(g_date_new())
{
	*date_ = *src.date_;
}

G::Date::~Date()
{
	if (date_)
	{
		g_date_free(date_);
		date_ = 0;
	}
}

G::Date&
G::Date::operator=(const Date& src)
{
	*date_ = *src.date_;
	return *this;
}

int
G::Date::compare(const Date& other) const
{
	return g_date_compare(g_date(), other.g_date());
}

bool
G::Date::operator==(const Date& other) const
{
	return compare(other) == 0;
}

bool
G::Date::operator!=(const Date& other) const
{
	return compare(other) != 0;
}

bool
G::Date::operator<(const Date& other) const
{
	return compare(other) < 0;
}

bool
G::Date::operator<=(const Date& other) const
{
	return compare(other) <= 0;
}

bool
G::Date::operator>(const Date& other) const
{
	return compare(other) > 0;
}

bool
G::Date::operator>=(const Date& other) const
{
	return compare(other) >= 0;
}

int
G::Date::days_between(const Date& date1, const Date& date2)
{
	return g_date_days_between(date1.g_date(), date2.g_date());
}

void
G::Date::set_parse(const String& str)
{
	g_date_set_parse(g_date(), str.c_str());
}

void
G::Date::clamp(const Date *min_date, const Date *max_date)
{
	g_date_clamp(g_date(), *min_date, *max_date);
}

void
G::Date::order(Date& other)
{
	g_date_order(g_date(), other.g_date());
}

String
G::Date::format(const String& date_format)
{
	String s;
	gsize result = 0;
	int buffersize = 64;

	do
	{
		char *buffer = static_cast<char*>(g_malloc(buffersize));
		result = g_date_strftime(buffer, buffersize, date_format.c_str(), g_date());
		if (result)
			s = buffer;
		g_free(buffer);
	}
	while (!result && (buffersize *= 2));

	return s;
}

