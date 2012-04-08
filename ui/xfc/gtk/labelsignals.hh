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
 
/// @file xfc/gtk/labelsignals.hh
/// @brief Gtk::Label virtual signal handlers.
///
/// Provides Gtk::LabelSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Label objects.

#ifndef XFC_GTK_LABEL_SIGNALS_HH
#define XFC_GTK_LABEL_SIGNALS_HH

#ifndef XFC_GTK_WIDGET_SIGNALS_HH
#include <xfc/gtk/widgetsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class LabelSignals labelsignals.hh xfc/gtk/labelsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Label.

class LabelSignals : public WidgetSignals
{
protected:
/// @name Constructors
/// @{

	LabelSignals(Label *label);
	///< Construct an empty LabelSignals object.

	virtual ~LabelSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_populate_popup(Menu& menu);
	///< Called just before the popup menu is displayed in response the a right-click on a selectable label.
	///< @param menu The popup menu.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_LABEL_SIGNALS_HH

