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
 
/// @file xfc/gtk/handlebox.hh
/// @brief A GtkHandleBox C++ wrapper interface.
///
/// Provides HandleBox, a widget that allows a portion of a window to be "torn off".
/// It is a bin widget which displays its child and a handle that the user can drag
/// to tear off a separate window (the float window) containing the child widget.

#ifndef XFC_GTK_HANDLE_BOX_HH
#define XFC_GTK_HANDLE_BOX_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_HANDLE_BOX_H__
#include <gtk/gtkhandlebox.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class HandleBox handlebox.hh xfc/gtk/handlebox.hh
/// @brief A GtkHandleBox C++ wrapper class.
///
/// The HandleBox widget allows a portion of a window to be "torn off". It is a bin widget
/// which displays its child and a handle that the user can drag to tear off a separate
/// window (the float window) containing the child widget. A thin ghost is drawn in the
/// original location of the handlebox. By dragging the separate window back to its original
/// location, it can be reattached. When reattaching, the ghost and float window, must be 
/// aligned along one of the edges, the snap edge. This either can be specified by the
/// application programmer explicitely, or GTK+ will pick a reasonable default based on the
/// handle position. To make detaching and reattaching the handlebox as minimally confusing
/// as possible to the user, it is important to set the snap edge so that the snap edge does
/// not move when the handlebox is deattached. For instance, if the handlebox is packed at 
/// the bottom of a VBox, then when the handlebox is detached, the bottom edge of the 
/// handlebox's allocation will remain fixed as the height of the handlebox shrinks, so the
/// snap edge should be set to POS_BOTTOM.

class HandleBox : public Bin
{
	friend class G::Object;

	HandleBox(const HandleBox&);
	HandleBox& operator=(const HandleBox&);

protected:
/// @name Constructors
/// @{

	explicit HandleBox(GtkHandleBox *handle_box, bool owns_reference = false);
	///< Construct a new HandleBox from an existing GtkHandleBox.
	///< @param handle_box A pointer to a GtkHandleBox.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>handle_box</EM> can be a newly created GtkHandleBox or an existing
	///< GtkHandleBox (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Widget&> ChildAttachedSignalType;
	typedef G::SignalProxy<TypeInstance, ChildAttachedSignalType> ChildAttachedSignalProxy;
	static const ChildAttachedSignalType child_attached_signal;
	///< Child attached signal (see signal_child_attached()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Widget& widget);
	///< // child: The child widget of the handlebox.
	///< @endcode

	typedef G::Signal<void, Widget&> ChildDetachedSignalType;
	typedef G::SignalProxy<TypeInstance, ChildDetachedSignalType> ChildDetachedSignalProxy;
	static const ChildDetachedSignalType child_detached_signal;
	///< Child detached signal (see signal_child_detached()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Widget& widget);
	///< // child: The child widget of the handlebox.
	///< @endcode
	
/// @}

public:
	typedef GtkHandleBox CObjectType;

/// @name Constructors
/// @{

	explicit HandleBox(ShadowType shadow_type = SHADOW_OUT);
	///< Construct a new HandleBox with the specified shadow type drawn around the border.
	///< @param shadow_type The shadow type.

	virtual ~HandleBox();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkHandleBox* gtk_handle_box() const;
	///< Get a pointer to the GtkHandleBox structure.

	operator GtkHandleBox* () const;
	///< Conversion operator; safely converts a HandleBox to a GtkHandleBox pointer.

	bool is_child_detached() const;
	///< Returns true if the handlebox's child is detached.

	Gdk::Window* get_bin_window() const;
	///< Gets the parent Gdk::Window for the child.

	Gdk::Window* get_float_window() const;
	///< Gets the Gdk::Window for the floating window.

	ShadowType get_shadow_type() const;
	///< Gets the type of shadow drawn around the handle box (see set_shadow_type()).

	PositionType get_handle_position() const;
	///< Gets the handle position of the handle box (see set_handle_position()).

	PositionType get_snap_edge() const;
	///< Gets the edge used for determining reattachment of the handle box (see set_snap_edge()).

/// @}
/// @name Methods
/// @{
	
	void set_shadow_type(ShadowType type);
	///< Sets the type of shadow to be drawn around the border of the handle box.
	///< @param type The shadow type.

	void set_handle_position(PositionType position);
	///< Sets the side of the handlebox where the handle is drawn.
	///< @param position The side of the handlebox where the handle should be drawn.

	void set_snap_edge(PositionType edge);
	///< Sets the snap edge of a handlebox.
	///< @param edge The snap edge.
	///<
	///< The snap edge is the edge of the detached child that must be aligned with
	///< the corresponding edge of the "ghost" left behind when the child was detached
	///< to reattach the torn-off window. Usually, the snap edge should be chosen so
	///< that it stays in the same place on the screen when the handlebox is torn off.
	///< If the snap edge is not set, then an appropriate value will be guessed from
	///< the handle position. If the handle position is POS_RIGHT or POS_LEFT, then 
	///< the snap edge will be POS_TOP, otherwise it will be POS_LEFT.

	void unset_snap_edge();
	///< Unsets the snap edge of a handlebox, in which case GTK+ will try to guess an
	///< appropriate value in the future.

/// @}
/// @name Signal Proxies
/// @{

	const ChildAttachedSignalProxy signal_child_attached();
	///< Connect to the child_attached_signal; emitted when the contents of the handlebox
	///< are reattached to the main window.

	const ChildDetachedSignalProxy signal_child_detached();
	///< Connect to the child_detached_signal; emitted when the contents of the handlebox
	///< are detached from the main window.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/handlebox.inl>

#endif // XFC_GTK_HANDLE_BOX_HH

