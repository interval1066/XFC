/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  dialog.inl - Gtk::Dialog inline functions
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

inline GtkDialog*
Xfc::Gtk::Dialog::gtk_dialog() const
{
	return reinterpret_cast<GtkDialog*>(instance_);
}

inline Xfc::Gtk::Dialog::operator GtkDialog* () const
{
	return this ? gtk_dialog() : 0;
}

inline bool
Xfc::Gtk::Dialog::get_has_separator() const
{
	return gtk_dialog_get_has_separator(gtk_dialog());
}

inline void
Xfc::Gtk::Dialog::set_response_sensitive(int response_id, bool setting)
{
	gtk_dialog_set_response_sensitive(gtk_dialog(), response_id, setting);
}

inline void
Xfc::Gtk::Dialog::set_default_response(int response_id)
{
	gtk_dialog_set_default_response(gtk_dialog(), response_id);
}

inline void
Xfc::Gtk::Dialog::response(int response_id)
{
	gtk_dialog_response(gtk_dialog(), response_id);
}

inline int
Xfc::Gtk::Dialog::run()
{
	return gtk_dialog_run(gtk_dialog());
}

inline void
Xfc::Gtk::Dialog::set_has_separator(bool setting)
{
	gtk_dialog_set_has_separator(gtk_dialog(), setting);
}

inline void 
Xfc::Gtk::Dialog::set_alternative_button_order(int n_params, int *new_order)
{
	gtk_dialog_set_alternative_button_order_from_array(gtk_dialog(), n_params, new_order);
}

inline const Xfc::Gtk::Dialog::ResponseSignalProxy 
Xfc::Gtk::Dialog::signal_response()
{
	return ResponseSignalProxy(this, &response_signal);
}

inline const Xfc::Gtk::Dialog::CloseSignalProxy 
Xfc::Gtk::Dialog::signal_close()
{
	return CloseSignalProxy(this, &close_signal);
}

