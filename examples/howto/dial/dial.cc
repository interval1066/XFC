/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  dial.cc - Dial is a custom widget, a C++ version of the GtkDial example.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "dial.hh"
#include <xfc/gtk/private/widgetclass.hh>
#include <xfc/gtk/adjustment.hh>
#include <xfc/gtk/style.hh>
#include <xfc/gdk/window.hh>
#include <xfc/glib/main.hh>
#include <xfc/main.hh>
#include <algorithm>
#include <cmath>

const int scroll_delay_length = 300;
const int dial_default_size = 100;

using namespace Xfc;

Gtk::Dial::Dial(Adjustment *adjustment)
: Gtk::Widget((GtkWidget*)Gtk::WidgetClass::create()),
  Gtk::WidgetSignals(this),
  adjustment_(0)
{
	button = 0;
	policy_ = UPDATE_CONTINUOUS;
	radius = 0;
	pointer_width = 0;
	angle = 0.0;
	old_value = 0.0;
	old_lower = 0.0;
	old_upper = 0.0;

	if (!adjustment)
		adjustment = new Gtk::Adjustment;

	set_adjustment(adjustment);
}

Gtk::Dial::~Dial()
{
}

Gtk::Adjustment*
Gtk::Dial::get_adjustment() const
{
	return adjustment_;
}

void 
Gtk::Dial::set_adjustment(Adjustment *adjustment)
{
	if (adjustment_)
	{
		adjustment_->disconnect_by_name("changed");
		adjustment_->disconnect_by_name("value_changed");
	}

	adjustment_ = adjustment;

	if (adjustment_)
	{
		adjustment_->signal_changed().connect(sigc::mem_fun(this, &Dial::on_adjustment_changed));
		adjustment_->signal_value_changed().connect(sigc::mem_fun(this, &Dial::on_adjustment_value_changed));
	}

	old_value = adjustment_->get_value();
	old_lower = adjustment_->lower();
	old_upper = adjustment_->upper();
	update();
}

void
Gtk::Dial::on_realize()
{
	set_flags(REALIZED);
	
	Gdk::EventMaskField mask = get_events() | Gdk::EXPOSURE_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK;
	mask |= (Gdk::POINTER_MOTION_MASK | Gdk::POINTER_MOTION_HINT_MASK);
	Gdk::WindowAttr attributes(get_allocation(), Gdk::WINDOW_CHILD, mask);
	attributes.set_visual(*get_visual());
	attributes.set_colormap(*get_colormap());
	
	Gdk::Window *window = new Gdk::Window(*get_parent_window(), attributes);
	set_window(*window);
	get_style()->attach(*window);
	window->set_user_data(gtk_widget());
	get_style()->set_background(*window, STATE_ACTIVE);
}
	
void 
Gtk::Dial::on_size_request(Requisition *requisition)
{
	requisition->set(dial_default_size, dial_default_size);
}

void
Gtk::Dial::on_size_allocate(const Allocation& allocation)
{
	set_allocation(allocation);

	if (is_realized())
	{
		get_window()->move_resize(allocation);
	}

	radius = (int)(std::min(allocation.width(), allocation.height()) * 0.45);
	pointer_width = radius / 5;
}

bool 
Gtk::Dial::on_expose_event(const Gdk::EventExpose& event)
{
	if (event.count() > 0)
		return false;

	Allocation allocation = get_allocation();
	int xc = allocation.width() / 2;
	int yc = allocation.height() / 2;

	int upper = (int)adjustment_->upper();
	int lower = (int)adjustment_->lower();

	double s = sin(last_angle);
	double c = cos(last_angle);
	last_angle = angle;

	Gdk::Point points[6];
	points[0].set(int(xc + s * pointer_width / 2), int(yc + c * pointer_width / 2));
	points[1].set(int(xc + c * radius), int(yc - s * radius));
	points[2].set(int(xc - s * pointer_width / 2), int(yc - c * pointer_width / 2));
	points[3].set(int(xc - c * radius / 10), int(yc + s * radius / 10));
	points[4].set(points[0].x(), points[0].y());

	Gdk::Window *window = get_window();
	window->invalidate(allocation, false);
	Gtk::Style *style = get_style();
	style->draw_polygon(*window, STATE_NORMAL, SHADOW_OUT, points, 5, false, 0, this);

	// Draw ticks
	int inc = upper - lower;
	if (inc == 0)
		return false;

	double increment = (100 * G_PI) / ( radius * radius);
	while (inc < 100) inc *= 10;
	while (inc >= 1000) inc /= 10;
	double last = -1;

	for (int i = 0; i <= inc; i++)
	{
		double theta = ((float)i * G_PI / (18 * inc / 24.) - G_PI / 6.);
		if ((theta - last) < (increment))
			continue;

		last = theta;
		s = sin(theta);
		c = cos(theta);

		int tick_length = (i % (inc / 10) == 0) ? pointer_width : pointer_width / 2;

		window->draw_line(*style->fg_gc(get_state()), int(xc + c * (radius - tick_length)),
		int(yc - s * (radius - tick_length)), int(xc + c * radius), int(yc - s * radius));
	}

  	// Draw pointer
	s = sin(angle);
	c = cos(angle);
	last_angle = angle;

	points[0].set(int(xc + s * pointer_width / 2), int(yc + c * pointer_width / 2));
	points[1].set(int(xc + c * radius), int(yc - s * radius));
	points[2].set(int(xc - s * pointer_width / 2), int(yc - c * pointer_width / 2));
	points[3].set(int(xc - c * radius / 10), int(yc + s * radius / 10));
	points[4].set(points[0].x(), points[0].y());

	style->draw_polygon(*window, STATE_NORMAL, SHADOW_OUT, points, 5, true, 0, this);
	return false;
}


