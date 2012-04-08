/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  events.inl - Gdk::Event inline functions
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

/*  Gdk::get_show_events
 */

inline bool
Xfc::Gdk::get_show_events()
{
	return gdk_get_show_events();
}

/*  Gdk::events_pending
 */

inline bool
Xfc::Gdk::events_pending()
{
	return gdk_events_pending();
}

/*  Gdk::set_show_events
 */

inline void
Xfc::Gdk::set_show_events(bool show_events)
{
	gdk_set_show_events(show_events);
}

/*  Gdk::Event
 */

inline GdkEvent*
Xfc::Gdk::Event::gdk_event() const
{
	return reinterpret_cast<GdkEvent*>(boxed_);
}

inline Xfc::Gdk::Event::operator GdkEvent* () const
{
	return this ? gdk_event() : 0;
}

inline Xfc::Gdk::EventType
Xfc::Gdk::Event::type() const
{
	return (EventType)gdk_event()->type;
}

inline unsigned int
Xfc::Gdk::Event::get_time() const
{
	return gdk_event_get_time(gdk_event());
}

inline bool
Xfc::Gdk::Event::get_state(ModifierTypeField *state) const
{
	return gdk_event_get_state(gdk_event(), (GdkModifierType*)state);
}

inline bool
Xfc::Gdk::Event::get_axis(AxisUse axis_use, double *value) const
{
	return gdk_event_get_axis(gdk_event(), (GdkAxisUse)axis_use, value);
}

inline bool
Xfc::Gdk::Event::get_coords(double *x_win, double *y_win) const
{
	return gdk_event_get_coords(gdk_event(), x_win, y_win);
}

inline bool
Xfc::Gdk::Event::get_root_coords(double *x_root, double *y_root) const
{
	return gdk_event_get_root_coords(gdk_event(), x_root, y_root);
}

inline void
Xfc::Gdk::Event::put()
{
	gdk_event_put(gdk_event());
}

/*  Gdk::EventAny
 */

inline GdkEventAny*
Xfc::Gdk::EventAny::gdk_event_any() const
{
	return reinterpret_cast<GdkEventAny*>(boxed_);
}

inline bool
Xfc::Gdk::EventAny::send_event() const
{
	return gdk_event_any()->send_event;
}

/*  Gdk::EventExpose
 */

inline GdkEventExpose*
Xfc::Gdk::EventExpose::gdk_event_expose() const
{
	return reinterpret_cast<GdkEventExpose*>(boxed_);
}

inline int
Xfc::Gdk::EventExpose::count() const
{
	return gdk_event_expose()->count;
}

/*  Gdk::EventVisibilty
 */

inline GdkEventVisibility*
Xfc::Gdk::EventVisibility::gdk_event_visibility() const
{
	return reinterpret_cast<GdkEventVisibility*>(boxed_);
}

inline Xfc::Gdk::VisibilityState
Xfc::Gdk::EventVisibility::state() const
{
	return (VisibilityState)gdk_event_visibility()->state;
}

/*  Gdk::EventMotion
 */

inline GdkEventMotion*
Xfc::Gdk::EventMotion::gdk_event_motion() const
{
	return reinterpret_cast<GdkEventMotion*>(boxed_);
}

inline unsigned int
Xfc::Gdk::EventMotion::time() const
{
	return gdk_event_motion()->time;
}

inline double
Xfc::Gdk::EventMotion::x() const
{
	return gdk_event_motion()->x;
}

inline double
Xfc::Gdk::EventMotion::y() const
{
	return gdk_event_motion()->y;
}

inline int
Xfc::Gdk::EventMotion::x_int() const
{
	return (int)gdk_event_motion()->x;
}

inline int
Xfc::Gdk::EventMotion::y_int() const
{
	return (int)gdk_event_motion()->y;
}

inline double*
Xfc::Gdk::EventMotion::axes() const
{
	return gdk_event_motion()->axes;
}

inline Xfc::Gdk::ModifierTypeField
Xfc::Gdk::EventMotion::state() const
{
	return gdk_event_motion()->state;
}

