/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treeviewcolumn.inl - Gtk::TreeViewColumn inline functions
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

/*  Gtk::TreeViewColumn
 */

inline GtkTreeViewColumn*
Xfc::Gtk::TreeViewColumn::gtk_tree_view_column() const
{
	return reinterpret_cast<GtkTreeViewColumn*>(instance_);
}

inline Xfc::Gtk::TreeViewColumn::operator GtkTreeViewColumn* () const
{
	return this ? gtk_tree_view_column() : 0;
}

inline int
Xfc::Gtk::TreeViewColumn::get_spacing() const
{
	return gtk_tree_view_column_get_spacing(gtk_tree_view_column());
}

inline bool
Xfc::Gtk::TreeViewColumn::get_visible() const
{
	return gtk_tree_view_column_get_visible(gtk_tree_view_column());
}

inline bool
Xfc::Gtk::TreeViewColumn::get_resizable() const
{
	return gtk_tree_view_column_get_resizable(gtk_tree_view_column());
}

inline Xfc::Gtk::TreeViewColumnSizing
Xfc::Gtk::TreeViewColumn::get_sizing() const
{
	return (TreeViewColumnSizing)gtk_tree_view_column_get_sizing(gtk_tree_view_column());
}

inline int
Xfc::Gtk::TreeViewColumn::get_fixed_width() const
{
	return gtk_tree_view_column_get_fixed_width(gtk_tree_view_column());
}

inline int
Xfc::Gtk::TreeViewColumn::get_width() const
{
	return gtk_tree_view_column_get_width(gtk_tree_view_column());
}

inline int
Xfc::Gtk::TreeViewColumn::get_min_width() const
{
	return gtk_tree_view_column_get_min_width(gtk_tree_view_column());
}

inline int
Xfc::Gtk::TreeViewColumn::get_max_width() const
{
	return gtk_tree_view_column_get_max_width(gtk_tree_view_column());
}

inline bool
Xfc::Gtk::TreeViewColumn::get_expand() const
{
	return gtk_tree_view_column_get_expand(gtk_tree_view_column());
}

inline bool
Xfc::Gtk::TreeViewColumn::get_clickable() const
{
	return gtk_tree_view_column_get_clickable(gtk_tree_view_column());
}

inline float
Xfc::Gtk::TreeViewColumn::get_alignment() const
{
	return gtk_tree_view_column_get_alignment(gtk_tree_view_column());
}

inline bool
Xfc::Gtk::TreeViewColumn::get_reorderable() const
{
	return gtk_tree_view_column_get_reorderable(gtk_tree_view_column());
}

inline int
Xfc::Gtk::TreeViewColumn::get_sort_column_id() const
{
	return gtk_tree_view_column_get_sort_column_id(gtk_tree_view_column());
}

inline bool
Xfc::Gtk::TreeViewColumn::get_sort_indicator() const
{
	return gtk_tree_view_column_get_sort_indicator(gtk_tree_view_column());
}

inline Xfc::Gtk::SortType
Xfc::Gtk::TreeViewColumn::get_sort_order() const
{
	return (SortType)gtk_tree_view_column_get_sort_order(gtk_tree_view_column());
}

inline bool
Xfc::Gtk::TreeViewColumn::cell_is_visible() const
{
	return gtk_tree_view_column_cell_is_visible(gtk_tree_view_column());
}

inline void
Xfc::Gtk::TreeViewColumn::clear()
{
	gtk_tree_view_column_clear(gtk_tree_view_column());
}

inline void
Xfc::Gtk::TreeViewColumn::set_spacing(int spacing)
{
	gtk_tree_view_column_set_spacing(gtk_tree_view_column(), spacing);
}

inline void
Xfc::Gtk::TreeViewColumn::set_visible(bool visible)
{
	gtk_tree_view_column_set_visible(gtk_tree_view_column(), visible);
}

inline void
Xfc::Gtk::TreeViewColumn::set_resizable(bool resizable)
{
	gtk_tree_view_column_set_resizable(gtk_tree_view_column(), resizable);
}

inline void
Xfc::Gtk::TreeViewColumn::set_sizing(TreeViewColumnSizing type)
{
	gtk_tree_view_column_set_sizing(gtk_tree_view_column(), (GtkTreeViewColumnSizing)type);
}

inline void
Xfc::Gtk::TreeViewColumn::set_fixed_width(int fixed_width)
{
	gtk_tree_view_column_set_fixed_width(gtk_tree_view_column(), fixed_width);
}

inline void
Xfc::Gtk::TreeViewColumn::set_min_width(int min_width)
{
	gtk_tree_view_column_set_min_width(gtk_tree_view_column(), min_width);
}

inline void
Xfc::Gtk::TreeViewColumn::set_max_width(int max_width)
{
	gtk_tree_view_column_set_max_width(gtk_tree_view_column(), max_width);
}

inline void
Xfc::Gtk::TreeViewColumn::set_title(const char *title)
{
	gtk_tree_view_column_set_title(gtk_tree_view_column(), title);
}

inline void
Xfc::Gtk::TreeViewColumn::clicked()
{
	return gtk_tree_view_column_clicked(gtk_tree_view_column());
}

inline void
Xfc::Gtk::TreeViewColumn::set_expand(bool expand)
{
	gtk_tree_view_column_set_expand(gtk_tree_view_column(), expand);
}

inline void
Xfc::Gtk::TreeViewColumn::set_clickable(bool active)
{
	gtk_tree_view_column_set_clickable(gtk_tree_view_column(), active);
}

inline void
Xfc::Gtk::TreeViewColumn::set_alignment(float xalign)
{
	gtk_tree_view_column_set_alignment(gtk_tree_view_column(), xalign);
}

inline void
Xfc::Gtk::TreeViewColumn::set_reorderable(bool reorderable)
{
	gtk_tree_view_column_set_reorderable(gtk_tree_view_column(), reorderable);
}

inline void
Xfc::Gtk::TreeViewColumn::set_sort_column_id(int sort_column_id)
{
	gtk_tree_view_column_set_sort_column_id(gtk_tree_view_column(), sort_column_id);
}

inline void
Xfc::Gtk::TreeViewColumn::set_sort_indicator(bool setting)
{
	gtk_tree_view_column_set_sort_indicator(gtk_tree_view_column(), setting);
}

inline void
Xfc::Gtk::TreeViewColumn::set_sort_order(SortType order)
{
	gtk_tree_view_column_set_sort_order(gtk_tree_view_column(), (GtkSortType)order);
}

inline const Xfc::Gtk::TreeViewColumn::ClickedSignalProxy
Xfc::Gtk::TreeViewColumn::signal_clicked()
{
	return ClickedSignalProxy(this, &clicked_signal);
}

