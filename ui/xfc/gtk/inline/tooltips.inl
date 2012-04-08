/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  tooltips.inl - Gtk::Tooltips inline functions
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

/*  Gtk::TooltipsData
 */

inline GtkTooltipsData*
Xfc::Gtk::TooltipsData::gtk_tooltips_data() const
{
	return const_cast<GtkTooltipsData*>(&data_);
}

/*  Gtk::Tooltips
 */

inline GtkTooltips*
Xfc::Gtk::Tooltips::gtk_tooltips() const
{
	return reinterpret_cast<GtkTooltips*>(instance_);
}

inline Xfc::Gtk::Tooltips::operator GtkTooltips* () const
{
	return this ? gtk_tooltips() : 0;
}

inline bool
Xfc::Gtk::Tooltips::is_enabled() const
{
	return gtk_tooltips()->enabled;
}

inline void
Xfc::Gtk::Tooltips::enable()
{
	gtk_tooltips_enable(gtk_tooltips());
}

inline void
Xfc::Gtk::Tooltips::disable()
{
	gtk_tooltips_disable(gtk_tooltips());
}

inline void
Xfc::Gtk::Tooltips::force_window()
{
	gtk_tooltips_force_window(gtk_tooltips());
}

