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

/// @file xfc/gtk/accelmap.hh
/// @brief A GtkAccelMap C++ wrapper interface.

#ifndef XFC_GTK_ACCEL_MAP_HH
#define XFC_GTK_ACCEL_MAP_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GTK_ACCEL_KEY_HH
#include <xfc/gtk/accelkey.hh>
#endif

#ifndef __GTK_ACCEL_MAP_H__
#include <gtk/gtkaccelmap.h>
#endif

namespace Xfc {

namespace G {
class Scanner;
}

namespace Gtk {

/// @class AccelMap accelmap.hh xfc/gtk/accelmap.hh
/// @brief A GtkAccelMap C++ wrapper class.

class AccelMap : public G::Object
{
	friend class G::Object;

	AccelMap(const AccelMap&);
	AccelMap& operator=(const AccelMap&);

protected:
/// @name Constructors
/// @{

	explicit AccelMap(GtkAccelMap *map, bool owns_reference = true);
	///< Construct a new AccelMap from an existing GtkAccelMap.
	///< @param map A pointer to a GtkAccelMap.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>map</EM> can be a newly created GtkAccelMap or an existing
	///< GtkAccelMap. (see G::Object::Object).

/// @}
/// @name Signals
/// @{

	typedef G::Signal<void, const String&, const AccelKey&> ChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ChangedSignalType> ChangedSignalProxy;
	static const ChangedSignalType changed_signal;
	///< Changed signal (see signal_changed()). Calls a slot with the signature:
	///< @code
	///< void function(const String& accel_path, const AccelKey& accel_key);
	///<
	///< // accel_path: The path of the accelerator that changed.
	///< // accel_key: An AccelKey specifying the accelerator key value and modifiers.
	///< @endcode

/// @}

public:
	typedef GtkAccelMap CObjectType;
	
	typedef sigc::slot<void, const String&, const AccelKey&, bool> ForeachSlot;
	///< Signature for the callback slot to be called on each entry in the accelerator map.
	///< <B>Example:</B> Method signature for ForeachSlot.
	///< @code
	///< void method(const char *accel_path, const AccelKey& accel_key, bool changed);
	///<
	///< // accel_path: The accelerator path for the entry.
	///< // accel_key: An AccelKey object that holds the entry's accelerator key and modifiers.
	///< // changed: Whether the accelerator was changed during runtime and would need saving.
	///< @endcode

/// @name Constructors
/// @{

	virtual ~AccelMap();
	///< Destructor,

/// @}
/// @name Accessors
/// @{

	GtkAccelMap* gtk_accel_map() const;
	///< Get a pointer to the global GtkAccelMap structure.

	operator GtkAccelMap* () const;
	///< Conversion operator; safely converts an AccelMap to a GtkAccelMap pointer.

/// @}
/// @name Accessors
/// @{

	static AccelMap* get();
	///< Gets the singleton global AccelMap object. 
	///< @return The global Gtk::AccelMap object.
	///<
	///< The AccelMap object is useful only for notification of changes to the
	///< accelerator map via the 'changed_signal'.

/// @}
/// @name Methods
/// @{
	
	static bool lookup_entry(const char *accel_path, AccelKey *accel_key = 0);
	static bool lookup_entry(const String& accel_path, AccelKey *accel_key = 0);
	///< Looks up the accelerator entry for accel_path and fills in accel_key.
	///< @param accel_path A valid accelerator path.
	///< @param accel_key The accelerator key to be filled in (optional).
	///< @return <EM>true</EM> if accel_path is known, <EM>false</EM> otherwise.

	static void add_entry(const char *accel_path, const AccelKey& accel_key);
	static void add_entry(const String& accel_path, const AccelKey& accel_key);
	///< Registers a new accelerator with the global accelerator map.
	///< @param accel_path A valid accelerator path.
	///< @param accel_key An AccelKey specifying the accelerator key value and modifiers.
	///<
	///< This function should only be called once per accel_path with the canonical
	///< accelerator key value and modifiers for this path. To change the accelerator
	///< during runtime programatically, use change_entry(). The accelerator path must
	///< consist of "\<WINDOWTYPE\>/Category1/Category2/.../Action", where \<WINDOWTYPE\>
	///< should be a unique application-specific identifier, that corresponds to the
	///< kind of window the accelerator is being used in, e.g. "Gimp-Image",
	///< "Abiword-Document" or "Gnumeric-Settings". The Category1/.../Action portion
	///< is most appropriately chosen by the action the accelerator triggers, i.e. for
	///< accelerators on menu items, choose the item's menu path, e.g. "File/Save As",
	///< "Image/View/Zoom" or "Edit/Select All". So a full valid accelerator path may 
	///< look like: "\<Gimp-Toolbox\>/File/Dialogs/Tool Options...".

