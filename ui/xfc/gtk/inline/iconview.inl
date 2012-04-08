/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  iconview.inl - Gtk::IconView inline functions
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

inline GtkIconView*
Xfc::Gtk::IconView::gtk_icon_view() const
{
	return reinterpret_cast<GtkIconView*>(instance_);
}

inline Xfc::Gtk::IconView::operator GtkIconView* () const
{
	return this ? gtk_icon_view() : 0;
}

inline int 
Xfc::Gtk::IconView::get_text_column() const
{
	return gtk_icon_view_get_text_column(gtk_icon_view());
}
	
inline int 
Xfc::Gtk::IconView::get_markup_column() const
{
	return gtk_icon_view_get_markup_column(gtk_icon_view());
}

inline int 
Xfc::Gtk::IconView::get_pixbuf_column() const
{
	return gtk_icon_view_get_pixbuf_column(gtk_icon_view());
}

inline Xfc::Gtk::Orientation 
Xfc::Gtk::IconView::get_orientation() const
{
	return (Orientation)gtk_icon_view_get_orientation(gtk_icon_view());
}

inline int 
Xfc::Gtk::IconView::get_columns() const
{
	return gtk_icon_view_get_columns(gtk_icon_view());
}

inline int 
Xfc::Gtk::IconView::get_item_width() const
{
	return gtk_icon_view_get_item_width(gtk_icon_view());
}

inline int 
Xfc::Gtk::IconView::get_spacing() const
{
	return gtk_icon_view_get_spacing(gtk_icon_view());
}

inline int 
Xfc::Gtk::IconView::get_row_spacing() const
{
	return gtk_icon_view_get_row_spacing(gtk_icon_view());
}

inline int 
Xfc::Gtk::IconView::get_column_spacing() const
{
	return gtk_icon_view_get_column_spacing(gtk_icon_view());
}

inline int 
Xfc::Gtk::IconView::get_margin() const
{
	return gtk_icon_view_get_margin(gtk_icon_view());
}

inline Xfc::Gtk::SelectionMode 
Xfc::Gtk::IconView::get_selection_mode() const
{
	return (SelectionMode)gtk_icon_view_get_selection_mode(gtk_icon_view());
}

inline void 
Xfc::Gtk::IconView::set_text_column(int column)
{
	gtk_icon_view_set_text_column(gtk_icon_view(), column);
}

inline void 
Xfc::Gtk::IconView::set_markup_column(int column)
{
	gtk_icon_view_set_markup_column(gtk_icon_view(), column);
}

inline void 
Xfc::Gtk::IconView::set_pixbuf_column(int column)
{
	gtk_icon_view_set_pixbuf_column(gtk_icon_view(), column);
}

inline void 
Xfc::Gtk::IconView::set_orientation(Orientation orientation)
{
	gtk_icon_view_set_orientation(gtk_icon_view(), (GtkOrientation)orientation);
}

inline void 
Xfc::Gtk::IconView::set_columns(int columns)
{
	gtk_icon_view_set_columns(gtk_icon_view(), columns);
}

inline void 
Xfc::Gtk::IconView::set_item_width(int item_width)
{
	gtk_icon_view_set_item_width(gtk_icon_view(), item_width);
}

inline void 
Xfc::Gtk::IconView::set_spacing(int spacing)
{
	gtk_icon_view_set_spacing(gtk_icon_view(), spacing);
}

inline void 
Xfc::Gtk::IconView::set_row_spacing(int row_spacing)
{
	gtk_icon_view_set_row_spacing(gtk_icon_view(), row_spacing);
}

inline void 
Xfc::Gtk::IconView::set_column_spacing(int column_spacing)
{
	gtk_icon_view_set_column_spacing(gtk_icon_view(), column_spacing);
}

inline void 
Xfc::Gtk::IconView::set_margin(int margin)
{
	gtk_icon_view_set_margin(gtk_icon_view(), margin);
}

inline void 
Xfc::Gtk::IconView::set_selection_mode(SelectionMode mode)
{
	gtk_icon_view_set_selection_mode(gtk_icon_view(), (GtkSelectionMode)mode);
}

inline void 
Xfc::Gtk::IconView::select_all()
{
	gtk_icon_view_select_all(gtk_icon_view());
}
	
inline void 
Xfc::Gtk::IconView::unselect_all()
{
	gtk_icon_view_unselect_all(gtk_icon_view());
}

inline const Xfc::Gtk::IconView::SetScrollAdjustmentsSignalProxy
Xfc::Gtk::IconView::signal_set_scroll_adjustments()
{
	return SetScrollAdjustmentsSignalProxy(this, &set_scroll_adjustments_signal);
}

inline const Xfc::Gtk::IconView::ItemActivatedSignalProxy
Xfc::Gtk::IconView::signal_item_activated()
{
	return ItemActivatedSignalProxy(this, &item_activated_signal);
}

inline const Xfc::Gtk::IconView::SelectionChangedSignalProxy
Xfc::Gtk::IconView::signal_selection_changed()
{
	return SelectionChangedSignalProxy(this, &selection_changed_signal);
}
	
