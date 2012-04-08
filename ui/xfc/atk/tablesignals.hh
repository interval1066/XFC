/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
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

/// @file xfc/atk/tablesignals.hh
/// @brief Atk::Table virtual signal handlers.
///
/// Provides Atk::TableSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Atk::Table objects.

#ifndef XFC_ATK_TABLE_SIGNALS_HH
#define XFC_ATK_TABLE_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace Atk {

/// @class TableSignals tablesignals.hh xfc/atk/tablesignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Atk::Table.

class TableSignals : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	virtual ~TableSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_row_inserted(int row, int num_inserted);
	///< Called when one or more rows are inserted into the table.
	///< @param row The index of the first row inserted.
	///< @param num_inserted The number of rows inserted.

	virtual void on_column_inserted(int column, int num_inserted);
	///< Called when one or more columns are inserted into the table.
	///< @param column The index of the first column inserted.
	///< @param num_inserted The number of columns inserted.

	virtual void on_row_deleted(int row, int num_deleted);
	///< Called when one or more rows in the table are deleted.
	///< @param row The index of the first row deleted.
	///< @param num_deleted The number of rows deleted.

	virtual void on_column_deleted(int column, int num_deleted);
	///< Called when one or more columns in the table are deleted.
	///< @param column The index of the first column deleted.
	///< @param num_deleted The number of columns deleted.

	virtual void on_row_reordered();
	///< Called when the rows in the table are reordered.

	virtual void on_column_reordered();
	///< Called when the columns in the table are reordered.

	virtual void on_model_changed();
	///< Called when a model_changed signal is received.

/// @}
};

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_TABLE_SIGNALS_HH

