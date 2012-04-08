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
 
/// @file xfc/gtk/socket.hh
/// @brief A GtkSocket C++ wrapper interface.
///
/// Provides Socket, a widget that together with Plug provides the ability to embed widgets
/// from one process into another process in a fashion that is transparent to the user.

#ifndef XFC_GTK_SOCKET_HH
#define XFC_GTK_SOCKET_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_SOCKET_H__
#include <gtk/gtksocket.h>
#endif

namespace Xfc {
	
namespace Gtk {

/// @class Socket socket.hh xfc/gtk/socket.hh
/// @brief A GtkSocket C++ wrapper class.
///
/// Together with Plug, Socket provides the ability to embed widgets from one process into
/// another process in a fashion that is transparent to the user. One process creates a 
/// Socket widget and, passes that widget's window ID to the other process, which then
/// creates a Plug with that window ID. Any widgets contained in the Plug will then appear
/// inside the first applications window.
///
/// The socket's window ID is obtained by using get_id(). Before using this method, the 
/// socket must have been realized, and hence, have been added to its parent.
///
/// <B>Example:</B> Obtaining the window ID of a socket.
/// @code
/// Gtk::Socket *socket = new Gtk::Socket;
/// socket->show();
/// parent->add(*socket);
///
/// // The following call is only necessary if one of
/// // the ancestors of the socket is not yet visible.
/// socket->realize();
/// g_print("The ID of the sockets window is %x\n", gtk_socket_get_id (socket));
/// @endcode
/// Note that if you pass the window ID of the socket to another process that will create
/// a plug in the socket, you must make sure that the socket widget is not destroyed until
/// that plug is created. Violating this rule will cause unpredictable consequences, the 
/// most likely consequence being that the plug will appear as a separate toplevel window.
/// You can check if the plug has been created by examining plug_window(). If this accessor
/// is non-null, then the plug has been successfully created inside of the socket.
///
/// When GTK+ is notified that the embedded window has been destroyed, then it will destroy
/// the socket as well. You should always, therefore, be prepared for your sockets to be
/// destroyed at any time when the main event loop is running. The communication between a
/// Socket and a Plug follows the XEmbed protocol. This protocol has also been implemented
/// in other toolkits, e.g. Qt, allowing the same level of integration when embedding a Qt
/// widget in GTK or vice versa.

class Socket : public Container
{
	friend class G::Object;

	Socket(const Socket&);
	Socket& operator=(const Socket&);
	
protected:
/// @name Constructors
/// @{

	explicit Socket(GtkSocket *socket, bool owns_reference = false);
	///< Construct a new Socket from an existing GtkSocket.
	///< @param socket A pointer to a GtkSocket.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>socket</EM> can be a newly created GtkSocket or an existing
	///< GtkSocket (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> PlugAddedSignalType;
	typedef G::SignalProxy<TypeInstance, PlugAddedSignalType> PlugAddedSignalProxy;
	static const PlugAddedSignalType plug_added_signal;
	///< Plug added signal (see signal_plug_added()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<bool> PlugRemovedSignalType;
	typedef G::SignalProxy<TypeInstance, PlugRemovedSignalType> PlugRemovedSignalProxy;
	static const PlugRemovedSignalType plug_removed_signal;
	///< Plug removed signal (see signal_plug_removed()). Calls a slot with the signature:
	///< @code
	///< bool function();
	///< @endcode
	
/// @}

public:
	typedef GtkSocket CObjectType;

/// @name Constructors

	Socket();
	///< Construct a new socket.

	virtual ~Socket();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkSocket* gtk_socket() const;
	///< Get a pointer to the GtkSocket structure.

	operator GtkSocket* () const;
	///< Conversion operator; safely converts a Socket to a GtkSocket pointer.

	bool has_plug() const;
	///< Returns true if this socket has a plug.
	
	Gdk::Window* plug_window() const;
	///< Returns the Gdk::Window for the plug.
	
	Widget* plug_widget() const;
	///< Returns the widget embedded into the socket.

	bool same_app() const;
	///< Returns true if the plug and socket are in the same application.
	
	GdkNativeWindow get_id() const;
	///< Gets the window ID of a Socket widget, which can then be used to create
	///< a client embedded inside the socket, for instance with Gtk::Plug.
	///< @return The window ID for the socket.
	///<
	///< The Socket must have already been added into a toplevel window before
	///< you can make this call.

/// @}
/// @name Methods
/// @{

	void add_id(GdkNativeWindow window_id);
	///< Adds an XEMBED client, such as a Plug, to the Socket. 
	///< @param window_id The window ID of a client participating in the XEMBED protocol.
	///<
	///< The client may be in the same process or in a different process. To embed
	///< a Plug in a Socket, you can either create a new Plug, or call Gtk::Plug::get_id()
	///< to get the window ID of the plug, and then pass that to add_id(), or you can call
	///< Gtk::Socket::get_id() to get the window ID for the socket, and pass to Gtk::Plug
	///< in the ID. The Socket must have already be added into a toplevel window before
	///< you can make this call.

/// @}
/// @name Signal Proxies
/// @{
	
	const PlugAddedSignalProxy signal_plug_added();
	///< Connect to the plug_added_signal; emitted when a widget is embedded into a socket.

	const PlugRemovedSignalProxy signal_plug_removed();
	///< Connect to the plug_removed_signal; emitted when a widget is removed from a socket.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/socket.inl>

#endif // XFC_GTK_SOCKET_HH

