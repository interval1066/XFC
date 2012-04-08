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
 
/// @file xfc/gtk/editablesignals.hh
/// @brief Gtk::Editable virtual signal handlers.
///
/// Provides Gtk::EditableSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::Editable objects.

#ifndef XFC_GTK_EDITABLE_SIGNALS_HH
#define XFC_GTK_EDITABLE_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class EditableSignals editable.hh xfc/gtk/impl/editable.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::Editable.

class EditableSignals : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	virtual ~EditableSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_insert_text(const String& text, int *position);
	///< Called when text is inserted into the widget by the user.
	///< @param text The new text to insert.
	///< @param position The position at which to insert the new text.
	///<
	///< Position is an in-out paramter. After the signal emission is finished, it should
	///< point after the newly inserted text. The default handler for this signal will normally
	///< be responsible for inserting the text, so by overriding this method and either calling
	///< or not calling the parent class method, it is possible to modify the inserted text,
	///< or prevent it from being inserted entirely.

	virtual void on_delete_text(int start_pos, int end_pos);
	///< Called when text is deleted from the widget by the user.
	///< @param start_pos The starting position.
	///< @param end_pos The end position.
	///<
	///< The default handler for this signal will normally be responsible for deleting
	///< the text, so by overriding this method and either calling or not calling the parent
	///< class method, it is possible to modify the deleted text, or prevent it from being
	///< deleted entirely. The start_pos and end_pos parameters are interpreted as for
	///< delete_text()

	virtual void on_changed();
	///< Called when the user changes the contents of the widget.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_EDITABLE_SIGNALS_HH

