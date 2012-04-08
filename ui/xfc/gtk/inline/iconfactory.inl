/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  iconfactory.inl - Gtk::IconFactory inline functions
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

inline GtkIconFactory*
Xfc::Gtk::IconFactory::gtk_icon_factory() const
{
	return reinterpret_cast<GtkIconFactory*>(instance_);
}

inline Xfc::Gtk::IconFactory::operator GtkIconFactory* () const
{
	return this ? gtk_icon_factory() : 0;
}

inline void
Xfc::Gtk::IconFactory::add_default()
{
	gtk_icon_factory_add_default(gtk_icon_factory());
}

inline void
Xfc::Gtk::IconFactory::remove_default()
{
	gtk_icon_factory_remove_default(gtk_icon_factory());
}

