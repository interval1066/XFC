/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/gdk/dnd.hh
/// @brief A GdkDragContext C++ wrapper interface.
///
/// Provides DragContext, an object that controls drag and drop handling.

#ifndef XFC_GDK_DND_HH
#define XFC_GDK_DND_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gdk {

class Display;
class Screen;
class Window;

/// @class DragContext dnd.hh xfc/gdk/dnd.hh
/// @brief A GdkDragContext C++ wrapper class.
///
/// DragContext provides a low level interface for drag and drop. The X backend of GDK
/// supports both the Xdnd and Motif drag and drop protocols transparently, the Win32
/// backend supports the WM_DROPFILES protocol.
///
/// GTK+ provides a higher level abstraction based on top of this inteface, so it's
/// not normally needed in GTK+ applications.

class DragContext : public G::Object
{
	friend class G::Object;

	DragContext(const DragContext&);
	DragContext& operator=(const DragContext&);
	
protected:
/// @name Constructors
/// @{

	DragContext();
	///< Constructs a new drag context.

	explicit DragContext(GdkDragContext *drag_context, bool owns_reference = true);
	///< Construct a new DragContext from an existing GdkDragContext.
	///< @param drag_context A pointer to a GdkDragContext.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>drag_context</EM> can be a newly created GdkDragContext or an existing
	///< GdkDragContext. (see G::Object::Object).

/// @}

public:
	typedef GdkDragContext CObjectType;

/// @name Constructors
/// @{

	virtual ~DragContext();
	///< Destructor.
	
/// @}
/// @name Accessors
///< @{

	GdkDragContext* gdk_drag_context() const;
	///< Get a pointer to the GdkDragContext structure.

	operator GdkDragContext* () const;
	///< Conversion operator; safely converts a DragContext to a GdkDragContext pointer.

	DragProtocol protocol() const;
	///< Returns the DND protocol which governs this drag.

	bool is_source() const;
	///< Returns <EM>true</EM> if the context is used on the source side.

	Window* source_window() const;
	///< Returns the source window of this drag.

	Window* dest_window() const;
	///< Returns the destination window of this drag.

	bool targets(std::vector<Atom>& target_list) const;
	///< Gets a list of targets offered by the source.
	///< @param target_list A reference to a vector of Atom to hold the list of targets.
	///< @return <EM>true</EM> if the vector is not empty.

	DragActionField actions() const;
	///< Returns a bitmask of actions proposed by the source when suggested_action is ACTION_ASK.

	DragActionField suggested_action() const;
	///< Returns the action suggested by the source.

	DragActionField action() const;
	///< Returns the action chosen by the destination.

	unsigned int start_time() const;
	///< Returns a timestamp recording the start time of this drag.

	Atom get_selection() const;
	///< Gets the selection atom for the current source window.
	///< @return The selection atom.

	bool drag_drop_succeeded() const;
	///< Determines wether the dropped data has been successfully transferred. 
	///< @return <EM>true</EM> if the drop was successful.
	///<	
	///< This method is intended to be used while handling a Gdk::DROP_FINISHED event,
	///< its return value is meaningless at other times.

/// @}
/// @name Accessors
/// @{

	static unsigned int drag_get_protocol(unsigned int xid, DragProtocol *protocol, const Display *display = 0);
	///< Finds out the DND protocol supported by a window.
	///< @param xid The X id of the destination window.
	///< @param protocol The location where the supported DND protocol is returned.
	///< @param display The Display where the destination window resides, or null for the defualt display.
	///< @return The X id of the window where the drop should happen.
	///<
	///< The X id may be <EM>xid</EM> or the X id of a proxy window, or none if xid
	///< doesn't support Drag and Drop.

/// @}
/// @name Methods
/// @{

	void drag_status(DragActionField action, unsigned int time);
	///< Selects one of the actions offered by the drag source.
	///< @param action The selected action which will be taken when a drop happens, or 0
	///<               to indicate that a drop will not be accepted.
	///< @param time The timestamp for this operation.
	///<
	///< This method is called by the drag destination in response to drag_motion()
	///< called by the drag source.

	void drop_reply(bool ok, unsigned int time);
	///< Accepts or rejects a drop.
	///< @param ok Set <EM>true</EM> if the drop is accepted.
	///< @param time The timestamp for this operation.
	///<
	///< This method is called by the drag destination in response to
	///< a drop initiated by the drag source.

	void drop_finish(bool success, unsigned int time);
	///< Ends the drag operation after a drop.
	///< @param success set <EM>true</EM> if the data was successfully received.
	///< @param time The timestamp for this operation.
	///<
	///< This method is called by the drag destination.

	void find_window(int x_root, int y_root, Window **dest_window, DragProtocol *protocol, const Screen *screen = 0);
	///< Finds the destination window and DND protocol to use at the given pointer position.
	///< @param x_root The X position of the pointer in root coordinates.
	///< @param y_root The Y position of the pointer in root coordinates.
	///< @param dest_window The location to store the destination window in.
	///< @param protocol The location to store the DND protocol in.
	///< @param screen The screen where the destination window is sought, or null
	///<               for the screen the source window is on.
	///<
	///< This method is called by the drag source to obtain the dest_window and protocol
	///< parameters for motion().

	bool drag_motion(const Window& dest_window, DragProtocol protocol, int x_root, int y_root,
	                 DragActionField suggested_action, DragActionField possible_actions, unsigned int time);
	///< Updates the drag context when the pointer moves or the set of actions changes.
	///< @param dest_window The new destination window, obtained by find_window().
	///< @param protocol The DND protocol in use, obtained by find_window().
	///< @param x_root The X position of the pointer in root coordinates.
	///< @param y_root The y position of the pointer in root coordinates.
	///< @param suggested_action The suggested action.
	///< @param possible_actions The possible actions.
	///< @param time The timestamp for this operation.
	///< @return
	///<
	///< This method is called by the drag source.

	void drag_drop(unsigned int time);
	///< Drops on the current destination.
	///< @param time The timestamp for this operation.
	///<
	///< This method is called by the drag source.

	void drag_abort(unsigned int time);
	///< Aborts a drag without dropping.
	///< @param time The timestamp for this operation.
	///<
	///< This method is called by the drag source.

	void set_action(DragActionField action);
	///< Set the drag action value that specifies what destination should do with the dropped data.
	///< @param action The new Gdk::DragAction value to set.
	///<
	///< You would typically call this method from within a Gtk::Widget <EM>drag_data_received</EM>
	///< signal handler. By calling action(), you can inspect the drag action chosen by the drop site
	///< and modify its value.

/// @}
/// @name Methods
/// @{

	static Pointer<DragContext> drag_begin(const Window& window, const std::vector<Atom>& targets);
	///< Starts a drag and creates a new drag context for it.
	///< @param window The source window for this drag.
	///< @param targets A reference to a vector of Atom holding the list of offered targets.
	///< @return A smart pointer to a newly created DragContext.
	///<
	///< This method is called by the drag source.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#include <xfc/gdk/inline/dnd.inl>

#endif // XFC_GDK_DND_HH

