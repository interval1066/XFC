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

/// @file xfc/glib/object.hh
/// @brief A GObject C++ wrapper interface.
///
/// Provides G::Object, the base class for all wrapped GTK+ objects.

#ifndef XFC_G_OBJECT_HH
#define XFC_G_OBJECT_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace G {

class Quark;
class Value;

/// @class Object object.hh xfc/glib/object.hh
/// @brief Base class for wrapped GTK+ objects and widgets.
///
/// G::Object wraps the GTK+ stucture GObject and its associated functions. It is the base class
/// from which most C++ wrappers for the various GTK+ objects and widgets are dervied. G::Object
/// is derived from G::TypeInstance and is a reference counted object. You reference a G::Object
/// by calling ref(). This increments the internal reference counter. You unreference a G::Object
/// by calling unref(). This decrements the internal reference counter. Objects that derive directly
/// from G::Object are created with a reference count of 1. This initial reference count is owned
/// by you and must be unreferenced. Because you own the initial reference count you don't need to 
/// reference the object before using it, but you  must remember to unreference it when your finished.
/// When the reference count drops to zero the object is finialized and destroyed. If the object was
/// a created on the heap, operator delete is called to destroy the object. <B>You must not call 
/// operator delete</B> yourself. To destroy an object you own a reference to you call unref(). To 
/// destroy an object you don't own a reference to you must call dispose();

class Object : public virtual TypeInstance
{
	Object(const Object&);
	Object& operator=(const Object&);

	static void destroy_notify(void *data);

protected:
/// @name Constructors
/// @{

	explicit Object(GObject *object, bool owns_reference = true);
	///< Construct a new G::Object from an existing GObject.
	///< @param object A pointer to a GObject.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< This constructor is used to wrap GTK+ objects. <EM>object</EM> can be a pointer to 
	///< newly created GObject or an existing GObject. If <EM>owns_reference</EM> is false the 
	///< object's initial reference count is floating and must not be unreferenced, unless the
	///< object was first referenced. If <EM>owns_reference</EM> is true the gfcal reference 
	///< is owned by you and must be unreferenced. 
	///<
	///< Each derived class declares a similar constructor with a default value for 
	///< <EM>owns_reference</EM> that indicates whether or not the gfcal reference count
	///< is floating. The XFC smart pointer, Xfc::Pointer, uses this value to determine
	///< if the object's initial reference count needs to be cleared.

/// @}
/// @name Signal Prototypes
/// @{

	typedef Signal<void, GParamSpec*> NotifySignalType;
	typedef SignalProxy<TypeInstance, NotifySignalType> NotifySignalProxy;
	static const NotifySignalType notify_signal;
	///< Notify signal (see signal_notify()). Calls a slot with the signature: 
	///< @code
	///< void function(GParamSpec *pspec);
	///< // pspec: A GParamSpec object that holds the meta data specifying the new property.
	///< @endcode

/// @}

public:
	typedef GObject CObjectType;
	
/// @name Constructors
/// @{

	virtual ~Object();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GObject* g_object() const;
	///< Get a pointer to the GObject structure.

	operator GObject* () const;
	///< Conversion operator; safely converts a G::Object to a GObject pointer.

	void get_property(const char *property_name, Value& value) const;
	///< Get a property of an object.
	///< @param property_name Name of property to get the value for.
	///< @param value Reference to a G::Value object that will hold the value for property_name.

	void* get_data(const Quark& quark) const;
	///< Get a user data pointer set by calling set().
	///< @param quark A G::Quark naming the user data pointer.
	///< @return The user data pointer set, or null if none exists.

	void* get_data(const char *key) const;
	void* get_data(const String& key) const;
	///< Get a user data pointer set by calling set().
	///< @param key A string naming the user data pointer.
	///< @return The user data pointer set, or null if none exists.

/// @}
/// @name Accessors
/// @{

	static Object* pointer(GObject* object);
	///< Get the G::Object pointer for the specified GTK+ object.
	///< @param object A pointer to a GTK+ C object.
	///< @return A G::Object pointer, or null if the GTK+ object has no C++ wrapper.

/// @}
/// @name Methods
/// @{

	virtual void ref();
	///< Increase the reference count of the object.
	///< This method is declared virtual for XFC's use only. You are not meant to override it.

	virtual void unref();
	///< Decrease the reference count of the object.
	///< This method is declared virtual for XFC's use only. You are not meant to override it.

	virtual void dispose();
	///< Finalize the object.
	///< This method is declared virtual for XFC's use only.

	void set_property(const char *property_name, const Value& value);
	///< Set a property on an object.
	///< @param property_name Name of the property to set the value for.
	///< @param value A G::Value that holds the value of the propery being set.

	void set_data(const Quark& quark, void *data, GDestroyNotify destroy = 0);
	///< Set an opaque named pointer on an object.
	///< @param quark A G::Quark, naming the user data pointer.
	///< @param data An opaque user data pointer.
	///< @param destroy A static function to invoke with data as its argument, when data needs to be freed.
	///<
	///< This sets an opaque, named pointer on an object. The name is specified through a G::Quark,
	///< and the pointer can be gotten back from the object with get_data() until the object is finalized.
	///< Setting a previously set user data pointer, overrides (frees) the old pointer set, using null as
	///< the pointer essentially removes the data stored.

