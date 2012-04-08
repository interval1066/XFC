/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  textview.inl - Gtk::TextView inline functions
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

inline GtkTextView*
Xfc::Gtk::TextView::gtk_text_view() const
{
	return reinterpret_cast<GtkTextView*>(instance_);
}

inline Xfc::Gtk::TextView::operator GtkTextView* () const
{
	return this ? gtk_text_view() : 0;
}

inline bool
Xfc::Gtk::TextView::get_cursor_visible() const
{
	return gtk_text_view_get_cursor_visible(gtk_text_view());
}

inline int
Xfc::Gtk::TextView::get_border_window_size(TextWindowType type) const
{
	return gtk_text_view_get_border_window_size(gtk_text_view(), (GtkTextWindowType)type);
}

inline Xfc::Gtk::WrapMode
Xfc::Gtk::TextView::get_wrap_mode() const
{
	return (WrapMode)gtk_text_view_get_wrap_mode(gtk_text_view());
}

inline bool
Xfc::Gtk::TextView::get_editable() const
{
	return gtk_text_view_get_editable(gtk_text_view());
}

inline bool
Xfc::Gtk::TextView::get_overwrite() const
{
	return gtk_text_view_get_overwrite(gtk_text_view());
}

inline bool
Xfc::Gtk::TextView::get_accepts_tab() const
{
	return gtk_text_view_get_accepts_tab(gtk_text_view());
}

inline int
Xfc::Gtk::TextView::get_pixels_above_lines() const
{
	return gtk_text_view_get_pixels_above_lines(gtk_text_view());
}

inline int
Xfc::Gtk::TextView::get_pixels_below_lines() const
{
	return gtk_text_view_get_pixels_below_lines(gtk_text_view());
}

inline int
Xfc::Gtk::TextView::get_pixels_inside_wrap() const
{
	return gtk_text_view_get_pixels_inside_wrap(gtk_text_view());
}

inline Xfc::Gtk::Justification
Xfc::Gtk::TextView::get_justification() const
{
	return (Justification)gtk_text_view_get_justification(gtk_text_view());
}

inline int
Xfc::Gtk::TextView::get_left_margin() const
{
	return gtk_text_view_get_left_margin(gtk_text_view());
}

inline int
Xfc::Gtk::TextView::get_right_margin() const
{
	return gtk_text_view_get_right_margin(gtk_text_view());
}

inline int
Xfc::Gtk::TextView::get_indent() const
{
	return gtk_text_view_get_indent(gtk_text_view());
}

inline bool
Xfc::Gtk::TextView::place_cursor_onscreen()
{
	return gtk_text_view_place_cursor_onscreen(gtk_text_view());
}

inline void
Xfc::Gtk::TextView::set_cursor_visible(bool setting)
{
	gtk_text_view_set_cursor_visible(gtk_text_view(), setting);
}

inline void
Xfc::Gtk::TextView::set_border_window_size(TextWindowType window_type, int size)
{
	gtk_text_view_set_border_window_size(gtk_text_view(), (GtkTextWindowType)window_type, size);
}

inline void
Xfc::Gtk::TextView::set_wrap_mode(WrapMode wrap_mode)
{
	gtk_text_view_set_wrap_mode(gtk_text_view(), (GtkWrapMode)wrap_mode);
}

inline void
Xfc::Gtk::TextView::set_editable(bool setting)
{
	gtk_text_view_set_editable(gtk_text_view(), setting);
}

inline void
Xfc::Gtk::TextView::set_overwrite(bool overwrite)
{
	gtk_text_view_set_overwrite(gtk_text_view(), overwrite);
}

inline void
Xfc::Gtk::TextView::set_accepts_tab(bool accepts_tab)
{
	gtk_text_view_set_accepts_tab(gtk_text_view(), accepts_tab);
}

inline void
Xfc::Gtk::TextView::set_pixels_above_lines(int pixels_above_lines)
{
	gtk_text_view_set_pixels_above_lines(gtk_text_view(), pixels_above_lines);
}

inline void
Xfc::Gtk::TextView::set_pixels_below_lines(int pixels_below_lines)
{
	gtk_text_view_set_pixels_below_lines(gtk_text_view(), pixels_below_lines);
}

inline void
Xfc::Gtk::TextView::set_pixels_inside_wrap(int pixels_inside_wrap)
{
	gtk_text_view_set_pixels_inside_wrap(gtk_text_view(), pixels_inside_wrap);
}

inline void
Xfc::Gtk::TextView::set_justification(Justification justification)
{
	gtk_text_view_set_justification(gtk_text_view(), (GtkJustification)justification);
}

inline void
Xfc::Gtk::TextView::set_left_margin(int left_margin)
{
	gtk_text_view_set_left_margin(gtk_text_view(), left_margin);
}

inline void
Xfc::Gtk::TextView::set_right_margin(int right_margin)
{
	gtk_text_view_set_right_margin(gtk_text_view(), right_margin);
}

inline void
Xfc::Gtk::TextView::set_indent(int indent)
{
	gtk_text_view_set_indent(gtk_text_view(), indent);
}

inline const Xfc::Gtk::TextView::SetScrollAdjustmentsSignalProxy
Xfc::Gtk::TextView::signal_set_scroll_adjustments()
{
	return SetScrollAdjustmentsSignalProxy(this, &set_scroll_adjustments_signal);
}

inline const Xfc::Gtk::TextView::PopulatePopupSignalProxy
Xfc::Gtk::TextView::signal_populate_popup()
{
	return PopulatePopupSignalProxy(this, &populate_popup_signal);
}

inline const Xfc::Gtk::TextView::SetAnchorSignalProxy
Xfc::Gtk::TextView::signal_set_anchor()
{
	return SetAnchorSignalProxy(this, &set_anchor_signal);
}

inline const Xfc::Gtk::TextView::InsertAtCursorSignalProxy
Xfc::Gtk::TextView::signal_insert_at_cursor()
{
	return InsertAtCursorSignalProxy(this, &insert_at_cursor_signal);
}

