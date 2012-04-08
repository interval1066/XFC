/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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

#include <gdk/gdk.h>
#include <sigc++/sigc++.h>
#include "private/marshal.hh"
#include "display.hh"
#include "xfc/glib/private/connection.hh"

using namespace Xfc;

/*  Gdk::Marshal::void_display_callback
 */

void
Gdk::Marshal::void_display_callback(void *data, GdkDisplay *arg)
{
	G::Connection *c = static_cast<G::Connection*>(data);
	if (c)
	{
		typedef	sigc::slot<void, Display&> SlotType;
		SlotType& slot = static_cast<SlotType&>(c->slot_);
		slot(*G::Object::wrap<Display>(arg));
	}
}
