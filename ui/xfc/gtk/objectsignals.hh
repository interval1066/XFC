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

/// @file xfc/gtk/objectsignals.hh
/// @brief Gtk::Object virtual signal handlers.
///
/// Provides Gtk::ObjectSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Object objects.

#ifndef XFC_GTK_OBJECT_SIGNALS_HH
#define XFC_GTK_OBJECT_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ObjectSignals objectsignals.hh xfc/gtk/objectsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Object.

class ObjectSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	ObjectSignals(Object *object);
	///< Constructs a new ObjectSignals object.
	///< @param object A Gtk::Object object inheriting the Gtk::ObjectSignals implementation.
	
	virtual ~ObjectSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_destroy();
	///< Called when the holder of a reference should release the reference that they hold.
	///< This may result in finalization of the object if all references are released.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_OBJECT_SIGNALS_HH

