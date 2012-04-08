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

/// @file xfc/gtk/action.hh
/// @brief A GtkAction C++ wrapper interface.
///
/// Provides Action, an object that represents an action that can be triggered
/// by a menu or toolbar item.

#ifndef XFC_GTK_ACTION_HH
#define XFC_GTK_ACTION_HH

#ifndef XFC_G_OBJECT_HH
#include <xfc/glib/object.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef __GTK_ACTION_H__
#include <gtk/gtkaction.h>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gtk {

class AccelGroup;
class ActionGroup;
class Image;
class MenuItem;
class StockId;
class ToolItem;
class Widget;

/// @class Action action.hh xfc/gtk/action.hh
/// @brief A GtkAction C++ wrapper class.
///
/// The Action object represents an action that can be triggered by a menu or toolbar item.
/// Actions are operations that the user can be perform, along with some information how it
/// should be presented in the interface. Each action provides methods to create icons, menu
/// items and toolbar items representing itself.
///
/// As well as the callback that is called when the action gets activated, the following also
/// gets associated with the action:
/// - a name (not translated, for path lookup)
/// - a label (translated, for display)
/// - an accelerator
/// - whether label indicates a stock id
/// - a tooltip (optional, translated)
/// - a toolbar label (optional, shorter than label)
///
/// The action will also have some state information:
/// - visible (shown/hidden)
/// - sensitive (enabled/disabled)
///
/// Apart from regular actions, there are toggle actions, which can be toggled between two states
/// and radio actions, of which only one in a group can be in the "active" state. Other actions
/// can be implemented as GtkAction subclasses.
///
/// Each action can have one or more proxy menu item, toolbar button or other proxy widgets.
/// Proxies mirror the state of the action (text label, tooltip, icon, visible, sensitive, etc),
/// and should change when the action's state changes. When the proxy is activated, it should
/// activate its action.
///
/// Note: <EM>dynamically allocated objects must either be unreferenced or assigned to a
/// smart pointer. Stack objects are automatically unreferenced when they go out of scope.</EM> 
///
/// <B>See also:</B> the <A HREF="../../howto/html/uimanager.html">User Interface Manager</A> HOWTO and example.

class Action : public G::Object
{
	friend class G::Object;
	friend class ActionGroup;

	Action(const Action&);
	Action& operator=(const Action&);

protected:
/// @name Constructors
/// @{

	explicit Action(GtkAction *action, bool owns_reference = true);
	///< Construct a new Action from an existing GtkAction.
	///< @param action A pointer to a GtkAction.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>action</EM> can be a newly created GtkAction or an existing GtkAction (see G::Object::Object).

/// @}
/// @name Methods
/// @{

	void block_activate_from(Widget& proxy);
	///< Disables calls to the activate() method by signals on the given proxy widget.
	///< @param proxy The action widget.
	///<
	///< This is used to break notification loops for things like check or radio
	///< actions. This method is intended for use by action implementations.

	void unblock_activate_from(Widget& proxy);
	///< Re-enables calls to the activate() method by signals on the given proxy widget.
	///< @param proxy The action widget.
	///<
	///< This undoes the blocking done by block_activate_from(). This method is
	///< intended for use by action implementations.

/// @}
/// @name Property Prototypes
/// @{

	typedef G::Property<String> LabelPropertyType;
	typedef G::PropertyProxy<G::Object, LabelPropertyType> LabelPropertyProxy;
	static const LabelPropertyType label_property;
	///< Label used for menu items and buttons that activate this action (see property_label()).

	typedef G::Property<String> ShortLabelPropertyType;
	typedef G::PropertyProxy<G::Object, ShortLabelPropertyType> ShortLabelPropertyProxy;
	static const ShortLabelPropertyType short_label_property;
	///< Shorter label that may be used on toolbar buttons (see property_short_label()).

	typedef G::Property<String> TooltipPropertyType;
	typedef G::PropertyProxy<G::Object, TooltipPropertyType> TooltipPropertyProxy;
	static const TooltipPropertyType tooltip_property;
	///< A tooltip for this action (see property_tooltip()).

	typedef G::Property<String> StockIdPropertyType;
	typedef G::PropertyProxy<G::Object, StockIdPropertyType> StockIdPropertyProxy;
	static const StockIdPropertyType stock_id_property;
	///< Stock icon displayed in widgets representing this action (see property_stock_id()).

	typedef G::Property<bool> IsImportantPropertyType;
	typedef G::PropertyProxy<G::Object, IsImportantPropertyType> IsImportantPropertyProxy;
	static const IsImportantPropertyType is_important_property;
	///< Whether the action is considered important (see property_is_important()).

	typedef G::Property<bool> HideIfEmptyPropertyType;
	typedef G::PropertyProxy<G::Object, HideIfEmptyPropertyType> HideIfEmptyPropertyProxy;
	static const HideIfEmptyPropertyType hide_if_empty_property;
	///< Whether empty menu proxies for this action are hidden (see property_hide_if_empty()).

