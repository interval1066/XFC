/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  stateset.inl - Atk::StateSet inline functions
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

inline AtkStateSet*
Xfc::Atk::StateSet::atk_state_set() const
{
	return reinterpret_cast<AtkStateSet*>(instance_);
}

inline Xfc::Atk::StateSet::operator AtkStateSet* () const
{
	return this ? atk_state_set() : 0;
}

inline bool
Xfc::Atk::StateSet::is_empty() const
{
	return atk_state_set_is_empty(atk_state_set());
}

inline bool
Xfc::Atk::StateSet::contains_state(StateType type) const
{
	return atk_state_set_contains_state(atk_state_set(), (AtkStateType)type);
}

inline bool
Xfc::Atk::StateSet::add_state(StateType type)
{
	return atk_state_set_add_state(atk_state_set(), (AtkStateType)type);
}

inline void
Xfc::Atk::StateSet::clear_states()
{
	atk_state_set_clear_states(atk_state_set());
}

inline bool
Xfc::Atk::StateSet::remove_state(StateType type)
{
	return atk_state_set_remove_state(atk_state_set(), (AtkStateType)type);
}

