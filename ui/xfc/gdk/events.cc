/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  events.cc - Gdk events C++ wrapper implementation
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
 
#include "events.hh"
#include "display.hh"
#include "dnd.hh"
#include "keyval.hh"
#include "input.hh"
#include "region.hh"
#include "screen.hh"
#include "window.hh"

using namespace Xfc;

/*  Gdk::Event
 */

Gdk::Event::Event()
: G::Boxed(GDK_TYPE_EVENT)
{
}

Gdk::Event::Event(GdkEvent* event)
: G::Boxed(GDK_TYPE_EVENT, event)
{
}

Gdk::Event::Event(GdkEvent* event, bool copy)
: G::Boxed(GDK_TYPE_EVENT, event, copy)
{
}

Gdk::Event::Event(const Event& src)
: G::Boxed(GDK_TYPE_EVENT, src.g_boxed(), true)
{
}

Gdk::Event::~Event()
{
}

Gdk::Event& 
Gdk::Event::operator=(const Event& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

Gdk::EventAny*
Gdk::Event::any() const
{
	return (EventAny*)gdk_event();
}

Gdk::EventExpose*
Gdk::Event::expose() const
{
	return type() == EXPOSE ? (EventExpose*)this : 0;
}

Gdk::EventVisibility*
Gdk::Event::visibility() const
{
	return type() == VISIBILITY_NOTIFY ? (EventVisibility*)this : 0;
}
	
Gdk::EventMotion*
Gdk::Event::motion() const
{
	return type() == MOTION_NOTIFY ? (EventMotion*)this : 0;
}

Gdk::EventButton*
Gdk::Event::button() const
{
	bool is_type = type() == BUTTON_PRESS || type() == TWO_BUTTON_PRESS || 
	               type() == THREE_BUTTON_PRESS || type() == BUTTON_RELEASE;
	return is_type ? (EventButton*)this : 0;
}
	
Gdk::EventScroll*
Gdk::Event::scroll() const
{
	return type() == SCROLL ? (EventScroll*)this : 0;
}

Gdk::EventKey*
Gdk::Event::key() const
{
	return (type() == KEY_PRESS || type() == KEY_RELEASE) ? (EventKey*)this : 0;
}
	
Gdk::EventCrossing*
Gdk::Event::crossing() const
{
	return (type() == ENTER_NOTIFY || type() == LEAVE_NOTIFY) ? (EventCrossing*)this : 0;
}

Gdk::EventFocus*
Gdk::Event::focus_change() const
{
	return type() == FOCUS_CHANGE ? (EventFocus*)this : 0;
}

Gdk::EventConfigure*
Gdk::Event::configure() const
{
	return type() == CONFIGURE ? (EventConfigure*)this : 0;
}

Gdk::EventProperty*
Gdk::Event::property() const
{
	return type() == PROPERTY_NOTIFY ? (EventProperty*)this : 0;
}

Gdk::EventSelection*
Gdk::Event::selection() const
{
	bool is_type = type() == SELECTION_CLEAR || type() == SELECTION_REQUEST || type() == SELECTION_NOTIFY;
	return is_type ? (EventSelection*)this : 0;
}

Gdk::EventOwnerChange* 
Gdk::Event::owner_change() const
{
	return (type() == OWNER_CHANGE) ? (EventOwnerChange*)this : 0;
}	

Gdk::EventProximity*
Gdk::Event::proximity() const
{
	return (type() == PROXIMITY_IN || type() == PROXIMITY_OUT) ? (EventProximity*)this : 0;
}
	
Gdk::EventClient*
Gdk::Event::client() const
{
	return type() == CLIENT_EVENT ? (EventClient*)this : 0;
}
	
Gdk::EventSetting*
Gdk::Event::setting() const
{
	return type() == SETTING ? (EventSetting*)this : 0;
}

Gdk::EventWindowState*
Gdk::Event::window_state() const
{
	return type() == WINDOW_STATE ? (EventWindowState*)this : 0;
}

Gdk::EventDND*
Gdk::Event::dnd() const
{
	bool is_type = type() == DRAG_ENTER || type() == DRAG_LEAVE || type() == DRAG_MOTION ||
	               type() == DRAG_STATUS || type() == DROP_START || type() == DROP_FINISHED;
	return is_type ? (EventDND*)this : 0;
}

Gdk::Screen*
Gdk::Event::get_screen() const
{
	return G::Object::wrap<Screen>(gdk_event_get_screen(gdk_event()));
}

Pointer<Gdk::Event>
Gdk::Event::get()
{
	Event *event = 0;
	GdkEvent *gdk_event = gdk_event_get();
	if (gdk_event)
		event = new Event(gdk_event, false);
	return event;
}

Pointer<Gdk::EventExpose>
Gdk::Event::get_graphics_expose(const Window& window)
{
	Event *event = 0;
	GdkEvent *gdk_event = gdk_event_get_graphics_expose(window.gdk_window());
	if (gdk_event)
		event = new Event(gdk_event, false);
	return event ? event->expose() : 0;
}

Pointer<Gdk::Event>
Gdk::Event::peek()
{
	Event *event = 0;
	GdkEvent *gdk_event = gdk_event_peek();
	if (gdk_event)
		event = new Event(gdk_event, false);
	return event;
}

bool
Gdk::Event::send_client_message(GdkNativeWindow winid, const Display *display)
{
	bool client_event = type() == CLIENT_EVENT;
	if (client_event)
	{
		GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
		client_event = gdk_event_send_client_message_for_display(tmp_display, gdk_event(), winid);
	}
	return client_event;
}

void 
Gdk::Event::send_clientmessage_toall()
{
	if (type() == CLIENT_EVENT)
		gdk_event_send_clientmessage_toall(gdk_event());
}

void 
Gdk::Event::set_screen(Screen& screen)
{
	gdk_event_set_screen(gdk_event(), screen.gdk_screen());
}

/*  Gdk::EventAny
 */

Gdk::Window*
Gdk::EventAny::window() const
{
	return G::Object::wrap<Window>(gdk_event_any()->window);
}

/*  Gdk::EventExpose
 */

const Gdk::Rectangle&
Gdk::EventExpose::area() const
{
	return reinterpret_cast<Rectangle&>(gdk_event_expose()->area);
}

Pointer<Gdk::Region>
Gdk::EventExpose::region() const
{
	return new Region(gdk_event_expose()->region, true);
}

/*  Gdk::EventMotion
 */

Gdk::Device*
Gdk::EventMotion::device() const
{
	return G::Object::wrap<Device>(gdk_event_motion()->device);
}

/*  Gdk::EventButton
 */

Gdk::Device*
Gdk::EventButton::device() const
{
	return G::Object::wrap<Device>(gdk_event_button()->device);
}

/*  Gdk::EventScroll
 */

Gdk::Device*
Gdk::EventScroll::device() const
{
	return G::Object::wrap<Device>(gdk_event_scroll()->device);
}

/*  Gdk::EventKey
 */

Gdk::Keyval
Gdk::EventKey::keyval() const
{
	return ((GdkEventKey*)boxed_)->keyval;
}

/*  Gdk::EventCrossing
 */

Gdk::Window*
Gdk::EventCrossing::subwindow() const
{
	return G::Object::wrap<Window>(gdk_event_crossing()->subwindow);
}

/*  Gdk::EventProximity
 */

Gdk::Device*
Gdk::EventProximity::device() const
{
	return G::Object::wrap<Device>(gdk_event_proximity()->device);
}

/*  Gdk::EventSetting
 */

String
Gdk::EventSetting::name() const
{
	return gdk_event_setting()->name;
}

/*  Gdk::EventDND
 */

Gdk::DragContext*
Gdk::EventDND::context() const
{
	return G::Object::wrap<DragContext>(gdk_event_dnd()->context);
}

