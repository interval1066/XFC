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
 
/// @file xfc/gtk/cellrenderertoggle.hh
/// @brief A GtkCellRendererToggle C++ wrapper interface.
///
/// Provides CellRendererToggle, an object that renders a toggle button in a cell.

#ifndef XFC_GTK_CELL_RENDERER_TOGGLE_HH
#define XFC_GTK_CELL_RENDERER_TOGGLE_HH

#ifndef XFC_GTK_CELL_RENDERER_HH
#include <xfc/gtk/cellrenderer.hh>
#endif

#ifndef XFC_G_PROPERTY_HH
#include <xfc/glib/property.hh>
#endif

#ifndef __GTK_CELL_RENDERER_TOGGLE_H__
#include <gtk/gtkcellrenderertoggle.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class CellRendererToggle cellrenderertoggle.hh xfc/gtk/cellrenderertoggle.hh
/// @brief A GtkCellRendererToggle C++ wrapper class.

class CellRendererToggle : public CellRenderer
{
	friend class G::Object;

	CellRendererToggle(const CellRendererToggle&);
	CellRendererToggle& operator=(const CellRendererToggle&);

protected:
/// @name Constructors
/// @{

	explicit CellRendererToggle(GtkCellRendererToggle *cell, bool owns_reference = false);
	///< Construct a new CellRendererToggle from an existing GtkCellRendererToggle.
	///< @param cell A pointer to a GtkCellRendererToggle.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>cell</EM> can be a newly created GtkCellRendererToggle or an existing
	///< GtkCellRendererToggle. (see G::Object::Object).

/// @}
/// @name Property Prototypes
/// @{

	typedef G::Property<bool> ActivePropertyType;
	typedef G::PropertyProxy<G::Object, ActivePropertyType> ActivePropertyProxy;
	static const ActivePropertyType active_property;
	///< The toggle state of the button (see property_active()).

	typedef G::Property<bool> ActivatablePropertyType;
	typedef G::PropertyProxy<G::Object, ActivatablePropertyType> ActivatablePropertyProxy;
	static const ActivatablePropertyType activatable_property;
	///< The toggle button can be activated (see property_activatable()).

	typedef G::Property<bool> RadioPropertyType;
	typedef G::PropertyProxy<G::Object, RadioPropertyType> RadioPropertyProxy;
	static const RadioPropertyType radio_property;
	///< Draw the toggle button as a radio button (see property_radio()).

	typedef G::Property<bool> InconsistentPropertyType;
	typedef G::PropertyProxy<G::Object, InconsistentPropertyType> InconsistentPropertyProxy;
	static const InconsistentPropertyType inconsistent_property;
	///< The inconsistent state of the button (see property_inconsistent()).

/// @}
/// @name Signal Prototypes
/// @{

	typedef G::Signal<void, const String&> ToggledSignalType;
	typedef G::SignalProxy<TypeInstance, ToggledSignalType> ToggledSignalProxy;
	static const ToggledSignalType toggled_signal;
	///< Toggled signal (see signal_toggled()). Calls a slot with the signature:
	///< @code
	///< void function(const String& path);
	///< // path: A widget-dependent string representation of the event location.
	///< @endcode
	
/// @}

public:
	typedef GtkCellRendererToggle CObjectType;

/// @name Constructors
/// @{

	CellRendererToggle();
	///< Construct a new CellRendererToggle. 
	///< Adjust rendering parameters using object properties. Also, with TreeViewColumn, 
	///< you can bind a property to a value in a TreeModel. For example, you can bind 
	///< the "active" property on the cell renderer to a bool value in the model, thus
	///< causing the check button to reflect the state of the model.

	virtual ~CellRendererToggle();
	///< Destructor.

/// @}
/// @name Accessors
/// @{

	GtkCellRendererToggle* gtk_cell_renderer_toggle() const;
	///< Get a pointer to the GtkCellRendererToggle structure.

	operator GtkCellRendererToggle* () const;
	///< Conversion operator; safely converts a CellRendererToggle to a GtkCellRendererToggle pointer.

	bool get_active() const;
	///< Returns true if the cell renderer is active (see set_active()).

	bool get_radio() const;
	///< Returns true if we're rendering radio toggles rather than checkboxes.

/// @}
/// @name Methods
/// @{

	void set_active(bool setting);
	///< Activates or deactivates a cell renderer.
	///< @param setting  The value to set.
	
	void set_radio(bool radio);
	///< If radio is <EM>true</EM>, the cell renderer renders a radio toggle; 
	///< if <EM>false</EM> it renders a check toggle.
	///< @param radio <EM>true</EM> to make the toggle look like a radio button.
	///<
	///< This can be set globally for the cell renderer, or changed just 
	///< before rendering each cell in the model (for TreeView, you set up a
	///< per-row setting using TreeViewColumn to associate model columns with
	///< cell renderer properties).

/// @}
/// @name Property Proxies
/// @{

	const ActivePropertyProxy property_active();
	///< The toggle state of the button (bool : Read / Write).

	const ActivatablePropertyProxy property_activatable();
	///< The toggle button can be activated (bool : Read / Write).

	const RadioPropertyProxy property_radio();
	///< Draw the toggle button as a radio button (bool : Read / Write).

	const InconsistentPropertyProxy property_inconsistent();
	///< The inconsistent state of the button (bool : Read / Write).

/// @}
/// @name Signal Proxies
/// @{

	const ToggledSignalProxy signal_toggled();
	///< Connect to the toggled_signal; emitted when the state of the CellRenderer is changed.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/cellrenderertoggle.inl>

#endif // XFC_GTK_CELL_RENDERER_TOGGLE_HH

