/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  separatortoolitem.cc - GtkSeparatorToolItem C++ wrapper implementation
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

#include "separatortoolitem.hh"
#include "private/separatortoolitemclass.hh"
#include "private/marshal.hh"

using namespace Xfc;

/*  Gtk::SeparatorToolItem
 */

Gtk::SeparatorToolItem::SeparatorToolItem(GtkSeparatorToolItem *item, bool owns_reference)
: ToolItem((GtkToolItem*)item, owns_reference)
{
}

Gtk::SeparatorToolItem::SeparatorToolItem()
: ToolItem((GtkToolItem*)SeparatorToolItemClass::create())
{
}

Gtk::SeparatorToolItem::~SeparatorToolItem()
{
}

/*  Gtk::SeparatorToolItemClass
 */

void
Gtk::SeparatorToolItemClass::init(GtkSeparatorToolItemClass *g_class)
{
	ToolItemClass::init((GtkToolItemClass*)g_class);
}

GType
Gtk::SeparatorToolItemClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_SEPARATOR_TOOL_ITEM, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::SeparatorToolItemClass::create()
{
	return g_object_new(get_type(), 0);
}

