/*  XFC: Xfce Foundation Classes (Core Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  connection.hh - Private interface
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

#ifndef XFC_G_CONNECTION_HH
#define XFC_G_CONNECTION_HH

#ifndef __GLIB_GOBJECT_H__
#include <glib-object.h>
#endif

namespace Xfc {

namespace G {

// Connection manages the connection between a sigc::slot and a G::Signal.

struct Connection : public sigc::connection
{
	GObject *object_;
	unsigned long connect_id_;
	sigc::slot_base slot_;

	Connection(GObject *object, const sigc::slot_base& slot);
	~Connection();

	static void* notify_handler(void *data);
	static void destroy_handler(void *data);
};

} // namespace G

} // namespace Xfc

#endif // XFC_G_CONNECTION_HH

