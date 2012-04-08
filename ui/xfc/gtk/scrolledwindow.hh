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
 
/// @file xfc/gtk/scrolledwindow.hh
/// @brief A GtkScrolledWindow C++ wrapper interface.
///
/// Provides ScrolledWindow, a container that holds a single child widget. ScrolledWindow adds
/// scrollbars to the child widget and optionally draws a beveled frame around the child widget.

#ifndef XFC_GTK_SCROLLED_WINDOW_HH
#define XFC_GTK_SCROLLED_WINDOW_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef XFC_GTK_ADJUSTMENT_HH
#include <xfc/gtk/adjustment.hh>
#endif

#ifndef __GTK_SCROLLED_WINDOW_H__
#include <gtk/gtkscrolledwindow.h>
#endif

namespace Xfc {

namespace Gtk {
	
class HScrollbar;
class VScrollbar;

/// @class ScrolledWindow scrolledwindow.hh xfc/gtk/scrolledwindow.hh
/// @brief A GtkScrolledWindow C++ wrapper class.
///
/// ScrolledWindow is a Bin subclass: it's a container that holds a single child widget. 
/// ScrolledWindow adds scrollbars to the child widget and optionally draws a beveled frame
/// around the child widget.
///
/// The scrolled window can work in two ways. Some widgets have native scrolling support;
/// these widgets have "slots" for Adjustment objects. The scrolled window installs 
/// Adjustment objects in the child window's slots using the set_scroll_adjustments_signal. 
/// Widgets with native scroll support include TreeView, TextView, and Layout. 
///
/// For widgets that lack native scrolling support, the Viewport widget acts as an adaptor
/// class, implementing scrollability for child widgets that lack their own scrolling 
/// capabilities. Use Viewport to scroll child widgets such as Table, Box, and so on. 
///
/// If a widget has native scrolling abilities, it can be added to the ScrolledWindow with
/// Gtk::Container::add(). If a widget does not, you must first add the widget to a Viewport,
/// then add the Viewport to the scrolled window. The convenience function add_with_viewport()
/// does exactly this, so you can ignore the presence of the viewport. 
///
/// The position of the scrollbars is controlled by the scroll adjustments. See Adjustment for
/// the fields in an adjustment - for Scrollbar, used by ScrolledWindow, the "value" field 
/// represents the position of the scrollbar, which must be between the <EM>lower</EM> field and
/// <EM>upper - page_size</EM>. The <EM>page_size</EM> field represents the size of the visible
/// scrollable area. The <EM>step_increment</EM> and "page_increment" fields are used when the user
/// asks to step down (using the small stepper arrows) or page down (using for example the Page Down key). 
///
/// If a ScrolledWindow doesn't behave quite as you would like, or doesn't have exactly the right 
/// layout, it's very possible to set up your own scrolling with Scrollbar and for example a Table.
///
/// <B>See also:</B> the <A HREF="../../howto/html/scrolledwindows.html">ScrolledWindow</A> and
/// <A HREF="../../howto/html/viewports.html">Viewport</A> HOWTOs.

class ScrolledWindow : public Bin
{
	friend class G::Object;

	ScrolledWindow(const ScrolledWindow&);
	ScrolledWindow& operator=(const ScrolledWindow&);

protected:
/// @name Constructors
/// @{

	explicit ScrolledWindow(GtkScrolledWindow *scrolled_window, bool owns_reference = false);
	///< Construct a new ScrolledWindow from an existing GtkScrolledWindow.
	///< @param scrolled_window A pointer to a GtkScrolledWindow.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>scrolled_window</EM> can be a newly created GtkScrolledWindow or an existing
	///< GtkScrolledWindow (see G::Object::Object).
	
/// @}	

public:
	typedef GtkScrolledWindow CObjectType;

/// @name Constructors
/// @{

	ScrolledWindow();
	///< Construct a new scrolled window. The scrolled window will create both adjustments for you.
	///< The adjustments can be retrieved by calling get_hadjustment() and get_vadjustment().

	ScrolledWindow(Adjustment *hadjustment, Adjustment *vadjustment);
	///< Construct a new scrolled window with the specified adjustments. 
	///< @param hadjustment The Horizontal adjustment. 
	///< @param vadjustment The Vertical adjustment. 
	///<	
	///< The two adjustments will be shared with the scrollbars and the child widget to keep
	///< the bars in sync with the child. If you pass null for an adjustment the scrolled window
	///< will create that adjustment for you.

	virtual ~ScrolledWindow();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkScrolledWindow* gtk_scrolled_window() const;
	///< Get a pointer to the GtkScrolledWindow structure.
	
