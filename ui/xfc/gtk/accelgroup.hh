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

/// @file xfc/gtk/accelgroup.hh
/// @brief GtkAccelGroup C++ wrapper interface.
///
/// Provides Gtk::AccelGroup, an object which represents a group of keyboard accelerators. 

#ifndef XFC_GTK_ACCEL_GROUP_HH
#define XFC_GTK_ACCEL_GROUP_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_ACCEL_KEY_HH
#include <xfc/gtk/accelkey.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @name Accelerator Methods
/// @{

bool accel_groups_activate(G::Object& object, const AccelKey& accel_key);
///< Finds the first accelerator in any AccelGroup attached to <EM>object</EM> that matches the
///< key value and modifiers, and activates that accelerator.
///< @param object The G::Object, usually a Gtk::Window, on which to activate the accelerator.
///< @param accel_key An AccelKey specifying the accelerator key value and modifiers.
///< @return <EM>true</EM> if an accelerator was activated and handled this keypress.

Gdk::ModifierTypeField accelerator_get_default_mod_mask();
///< Gets the value set by set_default_mod_mask().
///< @return The default accelerator modifier mask.

void accelerator_set_default_mod_mask(Gdk::ModifierTypeField default_mod_mask);
///< Sets the modifiers that will be considered significant for keyboard accelerators.
///< @param default_mod_mask Accelerator modifier mask.
///<
///< The default mod mask is GDK_CONTROL_MASK | GDK_SHIFT_MASK | GDK_MOD1_MASK, that is,
///< Control, Shift, and Alt. Other modifiers will by default be ignored by AccelGroup.
///< You must include at least the three default modifiers in any value you pass to this
///< method.
///<
///< The default mod mask should be changed on application startup, before using any
///< accelerator groups.

bool accelerator_valid(const AccelKey& accel_key);
///< Determines whether a given AccelKey is a valid keyboard accelerator.
///< @param accel_key An AccelKey specifying the accelerator key value and modifiers.
///< @return <EM>true</EM> if the accelerator is valid.
///<
///< For example, the GDK_a keyval plus Gdk::CONTROL_MASK is valid this is a
///< "Ctrl+a" accelerator. But, you can't, for instance, use the GDK_Control_L key value
///< as an accelerator.

AccelKey accelerator_parse(const char *accelerator, AccelFlagsField accel_flags = Gtk::ACCEL_VISIBLE);
AccelKey accelerator_parse(const String& accelerator, AccelFlagsField accel_flags = Gtk::ACCEL_VISIBLE);
///< Construct an AccelKey from a string representing an accelerator.
///< @param accelerator A string representing an accelerator.
///< @param accel_flags A flag mask to configure this accelerator.
///< @return accel_key An AccelKey specifying the accelerator key value and modifiers.
///<
///< Parses a string representing an accelerator. The format looks like "\<Control\>a" or
///< "\<Shift\>\<Alt\>F1" or "\<Release\>z" (the last one is for key release). The parser is fairly
///< liberal and allows lower or upper case, and also abbreviations such as "\<Ctl\>" and "\<Ctrl\>".
///< If the parse fails, accelerator and its modifiers will be set to 0 (zero).

String accelerator_name(const AccelKey& accel_key);
///< Converts an AccelKey's key value and modifier mask into a string parseable by parse().
///< @param accel_key An AccelKey specifying the accelerator key value and modifiers.
///< @return The accelerator name.
///<
///< For example, if you pass in GDK_q and Gdk::CONTROL_MASK, this function returns
///< "\<Control\>q".

String accelerator_get_label(unsigned int accelerator_key, Gdk::ModifierType accelerator_mods);
///< Converts an accelerator key value and modifier mask into a string
///< which can be used to represent the accelerator to the user.
///< @param accelerator_key The accelerator key value. 
///< @param accelerator_mods The accelerator modifier mask. 
///< @return A String representing the accelerator.

/// @}

/// @class AccelGroup accelgroup.hh xfc/gtk/accelgroup.hh
/// @brief GtkAccelGroup C++ wrapper class.
///
/// AccelGroup represents a group of keyboard accelerators, typically attached to a
/// toplevel Gtk::Window (with Gtk::Window::add_accel_group()). Usually you won't
/// need to create an AccelGroup directly; instead, when using Gtk::ItemFactory and
/// Gtk::Menu, GTK+ automatically sets up the accelerators for your menus in the
/// default accelerator group.
///
/// Note that accelerators are different from mnemonics. Accelerators are shortcuts for
/// activating a menu item; they appear alongside the menu item they're a shortcut for.
/// For example "Ctrl+Q" might appear alongside the "Quit" menu item. Mnemonics are
/// shortcuts for GUI elements such as text entries or buttons; they appear as underlined
/// characters. Menu items can have both accelerators and mnemonics, of course.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 