inline bool
Xfc::Gdk::EventMotion::is_hint() const
{
	return gdk_event_motion()->is_hint != 0;
}

inline double
Xfc::Gdk::EventMotion::x_root() const
{
	return gdk_event_motion()->x_root;
}

inline double
Xfc::Gdk::EventMotion::y_root() const
{
	return gdk_event_motion()->y_root;
}

/*  Gdk::EventButton
 */

inline GdkEventButton*
Xfc::Gdk::EventButton::gdk_event_button() const
{
	return reinterpret_cast<GdkEventButton*>(boxed_);
}

inline unsigned int
Xfc::Gdk::EventButton::time() const
{
	return gdk_event_button()->time;
}

inline double
Xfc::Gdk::EventButton::x() const
{
	return gdk_event_button()->x;
}

inline double
Xfc::Gdk::EventButton::y() const
{
	return gdk_event_button()->y;
}

inline int
Xfc::Gdk::EventButton::x_int() const
{
	return (int)gdk_event_button()->x;
}

inline int
Xfc::Gdk::EventButton::y_int() const
{
	return (int)gdk_event_button()->y;
}

inline double*
Xfc::Gdk::EventButton::axes() const
{
	return gdk_event_button()->axes;
}

inline Xfc::Gdk::ModifierTypeField
Xfc::Gdk::EventButton::state() const
{
	return gdk_event_button()->state;
}

inline unsigned int
Xfc::Gdk::EventButton::button() const
{
	return gdk_event_button()->button;
}

inline double
Xfc::Gdk::EventButton::x_root() const
{
	return gdk_event_button()->x_root;
}

inline double
Xfc::Gdk::EventButton::y_root() const
{
	return gdk_event_button()->y_root;
}

/*  Gdk::EventScroll
 */

inline GdkEventScroll*
Xfc::Gdk::EventScroll::gdk_event_scroll() const
{
	return reinterpret_cast<GdkEventScroll*>(boxed_);
}

inline unsigned int
Xfc::Gdk::EventScroll::time() const
{
	return gdk_event_scroll()->time;
}

inline double
Xfc::Gdk::EventScroll::x() const
{
	return gdk_event_scroll()->x;
}

inline double
Xfc::Gdk::EventScroll::y() const
{
	return gdk_event_scroll()->y;
}

inline int
Xfc::Gdk::EventScroll::x_int() const
{
	return (int)gdk_event_scroll()->x;
}

inline int
Xfc::Gdk::EventScroll::y_int() const
{
	return (int)gdk_event_scroll()->y;
}

inline Xfc::Gdk::ModifierTypeField
Xfc::Gdk::EventScroll::state() const
{
	return gdk_event_scroll()->state;
}

inline Xfc::Gdk::ScrollDirection
Xfc::Gdk::EventScroll::direction() const
{
	return (ScrollDirection)gdk_event_scroll()->direction;
}

inline double
Xfc::Gdk::EventScroll::x_root() const
{
	return gdk_event_scroll()->x_root;
}

inline double
Xfc::Gdk::EventScroll::y_root() const
{
	return gdk_event_scroll()->y_root;
}

/*  Gdk::EventKey
 */

inline GdkEventKey*
Xfc::Gdk::EventKey::gdk_event_key() const
{
	return reinterpret_cast<GdkEventKey*>(boxed_);
}

inline unsigned int
Xfc::Gdk::EventKey::time() const
{
	return gdk_event_key()->time;
}

inline Xfc::Gdk::ModifierTypeField
Xfc::Gdk::EventKey::state() const
{
	return gdk_event_key()->state;
}

inline unsigned short
Xfc::Gdk::EventKey::hardware_keycode() const
{
	return gdk_event_key()->hardware_keycode;
}

inline unsigned char
Xfc::Gdk::EventKey::group() const
{
	return gdk_event_key()->group;
}

/*  Gdk::EventCrossing
 */

inline GdkEventCrossing*
Xfc::Gdk::EventCrossing::gdk_event_crossing() const
{
	return reinterpret_cast<GdkEventCrossing*>(boxed_);
}

