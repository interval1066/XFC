/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  scale.inl - Gtk::Scale, Gtk::HScale and Gtk::VScale inline functions
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

/*  Gtk::Scale
 */

inline GtkScale*
Xfc::Gtk::Scale::gtk_scale() const
{
	return reinterpret_cast<GtkScale*>(instance_);
}

inline Xfc::Gtk::Scale::operator GtkScale* () const
{
	return this ? gtk_scale() : 0;
}

inline int
Xfc::Gtk::Scale::get_digits() const
{
	return gtk_scale_get_digits(gtk_scale());
}

inline bool
Xfc::Gtk::Scale::get_draw_value() const
{
	return gtk_scale_get_draw_value(gtk_scale());
}

inline Xfc::Gtk::PositionType
Xfc::Gtk::Scale::get_value_pos() const
{
	return (PositionType)gtk_scale_get_value_pos(gtk_scale());
}

inline void 
Xfc::Gtk::Scale::get_layout_offsets(int *x, int *y) const
{
	gtk_scale_get_layout_offsets(gtk_scale(), x, y);
}

inline void
Xfc::Gtk::Scale::set_digits(int digits)
{
	gtk_scale_set_digits(gtk_scale(), digits);
}

inline void
Xfc::Gtk::Scale::set_draw_value(bool draw_value)
{
	gtk_scale_set_draw_value(gtk_scale(), draw_value);
}

inline void
Xfc::Gtk::Scale::set_value_pos(PositionType pos)
{
	gtk_scale_set_value_pos(gtk_scale(), (GtkPositionType)pos);
}

inline const Xfc::Gtk::Scale::FormatValueSignalProxy 
Xfc::Gtk::Scale::signal_format_value()
{
	return FormatValueSignalProxy(this, &format_value_signal); 
}

/*  Gtk::HScale
 */

inline GtkHScale*
Xfc::Gtk::HScale::gtk_hscale() const
{
	return reinterpret_cast<GtkHScale*>(instance_);
}

inline Xfc::Gtk::HScale::operator GtkHScale* () const
{
	return this ? gtk_hscale() : 0;
}

/*  Gtk::VScale
 */

inline GtkVScale*
Xfc::Gtk::VScale::gtk_vscale() const
{
	return reinterpret_cast<GtkVScale*>(instance_);
}

inline Xfc::Gtk::VScale::operator GtkVScale* () const
{
	return this ? gtk_vscale() : 0;
}

