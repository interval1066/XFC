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

/// @file xfc/gtk/texttagsignals.hh
/// @brief Gtk::TextTag and Gtk::TextTagTable virtual signal handlers.
///
/// Provides Gtk::TextTagSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::TextTag objects.

#ifndef XFC_GTK_TEXT_TAG_SIGNALS_HH
#define XFC_GTK_TEXT_TAG_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class TextTagSignals texttagsignals.hh xfc/gtk/texttagsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::TextTag.

class TextTagSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	TextTagSignals(TextTag *tag);
	///< Constructs a new TextTagSignals object.
	///< @param tag A TextTag object inheriting the TextTagSignals implementation.

	virtual ~TextTagSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{
	bool on_event(G::Object& event_object, Gdk::Event& event, const TextIter& iter);
	///< Called when the text tag receives a motion, button, or key event signal.
	///< @param event_object The object that received the event, such as a widget.
	///< @param event The event.
	///< @param iter The location where the event was received.
	///< @return <EM>true</EM> if the event was handled, <EM>false</EM> if it wasn't handled.

/// @}
};

/// @class TextTagTableSignals texttagsignals.hh xfc/gtk/texttagsignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::TextTagTable.

class TextTagTableSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	TextTagTableSignals(TextTagTable *table);
	///< Constructs a new TextTagTableSignals object.
	///< @param table A TextTag object inheriting the TextTagTableSignals implementation.

	virtual ~TextTagTableSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_tag_changed(TextTag& tag, bool size_changed);
	///< Called whenever a tag property is changed.
	///< @param tag The tag whose property was changed.
	///< @param size_changed <EM>true</EM> if the changed property resulted in a change
	///< to the text display size.

	virtual void on_tag_added(TextTag& tag);
	///< Called whenever a tag is added to the table.
	///< @param tag The tag being added to the table.

	virtual void on_tag_removed(TextTag& tag);
	///< Called whenever a tag is removed from the table.
	///< @param tag The tag being removed to the table.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TEXT_TAG_SIGNALS_HH

