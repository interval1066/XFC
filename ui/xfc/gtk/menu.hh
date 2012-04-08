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
 
/// @file xfc/gtk/menu.hh
/// @brief A GtkMenu C++ wrapper interface.
///
/// Provides Menu, a MenuShell widget that implements a drop down menu consisting
/// of a list of MenuItem objects which can be navigated and activated by the user
/// to perform application functions.

#ifndef XFC_GTK_MENU_HH
#define XFC_GTK_MENU_HH

#ifndef XFC_GTK_MENU_SHELL_HH
#include <xfc/gtk/menushell.hh>
#endif

#ifndef __GTK_MENU_H__
#include <gtk/gtkmenu.h>
#endif

namespace Xfc {

namespace Gdk {
class Screen;
}

namespace Gtk {

class MenuClass;
class MenuItem;

/// @class Menu menu.hh xfc/gtk/menu.hh
/// @brief A GtkMenu C++ wrapper class.
///
/// A Menu is a MenuShell that implements a drop down menu consisting of a list of
/// MenuItem objects which can be navigated and activated by the user to perform
/// application functions. A Menu is most commonly dropped down by activating a
/// MenuItem in a MenuBar or popped up by activating a MenuItem in another Menu.
/// A Menu can also be popped up by activating an OptionMenu. Other composite
/// widgets such as the Notebook can pop up a Menu as well. Applications can
/// display a Menu as a popup menu by calling the popup() method. The example
/// below shows how an application can pop up a menu when the 3rd mouse button
/// is pressed.
///
/// <B>Example 1:</B> Connecting the popup signal handler.
/// @code
/// // Declare a button_press_event handler in you window class.
/// bool on_button_press(GdkEventButton *event);
///
/// // Then connect the window button_press_event to the popup signal handler.
/// signal_button_press_event().connect(slot(this, &MyWindow::on_button_press));
/// @endcode
///
/// <B>Example 2:</B> A signal handler which displays a popup menu.
/// @code
/// // Construct the popup menu somewhere first, then pop it up here.
/// bool MyWindow::on_button_press(GdkEventButton *event)
/// {
/// 	menu->popup(event->button, event->time);
/// 	return true;
/// }
/// @endcode
/// There is a complete example of this in the menu example programs in the <examples/menu>
/// subdirectory.
///
/// <B>See also:</B> the <A HREF="../../howto/html/menus.html">Menu</A> and
/// <A HREF="../../howto/html/menuitems.html">MenuItem</A> HOWTOs and example.

class Menu : public MenuShell
{
	friend class G::Object;
	friend class MenuClass;
	
	Menu(const Menu&);
	Menu& operator=(const Menu&);
	
protected:
/// @name Constructors
/// @{

	explicit Menu(GtkMenu *menu, bool owns_reference = false);
	///< Construct a new Menu from an existing GtkMenu.
	///< @param menu A pointer to a GtkMenu.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>menu</EM> can be a newly created GtkMenu or an existing
	///< GtkMenu (see G::Object::Object).

/// @}
/// @name Methods
/// @{

	virtual void on_menu_detach(Widget& attach_widget);
	///< Called when a menu previously attached to a widget by calling attach_to_widget()
	///< is later detached from the widget by calling detach().
	///< @param attach_widget The Widget that the menu is being detached from.

/// @}

public:
	typedef GtkMenu CObjectType;
	
	typedef sigc::slot<void, int*, int*, bool*> MenuPositionSlot;
	///< Signature of the callback slot to be called when a popup menu is displayed
	///< by calling popup(); this slot controls the position of the popup menu.
	///< <B>Example:</B> Method signature for MenuPositionSlot.
	///< @code
	///< void method(int *x, int *y, bool *push_in);
	///< // x: The address of the int representing the horizontal position where the menu shall be drawn.
	///< // y: The address of the int representing the vertical position where the menu shall be drawn.
	///< // push_in: If true, when the popup menu runs off the screen it is moved so it is displayed
	///< //          wholely on the screen. The default is false.
	///< @endcode

/// @name Constructors
/// @{

