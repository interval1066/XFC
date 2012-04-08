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
 
/// @file xfc/gtk/checkmenuitem.hh
/// @brief A GtkCheckMenuItem C++ wrapper interface.
///
/// Provides CheckMenuItem, a menu item with a check box.

#ifndef XFC_GTK_MENU_CHECK_ITEM_HH
#define XFC_GTK_MENU_CHECK_ITEM_HH

#ifndef XFC_GTK_MENU_ITEM_HH
#include <xfc/gtk/menuitem.hh>
#endif

#ifndef __GTK_MENU_CHECK_ITEM_H__
#include <gtk/gtkcheckmenuitem.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class CheckMenuItem checkmenuitem.hh xfc/gtk/checkmenuitem.hh
/// @brief A GtkCheckMenuItem C++ wrapper class.
///
/// A CheckMenuItem is a menu item that maintains the state of a bool value 
/// in addition to a MenuItem's usual role in activating application code.
/// A check box indicating the state of the bool value is displayed at the
/// left side of the MenuItem. Activating the MenuItem toggles the value.
///
/// <B>See also:</B> the <A HREF="../../howto/html/menuitems.html">MenuItem</A> and
/// <A HREF="../../howto/html/menus.html">Menu</A> HOWTOs and example.

class CheckMenuItem : public MenuItem
{
	friend class G::Object;

	CheckMenuItem(const CheckMenuItem&);
	CheckMenuItem& operator=(const CheckMenuItem&);

protected:
/// @name Constructors
/// @{

	explicit CheckMenuItem(GtkCheckMenuItem *check_menu_item, bool owns_reference = false);
	///< Construct a new CheckMenuItem from an existing GtkCheckMenuItem.
	///< @param check_menu_item A pointer to a GtkCheckMenuItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>check_menu_item</EM> can be a newly created GtkCheckMenuItem or an existing
	///< GtkCheckMenuItem. (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{
	
	typedef G::Signal<void> ToggledSignalType;
	typedef G::SignalProxy<TypeInstance, ToggledSignalType> ToggledSignalProxy;
	static const ToggledSignalType toggled_signal;
	///< Toggled signal (see signal_toggled()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode
/// @}

public:
	typedef GtkCheckMenuItem CObjectType;

/// @name Constructors
/// @{

	CheckMenuItem();
	///< Construct a new CheckMenuItem.

	explicit CheckMenuItem(const char *label, bool use_underline = false);
	explicit CheckMenuItem(const String& label, bool use_underline = false);
	///< Construct a new CheckMenuItem with a Label to the right of it.
	///< @param label The text for the menu item.
	///< @param use_underline <EM>true</EM> if the label contains an underscore, indicating a mnemonic.
	///<
	///< If <EM>use_underline</EM> is true an underscore in label indicates that the next
	///< character is the mnemonic accelerator for the menu item.

	virtual ~CheckMenuItem();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkCheckMenuItem* gtk_check_menu_item() const;
	///< Get a pointer to the GtkCheckMenuItem structure.

	operator GtkCheckMenuItem* () const;
	///< Conversion operator; safely converts a CheckMenuItem to a GtkCheckMenuItem pointer.

	bool get_active() const;
	///< Returns true if the check menu item is active (see set_active()).

	bool get_inconsistent() const;
	///< Returns true if the check menu item is in an "in between" state.

	bool get_draw_as_radio() const;
	///< Determines whether the check menu item looks like a Gtk::RadioMenuItem.
	///< @return <EM>true</EM> if the check menu item looks like a Gtk::RadioMenuItem.

/// @}
/// @name Methods
/// @{

	void set_active(bool is_active);
	///< Sets the active state of the menu item's check box.
	/// @param is_active A bool value indicating whether the check box is active.
	
	void set_inconsistent(bool setting);
	///< Display the check in an "in between" state.
	/// @param setting <EM>true</EM> to display an "inconsistent" third state check.
	///<
	///< If the user has selected a range of elements (such as some text or spreadsheet
	///< cells) that are affected by a boolean setting, and the current values in that
	///< range are inconsistent, you may want to display the check in an "in between"
	///< state. This function turns on "in between" display. Normally you would turn off
	///< the inconsistent state again if the user explicitly selects a setting. This has
	///< to be done manually, set_inconsistent() only affects visual appearance, it 
	///< doesn't affect the semantics of the widget.

	void set_draw_as_radio(bool draw_as_radio);
	///< Sets whether <EM>check_menu_item</EM> is drawn like a Gtk::RadioMenuItem.
	///< @param draw_as_radio Set <EM>true</EM> to draw the check menu item like a Gtk::RadioMenuItem.

	void toggled();
	///< Emits the "toggled" signal.

/// @}
/// @name Signal Proxies
/// @{

	const ToggledSignalProxy signal_toggled();
	///< Connect to the toggled_signal; emitted when the state of the check box is changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/checkmenuitem.inl>

#endif // XFC_GTK_MENU_CHECK_ITEM_HH

