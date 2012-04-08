/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  table.cc - AtkTable C++ wrapper implementation
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

#include "table.hh"
#include "tablesignals.hh"
#include "object.hh"
#include "private/marshal.hh"
#include "private/tableiface.hh"
#include "xfc/glib/object.hh"
#include "xfc/glib/objectsignals.hh"

using namespace Xfc;

/*  Atk::Table
 */

Atk::Table::Table()
{
}

Atk::Table::~Table()
{
}

Atk::Object*
Atk::Table::ref_at(int row, int column) const
{
	AtkObject *object = atk_table_ref_at(atk_table(), row, column);
	return object ? G::Object::wrap<Object>(object) : 0;
}

Atk::Object*
Atk::Table::get_caption() const
{
	AtkObject *object = atk_table_get_caption(atk_table());
	return object ? G::Object::wrap<Object>(object) : 0;
}

String
Atk::Table::get_column_description(int column) const
{
	return atk_table_get_column_description(atk_table(), column);
}

Atk::Object*
Atk::Table::get_column_header(int column) const
{
	AtkObject *object = atk_table_get_column_header(atk_table(), column);
	return object ? G::Object::wrap<Object>(object) : 0;
}

String
Atk::Table::get_row_description(int row) const
{
	return atk_table_get_row_description(atk_table(), row);
}

Atk::Object*
Atk::Table::get_row_header(int row) const
{
	AtkObject *object = atk_table_get_row_header(atk_table(), row);
	return object ? G::Object::wrap<Object>(object) : 0;
}

Atk::Object*
Atk::Table::get_summary() const
{
	AtkObject *object = atk_table_get_summary(atk_table());
	return object ? G::Object::wrap<Object>(object) : 0;
}

bool
Atk::Table::get_selected_columns(std::vector<int>& selected) const
{
	g_return_val_if_fail(selected.empty(), false);
	int *tmp_selected = 0;
	int n_columns = atk_table_get_selected_columns(atk_table(), &tmp_selected);

	int i = 0;
	while (i < n_columns)
	{
		selected.push_back(tmp_selected[i]);
		++i;
	}

	g_free(tmp_selected);
	return !selected.empty();
}

bool
Atk::Table::get_selected_rows(std::vector<int>& selected) const
{
	g_return_val_if_fail(selected.empty(), false);
	int *tmp_selected = 0;
	int n_rows = atk_table_get_selected_rows(atk_table(), &tmp_selected);

	int i = 0;
	while (i < n_rows)
	{
		selected.push_back(tmp_selected[i]);
		++i;
	}

	g_free(tmp_selected);
	return !selected.empty();
}

void
Atk::Table::set_caption(const Object *caption)
{
	atk_table_set_caption(atk_table(), *caption);
}

void
Atk::Table::set_column_description(int column, const String& description)
{
	atk_table_set_column_description(atk_table(), column, description.c_str());
}

void
Atk::Table::set_column_header(int column, const Object *header)
{
	atk_table_set_column_header(atk_table(), column, *header);
}

void
Atk::Table::set_row_description(int row, const String& description)
{
	atk_table_set_row_description(atk_table(), row, description.c_str());
}

void
Atk::Table::set_row_header(int row, const Object *header)
{
	atk_table_set_row_header(atk_table(), row, *header);
}

void
Atk::Table::set_summary(const Object *accessible)
{
	atk_table_set_summary(atk_table(), *accessible);
}

/*  Atk::TableIface
 */

void
Atk::TableIface::init(AtkTableIface *g_iface)
{
	g_iface->row_inserted = &row_inserted_proxy;
	g_iface->column_inserted = &column_inserted_proxy;
	g_iface->row_deleted = &row_deleted_proxy;
	g_iface->column_deleted = &column_deleted_proxy;
	g_iface->row_reordered = &row_reordered_proxy;
	g_iface->column_reordered = &column_reordered_proxy;
	g_iface->model_changed = &model_changed_proxy;
}

AtkTableIface*
Atk::TableIface::get_parent_iface(void *instance)
{
	return static_cast<AtkTableIface*>(g_type_interface_peek_parent(ATK_TABLE_GET_IFACE(instance)));
}

