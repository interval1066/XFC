/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  style.inl - Gtk::Style inline functions
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

inline GtkStyle*
Xfc::Gtk::Style::gtk_style() const
{
	return reinterpret_cast<GtkStyle*>(instance_);
}

inline Xfc::Gtk::Style::operator GtkStyle* () const
{
	return this ? gtk_style() : 0;
}

inline int 
Xfc::Gtk::Style::xthickness() const
{
	return gtk_style()->xthickness;
}

inline int 
Xfc::Gtk::Style::ythickness() const
{
	return gtk_style()->ythickness;
}

inline void 
Xfc::Gtk::Style::set_xthickness(int size)
{
	gtk_style()->xthickness = size;
}

inline void 
Xfc::Gtk::Style::set_ythickness(int size)
{
	gtk_style()->ythickness = size;
}