	operator GtkScrolledWindow* () const;
	///< Conversion operator; safely converts a ScrolledWindow to a GtkScrolledWindow pointer.

	HScrollbar* hscrollbar() const;
	///< Get a pointer to the horizontal scrollbar.

	VScrollbar* vscrollbar() const;
	///< Get a pointer to the vertical scrollbar.

	Adjustment* get_hadjustment() const;
	///< Returns the horizontal scrollbar's adjustment, used to connect the horizontal
	///< scrollbar to the child widget's horizontal scroll functionality. 
	///< @return The horizontal Adjustment.

 	Adjustment* get_vadjustment() const;
	///< Returns the vertical scrollbar's adjustment, used to connect the vertical
	///< scrollbar to the child widget's vertical scroll functionality. 
	///< @return The vertical Adjustment.

	void get_policy(PolicyType *hscrollbar_policy, PolicyType *vscrollbar_policy) const;
	///< Retrieves the current policy values for the horizontal and vertical scrollbars (see set_policy()).
	///< @param hscrollbar_policy The location to store the policy for the horizontal scrollbar, or null. 
	///< @param vscrollbar_policy The location to store the policy for the horizontal scrollbar, or null. 
 
	CornerType get_placement() const;
	///< Gets the placement of the scrollbars for the scrolled window (see set_placement()).
	///< @return The current placement value. 
 
 	ShadowType get_shadow_type() const;
	///< Gets the shadow type of the scrolled window (see set_shadow_type()).
	///< @return The current shadow type. 
 
/// @}
/// @name Methods
/// @{

	void set_hadjustment(Adjustment *hadjustment);
	///< Sets the Adjustment for the horizontal scrollbar. 
	///< @param hadjustment The horizontal scroll adjustment. 
 
	void set_vadjustment(Adjustment *vadjustment);
	///< Sets the Adjustment for the vertical scrollbar. 
	///< @param vadjustment The vertical scroll adjustment. 

	void set_policy(PolicyType hscrollbar_policy, PolicyType vscrollbar_policy);
	///< Sets the scrollbar policy for the horizontal and vertical scrollbars. 
	///< @param hscrollbar_policy The policy for horizontal bar. 
	///< @param vscrollbar_policy The policy for vertical bar.
	///< 
	///< The policy determines when the scrollbar should appear; it is a value from the 
	///< Gtk::PolicyType enumeration. If POLICY_ALWAYS, the scrollbar is always present; if
	///< POLICY_NEVER, the scrollbar is never present; if POLICY_AUTOMATIC, the scrollbar is
	///< present only if needed (that is, if the slider part of the bar would be smaller than
	///< the trough - the display is larger than the page size). 

	void set_policy_automatic();
	///< Sets the scrollbar policy for the horizontal and vertical scrollbars to POLICY_AUTOMATIC, 
	///< which means the scrollbars are present only if needed.
	
	void set_placement(CornerType window_placement);
	///< Determines the location of the child widget with respect to the scrollbars. 
	///< @param window_placement The position of the child window. 
	///<	
	///< The default is CORNER_TOP_LEFT, meaning the child is in the top left, with the
	///< scrollbars underneath and to the right. Other values in CornerType are CORNER_TOP_RIGHT,
	///< CORNER_BOTTOM_LEFT, and CORNER_BOTTOM_RIGHT. 
 
	void set_shadow_type(ShadowType type);
	///< Changes the type of shadow drawn around the contents of scrolled_window.
	///< @param type The kind of shadow to draw around scrolled window contents. 

	void add_with_viewport(Widget& child);
	///< Used to add children without native scrolling capabilities. 
	///< @param child The wdget you want to scroll.
	///<
	///< This is simply a convenience function; it is equivalent to adding the unscrollable
	///< child to a viewport, then adding the viewport to the scrolled window. If a child has
	///< native scrolling, use Gtk::Container::add() instead of this function. The viewport 
	///< scrolls the child by moving its Gdk::Window, and takes the size of the child to be the
	///< size of its toplevel Gdk::Window. This will be very wrong for most widgets that support
	///< native scrolling; for example, if you add a widget such as TreeView with a viewport, 
	///< the whole widget will scroll, including the column headings. Thus, widgets with native
	///< scrolling support should not be used with the Viewport proxy.
	///<
	///< A widget supports scrolling natively if the set_scroll_adjustments_signal is declared
	///< in its class declaration. 

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/scrolledwindow.inl>

#endif // XFC_GTK_SCROLLED_WINDOW_HH