void
Atk::TableIface::row_inserted_proxy(AtkTable *table, gint row, gint num_inserted)
{
	TableSignals *signals = dynamic_cast<TableSignals*>(G::ObjectSignals::pointer((GObject*)table));
	if (signals)
		signals->on_row_inserted(row, num_inserted);
	else
	{
		AtkTableIface *g_iface = get_parent_iface(table);
		if (g_iface && g_iface->row_inserted)
			g_iface->row_inserted(table, row, num_inserted);
	}
}

void
Atk::TableIface::column_inserted_proxy(AtkTable *table, gint column, gint num_inserted)
{
	TableSignals *signals = dynamic_cast<TableSignals*>(G::ObjectSignals::pointer((GObject*)table));
	if (signals)
		signals->on_column_inserted(column, num_inserted);
	else
	{
		AtkTableIface *g_iface = get_parent_iface(table);
		if (g_iface && g_iface->column_inserted)
			g_iface->column_inserted(table, column, num_inserted);
	}
}

void
Atk::TableIface::row_deleted_proxy(AtkTable *table, gint row, gint num_deleted)
{
	TableSignals *signals = dynamic_cast<TableSignals*>(G::ObjectSignals::pointer((GObject*)table));
	if (signals)
		signals->on_row_deleted(row, num_deleted);
	else
	{
		AtkTableIface *g_iface = get_parent_iface(table);
		if (g_iface && g_iface->row_deleted)
			g_iface->row_deleted(table, row, num_deleted);
	}
}

void
Atk::TableIface::column_deleted_proxy(AtkTable *table, gint column, gint num_deleted)
{
	TableSignals *signals = dynamic_cast<TableSignals*>(G::ObjectSignals::pointer((GObject*)table));
	if (signals)
		signals->on_column_deleted(column, num_deleted);
	else
	{
		AtkTableIface *g_iface = get_parent_iface(table);
		if (g_iface && g_iface->column_deleted)
			g_iface->column_deleted(table, column, num_deleted);
	}
}

void
Atk::TableIface::row_reordered_proxy(AtkTable *table)
{
	TableSignals *signals = dynamic_cast<TableSignals*>(G::ObjectSignals::pointer((GObject*)table));
	if (signals)
		signals->on_row_reordered();
	else
	{
		AtkTableIface *g_iface = get_parent_iface(table);
		if (g_iface && g_iface->row_reordered)
			g_iface->row_reordered(table);
	}
}

void
Atk::TableIface::column_reordered_proxy(AtkTable *table)
{
	TableSignals *signals = dynamic_cast<TableSignals*>(G::ObjectSignals::pointer((GObject*)table));
	if (signals)
		signals->on_column_reordered();
	else
	{
		AtkTableIface *g_iface = get_parent_iface(table);
		if (g_iface && g_iface->column_reordered)
			g_iface->column_reordered(table);
	}
}

void
Atk::TableIface::model_changed_proxy(AtkTable *table)
{
	TableSignals *signals = dynamic_cast<TableSignals*>(G::ObjectSignals::pointer((GObject*)table));
	if (signals)
		signals->on_model_changed();
	else
	{
		AtkTableIface *g_iface = get_parent_iface(table);
		if (g_iface && g_iface->model_changed)
			g_iface->model_changed(table);
	}
}

/*  Atk::Table signals
 */

const Atk::Table::RowInsertedSignalType Atk::Table::row_inserted_signal("row_inserted", (GCallback)&G::Marshal::void_int_int_callback);

const Atk::Table::ColumnInsertedSignalType Atk::Table::column_inserted_signal("column_inserted", (GCallback)&G::Marshal::void_int_int_callback);

const Atk::Table::RowDeletedSignalType Atk::Table::row_deleted_signal("row_deleted", (GCallback)&G::Marshal::void_int_int_callback);

const Atk::Table::ColumnDeletedSignalType Atk::Table::column_deleted_signal("column_deleted", (GCallback)&G::Marshal::void_int_int_callback);

const Atk::Table::RowReorderedSignalType Atk::Table::row_reordered_signal("row_reordered", (GCallback)&G::Marshal::void_callback);

const Atk::Table::ColumnReorderedSignalType Atk::Table::column_reordered_signal("column_reordered", (GCallback)&G::Marshal::void_callback);

const Atk::Table::ModelChangedSignalType Atk::Table::model_changed_signal("model_changed", (GCallback)&G::Marshal::void_callback);

