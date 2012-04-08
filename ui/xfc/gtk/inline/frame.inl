/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  frame.inl - Gtk::Frame inline functions
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

inline GtkFrame*
Xfc::Gtk::Frame::gtk_frame() const
{
	return reinterpret_cast<GtkFrame*>(instance_);
}

inline Xfc::Gtk::Frame::operator GtkFrame* () const
{
	return this ? gtk_frame() : 0;
}

inline void
Xfc::Gtk::Frame::get_label_align(float *xalign, float *yalign) const
{
	return gtk_frame_get_label_align(gtk_frame(), xalign, yalign);
}

inline Xfc::Gtk::ShadowType
Xfc::Gtk::Frame::get_shadow_type() const
{
	return (ShadowType)gtk_frame_get_shadow_type(gtk_frame());
}

inline void
Xfc::Gtk::Frame::remove_label()
{
	gtk_frame_set_label(gtk_frame(), 0);
}

inline void
Xfc::Gtk::Frame::set_label(const char *label)
{
	gtk_frame_set_label(gtk_frame(), label);
}

inline void
Xfc::Gtk::Frame::set_label_align(float xalign, float yalign)
{
	gtk_frame_set_label_align(gtk_frame(), xalign, yalign);
}

inline void
Xfc::Gtk::Frame::set_shadow_type(ShadowType type)
{
	gtk_frame_set_shadow_type(gtk_frame(), (GtkShadowType)type);
}

