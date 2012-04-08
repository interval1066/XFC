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

/// @file xfc/gtk/toolitemsignals.hh
/// @brief Gtk::ToolItem virtual signal handlers.
///
/// Provides Gtk::ToolItemSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::ToolItem objects.

#ifndef XFC_GTK_TOOL_ITEM_SIGNALS_HH
#define XFC_GTK_TOOL_ITEM_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class ToolItemSignals toolitemsignals.hh xfc/gtk/toolitemsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::ToolItem.

class ToolItemSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	ToolItemSignals(ToolItem *tool_item);
	///< Construct a new ToolItemSignals object.
	///< @param tool_item A ToolItem object inheriting the ToolItemSignals implementation.

	virtual ~ToolItemSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual bool on_create_menu_proxy();
	///< Called when the toolbar is displaying an overflow menu. 
	///< @return <EM>true</EM> if the signal was handled, <EM>false</EM> if not. 	
	///<
	///< In response the tool item should call Gtk::ToolItem::set_proxy_menu_item()
	///< with either with a null pointer and return true to indicate that the item should
	///< not appear in the overflow menu, or with a new menu item and return true, or 
	///< return false to indicate that the signal was not handled by the item. This means
	///< that the item will not appear in the overflow menu unless a later handler installs
	///< a menu item. 

	virtual void on_toolbar_reconfigured();
	///< Called when some property of the toolbar that the item is a child of changes. 
	///< For custom subclasses of Gtk::ToolItem, the default handler of this signal uses
	///< the functions Gtk::Toolbar::get_orientation(), Gtk::Toolbar::get_style(),
	///< Gtk::Toolbar::get_icon_size() and Gtk::Toolbar::get_relief_style() to find out
	///< what the toolbar should look like and change themselves accordingly.

	virtual bool on_set_tooltip(Tooltips& tooltips, const String& tip_text, const String& tip_private);
	///< Called when the toolitem's tooltip changes.
	///< @param tooltips The Gtk::Tooltips. 
	///< @param tip_text The tooltip text. 
	///< @param tip_private The tooltip private text. 
	///< @return <EM>true</EM> if the signal was handled, <EM>false</EM> if not.
	///<
	///< Application developers can use Gtk::ToolItem::set_tooltip() to set the item's tooltip.
	 
/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TOOL_ITEM_SIGNALS_HH

