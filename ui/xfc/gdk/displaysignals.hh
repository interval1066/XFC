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

/// @file xfc/gdk/displaysignals.hh
/// @brief Gdk::Display virtual signal handlers.
///
/// Provides Gdk::DisplaySignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gdk::Display objects.

#ifndef XFC_GDK_DISPLAY_SIGNALS_HH
#define XFC_GDK_DISPLAY_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gdk {

/// @class DisplaySignals displaysignals.hh xfc/gdk/displaysignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gdk::Display.

class DisplaySignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	DisplaySignals(Display *display);
	///< Constructs a new DisplaySignals object.
	///< @param display A Display object inheriting the DisplaySignals implementation.

	virtual ~DisplaySignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_closed(bool is_error);
	///< Called when the display is closed.
	///< @param is_error Is <EM>true</EM> if the display was closed due to an error.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#endif // XFC_GDK_DISPLAY_SIGNALS_HH

