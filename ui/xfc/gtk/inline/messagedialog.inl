/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  messagedialog.inl - Gtk::MessageDialog inline functions
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

inline GtkMessageDialog*
Xfc::Gtk::MessageDialog::gtk_message_dialog() const
{
	return reinterpret_cast<GtkMessageDialog*>(instance_);
}

inline Xfc::Gtk::MessageDialog::operator GtkMessageDialog* () const
{
	return this ? gtk_message_dialog() : 0;
}

inline void
Xfc::Gtk::MessageDialog::set_markup(const char *message)
{
	gtk_message_dialog_set_markup(gtk_message_dialog(), message);
}

inline void 
Xfc::Gtk::MessageDialog::set_secondary_text(const char *message)
{
	gtk_message_dialog_format_secondary_text(gtk_message_dialog(), message);
}
	
inline void 
Xfc::Gtk::MessageDialog::set_secondary_markup(const char *message)
{
	gtk_message_dialog_format_secondary_markup(gtk_message_dialog(), message);
}

