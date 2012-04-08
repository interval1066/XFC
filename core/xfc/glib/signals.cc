/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  signals.cc - C++ GTK+ signal implementation
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

#include "type.hh"
#include "private/connection.hh"

using namespace Xfc;

/*  G::SignalBase
 */

G::SignalBase::SignalBase(const char *name, GCallback callback)
: name_(name), callback_(callback)
{
}

G::SignalBase::~SignalBase()
{
}

void
G::SignalBase::connect(TypeInstance *instance, const SlotBase& slot,  const char *detail, bool after) const
{
	g_return_if_fail(instance != 0);
	Connection *c = new Connection((GObject*)instance->g_type_instance(), slot);
	GClosure* closure = g_cclosure_new_swap(callback_, c, (GClosureNotify)&Connection::destroy_handler);
	const char *detailed_signal = detail ? g_strjoin("::", name_, detail, 0) : name_;
	c->connect_id_ = g_signal_connect_closure(c->object_, detailed_signal, closure, after);
}

void
G::SignalBase::stop_emission(TypeInstance *instance)
{
	g_signal_stop_emission_by_name(instance->g_type_instance(), name_);
}

