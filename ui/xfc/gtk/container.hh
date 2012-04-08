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

/// @file xfc/gtk/container.hh
/// @brief A GtkContainer C++ wrapper interface.
///
/// Provides Container, an abstract base class for widgets (parents) that contain other
/// widgets (children).

#ifndef XFC_GTK_CONTAINER_HH
#define XFC_GTK_CONTAINER_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef __GTK_CONTAINER_H__
#include <gtk/gtkcontainer.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Container container.hh xfc/gtk/container.hh
/// @brief A GtkContainer C++ wrapper class.
///
/// Container is a base class for widgets (parents) that contain other widgets (children).
/// Container is responsible for managing the parent-child relationship. There are several
/// types of containers, some having only one child and others having several. Some
/// containers with only one child derive from Bin (Window, Button, Frame, HandleBox),
/// while others with several children derive from Box (HBox, VBox), MenuShell (Menu,
/// MenuBar) and Paned (HPaned, VPaned). Other containers with several children include
/// Fixed, Layout, Notebook, Table and Toolbar.

class Container : public Widget
{
	friend class G::Object;

	Container(const Container&);
	Container& operator=(const Container&);

protected:
/// @name Constructors
/// @{

	explicit Container(GtkContainer *container, bool owns_reference = false);
	///< Construct a new Container from an existing GtkContainer.
	///< @param container A pointer to a GtkContainer.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>container</EM> can be a newly created GtkContainer or an existing
	///< GtkContainer. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Widget&> AddSignalType;
	typedef G::SignalProxy<TypeInstance, AddSignalType> AddSignalProxy;
	static const AddSignalType add_signal;
	///< Add signal (see signal_add()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Widget& widget);
	///< // widget: The widget added to the container
	///< @endcode

	typedef G::Signal<void, Widget&> RemoveSignalType;
	typedef G::SignalProxy<TypeInstance, RemoveSignalType> RemoveSignalProxy;
	static const RemoveSignalType remove_signal;
	///< Remove signal (see signal_remove()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Widget& widget);
	///< // widget: The widget removed from the container
	///< @endcode

	typedef G::Signal<void> CheckResizeSignalType;
	typedef G::SignalProxy<TypeInstance, CheckResizeSignalType> CheckResizeSignalProxy;
	static const CheckResizeSignalType check_resize_signal;
	///< Check resize signal (see signal_check_resize()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, Widget*> SetFocusChildSignalType;
	typedef G::SignalProxy<TypeInstance, SetFocusChildSignalType> SetFocusChildSignalProxy;
	static const SetFocusChildSignalType set_focus_child_signal;
	///< Set focus child signal (see signal_set_focus_child()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Widget *widget);
	///< // widget: The widget that receives the focus.
	///< @endcode

/// @}

public:
	typedef GtkContainer CObjectType;
	
	typedef sigc::slot<void, Widget&> ForeachSlot;
	///< Signature of the callback slot to be called for each widget in the container.
	///<
	///< <B>Example:</B> Method signature for ForeachSlot.
	///< @code
	///< void method(Widget& widget);
	///< // widget: The child widget.
	///< @endcode

/// @name Constructors
/// @{
	
	virtual ~Container();
	///< Destructor.

/// @}
/// @name Accessors
/// @{
	
	GtkContainer* gtk_container() const;
	///< Get a pointer to the GtkContainer structure.

	operator GtkContainer* () const;
	///< Conversion operator; safely converts a Container to a GtkContainer pointer.

	bool is_resize_container() const;
	///< Returns true if the resize request is handled by the container, and false if it's
	///< passed to the container's parent (RESIZE_PARENT).

	GType child_type() const;
	///< Returns the type of the children supported by the container.
	///< @return A GType.
	///<
	///< Note that this may return G_TYPE_NONE to indicate that no more children can be
	///< added, e.g. for a Gtk::Paned which already has two children.

	Widget* focus_child() const;
	///< Returns the widget that currently has the focus set on it.
	
	bool get_children(std::vector<Widget*>& child_list) const;
	///< Gets a list ot the container's non-internal children.
	///< @param child_list A vector of Widget* to hold the list of the container's non-internal children.
	///<
	///< See foreach() for details on what constitutes an "internal" child.

	unsigned int get_border_width() const;
	///< Retrieves the current border width of the container; see set_border_width().
	
	ResizeMode get_resize_mode() const;
	///< Returns the resize mode for the container; see set_resize_mode().

	bool get_focus_chain(std::vector<Widget*>& focusable_widgets) const;
	///< Retrieves the focus chain of the container, if one has been set explicitly.
	///< @param focusable_widgets A vector of Widget* to store the focus chain of the container.
	///< @return <EM>true</EM> if the focus chain of the container has been set explicitly.
	///<
	///< If no focus chain has been explicitly set, GTK+ computes the focus chain based on
	///< the positions of the children. In that case, GTK+ stores null in focusable_widgets and
	///< returns false. <EM>No additional reference count is added to the individual widgets in
	///< the focus chain</EM>.

	Adjustment* get_focus_vadjustment() const;
	///< Retrieves the vertical focus adjustment for the container; see set_focus_vadjustment().
	///< @return The vertical focus adjustment, or null if none has been set.

	Adjustment* get_focus_hadjustment() const;
	///< Retrieves the horizontal focus adjustment for the container; see set_focus_hadjustment().
	///< @return The horizontal focus adjustment, or null if none has been set.

/// @}
/// @name Methods
/// @{

