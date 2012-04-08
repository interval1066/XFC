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

/// @file xfc/gtk/separatortoolitem.hh
/// @brief A GtkSeparatorToolItem C++ wrapper interface.
///
/// Provides SeparatorToolItem, a toolbar item that separates groups of other toolbar items. 

#ifndef XFC_GTK_SEPARATOR_TOOL_ITEM_HH
#define XFC_GTK_SEPARATOR_TOOL_ITEM_HH

#ifndef XFC_GTK_TOOL_ITEM_HH
#include <xfc/gtk/toolitem.hh>
#endif

#ifndef __GTK_SEPARATOR_TOOL_ITEM_H__
#include <gtk/gtkseparatortoolitem.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class SeparatorToolItem separatortoolitem.hh xfc/gtk/separatortoolitem.hh
/// @brief A GtkSeparatorToolItem C++ wrapper class.
///
/// SeparatorToolItem is a tool item that separates groups of other ToolItems. 
/// Depending on the theme, a SeparatorToolItem will often look like a vertical
/// line on horizontally docked toolbars.
///
/// If the property 'expand' is <EM>true</EM> and the property 'draw' is <EM>false</EM>,
/// a SeparatorToolItem will act as a "spring" that forces other items to the ends of
/// the toolbar. 
///
/// <B>See also:</B> the <A HREF="../../howto/html/toolitems.html">ToolItems</A> HOWTO.

class SeparatorToolItem : public ToolItem
{
	friend class G::Object;

	SeparatorToolItem(const SeparatorToolItem&);
	SeparatorToolItem& operator=(const SeparatorToolItem&);

protected:
/// @name Constructors
/// @{

	explicit SeparatorToolItem(GtkSeparatorToolItem *item, bool owns_reference = false);
	///< Construct a new SeparatorToolItem from an existing GtkSeparatorToolItem.
	///< @param item A pointer to a GtkSeparatorToolItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>item</EM> can be a newly created GtkSeparatorToolItem or an existing 
	///< SeparatorToolItem (see G::Object::Object).

/// @}

public:
	typedef GtkSeparatorToolItem CObjectType;

/// @name Constructors
/// @{

	SeparatorToolItem();
	///< Constructs a new separator tool item.

	virtual ~SeparatorToolItem();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkSeparatorToolItem* gtk_separator_tool_item() const;
	///< Get a pointer to the GtkSeparatorToolItem structure.

	operator GtkSeparatorToolItem* () const;
	///< Conversion operator; safely converts an SeparatorToolItem to a GtkSeparatorToolItem pointer.

	bool get_draw() const;
	///< Determines whether the separator tool item is drawn as a line, or just blank (see set_draw()).
	///< @return <EM>true</EM> if the separator tool item is drawn as a line.
	
/// @}
/// @name Methods
/// @{

	void set_draw(bool draw);
	///< Sets whether the separator tool item is drawn as a vertical line, or just blank. 
	///< @param draw Whether the separator tool item is drawn as a vertical line.
	///<	
	///< Setting <EM>draw</EM> false along with Gtk::ToolItem::set_expand() is useful
	///< to create an item that forces following items to the end of the toolbar.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/separatortoolitem.inl>

#endif // XFC_GTK_SEPARATOR_TOOL_ITEM_HH

