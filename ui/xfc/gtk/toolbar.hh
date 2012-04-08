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
 
/// @file xfc/gtk/toolbar.hh
/// @brief A GtkToolbar C++ wrapper interface.
///
/// Provides Toolbar, a container widget that Buttons, ToggleButtons, RadioButtons
/// and arbitrary widgets can be added to.

#ifndef XFC_GTK_TOOLBAR_HH
#define XFC_GTK_TOOLBAR_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef XFC_GTK_RADIO_TOOL_BUTTON_HH
#include <xfc/gtk/radiotoolbutton.hh>
#endif

#ifndef XFC_GTK_SEPARATOR_TOOL_ITEM_HH
#include <xfc/gtk/separatortoolitem.hh>
#endif

#ifndef __GTK_TOOLBAR_H__
#include <gtk/gtktoolbar.h>
#endif

namespace Xfc {

namespace Gtk {

class Tooltips;

/// @class Toolbar toolbar.hh xfc/gtk/toolbar.hh
/// @brief A GtkToolbar C++ wrapper class.
///
/// A toolbar can contain instances of a subclass of Gtk::ToolItem. To add a ToolItem
/// to the a toolbar, use append(), prepend() or insert(). To remove an item from the
/// toolbar use Gtk::Container::remove(). To add a button to the toolbar, add an 
/// instance of Gtk::ToolButton. 
///
/// Toolbar items can be visually grouped by adding instances of Gtk::SeparatorToolItem to
/// the toolbar. If a SeparatorToolItem has the 'expand' property set to <EM>true</EM> and
/// the 'draw' property set to <EM>false</EM> the effect is to force all following items to
/// the end of the toolbar. Creating a context menu for the toolbar can be done by connecting
/// to the Gtk::Toolbar popup_context_menu signal (see signal_popup_context_menu()).
///
/// <B>See also:</B> the <A HREF="../../howto/html/toolbar.html">Toolbar</A> and
/// <A HREF="../../howto/html/toolitems.html">ToolItems</A> HOWTOs and example.
 
class Toolbar : public Container
{
	friend class G::Object;

	Toolbar(const Toolbar&);
	Toolbar& operator=(const Toolbar&);

protected:
/// @name Constructors
/// @{

	explicit Toolbar(GtkToolbar *toolbar, bool owns_reference = false);
	///< Construct a new Toolbar from an existing GtkToolbar.
	///< @param toolbar A pointer to a GtkToolbar.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>toolbar</EM> can be a newly created GtkToolbar or an existing
	///< GtkToolbar (see G::Object::Object).
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, Orientation> OrientationChangedSignalType;
	typedef G::SignalProxy<TypeInstance, OrientationChangedSignalType> OrientationChangedSignalProxy;
	static const OrientationChangedSignalType orientation_changed_signal;
	///< Orientation changed signal (see signal_orientation_changed()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::Orientation orientation);
	///< // orientation: The new Orientation of the toolbar.
	///< @endcode

	typedef G::Signal<void, ToolbarStyle> StyleChangedSignalType;
	typedef G::SignalProxy<TypeInstance, StyleChangedSignalType> StyleChangedSignalProxy;
	static const StyleChangedSignalType style_changed_signal;
	///< %Style changed signal (see signal_style_changed()). Calls a slot with the signature:
	///< @code
	///< void function(Gtk::ToolbarStyle style);
	///< // style: The new ToolbarStyle of toolbar.
	///< @endcode

	typedef G::Signal<bool, int, int, int> PopupContextMenuSignalType;
	typedef G::SignalProxy<TypeInstance, PopupContextMenuSignalType> PopupContextMenuSignalProxy;
	static const PopupContextMenuSignalType popup_context_menu_signal;
	///< Popup context menu signal (see signal_popup_context_menu()). Calls a slot with the signature:
	///< @code
	///< bool function(int x, int y, int button);
	///< // x: The x coordinate of the point where the menu should appear.
	///< // y: The y coordinate of the point where the menu should appear.
	///< // button: The mouse button the user pressed, or -1.
	///< // return: true if the signal was handled, <EM>false</EM> if not.
	///< @endcode
	
/// @}

public:
	typedef GtkToolbar CObjectType;

/// @name Constructors
/// @{

