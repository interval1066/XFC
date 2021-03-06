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
 
/// @file xfc/gtk/cellrenderertextsignals.hh
/// @brief Gtk::CellRendererText virtual signal handlers.
///
/// Provides Gtk::CellRendererTextSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::CellRendererText objects.

#ifndef XFC_GTK_CELL_RENDERER_TEXT_SIGNALS_HH
#define XFC_GTK_CELL_RENDERER_TEXT_SIGNALS_HH

#ifndef XFC_GTK_CELL_RENDERER_SIGNALS_HH
#include <xfc/gtk/cellrenderersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class CellRendererTextSignals cellrenderertextsignals.hh xfc/gtk/cellrenderertextsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::CellRendererText.

class CellRendererTextSignals : public CellRendererSignals
{
protected:
/// @name Constructors
/// @{

	CellRendererTextSignals(CellRendererText *cell);
	///< Construct a new CellRendererTextSignals object. 
	///< @param cell A CellRendererText object inheriting the CellRendererTextSignals implementation.
	
	virtual ~CellRendererTextSignals() = 0;
	///< Destructor.
	
/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_edited(const String& path, const String& new_text);
	///< Called when the user has finished editing the cell text.
	///< @param path Widget-dependent string representation of the event location;
	///<             e.g. for TreeView, a string representation of TreePath.
	///< @param new_text The newly edited text.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_CELL_RENDERER_TEXT_SIGNALS_HH