	Menu();
	///< Construct a new Menu.

	Menu(const AccelGroup& accel_group);
	///< Construct a new Menu with an accelerator group which holds global accelerators for the menu.
	///< @param accel_group The AccelGroup to be associated with the menu.
	///<
	///< This accelerator group also needs to be added to all windows that this menu
	///< is being used in with Gtk::Window::add_accel_group(), in order for those windows
	///< to support all the accelerators contained in this group.

	virtual ~Menu();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkMenu* gtk_menu() const;
	///< Get a pointer to the GtkMenu structure.

	operator GtkMenu* () const;
	///< Conversion operator; safely converts a Menu to a GtkMenu pointer.

	MenuItem* get_active() const;
	///< Get the selected menu item from the menu.
	///< @return The MenuItem that was last selected in the menu.
	///<
	///< If a selection has not yet been made, the first menu item is selected.
	///< This is used by the OptionMenu.

	AccelGroup* get_accel_group() const;
	///< Gets the AccelGroup which holds global accelerators for the menu (see set_accel_group()).
	
	Widget* get_attach_widget() const;
	///< Returns the Widget that the menu is attached to.
	
	bool get_tearoff_state() const;
	///< Returns whether the menu is torn off (see set_tearoff_state()).
	/// @return <EM>true</EM> if the menu is currently torn off.

	String get_title() const;
	///< Returns the title of the menu (see set_title()).
	///< @return The title of the menu, or null if the menu has no title set on it.

/// @}
/// @name Accessors
/// @{
	
	static std::vector<Menu*> get_for_attach_widget(Widget& widget);
	///< Obtains a list of the menus which are attached to the <EM>widget</EM>. 
	///< @return A vector of menus attached to this widget.
	 
/// @}
/// @name Methods
/// @{

	void popup(MenuShell& parent_shell, MenuItem& parent_item, unsigned int button, const MenuPositionSlot& position,
	           unsigned int activate_time = GDK_CURRENT_TIME);
	///< Displays a menu and makes it available for selection.
	///< @param parent_shell The menu shell containing the triggering menu item.
	///< @param parent_item The menu item whose activation triggered the popup.
	///< @param button The button which was pressed to initiate the event.
	///< @param position A MenuPositionSlot that is called to control the positon of the menu.
	///< @param activate_time The time at which the activation event occurred.
	///<
	///< Applications can use this function to display context-sensitive menus.

	void popup(unsigned int button, const MenuPositionSlot& position, unsigned int activate_time = GDK_CURRENT_TIME);
	///< Displays a menu and makes it available for selection.
	///< @param button The button which was pressed to initiate the event.
	///< @param position A MenuPositionSlot that is called to control the positon of the menu.
	///< @param activate_time The time at which the activation event occurred.
	///<
	///< Applications can use this function to display context-sensitive menus.

	void popup(unsigned int button, unsigned int activate_time = GDK_CURRENT_TIME);
	///< Displays a menu and makes it available for selection.
	///< @param button The button which was pressed to initiate the event.
	///< @param activate_time The time at which the activation event occurred.
	///<
	///< Applications can use this function to display context-sensitive menus.
	///< The default menu positioning function will position the menu at the current
	///< pointer position.

	void reposition();
	///< Repositions the menu according to its position slot.

	void popdown();
	///< Removes the menu from the screen.

	void set_active(unsigned int index);
	///< Selects the specified menu item within the menu.
	///< @param index The index of the menu item to select. Index values are from 0 to n-1.
	///<
	///< This is used by the OptionMenu and should not be used by anyone else.

	void set_accel_group(const AccelGroup *accel_group);
	///< Set the AccelGroup which holds global accelerators for the menu.
	///< @param accel_group The AccelGroup to be associated with the menu.
	///<
	///< This accelerator group also needs to be added to all windows that this menu
	///< is being used in with Gtk::Window::add_accel_group(), in order for those windows
	///< to support all the accelerators contained in this group.

