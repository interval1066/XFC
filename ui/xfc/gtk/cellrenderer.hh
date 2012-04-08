/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
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
 
/// @file xfc/gtk/cellrenderer.hh
/// @brief A GtkCellRenderer C++ wrapper interface.
///
/// Provides CellRenderer, an object for rendering a single cell on a Gdk::Drawable.

#ifndef XFC_GTK_CELL_RENDERER_HH
#define XFC_GTK_CELL_RENDERER_HH

#ifndef XFC_GTK_OBJECT_HH
#include <xfc/gtk/object.hh>
#endif

#ifndef XFC_GTK_ENUMS_HH
#include <xfc/gtk/enums.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef __GTK_CELL_RENDERER_H__
#include <gtk/gtkcellrenderer.h>
#endif

namespace Xfc {

namespace Gdk {
class Color;
class Event;
class Rectangle;
class Window;
}

namespace Gtk {

class CellEditable;
class Widget;

/// @enum CellRendererState
/// Specifies how the CellRenderer should render a cell.

enum CellRendererState
{
	CELL_RENDERER_SELECTED = GTK_CELL_RENDERER_SELECTED, ///< The cell can be selected.
	CELL_RENDERER_PRELIT = GTK_CELL_RENDERER_PRELIT, ///< The cell can be prelit.
	CELL_RENDERER_INSENSITIVE = GTK_CELL_RENDERER_INSENSITIVE, ///< The cell is insensitive.
	CELL_RENDERER_SORTED = GTK_CELL_RENDERER_SORTED, ///< The cell is in the sort column/row.
	CELL_RENDERER_FOCUSED = GTK_CELL_RENDERER_FOCUSED ///< The cell can be focused.
};

/// CellRendererStateField holds one or more values from the Gtk::CellRendererState enum OR'd together.

typedef unsigned int CellRendererStateField;

/// @enum CellRendererMode
/// Specifies the editable mode of the CellRenderer.

enum CellRendererMode
{
	INERT = GTK_CELL_RENDERER_MODE_INERT, ///< The cell is neither activatable nor editable.
	ACTIVATABLE = GTK_CELL_RENDERER_MODE_ACTIVATABLE, ///< The cell can be activated.
	EDITABLE = GTK_CELL_RENDERER_MODE_EDITABLE ///< The cell can be edited.
};

/// @class CellRenderer cellrenderer.hh xfc/gtk/cellrenderer.hh
/// @brief A GtkCellRenderer C++ wrapper class.
///
/// The purpose of the cell renderers is to provide extensibility to the widget
/// and to allow multiple ways of rendering the same type of data. For example,
/// consider how to render a bool variable. Should you render it as a string of
/// "true" or "false", "On" or "Off", or should you render it as a checkbox?
///
/// The TreeView widget uses columns and cell renderers to display a model. Cell
/// renderers are used to draw the data in the tree model in a certain way. There
/// are three cell renderers that come with XFC. They are the CellRendererText,
/// CellRendererPixbuf and CellRendererToggle. It is relatively easy to write a
/// custom renderer.

class CellRenderer : public Object
{
	friend class G::Object;

	CellRenderer(const CellRenderer&);
	CellRenderer& operator=(const CellRenderer&);
	
protected:
/// @name Constructors
/// @{

	explicit CellRenderer(GtkCellRenderer *cell, bool owns_reference = false);
	///< Construct a new CellRenderer from an existing GtkCellRenderer.
	///< @param cell A pointer to a GtkCellRenderer.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>cell</EM> can be a newly created GtkCellRenderer or an existing
	///< GtkCellRenderer. (see G::Object::Object).

/// @}
/// @name Methods
/// @{
 
	void editing_canceled();
	///< Causes the cell renderer to emit the "editing-canceled" signal. This
	///< method is for use only by implementations of cell renderers that need
	///< to notify the client program that an editing process was canceled and
	///< the changes were not committed.
	
/// @}
/// @name Property Prototypes
/// @{

