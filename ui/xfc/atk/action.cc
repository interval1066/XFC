/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  action.cc - AtkAction C++ wrapper implementation
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
 
#include "action.hh"

using namespace Xfc;

/*  Atk::Action
 */

Atk::Action::Action()
{
}
	
Atk::Action::~Action()
{
}
	
inline String
Atk::Action::get_description(int i) const
{
	return atk_action_get_description(atk_action(), i);
}

inline String
Atk::Action::get_name(int i) const
{
	return atk_action_get_name(atk_action(), i);
}

inline String
Atk::Action::get_keybinding(int i) const
{
	return atk_action_get_keybinding(atk_action(), i);
}

inline String
Atk::Action::get_localized_name(int i) const
{
	return atk_action_get_localized_name(atk_action(), i);
}

