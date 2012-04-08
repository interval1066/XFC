/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  table.inl - Atk::Table inline functions
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

inline AtkTable*
Xfc::Atk::Table::atk_table() const
{
	return reinterpret_cast<AtkTable*>(instance_);
}

inline Xfc::Atk::Table::operator AtkTable* () const
{
	return this ? atk_table() : 0;
}

inline int
Xfc::Atk::Table::get_index_at(int row, int column) const
{
	return atk_table_get_index_at(atk_table(), row, column);
}

inline int
Xfc::Atk::Table::get_column_at_index(int index) const
{
	return atk_table_get_column_at_index(atk_table(), index);
}

inline int
Xfc::Atk::Table::get_row_at_index(int index) const
{
	return atk_table_get_row_at_index(atk_table(), index);
}

inline int
Xfc::Atk::Table::get_n_columns() const
{
	return atk_table_get_n_columns(atk_table());
}

inline int
Xfc::Atk::Table::get_n_rows() const
{
	return atk_table_get_n_rows(atk_table());
}

inline int
Xfc::Atk::Table::get_column_extent_at(int row, int column) const
{
	return atk_table_get_column_extent_at(atk_table(), row, column);
}

inline int
Xfc::Atk::Table::get_row_extent_at(int row, int column) const
{
	return atk_table_get_row_extent_at(atk_table(), row, column);
}

inline bool
Xfc::Atk::Table::is_column_selected(int column) const
{
	return atk_table_is_column_selected(atk_table(), column);
}

inline bool
Xfc::Atk::Table::is_row_selected(int row) const
{
	return atk_table_is_row_selected(atk_table(), row);
}

inline bool
Xfc::Atk::Table::is_selected(int row, int column) const
{
	return atk_table_is_selected(atk_table(), row, column);
}

inline void
Xfc::Atk::Table::set_column_description(int column, const char *description)
{
	atk_table_set_column_description(atk_table(), column, description);
}

inline void
Xfc::Atk::Table::set_row_description(int row, const char *description)
{
	atk_table_set_row_description(atk_table(), row, description);
}

inline bool
Xfc::Atk::Table::add_row_selection(int row)
{
	return atk_table_add_row_selection(atk_table(), row);
}

inline bool
Xfc::Atk::Table::remove_row_selection(int row)
{
	return atk_table_remove_row_selection(atk_table(), row);
}

inline bool
Xfc::Atk::Table::add_column_selection(int column)
{
	return atk_table_add_column_selection(atk_table(), column);
}

inline bool
Xfc::Atk::Table::remove_column_selection(int column)
{
	return atk_table_remove_column_selection(atk_table(), column);
}

inline const Xfc::Atk::Table::RowInsertedSignalProxy
Xfc::Atk::Table::signal_row_inserted()
{
	return RowInsertedSignalProxy(this, &row_inserted_signal);
}

inline const Xfc::Atk::Table::ColumnInsertedSignalProxy
Xfc::Atk::Table::signal_column_inserted()
{
	return ColumnInsertedSignalProxy(this, &column_inserted_signal);
}

inline const Xfc::Atk::Table::RowDeletedSignalProxy
Xfc::Atk::Table::signal_row_deleted()
{
	return RowDeletedSignalProxy(this, &row_deleted_signal);
}

inline const Xfc::Atk::Table::ColumnDeletedSignalProxy
Xfc::Atk::Table::signal_column_deleted()
{
	return ColumnDeletedSignalProxy(this, &column_deleted_signal);
}

inline const Xfc::Atk::Table::RowReorderedSignalProxy
Xfc::Atk::Table::signal_row_reordered()
{
	return RowReorderedSignalProxy(this, &row_reordered_signal);
}

inline const Xfc::Atk::Table::ColumnReorderedSignalProxy
Xfc::Atk::Table::signal_column_reordered()
{
	return ColumnReorderedSignalProxy(this, &column_reordered_signal);
}

inline const Xfc::Atk::Table::ModelChangedSignalProxy
Xfc::Atk::Table::signal_model_changed()
{
	return ModelChangedSignalProxy(this, &model_changed_signal);
}

