/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  treemodel.inl - Gtk::TreePath, Gtk::TreeIter, Gtk::TreeModel and Gtk::TreeRowReference inline functions
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

/*  Gtk::TreePath
 */

inline GtkTreePath*
Xfc::Gtk::TreePath::gtk_tree_path() const
{
	return reinterpret_cast<GtkTreePath*>(boxed_);
}

inline Xfc::Gtk::TreePath::operator GtkTreePath* () const
{
	return this ? gtk_tree_path() : 0;
}

inline int
Xfc::Gtk::TreePath::get_depth() const
{
	return gtk_tree_path_get_depth(gtk_tree_path());
}

inline void
Xfc::Gtk::TreePath::append_index(int index)
{
	gtk_tree_path_append_index(gtk_tree_path(), index);
}

inline void
Xfc::Gtk::TreePath::prepend_index(int index)
{
	gtk_tree_path_prepend_index(gtk_tree_path(), index);
}

inline void
Xfc::Gtk::TreePath::next()
{
	gtk_tree_path_next(gtk_tree_path());
}

inline bool
Xfc::Gtk::TreePath::prev()
{
	return gtk_tree_path_prev(gtk_tree_path());
}

inline bool
Xfc::Gtk::TreePath::up()
{
	return gtk_tree_path_up(gtk_tree_path());
}

inline void
Xfc::Gtk::TreePath::down()
{
	gtk_tree_path_down(gtk_tree_path());
}

/*  TreeIter
 */

inline GtkTreeIter*
Xfc::Gtk::TreeIter::gtk_tree_iter() const
{
	return reinterpret_cast<GtkTreeIter*>(boxed_);
}

inline Xfc::Gtk::TreeIter::operator GtkTreeIter* () const
{
	return this ? gtk_tree_iter() : 0;
}

/*  Gtk::TreeModel
 */

inline GtkTreeModel*
Xfc::Gtk::TreeModel::gtk_tree_model() const
{
	return reinterpret_cast<GtkTreeModel*>(instance_);
}

inline Xfc::Gtk::TreeModel::operator GtkTreeModel* () const
{
	return this ? gtk_tree_model() : 0;
}

inline Xfc::Gtk::TreeModelFlagsField
Xfc::Gtk::TreeModel::get_flags() const
{
	return (TreeModelFlagsField)gtk_tree_model_get_flags((GtkTreeModel*)instance_);
}

inline int
Xfc::Gtk::TreeModel::get_n_columns() const
{
	return gtk_tree_model_get_n_columns(gtk_tree_model());
}

inline GType
Xfc::Gtk::TreeModel::get_column_type(int index) const
{
	return gtk_tree_model_get_column_type(gtk_tree_model(), index);
}

template<typename DataType>
inline void
Xfc::Gtk::TreeModel::get_value(const TreeIter& iter, int column, DataType& data) const
{
	G::Value value;
	gtk_tree_model_get_value(gtk_tree_model(), iter, column, value.g_value());
	value.get(data);
}

template<typename DataType>
inline void
Xfc::Gtk::TreeModel::get_enum(const TreeIter& iter, int column, DataType& data) const
{
	G::Value value;
	gtk_tree_model_get_value(gtk_tree_model(), iter, column, value.g_value());
	int tmp_data;
	value.get(tmp_data);
	data = static_cast<DataType>(tmp_data);
}

template<typename DataType>
inline void
Xfc::Gtk::TreeModel::get_object(const TreeIter& iter, int column, DataType& data) const
{
	G::Value value;
	gtk_tree_model_get_value(gtk_tree_model(), iter, column, value.g_value());
	G::Object *object;
	value.get(object);
	data = static_cast<DataType>(object);
}

template<typename DataType>
inline void
Xfc::Gtk::TreeModel::get_pointer(const TreeIter& iter, int column, DataType& data) const
{
	G::Value value;
	gtk_tree_model_get_value(gtk_tree_model(), iter, column, value.g_value());
	void *tmp_data = 0;
	value.get(tmp_data);
	data = static_cast<DataType>(tmp_data);
}

inline const Xfc::Gtk::TreeModel::RowChangedSignalProxy
Xfc::Gtk::TreeModel::signal_row_changed()
{
	return RowChangedSignalProxy(this, &row_changed_signal);
}

inline const Xfc::Gtk::TreeModel::RowInsertedSignalProxy
Xfc::Gtk::TreeModel::signal_row_inserted()
{
	return RowInsertedSignalProxy(this, &row_inserted_signal);
}

inline const Xfc::Gtk::TreeModel::RowHasChildToggledSignalProxy
Xfc::Gtk::TreeModel::signal_row_has_child_toggled()
{
	return RowHasChildToggledSignalProxy(this, &row_has_child_toggled_signal);
}

inline const Xfc::Gtk::TreeModel::RowDeletedSignalProxy
Xfc::Gtk::TreeModel::signal_row_deleted()
{
	return RowDeletedSignalProxy(this, &row_deleted_signal);
}

inline const Xfc::Gtk::TreeModel::RowsReorderedSignalProxy
Xfc::Gtk::TreeModel::signal_rows_reordered()
{
	return RowsReorderedSignalProxy(this, &rows_reordered_signal);
}

/*  Gtk::TreeRowReference
 */

inline GtkTreeRowReference*
Xfc::Gtk::TreeRowReference::gtk_tree_row_reference() const
{
	return reinterpret_cast<GtkTreeRowReference*>(boxed_);
}

inline Xfc::Gtk::TreeRowReference::operator GtkTreeRowReference* () const
{
	return this ? gtk_tree_row_reference() : 0;
}

inline bool
Xfc::Gtk::TreeRowReference::valid() const
{
	return gtk_tree_row_reference_valid(gtk_tree_row_reference());
}

