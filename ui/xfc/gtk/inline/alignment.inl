/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  alignment.inl - Gtk::Alignment inline functions
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

inline GtkAlignment*
Xfc::Gtk::Alignment::gtk_alignment() const
{
	return reinterpret_cast<GtkAlignment*>(instance_);
}

inline Xfc::Gtk::Alignment::operator GtkAlignment* () const
{
	return this ? gtk_alignment() : 0;
}

inline void
Xfc::Gtk::Alignment::get_padding(unsigned int *top, unsigned int *bottom, unsigned int *left, unsigned int *right) const
{
	gtk_alignment_get_padding(gtk_alignment(), top, bottom, left, right);
}

inline void
Xfc::Gtk::Alignment::set_padding(unsigned int top, unsigned int bottom, unsigned int left, unsigned int right)
{
	gtk_alignment_set_padding(gtk_alignment(), top, bottom, left, right);
}

inline void
Xfc::Gtk::Alignment::set(float xalign, float yalign, float xscale, float yscale)
{
	gtk_alignment_set(gtk_alignment(), xalign, yalign, xscale, yscale);
}