	void add(Widget& widget);
	///< Adds widget to the container. 
	///< @param widget A widget to be placed inside the container.
	///<
	///< Typically used for simple containers such as Window, Frame, or Button;
	///< for more complicated layout containers such as Box or Table, this method 
	///< will pick default packing parameters that may not be correct. So consider
	///< methods such as Gtk::Box::pack_start() and Gtk::Table::attach() as an 
	///< alternative to add() in those cases. A widget may be added to only one
	///< container at a time; you can't place the same widget inside two different
	///< containers.

	void remove(Widget& widget);
	///< Removes widget from the container. 
	///< @param widget A current child of the container.
	///<
	///< The widget must be inside container. Note that the container will own a reference
	///< to widget, and that this may be the last reference held; so removing a widget from its
	///< container can destroy that widget. If you want to use widget again, you need to add a
	///< reference to it while it's not inside a container, using G::Object::ref().

	void check_resize();
	///< Check whether the container should resize, and if so queue a resize request.
	///< Only useful when writing a special custom widget.

	void set_focus_child(Widget& widget);
	///< Sets the focus on a widget.
	///< @param widget The widget that is to receive the focus.
	///< Only useful when writing a special custom widget.

	void set_border_width(unsigned int border_width);
	///< Sets the border width of the container.
	///< @param border_width Amount of blank space to leave outside the container. Valid values
	///<                     are in the range 0-65535 pixels.
	///<
	///< The border width of a container is the amount of space to leave around the outside
	///< of the container. The only exception to this is Gtk::Window; because toplevel windows
	///< can't leave space outside, they leave the space inside. The border is added on all 
	///< sides of the container. To add space to only one side, one approach is to create an
	///< Alignment widget, call Gtk::Widget::set_size_request() to give it a size, and place
	///< it on the side of the container as a spacer.

	void set_resize_mode(ResizeMode resize_mode);
	///< Sets the resize mode for the container.
	///< @param resize_mode The new resize mode.
	///<
	///< The resize mode of a container determines whether a resize request will be passed
	///< to the container's parent, queued for later execution or executed immediately.

	void foreach(const ForeachSlot& each);
	///< Invokes the <EM>each</EM> slot on each non-internal child of the container.
	///< @param each A ForeachSlot to call on each non-internal child of the container.
	///<
	///< "Internal" children generally weren't added by the user of the container, but were
	///< added by the container implementation itself.

	void set_reallocate_redraws(bool needs_redraws);
	///< Containers requesting reallocation redraws get automatically redrawn if any of their
	///< children change their allocation.
	///< @param needs_redraws The new value for the container's reallocate_redraws flag.

	void set_focus_vadjustment(Adjustment *adjustment);
	///< Sets the vertical focus adjustment for the container.
	///< @param adjustment The new vertical focus adjustment, or null.
	///<
	///< Updates the Adjustment to reflect the vertical position of the focused child,
	///< according to the height of the container.

	void set_focus_hadjustment(Adjustment *adjustment);
	///< Sets the horizontal focus adjustment for the container.
	///< @param adjustment The new horizontal focus adjustment, or null.
	///<
	///< Updates the Adjustment to reflect the horizontal position of the focused child,
	///< according to the width of the container.

	void resize_children();
	///< Update the size and position of the child widgets.
	///< Only useful when writing a special custom widget. Called after a size request to the
	///< get the container to reallocate its size and position to reflect a change in the size
	///< and position of its children.

	void propagate_expose(Widget& child, const Gdk::EventExpose& event);
	///< When a container receives an expose event, it must send synthetic expose events to all
	///< children that don't have their own Gdk::Windows.
	///< @param child A child of the container.
	///< @param event An expose event sent to the container.
	///<
	///< This method provides a convenient way of sending an expose event. A container,
	///< when it receives an expose event, calls propagate_expose() once for each child,
	///< passing in the event the container received. This method takes care of deciding
	///< whether an expose event needs to be sent to the child, intersecting the event's
	///< area with the child area, and sending the event. In most cases, a container can
	///< simply override the inherited on_expose_event() implementation from Container.

	void set_focus_chain(const std::vector<Widget*>& focusable_widgets);
	///< Sets a focus chain, overriding the one computed automatically by GTK+.
	///< @param focusable_widgets A vector of Widgets to set as the new focus chain.
	///<
	///< In principle each widget in the chain should be a descendant of the container,
	///< but this is not enforced by this method, since it's allowed to set the focus chain
	///< before you pack the widgets, or have a widget in the chain that isn't always packed.
	///< The necessary checks are done when the focus chain is actually traversed.

	void unset_focus_chain();
	///< Removes a focus chain explicitly set with set_focus_chain().

/// @}
/// @name Signal Proxies
/// @{

	const AddSignalProxy signal_add();
	///< Connect to the add_signal; emitted when a child widget is added to the container.

	const RemoveSignalProxy signal_remove();
	///< Connect to the remove_signal; emitted when a child widget is removed from the container.

	const CheckResizeSignalProxy signal_check_resize();
	///< Connect to the check_resize_signal; emitted when a container needs to check
	///< whether it should resize or when one of its children queues a resize request.

	const SetFocusChildSignalProxy signal_set_focus_child();
	///< Connect to the set_focus_child_signal; emitted when the container sets the focus on a child.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/container.inl>

#endif // XFC_GTK_CONTAINER_HH

