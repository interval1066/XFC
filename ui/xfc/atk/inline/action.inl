/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  action.inl - Atk::Action inline functions
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

inline AtkAction*
Xfc::Atk::Action::atk_action() const
{
	return reinterpret_cast<AtkAction*>(instance_);
}

inline Xfc::Atk::Action::operator AtkAction* () const
{
	return this ? atk_action() : 0;
}

inline int
Xfc::Atk::Action::get_n_actions() const
{
	return atk_action_get_n_actions((AtkAction*)instance_);
}

inline bool
Xfc::Atk::Action::do_action(int i)
{
	return atk_action_do_action(atk_action(), i);
}

inline bool
Xfc::Atk::Action::set_description(int i, const char *desc)
{
	return atk_action_set_description(atk_action(), i, desc);
}

