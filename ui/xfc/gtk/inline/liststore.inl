/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  liststore.inl - Gtk::ListStore inline functions
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


/*  Gtk::TreeRowValues
 */

inline const GValue* 
Xfc::Gtk::TreeRowValues::gvalues() const
{
	return gvalues_[0];
}	
	
inline const int* 
Xfc::Gtk::TreeRowValues::columns() const
{
	return &columns_[0];
}

inline unsigned int 
Xfc::Gtk::TreeRowValues::size() const
{
	return gvalues_.size();
}
	
template<typename DataType>
inline void 
Xfc::Gtk::TreeRowValues::add(GType type, int column, const DataType& data)
{
	G::Value value(type); 	
	value.set(data);
	gvalues_.push_back(create_value(value));	
	columns_.push_back(column);	
}

template<typename DataType>
inline void 
Xfc::Gtk::TreeRowValues::add_enum(GType type, int column, const DataType& data)
{
	G::Value value(type); 	
	value.set((int)data);
	gvalues_.push_back(create_value(value));	
	columns_.push_back(column);	
}

template<typename DataType>
inline void 
Xfc::Gtk::TreeRowValues::add_object(GType type, int column, const DataType& data)
{
	G::Value value(type); 	
	value.set((G::Object*)data);
	gvalues_.push_back(create_value(value));	
	columns_.push_back(column);	
}

template<typename DataType>
inline void 
Xfc::Gtk::TreeRowValues::add_pointer(GType type, int column, const DataType& data)
{
	G::Value value(type); 	
	value.set((void*)data);
	gvalues_.push_back(create_value(value));	
	columns_.push_back(column);	
}

/*  Gtk::ListStore
 */

inline GtkListStore*
Xfc::Gtk::ListStore::gtk_list_store() const
{
	return reinterpret_cast<GtkListStore*>(instance_);
}

inline Xfc::Gtk::ListStore::operator GtkListStore* () const
{
	return this ? gtk_list_store() : 0;
}

inline void
Xfc::Gtk::ListStore::clear()
{
	gtk_list_store_clear(gtk_list_store());
}

inline void
Xfc::Gtk::ListStore::reorder(int *new_order)
{
	gtk_list_store_reorder(gtk_list_store(), new_order);
}

template<typename DataType>
inline void
Xfc::Gtk::ListStore::set_value(const TreeIter& iter, int column, const DataType& data)
{
	G::Value value(gtk_list_store()->column_headers[column]);
	value.set(data);
	gtk_list_store_set_value(gtk_list_store(), iter, column, value.g_value());
}

template<typename DataType>
inline void
Xfc::Gtk::ListStore::set_enum(const TreeIter& iter, int column, const DataType& data)
{
	G::Value value(gtk_list_store()->column_headers[column]);
	value.set((int)data);
	gtk_list_store_set_value(gtk_list_store(), iter, column, value.g_value());
}

template<typename DataType>
inline void
Xfc::Gtk::ListStore::set_object(const TreeIter& iter, int column, const DataType& data)
{
	G::Value value(gtk_list_store()->column_headers[column]);
	value.set((G::Object*)data);
	gtk_list_store_set_value(gtk_list_store(), iter, column, value.g_value());
}

template<typename DataType>
inline void
Xfc::Gtk::ListStore::set_pointer(const TreeIter& iter, int column, const DataType& data)
{
	G::Value value(gtk_list_store()->column_headers[column]);
	value.set((void*)data);
	gtk_list_store_set_value(gtk_list_store(), iter, column, value.g_value());
}

