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
 
/// @file xfc/gtk/layout.hh
/// @brief A GtkLayout C++ wrapper interface.
///
/// Provides Layout, a widget similar to DrawingArea in that it's a "blank slate" and
/// doesn't do anything but paint a blank background by default. It's different in that
/// it supports scrolling natively (you can add it to a ScrolledWindow), and it can 
/// contain child widgets, since it's a Container.

#ifndef XFC_GTK_LAYOUT_HH
#define XFC_GTK_LAYOUT_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef __GTK_LAYOUT_H__
#include <gtk/gtklayout.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Layout label.hh xfc/gtk/layout.hh
/// @brief A GtkLayout C++ wrapper class.
///
/// Layout is similar to DrawingArea in that it's a "blank slate" and doesn't do anything
/// but paint a blank background by default. It's different in that it supports scrolling
/// natively (you can add it to a ScrolledWindow), and it can contain child widgets, since
/// it's a Container. However if you're just going to draw, a DrawingArea is a better
/// choice since it has lower overhead. When handling expose events on a Layout, you must
/// draw to bin_window(), rather than to Gtk::Widget::get_window() as you would for a
/// drawing area.
///
/// <B>See also:</B> the <A HREF="../../howto/html/layout.html">Layout Container</A> HOWTO.

class Layout : public Container
{
	friend class G::Object;

	Layout(const Layout&);
	Layout& operator=(const Layout&);
	
protected:
/// @name Constructors
/// @{

	explicit Layout(GtkLayout *layout, bool owns_reference = false);
	///< Construct a new Layout from an existing GtkLayout.
	///< @param layout A pointer to a GtkLayout.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>layout</EM> can be a newly created GtkLayout or an existing
	///< GtkLayout (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Adjustment*, Adjustment*> SetScrollAdjustmentsSignalType;
	typedef G::SignalProxy<TypeInstance, SetScrollAdjustmentsSignalType> SetScrollAdjustmentsSignalProxy;
	static const SetScrollAdjustmentsSignalType set_scroll_adjustments_signal;
	///< Set scroll adjustments signal (see signal_set_scroll_adjustments()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Adjustment *hadjustment, Gtk::Adjustment *vadjustment);
	///< // hadjustment: The horizontal adjustment.
	///< // vadjustment: The vertical adjustment.
	///< @endcode
	
/// @}

public:
	typedef GtkLayout CObjectType;

/// @name Constructors
/// @{

	Layout();
	///< Construct a new Layout with default horizontal and vertical adjustments.

	Layout(Adjustment *hadjustment, Adjustment *vadjustment);
	///< Construct a new Layout with the specified horizontal and vertical adjustments.
	///< @param hadjustment The Adjustment for the horizontal position.
	///< @param vadjustment The Adjustment for the vertical position.

	virtual ~Layout();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkLayout* gtk_layout() const;
	///< Get a pointer to the GtkLayout structure.

	operator GtkLayout* () const;
	///< Conversion operator; safely converts a Layout to a GtkLayout pointer.

	Gdk::Window* bin_window() const;
	///< Returns the Gdk::Window to draw to in response to an expose event.
	///< Note layout widgets should not draw to Gtk::Widget::get_window().

	void get_size(unsigned int *width, unsigned int *height);
	///< Gets the size that has been set on the layout, and that determines
	///< the total extents of the layout's scrollbar area (see set_size()).
	///< @param width The location to store the width set on layout, or null.
	///< @param height The location to store the height set on layout, or null.

	Adjustment* get_hadjustment() const;
	///< Get the Adjustment for the horizontal position.
	///< @return The Adjustment used for communication between the horizontal scrollbar and layout.
	///<
	///< This method should only be called after the layout has been
	///< placed in a ScrolledWindow or otherwise configured for scrolling
	///< (see ScrolledWindow, Scrollbar, Adjustment for details).

	Adjustment* get_vadjustment() const;
	///< Get the Adjustment for the vertical position.
	///< @return The Adjustment used for communication between the vertical scrollbar and layout.
	///<
	///< This method should only be called after the layout has been
	///< placed in a ScrolledWindow or otherwise configured for scrolling
	///< (see ScrolledWindow, Scrollbar, Adjustment for details).

/// @}
/// @name Methods
/// @{

	void put(Widget& child_widget, int x, int y);
	///< Add <EM>child_widget</EM> to the Layout, at position (x,y); the Layout becomes the new parent
	///< container of child_widget.
	///< @param child_widget The child widget to add.
	///< @param x The X position of child widget.
	///< @param y The Y position of child widget.

	void move(Widget& child_widget, int x, int y);
	///< Move a current child of the Layout to a new position.
	///< @param child_widget The child of the Layout to move.
	///< @param x The X position to move to.
	///< @param y The Y position to move to.
	
	void set_size(unsigned int width, unsigned int height);
	///< Sets the size of the scrollable area of the layout.
	///< @param width The width of entire scrollable area.
	///< @param height The height of entire scrollable area.

	void set_hadjustment(Adjustment *adjustment);
	///< Sets the horizontal scroll adjustment for the layout.
	///< @param adjustment The new horizontal scroll adjustment.
	///<
	///< See ScrolledWindow, Scrollbar, Adjustment for details.

	void set_vadjustment(Adjustment *adjustment);
	///< Sets the vertical scroll adjustment for the layout.
	///< @param adjustment The new vertical scroll adjustment.
	///<
	///< See ScrolledWindow, Scrollbar, Adjustment for details.

/// @}
/// @name Signal Proxies
/// @{

	const SetScrollAdjustmentsSignalProxy signal_set_scroll_adjustments();
	///< Connect to the set_scroll_adjustments_signal; emitted when a layout is added
	///< to a scrolling aware parent.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/layout.inl>

#endif // XFC_GTK_LAYOUT_HH

