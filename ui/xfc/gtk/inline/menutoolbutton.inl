/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  menutoolbutton.inl - Gtk::MenuToolButton inline functions
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

inline GtkMenuToolButton*
Xfc::Gtk::MenuToolButton::gtk_menu_tool_button() const
{
	return reinterpret_cast<GtkMenuToolButton*>(instance_);
}

inline Xfc::Gtk::MenuToolButton::operator GtkMenuToolButton* () const
{
	return this ? gtk_menu_tool_button() : 0;
}

