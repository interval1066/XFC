/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  scrollbar.inl - GtkScrollbar, GtkHScrollbar and GtkVScrollbar inline functions
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

/*  Gtk::Scrollbar
 */

inline GtkScrollbar*
Xfc::Gtk::Scrollbar::gtk_scrollbar() const
{
	return reinterpret_cast<GtkScrollbar*>(instance_);
}

inline Xfc::Gtk::Scrollbar::operator GtkScrollbar* () const
{
	return this ? gtk_scrollbar() : 0;
}

/*  Gtk::HScrollbar
 */

inline GtkHScrollbar*
Xfc::Gtk::HScrollbar::gtk_hscrollbar() const
{
	return reinterpret_cast<GtkHScrollbar*>(instance_);
}

inline Xfc::Gtk::HScrollbar::operator GtkHScrollbar* () const
{
	return this ? gtk_hscrollbar() : 0;
}

/*  Gtk::VScrollbar
 */

inline GtkVScrollbar*
Xfc::Gtk::VScrollbar::gtk_vscrollbar() const
{
	return reinterpret_cast<GtkVScrollbar*>(instance_);
}

inline Xfc::Gtk::VScrollbar::operator GtkVScrollbar* () const
{
	return this ? gtk_vscrollbar() : 0;
}

