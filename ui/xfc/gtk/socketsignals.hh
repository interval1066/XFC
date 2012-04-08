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

/// @file xfc/gtk/socketsignals.hh
/// @brief Gtk::Socket virtual signal handlers.
///
/// Provides Gtk::SocketSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Socket objects.

#ifndef XFC_GTK_SOCKET_SIGNALS_HH
#define XFC_GTK_SOCKET_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class SocketSignals socketsignals.hh xfc/gtk/socketsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Socket.

class SocketSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	SocketSignals(Socket *socket);
	///< Constructs a new SocketSignals object.
	///< @param socket A Socket object inheriting the SocketSignals implementation.

	virtual ~SocketSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_plug_added();
	///< Called when a widget is embedded into a socket.

	virtual bool on_plug_removed();
	///< Called when a widget is removed from a socket.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOCKET_SIGNALS_HH

