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
 
/// @file xfc/gtk/eventbox.hh
/// @brief A GtkEventBox C++ wrapper interface.
///
/// Provides EventBox, a widget that can be used to catch events for widgets which
/// do not have their own window.

#ifndef XFC_GTK_EVENT_BOX_HH
#define XFC_GTK_EVENT_BOX_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_EVENT_BOX_H__
#include <gtk/gtkeventbox.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class EventBox eventbox.hh xfc/gtk/eventbox.hh
/// @brief A GtkEventBox C++ wrapper class.
///
/// The EventBox widget is a subclass of Bin which also has its own window. It is useful since
/// it allows you to catch events for widgets which do not have their own window.
///
/// <B>See also:</B> the <A HREF="../../howto/html/eventbox.html">EventBox</A> HOWTO and example.

class EventBox : public Bin
{
	friend class G::Object;

	EventBox(const EventBox&);
	EventBox& operator=(const EventBox&);
	
protected:
/// @name Constructors
/// @{

	explicit EventBox(GtkEventBox *event_box, bool owns_reference = false);
	///< Construct a new EventBox from an existing GtkEventBox.
	///< @param event_box A pointer to a GtkEventBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>event_box</EM> can be a newly created GtkEventBox or an existing
	///< GtkEventBox (see G::Object::Object).

/// @}

public:
	typedef GtkEventBox CObjectType;

/// @name Constructors
/// @{

	EventBox();
	///< Construct a new EventBox.

	virtual ~EventBox();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkEventBox* gtk_event_box() const;
	///< Get a pointer to the GtkEventBox structure.

	operator GtkEventBox* () const;
	///< Conversion operator; safely converts an EventBox to a GtkEventBox pointer.

	bool get_visible_window() const;
	///< Determines whether the event box has a visible window (see set_visible_window() for details).
	///< @return <EM>true</EM> if the event box window is visible.

	bool get_above_child() const;
	///< Determines whether the event box window is above or below the windows of its child
	///< (see set_above_child() for details).
	///< @return <EM>true</EM> if the event box window is above the window of its child.

/// @}
/// @name Methods
/// @{

	void set_visible_window(bool visible_window);
	///< Set whether the event box uses a visible or invisible child window.
	///< @param visible_window Set <EM>true</EM> if the event box uses a visible child window.
	///<
	///< The default is to use visible windows. In an invisible window event box,
	///< the window that the event box creates is a Gdk::INPUT_ONLY window, which means
	///< that it is invisible and only serves to receive events.
	///<
	///< A visible window event box creates a visible (Gdk::INPUT_OUTPUT) window that acts as
	///< the parent window for all the widgets contained in the event box. You should generally
	///< make your event box invisible if you just want to trap events. Creating a visible
	///< window may cause artifacts that are visible to the user, especially if the user is
	///< using a theme with gradients or pixmaps. The main reason to create a non input-only
	///< event box is if you want to set the background to a different color or draw on it.
	///<
	///< <B>Note:</B> There is one unexpected issue for an invisible event box that has its
	///< window below the child (see set_above_child()). Since the input-only window is not
	///< an ancestor window of any windows that descendent widgets of the event box create,
	///< events on these windows aren't propagated up by the windowing system, but only by
	///< GTK+. The practical effect of this is if an event isn't in the event mask for the
	///< descendant window (see Gtk::Widget::add_events()), it won't be received by the event
	///< box. This problem doesn't occur for visible event boxes, because in that case, the
	///< event box window is actually the ancestor of the descendant windows, not just at the
	///< same place on the screen.

	void set_above_child(bool above_child);
	///< Set whether the event box window is positioned above the windows of its child,
	///< as opposed to below it.
	///< @param above_child Set <EM>true</EM> if the event box window is above the windows of its child.
	///<
	///< If the window is above, all events inside the event box will go to the event box.
	///< If the window is below, events in windows of child widgets will first go to that widget,
	///< and then to its parents. The default is to keep the window below the child.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/eventbox.inl>

#endif // XFC_GTK_EVENT_BOX_HH

