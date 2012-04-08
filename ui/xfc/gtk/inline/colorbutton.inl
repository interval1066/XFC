/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  colorbutton.inl - Gtk::ColorButton inline functions
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

inline GtkColorButton*
Xfc::Gtk::ColorButton::gtk_color_button() const
{
	return reinterpret_cast<GtkColorButton*>(instance_);
}

inline Xfc::Gtk::ColorButton::operator GtkColorButton* () const
{
	return this ? gtk_color_button() : 0;
}

inline unsigned short 
Xfc::Gtk::ColorButton::get_alpha() const
{					    
	return gtk_color_button_get_alpha(gtk_color_button());
}
	
inline bool 
Xfc::Gtk::ColorButton::get_use_alpha() const
{
	return gtk_color_button_get_use_alpha(gtk_color_button());
}

inline void 
Xfc::Gtk::ColorButton::set_alpha(unsigned short alpha)
{
	gtk_color_button_set_alpha(gtk_color_button(), alpha);
}
				    
inline void 
Xfc::Gtk::ColorButton::set_use_alpha(bool use_alpha)
{
	gtk_color_button_set_use_alpha(gtk_color_button(), use_alpha);
}

inline void 
Xfc::Gtk::ColorButton::set_title(const char *title)
{
	gtk_color_button_set_title(gtk_color_button(), title);
}

inline const Xfc::Gtk::ColorButton::ColorSetSignalProxy
Xfc::Gtk::ColorButton::signal_color_set()
{
	return ColorSetSignalProxy(this, &color_set_signal);
}

