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

/// @file xfc/gtk/widget.hh
/// @brief A GtkWidget C++ wrapper interface.
/// 
/// Provides Widget, the base class for widgets that make up the GTK+ graphical user interface,
/// such as windows, menus, buttons, scrollbars editors, drawing areas, and so on. 

#ifndef XFC_GTK_WIDGET_HH
#define XFC_GTK_WIDGET_HH

#ifndef XFC_CONFIG_H
#include <xfc/config.h>
#endif

#ifndef XFC_ATK_IMPLEMENTOR_HH
#include <xfc/atk/implementor.hh>
#endif

#ifndef XFC_GTK_ADJUSTMENT_HH
#include <xfc/gtk/adjustment.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef XFC_GDK_EVENTS_HH
#include <xfc/gdk/events.hh>
#endif

#ifndef XFC_GTK_SELECTION_HH
#include <xfc/gtk/selection.hh>
#endif

namespace Xfc {

namespace Atk {
class Object;
}

namespace Gdk {
class Bitmap;
class Color;
class Colormap;
class Cursor;
class Display;
class Event;
class Pixbuf;
class Region;
class Screen;
class Visual;
class Window;
}

namespace G {
class Value;
}

namespace Pango {
class Context;
class FontDescription;
class Layout;
}

namespace Gtk {

class AccelGroup;
class AccelKey;
class Clipboard;
class Container;
class RcStyle;
class Selection;
class Settings;
class StockId;
class Style;

/// @enum WidgetFlags
/// WidgetFlags tells about certain properties of the widget. 

enum WidgetFlags
{
	TOP_LEVEL = GTK_TOPLEVEL,
	///< Widgets without a real parent, such as Windows and Menus have this flag
	///< set throughout their lifetime; Toplevel widgets always contain their own
	///< Gdk::Window.
	
	NO_WINDOW = GTK_NO_WINDOW,
	///< Indicative for a widget that does not provide its own Gdk::Window;
	///< For such widgets, visible actions (such as drawing) are performed
	///< on the parent's Gdk::Window.
	
	REALIZED = GTK_REALIZED,
	///< Set by realize(), unset by unrealize(); A realized widget has an associated Gdk::Window.
	
	MAPPED = GTK_MAPPED,
	///< Set by map(), unset by unmap(); Only realized widgets can be mapped;
	///< It means that show() has been called on the widgets window(s).
	
	VISIBLE = GTK_VISIBLE,
	///< Set by show(), unset by hide(); Implies that a widget will be mapped
	///< as soon as its parent is mapped. 
	
	SENSITIVE = GTK_SENSITIVE,
	///< Set and unset by set_sensitive(); The sensitivity of a widget determines
	///< whether it will receive certain events (such as button or key presses);
	///< One premise for the widget's sensitivity is to have this flag set.
	
	PARENT_SENSITIVE = GTK_PARENT_SENSITIVE,
	///< Set and unset by set_sensitive() operations on the parents of the widget;
	///< This is the second premise for the widget's sensitivity; Once it has
	///< SENSITIVE and PARENT_SENSITIVE set, its state is effectively sensitive
	///< and Gtk::Widget::is_sensitive() will return true.

	CAN_FOCUS = GTK_CAN_FOCUS,
	///< Determines whether a widget is able to handle focus grabs.

	HAS_FOCUS = GTK_HAS_FOCUS,
	///< Set by grab_focus() for widgets that also have CAN_FOCUS set; This flag
	///< will be unset once another widget grabs the focus. 
	
	CAN_DEFAULT = GTK_CAN_DEFAULT,
	///< The widget is allowed to receive the default action via grab_default(). 
	
	HAS_DEFAULT = GTK_HAS_DEFAULT,
	///< The widget currently is receiving the default action. 
	
	HAS_GRAB = GTK_HAS_GRAB,
	///< Set by gtk_grab_add(), unset by gtk_grab_remove(); It means that the widget
	///< is in the grab_widgets stack, and will be the preferred one for receiving
	///< events other than ones of cosmetic value. 
	
	RC_STYLE = GTK_RC_STYLE,
	///< Indicates that the widgets style has been looked up through the rc mechanism; It does
	///< not imply that the widget actually had a style defined through the rc mechanism. 
	
	COMPOSITE_CHILD = GTK_COMPOSITE_CHILD,
	///< Indicates that the widget is a composite child of its parent; 
	///< see push_composite_child(), pop_composite_child(). 
	
	NO_REPARENT = GTK_NO_REPARENT,
	///< Unused since before GTK+ 1.2, will be removed in a future version. 
	
	APP_PAINTABLE = GTK_APP_PAINTABLE,
	///< Set and unset by set_app_paintable(); Must be set on widgets whose window the application
	///< directly draws on, in order to keep GTK+ from overwriting the drawn stuff. 
	
	RECEIVES_DEFAULT = GTK_RECEIVES_DEFAULT,
	///< The widget when focused will receive the default action and have HAS_DEFAULT
	///< set even if there is a different widget set as default.
	
	DOUBLE_BUFFERED = GTK_DOUBLE_BUFFERED,
	///< Set and unset by set_double_buffered(); Indicates that exposes
	///< done on the widget should be double-buffered.

	NO_SHOW_ALL = GTK_NO_SHOW_ALL
	///< The "no_show_all" property, which determines whether calls to show_all()
	///< and hide_all() will affect this widget (see Gtk::Widget::set_no_show_all()).
};

/// WidgetFlagsField holds one or more values from the Gtk::WidgetFlags enumeration OR'd together.

typedef unsigned int WidgetFlagsField;

/// @enum WidgetHelpType
/// WidgetHelpType defines the type of help, either tooltip or "What's this".

enum WidgetHelpType
{
	WIDGET_HELP_TOOLTIP = GTK_WIDGET_HELP_TOOLTIP, ///< Tooltip help.
	WIDGET_HELP_WHATS_THIS = GTK_WIDGET_HELP_WHATS_THIS ///< "What's this" help.
};

/// @class Allocation widget.hh xfc/gtk/widget.hh
/// @brief A GtkAllocation C++ wrapper class.
///
/// Allocation holds the position and size allocated to a widget. It derives publicly
/// from Gdk::Rectangle, which derives publicly from GdkRectangle. Allocation uses 
/// default copy, assignment and destruction and allows public access to GdkRectangle's 
/// x, y, width and height fields.

class Allocation : public Gdk::Rectangle
{
public:
/// @name Constructors
/// @{

	Allocation();
	///< Construct an empty allocation.

	Allocation(int x, int y, int width, int height);
	///< Construct an allocation with the specified position an size.
	///< @param x The X coordinate.
	///< @param y The Y coordinate.
	///< @param width The width of the allocation.
	///< @param height The height of the allocation.

	Allocation(const GtkAllocation& allocation);
	///< Construct a new allocation from an existing GtkAllocation.
	///< @param allocation A GtkAllocation.
	
/// @}
/// @name Accessors
/// @{

	GtkAllocation* gtk_allocation() const;
	///< Get a pointer to the GtkAllocation structure (GtkAllocation is a
	///< typedef for GdkRectangle).
	
/// @}
};

/// @class Requisition widget.hh xfc/gtk/widget.hh
/// @brief A GtkRequisition C++ wrapper class.
///
/// Requisition holds the preferred size for a widget. It derives publicly from
/// GtkRequisition. Requisition uses default copy, assignment and destruction
/// and allows public access to GtkRequisition's width and height fields.

class Requisition
{
	GtkRequisition requisition_;

public:
/// @name Constructors
/// @{

	Requisition();
	///< Construct an empty requisition.

	Requisition(int width, int height);
	///< Construct a requisition with the specified width and height.
	///< @param width The width of the requisition.
	///< @param height The height of the requisition.

	Requisition(const GtkRequisition& requisition);
	///< Construct a requisition from an exisiting GtkRequisition.
	///< @param requisition A GtkRequisition.

/// @}
/// @name Accessors
/// @{

	GtkRequisition* gtk_requisition() const;
	///< Get a pointer to the GtkRequisition structure.

	operator GtkRequisition* () const;
	///< Conversion operator; safely converts a Requisition to a GtkRequisition pointer.

	int width() const;
	///< Returns the requisition width.

	int height() const;
	///< Returns the requisition height.

	bool operator==(const Requisition& other) const;
	///< Returns <EM>true</EM> if this requisition is equal to <EM>other</EM>.
	///< @param other Another Requisition. 

	bool operator!=(const Requisition& other) const;
	///< Returns <EM>true</EM> if this requisition is not equal to <EM>other</EM>. 
	///< @param other Another Requisition. 

/// @}
/// @name Methods
/// @{

	void set(int width, int height);
	///< Set the width and height for the requisition.
	///< @param width The new width of the requisition.
	///< @param height The new height of the requisition.
	
/// @}
};

/// @class Widget widget.hh xfc/gtk/widget.hh
/// @brief A GtkWidget C++ wrapper class.
///
/// Widget is the base class for widgets that make up the graphical user interface,
/// such as windows, menus, buttons, scrollbars, editors, drawing areas, and so on.
///
/// After implementing a widget in your application you frequently need to set some
/// widget-specific attributes, such as the widget's size, position, and so on.
/// When the user interacts with a widget, such as pulling down a menu and making
/// a selection, clicking a button, or moving a scrollbar, your application needs to
/// respond by calling a callback slot that you supply. Callback slots are objects
/// that call the class or static method that you want attached to a user action.
/// 
/// A parent-child relationship must be established between widgets in your application,
/// such as by packing a button into a box or adding a menu item to a menu. These 
/// releationships provide management capabitilies and help determine the layout
/// of the user interface. After widgets are created, parent-child relationships
/// established, and callback slots attached you need to display the widgets. This is
/// accomplished by calling show() on a widget, or show_all() on the parent widget to
/// to show all the child widgets at once.
///
/// Any user action in you interface causes the corresponding widget to emit a signal,
/// to which your callback slot has been attached. You can respond to these signals
/// in two ways. The first way is to derive a new class from the widget, such as 
/// Gtk::Button, and override one or more of its inherited virutal signal handlers,
/// such as on_clicked() for the button's "clicked" signal. Continuing with 
/// Gtk::Button, the second way is to create an instance of Gtk::Button and attach to
/// it your clicked callback slot, by calling signal_clicked().connect(slot());
///
/// Widget implements this Atk::Implementor interface. Calling get_accessible() is the
/// same as calling ref_accessible() inherited from Atk::Implementor, except 
/// ref_accessible() returns a smart pointer.
///
/// <B>See also:</B> the <A HREF="../../howto/html/widgets.html">Widget</A>,
/// <A HREF="../../howto/html/composite_widgets.html">Composite Widget</A> and
/// <A HREF="../../howto/html/custom_widgets.html">Custom Widget</A> HOWTOs and examples.

class Widget : public Object, public Atk::Implementor
{
	friend class G::Object;

	Widget(const Widget&);
	Widget& operator=(const Widget&);

protected:
/// @name Constructors
/// @{

	Widget();
	///< Construct a new widget.

	explicit Widget(GtkWidget *widget, bool owns_reference = false);
	///< Construct a new Widget from an existing GtkWidget.
	///< @param widget A pointer to a GtkWidget.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>widget</EM> can be a newly created GtkWidget or an existing
	///< GtkWidget (see G::Object::Object).

/// @}
/// @name Methods
/// @{

	void set_allocation(const Allocation& allocation);
	///< Sets the position and size allocated to a child widget.
	///< @param allocation The position and size to be allocated to the widget.
	///<
	///< This method can be called from the widget's virtual <EM>on_size_request</EM>
	///< to set the allocation (see the Dial example program).

	void set_window(const Gdk::Window& window);
	///< Sets the Gdk::Window for the widget.
	///< @param window A Gdk::Window.
	///<
	///< This method only works if gtk_widget()->window is null. It is only for use when
	///< implementing a custom widget that derives directly from Gtk::Widget. After creating
	///< a Gdk::Window for the custom widget in the widget's virtual <EM>on_realize()</EM>
	///< method you should call this method to set the window. If the widget already has a
	///< Gdk::Window nothing happens (see the Dial example program).

/// @}
/// @name Basic Signal Prototypes
/// @{

	typedef G::Signal<void> ShowSignalType;
	typedef G::SignalProxy<TypeInstance, ShowSignalType> ShowSignalProxy;
	static const ShowSignalType show_signal;
	///< Show signal (see signal_show()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> HideSignalType;
	typedef G::SignalProxy<TypeInstance, HideSignalType> HideSignalProxy;
	static const HideSignalType hide_signal;
	///< Hide signal (see signal_hide()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> MapSignalType;
	typedef G::SignalProxy<TypeInstance, MapSignalType> MapSignalProxy;
	static const MapSignalType map_signal;
	///< Map signal (see signal_Map()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> UnmapSignalType;
	typedef G::SignalProxy<TypeInstance, UnmapSignalType> UnmapSignalProxy;
	static const UnmapSignalType unmap_signal;
	///< Unmap signal (see signal_unmap()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> RealizeSignalType;
	typedef G::SignalProxy<TypeInstance, RealizeSignalType> RealizeSignalProxy;
	static const RealizeSignalType realize_signal;
	///< Realize signal (see signal_realize()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> UnrealizeSignalType;
	typedef G::SignalProxy<TypeInstance, UnrealizeSignalType> UnrealizeSignalProxy;
	static const UnrealizeSignalType unrealize_signal;
	///< Unrealize signal (see signal_unrealize()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, Requisition*> SizeRequestSignalType;
	typedef G::SignalProxy<TypeInstance, SizeRequestSignalType> SizeRequestSignalProxy;
	static const SizeRequestSignalType size_request_signal;
	///< Size request signal (see signal_size_request()). Calls a slot with the signature:
	///< @code
	///< void function(Requisition *requisition);
	///< // requisition: The Requisition to be filled in.
	///< @endcode

	typedef G::Signal<void, const Allocation&> SizeAllocateSignalType;
	typedef G::SignalProxy<TypeInstance, SizeAllocateSignalType> SizeAllocateSignalProxy;
	static const SizeAllocateSignalType size_allocate_signal;
	///< Size allocate signal (see signal_size_allocate()). Calls a slot with the signature:
	///< @code
	///< void function(const Allocation& allocation);
	///< // allocation: The position and size allocated to the widget.
	///< @endcode

