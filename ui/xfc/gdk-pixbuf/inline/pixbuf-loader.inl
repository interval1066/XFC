/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  pixbuf-loader.inl - Gdk::PixbufLoader inline functions
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

inline GdkPixbufLoader*
Xfc::Gdk::PixbufLoader::gdk_pixbuf_loader() const
{
	return reinterpret_cast<GdkPixbufLoader*>(instance_);
}

inline Xfc::Gdk::PixbufLoader::operator GdkPixbufLoader* () const
{
	return this ? ((GdkPixbufLoader*)instance_) : 0;
}

inline void
Xfc::Gdk::PixbufLoader::set_size(int width, int height)
{
	gdk_pixbuf_loader_set_size(gdk_pixbuf_loader(), width, height);
}

inline const Xfc::Gdk::PixbufLoader::SizePreparedSignalProxy
Xfc::Gdk::PixbufLoader::signal_size_prepared()
{
	return SizePreparedSignalProxy(this, &size_prepared_signal);
}

inline const Xfc::Gdk::PixbufLoader::AreaPreparedSignalProxy
Xfc::Gdk::PixbufLoader::signal_area_prepared()
{
	return AreaPreparedSignalProxy(this, &area_prepared_signal);
}

inline const Xfc::Gdk::PixbufLoader::AreaUpdatedSignalProxy
Xfc::Gdk::PixbufLoader::signal_area_updated()
{
	return AreaUpdatedSignalProxy(this, &area_updated_signal);
}

inline const Xfc::Gdk::PixbufLoader::ClosedSignalProxy
Xfc::Gdk::PixbufLoader::signal_closed()
{
	return ClosedSignalProxy(this, &closed_signal);
}

