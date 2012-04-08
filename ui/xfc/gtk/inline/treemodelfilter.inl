/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treemodelfilter.inl - Gtk::TreeModelFilter inline functions
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

inline GtkTreeModelFilter*
Xfc::Gtk::TreeModelFilter::gtk_tree_model_filter() const
{
	return reinterpret_cast<GtkTreeModelFilter*>(instance_);
}

inline Xfc::Gtk::TreeModelFilter::operator GtkTreeModelFilter* () const
{
	return this ? gtk_tree_model_filter() : 0;
}

inline void
Xfc::Gtk::TreeModelFilter::set_visible_column(int column)
{
	gtk_tree_model_filter_set_visible_column(gtk_tree_model_filter(), column);
}

inline void
Xfc::Gtk::TreeModelFilter::refilter()
{
	gtk_tree_model_filter_refilter(gtk_tree_model_filter());
}

inline void
Xfc::Gtk::TreeModelFilter::clear_cache()
{
	gtk_tree_model_filter_clear_cache(gtk_tree_model_filter());
}