class AccelGroup : public G::Object
{
	friend class G::Object;

	AccelGroup(const AccelGroup&);
	AccelGroup& operator=(const AccelGroup&);

protected:
/// @name Constructors
/// @{

	explicit AccelGroup(GtkAccelGroup *group, bool owns_reference = true);
	///< Construct a new AccelGroup from an existing GtkAccelGroup.
	///< @param group A pointer to a GtkAccelGroup.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>group</EM> can be a newly created GtkAccelGroup or an existing
	///< GtkAccelGroup. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, const AccelKey&, GClosure*> AccelChangedSignalType;
	typedef G::SignalProxy<TypeInstance, AccelChangedSignalType> AccelChangedSignalProxy;
	static const AccelChangedSignalType accel_changed_signal;
	///< Accelerator changed signal (see signal_accel_changed()). Calls a slot with the signature:
	///< @code
	///< void function(const AccelKey& accel_key, GClosure *accel_closure);
	///< // accel_key: An AccelKey specifying the accelerator key value and modifiers.
	///< // accel_closure: Closure to be executed upon accelerator activation.
	///< @endcode

/// @}

public:
	typedef GtkAccelGroup CObjectType;

/// @name Constructors
/// @{

	AccelGroup();
	///< Constructs a new AccelGroup with a reference count of 1 that the caller owns.
	
	virtual ~AccelGroup();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkAccelGroup* gtk_accel_group() const;
	///< Get a pointer to the GtkAccelGroup structure.

	operator GtkAccelGroup* () const;
	///< Conversion operator; safely converts an AccelGroup to a GtkAccelGroup pointer.

/// @}
/// @name Accessors
/// @{
	
	static AccelGroup* from_accel_closure(GClosure *closure);
	///< Finds the AccelGroup to which <EM>closure</EM> is connected; (see connect()).
	///< @param closure A closure.
	///< @return The AccelGroup to which closure is connected, or null.
	
/// @}
/// @name Methods
/// @{

	void lock();
	///< Locks the given accelerator group.
	///< Locking an accelerator group prevents the accelerators contained within it being changed
	///< during runtime. Refer to Gtk::AccelMap::change_entry() about runtime accelerator changes.
	///< If called more than once, the accelerator group remains locked until unlock() has been
	///< called an equivalent number of times.

	void unlock();
	///< Undoes the last call to lock() on the accelerator group.

	void connect(const AccelKey& accel_key, GClosure *closure);
	///< Installs an accelerator in the group.
	///< @param accel_key An AccelKey specifying the accelerator key value, modifiers and flags.
	///< @param closure Closure to be executed upon accelerator activation.
	///<
	///< When the accelerator group is being activated in response to a call to activate(),
	///< <EM>closure</EM> will be invoked if the accelerator key value and modifiers from activate()
	///< match those of this connection.
	///<
	///< Note that, due to implementation details, a single closure can only be connected to one
	///< accelerator group.

	void connect(const char *accel_path, GClosure *closure);
	void connect(const String& accel_path, GClosure *closure);
	///< Installs an accelerator in this group, using an accelerator path to look up the
	///< appropriate key and modifiers (see Gtk::AccelMap::add_entry()).
	///< @param accel_path The path used for determining the accelerator key value and modifiers.
	///< @param closure Closure to be executed upon accelerator activation.
	///<
	///< When the accelerator group is being activated in response to a call to activate(),
	///< <EM>closure</EM> will be invoked if the accelerator key value and modifiers from activate()
	///< match the key and modifiers for the path.

	bool disconnect(GClosure *closure);
	///< Removes an accelerator previously installed through connect().
	///< @param closure The closure to remove from this accelerator group.
	///< @return <EM>true</EM> if the closure was found and got disconnected.

	bool disconnect(const AccelKey& accel_key);
	///< Removes an accelerator previously installed through connect().
	///< @param accel_key An AccelKey specifying the accelerator key value and modifiers.
	///< @return <EM>true</EM> if there was an accelerator which could be removed, <EM>fakse</EM> otherwise.

/// @}
/// @name Signal Proxies
/// @{

	const AccelChangedSignalProxy signal_accel_changed();
	///< Connect to the accel_changed_signal; emitted when an accelerator is changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/accelgroup.inl>

#endif // XFC_GTK_ACCEL_GROUP_HH

