/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  connection.cc - Connection object for managing the connection between a sigc::slot and a G::Signal.
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

#include <glib-object.h>
#include <sigc++/sigc++.h>
#include "private/connection.hh"

using namespace Xfc;

/*  G::Connection
 */

G::Connection::Connection(GObject *object, const sigc::slot_base& slot)
: sigc::connection(const_cast<sigc::slot_base&>(slot)), slot_(slot)
{
	object_ = object;
	connect_id_ = 0; 
	slot_.add_destroy_notify_callback(this, &notify_handler);
}

G::Connection::~Connection()
{
	slot_.remove_destroy_notify_callback(this);
}

void*
G::Connection::notify_handler(void *data)
{
	Connection *c = static_cast<Connection*>(data);
	if (c)
	{
		if (c->object_)
		{
			GObject *tmp = c->object_;
			c->object_ = 0;

			if (g_signal_handler_is_connected(tmp, c->connect_id_))
				g_signal_handler_disconnect(tmp, c->connect_id_);
		}
		c->connect_id_ = 0;
	}
	return 0;
}

void
G::Connection::destroy_handler(void *data)
{
	Connection *c = static_cast<Connection*>(data);
	if (c)
	{
		GObject *tmp = c->object_;
		c->object_ = 0;

		if (tmp)
			c->notify(data);

		delete c;
	}
}

