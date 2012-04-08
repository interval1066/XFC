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

/// @file xfc/gtk/actionsignals.hh
/// @brief Gtk::Action virtual signal handlers.
///
/// Provides Gtk::ActionSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Action objects.

#ifndef XFC_GTK_ACTION_SIGNALS_HH
#define XFC_GTK_ACTION_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ActionSignals actionsignals.hh xfc/gtk/actionsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Action.

class ActionSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	ActionSignals(Action *action);
	///< Construct a new ActionSignals object.
	///< @param action An Action object inheriting the ActionSignals implementation.

	virtual ~ActionSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_activate();
	///< Called when the action is activated.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_ACTION_SIGNALS_HH