inline unsigned int
Xfc::Gdk::EventCrossing::time() const
{
	return gdk_event_crossing()->time;
}

inline double
Xfc::Gdk::EventCrossing::x() const
{
	return gdk_event_crossing()->x;
}

inline double
Xfc::Gdk::EventCrossing::y() const
{
	return gdk_event_crossing()->y;
}

inline int
Xfc::Gdk::EventCrossing::x_int() const
{
	return (int)gdk_event_crossing()->x;
}

inline int
Xfc::Gdk::EventCrossing::y_int() const
{
	return (int)gdk_event_crossing()->y;
}

inline double
Xfc::Gdk::EventCrossing::x_root() const
{
	return gdk_event_crossing()->x_root;
}

inline double
Xfc::Gdk::EventCrossing::y_root() const
{
	return gdk_event_crossing()->y_root;
}

inline int
Xfc::Gdk::EventCrossing::x_root_int() const
{
	return (int)gdk_event_crossing()->x_root;
}

inline int
Xfc::Gdk::EventCrossing::y_root_int() const
{
	return (int)gdk_event_crossing()->y_root;
}

inline Xfc::Gdk::CrossingMode
Xfc::Gdk::EventCrossing::mode() const
{
	return (CrossingMode)gdk_event_crossing()->mode;
}

inline Xfc::Gdk::NotifyType
Xfc::Gdk::EventCrossing::detail() const
{
	return (NotifyType)gdk_event_crossing()->detail;
}

inline bool
Xfc::Gdk::EventCrossing::focus() const
{
	return gdk_event_crossing()->focus != 0;
}

inline Xfc::Gdk::ModifierTypeField
Xfc::Gdk::EventCrossing::state() const
{
	return gdk_event_crossing()->state;
}

/*  Gdk::EventFocus
 */

inline GdkEventFocus*
Xfc::Gdk::EventFocus::gdk_event_focus() const
{
	return reinterpret_cast<GdkEventFocus*>(boxed_);
}

inline bool
Xfc::Gdk::EventFocus::in() const
{
	return gdk_event_focus()->in != 0;
}

inline bool
Xfc::Gdk::EventFocus::out() const
{
	return gdk_event_focus()->in == 0;
}

/*  Gdk::EventConfigure
 */

inline GdkEventConfigure*
Xfc::Gdk::EventConfigure::gdk_event_configure() const
{
	return reinterpret_cast<GdkEventConfigure*>(boxed_);
}

inline int
Xfc::Gdk::EventConfigure::x() const
{
	return gdk_event_configure()->x;
}

inline int
Xfc::Gdk::EventConfigure::y() const
{
	return gdk_event_configure()->y;
}

inline int
Xfc::Gdk::EventConfigure::width() const
{
	return gdk_event_configure()->width;
}

inline int
Xfc::Gdk::EventConfigure::height() const
{
	return gdk_event_configure()->height;
}

/*  Gdk::EventProperty
 */

inline GdkEventProperty*
Xfc::Gdk::EventProperty::gdk_event_property() const
{
	return reinterpret_cast<GdkEventProperty*>(boxed_);
}

inline Xfc::Gdk::Atom
Xfc::Gdk::EventProperty::atom() const
{
	return gdk_event_property()->atom;
}

inline unsigned int
Xfc::Gdk::EventProperty::time() const
{
	return gdk_event_property()->time;
}

inline Xfc::Gdk::PropertyState
Xfc::Gdk::EventProperty::state() const
{
	return (PropertyState)gdk_event_property()->state;
}

/*  Gdk::EventSelection
 */

inline GdkEventSelection*
Xfc::Gdk::EventSelection::gdk_event_selection() const
{
	return reinterpret_cast<GdkEventSelection*>(boxed_);
}

inline Xfc::Gdk::Atom
Xfc::Gdk::EventSelection::selection() const
{
	return gdk_event_selection()->selection;
}

inline Xfc::Gdk::Atom
Xfc::Gdk::EventSelection::target() const
{
	return gdk_event_selection()->target;
}

inline Xfc::Gdk::Atom
Xfc::Gdk::EventSelection::property() const
{
	return gdk_event_selection()->property;
}

