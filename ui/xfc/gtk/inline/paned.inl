/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  paned.inl - Gtk::Paned, Gtk::HPaned and Gtk::VPaned inline functions
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

/*  Gtk::Paned
 */

inline GtkPaned*
Xfc::Gtk::Paned::gtk_paned() const
{
	return reinterpret_cast<GtkPaned*>(instance_);
}

inline Xfc::Gtk::Paned::operator GtkPaned* () const
{
	return this ? gtk_paned() : 0;
}

inline int
Xfc::Gtk::Paned::get_position() const
{
	return gtk_paned_get_position(gtk_paned());
}

inline void
Xfc::Gtk::Paned::set_position(int position)
{
	gtk_paned_set_position(gtk_paned(), position);
}

/*  Gtk::HPaned
 */

inline GtkHPaned*
Xfc::Gtk::HPaned::gtk_hpaned() const
{
	return reinterpret_cast<GtkHPaned*>(instance_);
}

inline Xfc::Gtk::HPaned::operator GtkHPaned* () const
{
	return this ? gtk_hpaned() : 0;
}

/*  Gtk::VPaned
 */

inline GtkVPaned*
Xfc::Gtk::VPaned::gtk_vpaned() const
{
	return reinterpret_cast<GtkVPaned*>(instance_);
}

inline Xfc::Gtk::VPaned::operator GtkVPaned* () const
{
	return this ? gtk_vpaned() : 0;
}

