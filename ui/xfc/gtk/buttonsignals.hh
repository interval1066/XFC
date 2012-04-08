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
 
/// @file xfc/gtk/buttonsignals.hh
/// @brief Gtk::Button virtual signal handlers.
///
/// Provides Gtk::ButtonSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Button objects.

#ifndef XFC_GTK_BUTTON_SIGNALS_HH
#define XFC_GTK_BUTTON_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ButtonSignals buttonsignals.hh xfc/gtk/buttonsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Button.

class ButtonSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	ButtonSignals(Button *button);
	///< Constructs a new ButtonSignals object.
	///< @param button A Button object inheriting the ButtonSignals implementation.

	virtual ~ButtonSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_pressed();
	///< Called when the button is initially pressed.

	virtual void on_released();
	///< Called when a button which is pressed is released, no matter where the mouse cursor is.

	virtual void on_clicked();
	///< Called when a button clicked on by the mouse and the cursor stays on the button. If the
	///< cursor is not on the button when the mouse button is released, the signal is not emitted.

	virtual void on_enter();
	///< Called when the mouse cursor enters the region of the button.

	virtual void on_leave();
	///< Called when the mouse cursor leaves the region of the button.

	virtual void on_activate();
	///< Called when the button is activated.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_BUTTON_SIGNALS_HH

