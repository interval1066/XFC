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

/// @file xfc/gtk/accelgroupsignals.hh
/// @brief GtkAccelGroup virtual signal handlers.
///
/// Provides Gtk::AccelGroupSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::AccelGroup objects.

#ifndef XFC_GTK_ACCEL_GROUP_SIGNALS_HH
#define XFC_GTK_ACCEL_GROUP_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class AccelGroupSignals accelgroupsignals.hh xfc/gtk/accelgroupsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::AccelGroup.

class AccelGroupSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	AccelGroupSignals(AccelGroup *group);
	///< Constructs a new AccelGroupSignals.
	///< @param group An AccelGroup object inheriting the AccelGroupSignals implementation.

	virtual ~AccelGroupSignals() = 0;
	///< Destructor,

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_accel_changed(const AccelKey& accel_key, GClosure *accel_closure);
	///< Called when an accelerator key is changed.
	///< @param accel_key An AccelKey specifying the accelerator key value and modifiers.
	///< @param accel_closure Closure to be executed upon accelerator activation.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_ACCEL_GROUP_SIGNALS_HH

