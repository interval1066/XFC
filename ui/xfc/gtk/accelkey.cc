/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  accelkey.cc - GtkAccelKey C++ wrapper implementation
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

#include "accelkey.hh"

using namespace Xfc;

/*  Gtk::AccelKey
 */

Gtk::AccelKey::AccelKey()
{
	set(0, 0, 0);
}

Gtk::AccelKey::AccelKey(const char *accelerator, AccelFlagsField accel_flags)
{
	set(accelerator, accel_flags);
}

Gtk::AccelKey::AccelKey(const String& accelerator, AccelFlagsField accel_flags)
{
	set(accelerator.c_str(), accel_flags);
}

Gtk::AccelKey::AccelKey(unsigned int accel_key, Gdk::ModifierTypeField accel_mods, AccelFlagsField accel_flags)
{
	set(accel_key, accel_mods, accel_flags);
}

Gtk::AccelKey::AccelKey(const AccelKey& src)
{
	key_ = src.key_;
}

Gtk::AccelKey&
Gtk::AccelKey::operator=(const AccelKey& src)
{
	key_ = src.key_;
	return *this;
}

void
Gtk::AccelKey::set(const char *accelerator, AccelFlagsField accel_flags)
{
	gtk_accelerator_parse(accelerator, &key_.accel_key, &key_.accel_mods);
	key_.accel_flags = accel_flags;
}

void
Gtk::AccelKey::set(const String& accelerator, AccelFlagsField accel_flags)
{
	set(accelerator.c_str(), accel_flags);
}

void
Gtk::AccelKey::set(unsigned int accel_key, Gdk::ModifierTypeField accel_mods, AccelFlagsField accel_flags)
{
	key_.accel_key = accel_key;
	key_.accel_mods = (GdkModifierType)accel_mods;
	key_.accel_flags = accel_flags;
}

