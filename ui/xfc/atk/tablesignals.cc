/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  tablesignals.cc - Atk::Table virtual signal handlers
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

#include <atk/atktable.h>
#include "tablesignals.hh"
#include "private/tableiface.hh"

using namespace Xfc;

/*  Atk::TableSignals
 */

Atk::TableSignals::~TableSignals()
{
}

void
Atk::TableSignals::on_row_inserted(int row, int num_inserted)
{
	AtkTableIface *g_iface = TableIface::get_parent_iface(instance_);
	if (g_iface && g_iface->row_inserted)
		g_iface->row_inserted((AtkTable*)instance_, row, num_inserted);
}

void
Atk::TableSignals::on_column_inserted(int column, int num_inserted)
{
	AtkTableIface *g_iface = TableIface::get_parent_iface(instance_);
	if (g_iface && g_iface->column_inserted)
		g_iface->column_inserted((AtkTable*)instance_, column, num_inserted);
}

void
Atk::TableSignals::on_row_deleted(int row, int num_deleted)
{
	AtkTableIface *g_iface = TableIface::get_parent_iface(instance_);
	if (g_iface && g_iface->row_deleted)
		g_iface->row_deleted((AtkTable*)instance_, row, num_deleted);
}

void
Atk::TableSignals::on_column_deleted(int column, int num_deleted)
{
	AtkTableIface *g_iface = TableIface::get_parent_iface(instance_);
	if (g_iface && g_iface->column_deleted)
		g_iface->column_deleted((AtkTable*)instance_, column, num_deleted);
}

void
Atk::TableSignals::on_row_reordered()
{
	AtkTableIface *g_iface = TableIface::get_parent_iface(instance_);
	if (g_iface && g_iface->row_reordered)
		g_iface->row_reordered((AtkTable*)instance_);
}

void
Atk::TableSignals::on_column_reordered()
{
	AtkTableIface *g_iface = TableIface::get_parent_iface(instance_);
	if (g_iface && g_iface->column_reordered)
		g_iface->column_reordered((AtkTable*)instance_);
}

void
Atk::TableSignals::on_model_changed()
{
	AtkTableIface *g_iface = TableIface::get_parent_iface(instance_);
	if (g_iface && g_iface->model_changed)
		g_iface->model_changed((AtkTable*)instance_);
}