	void set_accel_path(const char *accel_path);
	void set_accel_path(const String& accel_path);
	///< Sets an accelerator path for this menu from which accelerator paths for its
	///< immediate children, its menu items, can be constructed.
	///< @param accel_path A valid accelerator path.
	///<
	///< The main purpose of this method is to spare the programmer the inconvenience
	///< of having to call set_accel_path() on each menu item that should support 
	///< runtime user changable accelerators. Instead, by just calling set_accel_path()
	///< on their parent, each menu item of this menu, that contains a label describing
	///< its purpose, automatically gets an accel path assigned. For example, a menu
	///< containing menu items "New" and "Exit", will, after 
	///< set_accel_path("<Gnumeric-Sheet>/File") has been called, assign its items the
	///< accel paths: "<Gnumeric-Sheet>/File/New" and "<Gnumeric-Sheet>/File/Exit". 
	///< Assigning accel paths to menu items then enables the user to change their
	///< accelerators at runtime. More details about accelerator paths and their default
	///< setups can be found at Gtk::AccelMap::add_entry().
	///< @param accel_path A valid accelerator path.

	void attach_to_widget(Widget& attach_widget);
	///< Attaches the menu to the <EM>widget</EM>.
	///< @param attach_widget The Widget that the menu will be attached to.
	///<
	///< When the menu calls detach() during its destruction the virtual
	///< on_menu_detach() method is called.

	void detach();
	///< Detaches the menu from the widget to which it had been attached.
	///< Calling this method invokes the virtual on_menu_detach() method.

	void set_tearoff_state(bool torn_off);
	///< Changes the tearoff state of the menu.
	///< @param torn_off If <EM>true</EM>, the menu is displayed as a tearoff menu.
	///<
	///< A menu is normally displayed as drop down menu which persists as long as the
	///< menu is active. It can also be displayed as a tearoff menu which persists until
	///< it is closed or reattached.

	void set_title(const char *title);
	void set_title(const String& title);
	///< Sets the title string for the menu.
	///< @param title A string containing the title for the menu.
	///<
	///< The title is displayed when the menu is shown as a tearoff menu.

	void reorder_child(const MenuItem& child, int position);
	///< Moves a MenuItem to a new position within the Menu.
	///< @param child The MenuItem to move.
	///< @param position The new position to place child. Positions are numbered from 0 to n-1.

	void set_screen(const Gdk::Screen *screen);
	///< Sets the Gdk::Screen on which the menu will be displayed.
	///< @param screen A Gdk::Screen, or null if the screen should be determined
	///< by the widget the menu is attached to.

	void attach(MenuItem &child, unsigned int left_attach, unsigned int right_attach,
	            unsigned int  top_attach, unsigned int bottom_attach);
	///< Adds a new MenuItem to a (table) menu.
	///< @param child A MenuItem.
	///< @param left_attach The column number to attach the left side of the item to.
	///< @param right_attach The column number to attach the right side of the item to.
	///< @param top_attach The row number to attach the top of the item to.
	///< @param bottom_attach The row number to attach the bottom of the item to.
	///<
	///< The number of 'cells' that an item will occupy is specified by left_attach,
	///< right_attach, top_attach and bottom_attach. These each represent the leftmost,
	///< rightmost, uppermost and lower column and row numbers of the table. (Columns
	///< and rows are indexed from zero).

	void set_monitor(int monitor_num);
	///< Informs GTK+ on which monitor a menu should be popped up
	///< (see Gdk::Screen::get_monitor_geometry()).
	///< @param monitor_num The number of the monitor on which the menu should be popped up.
	///<
	///< This function should be called from a MenuPositionSlot if the
	///< menu should not appear on the same monitor as the pointer. This
	///< information can't be reliably inferred from the coordinates returned
	///< by a MenuPositionSlot, since, for very long menus, these coordinates
	///< may extend beyond the monitor boundaries or even the screen boundaries.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/menu.inl>

#endif // XFC_GTK_MENU_HH

