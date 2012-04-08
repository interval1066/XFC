/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  handlebox.inl - Gtk::HandleBox inline functions
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

inline GtkHandleBox*
Xfc::Gtk::HandleBox::gtk_handle_box() const
{
	return reinterpret_cast<GtkHandleBox*>(instance_);
}

inline Xfc::Gtk::HandleBox::operator GtkHandleBox* () const
{
	return this ? gtk_handle_box() : 0;
}

inline bool
Xfc::Gtk::HandleBox::is_child_detached() const
{
	return gtk_handle_box()->child_detached;
}

inline Xfc::Gtk::ShadowType
Xfc::Gtk::HandleBox::get_shadow_type() const
{
	return (ShadowType)gtk_handle_box_get_shadow_type(gtk_handle_box());
}

inline Xfc::Gtk::PositionType
Xfc::Gtk::HandleBox::get_handle_position() const
{
	return (PositionType)gtk_handle_box_get_handle_position(gtk_handle_box());
}

inline Xfc::Gtk::PositionType
Xfc::Gtk::HandleBox::get_snap_edge() const
{
	return (PositionType)gtk_handle_box_get_snap_edge(gtk_handle_box());
}

inline void
Xfc::Gtk::HandleBox::set_shadow_type(ShadowType type)
{
	gtk_handle_box_set_shadow_type(gtk_handle_box(), (GtkShadowType)type);
}

inline void
Xfc::Gtk::HandleBox::set_handle_position(PositionType position)
{
	gtk_handle_box_set_handle_position(gtk_handle_box(), (GtkPositionType)position);
}

inline void
Xfc::Gtk::HandleBox::set_snap_edge(PositionType edge)
{
	gtk_handle_box_set_snap_edge(gtk_handle_box(), (GtkPositionType)edge);
}

inline void
Xfc::Gtk::HandleBox::unset_snap_edge()
{
	gtk_handle_box_set_snap_edge(gtk_handle_box(), (GtkPositionType)-1);
}

inline const Xfc::Gtk::HandleBox::ChildAttachedSignalProxy
Xfc::Gtk::HandleBox::signal_child_attached()
{
	return ChildAttachedSignalProxy(this, &child_attached_signal);
}

inline const Xfc::Gtk::HandleBox::ChildDetachedSignalProxy
Xfc::Gtk::HandleBox::signal_child_detached()
{
	return ChildDetachedSignalProxy(this, &child_detached_signal);
}

