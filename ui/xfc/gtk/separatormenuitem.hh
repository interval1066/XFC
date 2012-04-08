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
 
/// @file xfc/gtk/separatormenuitem.hh
/// @brief A GtkSeparatorMenuItem C++ wrapper interface.
///
/// Provides SeparatorMenuItem, a separator used to group items within a menu.

#ifndef XFC_GTK_SEPARATOR_MENU_ITEM_HH
#define XFC_GTK_SEPARATOR_MENU_ITEM_HH

#ifndef XFC_GTK_MENU_ITEM_HH
#include <xfc/gtk/menuitem.hh>
#endif

#ifndef __GTK_SEPARATOR_MENU_ITEM_H__
#include <gtk/gtkseparatormenuitem.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class SeparatorMenuItem separatormenuitem.hh xfc/gtk/separatormenuitem.hh
/// @brief A GtkSeparatorMenuItem C++ wrapper class.
///
/// The SeparatorMenuItem is a separator used to group items within a menu. It displays
/// a horizontal line with a shadow to make it appear sunken into the interface.
///
/// <B>See also:</B> the <A HREF="../../howto/html/menuitems.html">MenuItem</A> and
/// <A HREF="../../howto/html/menus.html">Menu</A> HOWTOs and example.

class SeparatorMenuItem : public MenuItem
{
	friend class G::Object;
	
	SeparatorMenuItem(const SeparatorMenuItem&);
	SeparatorMenuItem& operator=(const SeparatorMenuItem&);
	
protected:
/// @name Constructors
/// @{

	explicit SeparatorMenuItem(GtkSeparatorMenuItem *menu_item, bool owns_reference = false);
	///< Construct a new SeparatorMenuItem from an existing GtkSeparatorMenuItem.
	///< @param menu_item A pointer to a GtkSeparatorMenuItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>menu_item</EM> can be a newly created GtkSeparatorMenuItem or an existing
	///< GtkSeparatorMenuItem (see G::Object::Object).

/// @}

public:
	typedef GtkSeparatorMenuItem CObjectType;

/// @name Constructors
/// @{

	SeparatorMenuItem();
	///< Construct a new separator menu item.

	
	virtual ~SeparatorMenuItem();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkSeparatorMenuItem* gtk_separator_menu_item() const;
	///< Get a pointer to the GtkSeparatorMenuItem structure.

	operator GtkSeparatorMenuItem* () const;
	///< Conversion operator; safely converts a SeparatorMenuItem to a GtkSeparatorMenuItem pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/separatormenuitem.inl>

#endif // XFC_GTK_SEPARATOR_MENU_ITEM_HH