	void set_data(const char *key, void *data, GDestroyNotify destroy = 0);
	void set_data(const String& key, void *data, GDestroyNotify destroy = 0);
	///< Set an opaque named pointer on an object.
	///< @param key A string naming the user data pointer.
	///< @param data An opaque user data pointer.
	///< @param destroy A static function to invoke with data as its argument, when data needs to be freed.
	///<
	///< This sets an opaque, named pointer on an object. The name is specified through a String,
	///< and the pointer can be gotten back from the object with get_data() until the object is finalized.
	///< Setting a previously set user data pointer, overrides (frees) the old pointer set, using null as
	///< the pointer essentially removes the data stored.

	void* remove_data(const Quark& quark, bool notify = false);
	///< Remove an opaque named pointer previously set on an object.
	///< @param quark A G::Quark, naming the user data pointer.
	///< @param notify Set <EM>true</EM> if the destroy function should be invoked (if any was set).
	///< @return The user data pointer set, or null if none exists or <EM>notify</EM> is true.
	///<
	///< This function gets back user data pointers stored via set_data() and removes the data
	///< from object. If <EM>notify</EM> is true its destroy function is called (if any was set) and
	///< null is returned. Usually you wont use a destroy function so you can ignore <EM>notify</EM>.

	void* remove_data(const char *key, bool notify = false);
	void* remove_data(const String& key, bool notify = false);
	///< Remove an opaque named pointer previously set on an object.
	///< @param key A string naming the user data pointer.
	///< @param notify Set <EM>true</EM> if the destroy function should be invoked (if any was set).
	///< @return the user data pointer set, or null if none exists or <EM>notify</EM> is true.
	///<
	///< This function gets back user data pointers stored via set_data() and removes the data
	///< from object. If <EM>notify</EM> is true its destroy function is called (if any was set) and
	///< null is returned. Usually you wont use a destroy function so you can ignore <EM>notify</EM>.

/// @}
/// @name Signal Methods
/// @{

	void emit_by_name(const char *signal_name, ...);
	///< Emit a signal by name.
	///< @param signal_name The name of the signal.
	///< @param ... The parameters to pass to the signal handler, followed by a pointer to the
	///<            return type, if any.
	///<
	///< This causes the default handler and user-connected handlers to be run.

	void stop_emission_by_name(const char *detailed_signal);
	///< Aborts a signal's current emission by name.
	///< @param detailed_signal The name of the signal you wish to stop.
	///<
	///< The name of the signal you wish to stop is the GTK+ name, not its XFC name.
	///< Signals in XFC are named by adding the "_signal" suffix to the GTK+ name. For
	///< example, the XFC name for the GTK+ "clicked" signal is "clicked_signal".

	bool disconnect_by_name(const char* signal_name);
	///< Disconnect a signal by name. 
	///< @param signal_name The name of the signal.
	///< @return <EM>true</EM> if the signal was disconnected, <EM>false</EM> if <EM>signal_name</EM>
	///< is not connected to this object.
	///<
	///< This is a convenience method that can be used to disconnect a signal when you don't
	///< want to use a Connection object. It looks up the signal_id for <EM>signal name</EM> and
	///< uses it to search for the first signal handler connected to the object. If found, it
	///< disconnects the handler and returns true.

/// @}
/// @name Templates
/// @{

	template<typename T, typename gObject>
	static T* wrap(gObject *object, bool owns_reference = false);
	///< Wrap a GTK+ C object in as C++ wrapper class.
	///< @param object A pointer to a GTK+ C object.
	///< @param owns_reference Set <EM>true</EM> if the GTK+ object must be unreferenced.
	///< @return A pointer to the C++ class cast to a pointer of type T.
	///<
	///< If <EM>object</EM> was previously wrapped this function returns the existing C++ pointer
	///< cast to a pointer of type T. If no wrapper exists a new one is created. Each GTK+ C object
	///< can have only one wrapper. A smart pointer can be used to handle the returned pointer.
	///< Otherwise if T->is_referenced() is true, T->unref() must be explicitly called.

	template<typename T, typename gObject>
	static T* wrap_new(gObject *object, bool owns_reference = false);
	///< Wrap a GTK+ C object in a C++ wrapper class.
	///< @param object A pointer to a GTK+ C object.
	///< @param owns_reference Set <EM>true</EM> if the GTK+ object must be unreferenced.
	///< @return A pointer to the C++ class cast to a pointer of type T.
	///<
	///< Only use this if <EM>object</EM> has not been wrapped before. Usually <EM>reference</EM>
	///< is false. Set <EM>reference</EM> to true if the wrapped object must be unreferenced when
	///< finished.

/// @}
/// @name Signal Proxies
/// @{

	const NotifySignalProxy signal_notify(const char *property_name = 0);
	const NotifySignalProxy signal_notify(const String& property_name);
	///< Connect to the notify_signal; emitted when a property on an object is changed.
	///< @param property_name The property name to be notified of changes to.
	///<
	///< If <EM>property_name</EM> is provided it is appended to the signal name so that
	///< the signal connected to becomes "notify::property_name". What this does is ensure 
	///< that your notification slot is only called if <EM>property_name</EM> matches the
	///< property name of the "notify" signal being emitted. 

/// @}
};

} // namespace G

} // namespace Xfc

#include <xfc/glib/inline/object.inl>

#endif // XFC_G_OBJECT_HH

