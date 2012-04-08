/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  separator.inl - Gtk::Separator, Gtk::HSeparator and Gtk::VSeparator inline functions
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

/*  Gtk::Separator
 */

inline GtkSeparator*
Xfc::Gtk::Separator::gtk_separator() const
{
	return reinterpret_cast<GtkSeparator*>(instance_);
}

inline Xfc::Gtk::Separator::operator GtkSeparator* () const
{
	return this ? gtk_separator() : 0;
}

/*  Gtk::HSeparator
 */

inline GtkHSeparator*
Xfc::Gtk::HSeparator::gtk_hseparator() const
{
	return reinterpret_cast<GtkHSeparator*>(instance_);
}

inline Xfc::Gtk::HSeparator::operator GtkHSeparator* () const
{
	return this ? gtk_hseparator() : 0;
}

/*  Gtk::VSeparator
 */

inline GtkVSeparator*
Xfc::Gtk::VSeparator::gtk_vseparator() const
{
	return reinterpret_cast<GtkVSeparator*>(instance_);
}

inline Xfc::Gtk::VSeparator::operator GtkVSeparator* () const
{
	return this ? gtk_vseparator() : 0;
}

