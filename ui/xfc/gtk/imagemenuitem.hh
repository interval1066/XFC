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

/// @file xfc/gtk/imagemenuitem.hh
/// @brief A GtkImageMenuItem C++ wrapper interface.
///
/// Provides ImageMenuItem, a MenuItem widget that displays an image at the left side of the menu item text.

#ifndef XFC_GTK_MENU_IMAGE_ITEM_HH
#define XFC_GTK_MENU_IMAGE_ITEM_HH

#ifndef XFC_GTK_MENU_ITEM_HH
#include <xfc/gtk/menuitem.hh>
#endif

#ifndef __GTK_MENU_IMAGE_ITEM_H__
#include <gtk/gtkimagemenuitem.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class ImageMenuItem imagemenuitem.hh xfc/gtk/imagemenuitem.hh
/// @brief A GtkImageMenuItem C++ wrapper class.
///
/// ImageMenuItem is a MenuItem widget that displays an image at the left side of the menu item text.

class ImageMenuItem : public MenuItem
{
	friend class G::Object;

	ImageMenuItem(const ImageMenuItem&);
	ImageMenuItem& operator=(const ImageMenuItem&);
	
protected:
/// @name Constructors
/// @{

	explicit ImageMenuItem(GtkImageMenuItem *menu_item, bool owns_reference = false);
	///< Construct a new ImageMenuItem from an existing GtkImageMenuItem.
	///< @param menu_item A pointer to a GtkImageMenuItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>menu_item</EM> can be a newly created GtkImageMenuItem or an existing
	///< GtkImageMenuItem (see G::Object::Object).

/// @}

public:
	typedef GtkImageMenuItem CObjectType;

/// @name Constructors
/// @{

	ImageMenuItem();
	///< Construct a new ImageMenuItem.

	explicit ImageMenuItem(const char *label, bool use_underline = false);
	explicit ImageMenuItem(const String& label, bool use_underline = false);
	///< Constructs a new ImageMenuItem containing a label.
	///< @param label The text of the menu item.
	///< @param use_underline Set <EM>true</EM> if label contains a mnemonic character.
	///<
	///< If characters in label are preceded by an underscore, they are underlined.
	///< If you need a literal underscore character in a label, use '__' (two underscores).
	///< The first underlined character represents a keyboard accelerator called a mnemonic.
	///< Pressing Alt and that key activates the menu item.

	ImageMenuItem(Widget& image, const char *label, bool use_underline = false);
	ImageMenuItem(Widget& image, const String& label, bool use_underline = false);
	///< Constructs a new ImageMenuItem containing an image and a label.
	///< @param image A widget to set as the image for the menu item.
	///< @param label The text of the menu item.
	///< @param use_underline Set <EM>true</EM> if label contains a mnemonic character.
	///<
	///< If characters in label are preceded by an underscore, they are underlined.
	///< If you need a literal underscore character in a label, use '__' (two underscores).
	///< The first underlined character represents a keyboard accelerator called a mnemonic.
	///< Pressing Alt and that key activates the menu item.

	ImageMenuItem(Widget& image, const char *label, Menu& submenu, bool use_underline = false);
	ImageMenuItem(Widget& image, const String& label, Menu& submenu, bool use_underline = false);
	///< Constructs a new ImageMenuItem that displays a submenu.
	///< @param image A widget to set as the image for the menu item.
	///< @param label The text of the menu item.
	///< @param submenu The submenu under this menu item. 
	///< @param use_underline Set <EM>true</EM> if label contains a mnemonic character.
	///<
	///< If characters in label are preceded by an underscore, they are underlined.
	///< If you need a literal underscore character in a label, use '__' (two underscores).
	///< The first underlined character represents a keyboard accelerator called a mnemonic.
	///< Pressing Alt and that key activates the menu item.

	explicit ImageMenuItem(const StockId& stock_id, AccelGroup *accel_group = 0);
	///< Create a new ImageMenuItem containing the image and text from a stock item.
	///< @param stock_id The ID of the stock item.
	///< @param accel_group The AccelGroup to add the menu items accelerator to, or null.
	///<
	///< Some stock ids have preprocessor macros like Gtk::StockId::OK and Gtk::StockId::APPLY.
	///< If you want this menu item to have changeable accelerators, then pass in null for accel_group
	///< and call Gtk::MenuItem::set_accel_path() with an appropriate path for the menu item, then use
	///< Gtk::Stock::lookup() too look up the standard accelerator  for the stock item and if one is
	///< found, call Gtk::AccelMap::add_entry() to register it.
	
	virtual ~ImageMenuItem();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkImageMenuItem* gtk_image_menu_item() const;
	///< Get a pointer to the GtkImageMenuItem structure.

	operator GtkImageMenuItem* () const;
	///< Conversion operator; safely converts an ImageMenuItem to a GtkImageMenuItem pointer.

	Widget* get_image() const;
	///< Gets the widget that is currently set as the image of ImageMenuItem (see set_image()).

/// @}
/// @name Methods
/// @{

	void set_image(Widget& image);
	///< Sets the image of ImageMenuItem to the given widget.
	///< @param image A widget to set as the image for the menu item.

	void set_image(const StockId& stock_id);
	///< Sets the image of ImageMenuItem to the given stock icon.
	///< @param stock_id The ID of the stock icon to set as the image for the menu item.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/imagemenuitem.inl>

#endif // XFC_GTK_MENU_IMAGE_ITEM_HH

