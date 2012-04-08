/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  progressbar.inl - Gtk::ProgressBar inline functions
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

inline GtkProgressBar*
Xfc::Gtk::ProgressBar::gtk_progress_bar() const
{
	return reinterpret_cast<GtkProgressBar*>(instance_);
}

inline Xfc::Gtk::ProgressBar::operator GtkProgressBar* () const
{
	return this ? gtk_progress_bar() : 0;
}

inline double
Xfc::Gtk::ProgressBar::get_fraction() const
{
	return gtk_progress_bar_get_fraction(gtk_progress_bar());
}

inline double
Xfc::Gtk::ProgressBar::get_pulse_step() const
{
	return gtk_progress_bar_get_pulse_step(gtk_progress_bar());
}

inline Xfc::Gtk::ProgressBarOrientation
Xfc::Gtk::ProgressBar::get_orientation() const
{
	return (ProgressBarOrientation)gtk_progress_bar_get_orientation(gtk_progress_bar());
}

inline Xfc::Pango::EllipsizeMode 
Xfc::Gtk::ProgressBar::get_ellipsize() const
{
	return (Pango::EllipsizeMode)gtk_progress_bar_get_ellipsize(gtk_progress_bar());
}

inline void
Xfc::Gtk::ProgressBar::pulse()
{
	gtk_progress_bar_pulse(gtk_progress_bar());
}

inline void
Xfc::Gtk::ProgressBar::set_text(const char *text)
{
	gtk_progress_bar_set_text(gtk_progress_bar(), text);
}

inline void
Xfc::Gtk::ProgressBar::set_fraction(double fraction)
{
	gtk_progress_bar_set_fraction(gtk_progress_bar(), fraction);
}

inline void
Xfc::Gtk::ProgressBar::set_pulse_step(double fraction)
{
	gtk_progress_bar_set_pulse_step(gtk_progress_bar(), fraction);
}

inline void
Xfc::Gtk::ProgressBar::set_orientation(ProgressBarOrientation orientation)
{
	gtk_progress_bar_set_orientation(gtk_progress_bar(), (GtkProgressBarOrientation)orientation);
}

inline void 
Xfc::Gtk::ProgressBar::set_ellipsize(Pango::EllipsizeMode mode)
{
	gtk_progress_bar_set_ellipsize(gtk_progress_bar(), (PangoEllipsizeMode)mode);
}