	static bool change_entry(const char *accel_path, const AccelKey& accel_key, bool replace);
	static bool change_entry(const String& accel_path, const AccelKey& accel_key, bool replace);
	///< Changes the key value and modifiers currently associated with accel_path.
	///< @param accel_path A valid accelerator path.
	///< @param accel_key An AccelKey specifying the accelerator key value and modifiers.
	///< @param replace Set <EM>true</EM> if other accelerators may be deleted upon conflicts.
	///< @return <EM>true</EM> if the accelerator could be changed, <EM>false</EM> otherwise.
	///<
	///< Due to conflicts with other accelerators, a change may not always be possible,
	///< replace indicates whether other accelerators may be deleted to resolve such conflicts.
	///< A change will only occur if all conflicts could be resolved (which might not be the 
	///< case if conflicting accelerators are locked). Successful changes are indicated by a
	///< <EM>true</EM> return value.

	static void load(const char *filename);
	static void load(const String& filename);
	///< Parses a file previously saved with save() for accelerator specifications,
	///< and propagates them accordingly.
	///< @param filename A file containing accelerator specifications.

	static void load(int file_descriptor);
	///< Filedescriptor variant of load().
	///< @param file_descriptor A valid readable file descriptor.
	///<
	///< Note that the file descriptor will not be closed by this function.

	static void load(G::Scanner& scanner);
	///< G::Scanner variant of load().
	///< @param scanner A G::Scanner which has already been provided with an input file.
	
	static void save(const char *filename);
	static void save(const String& filename);
	///< Saves current accelerator specifications (accelerator path, key and modifiers) to file_name.
	///< @param filename A file to contain accelerator specifications.
	///<
	///< The file is written in a format suitable to be read back in by load().

	static void save(int file_descriptor);
	///< Filedescriptor variant of save().
	///< @param file_descriptor A valid writable file descriptor.
	
	static void foreach(const ForeachSlot& slot);
	///< Loops over the entries in the accelerator map whose accel_path doesn't match any
	///< of the filters added with add_filter(), and calls <EM>slot</EM> on each.
	///< @param slot Ahe ForeachSlot to be called for each map entry not filtered out.
	///<
	///< The signature for the ForeachSlot is typedef'd above, the changed parameter indicates
	///< whether this accelerator was changed during runtime (thus, would need saving during
	///< an accelerator map dump).

	static void lock_path(const char *accel_path);
	static void lock_path(const String& accel_path);
	///< Locks the given accelerator path.
	///< @param accel_path A valid accelerator path.
	///<
	///< If the accelerator map doesn't yet contain an entry for <EM>accel_path</EM>,
	///< a new one is created. Locking an accelerator path prevents its accelerator from
	///< being changed during runtime. A locked accelerator path can be unlocked by
	///< unlock_path(). Refer to change_entry() for information about runtime accelerator
	///< changes.
	///<
	///< If called more than once, <EM>accel_path</EM> remains locked until unlock_path()
	///< has been called an equivalent number of times. Note that locking of individual
	///< accelerator paths is independent from locking the Gtk::AccelGroup containing them.
	///< For runtime accelerator changes to be possible both the accelerator path and its
	///< Gtk::AccelGroup have to be unlocked.

	static void unlock_path(const char *accel_path);
	static void unlock_path(const String& accel_path);
	///< Undoes the last call to lock_path() on this <EM>accel_path</EM> (see lock_path()).
	///< @param accel_path A valid accelerator path.
	
/// @}
/// @name Signal Proxies
/// @{

	const ChangedSignalProxy signal_changed(const char *accel_path = 0);
	const ChangedSignalProxy signal_changed(const String& accel_path);
	///< Connect to the changed_signal; emitted when an entry in the global accelerator map is changed.
	///< @param accel_path The accelerator path to be notified of changes to.
	///<
	///< If <EM>accel_path</EM> is provided it is appended to the signal name so that
	///< the signal connected to becomes "changed::accel_path". What this does is ensure 
	///< that your changed slot is only called if <EM>accel_path</EM> matches the 
	///< accelerator path of the "changed" signal being emitted. 

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/accelmap.inl>

#endif // XFC_GTK_ACCEL_MAP_HH

