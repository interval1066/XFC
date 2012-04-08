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
 
/// @file xfc/gtk/entrysignals.hh
/// @brief Gtk::Entry virtual signal handlers.
///
/// Provides Gtk::EntrySignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Entry objects.

#ifndef XFC_GTK_ENTRY_SIGNALS_HH
#define XFC_GTK_ENTRY_SIGNALS_HH

#ifndef XFC_GTK_WIDGET_SIGNALS_HH
#include <xfc/gtk/widgetsignals.hh>
#endif

#ifndef XFC_GTK_EDITABLE_SIGNALS_HH
#include <xfc/gtk/editablesignals.hh>
#endif

#ifndef XFC_GTK_CELL_EDITABLE_SIGNALS_HH
#include <xfc/gtk/celleditablesignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class EntrySignals entrysignals.hh xfc/gtk/entrysignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Entry.

class EntrySignals : public WidgetSignals, public EditableSignals, public CellEditableSignals
{
protected:
/// @name Constructors
/// @{

	EntrySignals(Entry *entry);
	///< Construct a new EntrySignals object.
	///< @param entry An Entry object inheriting the EntrySignals implementation.

	virtual ~EntrySignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_populate_popup(Menu& menu);
	///< Called when the Entry displays its context-sensitive menu.
	///< @param menu The popup menu.

	virtual void on_activate();
	///< Called when the Entry is activated by pressing the enter key.

	virtual void on_insert_at_cursor(const String& text);
	///< Called when text is inserted into the Entry at the current cursor position.
	///< @param text The new text to insert.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_ENTRY_SIGNALS_HH

