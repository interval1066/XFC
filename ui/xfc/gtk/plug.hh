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
 
/// @file xfc/gtk/plug.hh
/// @brief A GtkPlug C++ wrapper interface.
///
/// Provides Plug, which together with Socket, provides the ability to embed widgets
/// from one process into another process in a fashion that is transparent to the user.

#ifndef XFC_GTK_PLUG_HH
#define XFC_GTK_PLUG_HH

#ifndef XFC_GTK_WINDOW_HH
#include <xfc/gtk/window.hh>
#endif

#ifndef __GTK_PLUG_H__
#include <gtk/gtkplug.h>
#endif

namespace Xfc {

namespace Gdk {
class Display;
}

namespace Gtk {

class Socket;

/// @class Plug plug.hh xfc/gtk/plug.hh
/// @brief A GtkPlug C++ wrapper class.
///
/// Together with Socket, Plug provides the ability to embed widgets from one process
/// into another process in a fashion that is transparent to the user. One process
/// creates a Socket widget and, passes the ID of that widgets window to the other
/// process, which then creates a Plug with that window ID. Any widgets contained in
/// the Plug then will appear inside the first applications window.

class Plug : public Window
{
	friend class G::Object;

	Plug(const Plug&);
	Plug& operator=(const Plug&);
	
protected:
/// @name Constructors
/// @{

	explicit Plug(GtkPlug *plug, bool owns_reference = false);
	///< Construct a new Plug from an existing GtkPlug.
	///< @param plug A pointer to a GtkPlug.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>plug</EM> can be a newly created GtkPlug or an existing
	///< GtkPlug (see G::Object::Object).

/// @}
/// @name Signal Prototypes

	typedef G::Signal<void> EmbeddedSignalType;
	typedef G::SignalProxy<TypeInstance, EmbeddedSignalType> EmbeddedSignalProxy;
	static const EmbeddedSignalType embedded_signal;
	///< Embedded signal (see signal_embedded()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkPlug CObjectType;

/// @name Constructors
/// @{

	Plug(GdkNativeWindow socket_id, const Gdk::Display *display = 0);
	///< Constructs a new plug widget inside the Socket identified by socket_id.
	///< @param socket_id The XID of the socket's window.
	///< @param display The Gdk::Display on which socket_id is displayed, or null for the default display.
	///<
	///< If socket_id is 0, the plug is left "unplugged" and can later be plugged
	///< into a Socket by Gtk::Socket::add_id().
	///< 
	///< <B>Note:</B> The default GDK display is the only display in the absence of MultiHead support.

	virtual ~Plug();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkPlug* gtk_plug() const;
	///< Get a pointer to the GtkPlug structure.

	operator GtkPlug* () const;
	///< Conversion operator; safely converts a Plug to a GtkPlug pointer.

	bool has_socket() const;
	///< Returns true if this plug is embedded into a socket.

	Gdk::Window* socket_window() const;
	///< Returns the socket window the plug is embedded into, or null if it is not embedded.

	bool same_app() const;
	///< Return true if the plug is embedded into a socket in the same application.
	
	GdkNativeWindow get_id() const;
	///< Gets the window ID of a Plug widget, which can then be used to embed this window
	///< inside another window, for instance with Gtk::Socket::add_id().
	///< @return The window ID for the plug.

/// @}
/// @name Signal Proxies

	const EmbeddedSignalProxy signal_embedded();
	///< Connect to the embedded_signal; emitted when a plug is embedded into a socket.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/plug.inl>

#endif // XFC_GTK_PLUG_HH

