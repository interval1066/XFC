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

/// @file xfc/gtk/menushell.hh
/// @brief A GtkMenuShell C++ wrapper interface.
///
/// Provides MenuShell, an abstract base class used to derive the Menu and MenuBar subclasses.

#ifndef XFC_GTK_MENU_SHELL_HH
#define XFC_GTK_MENU_SHELL_HH

#ifndef XFC_GTK_CONTAINER_HH
#include <xfc/gtk/container.hh>
#endif

#ifndef XFC_GTK_MENU_ITEM_H
#include <xfc/gtk/menuitem.hh>
#endif

#ifndef __GTK_MENU_SHELL_H__
#include <gtk/gtkmenushell.h>
#endif

namespace Xfc {

namespace Gtk {

/// @enum MenuDirectionType
/// MenuDirectionType represents the directional movements within a menu.

enum MenuDirectionType
{
	MENU_DIR_PARENT = GTK_MENU_DIR_PARENT, ///< To the parent menu shell.
	MENU_DIR_CHILD = GTK_MENU_DIR_CHILD, ///< To the submenu, if any, associated with the item.
	MENU_DIR_NEXT = GTK_MENU_DIR_NEXT, ///< To the next menu item.
	MENU_DIR_PREV = GTK_MENU_DIR_PREV ///< To the previous menu item.
};

/// @class MenuShell menushell.hh xfc/gtk/menushell.hh
/// @brief A GtkMenuShell C++ wrapper class.
///
/// A MenuShell is the abstract base class used to derive the Menu and MenuBar subclasses.
/// It is a container of MenuItem objects arranged in a list which can be navigated,
/// selected, and activated by the user to perform application functions. A MenuItem can
/// have a submenu associated with it, allowing for nested hierarchical menus.
///
/// <B>See also:</B> the <A HREF="../../howto/html/menus.html">Menu</A> and
/// <A HREF="../../howto/html/menuitems.html">MenuItem</A> HOWTOs and example.

class MenuShell : public Container
{
	friend class G::Object;

	MenuShell(const MenuShell&);
	MenuShell& operator=(const MenuShell&);

protected:
/// @name Constructors
/// @{

	MenuShell();
	///< Construct a new MenuShell.

	explicit MenuShell(GtkMenuShell *menu_shell, bool owns_reference = false);
	///< Construct a new MenuShell from an existing GtkMenuShell.
	///< @param menu_shell A pointer to a GtkMenuShell.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>menu_shell</EM> can be a newly created GtkMenuShell or an existing
	///< GtkMenuShell (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> DeactivateSignalType;
	typedef G::SignalProxy<TypeInstance, DeactivateSignalType> DeactivateSignalProxy;
	static const DeactivateSignalType deactivate_signal;
	///< Deactivate signal (see signal_deactivate()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> SelectionDoneSignalType;
	typedef G::SignalProxy<TypeInstance, SelectionDoneSignalType> SelectionDoneSignalProxy;
	static const SelectionDoneSignalType selection_done_signal;
	///< Selection done signal (see signal_selection_done()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
	
/// @}

public:
	typedef GtkMenuShell CObjectType;

/// @name Constructors
/// @{

	virtual ~MenuShell();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkMenuShell* gtk_menu_shell() const;
	///< Get a pointer to the GtkMenuShell structure.

	operator GtkMenuShell* () const;
	///< Conversion operator; safely converts a MenuShell to a GtkMenuShell pointer.

	bool children(std::vector<MenuItem*>& child_list) const;
	///< Get the list of MenuItem objects contained by this MenuShell.
	///< @param child_list A reference to a <EM>vector of MenuItem*</EM> to hold the child list.
	///< @return <EM>true</EM> if the child list is not empty, and <EM>false</EM> if it is empty.

/// @}
/// @name Methods
/// @{

	void append(MenuItem& item);
	///< Adds a new menu item to the end of the menu shell's item list.
	///< @param item The menu item to add.

	void append(MenuItem& item, const sigc::slot<void>& callback);
	///< Adds a new menu item to the end of the menu shell's item list.
	///< @param item The menu item to add.
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.

	void append(MenuItem& item, const AccelKey& accel_key, const sigc::slot<void>& callback);
	///< Adds a new menu item to the end of the menu shell's item list.
	///< @param item The menu item to add.
	///< @param accel_key The accelerator key for the menu item.
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.
	///<
	///< Calls Gtk::Menu::get_accel_group() to retrieve the accelerator group for the menu,
	///< and adds the accelerator key to this accelerator group.

	void append(MenuItem& item, const AccelKey& accel_key, AccelGroup& accel_group, const sigc::slot<void>& callback);
	///< Adds a new menu item to the end of the menu shell's item list.
	///< @param item The menu item to add.
	///< @param accel_key The accelerator key for the menu item.
	///< @param accel_group The accelerator group to add the accelerator key to.
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.

	void append(const StockId& stock_id, const sigc::slot<void>& callback);
	///< Adds a new stock menu item to the end of the menu shell's item list.
	///< @param stock_id The stock ID of the menu item to append.
	///< @param callback The callback slot to connect to the stock menu item's <EM>activate_signal</EM>.

