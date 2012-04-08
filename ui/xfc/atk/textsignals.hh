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

/// @file xfc/atk/textsignals.hh
/// @brief Atk::Text virtual signal handlers.
///
/// Provides Atk::TextSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Atk::Text objects.

#ifndef XFC_ATK_TEXT_SIGNALS_HH
#define XFC_ATK_TEXT_SIGNALS_HH

#ifndef XFC_G_TYPE_HH
#include <xfc/glib/type.hh>
#endif

namespace Xfc {

namespace Atk {

/// @class TextSignals textsignals.hh xfc/atk/textsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Atk::Text.

class TextSignals : public virtual G::TypeInterface
{
protected:
/// @name Constructors
/// @{

	virtual ~TextSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_text_changed(int position, int length);
	///< Called when text is inserted or deleted.
	///< @param position The position of the insertion or deletion.
	///< @param length The length of the text inserted or deleted.

	virtual void on_text_caret_moved(int location);
	///< Called when the text caret is moved.
	///< @param location The new position of the text caret.

	virtual void on_text_selection_changed();
	///< Called when the text selection changes.

	virtual void on_text_attributes_changed();
	///< Called when the text attributes change.

/// @}
};

} // namespace Atk

} // namespace Xfc

#endif // XFC_ATK_TEXT_SIGNALS_HH

