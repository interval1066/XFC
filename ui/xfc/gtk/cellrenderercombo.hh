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
 
/// @file xfc/gtk/cellrenderercombo.hh
/// @brief A GtkCellRendererCombo C++ wrapper interface.
///
/// Provides CellRendererCombo, a cell renderer that renders a combobox in a cell.

#ifndef XFCE_GTK_CELL_RENDERER_COMBO_HH
#define XFC_GTK_CELL_RENDERER_COMBO_HH

#ifndef XFC_GTK_CELL_RENDERER_TEXT_HH
#include <xfc/gtk/cellrenderertext.hh>
#endif

#ifndef GTK_CELL_RENDERER_COMBO_H
#include <gtk/gtkcellrenderercombo.h>
#endif

namespace Xfc {

namespace Gtk {

class TreeModel;

/// @class CellRendererCombo cellrenderercombo.hh xfc/gtk/cellrenderercombo.hh
/// @brief A GtkCellRendererCombo C++ wrapper class.
///
/// CellRendererCombo is a cell renderer that renders a combobox in a cell. Whereas
/// CellRendererText offers a simple entry to edit text, CellRendererCombo offers a
/// ComboBox or ComboBoxEntry widget to edit the text. The values to display in the
/// combo box are taken from the tree model specified in the model property. 
///
/// The combo cell renderer takes care of adding a text cell renderer to the combo 
/// box and sets it to display the column specified by its text-column property. 
/// Further cell renderers can be added in a handler for the "editing-started" signal. 

class CellRendererCombo : public CellRendererText
{
	friend class G::Object;
	
	CellRendererCombo(const CellRendererCombo&);
	CellRendererCombo& operator=(const CellRendererCombo&);
	
protected:
/// @name Constructors
/// @{

	explicit CellRendererCombo(GtkCellRendererCombo *cell, bool owns_reference = false);
	///< Construct a new CellRendererCombo from an existing GtkCellRendererCombo.
	///< @param cell A pointer to a GtkCellRendererCombo.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>cell</EM> can be a newly created GtkCellRendererCombo or an existing
	///< GtkCellRendererCombo. (see G::Object::Object).
	
/// @}
/// @name Property Prototypes
/// @{

	typedef G::Property<TreeModel*, G::Object*> ModelPropertyType;
	typedef G::PropertyProxy<G::Object, ModelPropertyType> ModelPropertyProxy;
	static const ModelPropertyType model_property;
	///< The model containing the possible values for the combo box (see property_model()).
	
	typedef G::Property<int> TextColumnPropertyType;
	typedef G::PropertyProxy<G::Object, TextColumnPropertyType> TextColumnPropertyProxy;
	static const TextColumnPropertyType text_column_property;
	///< A column in the data source model to get the strings from (see property_text_column()).

	typedef G::Property<bool> HasEntryPropertyType;
	typedef G::PropertyProxy<G::Object, HasEntryPropertyType> HasEntryPropertyProxy;
	static const HasEntryPropertyType has_entry_property;
	///< If false, don't allow to enter strings other than the chosen ones (see property_has_entry()).

/// @}

public:
	typedef GtkCellRendererCombo CObjectType;

/// @name Constructors
/// @{
	
	CellRendererCombo();
	///< Construct a new CellRendererCombo. 
	
	
	virtual ~CellRendererCombo();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkCellRendererCombo* gtk_cell_renderer_combo() const;
	///< Get a pointer to the GtkCellRendererCombo structure.

	operator GtkCellRendererCombo* () const;
	///< Conversion operator; safely converts an CellRendererCombo to a GtkCellRendererCombo pointer.

/// @}
/// @name Property Proxies
/// @{

	const ModelPropertyProxy property_model();
	///< The model containing the possible values for the combo box (TreeModel* : Read / Write).

	const TextColumnPropertyProxy property_text_column();
	///< Specifies the column in the data source model to get the strings from (int : Read / Write).
	///< Note that this refers to the model specified in the model property, not the model backing
	///< the tree view to which this cell renderer is attached. 
	///<
	///< CellRendererCombo automatically adds a text cell renderer for this column to its combo box.
	///< The allowed vales are >= -1, the default value is -1.	
	
	const HasEntryPropertyProxy property_has_entry();
	///< If true, the cell renderer will include an entry and allow to enter values
	///< other than the ones in the popup list (bool : Read / Write). The default 
	///< value is <EM>true</EM>.	
	
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/cellrenderercombo.inl>

#endif // XFCE_GTK_CELL_RENDERER_COMBO_HH

