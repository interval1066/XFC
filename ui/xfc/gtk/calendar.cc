/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  calendar.cc - GtkCalendar C++ wrapper implementation
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
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Calendar
 */

Gtk::Calendar::Calendar(GtkCalendar *calendar, bool owns_reference)
: Widget((GtkWidget*)calendar, owns_reference)
{
}

Gtk::Calendar::Calendar()
: Widget((GtkWidget*)CalendarClass::create())
{
}

Gtk::Calendar::Calendar(CalendarDisplayOptionsField flags)
: Widget((GtkWidget*)CalendarClass::create())
{
	set_display_options(flags);
}

Gtk::Calendar::~Calendar()
{
}

std::vector<bool>
Gtk::Calendar::marked_date() const
{
	std::vector<bool> dates(31);

	for (int i = 0; i < 31; i++)
	{
		dates[i] = gtk_calendar()->marked_date[i];
	}

	return dates;
}

/*  Gtk::CalendarClass
 */

void
Gtk::CalendarClass::init(GtkCalendarClass *g_class)
{
	WidgetClass::init((GtkWidgetClass*)g_class);
	g_class->month_changed = &month_changed_proxy;
	g_class->day_selected = &day_selected_proxy;
	g_class->day_selected_double_click = &day_selected_double_click_proxy;
	g_class->prev_month = &prev_month_proxy;
	g_class->next_month = &next_month_proxy;
	g_class->prev_year = &prev_year_proxy;
	g_class->next_year = &next_year_proxy;
}

GtkCalendarClass*
Gtk::CalendarClass::get_parent_class(void *instance)
{
	return static_cast<GtkCalendarClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::CalendarClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_CALENDAR, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::CalendarClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::CalendarClass::month_changed_proxy(GtkCalendar *calendar)
{
	CalendarSignals *signals = dynamic_cast<CalendarSignals*>(G::ObjectSignals::pointer((GObject*)calendar));
	if (signals)
		signals->on_month_changed();
	else
	{
		GtkCalendarClass *g_class = get_parent_class(calendar);
		if (g_class && g_class->month_changed)
			g_class->month_changed(calendar);
	}
}

void
Gtk::CalendarClass::day_selected_proxy(GtkCalendar *calendar)
{
	CalendarSignals *signals = dynamic_cast<CalendarSignals*>(G::ObjectSignals::pointer((GObject*)calendar));
	if (signals)
		signals->on_day_selected();
	else
	{
		GtkCalendarClass *g_class = get_parent_class(calendar);
		if (g_class && g_class->day_selected)
			g_class->day_selected(calendar);
	}
}

void
Gtk::CalendarClass::day_selected_double_click_proxy(GtkCalendar *calendar)
{
	CalendarSignals *signals = dynamic_cast<CalendarSignals*>(G::ObjectSignals::pointer((GObject*)calendar));
	if (signals)
		signals->on_day_selected_double_click();
	else
	{
		GtkCalendarClass *g_class = get_parent_class(calendar);
		if (g_class && g_class->day_selected_double_click)
			g_class->day_selected_double_click(calendar);
	}
}

void
Gtk::CalendarClass::prev_month_proxy(GtkCalendar *calendar)
{
	CalendarSignals *signals = dynamic_cast<CalendarSignals*>(G::ObjectSignals::pointer((GObject*)calendar));
	if (signals)
		signals->on_prev_month();
	else
	{
		GtkCalendarClass *g_class = get_parent_class(calendar);
		if (g_class && g_class->prev_month)
			g_class->prev_month(calendar);
	}
}

void
Gtk::CalendarClass::next_month_proxy(GtkCalendar *calendar)
{
	CalendarSignals *signals = dynamic_cast<CalendarSignals*>(G::ObjectSignals::pointer((GObject*)calendar));
	if (signals)
		signals->on_next_month();
	else
	{
		GtkCalendarClass *g_class = get_parent_class(calendar);
		if (g_class && g_class->next_month)
			g_class->next_month(calendar);
	}
}

void
Gtk::CalendarClass::prev_year_proxy(GtkCalendar *calendar)
{
	CalendarSignals *signals = dynamic_cast<CalendarSignals*>(G::ObjectSignals::pointer((GObject*)calendar));
	if (signals)
		signals->on_prev_year();
	else
	{
		GtkCalendarClass *g_class = get_parent_class(calendar);
		if (g_class && g_class->prev_year)
			g_class->prev_year(calendar);
	}
}

void
Gtk::CalendarClass::next_year_proxy(GtkCalendar *calendar)
{
	CalendarSignals *signals = dynamic_cast<CalendarSignals*>(G::ObjectSignals::pointer((GObject*)calendar));
	if (signals)
		signals->on_next_year();
	else
	{
		GtkCalendarClass *g_class = get_parent_class(calendar);
		if (g_class && g_class->next_year)
			g_class->next_year(calendar);
	}
}

/*  Gtk::Calendar signals
 */

const Gtk::Calendar::MonthChangedSignalType Gtk::Calendar::month_changed_signal("month_changed", (GCallback)&G::Marshal::void_callback);

const Gtk::Calendar::DaySelectedSignalType Gtk::Calendar::day_selected_signal("day_selected", (GCallback)&G::Marshal::void_callback);

const Gtk::Calendar::DaySelectedDoubleClickSignalType Gtk::Calendar::day_selected_double_click_signal("day_selected_double_click", (GCallback)&G::Marshal::void_callback);

const Gtk::Calendar::PrevMonthSignalType Gtk::Calendar::prev_month_signal("prev_month", (GCallback)&G::Marshal::void_callback);

const Gtk::Calendar::NextMonthSignalType Gtk::Calendar::next_month_signal("next_month", (GCallback)&G::Marshal::void_callback);

const Gtk::Calendar::PrevYearSignalType Gtk::Calendar::prev_year_signal("prev_year", (GCallback)&G::Marshal::void_callback);

const Gtk::Calendar::NextYearSignalType Gtk::Calendar::next_year_signal("next_year", (GCallback)&G::Marshal::void_callback);

