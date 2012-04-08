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

/// @file xfc/gtk/notebooksignals.hh
/// @brief Gtk::Notebook virtual signal handlers.
///
/// Provides Gtk::NotebookSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Notebook objects.

#ifndef XFC_GTK_NOTEBOOK_SIGNALS_HH
#define XFC_GTK_NOTEBOOK_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class NotebookSignals notebooksignals.hh xfc/gtk/notebooksignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Notebook.

class NotebookSignals : public virtual ContainerSignals
{
protected:
/// @name Constructors
/// @{

	NotebookSignals(Notebook *notebook);
	///< Constructs a new NotebookSignals object.
	///< @param notebook A Notebook object inheriting the NotebookSignals implementation.

	virtual ~NotebookSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_switch_page(Widget& page_child, unsigned int page_num);
	///< Called when the user or a function changes the current page.
	///< @param page_child The child widget that is the contents of the new current page.
	///< @param page_num The index of the new current page.
	///<
	///< The <EM>page_child</EM> argument is a reference the child widget that was
	///< added to the page <EM>page_num</EM> when it was created, either by calling
	///< append_page(), prepend_page() or insert_page().

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_NOTEBOOK_SIGNALS_HH

