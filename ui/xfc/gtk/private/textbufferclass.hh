/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  textbufferclass.hh - Private interface
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

#ifndef XFC_GTK_TEXT_BUFFER_CLASS_HH
#define XFC_GTK_TEXT_BUFFER_CLASS_HH

#include <xfc/glib/private/objectclass.hh>

namespace Xfc {

namespace Gtk {

/*  Gtk::TextMarkClass
 */

class TextMarkClass
{
public:
	static void init(GtkTextMarkClass *g_class);
	
	static GType get_type();

	static void* create();
};

/*  Gtk::TextChildAnchorClass
 */

class TextChildAnchorClass
{
public:
	static void init(GtkTextChildAnchorClass *g_class);
	
	static GType get_type();

	static void* create();
};

/*  Gtk::TextBuffer
 */

class TextBufferClass
{
public:
	static void init(GtkTextBufferClass *g_class);

	static GtkTextBufferClass* get_parent_class(void *instance);

	static GType get_type();

	static void* create(GtkTextTagTable *table);

	static void insert_text_proxy(GtkTextBuffer *buffer, GtkTextIter *pos, const gchar *text, gint length);

	static void insert_pixbuf_proxy(GtkTextBuffer *buffer, GtkTextIter *pos, GdkPixbuf *pixbuf);

	static void insert_child_anchor_proxy(GtkTextBuffer *buffer, GtkTextIter *pos, GtkTextChildAnchor *anchor);

	static void delete_range_proxy(GtkTextBuffer *buffer, GtkTextIter *start, GtkTextIter *end);

	static void changed_proxy(GtkTextBuffer *buffer);

	static void modified_changed_proxy(GtkTextBuffer *buffer);

	static void mark_set_proxy(GtkTextBuffer *buffer, const GtkTextIter *location, GtkTextMark *mark);

	static void mark_deleted_proxy(GtkTextBuffer *buffer, GtkTextMark *mark);

	static void apply_tag_proxy(GtkTextBuffer *buffer, GtkTextTag *tag, const GtkTextIter *start_char, const GtkTextIter *end_char);

	static void remove_tag_proxy(GtkTextBuffer *buffer, GtkTextTag *tag, const GtkTextIter *start_char, const GtkTextIter *end_char);

	static void begin_user_action_proxy(GtkTextBuffer *buffer);

	static void end_user_action_proxy(GtkTextBuffer *buffer);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TEXT_BUFFER_CLASS_HH

