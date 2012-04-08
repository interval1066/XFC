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

/// @file xfc/gdk-pixbuf/pixbuf-loadersignals.hh
/// @brief Gdk::PixbufLoader virtual signal handlers.
///
/// Provides Gdk::PixbufLoaderSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gdk::PixbufLoader objects.

#ifndef XFC_GDK_PIXBUF_LOADER_SIGNALS_HH
#define XFC_GDK_PIXBUF_LOADER_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gdk {

/// @class PixbufLoaderSignals pixbuf-loadersignals.hh xfc/gdk-pibuf/pixbuf-loadersignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gdk::PixbufLoader.

class PixbufLoaderSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	PixbufLoaderSignals(PixbufLoader *pixbuf_loader);
	///< Constructs a new PixbufLoaderSignals object.
	///< @param pixbuf_loader A PixbufLoader object inheriting the PixbufLoaderSignals implementation.

	virtual ~PixbufLoaderSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	void on_size_prepared(int width, int height);
	///< Called when the pixbuf loader has been fed the initial amount of data that
	///< is required to figure out the size of the image that it will create.
	///< @param width The width of the image the pixbuf loader will create.
	///< @param height The height of the image the pixbuf loader will create.
	///<
	///< Applications can call set_size() in response to this signal to set
	///< the desired size to which the image should be scaled.

	void on_area_prepared();
	///< Called when the pixbuf loader has allocated the pixbuf in the desired size.
	///< After this signal is emitted, applications can call get_pixbuf() to fetch
	///< the partially-loaded pixbuf.

	void on_area_updated(int x, int y, int width, int height);
	///< Called when a significant area of the image being loaded has been updated.
	///< @param x The X coordinate of the updated area.
	///< @param y The Y coordinate of the updated area.
	///< @param width The width of the updated area.
	///< @param height The height of the updated area.
	///<
	///< Normally it means that one or more complete scanlines has been read in,
	///< but it could be a different area as well. Applications can use this signal
	///< to know when to repaint areas of an image that is being loaded. Usually the
	///< x coordinate and the width will remain the same. The y coordinate changes
	///< each time one or more scanlines are read in. The height is the number of
	///< scanlines, in pixels.

	void on_closed();
	///< Called when close() is called. It can be used by different parts of an
	///< application to receive notification when an image loader is closed by
	///< the code that drives it.

/// @}
};

} // namespace Gdk

} // namespace Xfc

#endif // XFC_GDK_PIXBUF_LOADER_SIGNALS_HH

