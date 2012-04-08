/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  curve.inl - Gtk::Curve inline functions
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

inline GtkCurve*
Xfc::Gtk::Curve::gtk_curve() const
{
	return reinterpret_cast<GtkCurve*>(instance_);
}

inline Xfc::Gtk::Curve::operator GtkCurve* () const
{
	return this ? gtk_curve() : 0;
}

inline void
Xfc::Gtk::Curve::get_vector(int count, float data[]) const
{
	gtk_curve_get_vector(gtk_curve(), count, data);
}

inline void
Xfc::Gtk::Curve::reset()
{
	gtk_curve_reset(gtk_curve());
}

inline void
Xfc::Gtk::Curve::set_gamma(float gamma)
{
	gtk_curve_set_gamma(gtk_curve(), gamma);
}

inline void
Xfc::Gtk::Curve::set_range(float min_x, float max_x, float min_y, float max_y)
{
	gtk_curve_set_range(gtk_curve(), min_x, max_x, min_y, max_y);
}

inline void
Xfc::Gtk::Curve::set_vector(int count, float data[])
{
	gtk_curve_set_vector(gtk_curve(), count, data);
}

inline void
Xfc::Gtk::Curve::set_curve_type(CurveType type)
{
	gtk_curve_set_curve_type(gtk_curve(), (GtkCurveType)type);
}

inline const Xfc::Gtk::Curve::CurveTypeChangedSignalProxy
Xfc::Gtk::Curve::signal_curve_type_changed()
{
	return CurveTypeChangedSignalProxy(this, &curve_type_changed_signal);
}

