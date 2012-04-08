/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treemodelsort.inl - Gtk::TreeModelSort inline functions
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

inline GtkTreeModelSort*
Xfc::Gtk::TreeModelSort::gtk_tree_model_sort() const
{
	return reinterpret_cast<GtkTreeModelSort*>(instance_);
}

inline Xfc::Gtk::TreeModelSort::operator GtkTreeModelSort* () const
{
	return this ? gtk_tree_model_sort() : 0;
}

inline void
Xfc::Gtk::TreeModelSort::reset_default_sort_func()
{
	gtk_tree_model_sort_reset_default_sort_func(gtk_tree_model_sort());
}

inline void
Xfc::Gtk::TreeModelSort::clear_cache()
{
	gtk_tree_model_sort_clear_cache(gtk_tree_model_sort());
}

