/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  stock.cc - GtkStockItem C++ wrapper implementation
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

#include "stock.hh"
#include "accelgroup.hh"
#include <glib/gstrfuncs.h>
#include <cstring>

using namespace Xfc;

/*  Gtk::StockItem
 */

Gtk::StockItem::StockItem()
{
	set(0, 0, 0, 0, 0);
}

Gtk::StockItem::StockItem(const StockId& stock_id, const char *label, const char *domain)
{
	set(stock_id, label, 0, 0, domain);
}
	
Gtk::StockItem::StockItem(const StockId& stock_id, const String& label, const String& domain)
{
	set(stock_id, label, 0, 0, domain);
}

Gtk::StockItem::StockItem(const StockId& stock_id, const char *label, const AccelKey& accel_key, const char *domain)
{
	set(stock_id, label, accel_key.mods(), accel_key.key(), domain);
}
	
Gtk::StockItem::StockItem(const StockId& stock_id, const String& label, const AccelKey& accel_key, const String& domain)
{
	set(stock_id, label, accel_key.mods(), accel_key.key(), domain);
}

Gtk::StockItem::StockItem(const StockId& stock_id, const char *label, Gdk::ModifierTypeField modifier, unsigned int key, const char *domain)
{
	set(stock_id, label, modifier, key, domain);
}
	
Gtk::StockItem::StockItem(const StockId& stock_id, const String& label, Gdk::ModifierTypeField modifier, unsigned int key, const String& domain)
{
	set(stock_id, label, modifier, key, domain);
}

Gtk::StockItem::StockItem(const StockItem& src)
{
	set(src.item_.stock_id, src.item_.label, src.item_.modifier, src.item_.keyval, src.item_.translation_domain);
}
	
Gtk::StockItem::~StockItem()
{
	if (item_.stock_id)
		g_free(item_.stock_id);
	if (item_.label)
		g_free(item_.label);
	if (item_.translation_domain)
		g_free(item_.translation_domain);
}

Gtk::StockItem& 
Gtk::StockItem::operator=(const StockItem& src)
{
	if (&src.item_ == &item_)
		return *this;
		
	if (item_.stock_id)
		g_free(item_.stock_id);
	if (item_.label)
		g_free(item_.label);
	if (item_.translation_domain)
		g_free(item_.translation_domain);
		
	set(src.item_.stock_id, src.item_.label, src.item_.modifier, src.item_.keyval, src.item_.translation_domain);
	return *this;
}

Gtk::AccelKey
Gtk::StockItem::accel_key() const
{
	return AccelKey(keyval(), modifier());
}

void 
Gtk::StockItem::set(const StockId& stock_id, const char *label, Gdk::ModifierTypeField modifier, unsigned int key, const char *domain)
{
	item_.stock_id = g_strdup(stock_id.c_str());
	item_.label = label ? g_strdup(label) : 0;
	item_.modifier = (GdkModifierType)modifier;
	item_.keyval = key;
	item_.translation_domain = domain ? g_strdup(domain) : 0;
}

void 
Gtk::StockItem::set(const StockId& stock_id, const String& label, Gdk::ModifierTypeField modifier, unsigned int key, const String& domain)
{
	set(stock_id, label.c_str(), modifier, key, domain.c_str());
}

/*  Gtk::Stock
 */

void
Gtk::Stock::add(const StockItem& item)
{
	gtk_stock_add(item.gtk_stock_item(), 1);
}

bool
Gtk::Stock::lookup(const StockId& stock_id, StockItem& item)
{
	GtkStockItem tmp_item;	
	bool result = gtk_stock_lookup(stock_id, &tmp_item);
	item.set(tmp_item.stock_id, tmp_item.label, tmp_item.modifier, tmp_item.keyval, tmp_item.translation_domain); 
	return result;
}

std::vector<Gtk::StockId>
Gtk::Stock::list_ids()
{
	std::vector<StockId> ids;
	GSList *first = g_slist_sort(gtk_stock_list_ids(), (GCompareFunc) strcmp);
	GSList *next = first;

	while (next)
	{
		char *stock_id = (char*)next->data;
		ids.push_back(stock_id);
		g_free(stock_id);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return ids;
}

