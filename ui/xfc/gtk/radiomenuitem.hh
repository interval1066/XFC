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
 
/// @file xfc/gtk/radiomenuitem.hh
/// @brief A GtkRadioMenuItem C++ wrapper interface.
///
/// Provides RadioMenuItem, a menu item widget that belongs to a group. At each instant exactly one
/// of the radio menu items from a group is selected. 

#ifndef XFC_GTK_RADIO_MENU_ITEM_HH
#define XFC_GTK_RADIO_MENU_ITEM_HH

#ifndef XFC_GTK_MENU_CHECK_ITEM_HH
#include <xfc/gtk/checkmenuitem.hh>
#endif

#ifndef __GTK_RADIO_MENU_ITEM_H__
#include <gtk/gtkradiomenuitem.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class RadioMenuItem radiomenuitem.hh xfc/gtk/radiomenuitem.hh
/// @brief A GtkRadioMenuItem C++ wrapper class.
///
/// A radio menu item is a check menu item that belongs to a group. At each instant exactly one
/// of the radio menu items from a group is selected. You create a group radio menu items the 
/// same way you would create a group of buttons (see Gtk::RadioButton).
///
/// Radio menu items are constructed with one of the following constructors:
///
/// @code
/// RadioMenuItem(const RadioMenuItem *group, const char *label, bool use_underline = false);
/// RadioMenuItem(const RadioMenuItem *group, const String& label, bool use_underline = false);
/// @endcode
///
/// The group argument is a pointer to an existing RadioMenuItem that already has a group
/// assigned to it. The first radio menu item in a group is constructed by passing null as
/// the group argument. Then subsequent menu items are constructed by passing an existing
/// menu item as the group argument, usually the last one constructed.
///
/// @code
/// Gtk::RadioMenuItem *menu_item = 0;
/// menu_item = new Gtk::RadioMenuItem(menu_item, "Item1");
/// menu->append(*menu_Rangeitem, item1_slot);
/// menu_item->show();
///
/// menu_item = new Gtk::RadioMenuItem(menu_item, "Item2");
/// menu->append(*menu_item, item2_slot);
/// menu_item->show();
///
/// menu_item = new Gtk::RadioMenuItem(menu_item, "Item3");
/// menu->append(*menu_item, item3_slot);
/// menu_item->show();
/// @endcode
///
/// To remove a RadioMenuItem from one group and make it part of a new one, use set_group().
///
/// <B>See also:</B> the <A HREF="../../howto/html/menuitems.html">MenuItem</A> and
/// <A HREF="../../howto/html/menus.html">Menu</A> HOWTOs and example.

class RadioMenuItem : public CheckMenuItem
{
	friend class G::Object;

	RadioMenuItem(const RadioMenuItem&);
	RadioMenuItem& operator=(const RadioMenuItem&);
	
protected:
/// @name Constructors
/// @{

	explicit RadioMenuItem(GtkRadioMenuItem *radio_menu_item, bool owns_reference = false);
	///< Construct a new RadioMenuItem from an existing GtkRadioMenuItem.
	///< @param radio_menu_item A pointer to a GtkRadioMenuItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>radio_menu_item</EM> can be a newly created GtkRadioMenuItem or an existing
	///< GtkRadioMenuItem (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> GroupChangedSignalType;
	typedef G::SignalProxy<TypeInstance, GroupChangedSignalType> GroupChangedSignalProxy;
	static const GroupChangedSignalType group_changed_signal;
	///< Group changed signal (see signal_group_changed()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkRadioMenuItem CObjectType;
	
	typedef GSList Group;
	///< The radio menu item group.

/// @name Constructors
/// @{

	RadioMenuItem();
	///< Construct a new radio menu item.

	explicit RadioMenuItem(const RadioMenuItem *group);
	///< Construct a new radio menu item. 
	///< @param group An exisitng radio menu item. 

	RadioMenuItem(const RadioMenuItem *group, const char *label, bool use_underline = false);
	RadioMenuItem(const RadioMenuItem *group, const String& label, bool use_underline = false);
	///< Constructs a new radio menu item that is a member of <EM>group</EM>. 
	///< @param group An exisitng radio menu item, or null to start a new group. 
	///< @param label The text for the label 
	///< @param use_underline Set <EM>true</EM> if label contains a mnemonic character.

	virtual ~RadioMenuItem();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkRadioMenuItem* gtk_radio_menu_item() const;
	///< Get a pointer to the GtkRadioMenuItem structure.
	
	operator GtkRadioMenuItem* () const;
	///< Conversion operator; safely converts a RadioMenuItem to a GtkRadioMenuItem pointer.
	
	Group* get_group() const;
	///< Returns the group to which the radio menu item belongs.

/// @}
/// @name Methods
/// @{

	void set_group(Group *group);
	///< Sets the group of a radio menu item, or changes it. 
	///< @param group The new group. 
 	
/// @}
/// @name Signal Proxies
/// @{

	const GroupChangedSignalProxy signal_group_changed();
	///< Connect to the group_changed_signal; emitted when the group of radio menu items
	///< that a radio menu item belongs to changes. This can be when a radio menu item
	///< switches from being alone to being part of a group of 2 or more menu items, or
	///< vice-versa, and when a button is moved from one group of 2 or more menu items
	///< to a different one, but not when the composition of the group that a menu item
	///< belongs to changes.

/// @}
};
	
} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/radiomenuitem.inl>

#endif // XFC_GTK_RADIO_MENU_ITEM_HH