	Toolbar();
	///< Construct a new default toolbar. The default toolbar is a horizontal toolbar that
	///< displays both icons and text.

	explicit Toolbar(Orientation orientation);
	///< Construct a new toolbar with the specifed <EM>orientation</EM>.
	///< @param orientation The Orientation, either horizontal or vertical.
	///<
	///< By default this toolbar displays both icons and text. To change the toolbar
	///< style call Gtk::Toolbar::set_style();

	Toolbar(Orientation orientation, ToolbarStyle style);
	///< Constrcut a new toolbar with the specified <EM>orientation</EM> and <EM>style</EM>.
	///< @param orientation The Orientation, either horizontal or vertical.
	///< @param style The style for the toolbar.

	virtual ~Toolbar();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkToolbar* gtk_toolbar() const;
	///< Get a pointer to the GtkToolbar structure.

	operator GtkToolbar* () const;
	///< Conversion operator; safely converts a Toolbar to a GtkToolbar pointer.

	int get_item_index(const ToolItem& item) const;
	///< Obtains the position of item on the toolbar, starting from 0.
	///< @param item A ToolItem that is a child of the toolbar.
	///< @return The position of <EM>item</EM> on the toolbar.
	///<
	///< It is an error if item is not a child of the toolbar.

	int get_n_items() const;
	///< Gets the number of items on the toolbar.
	///< @returns The number of items on the toolbar.

	ToolItem* get_nth_item(int n) const;
	///< Gets the tool item at position <EM>n</EM> on the toolbar, or null
	///< if the toolbar does not contain an n'th item.
	///< @param n A zero-based position on the toolbar.
	///< @return The nth ToolItem on the toolbar, or null if there isn't an nth item.

	bool get_show_arrow() const;
	///< Determines whether the toolbar has an overflow menu (see set_show_arrow()).
	///< @return <EM>true</EM> if the toolbar has an overflow menu.

	Orientation get_orientation() const;
	///< Gets the current orientation of the toolbar (see set_orientation()).
	///< @return The current orientation.

	bool get_tooltips() const;
	///< Determines whether tooltips are enabled (see set_tooltips()).
	///< @return <EM>true</EM> if tooltips are enabled.
	
	ToolbarStyle get_style() const;
	///< Retrieves whether the toolbar has text, icons, or both (see set_style()).
	///< @return The current style of the toolbar.

	IconSize get_icon_size() const;
	///< Gets the current icon size for the icons on the toolbar.
	///< @return The current icon size.

	ReliefStyle get_relief_style() const;
	///< Gets the relief style of buttons on the toolbar (see Gtk::Button::set_relief_style()).
	///< @return The relief style of buttons on the toolbar.

	int get_drop_index(int x, int y) const;
	///< Obtains the position corresponding to the indicated point on the toolbar.
	///< @param x The X coordinate of a point on the toolbar, in toolbar coordinates.
	///< @param y The Y coordinate of a point on the toolbar, in toolbar coordinates.
	///< @return The position corresponding to the point (x, y) on the toolbar.
	///<
	///< This is useful when dragging items to the toolbar. This method returns
	///< the position a new item should be inserted.

/// @}
/// @name Methods
/// @{

	void append(ToolItem& item, const char *tooltip = 0);
	void append(ToolItem& item, const String& tooltip);
	///< Appends a ToolItem to the end of the toolbar.
	///< @param item A ToolItem. 
	///< @param tooltip The tooltip to display for the <EM>item</EM>.
	
	void prepend(ToolItem& item, const char *tooltip = 0);
	void prepend(ToolItem& item, const String& tooltip);
	///< Prepends a ToolItem to the start of the toolbar.
	///< @param item A ToolItem. 
	///< @param tooltip The tooltip to display for the <EM>item</EM>.
	
