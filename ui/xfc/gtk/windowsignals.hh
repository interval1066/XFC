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

/// @file xfc/gtk/windowsignals.hh
/// @brief Gtk::Window virtual signal handlers.
///
/// Provides Gtk::WindowSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Window objects.

#ifndef XFC_GTK_WINDOW_SIGNALS_HH
#define XFC_GTK_WINDOW_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class WindowSignals windowsignals.hh xfc/gtk/windowsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Window.

class WindowSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	WindowSignals(Window *window);
	///< Constructs a new WindowSignals object.
	///< @param window A Window object inheriting the WindowSignals implementation.

	virtual ~WindowSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_set_focus(Widget *focus);
	///< Called when the focus widget for the window changes.
	///< @param focus The focus widget, or null if the focus is unset.

	virtual bool on_frame_event(const Gdk::Event& event);
	///< Called whenever the window receives an event targeted at the frame.
	///< @param event The Gdk::Event.
	///< @return <EM>false</EM> to allow the default frame event handler to be called.
	///<
	///< Returning true will prevent further propagation of this event and the
	///< default frame event handler will not be called. This handler is typically
	///< called when a user tries to resize the window frame. Returning true will
	///< prevent the frame being resized and returning false will allow the resizing
	///< to proceed.

	virtual void on_keys_changed();
	///< Called when the windows menmonic and/or accelerator keys have changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_WINDOW_SIGNALS_HH

