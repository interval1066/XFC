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
 
/// @file xfc/gtk/menubar.hh
/// @brief A GtkMenuBar C++ wrapper interface.
///
/// Provides MenuBar, a widget subclass of MenuShell which contains one to many MenuItem.
/// The result is a standard menu bar which can hold many menu items.

#ifndef XFC_GTK_MENU_BAR_HH
#define XFC_GTK_MENU_BAR_HH

#ifndef XFC_GTK_MENU_SHELL_HH
#include <xfc/gtk/menushell.hh>
#endif

#ifndef __GTK_MENU_BAR_H__
#include <gtk/gtkmenubar.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class MenuBar menubar.hh xfc/gtk/menubar.hh
/// @brief A GtkMenuBar C++ wrapper class.
///
/// The MenuBar is a subclass of MenuShell which contains one or more MenuItem.
/// The result is a standard menu bar which can hold many menu items. MenuBar
/// allows for a shadow type to be set for aesthetic purposes.
///
/// <B>See also:</B> the <A HREF="../../howto/html/menus.html">Menu</A> and
/// <A HREF="../../howto/html/menuitems.html">MenuItem</A> HOWTOs and example.

class MenuBar : public MenuShell
{
	friend class G::Object;

	MenuBar(const MenuBar&);
	MenuBar& operator=(const MenuBar&);
	
protected:
/// @name Constructors
/// @{

	explicit MenuBar(GtkMenuBar *menu_bar, bool owns_reference = false);
	///< Construct a new MenuBar from an existing GtkMenuBar.
	///< @param menu_bar A pointer to a GtkMenuBar.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>menu_bar</EM> can be a newly created GtkMenuBar or an existing
	///< GtkMenuBar (see G::Object::Object).

/// @}

public:
	typedef GtkMenuBar CObjectType;

/// @name Constructors
/// @{

	MenuBar();
	///< Construct a new MenuBar.

	virtual ~MenuBar();
	///< Destructor.
	
/// @}
/// @name Accessors

	GtkMenuBar* gtk_menu_bar() const;
	///< Get a pointer to the GtkMenuBar structure.

	operator GtkMenuBar* () const;
	///< Conversion operator; safely converts a MenuBar to a GtkMenuBar pointer.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/menubar.inl>

#endif // XFC_GTK_MENU_BAR_HH

