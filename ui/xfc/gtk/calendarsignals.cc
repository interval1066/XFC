/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  calendar.cc - Gtk::Calendar virtual signal handlers
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
 
#include "calendar.hh"
#include "calendarsignals.hh"
#include "private/calendarclass.hh"

using namespace Xfc;

/*  Gtk::CalendarSignals
 */

Gtk::CalendarSignals::CalendarSignals(Calendar *calendar)
: WidgetSignals(calendar)
{
}

Gtk::CalendarSignals::~CalendarSignals()
{
}

void
Gtk::CalendarSignals::on_month_changed()
{
	GtkCalendarClass *g_class = CalendarClass::get_parent_class(instance_);
	if (g_class && g_class->month_changed)
		g_class->month_changed((GtkCalendar*)instance_);
}

void
Gtk::CalendarSignals::on_day_selected()
{
	GtkCalendarClass *g_class = CalendarClass::get_parent_class(instance_);
	if (g_class && g_class->day_selected)
		g_class->day_selected((GtkCalendar*)instance_);
}

void
Gtk::CalendarSignals::on_day_selected_double_click()
{
	GtkCalendarClass *g_class = CalendarClass::get_parent_class(instance_);
	if (g_class && g_class->day_selected_double_click)
		g_class->day_selected_double_click((GtkCalendar*)instance_);
}

void
Gtk::CalendarSignals::on_prev_month()
{
	GtkCalendarClass *g_class = CalendarClass::get_parent_class(instance_);
	if (g_class && g_class->prev_month)
		g_class->prev_month((GtkCalendar*)instance_);
}

void
Gtk::CalendarSignals::on_next_month()
{
	GtkCalendarClass *g_class = CalendarClass::get_parent_class(instance_);
	if (g_class && g_class->next_month)
		g_class->next_month((GtkCalendar*)instance_);
}

void
Gtk::CalendarSignals::on_prev_year()
{
	GtkCalendarClass *g_class = CalendarClass::get_parent_class(instance_);
	if (g_class && g_class->prev_year)
		g_class->prev_year((GtkCalendar*)instance_);
}

void
Gtk::CalendarSignals::on_next_year()
{
	GtkCalendarClass *g_class = CalendarClass::get_parent_class(instance_);
	if (g_class && g_class->next_year)
		g_class->next_year((GtkCalendar*)instance_);
}

