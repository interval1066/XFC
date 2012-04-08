/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  label.inl - Gtk::Label inline functions
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

inline GtkLabel*
Xfc::Gtk::Label::gtk_label() const
{
	return reinterpret_cast<GtkLabel*>(instance_);
}

inline Xfc::Gtk::Label::operator GtkLabel* () const
{
	return this ? gtk_label() : 0;
}

inline bool
Xfc::Gtk::Label::get_use_markup() const
{
	return gtk_label_get_use_markup(gtk_label());
}

inline bool
Xfc::Gtk::Label::get_use_underline() const
{
	return gtk_label_get_use_underline(gtk_label());
}

inline unsigned int
Xfc::Gtk::Label::get_mnemonic_keyval() const
{
	return gtk_label_get_mnemonic_keyval(gtk_label());
}

inline Xfc::Gtk::Justification
Xfc::Gtk::Label::get_justify() const
{
	return (Justification)gtk_label_get_justify(gtk_label());
}

inline Xfc::Pango::EllipsizeMode 
Xfc::Gtk::Label::get_ellipsize() const
{
	return (Pango::EllipsizeMode)gtk_label_get_ellipsize(gtk_label());
}
	
inline int 
Xfc::Gtk::Label::get_width_chars() const
{
	return gtk_label_get_width_chars(gtk_label());
}
 
inline int 
Xfc::Gtk::Label::get_max_width_chars() const
{
	return gtk_label_get_max_width_chars(gtk_label());
}

inline bool
Xfc::Gtk::Label::get_line_wrap() const
{
	return gtk_label_get_line_wrap(gtk_label());
}

inline bool
Xfc::Gtk::Label::get_selectable() const
{
	return gtk_label_get_selectable(gtk_label());
}

inline double 
Xfc::Gtk::Label::get_angle() const
{
	return gtk_label_get_angle(gtk_label());
}
	
inline bool
Xfc::Gtk::Label::get_selection_bounds(int *start, int *end) const
{
	return gtk_label_get_selection_bounds(gtk_label(), start, end);
}

inline void
Xfc::Gtk::Label::get_layout_offsets(int *x, int *y) const
{
	gtk_label_get_layout_offsets(gtk_label(), x, y);
}

inline bool 
Xfc::Gtk::Label::get_single_line_mode() const
{
	return gtk_label_get_single_line_mode(gtk_label());
}

inline void
Xfc::Gtk::Label::set_text(const char *str)
{
	gtk_label_set_text(gtk_label(), str);
}

inline void
Xfc::Gtk::Label::set_markup(const char *str)
{
	gtk_label_set_markup(gtk_label(), str);
}

inline void
Xfc::Gtk::Label::set_label(const char *str)
{
	gtk_label_set_label(gtk_label(), str);
}

inline void
Xfc::Gtk::Label::set_markup_with_mnemonic(const char *str)
{
	gtk_label_set_markup_with_mnemonic(gtk_label(), str);
}

inline void
Xfc::Gtk::Label::set_text_with_mnemonic(const char *str)
{
	gtk_label_set_text_with_mnemonic(gtk_label(), str);
}

inline void 
Xfc::Gtk::Label::set_ellipsize(Pango::EllipsizeMode mode)
{
	gtk_label_set_ellipsize(gtk_label(), (PangoEllipsizeMode)mode);
}
	
inline void 
Xfc::Gtk::Label::set_width_chars(int n_chars)
{
	gtk_label_set_width_chars(gtk_label(), n_chars);
}
	
inline void 
Xfc::Gtk::Label::set_max_width_chars(int n_chars)
{
	gtk_label_set_max_width_chars(gtk_label(), n_chars);
}

inline void
Xfc::Gtk::Label::set_pattern(const char *pattern)
{
	gtk_label_set_pattern(gtk_label(), pattern);
}

inline void
Xfc::Gtk::Label::set_line_wrap(bool wrap)
{
	gtk_label_set_line_wrap(gtk_label(), wrap);
}

inline void
Xfc::Gtk::Label::set_selectable(bool setting)
{
	gtk_label_set_selectable(gtk_label(), setting);
}

inline void 
Xfc::Gtk::Label::set_angle(double angle)
{
	gtk_label_set_angle(gtk_label(), angle);
}

inline void
Xfc::Gtk::Label::select_region(int start_offset, int end_offset)
{
	gtk_label_select_region(gtk_label(), start_offset, end_offset);
}

inline void
Xfc::Gtk::Label::set_use_markup(bool setting)
{
	gtk_label_set_use_markup(gtk_label(), setting);
}

inline void
Xfc::Gtk::Label::set_use_underline(bool setting)
{
	gtk_label_set_use_underline(gtk_label(), setting);
}

inline void 
Xfc::Gtk::Label::set_single_line_mode(bool single_line_mode)
{
	gtk_label_set_single_line_mode(gtk_label(), single_line_mode);
}

inline const Xfc::Gtk::Label::PopulatePopupSignalProxy
Xfc::Gtk::Label::signal_populate_popup()
{
	return PopulatePopupSignalProxy(this, &populate_popup_signal);
}

