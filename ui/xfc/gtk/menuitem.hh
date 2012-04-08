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
 
/// @file xfc/gtk/menuitem.hh
/// @brief A GtkMenuItem C++ wrapper interface.
///
/// Provides MenuItem, the only valid child widget for menus.

#ifndef XFC_GTK_MENU_ITEM_HH
#define XFC_GTK_MENU_ITEM_HH

#ifndef XFC_GTK_ITEM_HH
#include <xfc/gtk/item.hh>
#endif

#ifndef __GTK_MENU_ITEM_H__
#include <gtk/gtkmenuitem.h>
#endif

namespace Xfc {

namespace Gtk {
	
class Menu;

/// @class MenuItem menuitem.hh xfc/gtk/menuitem.hh
/// @brief A GtkMenuItem C++ wrapper class.
///
/// The MenuItem widget and its derived widgets are the only valid child widgets for menus. Their
/// function is to correctly handle highlighting, alignment, events and submenus. As MenuItem
/// derives from Bin it can hold any valid child widget, although only a few are really useful.
///
/// <B>See also:</B> the <A HREF="../../howto/html/menuitems.html">MenuItem</A> and
/// <A HREF="../../howto/html/menus.html">Menu</A> HOWTOs and example.

class MenuItem : public Item
{
	friend class G::Object;

	MenuItem(const MenuItem&);
	MenuItem& operator=(const MenuItem&);

protected:
/// @name Contructors
/// @{

	explicit MenuItem(GtkMenuItem *menu_item, bool owns_reference = false);
	///< Construct a new MenuItem from an existing GtkMenuItem.
	///< @param menu_item A pointer to a GtkMenuItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>menu_item</EM> can be a newly created GtkMenuItem or an existing
	///< GtkMenuItem (see G::Object::Object).

/// @}
/// @name Methods
/// @{

	void add_label(const char *label, bool use_underline);
	void add_label(const String& label, bool use_underline);
	///< Adds a label widget to an empty menu item with the text <EM>label</EM>.
	///< @param label The text for the label.
	///< @param use_underline Set <EM>true</EM> if there is an underscore in front of the mnemonic character.
	///<
	///< This method is used by the derived menu item widgets such as CheckMenuItem and
	///< ImageMenuItem. You probably wont find much use for it.

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

	typedef G::Signal<void> ActivateItemSignalType;
	typedef G::SignalProxy<TypeInstance, ActivateItemSignalType> ActivateItemSignalProxy;
	static const ActivateItemSignalType activate_item_signal;
	///< Activate item signal (see signal_activate_item()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, int*> ToggleSizeRequestSignalType;
	typedef G::SignalProxy<TypeInstance, ToggleSizeRequestSignalType> ToggleSizeRequestSignalProxy;
	static const ToggleSizeRequestSignalType toggle_size_request_signal;
	///< Toggle size request signal (see signal_toggle_size_request()). Calls a slot with the signature:
	///< @code
	///< void function(int *requisition);
	///< // requisition: The return location for the size of the toggle.
	///< @endcode

	typedef G::Signal<void, int> ToggleSizeAllocateSignalType;
	typedef G::SignalProxy<TypeInstance, ToggleSizeAllocateSignalType> ToggleSizeAllocateSignalProxy;
	static const ToggleSizeAllocateSignalType toggle_size_allocate_signal;
	///< Toggle size allocate signal (see signal_toggle_size_allocate()). Calls a slot with the signature:
	///< @code
	///< void function(int allocate);
	///< // allocate: The size allocated to the toggle.
	///< @endcode
	
/// @}

public:
	typedef GtkMenuItem CObjectType;

/// @name Constructors
/// @{

	MenuItem();
	///< Construct a new MenuItem.

	explicit MenuItem(const char *label, bool use_underline = false);
	explicit MenuItem(const String& label, bool use_underline = false);
	///< Construct a new MenuItem whose child is a Label.
	///< @param label The text for the label.
	///< @param use_underline Set <EM>true</EM> if there is an underscore in front of the mnemonic character.

