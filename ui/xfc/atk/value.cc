/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  value.cc - AtkValue C++ wrapper implementation
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
 
#include "value.hh"
#include "xfc/glib/value.hh"

using namespace Xfc;

/*  Atk::Value
 */

Atk::Value::Value()
{
}

Atk::Value::~Value()
{
}
	
void
Atk::Value::get_current_value(G::Value& value) const
{
	atk_value_get_current_value(atk_value(), value.g_value());
}

void
Atk::Value::get_maximum_value(G::Value& value) const
{
	atk_value_get_maximum_value(atk_value(), value.g_value());
}

void 
Atk::Value::get_minimum_value(G::Value& value) const
{
	atk_value_get_minimum_value(atk_value(), value.g_value());
}

bool
Atk::Value::set_current_value(const G::Value& value)
{
	return atk_value_set_current_value(atk_value(), value.g_value());
}

