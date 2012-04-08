/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  cellrenderertoggle.inl - Gtk::CellRendererToggle inline functions
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

inline GtkCellRendererToggle*
Xfc::Gtk::CellRendererToggle::gtk_cell_renderer_toggle() const
{
	return reinterpret_cast<GtkCellRendererToggle*>(instance_);
}

inline Xfc::Gtk::CellRendererToggle::operator GtkCellRendererToggle* () const
{
	return this ? gtk_cell_renderer_toggle() : 0;
}

inline bool
Xfc::Gtk::CellRendererToggle::get_active() const
{
	return gtk_cell_renderer_toggle_get_active(gtk_cell_renderer_toggle());
}

inline bool
Xfc::Gtk::CellRendererToggle::get_radio() const
{
	return gtk_cell_renderer_toggle_get_radio(gtk_cell_renderer_toggle());
}

inline void
Xfc::Gtk::CellRendererToggle::set_active(bool setting)
{
	gtk_cell_renderer_toggle_set_active(gtk_cell_renderer_toggle(), setting);
}

inline void
Xfc::Gtk::CellRendererToggle::set_radio(bool radio)
{
	gtk_cell_renderer_toggle_set_radio(gtk_cell_renderer_toggle(), radio);
}

inline const Xfc::Gtk::CellRendererToggle::ActivePropertyProxy
Xfc::Gtk::CellRendererToggle::property_active()
{
	return ActivePropertyProxy(this, &active_property);
}

inline const Xfc::Gtk::CellRendererToggle::ActivatablePropertyProxy
Xfc::Gtk::CellRendererToggle::property_activatable()
{
	return ActivatablePropertyProxy(this, &activatable_property);
}

inline const Xfc::Gtk::CellRendererToggle::RadioPropertyProxy
Xfc::Gtk::CellRendererToggle::property_radio()
{
	return RadioPropertyProxy(this, &radio_property);
}

inline const Xfc::Gtk::CellRendererToggle::InconsistentPropertyProxy
Xfc::Gtk::CellRendererToggle::property_inconsistent()
{
	return InconsistentPropertyProxy(this, &inconsistent_property);
}

inline const Xfc::Gtk::CellRendererToggle::ToggledSignalProxy
Xfc::Gtk::CellRendererToggle::signal_toggled()
{
	return ToggledSignalProxy(this, &toggled_signal);
}

