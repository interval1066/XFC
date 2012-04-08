/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  layout.inl - Gtk::Layout inline functions
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

inline GtkLayout*
Xfc::Gtk::Layout::gtk_layout() const
{
	return reinterpret_cast<GtkLayout*>(instance_);
}

inline Xfc::Gtk::Layout::operator GtkLayout* () const
{
	return this ? gtk_layout() : 0;
}

inline void
Xfc::Gtk::Layout::get_size(unsigned int *width, unsigned int *height)
{
	gtk_layout_get_size(gtk_layout(), width, height);
}

inline void
Xfc::Gtk::Layout::set_size(unsigned int width, unsigned int height)
{
	gtk_layout_set_size(gtk_layout(), width, height);
}

inline const Xfc::Gtk::Layout::SetScrollAdjustmentsSignalProxy
Xfc::Gtk::Layout::signal_set_scroll_adjustments()
{
	return SetScrollAdjustmentsSignalProxy(this, &set_scroll_adjustments_signal);
}

