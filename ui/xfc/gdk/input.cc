/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  input.cc - GdkDevice C++ wrapper interface
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
 
#include "input.hh"
#include "display.hh"
#include "window.hh"

using namespace Xfc;

/*  Gdk::devices_list
 */
 
bool 
Gdk::devices_list(std::vector<Device*>& devices)
{
	Display *display = Display::get_default();
	return display->list_devices(devices);
}

/*  Gdk::Device
 */

Gdk::Device::Device(GdkDevice *device, bool owns_reference)
: G::Object((GObject*)device, owns_reference)
{
}
	
Gdk::Device::~Device()
{
}
	
String
Gdk::Device::name() const
{
	return gdk_device()->name;
}

void
Gdk::Device::get_state(Window& window, double *axes, ModifierTypeField *mask) const
{
	gdk_device_get_state(gdk_device(), window.gdk_window(), axes, (GdkModifierType*)mask);
}

bool
Gdk::Device::get_history(Window& window, unsigned long start, unsigned long stop, GdkTimeCoord ***events, int *n_events) const
{
	return gdk_device_get_history(gdk_device(), window.gdk_window(), start, stop, events, n_events);
}

Gdk::Device*
Gdk::Device::get_core_pointer(const Display *display)
{
	GdkDisplay *tmp_display = display ? display->gdk_display() : gdk_display_get_default();
	return G::Object::wrap<Device>(gdk_display_get_core_pointer(tmp_display));
}

