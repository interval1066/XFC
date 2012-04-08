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
 
/// @file xfc/gtk/celleditable.hh
/// @brief A GtkCellEditable C++ wrapper interface.
///
/// Provides CellEditable, an interface for widgets which can be used for editing cells.

#ifndef XFC_GTK_CELL_EDITABLE_HH
#define XFC_GTK_CELL_EDITABLE_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

#ifndef __GTK_CELL_EDITABLE_H__
#include <gtk/gtkcelleditable.h>
#endif

namespace Xfc {

namespace Gdk {
class Event;
}

namespace Gtk {

/// @class CellEditable celleditable.hh xfc/gtk/celleditable.hh
/// @brief A GtkCellEditable C++ wrapper class.
///
/// CellEditable is an abstract interface that Entry implements through
/// multiple inheritance. CellRenderer returns a smart pointer to a 
/// CellEditable when you call CellRenderer::start_editing(). Using this
/// pointer, you can monitor the editing process by connecting to either
/// its editing_done_signal or remove_widget_signal.

class CellEditable : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	CellEditable();
	///< Constructs a new CellEditable object.	
	
	virtual ~CellEditable() = 0;
	///< Destructor.
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> EditingDoneSignalType;
	typedef G::SignalProxy<TypeInstance, EditingDoneSignalType> EditingDoneSignalProxy;
	static const EditingDoneSignalType editing_done_signal;
	///< Editing done signal (see signal_editing_done()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> RemoveWidgetSignalType;
	typedef G::SignalProxy<TypeInstance, RemoveWidgetSignalType> RemoveWidgetSignalProxy;
	static const RemoveWidgetSignalType remove_widget_signal;
	///< Remove widget signal (see signal_remove_widget()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
/// @name Accessors
/// @{

	GtkCellEditable* gtk_cell_editable() const;
	///< Get a pointer to the GtkCellEditable structure.

	operator GtkCellEditable* () const;
	///< Conversion operator; safely converts a Calendar to a GtkCalendar pointer.

/// @}
/// @name Methods
/// @{

	void start_editing(const Gdk::Event *event);
	///< Begins editing on a cell_editable. 
	///< @param event A Gdk::Event, or null.
	///<
	///< The <EM>event</EM> is the Gdk::Event that began the editing process. It may be null,
	///< in the instance that editing was initiated through programatic means.

	void editing_done();
	///< Emits the "editing_done" signal.
	///< This signal is a sign for the cell renderer to update it's value from the cell.

	void remove_widget();
	///< Emits the "remove_widget" signal. 
	///< This signal is meant to indicate that the cell is finished editing, and the
	///< editable widget may now be destroyed.

/// @}
/// @name Signal Proxies
/// @{

	const EditingDoneSignalProxy signal_editing_done();
	///< Connect to the editing_done_signal; emitted when the cell renderer should
	/// update it's value from the cell.

	const RemoveWidgetSignalProxy signal_remove_widget();
	///< Connect to the remove_widget_signal; emitted when the cell is finished editing,
	///< and the editable widget may now be destroyed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/celleditable.inl>

#endif // XFC_GTK_CELL_EDITABLE_HH

