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

/// @file xfc/gtk/toolitem.hh
/// @brief A GtkToolItem C++ wrapper interface.
///
/// Provides ToolItem, a base class for widgets that can be added to Gtk::Toolbar. 

#ifndef XFC_GTK_TOOL_ITEM_HH
#define XFC_GTK_TOOL_ITEM_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_TOOL_ITEM_H__
#include <gtk/gtktoolitem.h>
#endif

namespace Xfc {

namespace Gtk {

class Tooltips;

/// @class ToolItem toolitem.hh xfc/gtk/toolitem.hh
/// @brief A GtkToolItem C++ wrapper class.
///
/// ToolItems are widgets that can appear on a toolbar. To construct a toolbar
/// item that contains something other than a button, use ToolItem(). Use 
/// Gtk::Container::add() to add a child widget to the tool item. 
///
/// For toolbar items that contain buttons, see the Gtk::ToolButton, Gtk::ToggleToolButton
/// and Gtk::RadioToolButton classes. See the Gtk::Toolbar class for a description of the
/// toolbar widget. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/toolitems.html">ToolItems</A> HOWTO.

class ToolItem : public Bin
{
	friend class G::Object;

	ToolItem(const ToolItem&);
	ToolItem& operator=(const ToolItem&);

protected:
/// @name Constructors
/// @{

	explicit ToolItem(GtkToolItem *tool_item, bool owns_reference = false);
	///< Construct a new ToolItem from an existing GtkToolItem.
	///< @param tool_item A pointer to a GtkToolItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tool_item</EM> can be a newly created GtkToolItem or an existing GtkToolItem (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<bool> CreateMenuProxySignalType;
	typedef G::SignalProxy<TypeInstance, CreateMenuProxySignalType> CreateMenuProxySignalProxy;
	static const CreateMenuProxySignalType create_menu_proxy_signal;
	///< Create menu proxy signal (see signal_create_menu_proxy()). Calls a slot with the signature:
	///< @code
	///< bool function();
	///< // return: true if the signal was handled, false if not. 	
	///< @endcode

	typedef G::Signal<void> ToolbarReconfiguredSignalType;
	typedef G::SignalProxy<TypeInstance, ToolbarReconfiguredSignalType> ToolbarReconfiguredSignalProxy;
	static const ToolbarReconfiguredSignalType toolbar_reconfigured_signal;
	///< Toolbar reconfigured signal (see signal_toolbar_reconfigured()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<bool, Tooltips&, const String&, const String&> SetTooltipSignalType;
	typedef G::SignalProxy<TypeInstance, SetTooltipSignalType> SetTooltipSignalProxy;
	static const SetTooltipSignalType set_tooltip_signal;
	///< Set tooltip signal (see signal_set_tooltip()). Calls a slot with the signature:
	///< @code
	///< bool function(Tooltips& tooltips, const String& tip_text, const String& tip_private);
	///< // tooltips: The Gtk::Tooltips. 
	///< // tip_text: The tooltip text. 
	///< // tip_private: The tooltip private text. 
	///< // return: true if the signal was handled, false if not.
	///< @endcode

/// @}

public:
	typedef GtkToolItem CObjectType;

/// @name Constructors
/// @{

	ToolItem();
	///< Constructs a new tool item.
	
	explicit ToolItem(Widget& widget);
	///< Constructs a new tool item that displays <EM>widget</EM>.
	///< @param widget The widget to set as the tool item's content.	

	virtual ~ToolItem();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkToolItem* gtk_tool_item() const;
	///< Get a pointer to the GtkToolItem structure.

	operator GtkToolItem* () const;
	///< Conversion operator; safely converts an ToolItem to a GtkToolItem pointer.

	bool get_homogeneous() const;
	///< Determines whether the tool item is the same size as other homogeneous items (see set_homogeneous()).
	///< @return <EM>true</EM> if the item is the same size as other homogeneous items.

	bool get_expand() const;
	///< Determines whether the tool item is allocated extra space (see set_expand()).
	///< @return <EM>true</EM> if then tool item is allocated extra space.

	bool get_use_drag_window() const;
	///< Determines whether the tool item has a drag window (see set_use_drag_window()).
	///< @return <EM>true</EM> if the tool item uses a drag window.