inline unsigned int
Xfc::Gdk::EventSelection::time() const
{
	return gdk_event_selection()->time;
}

inline GdkNativeWindow
Xfc::Gdk::EventSelection::requestor() const
{
	return gdk_event_selection()->requestor;
}

/*  Gdk::EventOwnerChange
 */
 
inline GdkEventOwnerChange*
Xfc::Gdk::EventOwnerChange::gdk_event_owner_change() const
{
	return reinterpret_cast<GdkEventOwnerChange*>(boxed_);
}

inline GdkNativeWindow 
Xfc::Gdk::EventOwnerChange::owner() const
{
	return gdk_event_owner_change()->owner;
}
  
inline Xfc::Gdk::OwnerChange 
Xfc::Gdk::EventOwnerChange::reason() const
{
	return (OwnerChange)gdk_event_owner_change()->reason;
}
  
inline Xfc::Gdk::Atom 
Xfc::Gdk::EventOwnerChange::selection() const
{
	return gdk_event_owner_change()->selection;
}
	
inline unsigned int
Xfc::Gdk::EventOwnerChange::time() const
{
	return gdk_event_owner_change()->time;
}

inline unsigned int
Xfc::Gdk::EventOwnerChange::selection_time() const
{
	return gdk_event_owner_change()->selection_time;
}

/*  Gdk::EventProximity
 */

inline GdkEventProximity*
Xfc::Gdk::EventProximity::gdk_event_proximity() const
{
	return reinterpret_cast<GdkEventProximity*>(boxed_);
}

inline unsigned int
Xfc::Gdk::EventProximity::time() const
{
	return gdk_event_proximity()->time;
}

/*  Gdk::EventClient
 */

inline GdkEventClient*
Xfc::Gdk::EventClient::gdk_event_client() const
{
	return reinterpret_cast<GdkEventClient*>(boxed_);
}

inline Xfc::Gdk::Atom
Xfc::Gdk::EventClient::message_type() const
{
	return gdk_event_client()->message_type;
}

inline unsigned short
Xfc::Gdk::EventClient::data_format() const
{
	return gdk_event_client()->data_format;
}

inline const char*
Xfc::Gdk::EventClient::char_data() const
{
	return gdk_event_client()->data.b;
}

inline const short*
Xfc::Gdk::EventClient::short_data() const
{
	return gdk_event_client()->data.s;
}

inline const long*
Xfc::Gdk::EventClient::long_data() const
{
	return gdk_event_client()->data.l;
}

/*  Gdk::EventSetting
 */

inline GdkEventSetting*
Xfc::Gdk::EventSetting::gdk_event_setting() const
{
	return reinterpret_cast<GdkEventSetting*>(boxed_);
}

inline Xfc::Gdk::SettingAction
Xfc::Gdk::EventSetting::action() const
{
	return (SettingAction)gdk_event_setting()->action;
}

/*  Gdk::EventWindowState
 */

inline GdkEventWindowState*
Xfc::Gdk::EventWindowState::gdk_event_window_state() const
{
	return reinterpret_cast<GdkEventWindowState*>(boxed_);
}

inline Xfc::Gdk::WindowStateField
Xfc::Gdk::EventWindowState::changed_mask() const
{
	return (WindowStateField)gdk_event_window_state()->changed_mask;
}

inline Xfc::Gdk::WindowStateField
Xfc::Gdk::EventWindowState::new_window_state() const
{
	return (WindowStateField)gdk_event_window_state()->new_window_state;
}

/*  Gdk::EventDND
 */

inline GdkEventDND*
Xfc::Gdk::EventDND::gdk_event_dnd() const
{
	return reinterpret_cast<GdkEventDND*>(boxed_);
}

inline unsigned int
Xfc::Gdk::EventDND::time() const
{
	return gdk_event_dnd()->time;
}

inline short
Xfc::Gdk::EventDND::x_root() const
{
	return gdk_event_dnd()->x_root;
}

inline short
Xfc::Gdk::EventDND::y_root() const
{
	return gdk_event_dnd()->y_root;
}

