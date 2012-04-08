/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
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
 
/// @file xfc/gtk/menutoolbutton.hh
/// @brief A GtkMenuToolButton C++ wrapper interface.
///
/// Provides MenuToolButton, a ToolItem containing a button with an additional dropdown menu.

#ifndef XFCE_GTK_MENU_TOOL_BUTTON_HH
#define XFC_GTK_MENU_TOOL_BUTTON_HH

#ifndef XFC_GTK_TOOL_BUTTON_HH
#include <xfc/gtk/toolbutton.hh>
#endif

#ifndef __GTK_MENU_TOOL_BUTTON_H__
#include <gtk/gtkmenutoolbutton.h>
#endif

namespace Xfc {

namespace Gtk {

class Menu;
class Tooltips;

/// @class MenuToolButton menutoolbutton.hh xfc/gtk/menutoolbutton.hh
/// @brief A GtkMenuToolButton C++ wrapper class.
///
/// MenuToolButton is a ToolItem that contains a button and a small additional
/// button with an arrow. When clicked, the arrow button pops up a dropdown menu. 

class MenuToolButton : public ToolButton
{
	friend class G::Object;
	
	MenuToolButton(const MenuToolButton&);
	MenuToolButton& operator=(const MenuToolButton&);
	
protected:
/// @name Constructors
/// @{

	explicit MenuToolButton(GtkMenuToolButton *button, bool owns_reference = false);
	///< Construct a new MenuToolButton from an existing GtkMenuToolButton.
	///< @param button A pointer to a GtkMenuToolButton.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>button</EM> can be a newly created GtkMenuToolButton or an existing
	///< GtkMenuToolButton. (see G::Object::Object).
	
/// @}
public:
	typedef GtkMenuToolButton CObjectType;

/// @name Constructors
/// @{
	
	MenuToolButton();
	///< Constructs an empty menu tool button.

	MenuToolButton(Widget& icon_widget);
	///< Constructs a new menu tool button using <EM>icon_widget</EM> as the icon.
	///< @param icon_widget A widget that will be used as the icon widget.
	
	MenuToolButton(const char *label, bool use_underline = false);
	MenuToolButton(const String& label, bool use_underline = false);
	///< Constructs a new menu tool button using <EM>label</EM> as the label.
	///< @param label A string that will be used as the label.
	///< @param use_underline Whether the button label has the mnemonic form "_Open". 
	
	MenuToolButton(Widget& icon_widget, const char *label, bool use_underline = false);
	MenuToolButton(Widget& icon_widget, const String& label, bool use_underline = false);
	///< Constructs a new menu tool button using <EM>label</EM> as the label.
	///< @param icon_widget A widget that will be used as the icon widget.
	///< @param label A string that will be used as the label.
	///< @param use_underline Whether the button label has the mnemonic form "_Open". 
	
	MenuToolButton(const StockId& stock_id);
	///< Constructs a new menu tool button containing the image and text from a stock item.
	///< @param stock_id The ID of the stock item (see set_stock_id()).
	///<
	///< It is an error if <EM>stock_id</EM> is not a name of a stock item.
	
	virtual ~MenuToolButton();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkMenuToolButton* gtk_menu_tool_button() const;
	///< Get a pointer to the GtkMenuToolButton structure.

	operator GtkMenuToolButton* () const;
	///< Conversion operator; safely converts an MenuToolButton to a GtkMenuToolButton pointer.

	Menu* get_menu() const;
	///< Gets the Menu associated with the MenuToolButton.
	///< @return The Menu associated with MenuToolButton.
	
/// @}
/// @name Methods
/// @{

	void set_menu(Menu *menu);
	///< Sets the Menu that is popped up when the user clicks on the arrow. 
	///< @param menu The Gtk::Menu associated with MenuToolButton.
	///<	
	///< If menu is null, the arrow button becomes insensitive.

	void set_arrow_tooltip(Tooltips& tooltips, const char *tip_text, const char *tip_private);
	void set_arrow_tooltip(Tooltips& tooltips, const String& tip_text, const String& tip_private);
	///< Sets the Tooltips object to be used for the arrow button which pops up the menu. 
	///< @param tooltips  The Tooltips object to be used.
	///< @param tip_text The text to be used as tooltip text for tool_item.
	///< @param tip_private The text to be used as private tooltip text.
	///<	
	///< To set the tooltip on the whole MenuToolButton see Gtk:ToolItem::set_tooltip().
 
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/menutoolbutton.inl>

#endif // XFC_GTK_MENU_TOOL_BUTTON_HH

