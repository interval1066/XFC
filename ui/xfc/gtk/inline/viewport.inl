/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  viewport.inl - Gtk::Viewport inline functions
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

inline GtkViewport*
Xfc::Gtk::Viewport::gtk_viewport() const
{
	return reinterpret_cast<GtkViewport*>(instance_);
}

inline Xfc::Gtk::Viewport::operator GtkViewport* () const
{
	return this ? gtk_viewport() : 0;
}

inline void
Xfc::Gtk::Viewport::set_shadow_type(ShadowType type)
{
	gtk_viewport_set_shadow_type(gtk_viewport(), (GtkShadowType)type);
}

inline const Xfc::Gtk::Viewport::SetScrollAdjustmentsSignalProxy
Xfc::Gtk::Viewport::signal_set_scroll_adjustments()
{
	return SetScrollAdjustmentsSignalProxy(this, &set_scroll_adjustments_signal);
}