	typedef G::Property<bool> SensitivePropertyType;
	typedef G::PropertyProxy<G::Object, SensitivePropertyType> SensitivePropertyProxy;
	static const SensitivePropertyType sensitive_property;
	///< Whether the action is enabled (see property_sensitive()).

	typedef G::Property<bool> VisiblePropertyType;
	typedef G::PropertyProxy<G::Object, VisiblePropertyType> VisiblePropertyProxy;
	static const VisiblePropertyType visible_property;
	///< Whether the action is visible (see property_visible()).
	
	typedef G::Property<bool> VisibleHorizontalPropertyType;
	typedef G::PropertyProxy<G::Object, VisibleHorizontalPropertyType> VisibleHorizontalPropertyProxy;
	static const VisibleHorizontalPropertyType visible_horizontal_property;
	///< Whether the toolbar item is visible in horizontal orientation (see property_visible_horizontal()). 
	
	typedef G::Property<bool> VisibleVerticalPropertyType;
	typedef G::PropertyProxy<G::Object, VisibleVerticalPropertyType> VisibleVerticalPropertyProxy;
	static const VisibleVerticalPropertyType visible_vertical_property;
	///< Whether the toolbar item is visible in a vertical orientation (see property_visible_vertical()). 

	typedef G::Property<bool> VisibleOverflownPropertyType;
	typedef G::PropertyProxy<G::Object, VisibleOverflownPropertyType> VisibleOverflownPropertyProxy;
	static const VisibleOverflownPropertyType visible_overflown_property;
	///< Whether toolitem proxies for this action are represented in the toolbar overflow menu
	///< (see property_visible_overflown()).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> ActivateSignalType;
	typedef G::SignalProxy<TypeInstance, ActivateSignalType> ActivateSignalProxy;
	static const ActivateSignalType activate_signal;
	///< Activate signal (see signal_activate()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkAction CObjectType;

/// @name Constructors
/// @{

	Action(const char *name, const char *label);	
	Action(const String& name, const String& label);
	///< Constructs a new Action object with a reference count of 1 that the caller owns. 
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///<	
	///< To add the action to a ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action().
	
	Action(const char *name, const StockId& stock_id);	
	Action(const String& name, const StockId& stock_id);
	///< Constructs a new Action object with a reference count of 1 that the caller owns. 
	///< @param name A unique name for the action. 
	///< @param stock_id The stock icon and label to display in widgets representing the action. 
	///<	
	///< To add the action to a ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action().
	
	Action(const char *name, const char *label, const StockId& stock_id);	
	Action(const String& name, const String& label, const StockId& stock_id);
	///< Constructs a new Action object with a reference count of 1 that the caller owns. 
	///< @param name A unique name for the action. 
	///< @param label The label displayed in menu items and on buttons. 
	///< @param stock_id The stock icon to display in widgets representing the action. 
	///<	
	///< To add the action to a ActionGroup and set the accelerator for the action, 
	///< call Gtk::ActionGroup::add_action(). Note that <EM>label</EM> is displayed
	///< instead of the <EM>stock_id</EM> label. 
	
	virtual ~Action();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkAction* gtk_action() const;
	///< Get a pointer to the GtkAction structure.

	operator GtkAction* () const;
	///< Conversion operator; safely converts an Action to a GtkAction pointer.

	String get_name() const;
	///< Gets the name of the action.
	///< @return The name of the action.

	bool get_proxies(std::vector<Widget*>& proxies) const;
	///< Gets a list of the proxy widgets for an action.
	///< @param proxies A reference to a vector of Widget pointers to hold the proxy list.
	///< @return <EM>true</EM> if the proxies vector is not empty, <EM>false</EM> otherwise.

	bool get_sensitive() const;
	///< Determines whether the action itself is sensitive. 
	///< @returns <EM>true</EM> if the action itself is sensitive. 
	///<	
	///< Note that this doesn't necessarily mean effective sensitivity (see is_sensitive() for that).

	bool get_visible() const;
	///< Determines whether the action itself is visible. 
	///< @return <EM>true</EM> if the action itself is visible. 
	///<	
	///< Note that this doesn't necessarily mean effective visibility (see is_visible() for that).

	bool is_sensitive() const;
	///< Determines whether the action is effectively sensitive.
	///< @return <EM>true</EM> if the action and its associated action group are both sensitive.

	bool is_visible() const;
	///< Determines whether the action is effectively visible.
	///< @return <EM>true</EM> if the action and its associated action group are both visible.

	String get_accel_path() const;
	///< Obtains the accelerator path for this action.
	///< @return The accelerator path for this action, or null if none is set. 

/// @}
/// @name Methods
/// @{

