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
 
/// @file xfc/gtk/dialogsignals.hh
/// @brief Gtk::Dialog virtual signal handlers.
///
/// Provides Gtk::DialogSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Dialog objects.

#ifndef XFC_GTK_DIALOG_SIGNALS_HH
#define XFC_GTK_DIALOG_SIGNALS_HH

#ifndef XFC_GTK_WINDOW_SIGNALS_HH
#include <xfc/gtk/windowsignals.hh>
#endif

namespace Xfc {

namespace Gtk {
	
/// @class DialogSignals dialogsignals.hh xfc/gtk/dialogsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Dialog.

class DialogSignals : public WindowSignals
{
protected:
/// @name Constructors
/// @{

	DialogSignals(Dialog *dialog);
	///< Construct a new DialogSignals object.
	///< @param dialog A Dialog object inheriting the DialogSignals implementation.

	virtual ~DialogSignals() = 0;
	///< Destructor.
/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_response(int response_id);
	///< Called when an action widget is activated, the dialog receives a delete event,
	///< or the application programmer calls response().
	///< @param response_id The response ID of the action widget.
	///<
	///< On a delete event, the response ID is RESPONSE_NONE. Otherwise, it depends
	///< on which action widget was activated.

	virtual void on_close();
	///< Called when the user closes the dialog box by pressing the escape key (GDK_Escape).

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_DIALOG_SIGNALS_HH