bool
Gtk::Dial::on_button_press_event(const Gdk::EventButton& event)
{
	// Determine if button press was within pointer region - we do this by
	// computing the parallel and perpendicular distance of the point where
	// the mouse was pressed from the line passing through the pointer.

	int dx = int(event.x()) - get_allocation().width() / 2;
	int dy = get_allocation().height() / 2 - int(event.y());

	double s = sin(angle);
	double c = cos(angle);
	double d_parallel = s * dy + c * dx;
	double d_perpendicular = fabs(s * dx - c * dy);

	if (!button && (d_perpendicular < pointer_width/2) && (d_parallel > - pointer_width))
	{
		Main::grab_add(*this);
		button = event.button();
		update_mouse(int(event.x()), int(event.y()));
	}
	return false;
}

bool
Gtk::Dial::on_button_release_event(const Gdk::EventButton& event)
{
	if (button == event.button())
	{
		Main::grab_remove(*this);
		button = 0;

		if (policy_ == UPDATE_DELAYED)
			timer.disconnect();

		if ((policy_ != UPDATE_CONTINUOUS) && (old_value != adjustment_->get_value()))
			adjustment_->value_changed();
	}
	return false;
}

bool 
Gtk::Dial::on_motion_notify_event(const Gdk::EventMotion& event)
{
	Gtk::WidgetSignals::on_motion_notify_event(event);

	if (button != 0)
	{
		
		int x = int(event.x());
		int y = int(event.y());


		Gdk::ModifierTypeField mods;
		Gdk::Window *window = get_window();
		if (event.is_hint() || (event.window() != window))
			window->get_pointer(&x, &y, &mods);

		int mask;
		switch (button)
		{
		case 1:
			mask = GDK_BUTTON1_MASK;
			break;
		case 2:
			mask = GDK_BUTTON2_MASK;
			break;
		case 3:
			mask = GDK_BUTTON3_MASK;
			break;
		default:
			mask = 0;
			break;
		}

		if (mods & mask)
			update_mouse(x, y);
	}
	return false;
}

void
Gtk::Dial::set_update_policy(UpdateType policy)
{
	policy_ = policy;
}

void
Gtk::Dial::update()
{
	double value = adjustment_->get_value();
	double lower = adjustment_->lower();
	double upper = adjustment_->upper();

	double new_value = std::max(lower, value);
	new_value = std::min(new_value, upper);

	if (new_value != value)
	{
		adjustment_->set_value(new_value);
		adjustment_->value_changed();
	}

	angle = 7.*G_PI/6. - (new_value - lower) * 4.*G_PI/3. / (upper - lower);
	queue_draw();
}

void
Gtk::Dial::update_mouse(int x, int y)
{
	int xc = get_allocation().width() / 2;
	int yc = get_allocation().height() / 2;

	float old_value = adjustment_->get_value();
	angle = atan2(yc - y, x - xc);

	if (angle < -G_PI/2.)
		angle += 2*G_PI;

	if (angle < -G_PI/6)
		angle = -G_PI/6;

	if (angle > 7.*G_PI/6.)
		angle = 7.*G_PI/6.;

	double lower = adjustment_->lower();
	adjustment_->set_value(lower + (7.*G_PI/6 - angle) * (adjustment_->upper() - lower) / (4.*G_PI/3.));

	if (adjustment_->get_value() == old_value)
	{
		if (policy_ == UPDATE_CONTINUOUS)
		{
			adjustment_->value_changed();
		}
		else
		{
			queue_draw();
			if (policy_ == UPDATE_DELAYED)
			{
				timer = G::timeout_signal.connect(sigc::mem_fun(this, &Dial::on_timeout), scroll_delay_length);
			}
		}
	}
}

bool
Gtk::Dial::on_timeout()
{
	if (policy_ == UPDATE_DELAYED)
		adjustment_->value_changed();
	return false;
}

void
Gtk::Dial::on_adjustment_changed()
{
	double value = adjustment_->get_value();
	double lower = adjustment_->lower();
	double upper = adjustment_->upper();

	if ((old_value != value) || (old_lower != lower) || (old_upper != upper))
	{
		update();
		old_value = value;
		old_lower = lower;
		old_upper = upper;
	}
}

void
Gtk::Dial::on_adjustment_value_changed()
{
	double value = adjustment_->get_value();

	if (old_value != value)
	{
		update();
		old_value = value;
	}
}

