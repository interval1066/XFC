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

/// @file xfc/gtk/object.hh
/// @brief A GtkObject C++ wrapper interface.
///
/// Provides Object and ObjectImpl. Gtk::Object is the base class for all widgets,
/// and for a few non-widget objects such as Adjustment. Gtk::ObjectImpl is the base
/// for all extended widget implementation classes

#ifndef XFC_GTK_OBJECT_HH
#define XFC_GTK_OBJECT_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef __GTK_OBJECT_H__
#include <gtk/gtkobject.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Object object.hh xfc/gtk/object.hh
/// @brief A GtkObject C++ wrapper class.
///
/// Object is the base class for all widgets, and for a few non-widget objects such as Adjustment.
/// Object predates G::Object; non-widgets that derive from Gtk::Object rather than G::Object
/// do so for backward compatibility reasons. The most interesting difference between Gtk::Object
/// and G::Object is the "floating" reference count. A G::Object is created with a reference count
/// of 1, owned by the creator of the G::Object. (The owner of a reference is the code section that
/// has the right to call G::Object::unref() in order to remove that reference.) A Gtk::Object is
/// created with a reference count of 1 also, but it isn't owned by anyone. Calling G::Object::unref()
/// on the newly-created Gtk::Object is incorrect. Instead, the initial reference count of a Gtk::Object
/// is "floating". The floating reference can be removed by anyone at any time, by calling sink().
/// Sinking an object does nothing if the object is already sunk (has no floating reference).
///
/// When you add a widget to its parent container, the parent GTK+ container will do this:
/// @code
/// g_object_ref (G_OBJECT (child_widget));
/// gtk_object_sink (GTK_OBJECT (child_widget));
/// @endcode
/// This means that the container now owns a reference to the child widget (since it called
/// g_object_ref()), and the child widget has no floating reference. If you want to hold onto
/// a reference to the child widget you would have to reference then sink the child widget
/// yourself. In XFC, Gtk::Object::ref() does this for you, by sinking any widget with a
/// floating reference.
///
/// The purpose of the floating reference is to keep the child widget alive until you add
/// it to a parent container:
/// @code
/// Gtk::Button *button = new Gtk::Button;
/// // button has one floating reference to keep it alive.
/// 
/// container->add(*button);
/// // button has one non-floating reference owned by the container.
/// @endcode
///
/// Gtk::Window is a special case, because GTK+ itself will ref/sink it on creation.
/// That is, after constructing a new Gtk::Window it will have one reference which
/// is owned by GTK+, and is not a floating reference.
/// 
/// One more factor comes into play: the "destroy" signal, emitted by the Gtk::Object::dispose()
/// method. The "destroy" signal asks all code owning a reference to an object to release said
/// reference. So, for example, if you call Gtk::Object::dispose() on a Gtk::Window, GTK+ will
/// release the reference count that it owns; if you call Gtk::Object::dispose() on a Button, 
/// then the button will be removed from its parent container and the parent container will
/// release its reference to the button. Because these references are released, calling dispose()
/// should result in freeing all memory associated with an object, unless some buggy code fails
/// to release its references in response to the "destroy" signal. Freeing memory (referred to as
/// finalization) only happens if the reference count reaches zero.
///
/// Some simple rules for handling Gtk::Object's:
/// - Never call unref() unless you have previously called ref(), even if you created the object.
///   (Note: this is not true for G::Object; for G::Object, the creator of the object owns a reference.)
/// - Call dispose() to get rid of most objects in most cases. In particular, widgets are almost
///   always destroyed in this way.
/// - Because of the floating reference count, you don't need to worry about reference counting
///   for widgets and toplevel windows, unless you explicitly call ref() yourself.

class Object : public G::Object
{
	friend class G::Object;

	Object(const Object&);
	Object& operator=(const Object&);

protected:
/// @name Constructors
/// @{

	explicit Object(GtkObject *object, bool owns_reference = false);
	///< Construct a new Object from an existing GtkObject.
	///< @param object A pointer to a GtkObject.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>object</EM> can be a newly created GtkObject or an existing
	///< GtkObject (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> DestroySignalType;
	typedef G::SignalProxy<TypeInstance, DestroySignalType> DestroySignalProxy;
	static const DestroySignalType destroy_signal;
	///< Destroy signal (see signal_destroy()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkObject CObjectType;

/// @name Constructors
/// @{

	virtual ~Object();
	///< Desructor.

/// @}
/// @name Accessors

	GtkObject* gtk_object() const;
	///< Get a pointer to the GtkObject structure.

	operator GtkObject* () const;
	///< Conversion operator; safely converts an Object to a GtkObject pointer.

/// @}
/// @name Methods
/// @{

	void sink();
	///< Removes the floating reference from an object, if it exists; otherwise does nothing.
	///< The ref() method calls this function to sink any object with a floating reference.
	///< So as a rule you shouldn't need to call this method at all.

	virtual void ref();
	///< Increases the reference count of the object.
	///< This method calls G::Object::ref() first and then sink() to sink the object if it
	///< has a floating reference.

	virtual void dispose();
	///< Emits the "destroy" signal notifying all reference holders that they should release
	///< the object. See the overview documentation at the top of the page for more details.
	///< The memory for the object itself won't be deleted until its reference count actually
	///< drops to 0; dispose() merely asks reference holders to release their references, it
	///< does not free the object. This method is declared virtual for XFC's use only.

/// @}
/// @name Signal Proxies
/// @{

	const DestroySignalProxy signal_destroy();
	///< Connect to the destroy_signal; emitted when the holder of a reference should release
	///< the reference that they hold.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/object.inl>

#endif // XFC_GTK_OBJECT_HH

