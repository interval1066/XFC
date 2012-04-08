/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  treeview.inl - Gtk::TreeView inline functions
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

inline GtkTreeView*
Xfc::Gtk::TreeView::gtk_tree_view() const
{
	return reinterpret_cast<GtkTreeView*>(instance_);
}

inline Xfc::Gtk::TreeView::operator GtkTreeView* () const
{
	return this ? gtk_tree_view() : 0;
}

inline bool
Xfc::Gtk::TreeView::get_headers_visible() const
{
	return gtk_tree_view_get_headers_visible(gtk_tree_view());
}

inline bool
Xfc::Gtk::TreeView::get_reorderable() const
{
	return gtk_tree_view_get_reorderable(gtk_tree_view());
}

inline bool
Xfc::Gtk::TreeView::get_rules_hint() const
{
	return gtk_tree_view_get_rules_hint(gtk_tree_view());
}

inline bool
Xfc::Gtk::TreeView::get_enable_search() const
{
	return gtk_tree_view_get_enable_search(gtk_tree_view());
}

inline int
Xfc::Gtk::TreeView::get_search_column() const
{
	return gtk_tree_view_get_search_column(gtk_tree_view());
}

inline bool 
Xfc::Gtk::TreeView::get_fixed_height_mode() const
{
	return gtk_tree_view_get_fixed_height_mode(gtk_tree_view());
}
	
inline bool 
Xfc::Gtk::TreeView::get_hover_selection() const
{
	return gtk_tree_view_get_hover_selection(gtk_tree_view());
}
	
inline bool 
Xfc::Gtk::TreeView::get_hover_expand() const
{
	return gtk_tree_view_get_hover_expand(gtk_tree_view());
}

inline void
Xfc::Gtk::TreeView::set_headers_visible(bool headers_visible)
{
	gtk_tree_view_set_headers_visible(gtk_tree_view(), headers_visible);
}

inline void
Xfc::Gtk::TreeView::columns_autosize()
{
	gtk_tree_view_columns_autosize(gtk_tree_view());
}

inline void
Xfc::Gtk::TreeView::set_headers_clickable(bool setting)
{
	gtk_tree_view_set_headers_clickable(gtk_tree_view(), setting);
}

inline void
Xfc::Gtk::TreeView::scroll_to_point(int tree_x, int tree_y)
{
	gtk_tree_view_scroll_to_point(gtk_tree_view(), tree_x, tree_y);
}

inline void
Xfc::Gtk::TreeView::expand_all()
{
	gtk_tree_view_expand_all(gtk_tree_view());
}

inline void
Xfc::Gtk::TreeView::collapse_all()
{
	gtk_tree_view_collapse_all(gtk_tree_view());
}

inline void
Xfc::Gtk::TreeView::set_reorderable(bool reorderable)
{
	gtk_tree_view_set_reorderable(gtk_tree_view(), reorderable);
}

inline void
Xfc::Gtk::TreeView::widget_to_tree_coords(int wx, int wy, int *tx, int *ty) const
{
	gtk_tree_view_widget_to_tree_coords(gtk_tree_view(), wx, wy, tx, ty);
}

inline void
Xfc::Gtk::TreeView::tree_to_widget_coords(int tx, int ty, int *wx, int *wy) const
{
	gtk_tree_view_tree_to_widget_coords(gtk_tree_view(), tx, ty, wx, wy);
}

inline void
Xfc::Gtk::TreeView::set_rules_hint(bool setting)
{
	gtk_tree_view_set_rules_hint(gtk_tree_view(), setting);
}

inline void
Xfc::Gtk::TreeView::unset_rows_drag_source()
{
	gtk_tree_view_unset_rows_drag_source(gtk_tree_view());
}

inline void
Xfc::Gtk::TreeView::unset_rows_drag_dest()
{
	gtk_tree_view_unset_rows_drag_dest(gtk_tree_view());
}

inline void
Xfc::Gtk::TreeView::set_enable_search(bool enable_search)
{
	gtk_tree_view_set_enable_search(gtk_tree_view(), enable_search);
}

inline void
Xfc::Gtk::TreeView::set_search_column(int column)
{
	gtk_tree_view_set_search_column(gtk_tree_view(), column);
}

inline const Xfc::Gtk::TreeView::SetScrollAdjustmentsSignalProxy
Xfc::Gtk::TreeView::signal_set_scroll_adjustments()
{
	return SetScrollAdjustmentsSignalProxy(this, &set_scroll_adjustments_signal);
}

inline const Xfc::Gtk::TreeView::RowActivatedSignalProxy
Xfc::Gtk::TreeView::signal_row_activated()
{
	return RowActivatedSignalProxy(this, &row_activated_signal);
}

inline const Xfc::Gtk::TreeView::TestExpandRowSignalProxy
Xfc::Gtk::TreeView::signal_test_expand_row()
{
	return TestExpandRowSignalProxy(this, &test_expand_row_signal);
}

inline const Xfc::Gtk::TreeView::TestCollapseRowSignalProxy
Xfc::Gtk::TreeView::signal_test_collapse_row()
{
	return TestCollapseRowSignalProxy(this, &test_collapse_row_signal);
}

inline const Xfc::Gtk::TreeView::RowExpandedSignalProxy
Xfc::Gtk::TreeView::signal_row_expanded()
{
	return RowExpandedSignalProxy(this, &row_expanded_signal);
}

inline const Xfc::Gtk::TreeView::RowCollapsedSignalProxy
Xfc::Gtk::TreeView::signal_row_collapsed()
{
	return RowCollapsedSignalProxy(this, &row_collapsed_signal);
}

inline const Xfc::Gtk::TreeView::ColumnsChangedSignalProxy
Xfc::Gtk::TreeView::signal_columns_changed()
{
	return ColumnsChangedSignalProxy(this, &columns_changed_signal);
}

inline const Xfc::Gtk::TreeView::CursorChangedSignalProxy
Xfc::Gtk::TreeView::signal_cursor_changed()
{
	return CursorChangedSignalProxy(this, &cursor_changed_signal);
}

