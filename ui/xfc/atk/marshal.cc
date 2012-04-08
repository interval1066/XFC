/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  marshal.cc - ATK GObject signal callback functions.
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

#include <sigc++/sigc++.h>
#include "private/marshal.hh"
#include "xfc/glib/private/connection.hh"
#include "xfc/utfstring.hh"

using namespace Xfc;

/*  Atk::Marshal::void_int_pvoid_callback
 */

void
Atk::Marshal::void_int_pvoid_callback(void *data, unsigned int arg1, void *arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, unsigned int, void*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg1, arg2);
	}
}

/*  Atk::Marshal::void_patkpropertyvalues_callback
 */
void
Atk::Marshal::void_patkpropertyvalues_callback(void *data, AtkPropertyValues *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, AtkPropertyValues*> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg);
	}
}

/*  Atk::Marshal::void_string_bool_callback
 */
void
Atk::Marshal::void_string_bool_callback(void *data, const char *arg1, bool arg2)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, const String&, bool> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		String s(arg1);
		slot(s, arg2);
	}
}

/*  Atk::Marshal::void_ppvoid_callback
 */
void
Atk::Marshal::void_ppvoid_callback(void *data, void **arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, void**> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg);
	}
}

