/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  pixbuf-loader.cc - GdkPixbufLoader C++ wrapper implementation
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
 
#include "pixbuf-loader.hh"
#include "pixbuf-loadersignals.hh"
#include "pixbuf.hh"
#include "pixbuf-animation.hh"
#include "pixbuf-io.hh"
#include "private/pixbuf-loaderclass.hh"
#include "xfc/glib/error.hh"
#include "xfc/glib/private/marshal.hh"

using namespace Xfc;

/*  Gdk::PixbufLoader
 */

Gdk::PixbufLoader::PixbufLoader(GdkPixbufLoader *pixbuf_loader, bool owns_reference)
: G::Object((GObject*)pixbuf_loader, owns_reference)
{
}
	
Gdk::PixbufLoader::PixbufLoader() 
: G::Object((GObject*)PixbufLoaderClass::create())
{
}

Gdk::PixbufLoader::~PixbufLoader()
{
}

Pointer<Gdk::PixbufLoader>
Gdk::PixbufLoader::create_with_type(const char *image_type, G::Error *error)
{
	return G::Object::wrap<PixbufLoader>(gdk_pixbuf_loader_new_with_type(image_type, *error));
}

Pointer<Gdk::PixbufLoader>
Gdk::PixbufLoader::create_with_type(const String& image_type, G::Error *error)
{
	return create_with_type(image_type.c_str(), error);
}

Pointer<Gdk::PixbufLoader>
Gdk::PixbufLoader::create_with_mime_type(const char *mime_type, G::Error *error)
{
	return G::Object::wrap<PixbufLoader>(gdk_pixbuf_loader_new_with_mime_type(mime_type, *error));
}

Pointer<Gdk::PixbufLoader>
Gdk::PixbufLoader::create_with_mime_type(const String& mime_type, G::Error *error)
{
	return create_with_mime_type(mime_type.c_str(), error);
}

Pointer<Gdk::Pixbuf>
Gdk::PixbufLoader::get_pixbuf() const
{
	GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(gdk_pixbuf_loader());
	return pixbuf ? G::Object::wrap_new<Pixbuf>(pixbuf) : 0;
}

Pointer<Gdk::PixbufAnimation>
Gdk::PixbufLoader::get_animation() const
{
	GdkPixbufAnimation *animation = gdk_pixbuf_loader_get_animation(gdk_pixbuf_loader());
	return animation ? G::Object::wrap_new<PixbufAnimation>(animation) : 0;
}

Pointer<Gdk::PixbufFormat>
Gdk::PixbufLoader::get_format() const
{
	return new PixbufFormat(gdk_pixbuf_loader_get_format(gdk_pixbuf_loader()));
}

bool
Gdk::PixbufLoader::write(const unsigned char *buffer, size_t count, G::Error *error)
{
	return gdk_pixbuf_loader_write(gdk_pixbuf_loader(), buffer, (gsize)count, *error);
}

bool
Gdk::PixbufLoader::close(G::Error *error)
{
	return gdk_pixbuf_loader_close(gdk_pixbuf_loader(), *error);
}

/*  Gdk::PixbufLoaderClass
 */

void
Gdk::PixbufLoaderClass::init(GdkPixbufLoaderClass *g_class)
{
	G::ObjectClass::init((GObjectClass*)g_class);
	g_class->size_prepared = &size_prepared_proxy;
	g_class->area_prepared = &area_prepared_proxy;
	g_class->area_updated = &area_updated_proxy;
	g_class->closed = &closed_proxy;
}

GdkPixbufLoaderClass*
Gdk::PixbufLoaderClass::get_parent_class(void *instance)
{
	return static_cast<GdkPixbufLoaderClass*>(g_type_class_peek_parent(G_OBJECT_GET_CLASS(instance)));
}

GType
Gdk::PixbufLoaderClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GDK_TYPE_PIXBUF_LOADER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gdk::PixbufLoaderClass::create()
{
	return g_object_new(get_type(), 0);
}

void 
Gdk::PixbufLoaderClass::size_prepared_proxy(GdkPixbufLoader *loader, int width, int height)
{
	PixbufLoaderSignals *signals = dynamic_cast<PixbufLoaderSignals*>(G::ObjectSignals::pointer((GObject*)loader));
	if (signals)
		signals->on_size_prepared(width, height);
	else
	{
		GdkPixbufLoaderClass *g_class = get_parent_class(loader);
		if (g_class && g_class->size_prepared)
			g_class->size_prepared(loader, width, height);
	}
}

void
Gdk::PixbufLoaderClass::area_prepared_proxy(GdkPixbufLoader *loader)
{
	PixbufLoaderSignals *signals = dynamic_cast<PixbufLoaderSignals*>(G::ObjectSignals::pointer((GObject*)loader));
	if (signals)
		signals->on_area_prepared();
	else
	{
		GdkPixbufLoaderClass *g_class = get_parent_class(loader);
		if (g_class && g_class->area_prepared)
			g_class->area_prepared(loader);
	}
}

void
Gdk::PixbufLoaderClass::area_updated_proxy(GdkPixbufLoader *loader, int x, int y, int width, int height)
{
	PixbufLoaderSignals *signals = dynamic_cast<PixbufLoaderSignals*>(G::ObjectSignals::pointer((GObject*)loader));
	if (signals)
		signals->on_area_updated(x, y, width, height);
	else
	{
		GdkPixbufLoaderClass *g_class = PixbufLoaderClass::get_parent_class(loader);
		if (g_class && g_class->area_updated)
			g_class->area_updated(loader, x, y, width, height);
	}
}

void
Gdk::PixbufLoaderClass::closed_proxy(GdkPixbufLoader *loader)
{
	PixbufLoaderSignals *signals = dynamic_cast<PixbufLoaderSignals*>(G::ObjectSignals::pointer((GObject*)loader));
	if (signals)
		signals->on_closed();
	else
	{
		GdkPixbufLoaderClass *g_class = PixbufLoaderClass::get_parent_class(loader);
		if (g_class && g_class->closed)
			g_class->closed(loader);
	}
}

/*  Gdk::PixbufLoader signals
 */

const Gdk::PixbufLoader::SizePreparedSignalType Gdk::PixbufLoader::size_prepared_signal("size_prepared", (GCallback)&G::Marshal::void_int_int_callback);

const Gdk::PixbufLoader::AreaPreparedSignalType Gdk::PixbufLoader::area_prepared_signal("area_prepared", (GCallback)&G::Marshal::void_callback);

const Gdk::PixbufLoader::AreaUpdatedSignalType Gdk::PixbufLoader::area_updated_signal("area_updated", (GCallback)&G::Marshal::void_int_int_int_int_callback);

const Gdk::PixbufLoader::ClosedSignalType Gdk::PixbufLoader::closed_signal("closed", (GCallback)&G::Marshal::void_callback);