	typedef G::Property<CellRendererMode, int> ModePropertyType;
	typedef G::PropertyProxy<G::Object, ModePropertyType> ModePropertyProxy;
	static const ModePropertyType mode_property;
	///< Editable mode of the CellRenderer (see property_mode()).

	typedef G::Property<bool> VisiblePropertyType;
	typedef G::PropertyProxy<G::Object, VisiblePropertyType> VisiblePropertyProxy;
	static const VisiblePropertyType visible_property;
	///< Display the cell (see property_visible()).

	typedef G::Property<bool> SensitivePropertyType;
	typedef G::PropertyProxy<G::Object, SensitivePropertyType> SensitivePropertyProxy;
	static const SensitivePropertyType sensitive_property;
	///< Display the cell sensitive(see property_sensitive()).

	typedef G::Property<float> XAlignPropertyType;
	typedef G::PropertyProxy<G::Object, XAlignPropertyType> XAlignPropertyProxy;
	static const XAlignPropertyType xalign_property;
	///< The x-align (see property_xalign()).

	typedef G::Property<float> YAlignPropertyType;
	typedef G::PropertyProxy<G::Object, YAlignPropertyType> YAlignPropertyProxy;
	static const YAlignPropertyType yalign_property;
	///< The y-align (see property_yalign()).

	typedef G::Property<unsigned int> XPadPropertyType;
	typedef G::PropertyProxy<G::Object, XPadPropertyType> XPadPropertyProxy;
	static const XPadPropertyType xpad_property;
	///< The xpad (see property_xpad()).

	typedef G::Property<unsigned int> YPadPropertyType;
	typedef G::PropertyProxy<G::Object, YPadPropertyType> YPadPropertyProxy;
	static const YPadPropertyType ypad_property;
	///< The ypad (see property_ypad()).

	typedef G::Property<int> WidthPropertyType;
	typedef G::PropertyProxy<G::Object, WidthPropertyType> WidthPropertyProxy;
	static const WidthPropertyType width_property;
	///< The fixed height (see property_height()).

	typedef G::Property<int> HeightPropertyType;
	typedef G::PropertyProxy<G::Object, HeightPropertyType> HeightPropertyProxy;
	static const HeightPropertyType height_property;
	///< The fixed height (see property_height()).

	typedef G::Property<bool> IsExpanderPropertyType;
	typedef G::PropertyProxy<G::Object, IsExpanderPropertyType> IsExpanderPropertyProxy;
	static const IsExpanderPropertyType is_expander_property;
	///< The row has children (see property_is_expander()).

	typedef G::Property<bool> IsExpandedPropertyType;
	typedef G::PropertyProxy<G::Object, IsExpandedPropertyType> IsExpandedPropertyProxy;
	static const IsExpandedPropertyType is_expanded_property;
	///< The row is an expander row, and is expanded (see property_is_expanded()).

	typedef G::WritableProperty<String> CellBackgroundPropertyType;
	typedef G::PropertyProxy<G::Object, CellBackgroundPropertyType> CellBackgroundPropertyProxy;
	static const CellBackgroundPropertyType cell_background_property;
	///< The cell background color as a string (see property_cell_background()).

	typedef G::Property<Pointer<Gdk::Color> > CellBackgroundGdkPropertyType;
	typedef G::PropertyProxy<G::Object, CellBackgroundGdkPropertyType> CellBackgroundGdkPropertyProxy;
	static const CellBackgroundGdkPropertyType cell_background_gdk_property;
	///< The cell background color as a Gdk::Color (see property_cell_background_gdk()).

