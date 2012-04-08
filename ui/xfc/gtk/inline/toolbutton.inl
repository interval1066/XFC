/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  toolbutton.inl - Gtk::ToolButton inline functions
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

inline GtkToolButton*
Xfc::Gtk::ToolButton::gtk_tool_button() const
{
	return reinterpret_cast<GtkToolButton*>(instance_);
}

inline Xfc::Gtk::ToolButton::operator GtkToolButton* () const
{
	return this ? gtk_tool_button() : 0;
}

inline bool 
Xfc::Gtk::ToolButton::get_use_underline() const
{
	return gtk_tool_button_get_use_underline(gtk_tool_button());
}
	
inline void 
Xfc::Gtk::ToolButton::set_use_underline(bool use_underline)
{
	gtk_tool_button_set_use_underline(gtk_tool_button(), use_underline);
}

inline const Xfc::Gtk::ToolButton::ClickedSignalProxy
Xfc::Gtk::ToolButton::signal_clicked()
{
	return ClickedSignalProxy(this, &clicked_signal);
}
	
