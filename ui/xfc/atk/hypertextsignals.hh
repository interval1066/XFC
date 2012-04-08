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

/// @file xfc/atk/hypertextsignals.hh
/// @brief Atk::Hypertext virtual signal handlers.
///
/// Provides Atk::HypertextSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Atk::Hypertext objects.

#ifndef XFC_ATK_HYPERTEXT_SIGNALS_HH
#define XFC_ATK_HYPERTEXT_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace Atk {

/// @class HypertextSignals hypertextsignals.hh xfc/atk/hypertextsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Atk::Hypertext.

class HypertextSignals : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	virtual ~HypertextSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_link_selected(int link_index);
	///< Called when one of the hyperlinks associated with the HyperText object is selected.
	///< @param link_index The index of the hyperlink which is selected.

/// @}
};

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_HYPERTEXT_SIGNALS_HH

