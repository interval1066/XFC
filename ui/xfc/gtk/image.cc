/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  image.cc - GtkImage C++ wrapper implementation
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
 
#include "image.hh"
#include "iconfactory.hh"
#include "stockid.hh"
#include "private/imageclass.hh"
#include "../gdk/pixmap.hh"
#include "../gdk/bitmap.hh"
#include "../gdk/image.hh"
#include "../gdk-pixbuf/pixbuf.hh"
#include "../gdk-pixbuf/pixbuf-animation.hh"

using namespace Xfc;

/*  Gtk::Image
 */

Gtk::Image::Image(GtkImage *image, bool owns_reference)
: Misc((GtkMisc*)image, owns_reference)
{
}

Gtk::Image::Image()
: Misc((GtkMisc*)ImageClass::create())
{
}

Gtk::Image::Image(Gdk::Pixmap& pixmap, Gdk::Bitmap& mask) 
: Misc((GtkMisc*)ImageClass::create())
{
	set(&pixmap, &mask);
}

Gtk::Image::Image(Gdk::Image& image, Gdk::Bitmap& mask) 
: Misc((GtkMisc*)ImageClass::create())
{
	set(&image, &mask);
}

Gtk::Image::Image(const char *filename)
: Misc((GtkMisc*)ImageClass::create())
{
	set(filename);
}

Gtk::Image::Image(const String& filename)
: Misc((GtkMisc*)ImageClass::create())
{
	set(filename);
}

Gtk::Image::Image(Gdk::Pixbuf& pixbuf)
: Misc((GtkMisc*)ImageClass::create())
{
	set(&pixbuf);
}

Gtk::Image::Image(const char **xpm_data) 
: Misc((GtkMisc*)ImageClass::create())
{
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_xpm_data(xpm_data);
	gtk_image_set_from_pixbuf(gtk_image(), pixbuf);
	g_object_unref(pixbuf);
}

Gtk::Image::Image(const StockId& stock_id, IconSize size)
: Misc((GtkMisc*)ImageClass::create())
{
	set(stock_id, size);
}

Gtk::Image::Image(IconSet& icon_set, IconSize size)
: Misc((GtkMisc*)ImageClass::create())
{
	set(&icon_set, size);
}

Gtk::Image::Image(Gdk::PixbufAnimation& animation)
: Misc((GtkMisc*)ImageClass::create())
{
	set(animation);
}

Gtk::Image::Image(const char *icon_name, IconSize size)
: Misc((GtkMisc*)ImageClass::create())
{
	set(icon_name, size);
}

Gtk::Image::Image(const String& icon_name, IconSize size)
: Misc((GtkMisc*)ImageClass::create())
{
	set(icon_name, size);
}
	
Gtk::Image::~Image()
{
}

void
Gtk::Image::get_pixmap(Gdk::Pixmap **pixmap, Gdk::Bitmap **mask) const
{
	GdkPixmap *tmp_pixmap = 0;
	GdkBitmap *tmp_mask = 0;
	gtk_image_get_pixmap(gtk_image(), &tmp_pixmap, &tmp_mask);

	if (pixmap && tmp_pixmap)
		*pixmap = G::Object::wrap<Gdk::Pixmap>(tmp_pixmap);

	if (mask && tmp_mask)
		*mask = G::Object::wrap<Gdk::Bitmap>(tmp_mask);
}

void
Gtk::Image::get_image(Gdk::Image **gdk_image, Gdk::Bitmap **mask) const
{
	GdkImage *tmp_image = 0;
	GdkBitmap *tmp_mask = 0;
	gtk_image_get_image(gtk_image(), &tmp_image, &tmp_mask);

	if (gdk_image && tmp_image)
		*gdk_image = G::Object::wrap<Gdk::Image>(tmp_image);

	if (mask && tmp_mask)
		*mask = G::Object::wrap<Gdk::Bitmap>(tmp_mask);
}

Gdk::Pixbuf*
Gtk::Image::get_pixbuf() const
{
	return G::Object::wrap<Gdk::Pixbuf>(gtk_image_get_pixbuf(gtk_image()));
}

void
Gtk::Image::get_stock(StockId *stock_id, IconSize *size) const
{
	char *tmp_stock_id = 0;
	gtk_image_get_stock(gtk_image(), &tmp_stock_id, (GtkIconSize*)size);
	if (stock_id)
		*stock_id = tmp_stock_id;
}

void
Gtk::Image::get_icon_set(Pointer<IconSet> *icon_set, IconSize *size) const
{
	GtkIconSet *tmp_icon_set = 0;
	gtk_image_get_icon_set(gtk_image(), &tmp_icon_set, (GtkIconSize*)size);
	
	if (icon_set && tmp_icon_set)
		*icon_set = G::Boxed::wrap<IconSet>(GTK_TYPE_ICON_SET, tmp_icon_set, true);
}

Gdk::PixbufAnimation*
Gtk::Image::get_animation() const
{
	return G::Object::wrap<Gdk::PixbufAnimation>(gtk_image_get_animation(gtk_image()));
}

void 
Gtk::Image::get_icon_name(String& icon_name, IconSize *size) const
{
	const char *tmp_icon_name = 0;
	gtk_image_get_icon_name(gtk_image(), &tmp_icon_name, (GtkIconSize*)size);
	icon_name.assign(tmp_icon_name);
}

void 
Gtk::Image::set(Gdk::Pixmap *pixmap, Gdk::Bitmap *mask)
{
	gtk_image_set_from_pixmap(gtk_image(), *pixmap, *mask);
}

void 
Gtk::Image::set(Gdk::Image *image, Gdk::Bitmap *mask)
{
	gtk_image_set_from_image(gtk_image(), *image, *mask);
}

void
Gtk::Image::set(const String& filename)
{
	gtk_image_set_from_file(gtk_image(), filename.c_str());
}

void
Gtk::Image::set(Gdk::Pixbuf *pixbuf)
{
	gtk_image_set_from_pixbuf(gtk_image(), *pixbuf);
}

void
Gtk::Image::set(const StockId& stock_id, IconSize size)
{
	gtk_image_set_from_stock(gtk_image(), stock_id, (GtkIconSize)size);
}

void
Gtk::Image::set(Gtk::IconSet *icon_set, IconSize size)
{
	gtk_image_set_from_icon_set(gtk_image(), *icon_set, (GtkIconSize)size);
}

void 
Gtk::Image::set(Gdk::PixbufAnimation& animation)
{
	gtk_image_set_from_animation(gtk_image(), animation.gdk_pixbuf_animation());
}

void 
Gtk::Image::set(const char *icon_name, IconSize size)
{
	gtk_image_set_from_icon_name(gtk_image(), icon_name, (GtkIconSize)size);
}
	
void 
Gtk::Image::set(const String& icon_name, IconSize size)
{
	set(icon_name.c_str(), size);
}

/*  Gtk::ImageClass
 */

void
Gtk::ImageClass::init(GtkImageClass *g_class)
{
	MiscClass::init((GtkMiscClass*)g_class);
}

GType
Gtk::ImageClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_IMAGE, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::ImageClass::create()
{
	return g_object_new(get_type(), 0);
}