	typedef G::Property<bool> CellBackgroundSetPropertyType;
	typedef G::PropertyProxy<G::Object, CellBackgroundSetPropertyType> CellBackgroundSetPropertyProxy;
	static const CellBackgroundSetPropertyType cell_background_set_property;
	///< Whether this tag affects the cell background color (see property_cell_background_set()).
	
/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void> EditingCanceledSignalType;
	typedef G::SignalProxy<TypeInstance, EditingCanceledSignalType> EditingCanceledSignalProxy;
	static const EditingCanceledSignalType editing_canceled_signal;
	///< Editing canceled signal (see signal_editing_canceled()). Calls a slot with the signature:
	///< @code
	///< void function();
	///< @endcode

	typedef G::Signal<void, CellEditable*, const String&> EditingStartedSignalType;
	typedef G::SignalProxy<TypeInstance, EditingStartedSignalType> EditingStartedSignalProxy;
	static const EditingStartedSignalType editing_started_signal;
	///< Editing started signal (see signal_editing_started()). Calls a slot with the signature:
	///< @code
	///< void function(CellEditable *editable, const String& path);
	///< // cell_editable: The CellEditable
	///< // path: The path identifying the edited cell.
	///< @endcode

/// @}

public:
	typedef GtkCellRenderer CObjectType;

/// @name Constructors
/// @{

	virtual ~CellRenderer();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkCellRenderer* gtk_cell_renderer() const;
	///< Get a pointer to the GtkCellRenderer structure.

	operator GtkCellRenderer* () const;
	///< Conversion operator; safely converts a CellRenderer to a GtkCellRenderer pointer.

	void get_fixed_size(int *width, int *height) const;
	///< Fills in width and height with the appropriate size of cell.
	///< @param width Location to fill in with the fixed width of the widget, or null.
	///< @param height Location to fill in with the fixed height of the widget, or null.

	void get_size(const Widget& widget, const Gdk::Rectangle *cell_area,
	              int *x_offset, int *y_offset, int *width, int *height) const;
	///< Obtains the width and height needed to render the cell and sets the x and y offets (if set).
	///< @param widget The widget the renderer is rendering to.
	///< @param cell_area The area a cell will be allocated, or null
	///< @param x_offset Location to return x offset of cell relative to cell_area, or null.
	///< @param y_offset Location to return y offset of cell relative to cell_area, or null.
	///< @param width Location to return width needed to render a cell, or null.
	///< @param height Location to return height needed to render a cell, or null.
	///<
	///< Used by view widgets to determine the appropriate size for the cell_area passed
	///< to render(). If cell_area is not null, fills in the x and y offsets (if set) of the
	///< cell relative to this location. Otherwise x_offset and y_offset are inorgred. Please
	///< note that the values set in width and height, as well as those in x_offset and 
	///< y_offset are inclusive of the xpad and ypad properties.

/// @}
/// @name Methods
/// @{

	void render(Gdk::Window& window, Widget& widget, const Gdk::Rectangle *background_area,
	            const Gdk::Rectangle *cell_area, const Gdk::Rectangle *expose_area, 
	            CellRendererStateField flags);
	///< Invokes the virtual render function of the GtkCellRenderer.
	///< @param window A GdkDrawable to draw to.
	///< @param widget The widget owning window.
	///< @param background_area Entire cell area (including tree expanders and maybe padding on the sides).
	///< @param cell_area Area normally rendered by a cell renderer.
	///< @param expose_area Area that actually needs updating.
	///< @param flags The Gtk::CellRendererState flags that affect the rendering.
	///<
	///< The three passed-in rectangles are areas of window. Most renderers will draw
	///< within cell_area; the xalign, yalign, xpad, and ypad properties of the CellRenderer
	///< should be honored with respect to cell_area. The background_area includes the blank
	///< space around the cell, and also the area containing the tree expander; so the
	///< background_area rectangles for all cells tile to cover the entire window. The
	///< expose_area is a clip rectangle.

