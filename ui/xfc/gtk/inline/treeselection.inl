/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treeselection.inl - Gtk::TreeSelection inline functions
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

inline GtkTreeSelection*
Xfc::Gtk::TreeSelection::gtk_tree_selection() const
{
	return reinterpret_cast<GtkTreeSelection*>(instance_);
}

inline Xfc::Gtk::TreeSelection::operator GtkTreeSelection* () const
{
	return this ? gtk_tree_selection() : 0;
}

inline Xfc::Gtk::SelectionMode
Xfc::Gtk::TreeSelection::get_mode() const
{
	return (SelectionMode)gtk_tree_selection_get_mode(gtk_tree_selection());
}

inline bool
Xfc::Gtk::TreeSelection::any_selected() const
{
	return gtk_tree_selection_get_selected(gtk_tree_selection(), 0, 0);
}

inline int
Xfc::Gtk::TreeSelection::count_selected_rows() const
{
	return gtk_tree_selection_count_selected_rows(gtk_tree_selection());
}

inline void
Xfc::Gtk::TreeSelection::set_mode(SelectionMode type)
{
	gtk_tree_selection_set_mode(gtk_tree_selection(), (GtkSelectionMode)type);
}

inline void
Xfc::Gtk::TreeSelection::select_all()
{
	gtk_tree_selection_select_all(gtk_tree_selection());
}

inline void
Xfc::Gtk::TreeSelection::unselect_all()
{
	gtk_tree_selection_select_all(gtk_tree_selection());
}

inline const Xfc::Gtk::TreeSelection::ChangedSignalProxy
Xfc::Gtk::TreeSelection::signal_changed()
{
	return ChangedSignalProxy(this, &changed_signal);
}