	typedef G::Signal<void, StateType> StateChangedSignalType;
	typedef G::SignalProxy<TypeInstance, StateChangedSignalType> StateChangedSignalProxy;
	static const StateChangedSignalType state_changed_signal;
	///< State changed signal (see signal_state_changed()). Calls a slot with the signature:
	///< @code
	///< void function(StateType previous_state);
	///< // previous_state: The previous StateType.
	///< @endcode

	typedef G::Signal<void, Widget*> ParentSetSignalType;
	typedef G::SignalProxy<TypeInstance, ParentSetSignalType> ParentSetSignalProxy;
	static const ParentSetSignalType parent_set_signal;
	///< Parent set signal (see signal_parent_set()). Calls a slot with the signature:
	///< @code
	///< void function((Widget *previous_parent);
	///< // previous_parent: The previous parent of the widget, or null.
	///< @endcode

	typedef G::Signal<void, Widget*> HierarchyChangedSignalType;
	typedef G::SignalProxy<TypeInstance, HierarchyChangedSignalType> HierarchyChangedSignalProxy;
	static const HierarchyChangedSignalType hierarchy_changed_signal;
	///< Hierarchy changed signal (see signal_hierarchy_changed()). Calls a slot with the signature:
	///< @code
	///< void function(Widget *previous_toplevel);
	///< // previous_toplevel: The previous toplevel widget.
	///< @endcode

	typedef G::Signal<void, Style*> StyleSetSignalType;
	typedef G::SignalProxy<TypeInstance, StyleSetSignalType> StyleSetSignalProxy;
	static const StyleSetSignalType style_set_signal;
	///< Style set signal (see signal_style_set()). Calls a slot with the signature:
	///< @code
	///< void function(Style* previous_style);
	///< // previous_style: The previous Style, or null.
	///< @endcode

	typedef G::Signal<void, TextDirection> DirectionChangedSignalType;
	typedef G::SignalProxy<TypeInstance, DirectionChangedSignalType> DirectionChangedSignalProxy;
	static const DirectionChangedSignalType direction_changed_signal;
	///< Direction changed signal (see signal_direction_changed()). Calls a slot with the signature:
	///< @code
	///< void function(TextDirection  previous_direction);
	///< // previous_direction: The previous direction.
	///< @endcode

	typedef G::Signal<void, bool> GrabNotifySignalType;
	typedef G::SignalProxy<TypeInstance, GrabNotifySignalType> GrabNotifySignalProxy;
	static const GrabNotifySignalType grab_notify_signal;
	///< Grab notify signal (see signal_grab_notify()). Calls a slot with the signature:
	///< @code
	///< void function(bool was_grabbed);
	///< // was_grabbed: true if the widget is the current grabbed widget, false
	///< //              if it was but is no longer the current grabbed widget.
	///< @endcode

	typedef G::Signal<void, GParamSpec*> ChildNotifySignalType;
	typedef G::SignalProxy<TypeInstance, ChildNotifySignalType> ChildNotifySignalProxy;
	static const ChildNotifySignalType child_notify_signal;
	///< Child notify signal (see signal_child_notify()). Calls a slot with the signature:
	///< @code
	///< void function(GParamSpec *pspec);
	///< // pspec: A GParamSpec object that holds the meta data specifying the new property.
	///< @endcode

	typedef G::Signal<bool, bool> MnemonicActivateSignalType;
	typedef G::SignalProxy<TypeInstance, MnemonicActivateSignalType> MnemonicActivateSignalProxy;
	static const MnemonicActivateSignalType mnemonic_activate_signal;
	///< Mnemonic activate signal (see signal_mnemonic_activate()). Calls a slot with the signature:
	///< @code
	///< bool function(bool group_cycling);
	///< // group_cycling:
	///< @endcode

	typedef G::Signal<void> GrabFocusSignalType;
	typedef G::SignalProxy<TypeInstance, GrabFocusSignalType> GrabFocusSignalProxy;
	static const GrabFocusSignalType grab_focus_signal;
	///< Grab focus signal (see signal_grab_focus()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<bool, DirectionType> FocusSignalType;
	typedef G::SignalProxy<TypeInstance, FocusSignalType> FocusSignalProxy;
	static const FocusSignalType focus_signal;
	///< Focus signal (see signal_focus()). Calls a slot with the signature:
	///< @code
	///< bool function(DirectionType direction);
	///< // direction: The direction of focus movement.
	///< // return: true if the focus ended up inside the child widget.
	///< @endcode

	typedef G::Signal<void> AccelClosuresChangedSignalType;
	typedef G::SignalProxy<TypeInstance, AccelClosuresChangedSignalType> AccelClosuresChangedSignalProxy;
	static const AccelClosuresChangedSignalType accel_closures_changed_signal;
	///< Accel closures changed signal (see signal_accel_closures_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, Gdk::Screen*> ScreenChangedSignalType;
	typedef G::SignalProxy<TypeInstance, ScreenChangedSignalType> ScreenChangedSignalProxy;
	static const ScreenChangedSignalType screen_changed_signal;
	///< Screen changed signal (see signal_screen_changed()). Calls a slot with the signature:
	///< @code
	///< void function(Gdk::Screen *previous_screen);
	///< // previous_screen: The previous Gdk:Screen.
	///< @endcode

	typedef G::Signal<bool, unsigned int> CanActivateAccelSignalType;
	typedef G::SignalProxy<TypeInstance, CanActivateAccelSignalType> CanActivateAccelSignalProxy;
	static const CanActivateAccelSignalType can_activate_accel_signal;
	///< Can activate accel signal (see signal_can_activate_accel()). Calls a slot with the signature:
	///< @code
	///< bool function(unsigned int signal_id);
	///< // signal_id: The id of a signal installed on the widget.
	///< // return: true if the accelerator can be activated.
	///< @endcode

/// @}
/// @name Selection Signal Prototypes
/// @{

	typedef G::Signal<void, SelectionData&, unsigned int, unsigned int> SelectionGetSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionGetSignalType> SelectionGetSignalProxy;
	static const SelectionGetSignalType selection_get_signal;
	///< Selection get signal (see signal_selection_get()). Calls a slot with the signature:
	///< @code
	///< void function(SelectionData& selection_data, unsigned int info, unsigned int time);
	///< // selection_data: The SelectionData object to be filled in.
	///< // info: The info integer that was set when the target was registered (see TargetEntry).
	///< // time: The time of the conversion request as set by the requestor with selectionn_convert().
	///< @endcode

	typedef G::Signal<void, const SelectionData&, unsigned int> SelectionReceivedSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionReceivedSignalType> SelectionReceivedSignalProxy;
	static const SelectionReceivedSignalType selection_received_signal;
	///< Selection received signal (see signal_selection_received()). Calls a slot with the signature:
	///< @code
	///< void function(const SelectionData& selection_data, unsigned int time);
	///< // selection_data: The requested selection data.
	///< // time: The time of the conversion request.
	///< @endcode
	
/// @}
/// @name Drag Source-side Signal Prototypes
/// @{

	typedef G::Signal<void, DragContext&> DragBeginSignalType;
	typedef G::SignalProxy<TypeInstance, DragBeginSignalType> DragBeginSignalProxy;
	static const DragBeginSignalType drag_begin_signal;
	///< Drag begin signal (see signal_drag_begin()). Calls a slot with the signature:
	///< @code
	///< void function(DragContext& context);
	///< // context: A reference to a Gtk::DragContext (only used by GTK+).
	///< @endcode

	typedef G::Signal<void, DragContext&> DragEndSignalType;
	typedef G::SignalProxy<TypeInstance, DragEndSignalType> DragEndSignalProxy;
	static const DragEndSignalType drag_end_signal;
	///< Drag end signal (see signal_drag_end()). Calls a slot with the signature:
	///< @code
	///< void function(DragContext& context);
	///< // context: A reference to a Gtk::DragContext (only used by GTK+).
	///< @endcode

	typedef G::Signal<void, DragContext&, SelectionData&, unsigned int, unsigned int> DragDataGetSignalType;
	typedef G::SignalProxy<TypeInstance, DragDataGetSignalType> DragDataGetSignalProxy;
	static const DragDataGetSignalType drag_data_get_signal;
	///< Drag data get signal (see signal_drag_data_get()). Calls a slot with the signature:
	///< @code
	///< void function(DragContext& context, SelectionData& data, unsigned int info, unsigned int time);
	///< // context: A reference to a Gtk::DragContext (only used by GTK+).
	///< // data: The SelectionData that needs to be filled in to provide the requested data.
	///< // info: The info integer that was set when the target was registered (see TargertEntry).
	///< // time: The time of the conversion request.
	///< @endcode

	typedef G::Signal<void, DragContext&> DragDataDeleteSignalType;
	typedef G::SignalProxy<TypeInstance, DragDataDeleteSignalType> DragDataDeleteSignalProxy;
	static const DragDataDeleteSignalType drag_data_delete_signal;
	///< Drag data delete signal (see signal_drag_data_delete()). Calls a slot with the signature:
	///< @code
	///< void function(DragContext& context);
	///< // context: A reference to a Gtk::DragContext (only used by GTK+).
	///< @endcode
	
/// @}
/// @name Drag Target-side Signal Prototypes
/// @{

	typedef G::Signal<void, DragContext&, unsigned int> DragLeaveSignalType;
	typedef G::SignalProxy<TypeInstance, DragLeaveSignalType> DragLeaveSignalProxy;
	static const DragLeaveSignalType drag_leave_signal;
	///< Drag leave signal (see signal_drag_leave()). Calls a slot with the signature:
	///< @code
	///< void function(DragContext& context, unsigned int time);
	///< // context: A reference to the Gtk::DragContext for the current drag-and-drop event.
	///< // time: The timestamp of the motion event.
	///< @endcode

	typedef G::Signal<bool, DragContext&, int, int, unsigned int> DragMotionSignalType;
	typedef G::SignalProxy<TypeInstance, DragMotionSignalType> DragMotionSignalProxy;
	static const DragMotionSignalType drag_motion_signal;
	///< Drag motion signal (see signal_drag_motion()). Calls a slot with the signature:
	///< @code
	///< bool function(DragContext& context, int x, int y, unsigned int time);
	///< // context: A reference to the Gtk::DragContext for the current drag-and-drop event.
	///< // x: The X position of the mouse pointer relative to the widget.
	///< // y: The Y position of the mouse pointer relative to the widget.
	///< // time: The time when the event occurred.
	///< // return: true if the widget is a valid drag-and-drop destination.
	///< @endcode

	typedef G::Signal<bool, DragContext&, int, int, unsigned int> DragDropSignalType;
	typedef G::SignalProxy<TypeInstance, DragDropSignalType> DragDropSignalProxy;
	static const DragDropSignalType drag_drop_signal;
	///< Drag drop signal (see signal_drag_drop()). Calls a slot with the signature:
	///< @code
	///< bool function(DragContext& context, int x, int y, unsigned int time);
	///< // context: A reference to the Gtk::DragContext for the current drag-and-drop event.
	///< // x: The X position of the mouse pointer relative to the widget.
	///< // y: The Y position of the mouse pointer relative to the widget.
	///< // time: The time when the event occurred.
	///< // return: true if the widget is a valid drag-and-drop destination.
	///< @endcode

	typedef G::Signal<void, DragContext&, int, int, const SelectionData&, unsigned int, unsigned int> DragDataReceivedSignalType;
	typedef G::SignalProxy<TypeInstance, DragDataReceivedSignalType> DragDataReceivedSignalProxy;
	static const DragDataReceivedSignalType drag_data_received_signal;
	///< Drag data received signal (see signal_drag_data_received()). Calls a slot with the signature:
	///< @code
	///< void function(DragContext& context, int x, int y, const SelectionData& data, unsigned int info, unsigned int time);
	///< // context: A reference to a Gtk::DragContext.
	///< // x: The X position of the mouse pointer relative to the widget. 
	///< // y: The Y position of the mouse pointer relative to the widget. 
	///< // data: The SelectionData that contains all the information about the data received.
	///< // info: The info integer that was set when the target was registered (see TargertEntry).
	///< // time: The time of the conversion request.
	///< @endcode
	
/// @}
/// @name GDK Event Signal Prototypes
/// @{

	typedef G::Signal<bool, const Gdk::Event&> EventSignalType;
	typedef G::SignalProxy<TypeInstance, EventSignalType> EventSignalProxy;
	static const EventSignalType event_signal;
	///< Event signal (see signal_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::Event& event);
	///< // event: The Gdk::Event.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<void, const Gdk::Event&> EventAfterSignalType;
	typedef G::SignalProxy<TypeInstance, EventAfterSignalType> EventAfterSignalProxy;
	static const EventAfterSignalType event_after_signal;
	///< Event after signal (see signal_event_after()). Calls a slot with the signature:
	///< @code
	///< void function(const Gdk::Event& event);
	///< // event: The Gdk::Event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventButton&> ButtonPressEventSignalType;
	typedef G::SignalProxy<TypeInstance, ButtonPressEventSignalType> ButtonPressEventSignalProxy;
	static const ButtonPressEventSignalType button_press_event_signal;
	///< Button press event signal (see signal_button_press_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventButton& event);
	///< // event: The Gdk::EventButton.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventButton&> ButtonReleaseEventSignalType;
	typedef G::SignalProxy<TypeInstance, ButtonReleaseEventSignalType> ButtonReleaseEventSignalProxy;
	static const ButtonReleaseEventSignalType button_release_event_signal;
	///< Button release event signal (see signal_button_release_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventButton& event);
	///< // event: The Gdk::EventButton.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventScroll&> ScrollEventSignalType;
	typedef G::SignalProxy<TypeInstance, ScrollEventSignalType> ScrollEventSignalProxy;
	static const ScrollEventSignalType scroll_event_signal;
	///< Scroll event signal (see signal_scroll_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventScroll& event);
	///< // event: The Gdk::EventScroll.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventMotion&> MotionNotifyEventSignalType;
	typedef G::SignalProxy<TypeInstance, MotionNotifyEventSignalType> MotionNotifyEventSignalProxy;
	static const MotionNotifyEventSignalType motion_notify_event_signal;
	///< Motion notify event signal (see signal_motion_notify_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventMotion& event);
	///< // event: The Gdk::EventMotion.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventAny&> DeleteEventSignalType;
	typedef G::SignalProxy<TypeInstance, DeleteEventSignalType> DeleteEventSignalProxy;
	static const DeleteEventSignalType delete_event_signal;
	///< Delete event signal (see signal_delete_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventAny& event);
	///< // event: The Gdk::Event.
	///< // return: false to allow the application window to close.
	///< @endcode
	
