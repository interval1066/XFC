/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  displaysignals.cc - Gdk::Display virtual signal handlers
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
 
#include "display.hh"
#include "displaysignals.hh"
#include "private/displayclass.hh"

using namespace Xfc;

/*  Gdk::DisplaySignals
 */

Gdk::DisplaySignals::DisplaySignals(Display *display)
: G::ObjectSignals(display)
{
}

Gdk::DisplaySignals::~DisplaySignals()
{
}
	
void
Gdk::DisplaySignals::on_closed(bool is_error)
{
	GdkDisplayClass *g_class = DisplayClass::get_parent_class(instance_);
	if (g_class && g_class->closed)
		g_class->closed((GdkDisplay*)instance_, is_error);
}

