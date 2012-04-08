/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  input.inl - Gdk::Device inline functions
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

inline GdkDevice*
Xfc::Gdk::Device::gdk_device() const
{
	return reinterpret_cast<GdkDevice*>(instance_);
}

inline Xfc::Gdk::Device::operator GdkDevice* () const
{
	return this ? gdk_device() : 0;
}

inline Xfc::Gdk::InputSource
Xfc::Gdk::Device::source() const
{
	return (InputSource)gdk_device()->source;
}

inline Xfc::Gdk::InputMode
Xfc::Gdk::Device::mode() const
{
	return (InputMode)gdk_device()->mode;
}

inline bool
Xfc::Gdk::Device::has_cursor() const
{
	return gdk_device()->has_cursor;
}

inline void
Xfc::Gdk::Device::free_history(GdkTimeCoord **events, int n_events)
{
	gdk_device_free_history(events, n_events);
}

inline bool
Xfc::Gdk::Device::get_axis(double *axes, AxisUse use, double *value) const
{
	return gdk_device_get_axis(gdk_device(), axes, (GdkAxisUse)use, value) != 0;
}

inline void
Xfc::Gdk::Device::set_source(InputSource source)
{
	gdk_device_set_source(gdk_device(), (GdkInputSource)source);
}

inline bool
Xfc::Gdk::Device::set_mode(InputMode mode)
{
	return gdk_device_set_mode(gdk_device(), (GdkInputMode)mode);
}

inline void
Xfc::Gdk::Device::set_key(unsigned int index, unsigned int keyval, ModifierTypeField modifiers)
{
	gdk_device_set_key(gdk_device(), index, keyval, (GdkModifierType)modifiers);
}

inline void
Xfc::Gdk::Device::set_axis_use(unsigned int index, AxisUse use)
{
	gdk_device_set_axis_use(gdk_device(), index, (GdkAxisUse)use);
}