	typedef G::Signal<bool, const Gdk::EventAny&> DestroyEventSignalType;
	typedef G::SignalProxy<TypeInstance, DestroyEventSignalType> DestroyEventSignalProxy;
	static const DestroyEventSignalType destroy_event_signal;
	///< Destroy event signal (see signal_destroy_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventAny& event);
	///< // event: The Gdk::EventAny.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventExpose&> ExposeEventSignalType;
	typedef G::SignalProxy<TypeInstance, ExposeEventSignalType> ExposeEventSignalProxy;
	static const ExposeEventSignalType expose_event_signal;
	///< Expose event signal (see signal_expose_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventExpose& event);
	///< // event: The Gdk::EventExpose.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventKey&> KeyPressEventSignalType;
	typedef G::SignalProxy<TypeInstance, KeyPressEventSignalType> KeyPressEventSignalProxy;
	static const KeyPressEventSignalType key_press_event_signal;
	///< Key press event signal (see signal_key_press_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventKey& event);
	///< // event: The Gdk::EventKey.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventKey&> KeyReleaseEventSignalType;
	typedef G::SignalProxy<TypeInstance, KeyReleaseEventSignalType> KeyReleaseEventSignalProxy;
	static const KeyReleaseEventSignalType key_release_event_signal;
	///< Key release event signal (see signal_key_release_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventKey& event);
	///< // event: The Gdk::EventKey.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventCrossing&> EnterNotifyEventSignalType;
	typedef G::SignalProxy<TypeInstance, EnterNotifyEventSignalType> EnterNotifyEventSignalProxy;
	static const EnterNotifyEventSignalType enter_notify_event_signal;
	///< Enter notify event signal (see signal_enter_notify_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventCrossing& event);
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventCrossing&> LeaveNotifyEventSignalType;
	typedef G::SignalProxy<TypeInstance, LeaveNotifyEventSignalType> LeaveNotifyEventSignalProxy;
	static const LeaveNotifyEventSignalType leave_notify_event_signal;
	///< Leave notify event signal (see signal_leave_notify_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventCrossing& event);
	///< // event: The Gdk::EventCrossing.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventConfigure&> ConfigureEventSignalType;
	typedef G::SignalProxy<TypeInstance, ConfigureEventSignalType> ConfigureEventSignalProxy;
	static const ConfigureEventSignalType configure_event_signal;
	///< Configure event signal (see signal_configure_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventConfigure& event);
	///< // event: The Gdk::EventConfigure.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventFocus&> FocusInEventSignalType;
	typedef G::SignalProxy<TypeInstance, FocusInEventSignalType> FocusInEventSignalProxy;
	static const FocusInEventSignalType focus_in_event_signal;
	///< Focus in event signal (see signal_focus_in_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventFocus& event);
	///< // event: The Gdk::EventFocus.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventFocus&> FocusOutEventSignalType;
	typedef G::SignalProxy<TypeInstance, FocusOutEventSignalType> FocusOutEventSignalProxy;
	static const FocusOutEventSignalType focus_out_event_signal;
	///< Focus out event signal (see signal_focus_out_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventFocus& event);
	///< // event: The Gdk::EventFocus.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventAny&> MapEventSignalType;
	typedef G::SignalProxy<TypeInstance, MapEventSignalType> MapEventSignalProxy;
	static const MapEventSignalType map_event_signal;
	///< Map event signal (see signal_map_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventAny& event);
	///< // event: The Gdk::EventAny.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventAny&> UnmapEventSignalType;
	typedef G::SignalProxy<TypeInstance, UnmapEventSignalType> UnmapEventSignalProxy;
	static const UnmapEventSignalType unmap_event_signal;
	///< Unmap event signal (see signal_unmap_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventAny& event);
	///< // event: The Gdk::EventAny.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventProperty&> PropertyNotifyEventSignalType;
	typedef G::SignalProxy<TypeInstance, PropertyNotifyEventSignalType> PropertyNotifyEventSignalProxy;
	static const PropertyNotifyEventSignalType property_notify_event_signal;
	///< Property notify event signal (see signal_property_notify_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventProperty& event);
	///< // event: The Gdk::EventProperty.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventSelection&> SelectionClearEventSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionClearEventSignalType> SelectionClearEventSignalProxy;
	static const SelectionClearEventSignalType selection_clear_event_signal;
	///< Selection clear event signal (see signal_selection_clear_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventSelection& event);
	///< // event: The Gdk::EventSelection.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventSelection&> SelectionRequestEventSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionRequestEventSignalType> SelectionRequestEventSignalProxy;
	static const SelectionRequestEventSignalType selection_request_event_signal;
	///< Selection request event signal (see signal_selection_request_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventSelection& event);
	///< // event: The Gdk::EventSelection.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventSelection&> SelectionNotifyEventSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionNotifyEventSignalType> SelectionNotifyEventSignalProxy;
	static const SelectionNotifyEventSignalType selection_notify_event_signal;
	///< Selection notify event signal (see signal_selection_notify_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventSelection& event);
	///< // event: The Gdk::EventSelection.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventProximity&> ProximityInEventSignalType;
	typedef G::SignalProxy<TypeInstance, ProximityInEventSignalType> ProximityInEventSignalProxy;
	static const ProximityInEventSignalType proximity_in_event_signal;
	///< Proximity in event signal (see signal_proximity_in_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventProximity& event);
	///< // event: The Gdk::EventProximity.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventProximity&> ProximityOutEventSignalType;
	typedef G::SignalProxy<TypeInstance, ProximityOutEventSignalType> ProximityOutEventSignalProxy;
	static const ProximityOutEventSignalType proximity_out_event_signal;
	///< Proximity out event signal (see signal_proximity_out_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventProximity& event);
	///< // event: The Gdk::EventProximity.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventVisibility&> VisibilityNotifyEventSignalType;
	typedef G::SignalProxy<TypeInstance, VisibilityNotifyEventSignalType> VisibilityNotifyEventSignalProxy;
	static const VisibilityNotifyEventSignalType visibility_notify_event_signal;
	///< Visibility notify event signal (see signal_visibility_notify_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventVisibility& event);
	///< // event: The Gdk::EventVisibility.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventClient&> ClientEventSignalType;
	typedef G::SignalProxy<TypeInstance, ClientEventSignalType> ClientEventSignalProxy;
	static const ClientEventSignalType client_event_signal;
	///< Client event signal (see signal_client_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventClient& event);
	///< // event: The Gdk::EventClient.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventAny&> NoExposeEventSignalType;
	typedef G::SignalProxy<TypeInstance, NoExposeEventSignalType> NoExposeEventSignalProxy;
	static const NoExposeEventSignalType no_expose_event_signal;
	///< No expose event signal (see signal_no_expose_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventAny& event);
	///< // event: The Gdk::EventAny.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode

	typedef G::Signal<bool, const Gdk::EventWindowState&> WindowStateEventSignalType;
	typedef G::SignalProxy<TypeInstance, WindowStateEventSignalType> WindowStateEventSignalProxy;
	static const WindowStateEventSignalType window_state_event_signal;
	///< Window state event signal (see signal_window_state_event()). Calls a slot with the signature:
	///< @code
	///< bool function(const Gdk::EventWindowState& event);
	///< // event: The Gdk::EventWindowState.
	///< // return: true to stop invoking other handlers, false to propagate the event.
	///< @endcode
	
/// @}

public:
	typedef GtkWidget CObjectType;

/// @name Constructors
/// @{

	virtual ~Widget();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkWidget* gtk_widget() const;
	///< Get a pointer to the GtkWidget structure.

	operator GtkWidget* () const;
	///< Conversion operator; safely converts a Widget to a GtkWidget pointer.

	bool is_toplevel() const;
	///< Returns true if the widget is a toplevel widget.

	bool has_no_window() const;
	///< Returns true if the widget doesn't have it's own Gdk::Window.

	bool is_realized() const;
	///< Returns true if the widget is realized.

	bool is_mapped() const;
	///< Returns true if the widget is mapped.

	bool is_visible() const;
	///< Returns true if the widget is visible.

	bool is_drawable() const;
	///< Returns true if the widget is mapped and visible.

	bool sensitive() const;
	///< Returns true if the Gtk::SENSITIVE flag has be set on the widget.

	bool parent_sensitive() const;
	///< Returns true if the Gtk::PARENT_SENSITIVE flag has be set on the widget.

	bool is_sensitive() const;
	///< Returns true if the widget is effectively sensitive.

	bool can_focus() const;
	///< Returns true if the widget is able to handle focus grabs.

	bool has_focus() const;
	///< Returns true if the widget has grabbed the focus and no other widget has done so more recently.

	bool can_default() const;
	///< Returns true if the widget is allowed to receive the default action via grab_default().

	bool has_default() const;
	///< Returns true if the widget currently is receiving the default action.
	
	bool has_grab() const;
	///< Returns true if the widget is in the grab_widgets stack, and will be the preferred one
	///< for receiving events other than ones of cosmetic value.

	bool has_rc_style() const;
	///< Returns true if the widgets style has been looked up through the rc mechanism.

	bool is_composite_child() const;
	///< Returns true if the widget is a composite child of its parent.

	bool is_app_paintable() const;
	///< Returns true if the Gtk::APP_PAINTABLE flag has been set on the widget.

	bool receives_default() const;
	///< Returns true if the widget when focused will receive the default action even if
	///< there is a different widget set as default.

	bool is_double_buffered() const;
	///< Returns true if the Gtk::DOUBLE_BUFFERED flag has been set on the widget.

	bool get_no_show_all() const;
	///< Returns the current value of the "no_show_all" property, which determines
	///< whether calls to show_all() and hide_all() will affect this widget.
	///< @return The current value of the "no_show_all" property.

	StateType get_state() const;
	///< Returns the current state of the widget.

	const Allocation& get_allocation() const;
	///< Returns the size allocated to the widget.

	Requisition get_child_requisition() const;
	///< Obtains the child widget requisition (see get_child_requisition(Requisition&) const).
	///< @return A Requisition that holds the child widget's width and height.
	
	void get_child_requisition(Requisition& requisition) const;
	///< Obtains the child widget requisition, unless someone has forced a particular geometry on the widget, 
	///< in which case it returns that geometry instead of the widget's requisition.
	///< @param requisition The Requisition to be filled in.
	///<
	///< This method is only for use in widget implementations. It differs from size_request()
	///< in that it retrieves the last size request value from gtk_widget()->requisition, while
	///< size_request() actually calls the "size_request" method on the widget to compute the size
	///< request and fill in gtk_widget()->requisition, and only then returns gtk_widget()->requisition.
	///< Because this method does not call the "size_request" method, it can only be used when you
	///< know that gtk_widget()->requisition is up-to-date, that is, size_request() has been called
	///< since the last time a resize was queued. In general, only container implementations have
	///< this information; applications should use size_request().
	
	Gdk::Window* get_window() const;
	///< Returns the widget's window or its parent window if it doesn't have a window 
	///< (which will be indicated by the Gtk::NO_WINDOW flag being set).

	bool is_focus() const;
	///< Determines if the widget is the focus widget within its toplevel. 
	///< @return <EM>true</EM> if the widget is the focus widget.
	///<
	///< This does not mean that the HAS_FOCUS flag is necessarily set; HAS_FOCUS will
	///< only be set if the toplevel widget additionally has the global input focus.

	String get_name() const;
	///< Retrieves the name of the widget (see set_name() for the significance of widget names).
	///< @return The name of the widget.
	
	bool get_child_visible() const;
	///< Returns the value set with set_child_visible(). 
	///< @return <EM>true</EM> if the widget is mapped with the parent.
	///<
	///< If you feel a need to use this method, your code probably needs reorganization.
	///< This method is only useful for container implementations and never should be called by an application.

	Widget* get_parent() const;
	///< Returns the parent container of widget, or null.
	
	Gdk::Window* get_parent_window() const;
	///< Returns the widget's parent window.
	
	void get_size_request(int *width, int *height) const;
	///< Gets the size request that was explicitly set for the widget using set_size_request().
	///< @param width The return location for the width, or null.
	///< @param height The return location for the height, or null.
	///<
	///< A value of -1 stored in <EM>width</EM> or <EM>height</EM> indicates that that
	///< dimension has not been set explicitly and the natural requisition of the widget
	///< will be used intead. See set_size_request(). To get the size a widget will actually
	///< use, call size_request() instead of this method.

	Gdk::ExtensionMode get_extension_events() const;
	///< Retrieves the extension events the widget will receive (see Gdk::Input::set_extension_events()).
	
	Widget* get_toplevel() const;
	///< This method returns the topmost widget in the container hierarchy the widget is a part of.
	///< @return The topmost ancestor of widget, or widget itself if there's no ancestor.
	///<
	///< If widget has no parent widgets, it will be returned as the topmost widget. No reference
	///< will be added to the returned widget; it should not be unreferenced. Note the difference in
	///< behavior vs get_ancestor(); get_ancestor(Gtk::TYPE_WINDOW) would return null if widget wasn't
	///< inside a toplevel window, and if the window was inside a Gtk::Window-derived widget which was
	///< in turn inside the toplevel Gtk::Window. While the second case may seem unlikely, it actually
	///< happens when a Plug is embedded inside a Socket within the same application.
	///<
	///< To reliably find the toplevel Gtk::Window, use get_toplevel() and check is_top_level() on the result.
	///< @code
	///< Gtk::Widget *toplevel = widget->get_toplevel();
	///< if (is_toplevel())
	///< {
	///< 	// Perform action on toplevel.
	///< }
	///< @endcode

