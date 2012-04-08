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

/// @file xfc/gtk/textbuffersignals.hh
/// @brief Gtk::TextBuffer virtual signal handlers.
///
/// Provides Gtk::TextBufferSignals, an abstract base class that implements
/// the overridable virtual signal handlers for Gtk::TextBuffer objects.

#ifndef XFC_GTK_TEXT_BUFFER_SIGNALS_HH
#define XFC_GTK_TEXT_BUFFER_SIGNALS_HH

#ifndef XFC_G_OBJECT_SIGNALS_HH
#include <xfc/glib/objectsignals.hh>
#endif

namespace Xfc {

namespace Gtk {

/// @class TextBufferSignals textbuffersignals.hh xfc/gtk/textbuffersignals.hh
/// @brief Abstract base class that implements the virtual signal handlers for Gtk::TextBuffer.

class TextBufferSignals : public G::ObjectSignals
{
protected:
/// @name Constructors
/// @{

	TextBufferSignals(TextBuffer *buffer);
	///< Constructs a new TextBufferSignals object.
	///< @param buffer A TextBuffer object inheriting the TextBufferSignals implementation.

	virtual ~TextBufferSignals() = 0;
	///< Destructor.

/// @}

public:
/// @name Signal Handlers
/// @{

	virtual void on_insert_text(TextIter& pos, const String& text);
	///< Called whenever text is inserted into the text buffer.
	///< @param pos A position in the buffer.
	///< @param text The text to insert.

	virtual void on_insert_pixbuf(TextIter& pos, Gdk::Pixbuf& pixbuf);
	///< Called when a pixbuf image is inserted into the buffer.
	///< @param pos The location to insert the pixbuf.
	///< @param pixbuf A Gdk::Pixbuf.

	virtual void on_insert_child_anchor(TextIter& pos, TextChildAnchor& anchor);
	///< Called when a child anchor is inserted into the buffer.
	///< @param pos The location to insert the anchor.
	///< @param anchor A TextChildAnchor.

	virtual void on_delete_range(TextIter& start, TextIter& end);
	///< Called when contents of the buffer in the range <EM>start</EM> to <EM>end</EM> are removed.
	///< @param start A position in the buffer.
	///< @param end Another position in the buffer.

	virtual void on_changed();
	///< Called when the contents of the buffer are changed by an insertion or deletion action.

	virtual void on_modified_changed();
	///< Called when the buffer has been modified since the last time it was saved.

	virtual void on_mark_set(const TextIter& location, TextMark& mark);
	///< Called when a mark is placed in the buffer.
	///< @param location The location for <EM>mark</EM> in the buffer.
	///< @param mark A TextMark.

	virtual void on_mark_deleted(TextMark& mark);
	///< Called when a mark is removed from the buffer.
	///< @param mark A TextMark.

	virtual void on_apply_tag(TextTag& tag, const TextIter& start_char, const TextIter& end_char);
	///< Called when <EM>tag</EM> is applied to the given range <EM>start_char</EM> to <EM>end_char</EM>.
	///< @param tag A TextTag.
	///< @param start_char One bound of a range to be tagged.
	///< @param end_char The other bound of a range to be tagged.

	virtual void on_remove_tag(TextTag& tag, const TextIter& start_char, const TextIter& end_char);
	///< Called when all occurrences of <EM>tag</EM> are removed from the given range
	///< <EM>start_char</EM> to <EM>end_char</EM>.
	///< @param tag A TextTag.
	///< @param start_char One bound of a range to be untagged.
	///< @param end_char The other bound of a range to be untagged.

	virtual void on_begin_user_action();
	///< Called to indicate the user is starting buffer operations that are part
	///< of a single user-visible operation.

	virtual void on_end_user_action();
	///< Called to indicate the user has ended the current buffer operations.

/// @}
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TEXT_BUFFER_SIGNALS_HH

