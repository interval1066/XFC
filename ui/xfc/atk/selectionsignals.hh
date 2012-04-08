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

/// @file xfc/atk/selectionsignals.hh
/// @brief Atk::Selection virtual signal handlers.
///
/// Provides Atk::SelectionSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Atk::Selection objects.

#ifndef XFC_ATK_SELECTION_SIGNALS_HH
#define XFC_ATK_SELECTION_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace Atk {

/// @class SelectionSignals selectionsignals.hh xfc/atk/selectionsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Atk::Selection.

class SelectionSignals : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	virtual ~SelectionSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_selection_changed();
	///< Called when an object's selection changes.

/// @}
};

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_SELECTION_SIGNALS_HH