	Widget* get_ancestor(GType widget_type) const;
	///< Gets the first ancestor of widget with type widget_type. 
	///< @param widget_type The ancestor type.
	///< @return The ancestor widget, or null if not found.
	///<
	///< For example, get_ancestor(GTK_TYPE_BOX) gets the first Box that's an ancestor of the widget.
	///< No reference will be added to the returned widget; it should not be unreferenced. See note about
	///< checking for a toplevel Gtk::Window in the docs for get_toplevel().

	Gdk::Colormap* get_colormap() const;
	///< Returns the colormap that will be used to render the widget. No reference 
	///< will be added to the returned colormap; it should not be unreferenced.
	
	const Gdk::Visual* get_visual() const;
	///< Returns the visual that will be used to render widget.

	Gdk::Screen* get_screen() const;
	///< Get the Gdk::Screen from the toplevel window associated with this widget.
	///< @return The Gdk::Screen for the toplevel for this widget.
	///<
	///< This function can only be called after the widget has been added to a widget
	///< hierarchy with a Gtk::Window at the top. In general, you should only create screen
	///< specific resources when a widget has been realized, and you should free those
	///< resources when the widget is unrealized.

	bool has_screen() const;
	///< Checks whether there is a Gdk::Screen is associated with this widget.
	///< @returns <EM>true</EM> if there is a Gdk::Screen associcated with the widget.
	///<
	///< All toplevel widgets have an associated screen, as do all widgets added into a
	///< heirarchy with a toplevel window at the top.

	Gdk::Display* get_display() const;
	///< Get the Gdk::Display for the toplevel window associated with this widget. 
	///< @return The Gdk::Display for the toplevel for this widget.
	///<
	///< This method can only be called after the widget has been added to a widget
	///< hierarchy with a Gtk::Window at the top. In general, you should only create
	///< display specific resources when a widget has been realized, and you should free
	///< those resources when the widget is unrealized.

	Gdk::Window* get_root_window() const;
	///< The root window is useful for such purposes as creating a popup Gdk::Window
	///< associated with the window. 
	///< @return The Gdk::Window root window for the toplevel for this widget.
	///<
	///< In general, you should only create display specific resources when a widget
	///< has been realized, and you should free those resources when the widget is
	///< unrealized.

	Settings* get_settings() const;
	///< Gets the settings object holding the settings (global property settings,
	///< RC file information, etc) used for this widget.
	///< @return The relevant Settings object.
	///<
	///< Note that this method can only be called when the Widget is attached to a
	///< toplevel, since the settings object is specific to a particular Gdk::Screen.

	Clipboard* get_clipboard(Gdk::Atom selection = GDK_SELECTION_CLIPBOARD) const;
	///< Returns the clipboard object for the given selection to be used with widget.
	///< @param selection A Gdk::Atom which identifies the clipboard to use.
	///< @return The appropriate clipboard object.
	///<
	///< The widget must have a Gdk::Display associated with it, and so must be attached
	///< to a toplevel window. GDK_SELECTION_CLIPBOARD gives the default clipboard. Another
	///< common value is GDK_SELECTION_PRIMARY, which gives the primary X selection. If no
	///< clipboard already exists, a new one will be created. Once a clipboard object has
	///< been created, it is persistent for all time. All clipboard objects are owned by
	///< GTK+ and will be freed when GTK+ is removed from memory.

	Atk::Object* get_accessible() const;
	///< Returns an accessible object for this widget.

	Gdk::EventMaskField get_events() const;
	///< Gets the event mask for the widget (a bitfield containing flags from the Gdk::EventMask enumeration).
	///< @return The event mask for the widget.
	///<
	///< These are the events that the widget will receive.
	
	void get_pointer(int *x, int *y) const;
	///< Obtains the location of the mouse pointer in widget coordinates.
	///< @param x The return location for the X coordinate, or null.
	///< @param y The return location for the Y coordinate, or null.
	///<
	///< Widget coordinates are a bit odd; for historical reasons, they are defined as
	///< Gdk::Window coordinates for widgets that are not Gtk::NO_WINDOW widgets, and are
	///< relative to get_allocation().x and get_allocation().y for widgets that are
	///< Gtk::NO_WINDOW widgets.

	Gdk::Point get_pointer() const;
	///< Obtains the location of the mouse pointer in widget coordinates.
	///< @return The widget coordinates stored in a Gdk::Point.
	///<
	///< Widget coordinates are a bit odd; for historical reasons, they are defined as
	///< Gdk::Window coordinates for widgets that are not Gtk::NO_WINDOW widgets, and are
	///< relative to get_allocation().x and get_allocation().y for widgets that are
	///< Gtk::NO_WINDOW widgets.

	bool is_ancestor(Widget *ancestor) const;
	///< Determines whether the widget is somewhere inside <EM>ancestor</EM>,
	///< possibly within an intermediate container.
	///< @param ancestor Another Widget.
	///< @return <EM>true</EM> if ancestor contains the widget as a child, grandchild, great grandchild, etc.

	Style* get_style() const;
	///< Returns the widget Style (see set_style().

	Style* rc_get_style() const;
	///< Finds all matching RC styles for a given widget, composites them together, 
	///< and then creates a Style representing the composite appearance. 
	///< @return The resulting style. No refcount is added to the returned style,
	///< so if you want to keep this style around, you should add a reference yourself.
	///<
	///< GTK+ actually keeps a cache of previously created styles, so a new style may not be created.

	RcStyle* get_modifier_style() const;
	///< Returns the current modifier style for the widget (as set by modify_style()).
	///< If no style has previously set, a new RcStyle will be created with all values
	///< unset, and set as the modifier style for the widget. If you make changes to
	///< this rc style, you must call modify_style(), passing in the returned rc style,
	///< to make sure that your changes take effect.
	///<
	///< <B>Caution:</B> passing the style back to modify_style() will normally end up 
	///< destroying it, because modify_style() copies the passed-in style and sets the
	///< copy as the new modifier style, thus dropping any reference to the old modifier
	///< style. Add a reference to the modifier style if you want to keep it alive.

	String get_composite_name() const;
	///< Returns the composite name of the widget or a null String if the widget
	///<  is not a composite child. 

	Pango::Context* get_pango_context() const;
	///< Returns a Pango::Context with the appropriate colormap, font description and base
	///< direction for the widget. Unlike the context returned by create_pango_context(),
	///< this context is owned by the widget (it can be used as long as widget exists), and
	///< will be updated to match any changes to the widget's attributes.
	///<
	///< If you create and keep a Pango::Layout using this context, you must deal with 
	///< changes to the context by calling Pango::Layout::context_changed() on the layout in
	///< response to the <EM>style_set</EM> and <EM>direction_set</EM> signals for the widget.

	TextDirection get_direction() const;
	///< Returns the reading direction for the widget (see set_direction()).

	void style_get_property(const char *property_name, G::Value& value);
	void style_get_property(const String& property_name, G::Value& value);
	///< Gets the value of a style property of the widget.
	///< @param property_name The name of a style property.
	///< @param value The location to return the property value.

	void path(String& path, String& path_reversed) const;
	///< Obtains the full path to the widget.
	///< @param path The location to store the path string, or null.
	///< @param path_reversed The location to store path string, or null.
	///<
	///< The path is simply the name of a widget and all its parents in the container hierarchy,
	///< separated by periods. The name of a widget comes from get_name(). Paths are used to apply
	///< styles to a widget in gtkrc configuration files. Widget names are the type of the widget
	///< by default (e.g. "Button") or can be set to an application-specific value with set_name().
	///< By setting the name of a widget, you allow users or theme authors to apply styles to that
	///< specific widget in their gtkrc file. <EM>path_reversed</EM> fills in the path in reverse
	///< order, i.e. starting with widget's name instead of starting with the name of widget's
	///< outermost ancestor.

	void class_path(String& path, String& path_reversed) const;
	///< Same as path(), but always uses the name of a widget's type,
	///< never uses a custom name set with set_name().
	///< @param path The location to store the path string, or null.
	///< @param path_reversed The location to store path string, or null.

/// @}
/// @name Accessors
/// @{

	static const Style* get_default_style();
	///< Returns the default style used by all widgets initially.
	///< @return The default style. This Style object is owned by GTK+ and should
	///< not be modified or unreferenced.

	static Gdk::Colormap* get_default_colormap();
	///< Returns the default colormap used to create widgets.

	static const Gdk::Visual* get_default_visual();
	///< Returns the visual of the default colormap. Not really useful; used to be useful
	///< before Gdk::Colormap::get_visual() existed.

	static TextDirection get_default_direction();
	///< Returns the current default reading direction (see set_default_direction()).

/// @}	
/// @name Methods
/// @{

	void set_flags(WidgetFlagsField flags);
	///< Turns on certain widget flags.
	///< @param flags The Gtk::WidgetFlags to set.

	void unset_flags(WidgetFlagsField flags);
	///< Turns off certain widget flags.
	///< @param flags The Gtk::WidgetFlags to unset.

	void unparent();
	///< Used in widget implementations; should be called by implementations of the
	///< remove method on Gtk::Container, to dissociate a child from the container.

	void show();
	///< Flags a widget to be displayed. Any widget that isn't shown will not appear on the screen.
	///< If you want to show all the widgets in a container, it's easier to call widget_show_all()
	///< on the container, instead of individually showing the widgets. 
	///<
	///< Remember that you have to show the container containing a widget, in addition to the
	///< widget itself, before it will appear onscreen. When a toplevel container is shown, it
	///< is immediately realized and mapped; other shown widgets are realized and mapped when
	///< their toplevel container is realized and mapped.

	void show(bool visible);
	///< Convenience method that combines the functionality of show() and hide().
	///< @param visible Set <EM>true</EM> to show the widget, or <EM>false</EM> to hide it.
	///<
	///< This method is useful when you want to use another boolean value to toggle
	///< the visibility of this widget.
	
	void hide();
	///< Reverses the effects of show(), causing the widget to be hidden (invisible to the user).

	void show_now();
	///< Shows a widget. If the widget is an unmapped toplevel widget (i.e. a Gtk::Window that
	///< has not yet been shown), enter the main loop and wait for the window to actually be
	///< mapped. Be careful; because the main loop is running, anything can happen during this
	///< method.

	void show_all();
	///< Recursively shows a widget, and any child widgets (if the widget is a container).

	void hide_all();
	///< Recursively hides a widget and any child widgets.

	void set_no_show_all(bool no_show_all);
	///< Sets the "no_show_all" property, which determines whether calls to show_all() and
	///< hide_all() will affect this widget.
	///< @param no_show_all The new value for the "no_show_all" property.
	///<
	///< This is mostly for use in constructing widget hierarchies with externally
	///< controlled visibility, see Gtk::UIManager.

	void map();
	///< Used in widget implementations; causes the widget to be mapped if it isn't already
	///< (visible on the screen).

	void unmap();
	///< Used in widget implementations; causes the widget to be unmapped if it's currently
	///< mapped (no longer visible on the screen).

	void realize();
	///< Creates the GDK (windowing system) resources associated with a widget. For example,
	///< a widget's GDK window will be created when a widget is realized. Normally realization
	///< happens implicitly; if you show a widget and all its parent containers, then the
	///< widget will be realized and mapped automatically. Realizing a widget requires all
	///< the widget's parent widgets to be realized. Calling realize() realizes the widget's
	///< parents in addition to widget itself. If a widget is not yet inside a toplevel 
	///< window when you realize it, bad things will happen.
	///<
	///< This method is primarily used in widget implementations, and isn't very useful
	///< otherwise. Many times when you think you might need it, a better approach is to
	///< connect to a signal that will be called after the widget is realized automatically,
	///< such as <EM>expose_event</EM> signal. Or simply connect to the <EM>realize</EM>
	///< signal specifying <EM>after</EM> as true in the signal's connect method.

	void unrealize();
	///< Used in widget implementations; causes a widget to be unrealized (frees all
	///< GDK resources associated with the widget, such as gtk_widget()->window).

	void queue_draw();
	///< Equivalent to calling queue_draw_area() for the entire area of a widget.

	void queue_draw_area(int x, int y, int width, int height);
	///< Invalidates the rectangular area of the widget defined by x, y, width and height by calling
	///< Gdk::Window::invalidate_rect() on the widget's window and all its child windows.
	///< @param x The X coordinate of upper-left corner of rectangle to redraw.
	///< @param y The Y coordinate of upper-left corner of rectangle to redraw
	///< @param width The width of region to draw.
	///< @param height The height of region to draw.
	///<
	///< Once the main loop becomes idle (after the current batch of events
	///< has been processed, roughly), the window will receive expose events for
	///< the union of all regions that have been invalidated.
	///<
	///< Normally you would only use this method in widget implementations. You 
	///< might also use it, or Gdk::Window::invalidate_rect() directly, to schedule
	///< a redraw of a DrawingArea or some portion thereof. Frequently you can just
	///< call Gdk::Window::invalidate_rect() or Gdk::Window::invalidate_region() 
	///< instead of this method. Those methods will invalidate only a single window,
	///< instead of the widget and all its children.
	///<
	///< The advantage of adding to the invalidated region compared to simply drawing
	///< immediately is efficiency; using an invalid region ensures that you only have
	///< to redraw one time.

	void queue_draw_area(const Gdk::Rectangle& rectangle);
	///< Invalidates the rectangular area of the widget defined by rectangle by calling
	///< Gdk::Window::invalidate_rect() on the widget's window and all its child windows.
	///< @param rectangle A rectangle that specifies the area of the widget to invalidate.

	void queue_resize();
	///< This method is only for use in widget implementations. Flags a widget to have its size
	///< renegotiated; should be called when a widget for some reason has a new size request.
	///< For example, when you change the text in a Label, Label queues a resize to ensure
	///< there's enough space for the new text.

	void queue_resize_no_redraw();
	///< This function works like queue_resize(), except that the widget is not invalidated.

