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

/// @file xfc/gtk/tearoffmenuitem.hh
/// @brief Gtk::TearoffMenuItem virtual signal handlers.
///
/// Provides Gtk::TearoffMenuItemSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::TearoffMenuItem objects.

#ifndef XFC_GTK_MENU_TEAROFF_ITEM_HH
#define XFC_GTK_MENU_TEAROFF_ITEM_HH

#ifndef XFC_GTK_MENU_ITEM_HH
#include <xfc/gtk/menuitem.hh>
#endif

#ifndef __GTK_MENU_TEAROFF_ITEM_H__
#include <gtk/gtktearoffmenuitem.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class TearoffMenuItem tearoffmenuitem.hh xfc/gtk/tearoffmenuitem.hh
/// @brief A GtkTearoffMenuItem C++ wrapper class.
///
/// TearoffMenuItem is a special MenuItem which is used to tear off and reattach its menu.
/// When its menu is shown normally, the TearoffMenuItem is drawn as a dotted line indicating
/// that the menu can be torn off. Activating it causes its menu to be torn off and displayed
/// in its own window as a tearoff menu. When its menu is shown as a tearoff menu, the 
/// TearoffMenuItem is drawn as a dotted line which has a left pointing arrow graphic 
/// indicating that the tearoff menu can be reattached. Activating it will erase the tearoff
/// menu window.
///
/// <B>See also:</B> the <A HREF="../../howto/html/menuitems.html">MenuItem</A> and
/// <A HREF="../../howto/html/menus.html">Menu</A> HOWTOs and example.

class TearoffMenuItem : public MenuItem
{
	friend class G::Object;

	TearoffMenuItem(const TearoffMenuItem&);
	TearoffMenuItem& operator=(const TearoffMenuItem&);
	
protected:
/// @name Constructors
/// @{

	explicit TearoffMenuItem(GtkTearoffMenuItem *tearoff_menu_item, bool owns_reference = false);
	///< Construct a new TearoffMenuItem from an existing GtkTearoffMenuItem.
	///< @param tearoff_menu_item A pointer to a GtkTearoffMenuItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>tearoff_menu_item</EM> can be a newly created GtkTearoffMenuItem or an existing
	///< GtkTearoffMenuItem (see G::Object::Object).

/// @}

public:
	typedef GtkTearoffMenuItem CObjectType;

/// @name Constructors
/// @{

	TearoffMenuItem();
	///< Construct a new tearoff menu item.

	virtual ~TearoffMenuItem();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkTearoffMenuItem* gtk_tearoff_menu_item() const;
	///< Get a pointer to the GtkTearoffMenuItem structure.

	operator GtkTearoffMenuItem* () const;
	///< Conversion operator; safely converts a TearoffMenuItem to a GtkTearoffMenuItem pointer.

	bool is_torn_off() const;
	///< Returns true if the tearoff menu item is torn off.
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/tearoffmenuitem.inl>

#endif // XFC_GTK_MENU_TEAROFF_ITEM_HH