	MenuItem(const char *label, Menu& submenu, bool use_underline = false);
	MenuItem(const String& label, Menu& submenu, bool use_underline = false);
	///< Construct a new MenuItem that pops up a submenu.
	///< @param label The text for the label.
	///< @param submenu The submenu.
	///< @param use_underline Set <EM>true</EM> if there is an underscore in front of the mnemonic character.

	virtual ~MenuItem();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkMenuItem* gtk_menu_item() const;
	///< Get a pointer to the GtkMenuItem structure.

	operator GtkMenuItem* () const;
	///< Conversion operator; safely converts a MenuItem to a GtkMenuItem pointer.

	bool has_submenu() const;
	///< Returns true if the menu item displays a submenu.
	
	bool get_right_justified() const;
	///< Gets whether the menu item appears justified at the right side of the menu bar.
	///< @return <EM>true</EM> if the menu item will appear at the far right if added to a menu bar.

	Menu* get_submenu() const;
	///< Gets the submenu underneath this menu item, if any (see set_submenu()).
	///< @return The submenu for this menu item, or null if there is none.

/// @}
/// @name Methods
/// @{

	void set_label(const char *label, bool use_underline = false);
	void set_label(const String& label, bool use_underline = false);
	///< Sets the label text to <EM>label</EM>.
	///< @param label The text for the label.
	///< @param use_underline Set <EM>true</EM> if there is an underscore in front of the mnemonic character.
	///<
	///< This method can be used to dynamically change the menu item text. If the menu item
	///< is empty, a label widget is added with the text <EM>label</EM>.

	void set_submenu(Menu& submenu);
	///< Sets the widget submenu, or changes it. 
	///< @param submenu The submenu.

	void remove_submenu();
	///< Removes the widget's submenu.

	void activate();
	///< Emits the "activate" signal on the given item.

	void toggle_size_request(int *requisition);
	///< Emits the "toggle_size_request" signal on the menu item. 

	void toggle_size_allocate(int allocation);
	///< Emits the "toggle_size_allocate" signal on the menu item.

	void set_right_justified(bool right_justified);
	///< Sets whether the menu item appears justified at the right side of a menu bar.
	///< @param right_justified If <EM>true</EM> the menu item will appear at the far right
	///<                        if added to a menu bar.
	///< This was traditionally done for "Help" menu items, but is now considered a
	///< bad idea. If the widget layout is reversed for a right-to-left language like
	///< Hebrew or Arabic, right-justified-menu-items appear at the left.

	void set_accel_path(const char *accel_path);
	void set_accel_path(const String& accel_path);
	///< Set the accelerator path on the menu item, through which runtime changes
	///< of the menu item's accelerator caused by the user can be identified and
	///< saved to persistant storage (see Gtk::AccelMap::save() on this).
	///< @param accel_path The accelerator path, corresponding to this menu item's
	///<                   functionality, or null to unset the current path.
	///<
	///< To setup a default accelerator for this menu item, call Gtk::AccelMap::add_entry()
	///< with the same accel_path. See also Gtk::AccelMap::add_entry() on the specifics of
	///< accelerator paths, and Gtk::Menu::set_accel_path() for a more convenient variant of 
	///< this function.
	///<
	///< This Method is basically a convenience wrapper that handles calling
	///< Gtk::Widget::set_accel_path() with the appropriate accelerator group for the menu item.
	///< Note that you do need to set an accelerator group on the parent menu at construction or
	///< later with Gtk::Menu::set_accel_group() for this to work.

/// @}
/// @name Signal Proxies
/// @{

	const ActivateSignalProxy signal_activate();
	///< Connect to the activate_signal; emitted when the menu item is activated.

	const ActivateItemSignalProxy signal_activate_item();
	///< Connect to the activate_item_signal; emitted when the item is activated,
	///< but also if the menu item has a submenu. For normal applications, the
	///< relevant signal is "activate".

	const ToggleSizeRequestSignalProxy signal_toggle_size_request();
	///< Connect to the toggle_size_request_signal; emitted when MenuBar or Menu requests
	///< the size of the toggle.

	const ToggleSizeAllocateSignalProxy signal_toggle_size_allocate();
	///< Connect to the toggle_size_allocate_signal; emitted when MenuBar or Menu allocates
	///< a size for the toggle.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/menuitem.inl>

#endif // XFC_GTK_MENU_ITEM_HH

