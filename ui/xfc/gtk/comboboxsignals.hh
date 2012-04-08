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

/// @file xfc/gtk/comboboxsignals.hh
/// @brief Gtk::ComboBox virtual signal handlers.
///
/// Provides Gtk::ComboBoxSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::ComboBox objects.

#ifndef XFC_GTK_COMBO_BOX_SIGNALS_HH
#define XFC_GTK_COMBO_BOX_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ComboBoxSignals comboboxsignals.hh xfc/gtk/comboboxsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::ComboBox.

class ComboBoxSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	ComboBoxSignals(ComboBox *combo_box);
	///< Construct a new ComboBoxSignals object.
	///< @param combo_box A ComboBox object inheriting the ComboBoxSignals implementation.

	virtual ~ComboBoxSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_changed();
	///< Called when the active item in the combo box is changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_COMBO_BOX_SIGNALS_HH

