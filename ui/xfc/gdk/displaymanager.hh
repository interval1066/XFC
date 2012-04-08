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

/// @file xfc/gdk/displaymanager.hh
/// @brief A GdkDisplayManager C++ wrapper interface.
///
/// Provides DisplayManager, an object that Maintains a list of all open Gdk::Displays.

#ifndef XFC_GDK_DISPLAY_MANAGER_HH
#define XFC_GDK_DISPLAY_MANAGER_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GDK_DISPLAY_HH
#include <xfc/gdk/display.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {

/// @class DisplayManager displaymanager.hh xfc/gdk/displaymanager.hh
/// @brief A GdkDisplayManager C++ wrapper class.
///
/// The purpose of the DisplayManager singleton object is to offer notification
/// when displays appear or disappear or the default display changes.

class DisplayManager : public G::Object
{
	friend class G::Object;

	DisplayManager(const DisplayManager&);
	DisplayManager& operator=(const DisplayManager&);

protected:
/// @name Constructors
/// @{

	explicit DisplayManager(GdkDisplayManager *display_manager, bool owns_reference = true);
	///< Construct a new DisplayManager from an existing GdkDisplayManager.
	///< @param display_manager A pointer to a GdkDisplayManager.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>display_manager</EM> can be a newly created GdkDisplayManager or an existing
	///< GdkDisplayManager. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Display&> DisplayOpenedSignalType;
	typedef G::SignalProxy<TypeInstance, DisplayOpenedSignalType> DisplayOpenedSignalProxy;
	static const DisplayOpenedSignalType display_opened_signal;
	///< Display opened signal (see signal_display_opened()). Calls a slot with the signature:
	///< @code
	///< void function(Display& display);
	///< // display: The Display being opened.
	///< @endcode
	
/// @}

public:
	typedef GdkDisplayManager CObjectType;

/// @name Constructors
/// @{

	virtual ~DisplayManager();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GdkDisplayManager* gdk_display_manager() const;
	///< Get a pointer to the GdkDisplayManager structure.

	operator GdkDisplayManager* () const;
	///< Conversion operator; safely converts a DisplayManager to a GdkDisplayManager pointer.

	Display* get_default_display() const;
	///< Gets the default Display.
	///< @return A Display, or null if there is no default display.

	bool list_displays(std::vector<Display*>& displays) const;
	///< List all currently open displays.
	///< @param displays A reference to a vector of Display* to hold the list of opened displays.
	///< @return <EM>true</EM> if the vector is not empty.

/// @}
/// @name Accessors
/// @{

	static DisplayManager* get();
	///< Returns the global DisplayManager singleton object.

/// @}
/// @name Methods
/// @{

	void set_default_display(const Display& display);
	///< Sets display as the default display.
	///< @param display A Display.

/// @}
/// @name Signal Proxies
/// @{

	const DisplayOpenedSignalProxy signal_display_opened();
	///< Connect to the display_opened_signal; emitted when a Display is opened.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/displaymanager.inl>

#endif // XFC_GDK_DISPLAY_MANAGER_HH

