/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  sizegroup.inl - Gtk::SizeGroup inline functions
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

inline GtkSizeGroup*
Xfc::Gtk::SizeGroup::gtk_size_group() const
{
	return reinterpret_cast<GtkSizeGroup*>(instance_);
}

inline Xfc::Gtk::SizeGroup::operator GtkSizeGroup* () const
{
	return this ? gtk_size_group() : 0;
}

inline Xfc::Gtk::SizeGroupMode
Xfc::Gtk::SizeGroup::get_mode() const
{
	return (SizeGroupMode)gtk_size_group_get_mode(gtk_size_group());
}

inline void
Xfc::Gtk::SizeGroup::set_mode(SizeGroupMode mode)
{
	gtk_size_group_set_mode(gtk_size_group(), (GtkSizeGroupMode)mode);
}