	void size_request(Requisition *requisition);
	///< Typically used when implementing a Container subclass; obtains the preferred size of the widget.
	///< @param requisition A Requisition to be filled in.
	///<
	///<  The container uses this information to arrange
	///< its child widgets and decide what size allocations to give them with size_allocate().
	///<
	///< You can also call this function from an application, with some caveats. Most notably,
	///< getting a size request requires the widget to be associated with a screen, because font
	///< information may be needed. Multihead-aware applications should keep this in mind. Also
	///< remember that the size request is not necessarily the size a widget will actually be
	///< allocated. See also get_child_requisition().

	void size_allocate(const Allocation& allocation);
	///< This method is only used by Container subclasses to assign a size and position
	///< to their child widgets.
	///< @param allocation The position and size to be allocated to the widget.

	void add_accelerator(const char *accel_signal, AccelGroup& accel_group, const AccelKey& accel_key);
	void add_accelerator(const String& accel_signal, AccelGroup& accel_group, const AccelKey& accel_key);
	///< Installs an accelerator for this widget in accel_group that causes accel_signal
	///< to be emitted if the accelerator is activated.
	///< @param accel_signal The widget signal to emit on accelerator activation.
	///< @param accel_group The accelerator group for this widget, added to its toplevel.
	///< @param accel_key An AccelKey that holds the accelerator key, modifier and flag values.
	///<
	///< The accel_group needs to be added to the widget's toplevel via Gtk::Window::add_accel_group(),
	///< and the signal must be of type G_RUN_ACTION. Accelerators added through this function are not user
	///< changeable during runtime. If you want to support accelerators that can be changed by the user,
	///< use Gtk::AccelMap::add_entry() and set_accel_path() or Gtk::MenuItem::set_accel_path() instead.

	bool remove_accelerator(AccelGroup& accel_group, const AccelKey& accel_key);
	///< Removes an accelerator from the widget previously installed with add_accelerator().
	///< @param accel_group The accel group for this widget.
	///< @param accel_key An AccelKey that holds the accelerator key, modifier and flag values.
	///< @return Whether an accelerator was installed and could be removed.

	void set_accel_path(const char *accel_path, AccelGroup& accel_group);
	void set_accel_path(const String& accel_path, AccelGroup& accel_group);
	///< Given an accelerator group <EM>accel_group</EM> and an accelerator path <EM>accel_path</EM>,
	///< sets up an accelerator in accel_group so whenever the key binding that is defined for accel_path
	///< is pressed, the widget will be activated. 
	///< @param accel_path The path used to look up the the accelerator.
	///< @param accel_group The accelerator group.
	///<
	///< This removes any accelerators (for any accelerator group) installed by previous calls
	///< to set_accel_path(). Associating accelerators with paths allows them to be modified by the
	///< user and the modifications to be saved for future use. (See Gtk::AccelMap_save().)
	///<
	///< This method is a low level function that would most likely be used by a menu creation system
	///< like ItemFactory. If you use ItemFactory, setting up accelerator paths will be done automatically.
	///< Even when you you aren't using ItemFactory, if you only want to set up accelerators on menu items
	///< Gtk::MenuItem::set_accel_path() provides a somewhat more convenient interface.

	bool list_accel_closures(std::vector<GClosure*>& closures);
	///< Lists the closures used by the widget for accelerator group connections with
	///< Gtk::AccelGroup::connect(). /* T
	///< @param closures A reference to a vector of GClosure* to hold the list of closures.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< The closures can be used to monitor accelerator changes on the widget, by connecting
	///< to the <EM>accel_changed</EM> signal of the AccelGroup of a closure, which can be found out
	///< with Gtk::AccelGroup::from_accel_closure().

	bool can_activate_accel(unsigned int signal_id);
	///< Determines whether an accelerator that activates the signal identified by
	///< <EM>signal_id</EM> can currently be activated.
	///< @param signal_id The id of a signal installed on the widget.
	///< @return <EM>true</EM> if the accelerator can be activated.
	///<
	///< The determination is made by emitting the <EM>can_activate_accel</EM>
	///< signal on the widget. If the signal isn't overridden by a handler or in a
	///< derived widget, then the default check is that the widget must be sensitive,
	///< and the widget and all its parents mapped.

	bool can_activate_accel(const char *signal_name);
	bool can_activate_accel(const String& signal_name);
	///< Determines whether an accelerator that activates the signal identified by <EM>signal_name</EM>
	///< can currently be activated (see can_activate_accel(unsigned int)).
	///< @param signal_name The name of a signal installed on the widget.
	///< @return <EM>true</EM> if the accelerator can be activated.

	int send_expose(const Gdk::EventExpose& event);
	///< This rarely-used method is used to emit an <EM>expose_event</EM> signal on the widget.
	///< @param event A Gdk::GdkEventExpose.
	///< @return The return from the event signal emission (true if the event was handled).
	///<
	///< This method is not normally used directly. The only time it is used is when
	///< propagating an expose event to a child NO_WINDOW widget, and that is normally
	///< done using Gtk::Container::propagate_expose(). 
	///<
	///< If you want to force an area of a window to be redrawn, use Gdk::Window::invalidate_rect()
	///< or Gdk::Window::invalidate_region(). To cause the redraw to be done immediately, follow
	///< that call with a call to Gdk::Window::process_updates().

	bool mnemonic_activate(bool group_cycling);
	///< Actviates the widget if it's suitable for mnemonic actviaton.
	///< @param group_cycling
	///< @return <EM>true</EM> if the widget was activated.

	bool event(const Gdk::Event& event);
	///< This rarely-used method is used to emit the event signals on a widget (those signals
	///< should never be emitted without using this method to do so).
	///< @param event A Gdk::Event.
	///< @return The return from the event signal emission (true if the event was handled).
	///<
	///< If you want to synthesize an event though, don't use this function; instead,
	///< use gtk_main_do_event() so the event will behave as if it were in the event queue.
	///< Don't synthesize expose events; instead, use Gdk::Window::invalidate_rect() to
	///< invalidate a region of the window.

	bool activate();
	///< For widgets that can be activated (buttons, menu items, etc) this method activates them.
	///< @return <EM>true</EM> if the widget was activatable.
	///<
	///< Activation is what happens when you press <EM>Enter</EM> on a widget during key navigation;
	///< clicking a button, selecting a menu item, etc. If the widget isn't activatable, this method
	///< returns false.

	bool set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment);
	///< Sets the widget's scroll adjustments.
	///< @param hadjustment An adjustment for horizontal scrolling, or null.
	///< @param vadjustment An adjustment for vertical scrolling, or null.
	///< @return <EM>true</EM> if the widget supports scrolling.
	///<
	///< For widgets that support scrolling, sets the scroll adjustments and returns true.
	///< For widgets that don't support scrolling, does nothing and returns false. Widgets that
	///< don't support scrolling can be scrolled by placing them in a Viewport, which does 
	///< support scrolling.

	void reparent(Widget& new_parent);
	///< Moves a widget from one Container to another, handling reference count issues
	///< to avoid destroying the widget.
	///< @param new_parent A Container to move the widget into.

	bool intersect(const Gdk::Rectangle& area, Gdk::Rectangle *intersection);
	///< Computes the intersection of a widget's area and <EM>area</EM>, storing the intersection
	///< in <EM>intersection</EM>, and returns true if there was an intersection.
	///< @param area A rectangle.
	///< @param intersection The rectangle to store intersection of the widget and <EM>area</EM>.
	///< @return <EM>true</EM> if there was an intersection.
	///<
	///< The intersection may be null if you're only interested in whether there was an intersection.

	Gdk::Rectangle intersect(const Gdk::Rectangle& area);
	///< Computes the intersection of a widget's area and <EM>area</EM>, and returns
	///< the intersection as a rectanlge.
	///< that stores .
	///< @param area A rectangle.
	///< @return A rectangle storing the intersection if there was an intersection.
	///<
	///< The returned rectangle will be empty if there was no intersection.

	Pointer<Gdk::Region> intersect(Gdk::Region& region);
	///< Computes the intersection of a widget's area and <EM>region</EM>,
	///< and returns the intersection as a new Gdk::Region.
	///< @param region a Gdk::Region.
	///< @return A smart pointer to a new Gdk::Region holding the intersection of the widget and <EM>region</EM>.
	///<
	///< <EM>region</EM> must be in the same coordinate system as the widget's allocation.
	///< That is, relative to the widget's GDK window for NO_WINDOW widgets; relative to
	///< the parent window of widget's GDK window for widgets with their own window. The
	///< coordinates returned are relative to the widget's GDK window for NO_WINDOW widgets,
	///< and relative to the parent window of widget's GDK window for widgets with their
	///< own window. The returned region may be empty, use Gdk::Region::empty() to check.

	void freeze_child_notify();
	///< Stops the emission of <EM>child_notify</EM> signals on the widget. The signals are
	///< queued until thaw_child_notify() is called on the widget.

	void child_notify(const char *child_property);
	void child_notify(const String& child_property);
	///< Emits a <EM>child_notify</EM> signal for the child property <EM>child_property</EM> on the widget.
	///< @param child_property The name of a child property installed on the class of widget's parent.

	void thaw_child_notify();
	///< Reverts the effect of a prevoious call to freeze_child_notify(). This causes all queued
	///< <EM>child_notify</EM> signals on widget to be emitted.
	
	void grab_focus();
	///< Causes the widget to have the keyboard focus for the Window it's inside. The widget
	///< must be a focusable widget, such as an Entry; something like Frame won't work. More
	///< precisely, it must have the Gtk::CAN_FOCUS flag set.

	void grab_default();
	///< Causes the widget to become the default widget. The widget must have the Gtk::CAN_DEFAULT
	///< flag set; typically you have to set this flag yourself by calling set_flags(Gtk::CAN_DEFAULT).
	///< The default widget is activated when the user presses <EM>Enter</EM> in a window. Default
	///< widgets must be activatable, that is, activate() should affect them.

	void set_name(const char *name);
	void set_name(const String& name);
	///< Widgets can be named, which allows you to refer to them in a gtkrc file.
	///< @param name The name for the widget.
	///<
	///< You can apply a style to widgets with a particular name in the gtkrc file. See the
	///< GTK+ documentation for gtkrc files (on the same page as the docs for GtkRcStyle).

	void set_state(StateType state);
	///< Used in widget implementations; sets the state of the widget (insensitive, prelighted, etc).
	///< @param state The new state for the widget.
	///<
	///< Usually you should set the state using wrapper functions such as set_sensitive().

	void set_sensitive(bool sensitive);
	///< Sets the sensitivity of the widget.
	///< @param sensitive <EM>true</EM> to make the widget sensitive.
	///<
	///< A widget is sensitive if the user can interact with it. Insensitive widgets are
	///< <EM>grayed out</EM> and the user can't interact with them. Insensitive widgets are 
	///< known as <EM>inactive, disabled, or ghosted</EM> in some other toolkits.

	void set_app_paintable(bool app_paintable);
	///< Sets the Gtk::APP_PAINTABLE flags on the widget.
	///< @param app_paintable <EM>true</EM> if Gtk::APP_PAINTABLE should be set.
	///<
	///< Must be set on widgets whose window the application directly draws on, 
	///< in order to keep GTK+ from overwriting the drawn stuff.

	void set_double_buffered(bool double_buffered);
	///< Widgets are double buffered by default; you can use this function to turn off the buffering.
	///< @param double_buffered <EM>true</EM> to double-buffer a widget.
	///<
	///< <EM>Double buffered</EM> simply means that Gdk::Window::begin_paint() and
	///< Gdk::Window::end_paint() are called automatically around expose events sent to
	///< the widget. Gdk::Window::begin_paint() diverts all drawing to a widget's window
	///< to an offscreen buffer, and Gdk::Window::end_paint() draws the buffer to the 
	///< screen. The result is that users see the window update in one smooth step, and 
	///< don't see individual graphics primitives being rendered. In very simple terms, 
	///< double buffered widgets don't flicker, so you would only use this function to turn
	///< off double buffering if you had special needs and really knew what you were doing.

	void set_redraw_on_allocate(bool redraw_on_allocate);
	///< When a widgets size allocation changes, sets whether the entire widget is queued
	///< for drawing or not.
	///< @param redraw_on_allocate Set <EM>true</EM> to redraw the entire widget when it's resized,
	///<                           and <EM>false</EM> to only redraw the new portion of the widget
	///<
	///< By default, this setting is true and the entire widget is redrawn on every size change. 
	///< If your widget leaves the upper left unchanged when made bigger, turning this setting on 
	///< will improve performance. Note that for NO_WINDOW widgets setting this flag to false turns
	///< off all allocation on resizing: the widget will not even redraw if its position changes;
	///< this is to allow containers that don't draw anything to avoid excess invalidations. If you
	///< set this flag on a NO_WINDOW widget that does draw on the widget's GDK window, you are 
	///< responsible for invalidating both the old and new allocation of the widget when the widget
	///< is moved and responsible for invalidating regions newly when the widget increases size.

	void set_parent(Widget& parent);
	///< Sets the container as the parent of widget, and takes care of some details such as
	///< updating the state and style of the child to reflect its new location. 
	///< @param parent The parent container.
	///<
	///< This method is useful only when implementing subclasses of Container. The opposite
	///< method is unparent().

	void set_parent_window(Gdk::Window *parent_window);
	///< Sets a non default parent window for widget.
	///< @param parent_window The new parent window.

	void set_child_visible(bool is_visible);
	///< Sets whether the widget should be mapped along with its parent when its parent
	///< is mapped and the widget has been shown with show().
	///< @param is_visible If <EM>true</EM>, the widget should be mapped along with its parent.
	///<
	///< The child visibility can be set for a widget before it is added to a container
	///< with set_parent(), to avoid mapping children unnecessary before immediately 
	///< unmapping them. However it will be reset to its default state of true when the
	///< widget is removed from a container. 
	///<
	///< Note that changing the child visibility of a widget does not queue a resize on 
	///< the widget. Most of the time, the size of a widget is computed from all visible 
	///< children, whether or not they are mapped. If this is not the case, the container
	///< can queue a resize itself. This method is only useful for container implementations
	///< and never should be called by an application.

