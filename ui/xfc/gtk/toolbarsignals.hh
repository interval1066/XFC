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

/// @file xfc/gtk/toolbarsignals.hh
/// @brief Gtk::Toolbar virtual signal handlers.
///
/// Provides Gtk::ToolbarSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Toolbar objects.

#ifndef XFC_GTK_TOOLBAR_SIGNALS_HH
#define XFC_GTK_TOOLBAR_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToolbarSignals toolbarsignals.hh xfc/gtk/toolbarsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Toolbar.

class ToolbarSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	ToolbarSignals(Toolbar *toolbar);
	///< Constructs a new ToolbarSignals object.
	
	virtual ~ToolbarSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_orientation_changed(Orientation orientation);
	///< Called when the orientation of a toolbar is changed.
	///< @param orientation  The new Orientation of the toolbar.

	virtual void on_style_changed(ToolbarStyle style);
	///< Called when ever the style of a toolbar is adjusted.
	///< @param style The new ToolbarStyle of toolbar.
	///<
	///< For example, this would be a useful signal to connect to if you want to
	///< display more items on the toolbar when it is in icon-only mode; each item
	///< takes less space on the bar.

	virtual bool on_popup_context_menu(int x, int y, int button_number);
 	///< Called when the user right-clicks the toolbar or uses the keybinding
	///< to display a popup menu.
	///< @param x The x coordinate of the point where the menu should appear.
	///< @param y The y coordinate of the point where the menu should appear.
	///, @param button_number The mouse button the user pressed, or -1.
	///< @return <EM>true</EM> if the signal was handled, <EM>false</EM> if not.
	///<
	///< Application developers should handle this signal if they want to
	///< display a context menu on the toolbar. The context-menu should appear
	///< at the coordinates given by <EM>x</EM> and <EM>y</EM>. The mouse button
	///< number is given by the <EM>button</EM> parameter. If the menu was popped
	///< up using the keybaord, <EM>button</EM> is -1.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TOOLBAR_SIGNALS_HH

