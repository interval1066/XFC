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
 
/// @file xfc/gtk/cellrendererprogress.hh
/// @brief A GtkCellRendererProgress C++ wrapper interface.
///
/// Provides CellRendererProgress, a cell renderer that renders numbers as progress bars.

#ifndef XFCE_GTK_CELL_RENDERER_PROGRESS_HH
#define XFC_GTK_CELL_RENDERER_PROGRESS_HH

#ifndef XFC_GTK_CELL_RENDERER_HH
#include <xfc/gtk/cellrenderer.hh>
#endif

#ifndef GTK_CELL_RENDERER_PROGRESS_H
#include <gtk/gtkcellrendererprogress.h>
#endif

namespace Xfc {

namespace Gtk {

/// @class CellRendererProgress cellrendererprogress.hh xfc/gtk/cellrendererprogress.hh
/// @brief A GtkCellRendererProgress C++ wrapper class.
///
/// CellRendererProgress is a cell renderer that renders numbers as progress bars. 

class CellRendererProgress : public CellRenderer
{
	friend class G::Object;
	
	CellRendererProgress(const CellRendererProgress&);
	CellRendererProgress& operator=(const CellRendererProgress&);
	
protected:
/// @name Constructors
/// @{

	explicit CellRendererProgress(GtkCellRendererProgress *cell, bool owns_reference = false);
	///< Construct a new CellRendererProgress from an existing GtkCellRendererProgress.
	///< @param cell A pointer to a GtkCellRendererProgress.
	///< @param owns_reference Set false if the initial reference count is floating, set true if it's not.
	///<
	///< The <EM>cell</EM> can be a newly created GtkCellRendererProgress or an existing
	///< GtkCellRendererProgress. (see G::Object::Object).
	
/// @}
/// @name Property Prototypes
/// @{

	typedef G::Property<int> ValuePropertyType;
	typedef G::PropertyProxy<G::Object, ValuePropertyType> ValuePropertyProxy;
	static const ValuePropertyType value_property;
	///< The Value of the progress bar (see property_value()).
	
	typedef G::Property<String> TextPropertyType;
	typedef G::PropertyProxy<G::Object, TextPropertyType> TextPropertyProxy;
	static const TextPropertyType text_property;
	///< The text on the progress bar (see property_text()).

/// @}

public:
	typedef GtkCellRendererProgress CObjectType;

/// @name Constructors
/// @{
	
	CellRendererProgress();
	///< Construct a new CellRendererProgress. 
	
	
	virtual ~CellRendererProgress();
	///< Destructor.
	
/// @}
/// @name Accessors
/// @{

	GtkCellRendererProgress* gtk_cell_renderer_progress() const;
	///< Get a pointer to the GtkCellRendererProgress structure.

	operator GtkCellRendererProgress* () const;
	///< Conversion operator; safely converts an CellRendererProgress to a GtkCellRendererProgress pointer.

/// @}
/// @name Property Proxies
/// @{

	const ValuePropertyProxy property_value();
	///< The "value" property determines the percentage to which the progress bar
	///< will be "filled in" (int : Read / Write). The allowed values are: [0,100]. 
	///< The default value is 0.	
	
	const TextPropertyProxy property_text();
	///< The "text" property determines the label which will be drawn over the 
	///< progress bar. Setting this property to null causes the default label
	///< to be displayed. Setting this property to an empty string causes no
	///< label to be displayed. The default value is null.
		
/// @}
};

} // namespace Gtk

} // namespace Xfc

#include <xfc/gtk/inline/cellrendererprogress.inl>

#endif // XFCE_GTK_CELL_RENDERER_PROGRESS_HH

