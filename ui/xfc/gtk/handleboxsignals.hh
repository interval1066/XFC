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
 
/// @file xfc/gtk/handleboxsignals.hh
/// @brief Gtk::HandleBox virtual signal handlers.
///
/// Provides Gtk::HandleBoxSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::HandleBox objects.

#ifndef XFC_GTK_HANDLE_BOX_SIGNALS_HH
#define XFC_GTK_HANDLE_BOX_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class HandleBoxSignals handleboxsignals.hh xfc/gtk/handleboxsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::HandleBox.

class HandleBoxSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	HandleBoxSignals(HandleBox *handle_box);
	///< Construct a new HandleBoxSignals object.
	///< @param handle_box A HandleBox object inheriting the HandleBoxSignals implementation.
	
	virtual ~HandleBoxSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_child_attached(Widget& child);
	///< Called when the contents of the handlebox are reattached to the main window.
	///< @param child The child widget of the handlebox.
	///<
	///< The <EM>child</EM> argument provides no extra information and is here only
	///< for backwards compatibility.

	virtual void on_child_detached(Widget& child);
	///< Called when the contents of the handlebox are detached from the main window.
	///< @param child The child widget of the handlebox.
	///<
	///< The <EM>child</EM> argument provides no extra information and is here only
	///< for backwards compatibility.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_HANDLE_BOX_SIGNALS_HH

