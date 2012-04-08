/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  displaymanagersignals.cc - Gdk::DisplayManager virtual signal handlers
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
 
#include "displaymanager.hh"
#include "displaymanagersignals.hh"
#include "private/displaymanagerclass.hh"

using namespace Xfc;

/*  Gdk::DisplayManagerSignals
 */

Gdk::DisplayManagerSignals::DisplayManagerSignals(DisplayManager *display_manager)
: G::ObjectSignals(display_manager)
{
}

Gdk::DisplayManagerSignals::~DisplayManagerSignals()
{
}
	
void
Gdk::DisplayManagerSignals::on_display_opened(Display& display)
{
	GdkDisplayManagerClass *g_class = DisplayManagerClass::get_parent_class(instance_);
	if (g_class && g_class->display_opened)
		g_class->display_opened((GdkDisplayManager*)instance_, display.gdk_display());
}

