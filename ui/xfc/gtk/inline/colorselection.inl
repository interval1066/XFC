/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  colorselection.inl - Gtk::ColorSelection inline functions
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

/*  Gtk::ColorSelection
 */

inline GtkColorSelection*
Xfc::Gtk::ColorSelection::gtk_color_selection() const
{
	return reinterpret_cast<GtkColorSelection*>(instance_);
}

inline Xfc::Gtk::ColorSelection::operator GtkColorSelection* () const
{
	return this ? gtk_color_selection() : 0;
}

inline bool
Xfc::Gtk::ColorSelection::get_has_opacity_control() const
{
	return gtk_color_selection_get_has_opacity_control(gtk_color_selection());
}

inline bool
Xfc::Gtk::ColorSelection::get_has_palette() const
{
	return gtk_color_selection_get_has_palette(gtk_color_selection());
}

inline unsigned short
Xfc::Gtk::ColorSelection::get_current_alpha() const
{
	return gtk_color_selection_get_current_alpha(gtk_color_selection());
}

inline unsigned short
Xfc::Gtk::ColorSelection::get_previous_alpha() const
{
	return gtk_color_selection_get_previous_alpha(gtk_color_selection());
}

inline bool
Xfc::Gtk::ColorSelection::is_adjusting() const
{
	return gtk_color_selection_is_adjusting(gtk_color_selection());
}

inline void
Xfc::Gtk::ColorSelection::set_has_opacity_control(bool has_opacity)
{
	gtk_color_selection_set_has_opacity_control(gtk_color_selection(), has_opacity);
}

inline void
Xfc::Gtk::ColorSelection::set_has_palette(bool has_palette)
{
	return gtk_color_selection_set_has_palette(gtk_color_selection(), has_palette);
}

inline void
Xfc::Gtk::ColorSelection::set_current_alpha(unsigned short alpha)
{
	gtk_color_selection_set_current_alpha(gtk_color_selection(), alpha);
}

inline void
Xfc::Gtk::ColorSelection::set_previous_alpha(unsigned short alpha)
{
	gtk_color_selection_set_previous_alpha(gtk_color_selection(), alpha);
}

inline const Xfc::Gtk::ColorSelection::ColorChangedSignalProxy
Xfc::Gtk::ColorSelection::signal_color_changed()
{
	return ColorChangedSignalProxy(this, &color_changed_signal);
}

/*  Gtk::ColorSelectionDialog
 */

inline GtkColorSelectionDialog*
Xfc::Gtk::ColorSelectionDialog::gtk_color_selection_dialog() const
{
	return reinterpret_cast<GtkColorSelectionDialog*>(instance_);
}

inline Xfc::Gtk::ColorSelectionDialog::operator GtkColorSelectionDialog* () const
{
	return this ? gtk_color_selection_dialog() : 0;
}

