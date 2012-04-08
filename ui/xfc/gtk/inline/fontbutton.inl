/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  fontbutton.inl - Gtk::FontButton inline functions
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

inline GtkFontButton*
Xfc::Gtk::FontButton::gtk_font_button() const
{
	return reinterpret_cast<GtkFontButton*>(instance_);
}

inline Xfc::Gtk::FontButton::operator GtkFontButton* () const
{
	return this ? gtk_font_button() : 0;
}

inline bool 
Xfc::Gtk::FontButton::get_use_font() const
{
	return gtk_font_button_get_use_font(gtk_font_button());
}

inline bool 
Xfc::Gtk::FontButton::get_use_size() const
{
	return gtk_font_button_get_use_size(gtk_font_button());
}
	
inline bool 
Xfc::Gtk::FontButton::get_show_style() const
{
	return gtk_font_button_get_show_style(gtk_font_button());
}
	
inline bool 
Xfc::Gtk::FontButton::get_show_size() const
{	
	return gtk_font_button_get_show_size(gtk_font_button());
}

inline void 
Xfc::Gtk::FontButton::set_title(const char *title)
{
	gtk_font_button_set_title(gtk_font_button(), title);
}

inline void 
Xfc::Gtk::FontButton::set_use_font(bool use_font)
{
	gtk_font_button_set_use_font(gtk_font_button(), use_font);
}
	
inline void 
Xfc::Gtk::FontButton::set_use_size(bool use_size)
{
	gtk_font_button_set_use_size(gtk_font_button(), use_size);
}
	
inline bool 
Xfc::Gtk::FontButton::set_font_name(const char *fontname)
{
	return gtk_font_button_set_font_name(gtk_font_button(), fontname);
}

inline void 
Xfc::Gtk::FontButton::set_show_style(bool show_style)
{
	gtk_font_button_set_show_style(gtk_font_button(), show_style);
}
	
inline void 
Xfc::Gtk::FontButton::set_show_size(bool show_size)
{
	gtk_font_button_set_show_size(gtk_font_button(), show_size);
}

inline const Xfc::Gtk::FontButton::FontSetSignalProxy
Xfc::Gtk::FontButton::signal_font_set()
{
	return FontSetSignalProxy(this, &font_set_signal);
}

