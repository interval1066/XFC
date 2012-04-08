/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
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
 
/// @file xfc/gtk/cellview.hh
/// @brief A GtkCellView C++ wrapper interface.
///
/// Provides CellView, a widget displaying a single row of a Gtk::TreeModel.

#ifndef XFC_GTK_CELL_VIEW_HH
#define XFC_GTK_CELL_VIEW_HH

#ifndef XFC_GTK_WIDGET_HH
#include <xfc/gtk/widget.hh>
#endif

#ifndef XFC_GTK_CELL_LAYOUT_HH
#include <xfc/gtk/celllayout.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef __GTK_CELL_VIEW_H__
#include <gtk/gtkcellview.h>
#endif

namespace Xfc {

namespace Gtk {

class CellRenderer;
class TreeModel;
class TreePath;

/// @class CellView cellview.hh xfc/gtk/cellview.hh
/// @brief A GtkCellView C++ wrapper class.
///
/// A CellView displays a single row of a Gtk::TreeModel, using cell renderers just like Gtk::TreeView.
/// CellView doesn't support some of the more complex features of Gtk::TreeView, like cell editing and
/// drag and drop.

class CellView : public Widget, public CellLayout
{
	friend class G::Object;
	
	CellView(const CellView&);
	CellView& operator=(const CellView&);
	
protected:
/// @name Constructors
/// @{

	explicit CellView(GtkCellView *cell_view, bool owns_reference = false);
	///< Construct a new CellView from an existing GtkCellView.
	///< @param cell_view A pointer to a GtkCellView.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>cell_view</EM> can be a newly created GtkCellView or an existing
	///< GtkCellView. (see G::Object::Object).
	
/// @}
/// @name Property Prototypes
/// @{

	typedef G::WritableProperty<String> BackgroundPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundPropertyType> BackgroundPropertyProxy;
	static const BackgroundPropertyType background_property;
	///< The background color as a string (see property_background()).

	typedef G::Property<Pointer<Gdk::Color> > BackgroundGdkPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundGdkPropertyType> BackgroundGdkPropertyProxy;
	static const BackgroundGdkPropertyType background_gdk_property;
	///< The background color as a (possibly unallocated) Gdk::Color (see property_background_gdk()).

	typedef G::Property<bool> BackgroundSetPropertyType;
	typedef G::PropertyProxy<G::Object, BackgroundSetPropertyType> BackgroundSetPropertyProxy;
	static const BackgroundSetPropertyType background_set_property;
	///< Whether this tag affects the background color (see property_background_set()).

/// @}

public:
	typedef GtkCellView CObjectType;

/// @name Constructors
/// @{
	
	CellView();
	///< Constructs a new cell view widget.

	CellView(const char *text, bool use_markup = false);
	CellView(const String& text, bool use_markup = false);
	///< Constructs a new cell view widget, adds a Gtk::CellRendererText to it, and makes its show <EM>text</EM>.
	///< @param text The text to display in the cell view. 
	///< @param use_markup Set to <EM>true</EM> if <EM>text</EM> is marked up. 
	///<
	///< If <EM>use_markup</EM> is true, <EM>text</EM> can be text marked up with the Pango text markup language. 
	
	CellView(Gdk::Pixbuf& pixbuf);
	///< Constructs a new cell view widget, adds a Gtk::CellRendererPixbuf to it, and makes its show <EM>pixbuf</EM>.
	///< @param pixbuf The image to display in the cell view. 

	virtual ~CellView();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkCellView* gtk_cell_view() const;
	///< Get a pointer to the GtkCellView structure.

	operator GtkCellView* () const;
	///< Conversion operator; safely converts an CellView to a GtkCellView pointer.

	Pointer<TreePath> get_displayed_row() const;
	///< Obtains the path of the row currently  displayed by the cell view, 
	///< or null if the path pointed to is no longer valid.
	///< @return The current path, or a null pointer. 

	bool get_size_of_row(const TreePath& path, Requisition& requisition);
	///< Sets requisition to the size needed by the cell view to display the model row pointed to by path.
	///< @param path A TreePath.
	///< @param requisition The return location for the size. 
	///< @return <EM>true</EM>

	bool get_cell_renderers(std::vector<CellRenderer*>& cell_list);
	///< Obtains a list of cell renderers which have been added to the cell view.
	///< @param cell_list A reference to a vector of CellRenderer* to hold the list of cell renderers.
	///< @return <EM>true</EM> if cell_list is not empty.

/// @}
/// @name Methods
/// @{

	void set_model(TreeModel *model);
	///< Sets the model for the cell view. 
	///< @param model A TreeModel
	///<	
	///< If the cell view already has a model set, it will remove it before setting the new model.
	///< If <EM>model</EM> is null, then it will unset the old model.
	
	void set_displayed_row(const TreePath *path);
	///< Sets the row of the model that is currently displayed by the cell view. 
	///< @param path A TreePath or null to unset the current path. 
	///<	
	///< If the path is unset, then the contents of the cellview "stick" at their last value;
	///< this is not normally a desired result, but may be a needed intermediate state if say,
	///< the model for the cell view becomes temporarily empty.


	void set_background_color(const Gdk::Color *color);
	///< Sets the background color of the cell view.
	///< @param color The new background color, or null to unset the current color.
	
/// @name Property Proxies
/// @{
/// @}

	const BackgroundPropertyProxy property_background();
	///< The background color as a string (String : Write).

	const BackgroundGdkPropertyProxy property_background_gdk();
	///< The background color as a (possibly unallocated) Gdk::Color (Pointer<Gdk::Color> : Read / Write).

	
	const BackgroundSetPropertyProxy property_background_set();
	///< Whether this tag affects the background color (bool : Read / Write).

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/cellview.inl>

#endif // XFC_GTK_CELL_VIEW_HH

