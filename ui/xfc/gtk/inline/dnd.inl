/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  dnd.inl - Gtk Drag and Drop inline functions
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

inline void
Xfc::Gtk::DragContext::finish(bool success, bool delete_data, unsigned int time)
{
	gtk_drag_finish((GdkDragContext*)instance_, success, delete_data, time);
}

inline void
Xfc::Gtk::DragContext::set_icon_default()
{
	gtk_drag_set_icon_default((GdkDragContext*)instance_);
}