	bool get_visible_horizontal() const;
	///< Determines whether the tool item is visible on toolbars that are docked horizontally.
	///< @return <EM>true</EM> if the tool item is visible on toolbars that are docked horizontally.
	
	bool get_visible_vertical() const;
	///< Determines whether the tool item is visible when the toolbar is docked
	///< vertically (see set_visible_vertical()).
	///< @return Whether the tool item is visible when the toolbar is docked vertically.

	bool get_is_important() const;
	///< Determines whether the tool item is considered important (see set_is_important()).
	///< @return <EM>true</EM> if the tool item is considered important.
	
	IconSize get_icon_size() const;
	///< Gets the icon size used for the tool item. 
	///< @return A Gtk::IconSize indicating the icon size used for the tool item.
	///<	
	///< Custom subclasses of ToolItem should call this function to find out
	///< what size icons they should use.

	Orientation get_orientation() const;
	///< Gets the orientation used for the tool item. 
	///< @return A Gtk::Orientation indicating the orientation used for the tool item.
	///<	
	///< Custom subclasses of ToolItem should call this function to find out
	///< the orientation of they should use.
	
	ToolbarStyle get_toolbar_style() const;
	///< Gets the toolbar style used for the tool item. 
	///< @return A Gtk::ToolbarStyle indicating the toolbar style used for the tool item.
	///<	
	///< Custom subclasses of ToolItem should call this function in the handler of the
	///< ToolItem "toolbar_reconfigured" signal to find out in what style the toolbar is
	///< displayed and change themselves accordingly. The possibilities are: Gtk::TOOLBAR_BOTH,
	///< meaning the tool item should show both an icon and a label, stacked vertically,
	///< Gtk::TOOLBAR_ICONS, meaning the toolbar shows only icons, Gtk::TOOLBAR_TEXT, meaning
	///< the tool item should only show text and Gtk::TOOLBAR_BOTH_HORIZ, meaning the tool item
	///< should show both an icon and a label, arranged horizontally.
	
	ReliefStyle get_relief_style() const;
	///< Gets the relief style of the tool item (see set_relief_style(). 
	///< @return A Gtk::ReliefStyle indicating the relief style used for the tool item.
	///	
	///< Custom subclasses of ToolItem should call this function in the handler of the
	///< ToolItem "toolbar_reconfigured" signal to find out the relief style of the buttons.

	Widget* get_proxy_menu_item(const char *menu_item_id) const;
	Widget* get_proxy_menu_item(const String& menu_item_id) const;
	///< If <EM>menu_item_id</EM> matches the string passed to set_proxy_menu_item()
	///< returns the corresponding Gtk::MenuItem widget.
	///< @param menu_item_id A string used to identify the menu item. 
	///< @return The MenuItem passed to set_proxy_menu_item(), if the menu_item_ids match.
	///<
	///< Custom subclasses of ToolItem should use this function to update their 
	///< menu item when the ToolItem changes. That the menu_item_ids must match 
	///< ensures that a ToolItem will not inadvertently change a menu item that they
	///< did not create.

	Widget* retrieve_proxy_menu_item() const;
	///< Retrieves the MenuItem that was last set by set_proxy_menu_item(), that is,
	///< the MenuItem that is going to appear in the overflow menu.
	///< @return The MenuItem that is going to appear in the overflow menu for the tool item.
	
/// @}
/// @name Methods
/// @{

	void set_homogeneous(bool homogeneous);
	///< Sets whether the tool item is to be allocated the same size as other homogeneous items.
	///< @param homogeneous Whether the tool item is the same size as other homogeneous items. 
	///<	 
	///< The effect is that all homogeneous items will have the same width as the widest of the items.
	
	void set_expand(bool expand);
	///< Sets whether the tool item is allocated extra space when there is more room
	///< on the toolbar than needed for the items. 
	///< @param expand Whether the tool item is allocated extra space.
	///<	
	///< The effect is that the item gets bigger when the toolbar gets bigger 
	///< and smaller when the toolbar gets smaller.