	void insert(ToolItem& item, int pos, const char *tooltip = 0);
	void insert(ToolItem& item, int pos, const String& tooltip);
	///< Insert a ToolItem into the toolbar at position <EM>pos</EM>.
	///< @param item A ToolItem. 
	///< @param pos The position of the new item. 
	///< @param tooltip The tooltip to display for the <EM>item</EM>.
	///<	 
	///< If pos is 0 the item is prepended to the start of the toolbar. If pos
	///< is -1, the item is appended to the end of the toolbar. Otherwise the tool
	///< item is inserted at position pos.
	
	void append_separator();
	///< Adds a new separator tool item to the end of the toolbar. 
	
	void insert_separator(int pos);
	///< Inserts a new separator tool item into the toolbar at the specified position.
	///< @param pos The number of tool items to insert the space after.
	///<
	///< If <EM>pos</EM> is -1 the separator is added to the end of the toolbar.
	///< If <EM>pos</EM> is 0 the separator is added to the beginning of the toolbar.
	///< Otherwise the separator is inserted at position <EM>pos</EM>. 	
	
	void set_show_arrow(bool show_arrow);
	///< Sets whether to show an overflow menu when toolbar doesn't have
	///< room for all items on it.
	///< @param show_arrow Set <EM>true</EM> to show an overflow menu.
	///<
	///< If <EM>show_arrow</EM> is true, items that there are not room for
	///< are available through an overflow menu.

	void set_orientation(Orientation orientation);
	///< Sets whether a toolbar should appear horizontally or vertically.
	///< @param orientation The new Orientation.

	void set_tooltips(bool enable);
	///< Sets if the tooltips of a toolbar should be active or not.
	///< @param enable Set to false to disable the tooltips, or true to enable them.
	
	void set_style(ToolbarStyle style);
	///< Alters the view of toolbar to display either icons only, text only, or both.
	///< @param style The new style for the toolbar.

	void unset_style();
	///< Unsets the toolbar style set with set_style(), so that user preferences will be
	///<  used to determine the toolbar style.

	void set_drop_highlight_item(ToolItem& item, int index);
	///< Highlights the toolbar to give an idea of what it would look like if <EM>item</EM>
	///< was added to the toolbar at the position indicated by index.
	///< @param item A ToolItem.
	///< @param index A position on the toolbar.
	///<
	///< The tool item passed to this function must not be part of any widget hierarchy.
	///< When an item is set as drop highlight item it can not added to any widget hierarchy
	///< or used as highlight item for another toolbar.

	void unset_drop_highlight_item();
	///< Turn off drop highlighting.

	void set_tooltip(ToolItem& item, const char *tip_text, const char *tip_private = 0);
	void set_tooltip(ToolItem& item, const String& tip_text, const String& tip_private = 0);
	///< Sets the tooltip to be used for the tool item, the text to be displayed
	///< as tooltip on the item and the private text to be used, if any.
	///< @param item A ToolItem. 
	///< @param tip_text The text to be used as tooltip text for the tool item. 
	///< @param tip_private The text to be used as private tooltip text. 
	///<
	///< Calling this convenience method is equivalent to calling Gtk::ToolItem::set_tooltip().
	
/// @}
/// @name Signal Proxies
/// @{

	const OrientationChangedSignalProxy signal_orientation_changed();
	///< Connect to the orientation_changed_signal; emitted when the orientation of a toolbar is changed.

	const StyleChangedSignalProxy signal_style_changed();
	///< Connect to the style_changed_signal; emitted when ever the style of a toolbar is adjusted.

	const PopupContextMenuSignalProxy signal_popup_context_menu();
	///< Connect to the popup_context_menu_signal; emitted when when the user right-clicks the
	///< toolbar or uses the keybinding to display a popup menu.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/toolbar.inl>

#endif // XFC_GTK_TOOLBAR_HH

