/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  marshal.cc - GObject signal callback functions.
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
#include "private/connection.hh"

using namespace Xfc;

/*  G::Marshal::void_callback
 */

void
G::Marshal::void_callback(void *data)
{
	Connection *c = static_cast<Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot();
	}
}

/*  G::Marshal::void_bool_callback
 */

void
G::Marshal::void_bool_callback(void *data, bool arg)
{
	Connection *c = static_cast<Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, bool> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg);
	}
}

/*  G::Marshal::void_int_callback
 */

void
G::Marshal::void_int_callback(void *data, int arg)
{
	Connection *c = static_cast<Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg);
	}
}

/*  G::Marshal::void_int_int_callback
 */

void
G::Marshal::void_int_int_callback(void *data, int arg1, int arg2)
{
	Connection *c = static_cast<Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, int, int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg1, arg2);
	}
}

/*  G::Marshal::void_int_int_int_int_callback
 */

void
G::Marshal::void_int_int_int_int_callback(void *data, int arg1, int arg2, int arg3, int arg4)
{
	Connection *c = static_cast<Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, int, int, int, int> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(arg1, arg2, arg3, arg4);
	}
}

/*  G::Marshal::void_gparamspec_callback
 */

void
G::Marshal::void_gparamspec_callback(void *data, GParamSpec *pspec)
{
	typedef	sigc::slot<void, GParamSpec*> SlotType;
	Connection *c = static_cast<Connection*>(data);
	if (c)
	{
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(pspec);
	}
}

