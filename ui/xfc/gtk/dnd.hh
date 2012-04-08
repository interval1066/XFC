/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2002-2003 The XFC Development Team.
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

/// @file xfc/gtk/dnd.hh
/// @brief Gtk Drag and Drop C++ wrapper interface.
///
/// GTK+ has a rich set of functions for doing inter-process communication via the drag-and-drop
/// metaphor. GTK+ can do drag-and-drop (DND) via multiple protocols. The currently supported
/// protocols are the Xdnd and Motif protocols. As well as the methods in this class, applications
/// may need to use some facilities provided for Selections. Also, the Drag and Drop API makes use
/// of signals in the Widget class.

#ifndef XFC_GTK_DND_HH
#define XFC_GTK_DND_HH

#ifndef XFC_GDK_DND_HH
#include <xfc/gdk/dnd.hh>
#endif

#ifndef __GTK_DND_H__
#include <gtk/gtkdnd.h>
#endif

namespace Xfc {
	
namespace Gdk {
class Bitmap;
class Colormap;
class Pixbuf;
class Pixmap;
}

namespace Gtk {
	
class StockId;
class Widget;

/// @enum DestDefaults
/// Specifies the various types of action that will be taken on behalf
/// of the user for a drag destination site.

enum DestDefaults
{
	DEST_DEFAULT_MOTION = GTK_DEST_DEFAULT_MOTION,
	///< If set for a widget, GTK+, during a drag over this widget will check if the drag
	///< matches this widget's list of possible targets and actions (GTK+ will then call
	///< gtk_drag_status() as appropriate).
	
	DEST_DEFAULT_HIGHLIGHT = GTK_DEST_DEFAULT_HIGHLIGHT,
	///< If set for a widget, GTK+ will draw a highlight on this widget as long as a drag
	///< is over this widget and the widget drag format and action are acceptable.
	
	DEST_DEFAULT_DROP = GTK_DEST_DEFAULT_DROP,
	///< If set for a widget, when a drop occurs, GTK+ will will check if the drag matches
	///< this widget's list of possible targets and actions and if so, GTK+ will call
	///< gtk_drag_data_get() on behalf of the widget. 

	DEST_DEFAULT_ALL = GTK_DEST_DEFAULT_ALL
	///<  If set, specifies that all default actions should be taken.
};

/// DestDefaultsField holds one or more flags from the Gtk::DestDefaults enumeration OR'd together.

typedef unsigned int DestDefaultsField;

/// @enum TargetFlags
/// Specifies the constraints on an entry in a TargetTable.

enum TargetFlags
{
	TARGET_SAME_APP = GTK_TARGET_SAME_APP,
	///< If this is set, the target will only be selected for drags within a single application. 
	
	TARGET_SAME_WIDGET = GTK_TARGET_SAME_WIDGET
	///< If this is set, the target will only be selected for drags within a single widget.
};

/// TargetFlagsField holds one or more flags from the Gtk::TargetFlags enumeration OR'd together.

typedef unsigned int TargetFlagsField;

/// @class DragContext dnd.hh xfc/gtk/dnd.hh
/// @brief A GTK+ Drag and Drop C++ wrapper class.
///
/// GTK+ has a rich set of functions for doing inter-process communication via the drag-and-drop
/// metaphor. GTK+ can do drag-and-drop (DND) via multiple protocols. The currently supported
/// protocols are the Xdnd and Motif protocols. As well as the methods in this class, applications
/// may need to use some facilities provided for Selections. Also, the Drag and Drop API makes use
/// of signals in the Widget class.
///
/// DragContext is a convenient wrapper class for the GTK+ drag-and-drop functions. It derives
/// from Gdk::DragContext. There is no GtkDragContext.
///
/// The default icon for a drag opration can be changed via the stock system by changing the stock
/// pixbuf for GTK_STOCK_DND.
///
/// <B>See also:</B> the <A HREF="../../howto/html/draganddrop.html">Drag and Drop</A> and
/// <A HREF="../../howto/html/selections.html">Selection</A> HOWTOs and examples.

class DragContext : public Gdk::DragContext
{
	friend class G::Object;
	
protected:
/// @name Constructors
/// @{

	explicit DragContext(GdkDragContext *drag_context, bool reference = true);
	///< Construct a new DragContext from an existing GdkDragContext.
	///< @param drag_context A pointer to a GdkDragContext.
	///< @param reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>drag_context</EM> can be a newly created GdkDragContext or an existing
	///< GdkDragContext. (see G::Object::Object).

/// @}

public:
/// @name Constructors
/// @{
	
	virtual ~DragContext();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	Widget* get_source_widget() const;
	///< Determines the source widget for a drag.
	///< @return If the drag is occurring within a single application, a pointer
	///<         to the source widget. Otherwise, null.

/// @}
/// @name Methods
/// @{

	void finish(bool success, bool delete_data, unsigned int time);
	///< Informs the drag source that the drop is finished, and that the data of the drag
	///< will no longer be required.
	///< @param success A flag indicating whether the drop was successful.
	///< @param delete_data A flag indicating whether the source should delete the original data (true for a move).
	///< @param time The timestamp from the "drag_data_drop" signal.

	void set_icon_widget(Widget& widget, int hot_x, int hot_y);
	///< Changes the icon for a widget to a given widget. 
	///< @param widget A toplevel window to use as an icon.
	///< @param hot_x The X offset within widget of the hotspot.
	///< @param hot_y The Y offset within widget of the hotspot.
	///<
	///< GTK+ will not destroy the icon, so if you don't want it to persist, you should
	///< connect to the "drag_end" signal and destroy it yourself.

	void set_icon_pixmap(Gdk::Colormap& colormap, Gdk::Pixmap& pixmap, Gdk::Bitmap *mask, int hot_x, int hot_y);
	///< Sets pixmap as the icon for a given drag. 
	///< @param colormap The colormap of the icon.
	///< @param pixmap The image data for the icon.
	///< @param mask The transparency mask for the icon.
	///< @param hot_x The X offset within pixmap of the hotspot.
	///< @param hot_y The Y offset within pixmap of the hotspot.
	///<
	///< GTK+ retains references for the arguments, and will release them when they are
	///< no longer needed. In general, set_icon_pixbuf() will be more convenient to use.

	void set_icon_pixbuf(Gdk::Pixbuf& pixbuf, int hot_x, int hot_y);
	///< Sets pixbuf as the icon for a given drag.
	///< @param pixbuf The image data for the icon.
	///< @param hot_x The X offset within pixbuf of the hotspot.
	///< @param hot_y The Y offset within pixbuf of the hotspot.

	void set_icon_stock(const StockId& stock_id, int hot_x, int hot_y);
	///< Sets the icon for a given drstock_idag from a stock ID.
	///< @param stock_id The identifier of the stock icon to use for the drag.
	///< @param hot_x The X offset within icon of the hotspot.
	///< @param hot_y The Y offset within icon of the hotspot.
	
	void set_icon_default();
	///< Sets the icon for a particular drag to the default icon.
	///< This must be called with a context for the source side of a drag.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/dnd.inl>

#endif // XFC_GTK_DND_HH

