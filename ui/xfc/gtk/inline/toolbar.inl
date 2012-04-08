/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  toolbar.inl - Gtk::Toolbar inline functions
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

inline GtkToolbar*
Xfc::Gtk::Toolbar::gtk_toolbar() const
{
	return reinterpret_cast<GtkToolbar*>(instance_);
}

inline Xfc::Gtk::Toolbar::operator GtkToolbar* () const
{
	return this ? gtk_toolbar() : 0;
}

inline bool
Xfc::Gtk::Toolbar::get_show_arrow() const
{
	return gtk_toolbar_get_show_arrow(gtk_toolbar());
}

inline Xfc::Gtk::Orientation
Xfc::Gtk::Toolbar::get_orientation() const
{
	return (Orientation)gtk_toolbar_get_orientation(gtk_toolbar());
}

inline bool
Xfc::Gtk::Toolbar::get_tooltips() const
{
	return gtk_toolbar_get_tooltips(gtk_toolbar());
}

inline Xfc::Gtk::ToolbarStyle
Xfc::Gtk::Toolbar::get_style() const
{
	return (ToolbarStyle)gtk_toolbar_get_style(gtk_toolbar());
}

inline Xfc::Gtk::IconSize
Xfc::Gtk::Toolbar::get_icon_size() const
{
	return (IconSize)gtk_toolbar_get_icon_size(gtk_toolbar());
}

inline Xfc::Gtk::ReliefStyle
Xfc::Gtk::Toolbar::get_relief_style() const
{
	return (ReliefStyle)gtk_toolbar_get_relief_style(gtk_toolbar());
}

inline int
Xfc::Gtk::Toolbar::get_drop_index(int x, int y) const
{
	return gtk_toolbar_get_drop_index(gtk_toolbar(), x, y);
}

inline void
Xfc::Gtk::Toolbar::set_show_arrow(bool show_arrow)
{
	gtk_toolbar_set_show_arrow(gtk_toolbar(), show_arrow);
}

inline void
Xfc::Gtk::Toolbar::set_orientation(Orientation orientation)
{
	gtk_toolbar_set_orientation(gtk_toolbar(), (GtkOrientation)orientation);
}

inline void
Xfc::Gtk::Toolbar::set_tooltips(bool enable)
{
	gtk_toolbar_set_tooltips(gtk_toolbar(), enable);
}

inline void
Xfc::Gtk::Toolbar::set_style(ToolbarStyle style)
{
	gtk_toolbar_set_style(gtk_toolbar(), (GtkToolbarStyle)style);
}

inline void
Xfc::Gtk::Toolbar::unset_style()
{
	gtk_toolbar_unset_style(gtk_toolbar());
}

inline void
Xfc::Gtk::Toolbar::unset_drop_highlight_item()
{
	gtk_toolbar_set_drop_highlight_item(gtk_toolbar(), 0, 0);
}

inline const Xfc::Gtk::Toolbar::OrientationChangedSignalProxy
Xfc::Gtk::Toolbar::signal_orientation_changed()
{
	return OrientationChangedSignalProxy(this, &orientation_changed_signal);
}

inline const Xfc::Gtk::Toolbar::StyleChangedSignalProxy
Xfc::Gtk::Toolbar::signal_style_changed()
{
	return StyleChangedSignalProxy(this, &style_changed_signal);
}

inline const Xfc::Gtk::Toolbar::PopupContextMenuSignalProxy
Xfc::Gtk::Toolbar::signal_popup_context_menu()
{
	return PopupContextMenuSignalProxy(this, &popup_context_menu_signal);
}

