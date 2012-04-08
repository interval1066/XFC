/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  buttonbox.inl - Gtk::ButtonBox, Gtk::HButtonBox and Gtk::VButtonBox inline functions
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

/*  Gtk::ButtonBox
 */

inline GtkButtonBox*
Xfc::Gtk::ButtonBox::gtk_button_box() const
{
	return reinterpret_cast<GtkButtonBox*>(instance_);
}

inline Xfc::Gtk::ButtonBox::operator GtkButtonBox* () const
{
	return this ? gtk_button_box() : 0;
}

inline Xfc::Gtk::ButtonBoxStyle
Xfc::Gtk::ButtonBox::get_layout() const
{
	return (ButtonBoxStyle)gtk_button_box_get_layout(gtk_button_box());
}

inline void
Xfc::Gtk::ButtonBox::set_layout(ButtonBoxStyle layout_style)
{
	gtk_button_box_set_layout(gtk_button_box(), (GtkButtonBoxStyle)layout_style);
}

/*  Gtk::HButtonBox
 */

inline GtkHButtonBox*
Xfc::Gtk::HButtonBox::gtk_hbutton_box() const
{
	return reinterpret_cast<GtkHButtonBox*>(instance_);
}

inline Xfc::Gtk::HButtonBox::operator GtkHButtonBox* () const
{
	return this ? gtk_hbutton_box() : 0;
}

/*  Gtk::VButtonBox
 */

inline GtkVButtonBox*
Xfc::Gtk::VButtonBox::gtk_vbutton_box() const
{
	return reinterpret_cast<GtkVButtonBox*>(instance_);
}

inline Xfc::Gtk::VButtonBox::operator GtkVButtonBox* () const
{
	return this ? gtk_vbutton_box() : 0;
}

