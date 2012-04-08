/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treestore.inl - Gtk::TreeStore inline functions
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

inline GtkTreeStore*
Xfc::Gtk::TreeStore::gtk_tree_store() const
{
	return reinterpret_cast<GtkTreeStore*>(instance_);
}

inline Xfc::Gtk::TreeStore::operator GtkTreeStore* () const
{
	return this ? gtk_tree_store() : 0;
}

inline void
Xfc::Gtk::TreeStore::clear()
{
	gtk_tree_store_clear(gtk_tree_store());
}

template<typename DataType>
inline void
Xfc::Gtk::TreeStore::set_value(const TreeIter& iter, int column, const DataType& data)
{
	G::Value value(gtk_tree_store()->column_headers[column]);
	value.set(data);
	gtk_tree_store_set_value(gtk_tree_store(), iter, column, value.g_value());
}

template<typename DataType>
inline void
Xfc::Gtk::TreeStore::set_enum(const TreeIter& iter, int column, const DataType& data)
{
	G::Value value(gtk_tree_store()->column_headers[column]);
	value.set((int)data);
	gtk_tree_store_set_value(gtk_tree_store(), iter, column, value.g_value());
}

template<typename DataType>
inline void
Xfc::Gtk::TreeStore::set_object(const TreeIter& iter, int column, const DataType& data)
{
	G::Value value(gtk_tree_store()->column_headers[column]);
	value.set((G::Object*)data);
	gtk_tree_store_set_value(gtk_tree_store(), iter, column, value.g_value());
}

template<typename DataType>
inline void
Xfc::Gtk::TreeStore::set_pointer(const TreeIter& iter, int column, const DataType& data)
{
	G::Value value(gtk_tree_store()->column_headers[column]);
	value.set((void*)data);
	gtk_tree_store_set_value(gtk_tree_store(), iter, column, value.g_value());
}