	bool child_focus(DirectionType direction);
	///< Moves the focus to the child widget.
	///< @param direction The direction of focus movement. 
	///< @return <EM>true</EM> if the focus ended up inside the widget.
	///<	
	///< This method is used by custom widget implementations; if you're writing an
	///< application, you'd use grab_focus() to move the focus to a particular widget,
	///< and Gtk::Container::set_focus_chain() to change the focus tab order. So you may
	///< want to investigate those methods instead.
	///<
	///< <EM>child_focus()</EM> is called by containers as the user moves around the window
	///< using keyboard shortcuts. <EM>direction</EM> indicates what kind of motion is 
	///< taking place (up, down, left, right, tab forward, tab backward). <EM>child_focus()</EM>
	///< invokes the "focus" signal on the Widget; widgets override the default handler for this
	///< signal in order to implement appropriate focus behavior. The "focus" default handler 
	///< for a widget should return true if moving in <EM>direction</EM> left the focus on a
	///< focusable location inside that widget, and false if moving in <EM>direction</EM> moved
	///< the focus outside the widget. If returning true, widgets normally call grab_focus() to
	///< place the focus accordingly; if returning false, they don't modify the current focus
	///< location. 

	void set_size_request(int width, int height);
	///< Sets the minimum size of a widget; that is, the widget's size request will be width by height.
	///< @param width The width the widget should request, or -1 to unset.
	///< @param height The height widget should request, or -1 to unset.
	///<
	///< You can use this method to force a widget to be either larger or smaller than it
	///< normally would be. In most cases, set_default_size() is a better choice for toplevel
	///< windows than this method; setting the default size will still allow users to shrink
	///< the window. Setting the size request will force them to leave the window at least as
	///< large as the size request. When dealing with window sizes, 
	///< Gtk::Window::set_geometry_hints() can be a useful method as well. 
	///<
	///< Note the inherent danger of setting any fixed size - themes, translations into other 
	///< languages, different fonts, and user action can all change the appropriate size for
	///< a given widget. So, it's basically impossible to hardcode a size that will always be
	///< correct.
	///<
	///< The size request of a widget is the smallest size a widget can accept while still 
	///< functioning well and drawing itself correctly. However in some strange cases a 
	///< widget may be allocated less than its requested size, and in many cases a widget 
	///< may be allocated more space than it requested. If the size request in a given 
	///< direction is -1 (unset), then the "natural" size request of the widget will be
	///< used instead. Widgets can't actually be allocated a size less than 1 by 1, but 
	///< you can pass 0,0 to this function to mean "as small as possible."

	void set_events(Gdk::EventMaskField events);
	///< Sets the event mask (see Gdk::EventMask) for a widget. 
	///< @param events The event mask.
	///<
	///< The event mask determines which events a widget will receive. Keep in mind that 
	///< different widgets have different default event masks, and by changing the event mask
	///< you may disrupt a widget's functionality, so be careful. This method must be called
	///< while a widget is unrealized. Consider add_events() for widgets that are already 
	///< realized, or if you want to preserve the existing event mask. This method can't be
	///< used with Gtk::NO_WINDOW widgets; to get events on those widgets, place them inside
	///< an EventBox and receive events on the event box.

	void add_events(Gdk::EventMaskField events);
	///< Adds the events in the bitfield <EM>events</EM> to the event mask for the widget (see set_events()).
	///< @param events An event mask, see Gdk::EventMask.

	void set_extension_events(Gdk::ExtensionMode mode);
	///< Sets the extension events mask to <EM>mode</EM> (see Gdk::ExtensionMode and
	///< Gdk::Input::set_extension_events()).
	///< @param mode The extension events to receive.

	void set_colormap(Gdk::Colormap& colormap);
	///< Sets the colormap for the widget to <EM>colormap</EM>. 
	///< @param colormap A colormap.
	///<
	///< The widget must not have been previously realized. This probably should only be used 
	///< from a constructor for the widget.

	bool translate_coordinates(Widget &src_widget, int src_x, int src_y, int *dest_x, int *dest_y) const;
	///< Translate coordinates relative to src_widget's allocation to coordinates
	///< relative to this widget's allocation.
	///< @param src_widget The source widget.
	///< @param src_x The X position relative to src_widget.
	///< @param src_y The Y position relative to src_widget.
	///< @param dest_x The location to store X position relative to this widget.
	///< @param dest_y The location to store Y position relative to this widget.
	///< @return <EM>false</EM> if either widget was not realized, or there was no common ancestor.
	///< In this case, nothing is stored in <EM>dest_x</EM> and <EM>dest_y</EM>. Otherwise <EM>true</EM>.
	///<
	///< In order to perform this operation, both widgets must be realized, and must share a common toplevel.

	void set_style(Style& style);
	///< Sets the Style for the widget.
	///< @param style A Gtk::Style, or null to remove the effect of a previous
	///<              set_style() and go back to the default style.
	///<
	///< You probably don't want to use this function; it interacts badly with themes, 
	///< because themes work by replacing the Style. Instead, use modify_style().

	void ensure_style();
	///< Ensures that the widget has a style. Not a very useful method; most of the time,
	///< if you want the style, the widget is realized, and realized widgets are guaranteed
	///< to have a style already.

	void modify_style(RcStyle& style);
	///< Modifies style values on the widget. 
	///< @param style The RcStyle holding the style modifications.
	///<
	///< Modifications made using this method take precedence over style values set
	///< via an RC file, however, they will be overridden if a style is explicitely set on
	///< the widget using set_style(). The RcStyle structure is designed so each field can
	///< either be set or unset, so it is possible, using this method, to modify some style
	///< values and leave the others unchanged.
	///<
	///< Note that modifications made with this method are not cumulative with previous 
	///< calls to modify_style() or with such functions as modify_fg(). If you wish to 
	///< retain previous values, you must first call get_modifier_style(), make your 
	///< modifications to the returned style, then call modify_style() with that style.
	///< On the other hand, if you first call modify_style(), subsequent calls to such 
	///< methods as modify_fg() will have a cumulative effect with the initial modifications.

	void modify_fg(StateType state, const Gdk::Color* color);
	///< Sets the foreground color for the widget in a particular state.
	///< @param state The state for which to set the foreground color.
	///< @param color The color to assign (does not need to be allocated), or null
	///<              to undo the effect of previous calls to modify_fg().
	///<
	///< All other style values are left untouched (se also modify_style()).

	void modify_bg(StateType state, const Gdk::Color *color);
	///< Sets the background color for the widget in a particular state.
	///< @param state The state for which to set the background color.
	///< @param color The color to assign (does not need to be allocated), or null
	///<              to undo the effect of previous calls to modify_bg().
	///<
	///< All other style values are left untouched (see also modify_style()).

	void modify_text(StateType state, const Gdk::Color *color);
	///< Sets the text color for the widget in a particular state.
	///< @param state The state for which to set the text color.
	///< @param color The color to assign (does not need to be allocated), or null
	///<              to undo the effect of previous calls to modify_text().
	///<
	///< All other style values are left untouched. The text color is the foreground
	///< color used along with the base color (see modify_base()) for widgets such as
	///< Entry and TextView. See also modify_style().

	void modify_base(StateType state, const Gdk::Color *color);
	///< Sets the base color for the widget in a particular state.
	///< @param state The state for which to set the base color.
	///< @param color The color to assign (does not need to be allocated), or null
	///<              to undo the effect of previous calls to of modify_base().
	///<
	///< All other style values are left untouched. The base color is the background 
	///< color used along with the text color (see modify_text()) for widgets such as 
	///< Entry and TextView. See also modify_style().

	void modify_font(const Pango::FontDescription *font_desc);
	///< Sets the font to use for the widget.
	///< @param font_desc The font description to use, or null to undo the effect
	///< of previous calls to modify_font().
	///<
	///< All other style values are left untouched. See also modify_style().

	Pointer<Pango::Context> create_pango_context();
	///< Creates a new Pango::Context with the appropriate colormap, font description,
	///< and base direction for drawing text for this widget (see also get_pango_context()).
	///< @return A smart pointer to the new Pango::Context.

	Pointer<Pango::Layout> create_pango_layout(const char *text);
	Pointer<Pango::Layout> create_pango_layout(const String& text);
	///< Creates a new Pango::Layout with the appropriate colormap, font description,
	///< and base direction for drawing text for this widget.
	///< @param text The text to set on the layout (can be a null String).
	///< @return A smart pointer to the new Pango::Layout.
	///<
	///< If you keep a Pango::Layout created in this way around, in order to notify
	///< the layout of changes to the base direction or font for this widget, you must
	///< call Pango::Layout::context_changed() in response to the <EM>style_set</EM>
	///< and <EM>direction_set</EM> signals for the widget.

	Pointer<Gdk::Pixbuf> render_icon(const StockId& stock_id, IconSize size, const char *detail = 0);
	///< A convenience method that uses the theme engine and RC file settings for the widget
	///< to look up stock_id and render it to a pixbuf. 
	///< @param stock_id A stock ID.
	///< @param size A stock size.
	///< @param detail The render detail to pass to a theme engine.
	///< @return A smart pointer to the new pixbuf, or null if the stock ID wasn't known.
	///<
	///< <EM>stock_id</EM> should be a stock icon ID such as Gtk::StockId::OPEN or 
	///< Gtk::StockId::OK. <EM>size</EM> should be a size such as Gtk::ICON_SIZE_MENU.
	///< <EM>detail</EM> should be a string that identifies the widget or code doing 
	///< the rendering, so that theme engines can special-case rendering for that widget
	///< or code. The pixels in the returned Gdk::Pixbuf are shared with the rest of the
	///< application and should not be modified.

	void set_composite_name(const char *name);
	void set_composite_name(const String& name);
	///< Sets a widgets composite name.
	///< @param name The name to set.
	///<
	///< The widget must be a composite child of its parent (see push_composite_child()).

	void reset_rc_styles();
	///< Reset the styles of the widget and all descendents, so when they are looked up again,
	///< they get the correct values for the currently loaded RC file settings. This method
	///< is not useful for applications

	void set_direction(TextDirection dir);
	///< Sets the reading direction on a particular widget. 
	///< @param dir The new direction.
	///<
	///< This direction controls the primary direction for widgets containing text,
	///< and also the direction in which the children of a container are packed. The
	///< ability to set the direction is present in order so that correct localization
	///< into languages with right-to-left reading directions can be done. Generally, 
	///< applications will let the default reading direction present, except for 
	///< containers where the containers are arranged in an order that is explicitely
	///< visual rather than logical (such as buttons for text justification). If the
	///< direction is set to Gtk::TEXT_DIR_NONE, then the value set by 
	///< set_default_direction() will be used.

	void shape_combine_mask(const Gdk::Bitmap& shape_mask, int offset_x, int offset_y);
	///< Sets a shape for this widget's GDK window.
	///< @param shape_mask The shape to be added.
	///< @param offset_x The X position of shape mask with respect to window.
	///< @param offset_y The Y position of shape mask with respect to window.
	///<
	///< This allows for transparent windows etc., see Gdk::Window::shape_combine_mask()
	///< for more information.

 	void shape_combine_mask();
	///< Removes an exisitng shape from this widget's GDK window.

	bool list_mnemonic_labels(std::vector<Widget*>& widgets);
	///< Returns a list of the widgets, normally labels, for which this widget
	///< is a the target of a mnemonic (see for example, Gtk::Label::set_mnemonic_widget()). 
	///< @param widgets A reference to a vector of Widget* to hold the list of mnemonic labels.
	///< @return <EM>true</EM> if the vector is not empty.
	///<
	///< The widgets in the vector are not individually referenced. If you want to iterate
	///< through the vector and perform actions that might destroy the widgets, you must call 
	///< ref() to reference a widget and unref() to unreference it afterwards.

	void add_mnemonic_label(Widget& label);
	///< Adds a widget to the list of mnemonic labels for this widget (see 
	///< Gtk::Widget::list_mnemonic_labels()). 
	///< @param label A Widget that acts as a mnemonic label for this widget. 
	///<
	///< <B>Note:</B> The list of mnemonic labels for the widget is cleared
	///< when the widget is destroyed, so the caller must make sure to update 
	///< it's internal state at this point as well, by using a connection to the
	///< Gtk::Object::signal_destroy() signal.

	void remove_mnemonic_label(Widget& label);
	///< Removes a widget from the list of mnemonic labels for this widget (see 
	///< Gtk::Widget::list_mnemonic_labels()). 
	///< @param label Widget that was previously set as a mnemonic label for this widget.
	///<
	///< The widget <EM>label</EM> must have previously been added to the list
	///< with add_mnemonic_label().

/// @}
/// @name Methods
/// @{

	static void push_colormap(Gdk::Colormap& cmap);
	///< Pushes <EM>cmap</EM> onto a global stack of colormaps; the topmost colormap on the stack
	///< will be used to create all widgets.
	///< @param cmap A Gdk::Colormap
	///<
	///< Remove <EM>cmap</EM> with pop_colormap(). There's little reason to use this method.

	static void push_composite_child();
	///< A composite child is a child that's an implementation detail of the container
	///< it's inside and should not be visible to people using the container. Composite
	///< children aren't treated differently by GTK but e.g. GUI builders might want to
	///< treat them in a different way.

	static void pop_composite_child();
	///< Cancels the effect of a previous call to push_composite_child().

	static void pop_colormap();
	///< Removes a colormap pushed with push_colormap().

	static void set_default_colormap(Gdk::Colormap *colormap);
	///< Sets the default colormap to use when creating widgets.
	///< @param colormap A Gdk::Colormap.
	///<
	///< push_colormap() is a better method to use if you only want to affect
	///< a few widgets, rather than all widgets.

	static void set_default_direction(TextDirection  dir);
	///< Sets the default reading direction for widgets where the direction has not been
	///< explicitly set by set_direction().
	///< @param dir The new default direction. This cannot be Gtk::TEXT_DIR_NONE.

/// @}	
/// @name Keyboard and Pointer Grab Methods
/// @{

