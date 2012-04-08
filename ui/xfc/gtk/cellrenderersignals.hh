/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/gtk/cellrenderersignals.hh
/// @brief Gtk::CellRenderer virtual signal handlers.
///
/// Provides Gtk::CellRendererSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::CellRenderer objects.

#ifndef XFC_GTK_CELL_RENDERER_SIGNALS_HH
#define XFC_GTK_CELL_RENDERER_SIGNALS_HH

#ifndef XFC_GTK_OBJECT_SIGNALS_HH
#include <xfc/gtk/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class CellRendererSignals cellrenderersignals.hh xfc/gtk/cellrenderersignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::CellRenderer.

class CellRendererSignals : public ObjectSignals
{
protected:
/// @name Constructors
/// @{

	CellRendererSignals(CellRenderer *cell);
	///< Construct a new CellRendererSignals object.	
	///< @param cell A CellRenderer object inheriting the CellRendererSignals implementation.
	
	virtual ~CellRendererSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	void on_editing_canceled();
	///< Called to notify a client program that an editing process was canceled and
	///< the changes were not committed.

	void on_editing_started(CellEditable *editable, const String& path);
	///< Called when a cell starts to be edited.
	///< @param editable The CellEditable.
	///< @param path The path identifying the edited cell. 
	///<
 	///< The indended use of this signal is to do special setup on editable, e.g. adding
	///< a Gtk::EntryCompletion or setting up additional columns in a Gtk::ComboBox. Note
	///< that GTK+ doesn't guarantee that cell renderers will continue to use the same 
	///< kind of widget for editing in future releases, therefore you should check the 
	///< type of editable before doing any specific setup, as in the following example:
	///<
	///< @code
	///< void
	///< MyClass::on_editing_started(CellEditable *editable, const String& path)
	///< {
	///<     if (editable->is_a(GTK_TYPE_ENTRY))
	///<     {
	///<         Gtk::Entry *entry = dynamic_cast<Gtk::Entry*>(editable);
	///<         // create an entry completion
 	///<         entry->set_completion(completion);
	///<     }
	///< }
	///< @endcode    

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_CELL_RENDERER_SIGNALS_HH

