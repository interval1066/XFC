/*  XFC: Xfce Foundation Classes (Core Library)
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

/// @file xfc/glib/objectsignals.hh
/// @brief G::Object virtual signal handlers.
///
/// Provides G::ObjectSignals, an abstract base class that implements
/// the overridable virtual signal handlers for G::Object.

#ifndef XFC_G_OBJECT_SIGNALS_HH
#define XFC_G_OBJECT_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace G {

/// @class ObjectSignals objectsignals.hh xfc/glib/objectsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for G::Object.
///
/// In XFC a signal object is an abstract implementation class that implements the
/// vitual signal handling mechanism for the corresponding instance object. 
/// Signal objects can only be used as a base class to multiplely inherit from.
/// This way, the overhead associated with multiple virtual function calls and
/// large virtual function tables is minimized by not forcing you to accept
/// this overhead when your not overriding any virtual signal handlers.
///
/// The main reason to override an object's virtual signal handlers would be to
/// customize an object's default response to one or more signals. You should note
/// that in XFC each virtual signal handler is called before the corresponding default
/// GTK+ signal handler. This gives you the powerful choice of either calling or not 
/// calling the default handler. Another reason to override an object's virtual signal
/// handlers would be for convenience. When your deriving a new class from an exisiting 
/// object instead of connecting to object signals in your constructor using the object's
/// proxy signal functions (ligsigc) you can override one or more of the object's virtual
/// signal handlers by multiplely inheriting your new class from the object's signal class. 
/// For example, to create a main window and override the on_delete_event() signal handler
/// you would do something like this:
/// 
/// @code
/// #include <xfc/gtk/window.hh>
/// #include <xfc/gtk/windowsignals.hh>
///
/// using namespace Xfc;
///
/// class MyWindow : public Gtk::Window, protected Gtk::WindowSignals
/// {
///     virtual bool on_delete_event(const Gdk::EventAny& event);
///
/// public: 
///     MyWindow();
/// };

/// MyWindow::MyWindow()
/// : Gtk::WindowSignals(*this)
/// {
///     // put your code here
/// }
/// 
/// bool 
/// MyWindow::on_delete_event(const Gdk::EventAny& event)
/// {
///     // put your code here     
/// 
///     return true;
/// }
/// @endcode

class ObjectSignals : public virtual TypeInstance
{
protected:
/// @name Constructors
/// @{

	ObjectSignals(Object *object);
	///< Constructs a new ObjectSignals object.
	///< @param object A G::Object inheriting the G::ObjectSignals implementation.

	virtual ~ObjectSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_notify(GParamSpec *pspec);
	///< Called when a property on an object is changed.
	///< @param pspec A GParamSpec object that holds the meta data specifying the new property.

/// @}
/// @name Accessors
/// @{

	static GQuark quark();
	///< Returns a quark that indentifies an object's stored signal class pointer.
	///< @return A GQuark value.
	///< 
	///< The pointer will be null if an object doesn't multiplely inherit from G::ObjectSignals. 
	
	static ObjectSignals* pointer(GObject* object);
	///< Returns the signal class pointer attached to <EM>object</EM>.
	///< @return A G::ObjectSignals pointer, or null.
	///<
	///< The returned pointer will be null if the the C++ wrapper class for <EM>object</EM>
	///< doesn't multiplely inherit from G::ObjectSignals.
	
/// @} 
};

} // namespace G

} // namespace Xfc

#endif // XFC_G_OBJECT_SIGNALS_HH