	void set_sensitive(bool sensitive);
	///< Sets the "sensitive" property of the action to <EM>sensitive</EM>. 
	///< @param sensitive Set to <EM>true</EM> to make the action sensitive.
	///<	
	///< Note that this doesn't necessarily mean effective sensitivity (see is_sensitive()).
							
	void set_visible(bool visible);
	///< Sets the "visible" property of the action to <EM>visible</EM>. 
	///< @param visible Set to <EM>true</EM> to make the action visible.							
	///< 	
	///< Note that this doesn't necessarily mean effective visibility (see is_visible()).
	
	void activate();
	///< Emits the "activate" signal on the specified action, if it isn't insensitive.
	///< This gets called by the proxy widgets when they get activated. It can also be
	///< used to manually activate an action.

	Image* create_icon(IconSize icon_size);
	///< This method is intended for use by action implementations to create
	///< stock icons displayed in the proxy widgets.
	///< @param icon_size The size of the icon that should be created.
	///< @return A widget that displays the icon for this action.

	MenuItem* create_menu_item();
	///< Creates a menu item widget that proxies for the given action.
	///< @return A menu item connected to the action.

	ToolItem* create_tool_item();
	///< Creates a toolbar item widget that proxies for the given action.
	///< @return A toolbar item connected to the action.

	void connect_proxy(Widget& proxy);
	///< Connects a widget to an action object as a proxy.
	///< @param proxy The proxy widget
	///<
	///< Synchronises various properties of the action with the widget (such as label text,
	///< icon, tooltip, etc), and attaches a callback so that the action gets activated when
	///< the proxy widget does. If the <EM>widget</EM> is already connected to an action, it
	///< is disconnected first.

	void disconnect_proxy(Widget& proxy);
	///< Disconnects a proxy widget from an action but does not destroy the widget.
	///< @param proxy The proxy widget

	void connect_accelerator();
	///< Installs the accelerator for the action, if the action has an accelerator path
	///< and group (see set_accel_path() and set_accel_group()). Since multiple proxies
	///< may independently trigger the installation of the accelerator, the action
	///< counts the number of times this method is called and doesn't remove the
	///< accelerator until disconnect_accelerator() has been called as many times.

	void disconnect_accelerator();
	///< Undoes the effect of one call to connect_accelerator().

	void set_accel_path(const char *accel_path);
	void set_accel_path(const String& accel_path);
	///< Sets the accelerator path for this action (used by action groups).
	///< @param accel_path The accelerator path.
	///<
	///< All proxy widgets associated with the action will have this accel path,
	///< so that their accelerators are consistent (use by action groups).

	void set_accel_group(AccelGroup *accel_group);
	///< Sets the AccelGroup in which the accelerator for this action will be installed
	///< (used by action groups).
	///< @param accel_group An AccelGroup, or null.

	void set_tooltip(const char *tooltip);
	void set_tooltip(const String& tooltip);
	///< Sets the tooltip for the action.
	///< @param tooltip The tooltip to display for the action.

/// @}
/// @name Property Proxies
/// @{

	const LabelPropertyProxy  property_label();
	///< The label used for menu items and buttons that activate this action (String : Read / Write).

	const ShortLabelPropertyProxy property_short_label();
	///< A shorter label that may be used on toolbar buttons (String : Read / Write).

	const TooltipPropertyProxy  property_tooltip();
	///< A tooltip for this action (String : Read / Write).
	
	const StockIdPropertyProxy property_stock_id();
	///< The stock icon displayed in widgets representing this action (String : Read / Write).

	const IsImportantPropertyProxy property_is_important();
	///< Whether the action is considered important. When TRUE, toolitem proxiesfor this action
	///< show text in Gtk::TOOLBAR_BOTH_HORIZ mode (bool : Read / Write).

	const HideIfEmptyPropertyProxy property_hide_if_empty();
	///< When true, empty menu proxies for this action are hidden (bool : Read / Write).

	const SensitivePropertyProxy property_sensitive();
	///< Whether the action is enabled (bool : Read / Write).

	const VisiblePropertyProxy property_visible();
	///< Whether the action is visible (bool : Read / Write).

	const VisibleHorizontalPropertyProxy property_visible_horizontal();
	///< Whether the toolbar item is visible when the toolbar is in a horizontal orientation (bool : Read / Write).

	const VisibleVerticalPropertyProxy property_visible_vertical();
	///< Whether the toolbar item is visible when the toolbar is in a vertical orientation (bool : Read / Write).

	const VisibleOverflownPropertyProxy property_visible_overflown();
	///< When true, toolitem proxies for this action are represented in the toolbar overflow menu (bool : Read / Write).

/// @}
/// @name Signal Proxies
/// @{

	const ActivateSignalProxy signal_activate();
	///< Connect to the activate_signal; emitted when the action is activated.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/action.inl>

#endif // XFC_GTK_ACTION_HH

