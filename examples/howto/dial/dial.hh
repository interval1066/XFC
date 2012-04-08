/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  dial.hh - Dial is a custom widget, a C++ version of the GtkDial example.
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

#ifndef XFC_GTK_DIAL_HH
#define XFC_GTK_DIAL_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef XFC_GTK_WIDGET_SIGNALS_HH
#include <xfc/gtk/widgetsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

class Adjustment;

class Dial : public Widget, protected WidgetSignals
{
	UpdateType policy_;
	// Either UPDATE_CONTINUOUS, UPDATE DISCONTINUOUS or UPDATE_DELAYED.
	
	unsigned int button;
	// The mouse button currently pressed or 0 if none.
	
	int radius;
	int pointer_width;
	// Dimensions of the dial components.

	sigc::connection timer;
	// Signal connection of the update timer.
	
	float angle;
	float last_angle;
	// Current angle.

	float old_value;
	float old_lower;
	float old_upper;
	// Old values from adjustment stored so we know when something changes.

	Pointer<Adjustment> adjustment_;
	// The adjustment object that stores the data for this dial. A smart
	// pointer is used to handle the reference counting.

	void update();
	void update_mouse(int x, int y);

	bool on_timeout();

protected:
// Signal Handlers
	
	virtual void on_realize();

	virtual bool on_expose_event(const Gdk::EventExpose& event);

	virtual void on_size_request(Requisition *requisition);

	virtual void on_size_allocate(const Allocation& allocation);

	virtual bool on_button_press_event(const Gdk::EventButton& event);

	virtual bool on_button_release_event(const Gdk::EventButton& event);

	virtual bool on_motion_notify_event(const Gdk::EventMotion& event);

	void on_adjustment_changed();

	void on_adjustment_value_changed();

public:
// Constructors

	Dial(Adjustment *adjustment = 0);

	virtual ~Dial();
	
// Accessors

	Adjustment* get_adjustment() const;
	
// Methods

	void set_adjustment(Adjustment *adjustment);

	void set_update_policy(UpdateType policy);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_DIAL_HH

