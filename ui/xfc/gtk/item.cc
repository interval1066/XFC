/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  item.cc - GtkItem C++ wrapper implementation
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
#include "itemsignals.hh"
#include "private/itemclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::Item
 */

Gtk::Item::Item(GtkItem *item, bool owns_reference)
: Bin((GtkBin*)item, owns_reference)
{
}

Gtk::Item::~Item()
{
}

/*  Gtk::ItemClass
 */

void
Gtk::ItemClass::init(GtkItemClass *g_class)
{
	BinClass::init((GtkBinClass*)g_class);
	g_class->select = &select_proxy;
	g_class->deselect = &deselect_proxy;
	g_class->toggle = &toggle_proxy;
}

GtkItemClass*
Gtk::ItemClass::get_parent_class(void *instance)
{
	return static_cast<GtkItemClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gtk::ItemClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_ITEM, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ItemClass::create()
{
	return g_object_new(get_type(), 0);
}

void
Gtk::ItemClass::select_proxy(GtkItem *item)
{
	ItemSignals *signals = dynamic_cast<ItemSignals*>(G::ObjectSignals::pointer((GObject*)item));
	if (signals)
		signals->on_select();
	else
	{
		GtkItemClass *g_class = get_parent_class(item);
		if (g_class && g_class->select)
			g_class->select(item);
	}
}

void
Gtk::ItemClass::deselect_proxy(GtkItem *item)
{
	ItemSignals *signals = dynamic_cast<ItemSignals*>(G::ObjectSignals::pointer((GObject*)item));
	if (signals)
		signals->on_deselect();
	else
	{
		GtkItemClass *g_class = get_parent_class(item);
		if (g_class && g_class->deselect)
			g_class->deselect(item);
	}
}

void
Gtk::ItemClass::toggle_proxy(GtkItem *item)
{
	ItemSignals *signals = dynamic_cast<ItemSignals*>(G::ObjectSignals::pointer((GObject*)item));
	if (signals)
		signals->on_toggle();
	else
	{
		GtkItemClass *g_class = get_parent_class(item);
		if (g_class && g_class->toggle)
			g_class->toggle(item);
	}
}

/*  Gtk::Item Signals
 */

const Gtk::Item::SelectSignalType Gtk::Item::select_signal("select", (GCallback)&G::Marshal::void_callback);

const Gtk::Item::DeselectSignalType Gtk::Item::deselect_signal("deselect", (GCallback)&G::Marshal::void_callback);

const Gtk::Item::ToggleSignalType Gtk::Item::toggle_signal("toggle", (GCallback)&G::Marshal::void_callback);

