/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treesortable.inl - Gtk::Dialog inline functions
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

inline GtkTreeSortable*
Xfc::Gtk::TreeSortable::gtk_tree_sortable() const
{
	return reinterpret_cast<GtkTreeSortable*>(instance_);
}

inline Xfc::Gtk::TreeSortable::operator GtkTreeSortable* () const
{
	return this ? gtk_tree_sortable() : 0;
}

inline bool
Xfc::Gtk::TreeSortable::get_sort_column_id(int *sort_column_id, SortType *order) const
{
	return gtk_tree_sortable_get_sort_column_id(gtk_tree_sortable(), sort_column_id, (GtkSortType*)order);
}

inline bool
Xfc::Gtk::TreeSortable::has_default_sort_func() const
{
	return gtk_tree_sortable_has_default_sort_func(gtk_tree_sortable());
}

inline void
Xfc::Gtk::TreeSortable::sort_column_changed()
{
	gtk_tree_sortable_sort_column_changed(gtk_tree_sortable());
}

inline void
Xfc::Gtk::TreeSortable::set_sort_column_id(int sort_column_id, SortType order)
{
	gtk_tree_sortable_set_sort_column_id(gtk_tree_sortable(), sort_column_id, (GtkSortType)order);
}

inline const Xfc::Gtk::TreeSortable::SortColumnChangedSignalProxy
Xfc::Gtk::TreeSortable::signal_sort_column_changed()
{
	return SortColumnChangedSignalProxy(this, &sort_column_changed_signal);
}

