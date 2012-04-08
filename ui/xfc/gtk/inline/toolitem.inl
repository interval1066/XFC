/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  toolitem.inl - Gtk::ToolItem inline functions
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

inline GtkToolItem*
Xfc::Gtk::ToolItem::gtk_tool_item() const
{
	return reinterpret_cast<GtkToolItem*>(instance_);
}

inline Xfc::Gtk::ToolItem::operator GtkToolItem* () const
{
	return this ? gtk_tool_item() : 0;
}

inline bool 
Xfc::Gtk::ToolItem::get_homogeneous() const
{
	return gtk_tool_item_get_homogeneous(gtk_tool_item());
}

inline bool 
Xfc::Gtk::ToolItem::get_expand() const
{
	return gtk_tool_item_get_expand(gtk_tool_item());
}

inline bool 
Xfc::Gtk::ToolItem::get_use_drag_window() const
{
	return gtk_tool_item_get_use_drag_window(gtk_tool_item());
}

inline bool 
Xfc::Gtk::ToolItem::get_visible_horizontal() const
{
	return gtk_tool_item_get_visible_horizontal(gtk_tool_item());
}
	
inline bool 
Xfc::Gtk::ToolItem::get_visible_vertical() const
{
	return gtk_tool_item_get_visible_vertical(gtk_tool_item());
}

inline bool 
Xfc::Gtk::ToolItem::get_is_important() const
{
	return gtk_tool_item_get_is_important(gtk_tool_item());
}
	
inline Xfc::Gtk::IconSize 
Xfc::Gtk::ToolItem::get_icon_size() const
{
	return (IconSize)gtk_tool_item_get_icon_size(gtk_tool_item());
}

inline Xfc::Gtk::Orientation 
Xfc::Gtk::ToolItem::get_orientation() const
{
	return (Orientation)gtk_tool_item_get_orientation(gtk_tool_item());
}
	
inline Xfc::Gtk::ToolbarStyle 
Xfc::Gtk::ToolItem::get_toolbar_style() const
{
	return (ToolbarStyle)gtk_tool_item_get_toolbar_style(gtk_tool_item());
}
	
inline Xfc::Gtk::ReliefStyle 
Xfc::Gtk::ToolItem::get_relief_style() const
{
	return (ReliefStyle)gtk_tool_item_get_relief_style(gtk_tool_item());
}

inline void 
Xfc::Gtk::ToolItem::set_homogeneous(bool homogeneous)
{
	gtk_tool_item_set_homogeneous(gtk_tool_item(), homogeneous);
}
	
inline void 
Xfc::Gtk::ToolItem::set_expand(bool expand)
{
	gtk_tool_item_set_expand(gtk_tool_item(), expand);
}

inline void 
Xfc::Gtk::ToolItem::set_use_drag_window(bool use_drag_window)
{
	gtk_tool_item_set_use_drag_window(gtk_tool_item(), use_drag_window);
}
	
inline void 
Xfc::Gtk::ToolItem::set_visible_horizontal(bool visible_horizontal)
{
	gtk_tool_item_set_visible_horizontal(gtk_tool_item(), visible_horizontal);
}
	 
inline void 
Xfc::Gtk::ToolItem::set_visible_vertical(bool visible_vertical)
{
	gtk_tool_item_set_visible_vertical(gtk_tool_item(), visible_vertical);
}
	
inline void 
Xfc::Gtk::ToolItem::set_is_important(bool is_important)
{
	gtk_tool_item_set_is_important(gtk_tool_item(), is_important);
}
	
inline void 
Xfc::Gtk::ToolItem::rebuild_menu()
{
	gtk_tool_item_rebuild_menu(gtk_tool_item());
}

inline const Xfc::Gtk::ToolItem::CreateMenuProxySignalProxy
Xfc::Gtk::ToolItem::signal_create_menu_proxy()
{
	return CreateMenuProxySignalProxy(this, &create_menu_proxy_signal);
}
	
inline const Xfc::Gtk::ToolItem::ToolbarReconfiguredSignalProxy
Xfc::Gtk::ToolItem::signal_toolbar_reconfigured()
{
	return ToolbarReconfiguredSignalProxy(this, &toolbar_reconfigured_signal);
}

inline const Xfc::Gtk::ToolItem::SetTooltipSignalProxy
Xfc::Gtk::ToolItem::signal_set_tooltip()
{
	return SetTooltipSignalProxy(this, &set_tooltip_signal);
}