	Gdk::GrabStatus keyboard_grab(bool owner_events = false, unsigned int time = GDK_CURRENT_TIME);
	///< Grabs the keyboard so that all events are passed to this widget until the keyboard
	///< is ungrabbed with Gdk::keyboard_ungrab().
	///< @param owner_events If <EM>false</EM> then all keyboard events are reported with respect the
	///<                     widget. If <EM>true</EM> then keyboard events for this application are
	///<                     reported as normal, but keyboard events outside this application are
	///<                     reported with respect to the widget. Both key press and key release events
	///<                     are always reported, independant of the event mask set by the application.
	///< @param time A timestamp from a Gdk::Event, or GDK_CURRENT_TIME if no timestamp is available.
	///< @return Gdk::GRAB_SUCCESS if the grab was successful.
	///<
	///< This overrides any previous keyboard grab by this client. The widget's Gdk::Window
	///< will own the grab (the grab window).

	Gdk::GrabStatus pointer_grab(Gdk::EventMaskField event_mask, Widget *confine_to = 0, Gdk::Cursor *cursor = 0,
	                             bool owner_events = false, unsigned int time = GDK_CURRENT_TIME);
	///< Grabs the pointer (usually a mouse) so that all events are passed to this widget until
	///< the pointer is ungrabbed with Gdk::pointer_ungrab(), or the grab widget becomes unviewable.
	///< @param event_mask Specifies the event mask, which is used in accordance with owner_events.
	///< @param confine_to If non-null, the pointer will be confined to this widget during the grab. If the
	///<                   pointer is outside confine_to, it will automatically be moved to the closest edge
	///<                   of confine_to and enter and leave events will be generated as necessary.
	///< @param cursor The cursor to display while the grab is active. If this is null then the normal
	///<               cursors are used for the widget and its descendants, and the cursor for the widget
	///<               is used for all other windows.
	///< @param owner_events If <EM>false</EM> then all pointer events are reported with respect to the
	///<                     widget and are only reported if selected by event_mask. If <EM>true</EM>
	///<                     then pointer events for this application are reported as normal, but pointer
	///<                     events outside this application are reported with respect to the widget and
	///<                     only if selected by event_mask. In either mode, unreported events are discarded.
	///< @param time The timestamp of the event which led to this pointer grab. This usually comes from a
	///<              Gdk::EventButton, though GDK_CURRENT_TIME can be used if the time isn't known.
	///< @return Gdk::GRAB_SUCCESS if the grab was successful.
	///<
	///< This overrides any previous pointer grab by this client. The widget's Gdk::Window
	///< will own the grab (the grab window). Pointer grabs are used for operations which need
	///< complete control over mouse events, even if the mouse leaves the application. For 
	///< example in GTK+ it is used for Drag and Drop, for dragging the handle in the HPaned
	///< and VPaned widgets. Note that if the event mask of an X window has selected both button
	///< press and button release events, then a button press event will cause an automatic 
	///< pointer grab until the button is released. X does this automatically since most 
	///< applications expect to receive button press and release events in pairs. It is 
	///< equivalent to a pointer grab on the window with owner_events set to true.

/// @}
/// @name Selection Methods (from gtkselection.h)
/// @{

	bool selection_owner_get(Gdk::Atom selection);
	///< Returns whether the widget owns <EM>selection</EM>.
	///< @param selection An interned atom representing the selection to check.
	///< @return <EM>true</EM> if this widget owns <EM>selection</EM>.

	bool selection_owner_set(Gdk::Atom selection, unsigned int time, const Gdk::Display *display = 0);
	///< Claim ownership of a given selection for a particular widget.
	///< @param selection An interned atom representing the selection to claim.
	///< @param time A timestamp with which to claim the selection, or GDK_CURRENT_TIME.
	///< @param display The Gdk::Display where the selection is set, or null for the default display.
	///< @return <EM>true</EM> if the operation succeeded.

	void selection_add_target(Gdk::Atom selection, Gdk::Atom target, unsigned int info);
	///< Adds the specified target to the list of supported targets for the widget and selection.
	///< @param selection The selection.
	///< @param target The target to add.
	///< @param info An unsigned integer which will be passed back to the application.

	void selection_add_target(Gdk::Atom selection, const TargetEntry& entry);
	///< Adds the specified target to the list of supported targets for the widget and selection.
	///< @param selection The selection.
	///< @param entry The target entry to add.

	void selection_add_targets(Gdk::Atom selection, const std::vector<TargetEntry>& targets);
	///< Adds the targets specified in <EM>targets</EM> to the list of supported targets
	///< for the widget and selection.
	///< @param selection The selection.
	///< @param targets A reference to a vector of TargetEntry that holds the targets to add.

	void selection_clear_targets(Gdk::Atom selection);
	///< Remove all targets registered for the given selection for the widget.
	///< @param selection An atom representing a selection.

	bool selection_convert(Gdk::Atom selection, Gdk::Atom target, unsigned int time = GDK_CURRENT_TIME);
	///< Requests the contents of a selection.
	///< @param selection Which selection to get.
	///< @param target Form of information desired (e.g., STRING).
	///< @param time Time of request (usually of triggering event), or you could use GDK_CURRENT_TIME.
	///< @return <EM>true</EM> if the request succeeded. <EM>false</EM> if we could not process
	///< the request (e.g. there was already a request in process for this widget).
	///<
	///< When received, a <EM>selection_received</EM> signal will be generated.

	void selection_remove_all();
	///< Removes all handlers and unsets ownership of all selections for the widget. Called when
	///< the widget is being destroyed. This method will not generally be called by applications.

/// @}
/// @name Selection Methods (from gtkselection.h)
/// @{

	static bool selection_owner_unset(Gdk::Atom selection, unsigned int time, const Gdk::Display *display = 0);
	///< Releases ownership of a given selection.
	///< @param selection An interned atom representing the selection to release.
	///< @param time A timestamp with which to claim the selection, or GDK_CURRENT_TIME.
	///< @param display The Gdk::Display where the selection is set, or null for the default display.
	///< @return <EM>true</EM> if the operation succeeded.

/// @}
/// @name Drag-and-Drop Target Methods (from gtkdnd.h)
/// @{

	void drag_get_data(DragContext& context, Gdk::Atom target, unsigned int time = GDK_CURRENT_TIME);
	///< Gets the data associated with a drag.
	///< @param context The drag context.
	///< @param target The target (form of the data) to retrieve.
	///< @param time A timestamp for retrieving the data.
	///<
	///< When the data is received or the retrieval fails, GTK+ will emit a <EM>drag_data_received</EM>
	///< signal. Failure of the retrieval is indicated by Gtk::SelectionData::is_valid() returning <EM>false</EM>.
	///< However, when drag_get_data() is called implicitely because the Gtk::DRAG_DEFAULT_DROP was set, then
	///< the widget will not receive notification of failed drops and Gtk::SelectionData::is_valid() will be
	///< undefined.	<EM>time</EM> will generally be the time received in a <EM>drag_data_motion</EM> or
	///< <EM>drag_data_drop</EM> signal.

	void drag_highlight();
	///< Draws a highlight around the widget. This will attach handlers to <EM>expose_event</EM> and
	///< draw, so the highlight will continue to be displayed until drag_unhighlight() is called.

	void drag_unhighlight();
	///< Removes a highlight set by drag_highlight() from the widget.

	void drag_dest_set(DestDefaultsField flags, const TargetEntry& target, Gdk::DragActionField actions);
	///< Sets the widget as a potential drop destination. 
	///< @param flags The flags that specify what actions GTK+ should take on behalf of
        ///<              a widget for drops onto that widget. 
	///< @param target A TargetEntry indicating the drop type that this widget will accept. 
	///< @param actions A bitmask of possible actions for a drop onto this widget.
	///< 
	///< The targets and actions fields only are used if DEST_DEFAULT_MOTION or
	///< DEST_DEFAULT_DROP are given. 
	
	void drag_dest_set(DestDefaultsField flags, const std::vector<TargetEntry>& targets, Gdk::DragActionField actions);
	///< Sets the widget as a potential drop destination. 
	///< @param flags The flags that specify what actions GTK+ should take on behalf of
        ///<              a widget for drops onto that widget. 
	///< @param targets A vector of TargetEntry indicating the drop types that this widget will accept. 
	///< @param actions A bitmask of possible actions for a drop onto this widget.
	///< 
	///< The targets and actions fields only are used if DEST_DEFAULT_MOTION or 
	///< DEST_DEFAULT_DROP are given. 

	void drag_dest_set_proxy(Gdk::Window *proxy_window, Gdk::DragProtocol protocol, bool use_coordinates);
	///< Sets the widget as a proxy for drops to another window.
	///< @param proxy_window The window to which to forward drag events
	///< @param protocol The drag protocol which the proxy_window accepts (You can use
	///<                 gdk_drag_get_protocol() to determine this).
	///< @param use_coordinates If <EM>true</EM>, send the same coordinates to the destination, 
	///<                        because it is an embedded subwindow.

	void drag_dest_unset();
	///< Clears information about a drop destination set with drag_dest_set().
	///< The widget will no longer receive notification of drags. 

	Gdk::Atom drag_dest_find_target(const DragContext& context, const TargetList *target_list = 0);
	///< Looks for a match between context.targets() and the target_list,
	///< returning the first matching target, otherwise returning GDK_NONE. 
	///< @param context A drag context.
	///< @param target_list A TargetList of droppable targets, or null to use drag_dest_get_target_list().
	///< @return The first target that the source offers and the dest can accept, or GDK_NONE.
	///<
	///< The target_list should usually be the return value from drag_dest_get_target_list(),
	///< but some widgets may have different valid targets for different parts of the widget; 
	///< in that case, they will have to implement a drag_motion handler that passes the correct
	///< target list to this function.

	TargetList* drag_dest_get_target_list() const;
	///< Returns the list of targets this widget can accept from drag-and-drop.
	///< @return The TargetList, or null if none.

	void drag_dest_set_target_list(TargetList *target_list);
	///< Sets the target types that this widget can accept from drag-and-drop
	///< @param target_list A list of droppable targets, or null for none.
	///<
	///< The widget must first be made into a drag destination with drag_dest_set().

	void drag_dest_add_text_targets();
	///< Add the text targets supported by Gtk::Selection to the target list of the
	///< drag destination. The targets are added with info = 0. If you need another
	///< value, use Gtk::TargetList::add_text_targets() and drag_dest_set_target_list().

	void drag_dest_add_image_targets();
	///< Add the image targets supported by Gtk::Selection to the target list of the
	///< drag destination. The targets are added with info = 0. If you need another
	///< value, use Gtk::TargetList::add_image_targets() and drag_dest_set_target_list().

	void drag_dest_add_uri_targets();
	///< Add the URI targets supported by Gtk::Selection to the target list of the
	///< drag destination. The targets are added with info = 0. If you need another
	///< value, use Gtk::TargetList::add_uri_targets() and drag_dest_set_target_list().

/// @}
/// @name Drag-and-Drop Source Methods (from gtkdnd.h)
/// @{

	DragContext* drag_source_begin(const TargetList& targets, Gdk::DragActionField actions, int button, const Gdk::Event& event);
	///< Initiates a drag on the source side. 
	///< @param targets The targets (data formats) in which the source can provide the data.
	///< @param actions A bitmask of the allowed drag actions for this drag.
	///< @param button The button the user clicked to start the drag.
	///< @param event The event that triggered the start of the drag.
	///< @return The context for this drag.
	///<	
	///< The method only needs to be used when the application is starting drags itself, 
	///< and is not needed when drag_source_set() is used.

	void drag_source_set(Gdk::ModifierTypeField start_button_mask, const TargetEntry& target, Gdk::DragActionField actions);
	///< Sets up the widget so that GTK+ will start a drag operation when the user
	///< clicks and drags on the widget. 
	///< @param start_button_mask The bitmask of buttons that can start the drag. 
	///< @param target The TargetEntry for the target the drag will support.
	///< @param actions The bitmask of possible actions for a drag from this widget.	
	
	void drag_source_set(Gdk::ModifierTypeField start_button_mask, const std::vector<TargetEntry>& targets, Gdk::DragActionField actions);
	///< Sets up the widget so that GTK+ will start a drag operation when the user
	///< clicks and drags on the widget. 
	///< @param start_button_mask The bitmask of buttons that can start the drag. 
	///< @param targets A vector of TargetEntry for the targets the drag will support. 
	///< @param actions The bitmask of possible actions for a drag from this widget.	

	void drag_source_unset();
	///< Undoes the effects of drag_source_set().

	TargetList* drag_source_get_target_list() const;
	///< Gets the list of targets this widget can provide for drag-and-drop.
	///< @return The TargetList, or null for none.
		
	void drag_source_set_target_list(TargetList *target_list);
	///< Changes the target types that this widget offers for drag-and-drop. 
	///< @param target_list	The list of draggable targets, or null for none .
	///<
	///< The widget must first be made into a drag source with drag_source_set().
	
	void drag_source_add_text_targets();
	///< Add the text targets supported by Gtk::Selection to the target list of the
	///< drag source. The targets are added with info = 0. If you need another value,
	///< use Gtk::TargetList::add_text_targets() and drag_source_set_target_list().

	void drag_source_add_image_targets();
	///< Add the image targets supported by Gtk::Selection to the target list of the
	///< drag source. The targets are added with info = 0. If you need another value,
	///< use Gtk::TargetList::add_image_targets() and drag_source_set_target_list().

	void drag_source_add_uri_targets();
	///< Add the URI targets supported by Gtk::Selection to the target list of the
	///< drag source. The targets are added with info = 0. If you need another value,
	///< use Gtk::TargetList::add_uri_targets() and drag_source_set_target_list().
	
	void drag_source_set_icon(Gdk::Colormap *colormap, Gdk::Pixmap *pixmap, Gdk::Bitmap *mask);
	///< Sets the icon that will be used for drags from the widget from a pixmap and mask.
	///< @param colormap The colormap of the icon.
	///< @param pixmap The image data for the icon.
	///< @param mask The transparency mask for an image.
	///<
	///< GTK+ retains references for the arguments, and will release them when they are
	///< no longer needed. Use drag_source_set_icon_pixbuf() instead.

	void drag_source_set_icon_pixbuf(Gdk::Pixbuf& pixbuf);
	///< Sets the icon that will be used for drags from the widget from a Gdk::Pixbuf.
	///< @param pixbuf The Gdk::Pixbuf for the drag icon.
	///<
	///< GTK+ retains references for pixbuf, and will release it when it is no longer needed.

