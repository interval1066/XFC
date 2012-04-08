/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004 The XFC Development Team.
 *
 *  cellrendererpixbuf.inl - Gtk::CellRendererPixbuf inline functions
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

inline GtkCellRendererPixbuf*
Xfc::Gtk::CellRendererPixbuf::gtk_cell_renderer_pixbuf() const
{
	return reinterpret_cast<GtkCellRendererPixbuf*>(instance_);
}

inline Xfc::Gtk::CellRendererPixbuf::operator GtkCellRendererPixbuf* () const
{
	return this ? gtk_cell_renderer_pixbuf() : 0;
}

inline const Xfc::Gtk::CellRendererPixbuf::PixbufPropertyProxy
Xfc::Gtk::CellRendererPixbuf::property_pixbuf()
{
	return PixbufPropertyProxy(this, &pixbuf_property);
}

inline const Xfc::Gtk::CellRendererPixbuf::PixbufExpanderOpenPropertyProxy
Xfc::Gtk::CellRendererPixbuf::property_pixbuf_expander_open()
{
	return PixbufExpanderOpenPropertyProxy(this, &pixbuf_expander_open_property);
}

inline const Xfc::Gtk::CellRendererPixbuf::PixbufExpanderClosedPropertyProxy
Xfc::Gtk::CellRendererPixbuf::property_pixbuf_expander_closed()
{
	return PixbufExpanderClosedPropertyProxy(this, &pixbuf_expander_closed_property);
}

inline const Xfc::Gtk::CellRendererPixbuf::StockIdPropertyProxy
Xfc::Gtk::CellRendererPixbuf::property_stock_id()
{
	return StockIdPropertyProxy(this, &stock_id_property);
}

inline const Xfc::Gtk::CellRendererPixbuf::StockSizePropertyProxy
Xfc::Gtk::CellRendererPixbuf::property_stock_size()
{
	return StockSizePropertyProxy(this, &stock_size_property);
}

inline const Xfc::Gtk::CellRendererPixbuf::StockDetailPropertyProxy
Xfc::Gtk::CellRendererPixbuf::property_stock_detail()
{
	return StockDetailPropertyProxy(this, &stock_detail_property);
}

