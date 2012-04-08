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
 
/// @file xfc/gtk/item.hh
/// @brief A GtkItem C++ wrapper interface.
///
/// Provides Item, a widget which is an abstract base class for MenuItem.

#ifndef XFC_GTK_ITEM_HH
#define XFC_GTK_ITEM_HH

#ifndef XFC_GTK_BIN_HH
#include <xfc/gtk/bin.hh>
#endif

#ifndef __GTK_ITEM_H__
#include <gtk/gtkitem.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class Item item.hh xfc/gtk/item.hh
/// @brief A GtkItem C++ wrapper class.
///
/// The Item widget is an abstract base class for MenuItem.

class Item : public Bin
{
	friend class G::Object;

	Item(const Item&);
	Item& operator=(const Item&);
	
protected:
/// @name Constructors
/// @{

	explicit Item(GtkItem *item, bool owns_reference = false);
	///< Construct a new Item from an existing GtkItem.
	///< @param item A pointer to a GtkItem.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>item</EM> can be a newly created GtkItem or an existing
	///< GtkItem (see G::Object::Object).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> SelectSignalType;
	typedef G::SignalProxy<TypeInstance, SelectSignalType> SelectSignalProxy;
	static const SelectSignalType select_signal;
	///< Select signal (see signal_select()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> DeselectSignalType;
	typedef G::SignalProxy<TypeInstance, DeselectSignalType> DeselectSignalProxy;
	static const DeselectSignalType deselect_signal;
	///< Deselect signal (see signal_deselect()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void> ToggleSignalType;
	typedef G::SignalProxy<TypeInstance, ToggleSignalType> ToggleSignalProxy;
	static const ToggleSignalType toggle_signal;
	///< Toggle signal (see signal_toggle()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

/// @}

public:
	typedef GtkItem CObjectType;

/// @name Constructors
/// @{
	virtual ~Item();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkItem* gtk_item() const;
	///< Get a pointer to the GtkItem structure.

	operator GtkItem* () const;
	///< Conversion operator; safely converts an Item to a GtkItem pointer.

/// @}
/// @name Methods
/// @{

	void select();
	///< Emits the "select" signal on Item.

	void deselect();
	///< Emits the "deselect" signal on Item.

	void toggle();
	///< Emits the "toggle" signal on Item.

/// @}
/// @name Signal Proxies
/// @{
	
	const SelectSignalProxy signal_select();
	///< Connect to the select_signal; emitted when the item is selected.


	const DeselectSignalProxy signal_deselect();
	///< Connect to the deselect_signal; emitted when the item is deselected.

	const ToggleSignalProxy signal_toggle();
	///< Connect to the toggle_signal; emitted when the item is toggled.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/item.inl>

#endif // XFC_GTK_ITEM_HH

