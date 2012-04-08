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
 
/// @file xfc/gtk/stock.hh
/// @brief A GtkStockItem C++ wrapper interface.
///
/// Provides Stock and StockItem, an interface to access commonly-used menu
/// or toolbar items such as "Open" or "Exit".

#ifndef XFC_GTK_STOCK_HH
#define XFC_GTK_STOCK_HH

#ifndef XFC_STACK_OBJECT_HH
#include <xfc/stackobject.hh>
#endif

#ifndef XFC_UTF_STRING_HH
#include <xfc/utfstring.hh>
#endif

#ifndef XFC_GDK_TYPES_HH
#include <xfc/gdk/types.hh>
#endif

#ifndef XFC_GTK_STOCK_ID_HH
#include <xfc/gtk/stockid.hh>
#endif

#ifndef _CPP_VECTOR
#include <vector>
#endif

namespace Xfc {

namespace Gtk {

class AccelKey;

/// @class StockItem stock.hh xfc/gtk/stock.hh
/// @brief A GtkStockItem C++ wrapper class.
///
/// Stock items represent commonly-used menu or toolbar items such as "Open" or "Exit".
/// Each stock item is identified by a stock ID; stock IDs are just strings. GTK+ provides
/// macros, such as GTK_STOCK_OPEN, to avoid typing mistakes in the strings. XFC wraps the
/// stock ID's in a class called Gtk::StockId. As well as providing constructors, StockId 
/// provides convenient ready-to-use static StockId objects, one for each pre-registered 
/// GTK+ stock ID, such as Gtk::StockId::OPEN and Gtk::StockId::QUIT. 
///
/// Applications can register their own stock items in addition to those built-in to GTK+.
/// Each stock ID can be associated with a StockItem, which contains the user-visible
/// label, keyboard accelerator, and translation domain of the menu or toolbar item;
/// and/or with an icon stored in an IconFactory. See IconFactory for more information
/// on stock icons. The connection between a StockItem and stock icons is purely 
/// conventional (by virtue of using the same stock ID); it's possible to register a
/// stock item but no icon, and vice versa (see Gtk::StockId).
///
/// StockItem is derived from Xfc::StackObject, a base class that can only be created on the
/// stack and not dynamically on the heap. In the \<demo/gfc-demo\> source directory the
/// application.cc file has an example that registers a new stock item and the stockbrowser.cc
/// file has an example that retrieves the values for registered stock items.

class StockItem : public StackObject
{
	GtkStockItem item_;
	
public:
/// @name Constructors
/// @{	

	StockItem();
	///< Constructs an empty StockItem to initialize with values by calling Gtk::Stock::lookup().

	StockItem(const StockId& stock_id, const char *label, const char *domain = 0);
	StockItem(const StockId& stock_id, const String& label, const String& domain = 0);
	///< Constructs a new StockItem initialized with the specified values; This item
	///< should be registered with Gtk::Stock::add().	
	///< @param stock_id The string identifier for the stock item.
	///< @param label The user-visible label.
	///< @param domain The translation domain.
	///<
	///< If the item already exists with the same stock ID as one of the items,
	///< the old item gets replaced. This stock item will have no accelerator key.

	StockItem(const StockId& stock_id, const char *label, const AccelKey& accel_key, const char *domain = 0);
	StockItem(const StockId& stock_id, const String& label, const AccelKey& accel_key, const String& domain = 0);
	///< Constructs a new StockItem initialized with the specified values; This item
	///< should be registered with Gtk::Stock::add().	
	///< @param stock_id The string identifier for the stock item.
	///< @param label The user-visible label.
	///< @param accel_key An AccelKey that holds the accelerator modifier and key values to set.
	///< @param domain The translation domain.
	///<
	///< If the item already exists with the same stock ID as one of the items,
	///< the old item gets replaced.

	StockItem(const StockId& stock_id, const char *label, Gdk::ModifierTypeField modifier, unsigned int key, const char *domain = 0);
	StockItem(const StockId& stock_id, const String& label, Gdk::ModifierTypeField modifier, unsigned int key, const String& domain = 0);
	///< Constructs a new StockItem initialized with the specified values; This item
	///< should be registered with Gtk::Stock::add().	
	///< @param stock_id The string identifier for the stock item.
	///< @param label The user-visible label.
	///< @param modifier The modifier combination of the accelerator.
	///< @param key The key value of the accelerator
	///< @param domain The translation domain.
	///<
	///< If the item already exists with the same stock ID as one of the items,
	///< the old item gets replaced.

	StockItem(const StockItem& src);
	///< Copy constructor.
	///< @param src Another stock item.
	
	~StockItem();
	///< Destructor.

	StockItem& operator=(const StockItem& src);
	///< Assignment operator
	///< @param src Another stock item.
	///< @return A reference to the modified stock item, after assignment.

/// @}
/// @name Accessors
/// @{

	GtkStockItem* gtk_stock_item() const;
	///< Get a pointer to the GtkStockItem structure.

	StockId stock_id() const;
	///< Returns the stock_id for the stock item.

	const char* label() const;
	///< Returns the user-visible label for the stock item.

	Gdk::ModifierTypeField modifier() const;
	///< Gets the modifier combination of the keyboard accelerator for the stock item.

	unsigned int keyval() const;
	///< Gets the key value of the keyboard accelerator for the stock item.

	const char* translation_domain() const;
	///< Returns the translation domain for the stock item.

	AccelKey accel_key() const;
	///< Returns an AccelKey object for the keyboard accelerator.

/// @}
/// @name Methods
/// @{

	void set(const StockId& stock_id, const char *label, Gdk::ModifierTypeField modifier, unsigned int key, const char *domain);
	void set(const StockId& stock_id, const String& label, Gdk::ModifierTypeField modifier, unsigned int key, const String& domain);
	///< Sets the values for the stock item.
	///< @param stock_id The string identifier for the stock item.
	///< @param label The user-visible label.
	///< @param modifier The modifier combination of the accelerator.
	///< @param key The key value of the accelerator
	///< @param domain The translation domain.
	
/// @}
};

/// @class Stock stock.hh xfc/gtk/stock.hh
/// @brief A C++ wrapper class for various stock methods.
///
/// Stock is a convenience class that wraps the miscellaneous GTK+ stock functions.

class Stock
{
public:
/// @name Methods
/// @{

	static void add(const StockItem& item);
	///< Registers a stock item.
	///< @param item The stock item to register.
	///<
	///< If the item already exists with the same stock ID as one of the items,
	///< the old item gets replaced. 

	static bool lookup(const StockId& stock_id, StockItem& item);
	///< Fills <EM>item</EM> with the registered values for stock_id, returning true if stock_id was known.
	///< @param stock_id The stock id for the stock item.
	///< @param item A stock item to initialize with values.
	///< @return <EM>true</EM> if item was initialized.

	static std::vector<StockId> list_ids();
	///< Retrieves a list of all known stock IDs added to an IconFactory or registered with add().
	///< @return A vector of StockId that holds the list of known stock IDs.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/stock.inl>

#endif // XFC_GTK_STOCK_HH

