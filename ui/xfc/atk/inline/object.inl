/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  object.inl - Atk::Object inline functions
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

inline AtkObject*
Xfc::Atk::Object::atk_object() const
{
	return reinterpret_cast<AtkObject*>(instance_);
}

inline Xfc::Atk::Object::operator AtkObject* () const
{
	return this ? atk_object() : 0;
}

inline int
Xfc::Atk::Object::get_n_accessible_children() const
{
	return atk_object_get_n_accessible_children(atk_object());
}

inline Xfc::Atk::Role
Xfc::Atk::Object::get_role() const
{
	return (Role)atk_object_get_role(atk_object());
}

inline int
Xfc::Atk::Object::get_index_in_parent() const
{
	return atk_object_get_index_in_parent(atk_object());
}

inline void
Xfc::Atk::Object::set_name(const char *name)
{
	atk_object_set_name(atk_object(), name);
}

inline void
Xfc::Atk::Object::set_description(const char *description)
{
	atk_object_set_description(atk_object(), description);
}

inline void
Xfc::Atk::Object::set_role(Role role)
{
	atk_object_set_role(atk_object(), (AtkRole)role);
}

inline void
Xfc::Atk::Object::notify_state_change(State state, bool value)
{
	atk_object_notify_state_change(atk_object(), state, value);
}

inline const Xfc::Atk::Object::ChildrenChangedSignalProxy
Xfc::Atk::Object::signal_children_changed()
{
	return ChildrenChangedSignalProxy(this, &children_changed_signal);
}

inline const Xfc::Atk::Object::FocusEventSignalProxy
Xfc::Atk::Object::signal_focus_event()
{
	return FocusEventSignalProxy(this, &focus_event_signal);
}

inline const Xfc::Atk::Object::PropertyChangeSignalProxy
Xfc::Atk::Object::signal_property_change()
{
	return PropertyChangeSignalProxy(this, &property_change_signal);
}

inline const Xfc::Atk::Object::StateChangeSignalProxy
Xfc::Atk::Object::signal_state_change()
{
	return StateChangeSignalProxy(this, &state_change_signal);
}

inline const Xfc::Atk::Object::VisibleDataChangedSignalProxy
Xfc::Atk::Object::signal_visible_data_changed()
{
	return VisibleDataChangedSignalProxy(this, &visible_data_changed_signal);
}

inline const Xfc::Atk::Object::ActiveDescendantChangedSignalProxy
Xfc::Atk::Object::signal_active_descendant_changed()
{
	return ActiveDescendantChangedSignalProxy(this, &active_descendant_changed_signal);
}

