/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  box.inl - Gtk::Box, Gtk::HBox, Gtk::VBox inline functions
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

/*  Gtk::Box
 */

inline GtkBox*
Xfc::Gtk::Box::gtk_box() const
{
	return reinterpret_cast<GtkBox*>(instance_);
}

inline Xfc::Gtk::Box::operator GtkBox* () const
{
	return this ? gtk_box() : 0;
}

inline bool
Xfc::Gtk::Box::get_homogeneous() const
{
	return gtk_box_get_homogeneous(gtk_box());
}

inline int
Xfc::Gtk::Box::get_spacing() const
{
	return gtk_box_get_spacing(gtk_box());
}

inline void
Xfc::Gtk::Box::set_homogeneous(bool homogeneous)
{
	gtk_box_set_homogeneous(gtk_box(), homogeneous);
}

inline void
Xfc::Gtk::Box::set_spacing(int spacing)
{
	gtk_box_set_spacing(gtk_box(), spacing);
}

/*  Gtk::HBox
 */

inline GtkHBox*
Xfc::Gtk::HBox::gtk_hbox() const
{
	return reinterpret_cast<GtkHBox*>(instance_);
}

inline Xfc::Gtk::HBox::operator GtkHBox* () const
{
	return this ? gtk_hbox() : 0;
}
/*  Gtk::VBox
 */

inline GtkVBox*
Xfc::Gtk::VBox::gtk_vbox() const
{
	return reinterpret_cast<GtkVBox*>(instance_);
}

inline Xfc::Gtk::VBox::operator GtkVBox* () const
{
	return this ? gtk_vbox() : 0;
}