	void drag_source_set_icon_stock(const StockId& stock_id);
	///< Sets the icon that will be used for drags from the widget to a stock icon.
	///< @param stock_id The stock ID of the icon to use.

	bool drag_check_threshold(int start_x, int start_y, int current_x, int current_y);
	///< Checks to see if a mouse drag starting at (start_x, start_y) and ending at
	///< (current_x, current_y) has passed the GTK+ drag threshhold, and thus should
	///< trigger the beginning of a drag-and-drop operation.
	///< @param start_x The X coordinate of start of drag.
	///< @param start_y The Y coordinate of start of drag.
	///< @param current_x The current X coordinate.
	///< @param current_y The current Y coordinate.
	///< @return <EM>true</EM> if the drag threshold has been passed.
	
/// @}
/// @name Basic Signal Proxies
/// @{

	const ShowSignalProxy signal_show();
	///< Connect to the show_signal; emitted when a widget becomes visible.

	const HideSignalProxy signal_hide();
	///< Connect to the hide_signal; emitted when a widget is hidden (invisible to the user).

	const MapSignalProxy signal_map();
	///< Connect to the map_signal; emitted when a widget becomes mapped.

	const UnmapSignalProxy signal_unmap();
	///< Connect to the unmap_signal; emitted when a widget becomes unmapped.

	const RealizeSignalProxy signal_realize();
	///< Connect to the realize_signal; emitted when a widget is realized.

	const UnrealizeSignalProxy signal_unrealize();
	///< Connect to the unrealize_signal; emitted when a widget is unrealized.

	const SizeRequestSignalProxy signal_size_request();
	///< Connect to the size_request_signal; emitted to obtain the preferred size of a widget.

	const SizeAllocateSignalProxy signal_size_allocate();
	///< Connect to the size_allocate_signal; emitted when a child widget is allocated a size and position.

	const StateChangedSignalProxy signal_state_changed();
	///< Connect to the state_changed_signal; emitted when the widget state changes.

	const ParentSetSignalProxy signal_parent_set();
	///< Connect to the parent_set_signal; emitted when the parent container of the widget is set.

	const HierarchyChangedSignalProxy signal_hierarchy_changed();
	///< Connect to the hierarchy_changed_signal; emitted when there is a change 
	///< in the hierarchy to which the widget belongs. More precisely, when its
	///< toplevel ancestor changes.

	const StyleSetSignalProxy signal_style_set();
	///< Connect to the style_set_signal; emitted when the widget style is changed.

	const DirectionChangedSignalProxy signal_direction_changed();
	///< Connect to the direction_changed_signal; emitted when the reading direction
	///< on the widget is changed.

	const GrabNotifySignalProxy signal_grab_notify();
	///< Connect to the grab_notify_signal; emitted to notify the widget whether it is
	///< the current grabbed widget in an application.

	const ChildNotifySignalProxy signal_child_notify(const char *property_name = 0);
	const ChildNotifySignalProxy signal_child_notify(const String& property_name);
	///< Connect to the child_notify_signal; emitted for each child property that changes on a widget.
	///< @param property_name The property name to be notified of changes to.
	///<
	///< If <EM>property_name</EM> is provided it is appended to the signal name so that
	///< the signal connected to becomes "child_notify::property_name". What this does is ensure 
	///< that your child notification slot is only called if <EM>property_name</EM> matches the
	///< property name of the "child_notify" signal being emitted. 

	const MnemonicActivateSignalProxy signal_mnemonic_activate();
	///< Connect to the mnemonic_activate_signal; emitted to activate the widget
	///< when the mnemonic key it's associated with is pressed.

	const GrabFocusSignalProxy signal_grab_focus();
	///< Connect to the grab_focus_signal; emitted when the widget receives
	///< the keyboard focus for the Window it's inside.

	const FocusSignalProxy signal_focus();
	///< Connect to the focus_signal; emitted when on a child widget when
	///< it receives the focus (see child_focus()).

	const AccelClosuresChangedSignalProxy signal_accel_closures_changed();
	///< Connect to the accel_closures_changed_signal; emitted whenever the closures used by
	///< the widget for accelerator group connections are changed. The closures can be used
	///< to monitor accelerator changes on widget.

	const ScreenChangedSignalProxy signal_screen_changed();
	///< Connect to the screen_changed_signal; emitted when the Gdk::Screen on which
	///< the widget is displayed is changed

	const CanActivateAccelSignalProxy signal_can_activate_accel();
	///< Connect to the can_activate_accel_signal; emitted to determine whether an
	///< accelerator that activates the indentifed signal can currently be activated.

/// @}
/// @name Selection Signal Proxies
/// @{

	const SelectionGetSignalProxy signal_selection_get();
	///< Connect to the selection_get_signal; emitted when the selection data is requested,
	///< if this widget is the selection owner.

	const SelectionReceivedSignalProxy signal_selection_received();
	///< Connect to the selection_received_signal; emitted to notify the widget that the
	///< requested selection data has been converted and provided by the selection owner.

/// @}
/// @name Source-side Drag Signal Proxies
/// @{

	const DragBeginSignalProxy signal_drag_begin();
	///< Connect to the drag_begin_signal; emitted on the drag source when a drag is started.
	///< A typical reason to connect to this signal is to set up a custom drag icon with
	///< drag_source_set_icon().

	const DragEndSignalProxy signal_drag_end();
	///< Connect to the drag_end_signal; emitted on the drag source when a drag is finished.
	///< A typical reason to connect to this signal is to undo things done in <EM>drag_begin</EM>.

	const DragDataGetSignalProxy signal_drag_data_get();
	///< Connect to the drag_data_get_signal; emitted on the drag source when the drop site
	///< requests the data of the first target supported. It is the responsibility of the
	///< signal handler to fill Gtk::SelectionData with the data in the format which is
	///< indicated by <EM>info</EM> (third) argument (see Gtk::SelectionData::set() and
	///< Gtk::SelectionData::set_text()).

	const DragDataDeleteSignalProxy signal_drag_data_delete();
	///< Connect to the drag_data_delete_signal; emitted on the drag source when a drag with the action
	///< Gdk::ACTION_MOVE is successfully completed. It indicates that the data can be deleted.

/// @}
/// @name Target-side Drag Signal Proxies
/// @{

	const DragLeaveSignalProxy signal_drag_leave();
	///< Connect to the drag_leave_signal; emitted on the drop site when the cursor leaves the widget.
	///< A typical reason to connect to this signal is to undo things done in <EM>drag_motion</EM>, e.g.
	///< undo highlighting with drag_unhighlight().

	const DragMotionSignalProxy signal_drag_motion();
	///< Connect to the drag_motion_signal; emitted on the drop site when the user moves the
	///< cursor over the widget during a drag. The signal handler must determine whether the
	///< cursor position is in a drop zone or not. If it is not in a drop zone, it returns
	///< <EM>false</EM> and no further processing is necessary. Otherwise, the handler returns
	///< <EM>true</EM>. In this case, the handler is responsible for providing the necessary
	///< information for displaying feedback to the user, by calling Gdk::DragContext::drag_status().
	///< If the decision whether the drop will be accepted or rejected can't be made based solely
	///< on the cursor position and the type of the data, the handler may inspect the dragged data
	///< by calling drag_get_data() and defer the Gdk::DragContext::drag_status() call to the
	///< <EM>drag_data_received</EM> signal handler.
	///<
	///< Note that there is no <EM>drag_enter</EM> signal. The drag receiver has to keep track of
	///< whether he has received any <EM>drag_motion</EM> signals since the last <EM>drag_leave</EM>
	///< and if not, treat the <EM>drag_motion</EM> signal as an "enter" signal. Upon an "enter",
	///< the handler will typically highlight the drop site with drag_highlight().

	const DragDropSignalProxy signal_drag_drop();
	///< Connect to the drag_drop_signal; emitted on the drop site when the user drops
	///< the data onto the widget. The signal handler must determine whether the cursor position
	///< is in a drop zone or not. If it is not in a drop zone, it returns <EM>false</EM> and no
	///< further processing is necessary. Otherwise, the handler returns <EM>true</EM>. In this
	///< case, the handler must ensure that Gtk::DragContext::finish() is called to let the source
	///< know that the drop is done. The call to Gtk::DragContext::finish() can be done either
	///< directly or in a <EM>drag_data_received</EM> handler which gets triggered by calling
	///< drag_get_data() to receive the data for one or more of the supported targets.

	const DragDataReceivedSignalProxy signal_drag_data_received();
	///< Connect to the drag_data_received_signal; emitted on the drop site when the dragged
	///< data has been received. If the data was received in order to determine whether the
	///< drop will be accepted, the handler is expected to call Gdk::DragContext::drag_status()
	///< and <EM>not</EM> finish the drag. If the data was received in response to a <EM>drag_drop</EM>
	///< signal (and this is the last target to be received), the handler for this signal is
	///< expected to process the received data and then call Gtk::DragContext::finish(), setting
	///< the <EM>success</EM> parameter depending on whether the data was processed successfully.
	///<
	///< The handler may inspect and modify the drag action chosen by the drop site by calling
	///< Gdk::DragContext()::action() and Gdk::DragContext()::set_action() before calling
	///< Gtk::DragContext::finish().

/// @}
/// @name GDK Event Signal Proxies
/// @{
	
	const EventSignalProxy signal_event();
	///< Connect to the event_signal; emitted when any GDK event occurs.

	const EventAfterSignalProxy signal_event_after();
	///< Connect to the event_after_signal; emitted after any GDK event occurs. This signal is
	///< used to observe events but not act on them. Hence the void return value. This signal
	///< exists because slots connected to events as 'after' handlers get called after the 
	///< default handler, but if the signal was handled they wont get called. Connect to this
	///< signal if you just want to monitor GDK events. 
	
	const ButtonPressEventSignalProxy signal_button_press_event();
	///< Connect to the button_press_event_signal; emitted when a mouse button has been pressed.

	const ButtonReleaseEventSignalProxy signal_button_release_event();
	///< Connect to the button_release_event_signal; emitted when a mouse button has been released.

	const ScrollEventSignalProxy signal_scroll_event();
	///< Connect to the scroll_event_signal; emitted when a mouse wheel is scrolled either up or down.

	const MotionNotifyEventSignalProxy signal_motion_notify_event();
	///< Connect to the motion_notify_event_signal; emitted when the mouse is moved.

	const DeleteEventSignalProxy signal_delete_event();
	///< Connect to the delete_event_signal; emitted when the user tries to close
	///< an application from the window manager frame.

	const DestroyEventSignalProxy signal_destroy_event();
	///< Connect to the destroy_event_signal; emitted when the widget has been destroyed.

	const ExposeEventSignalProxy signal_expose_event();
	///< Connect to the expose_event_signal; emitted when all or part of the widget
	///< has become visible and needs to be redrawn.

	const KeyPressEventSignalProxy signal_key_press_event();
	///< Connect to the key_press_event_signal; emitted when a key is pressed.

	const KeyReleaseEventSignalProxy signal_key_release_event();
	///< Connect to the key_release_event_signal; emitted when a key is released.

	const EnterNotifyEventSignalProxy signal_enter_notify_event();
	///< Connect to the enter_notify_event_signal; emitted when the widget is entered.

	const LeaveNotifyEventSignalProxy signal_leave_notify_event();
	///< Connect to the leave_notify_event_signal; emitted when then widget is exited.

	const ConfigureEventSignalProxy signal_configure_event();
	///< Connect to the configure_event_signal; emitted when the size, position or
	///< stacking order of the widget is changed.

	const FocusInEventSignalProxy signal_focus_in_event();
	///< Connect to the focus_in_event_signal; emitted when the widget gains the keyboard focus
	///< (the focus widget gets keyboard events).

	const FocusOutEventSignalProxy signal_focus_out_event();
	///< Connect to the focus_out_event_signal; emitted when the widget looses the keyboard focus.

	const MapEventSignalProxy signal_map_event();
	///< Connect to the map_event_signal; emitted when the widget has been mapped 
	///< (visible on the screen).

	const UnmapEventSignalProxy signal_unmap_event();
	///< Connect to the unmap_event_signal; emitted when the widget has been mapped
	///< (no longer visible on the screen).

	const PropertyNotifyEventSignalProxy signal_property_notify_event();
	///< Connect to the property_notify_event_signal; emitted when a property on the widget
	///< has been changed or deleted.

	const SelectionClearEventSignalProxy signal_selection_clear_event();
	///< Connect to the selection_clear_event_signal; emitted when an application has
	///< lost ownership of a selection.

	const SelectionRequestEventSignalProxy signal_selection_request_event();
	///< Connect to the selection_request_event_signal; emitted when another application
	///< has requested a selection.

	const SelectionNotifyEventSignalProxy signal_selection_notify_event();
	///< Connect to the selection_notify_event_signal; emitted when a selection has been received.

	const ProximityInEventSignalProxy signal_proximity_in_event();
	///< Connect to the proximity_in_event_signal; emitted when an input device has moved
	///< into contact with a sensing surface (such as a touchscreen or graphics tablet).

	const ProximityOutEventSignalProxy signal_proximity_out_event();
	///< Connect to the proximity_out_event_signal; emitted when an input device
	///< has moved out of contact with a sensing surface.

	const VisibilityNotifyEventSignalProxy signal_visibility_notify_event();
	///< Connect to the visibility_notify_event_signal; emitted when the widget's visibility
	///< status has changed (either fully obscured, partially obscured or unobscured).

	const ClientEventSignalProxy signal_client_event();
	///< Connect to the client_event_signal; emitted when a message has been received
	///< from another application.

	const NoExposeEventSignalProxy signal_no_expose_event();
	///< Connect to the no_expose_event_signal; emitted when all or part of the widget
	///< has become visible, but no expose event was generated.

	const WindowStateEventSignalProxy signal_window_state_event();
	///< Connect to the window_state_event_signal; emitted when the state of a toplevel
	///< window changes (either not shown, minimized, maximized, sticky or fullscreen).

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/widget.inl>

#endif // XFC_GTK_WIDGET_HH

