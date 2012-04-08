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
 
/// @file xfc/gtk/cellrendererpixbuf.hh
/// @brief A GtkCellRendererPixbuf C++ wrapper interface.
///
/// Provides CellRendererPixbuf, an object that renders a pixbuf in a cell.

#ifndef XFC_GTK_CELL_RENDERER_PIXBUF_HH
#define XFC_GTK_CELL_RENDERER_PIXBUF_HH

#ifndef XFC_GTK_CELL_RENDERER_HH
#include <xfc/gtk/cellrenderer.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef __GTK_CELL_RENDERER_PIXBUF_H__
#include <gtk/gtkcellrendererpixbuf.h>
#endif

namespace Xfc {

namespace Gdk {
class Pixbuf;
}

namespace Gtk {

class StockId;

/// @class CellRendererPixbuf cellrendererpixbuf.hh xfc/gtk/cellrendererpixbuf.hh
/// @brief A GtkCellRendererPixbuf C++ wrapper class.
///
/// CellRendererPixbuf is an object that renders a pixbuf in a cell.

class CellRendererPixbuf : public CellRenderer
{
	friend class G::Object;

	CellRendererPixbuf(const CellRendererPixbuf&);
	CellRendererPixbuf& operator=(const CellRendererPixbuf&);

protected:
/// @name Constructors
/// @{

	explicit CellRendererPixbuf(GtkCellRendererPixbuf *cell, bool owns_reference = false);
	///< Construct a new CellRendererPixbuf from an existing GtkCellRendererPixbuf.
	///< @param cell A pointer to a GtkCellRendererPixbuf.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>cell</EM> can be a newly created GtkCellRendererPixbuf or an existing
	///< GtkCellRendererPixbuf. (see G::Object::Object).

/// @}
/// @name Property Prototypess
/// @{

	typedef G::Property<Gdk::Pixbuf*, G::Object*> PixbufPropertyType;
	typedef G::PropertyProxy<G::Object, PixbufPropertyType> PixbufPropertyProxy;
	static const PixbufPropertyType pixbuf_property;
	///< The pixbuf to render (see property_pixbuf()).

	typedef G::Property<Gdk::Pixbuf*, G::Object*> PixbufExpanderOpenPropertyType;
	typedef G::PropertyProxy<G::Object, PixbufExpanderOpenPropertyType> PixbufExpanderOpenPropertyProxy;
	static const PixbufExpanderOpenPropertyType pixbuf_expander_open_property;
	///< Pixbuf for open expander (see property_pixbuf_expander_open()).

	typedef G::Property<Gdk::Pixbuf*, G::Object*> PixbufExpanderClosedPropertyType;
	typedef G::PropertyProxy<G::Object, PixbufExpanderClosedPropertyType> PixbufExpanderClosedPropertyProxy;
	static const PixbufExpanderClosedPropertyType pixbuf_expander_closed_property;
	///< Pixbuf for closed expander (see property_pixbuf_expander_closed()).

	typedef G::Property<String> StockIdPropertyType;
	typedef G::PropertyProxy<G::Object, StockIdPropertyType> StockIdPropertyProxy;
	static const StockIdPropertyType stock_id_property;
	///< The stock ID of the stock icon to render (see property_stock_id()).

	typedef G::Property<IconSize, int> StockSizePropertyType;
	typedef G::PropertyProxy<G::Object, StockSizePropertyType> StockSizePropertyProxy;
	static const StockSizePropertyType stock_size_property;
	///< The size of the rendered icon (see property_stock_size()).

	typedef G::Property<String> StockDetailPropertyType;
	typedef G::PropertyProxy<G::Object, StockDetailPropertyType> StockDetailPropertyProxy;
	static const StockDetailPropertyType stock_detail_property;
	///< The render detail to pass to the theme engine (see property_stock_detail()).
	
/// @}

public:
	typedef GtkCellRendererPixbuf CObjectType;

/// @name Constructors
/// @{

	CellRendererPixbuf();
	///< Construct a new CellRendererPixbuf.
	///< Adjust rendering parameters using object properties. Also, with TreeViewColumn, you 
	///< can bind a property to a value in a TreeModel. For example, you can bind the "pixbuf"
	///< property on the cell renderer to a pixbuf value in the model, thus rendering a 
	///< different image in each row of the TreeView.

	virtual ~CellRendererPixbuf();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkCellRendererPixbuf* gtk_cell_renderer_pixbuf() const;
	///< Get a pointer to the GtkCellRendererPixbuf structure.

	operator GtkCellRendererPixbuf* () const;
	///< Conversion operator; safely converts a CellRendererPixbuf to a GtkCellRendererPixbuf pointer.

/// @}
/// @name Property Proxies
/// @{

	const PixbufPropertyProxy property_pixbuf();
	///< The pixbuf to render (Gdk::Pixbuf* : Read / Write).

	const PixbufExpanderOpenPropertyProxy property_pixbuf_expander_open();
	///< Pixbuf for open expander (Gdk::Pixbuf* : Read / Write).

	const PixbufExpanderClosedPropertyProxy property_pixbuf_expander_closed();
	///< Pixbuf for closed expander (Gdk::Pixbuf* : Read / Write).

	const StockIdPropertyProxy property_stock_id();
	///< The stock ID of the stock icon to render (String : Read / Write).

	const StockSizePropertyProxy property_stock_size();
	///< The size of the rendered icon (IconSize : Read / Write).

	const StockDetailPropertyProxy property_stock_detail();
	///< The render detail to pass to the theme engine (String : Read / Write).

///@}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/cellrendererpixbuf.inl>

#endif // XFC_GTK_CELL_RENDERER_PIXBUF_HH

