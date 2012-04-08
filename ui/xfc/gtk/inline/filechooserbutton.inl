/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  filechooserbutton.inl - Gtk::FileChooserButton inline functions
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

inline GtkFileChooserButton*
Xfc::Gtk::FileChooserButton::gtk_file_chooser_button() const
{
	return reinterpret_cast<GtkFileChooserButton*>(instance_);
}

inline Xfc::Gtk::FileChooserButton::operator GtkFileChooserButton* () const
{
	return this ? gtk_file_chooser_button() : 0;
}

int 
Xfc::Gtk::FileChooserButton::get_width_chars() const
{
	return gtk_file_chooser_button_get_width_chars(gtk_file_chooser_button());
}

void 
Xfc::Gtk::FileChooserButton::set_title(const char *title)
{
	gtk_file_chooser_button_set_title(gtk_file_chooser_button(), title);
}

void 
Xfc::Gtk::FileChooserButton::set_width_chars(int n_chars)
{
	gtk_file_chooser_button_set_width_chars(gtk_file_chooser_button(), n_chars);
}

