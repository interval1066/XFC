/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  item.inl - Gtk::Item inline functions
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

inline GtkItem*
Xfc::Gtk::Item::gtk_item() const
{
	return reinterpret_cast<GtkItem*>(instance_);
}

inline Xfc::Gtk::Item::operator GtkItem* () const
{
	return this ? gtk_item() : 0;
}

inline void
Xfc::Gtk::Item::select()
{
	gtk_item_select(gtk_item());
}

inline void
Xfc::Gtk::Item::deselect()
{
	gtk_item_deselect(gtk_item());
}

inline void
Xfc::Gtk::Item::toggle()
{
	gtk_item_toggle(gtk_item());
}

inline const Xfc::Gtk::Item::SelectSignalProxy 
Xfc::Gtk::Item::signal_select()
{
	return SelectSignalProxy(this, &select_signal);
}


inline const Xfc::Gtk::Item::DeselectSignalProxy 
Xfc::Gtk::Item::signal_deselect()
{
	return DeselectSignalProxy(this, &deselect_signal);
}

inline const Xfc::Gtk::Item::ToggleSignalProxy 
Xfc::Gtk::Item::signal_toggle()
{
	return ToggleSignalProxy(this, &toggle_signal);
}