	bool activate(const Gdk::Event *event, Widget *widget, const String& path,
	              const Gdk::Rectangle *background_area, const Gdk::Rectangle *cell_area,
	              CellRendererStateField flags);
	///< Passes an activate event to the cell renderer for possible processing.
	///< @param event A Gdk::Event.
	///< @param widget Widget that received the event.
	///< @param path Widget-dependent string representation of the event location;
	///<             e.g. for TreeView, a string representation of TreePath.
	///< @param background_area Background area as passed to render.
	///< @param cell_area Cell area as passed to render().
	///< @param flags The Gtk::CellRendererState flags.
	///< @return <EM>true</EM> if the event was handled.
	///<
	///< Some cell renderers may use events; for example, CellRendererToggle
	///< toggles when it gets a mouse click.

	CellEditable* start_editing(const Gdk::Event *event, Widget *widget, const String& path,
	                            const Gdk::Rectangle *background_area, const Gdk::Rectangle *cell_area,
	                            CellRendererStateField  flags);
	///< Passes an activate event to the cell renderer for possible processing.
	///< @param event A Gdk::Event.
	///< @param widget Widget that received the event.
	///< @param path Widget-dependent string representation of the event location;
	///<             e.g. for TreeView, a string representation of TreePath.
	///< @param background_area Background area as passed to render.
	///< @param cell_area Cell area as passed to render().
	///< @param flags The Gtk::CellRendererState flags.
	///< @return A new CellEditable or null.

	void set_fixed_size(int width, int height);
	///< Sets the renderer size to be explicit, independent of the properties set.
	///< @param width The width of the cell renderer, or -1.
	///< @param height The height of the cell renderer, or -1.

	void stop_editing(bool canceled);
	///< Informs the cell renderer that the editing is stopped. 
	///< @param canceled Set to <EM>true</EM> if the editing has been canceled.
	///< 	
	///< If canceled is <EM>true</EM>, the cell renderer will emit the "editing-canceled" signal.
	///< This method should be called by cell renderer implementations in response to the 
	///< "editing-done" signal of Gtk::CellEditable.

/// @}
/// @name Property Proxies
/// @{

	const ModePropertyProxy property_mode();
	///< Editable mode of the CellRenderer (CellRendererMode : Read / Write).

	const VisiblePropertyProxy property_visible();
	///< Display the cell (bool : Read / Write).

	const SensitivePropertyProxy property_sensitive();
	///< Display the cell sensitive (bool : Read / Write).

	const XAlignPropertyProxy property_xalign();
	///< The x-align (float : Read / Write).

	const YAlignPropertyProxy property_yalign();
	///< The y-align (float : Read / Write).

	const XPadPropertyProxy property_xpad();
	///< The xpad (unsigned int : Read / Write).

	const YPadPropertyProxy property_ypad();
	///< The ypad (unsigned int : Read / Write).

	const WidthPropertyProxy property_width();
	///< The fixed width (int : Read / Write).

	const HeightPropertyProxy property_height();
	///< The fixed height (int : Read / Write).

	const IsExpanderPropertyProxy property_is_expander();
	///< The row has children (bool : Read / Write).

	const IsExpandedPropertyProxy property_is_expanded();
	///< The row is an expander row, and is expanded (bool : Read / Write).

	const CellBackgroundPropertyProxy property_cell_background();
	///< The cell background color as a string (String : Write).

	const CellBackgroundGdkPropertyProxy property_cell_background_gdk();
	///< The cell background color as a Gdk::Color (Pointer<Gdk::Color> : Read / Write).

	const CellBackgroundSetPropertyProxy property_cell_background_set();
	///< Whether this tag affects the cell background color (bool : Read / Write).

/// @}
/// @name Signal Proxies
/// @{

	const EditingCanceledSignalProxy signal_editing_canceled();
	///< Connect to the editing_canceled_signal; emitted when the user cancels
	///< the process of editing a cell, such as pressing the Escape key.

	const EditingStartedSignalProxy signal_editing_started();
	///< Connect to the editing_started_signal; emitted when a cell starts to be edited.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/cellrenderer.inl>

#endif // XFC_GTK_CELL_RENDERER_HH

