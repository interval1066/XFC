/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  expander.inl - Gtk::Expander inline functions
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

inline GtkExpander*
Xfc::Gtk::Expander::gtk_expander() const
{
	return reinterpret_cast<GtkExpander*>(instance_);
}

inline Xfc::Gtk::Expander::operator GtkExpander* () const
{
	return this ? gtk_expander() : 0;
}

inline bool 
Xfc::Gtk::Expander::get_expanded() const
{
	return gtk_expander_get_expanded(gtk_expander());
}

inline int 
Xfc::Gtk::Expander::get_spacing() const
{
	return gtk_expander_get_spacing(gtk_expander());
}
	
inline bool 
Xfc::Gtk::Expander::get_use_underline() const
{
	return gtk_expander_get_use_underline(gtk_expander());
}
	 
inline bool 
Xfc::Gtk::Expander::get_use_markup() const
{
	return gtk_expander_get_use_markup(gtk_expander());
}

inline void 
Xfc::Gtk::Expander::set_expanded(bool expanded)
{
	gtk_expander_set_expanded(gtk_expander(), expanded);
}

inline void 
Xfc::Gtk::Expander::set_spacing(int spacing)
{
	gtk_expander_set_spacing(gtk_expander(), spacing);
}
	
inline void 
Xfc::Gtk::Expander::set_label(const char *label)
{
	gtk_expander_set_label(gtk_expander(), label);
}

inline void 
Xfc::Gtk::Expander::set_use_underline(bool use_underline)
{
	gtk_expander_set_use_underline(gtk_expander(),  use_underline);
}
	 
inline void 
Xfc::Gtk::Expander::set_use_markup(bool use_markup)
{
	gtk_expander_set_use_markup(gtk_expander(), use_markup);
}
	 