	void set_tooltip(Tooltips& tooltips, const char *tip_text, const char *tip_private = 0);
	void set_tooltip(Tooltips& tooltips, const String& tip_text, const String& tip_private = 0);
	///< Sets the Tooltips object to be used for the tool item, the text to be displayed
	///< as tooltip on the item and the private text to be used (see Gtk::Tooltips::set_tip()).
	///< @param tooltips The Tooltips object to be used. 
	///< @param tip_text The text to be used as tooltip text for the tool item. 
	///< @param tip_private The text to be used as private tooltip text. 

	void set_use_drag_window(bool use_drag_window);
	///< Sets whether toolitem has a drag window. 
	///< @param use_drag_window Whether the tool item has a drag window.
	///< 	
	///< When <EM>use_drag_window</EM> is <EM>true</EM> the tool item can be used
	///< as a drag source through Gtk::Widget::drag_source_set(). When the  tool item
	///< has a drag window it will intercept all events, even those that would 
	///< otherwise be sent to a child of toolitem.
	
	void set_visible_horizontal(bool visible_horizontal);
	///< Sets whether the tool item is visible when the toolbar is docked horizontally.
	///< @param visible_horizontal Whether the tool item is visible when in horizontal mode.
	 
	void set_visible_vertical(bool visible_vertical);
	///< Sets whether the tool item is visible when the toolbar is docked vertically.
	///< @param visible_vertical Whether the tool item is visible when the toolbar is in vertical mode.
	///<	 
	///< Some tool items, such as text entries, are too wide to be useful on a vertically
	///< docked toolbar. If <EM>visible_vertical</EM> is <EM>false</EM> the tool item will not
	///< appear on toolbars that are docked vertically.
	
	void set_is_important(bool is_important);
	///< Sets whether the tool item should be considered important. 
	///< @param is_important Whether the tool item should be considered important.
	///<	
	///< The ToolButton class uses this property to determine whether to show
	///< or hide its label when the toolbar style is Gtk::TOOLBAR_BOTH_HORIZ. The
	///< result is that only tool buttons with the "is_important" property set have
	///< labels, an effect known as "priority text".
	
	void set_proxy_menu_item(const char *menu_item_id, Widget *menu_item);
	void set_proxy_menu_item(const String& menu_item_id, Widget *menu_item);
	///< Sets the MenuItem used in the toolbar overflow menu. 
	///< @param menu_item_id A string used to identify <EM>menu_item</EM>. 
	///< @param menu_item A MenuItem to be used in the overflow menu.
	///<	
	///< The <EM>menu_item_id</EM> is used to identify the caller of this function
	///< and should also be used with get_proxy_menu_item(). If <EM>menu_item</EM> is
	///< null the MenuItem last set will not appear in the overflow menu (see
	///< signal_create_menu_proxy()).

	void rebuild_menu();
	///< Calling this method signals to the toolbar that the overflow menu item
	///< for the tool item has changed. If the overflow menu is visible when this
	///< function it called, the menu will be rebuilt. 
	///< 
	///< This function must be called when the tool item changes what it will do
	///< in response to the "create_menu_proxy" signal.

/// @}
/// @name Signal Proxies
/// @{

	const CreateMenuProxySignalProxy signal_create_menu_proxy();
	///< Connect to the create_menu_proxy_signal; emitted when the toolbar is displaying an overflow menu.
	///< In response the tool item should call Gtk::ToolItem::set_proxy_menu_item() with either with a
	///< null pointer and return true to indicate that the item should not appear in the overflow menu,
	///< or with a new menu item and return true, or return false to indicate that the signal was not
	///< handled by the item. This means that the item will not appear in the overflow menu unless a 
	///< later handler installs a menu item. 
	
	const ToolbarReconfiguredSignalProxy signal_toolbar_reconfigured();
	///< Connect to the toolbar_reconfigured_signal; emitted when some property of the toolbar
	///< that the item is a child of changes. For custom subclasses of Gtk::ToolItem, the 
	///< default handler of this signal uses the functions Gtk::Toolbar::get_orientation(),
	///< Gtk::Toolbar::get_style(), Gtk::Toolbar::get_icon_size() and Gtk::Toolbar::get_relief_style()
	///< to find out what the toolbar should look like and change themselves accordingly.

	const SetTooltipSignalProxy signal_set_tooltip();
	///< Connect to the set_tooltip_signal; emitted when the toolitem's tooltip changes.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/toolitem.inl>

#endif // XFC_GTK_TOOL_ITEM_HH

