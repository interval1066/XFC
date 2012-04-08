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

/// @file xfc/gtk/statusbarsignals.hh
/// @brief Gtk::Statusbar virtual signal handlers.
///
/// Provides Gtk::StatusbarSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Statusbar objects.

#ifndef XFC_GTK_STATUSBAR_SIGNALS_HH
#define XFC_GTK_STATUSBAR_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class StatusbarSignals statusbarsignals.hh xfc/gtk/statusbarsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Statusbar.

class StatusbarSignals : public virtual ContainerSignals
{
protected:
/// @name Constructors
/// @{

	StatusbarSignals(Statusbar *statusbar);
	///< Constructs a new StatusbarSignals object.
	///< @param statusbar A Statusbar object inheriting the StatusbarSignals implementation.

	virtual ~StatusbarSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_text_pushed(unsigned int context_id, const String& text);
	///< Called whenever a new message gets pushed onto a statusbar's stack.
	///< @param context_id The context id of the relevant message.
	///< @param text The message that was pushed.

	virtual void on_text_popped(unsigned int context_id, const String& text);
	///< Called whenever a new message is popped off a statusbar's stack.
	///< @param context_id The context id of the relevant message.
	///< @param text The message that was just popped.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_STATUSBAR_SIGNALS_HH

