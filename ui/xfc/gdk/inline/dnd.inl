/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  dnd.inl - Gdk::DragContext inline functions
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

inline GdkDragContext*
Xfc::Gdk::DragContext::gdk_drag_context() const
{
	return reinterpret_cast<GdkDragContext*>(instance_);
}

inline Xfc::Gdk::DragContext::operator GdkDragContext* () const
{
	return this ? gdk_drag_context() : 0;
}

inline bool
Xfc::Gdk::DragContext::is_source() const
{
	return gdk_drag_context()->is_source;
}

inline Xfc::Gdk::DragActionField
Xfc::Gdk::DragContext::actions() const
{
	return (DragActionField)gdk_drag_context()->actions;
}

inline Xfc::Gdk::DragActionField
Xfc::Gdk::DragContext::suggested_action() const
{
	return (DragActionField)gdk_drag_context()->suggested_action;
}

inline Xfc::Gdk::DragActionField
Xfc::Gdk::DragContext::action() const
{
	return (DragActionField)gdk_drag_context()->action;
}

inline unsigned int
Xfc::Gdk::DragContext::start_time() const
{
	return gdk_drag_context()->start_time;
}

inline Xfc::Gdk::Atom
Xfc::Gdk::DragContext::get_selection() const
{
	return  gdk_drag_get_selection(gdk_drag_context());
}

inline bool
Xfc::Gdk::DragContext::drag_drop_succeeded() const
{
	return gdk_drag_drop_succeeded(gdk_drag_context());
}

inline void
Xfc::Gdk::DragContext::drag_status(DragActionField action, unsigned int time)
{
	gdk_drag_status(gdk_drag_context(), (GdkDragAction)action, time);
}

inline void
Xfc::Gdk::DragContext::drop_reply(bool ok, unsigned int time)
{
	gdk_drop_reply(gdk_drag_context(), ok, time);
}

inline void
Xfc::Gdk::DragContext::drop_finish(bool success, unsigned int time)
{
	gdk_drop_finish(gdk_drag_context(), success, time);
}

inline void
Xfc::Gdk::DragContext::drag_drop(unsigned int time)
{
	gdk_drag_drop(gdk_drag_context(), time);
}

inline void
Xfc::Gdk::DragContext::drag_abort(unsigned int time)
{
	gdk_drag_abort(gdk_drag_context(), time);
}

inline void
Xfc::Gdk::DragContext::set_action(DragActionField action)
{
	gdk_drag_context()->action = (GdkDragAction)action;
}

