/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  tableiface.hh - Private interface
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

#ifndef XFC_ATK_TABLE_IFACE_HH
#define XFC_ATK_TABLE_IFACE_HH

namespace Xfc {

namespace Atk {

class TableIface
{
public:
	static void init(AtkTableIface *g_iface);

	static AtkTableIface* get_parent_iface(void *instance);

	static void row_inserted_proxy(AtkTable *table, gint row, gint num_inserted);

	static void column_inserted_proxy(AtkTable *table, gint column, gint num_inserted);

	static void row_deleted_proxy(AtkTable *table, gint row, gint num_deleted);

	static void column_deleted_proxy(AtkTable *table, gint column, gint num_deleted);

	static void row_reordered_proxy(AtkTable *table);

	static void column_reordered_proxy(AtkTable *table);

	static void model_changed_proxy(AtkTable *table);
};

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_TABLE_IFACE_HH