	void append_separator();
	///< Adds a new separator menu item to the end of the menu shell's item list.	
	
	void prepend(MenuItem& item);
	///< Adds a new menu item to the beginning of the menu shell's item list.
	///< @param item The menu item to add.

	void prepend(MenuItem& item, const sigc::slot<void>& callback);
	///< Adds a new menu item to the beginning of the menu shell's item list.
	///< @param item The menu item to add.
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.

	void prepend(MenuItem& item, const AccelKey& accel_key, const sigc::slot<void>& callback);
	///< Adds a new menu item to the beginning of the menu shell's item list.
	///< @param item The menu item to add.
	///< @param accel_key The accelerator key for the menu item.
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.
	///<
	///< Calls Gtk::Menu::get_accel_group() to retrieve the accelerator group for the menu,
	///< and adds the accelerator key to this accelerator group.

	void prepend(MenuItem& item, const AccelKey& accel_key, AccelGroup& accel_group, const sigc::slot<void>& callback);
	///< Adds a new menu item to the beginning of the menu shell's item list.
	///< @param item The menu item to add.
	///< @param accel_key The accelerator key for the menu item.
	///< @param accel_group The accelerator group to add the accelerator key to.
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.

	void prepend(const StockId& stock_id, const sigc::slot<void>& callback);
	///< Adds a new stock menu item to the beginning of the menu shell's item list.
	///< @param stock_id The stock ID of the menu item to prepend.
	///< @param callback The callback slot to connect to the stock menu item's <EM>activate_signal</EM>.

	void insert(MenuItem& item, int position);
	///< Adds a new menu item to the menu shell's item list at the position indicated by <EM>position</EM>.
	///< @param item The menu item to add.
	///< @param position The position in the item list where child is added (numbered from 0 to n-1).

	void insert(MenuItem& item, int position, const sigc::slot<void>& callback);
	///< Adds a new menu item to the menu shell's item list at the position indicated by <EM>position</EM>.
	///< @param item The menu item to add.
	///< @param position The position in the item list where child is added (numbered from 0 to n-1).
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.

	void insert(MenuItem& item, int position, const AccelKey& accel_key, const sigc::slot<void>& callback);
	///< Adds a new menu item to the menu shell's item list at the position indicated by <EM>position</EM>.
	///< @param item The menu item to add.
	///< @param position The position in the item list where child is added (numbered from 0 to n-1).
	///< @param accel_key The accelerator key for the menu item.
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.
	///<
	///< Calls Gtk::Menu::get_accel_group() to retrieve the accelerator group for the menu,
	///< and adds the accelerator key to this accelerator group.

	void insert(MenuItem& item, int position, const AccelKey& accel_key, AccelGroup& accel_group, const sigc::slot<void>& callback);
	///< Adds a new menu item to the menu shell's item list at the position indicated by <EM>position</EM>.
	///< @param item The menu item to add.
	///< @param position The position in the item list where child is added (numbered from 0 to n-1).
	///< @param accel_key The accelerator key for the menu item.
	///< @param accel_group The accelerator group to add the accelerator key to.
	///< @param callback The callback slot to connect to item's <EM>activate_signal</EM>.

	void insert(const StockId& stock_id, int position, const sigc::slot<void>& callback);
	///< Adds a new stock menu item to the menu shell's item list at the position indicated by <EM>position</EM>.
	///< @param stock_id The stock ID of the menu item to insert.
	///< @param position The position in the item list where child is added (numbered from 0 to n-1).
	///< @param callback The callback slot to connect to the stock menu item's <EM>activate_signal</EM>.

	void insert_separator(int position);
	///< Adds a new separator menu item at the position indicated by <EM>position</EM>.	
	///< @param position The position in the item list where the separator is added (numbered from 0 to n-1).
	
	void select_item(MenuItem& item);
	///< Selects the menu item from the menu shell.
	///< @param item The MenuItem to select.

	void deselect();
	///< Deselects the currently selected item from the menu shell, if any.

	void activate_item(MenuItem& item, bool force_deactivate);
	///< Activates the menu item within the menu shell.
	///< @param item The menu item to activate.
	///< @param force_deactivate If <EM>true</EM>, force the deactivation of the menu shell
	///<                         after the menu item is activated.
	
	void deactivate();
	///< Deactivates the menu shell. Typically this results in the menu shell being erased
	///< from the screen.

	void select_first(bool search_sensitive);
	///< Select the first visible or selectable child of the menu shell; don't select tearoff
	///< items unless the only item is a tearoff item.
	///< @param search_sensitive If <EM>true</EM>, search for the first selectable menu item,
	///< otherwise select nothing if the first item isn't sensitive. 
	///<
	///< <EM>search_sensitive</EM> should be false if the menu is being popped up initially.

	void cancel();
	///< Cancels the selection within the menu shell.  

/// @}
/// @name Signal Proxies
/// @{

	const DeactivateSignalProxy signal_deactivate();
	///< Connect to the deactivate_signal; emitted when a menu shell is deactivated.

	const SelectionDoneSignalProxy signal_selection_done();
	///< Connect to the selection_done_signal; emitted when a selection has been completed
	///< within a menu shell.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/menushell.inl>

#endif // XFC_GTK_MENU_SHELL_HH

