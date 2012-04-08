/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  ruler.inl - Gtk::Ruler, Gtk::HRuler and Gtk::VRuler inline functions
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

/*  Gtk::Ruler
 */

inline GtkRuler*
Xfc::Gtk::Ruler::gtk_ruler() const
{
	return reinterpret_cast<GtkRuler*>(instance_);
}

inline Xfc::Gtk::Ruler::operator GtkRuler* () const
{
	return this ? gtk_ruler() : 0;
}

inline Xfc::Gtk::MetricType
Xfc::Gtk::Ruler::get_metric() const
{
	return (MetricType)gtk_ruler_get_metric(gtk_ruler());
}

inline double
Xfc::Gtk::Ruler::get_lower() const
{
	return gtk_ruler()->lower;
}

inline double
Xfc::Gtk::Ruler::get_upper() const
{
	return gtk_ruler()->upper;
}

inline double
Xfc::Gtk::Ruler::get_position() const
{
	return gtk_ruler()->position;
}

inline void
Xfc::Gtk::Ruler::get_range(double *lower, double *upper, double *position, double *max_size)
{
	gtk_ruler_get_range(gtk_ruler(), lower, upper, position, max_size);
}

inline void
Xfc::Gtk::Ruler::set_metric(MetricType metric)
{
	gtk_ruler_set_metric(gtk_ruler(), (GtkMetricType)metric);
}

inline void
Xfc::Gtk::Ruler::set_range(double lower, double upper, double position, double max_size)
{
	gtk_ruler_set_range(gtk_ruler(), lower, upper, position, max_size);
}

inline void
Xfc::Gtk::Ruler::draw_ticks()
{
	gtk_ruler_draw_ticks(gtk_ruler());
}

inline void
Xfc::Gtk::Ruler::draw_pos()
{
	gtk_ruler_draw_pos(gtk_ruler());
}

/*  Gtk::HRuler
 */

inline GtkHRuler*
Xfc::Gtk::HRuler::gtk_hruler() const
{
	return reinterpret_cast<GtkHRuler*>(instance_);
}

inline Xfc::Gtk::HRuler::operator GtkHRuler* () const
{
	return this ? gtk_hruler() : 0;
}

/*  Gtk::VRuler
 */

inline GtkVRuler*
Xfc::Gtk::VRuler::gtk_vruler() const
{
	return reinterpret_cast<GtkVRuler*>(instance_);
}

inline Xfc::Gtk::VRuler::operator GtkVRuler* () const
{
	return this ? gtk_vruler() : 0;
}

