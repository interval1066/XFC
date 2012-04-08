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

/// @file xfc/gtk/textviewsignals.hh
/// @brief Gtk::TextView virtual signal handlers.
///
/// Provides Gtk::TextViewSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::TextView objects.

#ifndef XFC_GTK_TEXT_VIEW_SIGNALS_HH
#define XFC_GTK_TEXT_VIEW_SIGNALS_HH

#ifndef XFC_GTK_CONTAINER_SIGNALS_HH
#include <xfc/gtk/containersignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class TextViewSignals textviewsignals.hh xfc/gtk/textviewsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::TextView.

class TextViewSignals : public ContainerSignals
{
protected:
/// @name Constructors
/// @{

	TextViewSignals(TextView *text_view);
	///< Constructs a new TextViewSignals object.
	///< @param text_view A TextView object inheriting the TextViewSignals implementation.

	virtual ~TextViewSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_set_scroll_adjustments(Adjustment *hadjustment, Adjustment *vadjustment);
	///< Called when a text view is added to a scrolling aware parent.
	///< @param hadjustment The horizontal adjustment.
	///< @param vadjustment The vertical adjustment.

	virtual void on_populate_popup(Menu& menu);
	///< Called when the text view displays its context-sensitive menu.
	///< @param menu The popup menu.

	virtual void on_set_anchor();
	///< Called when the "anchor" is moved (what Emacs calls the mark) to the cursor position.

	virtual void on_insert_at_cursor(const String& str);
	///< Called when text is inserted into the buffer at the current cursor position.
	///< @param str The new text to insert.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TEXT_VIEW_SIGNALS_HH

