/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  container.inl - Gtk::Container inline functions
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

inline GtkContainer*
Xfc::Gtk::Container::gtk_container() const
{
	return reinterpret_cast<GtkContainer*>(instance_);
}

inline Xfc::Gtk::Container::operator GtkContainer* () const
{
	return this ? gtk_container() : 0;
}

inline GType
Xfc::Gtk::Container::child_type() const
{
	return gtk_container_child_type(gtk_container());
}

inline unsigned int
Xfc::Gtk::Container::get_border_width() const
{
	return gtk_container_get_border_width(gtk_container());
}

inline Xfc::Gtk::ResizeMode
Xfc::Gtk::Container::get_resize_mode() const
{
	return (ResizeMode)gtk_container_get_resize_mode(gtk_container());
}

inline void
Xfc::Gtk::Container::check_resize()
{
	gtk_container_check_resize(gtk_container());
}

inline void
Xfc::Gtk::Container::set_border_width(unsigned int border_width)
{
	gtk_container_set_border_width(gtk_container(), border_width);
}

inline void
Xfc::Gtk::Container::set_resize_mode(ResizeMode resize_mode)
{
	gtk_container_set_resize_mode(gtk_container(), (GtkResizeMode)resize_mode);
}

inline void
Xfc::Gtk::Container::set_reallocate_redraws(bool needs_redraws)
{
	gtk_container_set_reallocate_redraws(gtk_container(), needs_redraws);
}

inline void
Xfc::Gtk::Container::resize_children()
{
	gtk_container_resize_children(gtk_container());
}

inline void
Xfc::Gtk::Container::unset_focus_chain()
{
	gtk_container_unset_focus_chain(gtk_container());
}

inline const Xfc::Gtk::Container::AddSignalProxy
Xfc::Gtk::Container::signal_add()
{
	return AddSignalProxy(this, &add_signal);
}

inline const Xfc::Gtk::Container::RemoveSignalProxy
Xfc::Gtk::Container::signal_remove()
{
	return RemoveSignalProxy(this, &remove_signal);
}

inline const Xfc::Gtk::Container::CheckResizeSignalProxy
Xfc::Gtk::Container::signal_check_resize()
{
	return CheckResizeSignalProxy(this, &check_resize_signal);
}

inline const Xfc::Gtk::Container::SetFocusChildSignalProxy
Xfc::Gtk::Container::signal_set_focus_child()
{
	return SetFocusChildSignalProxy(this, &set_focus_child_signal);
}

