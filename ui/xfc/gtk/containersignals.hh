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

/// @file xfc/gtk/containersignals.hh
/// @brief Gtk::Container virtual signal handlers.
///
/// Provides Gtk::ContainerSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Container objects.

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#define XFC_GTK_CONTAINER_SIGNALS_HH

#ifndef XFC_GTK_WIDGET_SIGNALS_HH
#include <xfc/gtk/widgetsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ContainerSignals containersignals.hh xfc/gtk/containersignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Container.

class ContainerSignals : public WidgetSignals
{
protected:
/// @name Constructors
/// @{

	ContainerSignals(Container *container);
	///< Construct a new ContainerSignals object.
	///< @param container A Container object inheriting the ContainerSignals implementation.

	virtual ~ContainerSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_add(Widget& widget);
	///< Called when a new child widget is added to the container.
	///< @param widget The widget added to the container

	virtual void on_remove(Widget& widget);
	///< Called when a child widget is removed from the container.
	///< @param widget The widget removed from the container

	virtual void on_check_resize();
	///< Called when a container needs to check whether it should resize or
	///< when one of its children queues a resize request.
	///< Only useful when writing a special custom widget.

	virtual void on_set_focus_child(Widget *widget);
	///< Called when the container sets the focus on a child.
	///< @param widget The widget that receives the focus.
	///< Only useful when writing a special custom widget.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_CONTAINER_SIGNALS_HH

