/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  item.cc - PangoItem C++ wrapper implementation
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
 
#include "item.hh"
#include "attributes.hh"
#include "font.hh"

using namespace Xfc;

/*  Pango::Analysis
 */

PangoEngineShape* 
Pango::Analysis::shape_engine() const
{
	return analysis_.shape_engine;
}

PangoEngineLang* 
Pango::Analysis::lang_engine() const
{
	return analysis_.lang_engine;
}

Pango::Font*
Pango::Analysis::font() const
{
	return G::Object::wrap<Font>(analysis_.font);
}

bool
Pango::Analysis::extra_attributes(std::vector<Pointer<Attribute> >& attrs) const
{
	g_return_val_if_fail(attrs.empty(), false);
	GSList *next = analysis_.extra_attrs;

	while (next)
	{
		Pointer<Attribute> tmp_attribute(new Attribute((PangoAttribute*)next->data, true));
		attrs.push_back(tmp_attribute);
		next = g_slist_next(next);
	}
	return !attrs.empty();
}

/*  Pango::Item
 */

Pango::Item::Item()
: item_(pango_item_new())
{
}

Pango::Item::Item(PangoItem *item, bool copy)
: item_(copy ? pango_item_copy(item) : item)
{
}

Pango::Item::Item(const Item& src)
: item_(pango_item_copy(src.pango_item()))
{
}

Pango::Item::~Item()
{
	if (item_)
	{
		pango_item_free(item_);
		item_ = 0;
	}
}		
	
Pango::Item& 
Pango::Item::operator=(const Item& src)
{
	if (src.item_ == item_)
		return *this;
		
	if (item_)
		pango_item_free(pango_item());

	item_ = pango_item_copy(src.pango_item());
	return *this;
}

const Pango::Analysis&
Pango::Item::analysis() const
{
	return reinterpret_cast<Analysis&>(pango_item()->analysis);
}
	
Pointer<Pango::Item> 
Pango::Item::split(int split_index, int split_offset)
{
	PangoItem *item = pango_item_split(pango_item(), split_index, split_offset);
	return item ? new Item(item, false) : 0;
}

std::vector<Pointer<Pango::Item> >
Pango::reorder_items(const std::vector<Pointer<Item> >& logical_items)
{
	GList *tmp_logical_items = 0;
	int count = logical_items.size();

	int i = 0;
	while (i < count)
	{
		tmp_logical_items = g_list_append(tmp_logical_items, logical_items[i].get());
		++i;
	}

	GList *first = pango_reorder_items(tmp_logical_items);
	GList *next = first;
	std::vector<Pointer<Item> > ordered_items;

	while (next)
	{
		Pointer<Item> item(new Item((PangoItem*)next->data, true));
		ordered_items.push_back(item);
		next = g_list_next(next);
	}

	g_list_free(tmp_logical_items);
	g_list_free(first);
	return ordered_items;
}

