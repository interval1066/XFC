/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  misc.inl - Gtk::Misc inline functions
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

inline GtkMisc*
Xfc::Gtk::Misc::gtk_misc() const
{
	return reinterpret_cast<GtkMisc*>(instance_);
}

inline Xfc::Gtk::Misc::operator GtkMisc* () const
{
	return this ? gtk_misc() : 0;
}

inline void
Xfc::Gtk::Misc::get_alignment(float *xalign, float *yalign)
{
	gtk_misc_get_alignment(gtk_misc(), xalign, yalign);
}

inline void
Xfc::Gtk::Misc::get_padding(int *xpad, int *ypad)
{
	gtk_misc_get_padding(gtk_misc(), xpad, ypad);
}

inline void
Xfc::Gtk::Misc::set_alignment(float xalign, float yalign)
{
	gtk_misc_set_alignment(gtk_misc(), xalign, yalign);
}

inline void
Xfc::Gtk::Misc::set_padding(int xpad, int ypad)
{
	gtk_misc_set_padding(gtk_misc(), xpad, ypad);
}

