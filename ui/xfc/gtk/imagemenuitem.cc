/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  imagemenuitem.cc - GtkImageMenuItem C++ wrapper implementation
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
 
#include "imagemenuitem.hh"
#include "accelgroup.hh"
#include "image.hh"
#include "stock.hh"
#include "private/imagemenuitemclass.hh"

using namespace Xfc;

/*  Gtk::ImageMenuItem
 */

Gtk::ImageMenuItem::ImageMenuItem(GtkImageMenuItem *menu_item, bool owns_reference)
: MenuItem((GtkMenuItem*)menu_item, owns_reference)
{
}
	
Gtk::ImageMenuItem::ImageMenuItem()
: MenuItem((GtkMenuItem*)ImageMenuItemClass::create())
{
}

Gtk::ImageMenuItem::ImageMenuItem(const char *label, bool use_underline)
: MenuItem((GtkMenuItem*)ImageMenuItemClass::create())
{
	add_label(label, use_underline);
}

Gtk::ImageMenuItem::ImageMenuItem(const String& label, bool use_underline)
: MenuItem((GtkMenuItem*)ImageMenuItemClass::create())
{
	add_label(label, use_underline);
}

Gtk::ImageMenuItem::ImageMenuItem(Widget& image, const char *label, bool use_underline)
: MenuItem((GtkMenuItem*)ImageMenuItemClass::create())
{
	add_label(label, use_underline);
	set_image(image);
}

Gtk::ImageMenuItem::ImageMenuItem(Widget& image, const String& label, bool use_underline)
: MenuItem((GtkMenuItem*)ImageMenuItemClass::create())
{
	add_label(label, use_underline);
	set_image(image);
}

Gtk::ImageMenuItem::ImageMenuItem(Widget& image, const char *label, Menu& submenu, bool use_underline)
: MenuItem((GtkMenuItem*)ImageMenuItemClass::create())
{
	add_label(label, use_underline);
	set_image(image);
	set_submenu(submenu);
}

Gtk::ImageMenuItem::ImageMenuItem(Widget& image, const String& label, Menu& submenu, bool use_underline)
: MenuItem((GtkMenuItem*)ImageMenuItemClass::create())
{
	add_label(label, use_underline);
	set_image(image);
	set_submenu(submenu);
}

Gtk::ImageMenuItem::ImageMenuItem(const StockId& stock_id, AccelGroup *accel_group)
: MenuItem((GtkMenuItem*)ImageMenuItemClass::create())
{
	StockItem item;
	if (Stock::lookup(stock_id, item))
	{
		add_label(item.label(), true);
		if (accel_group && item.keyval())
			add_accelerator("activate", *accel_group, item.accel_key());
	}
	else
		add_label(stock_id, true);

	set_image(stock_id);
}

Gtk::ImageMenuItem::~ImageMenuItem()
{
}

Gtk::Widget*
Gtk::ImageMenuItem::get_image() const
{
	return G::Object::wrap<Widget>(gtk_image_menu_item_get_image(gtk_image_menu_item()));
}

void
Gtk::ImageMenuItem::set_image(Widget& image)
{
	gtk_image_menu_item_set_image(gtk_image_menu_item(), image.gtk_widget());
}

void 
Gtk::ImageMenuItem::set_image(const StockId& stock_id)
{
	Image *image = new Image(stock_id, ICON_SIZE_MENU);
	set_image(*image);
	image->show();
}

/*  Gtk::ImageMenuItemClass
 */

void
Gtk::ImageMenuItemClass::init(GtkImageMenuItemClass *g_class)
{
	MenuItemClass::init((GtkMenuItemClass*)g_class);
}

GType
Gtk::ImageMenuItemClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_IMAGE_MENU_ITEM, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ImageMenuItemClass::create()
{
	return g_object_new(get_type(), 0);
}

