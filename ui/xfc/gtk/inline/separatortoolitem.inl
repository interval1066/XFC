/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  separatortoolitem.inl - Gtk::SeparatorToolItem inline functions
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

inline GtkSeparatorToolItem*
Xfc::Gtk::SeparatorToolItem::gtk_separator_tool_item() const
{
	return reinterpret_cast<GtkSeparatorToolItem*>(instance_);
}

inline Xfc::Gtk::SeparatorToolItem::operator GtkSeparatorToolItem* () const
{
	return this ? gtk_separator_tool_item() : 0;
}

inline bool 
Xfc::Gtk::SeparatorToolItem::get_draw() const
{
	return gtk_separator_tool_item_get_draw(gtk_separator_tool_item());
}
	
inline void 
Xfc::Gtk::SeparatorToolItem::set_draw(bool draw)
{
	gtk_separator_tool_item_set_draw(gtk_separator_tool_item(), draw);
}
