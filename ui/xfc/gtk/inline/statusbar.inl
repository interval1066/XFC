/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  statusbar.inl - Gtk::Statusbar inline functions
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

inline GtkStatusbar*
Xfc::Gtk::Statusbar::gtk_statusbar() const
{
	return reinterpret_cast<GtkStatusbar*>(instance_);
}

inline Xfc::Gtk::Statusbar::operator GtkStatusbar* () const
{
	return this ? gtk_statusbar() : 0;
}

inline unsigned int
Xfc::Gtk::Statusbar::get_context_id(const char *context_description) const
{
	return gtk_statusbar_get_context_id(gtk_statusbar(), context_description);
}

inline unsigned int
Xfc::Gtk::Statusbar::push(const char *text, unsigned int context_id)
{
	return gtk_statusbar_push(gtk_statusbar(), context_id, text);
}

inline void
Xfc::Gtk::Statusbar::pop(unsigned int context_id)
{
	gtk_statusbar_pop(gtk_statusbar(), context_id);
}

inline bool
Xfc::Gtk::Statusbar::get_has_resize_grip() const
{
	return gtk_statusbar_get_has_resize_grip(gtk_statusbar());
}

inline void
Xfc::Gtk::Statusbar::remove(unsigned int context_id, unsigned int message_id)
{
	gtk_statusbar_remove(gtk_statusbar(), context_id, message_id);
}

inline void
Xfc::Gtk::Statusbar::set_has_resize_grip(bool setting)
{
	gtk_statusbar_set_has_resize_grip(gtk_statusbar(), setting);
}

inline const Xfc::Gtk::Statusbar::TextPushedSignalProxy
Xfc::Gtk::Statusbar::signal_text_pushed()
{
	return TextPushedSignalProxy(this, &text_pushed_signal);
}

inline const Xfc::Gtk::Statusbar::TextPoppedSignalProxy
Xfc::Gtk::Statusbar::signal_text_popped()
{
	return TextPoppedSignalProxy(this, &text_popped_signal);
}

