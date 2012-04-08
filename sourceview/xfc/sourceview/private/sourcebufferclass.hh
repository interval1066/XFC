/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourcebufferclass.hh - Private interface
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef XFC_SOURCE_BUFFER_CLASS_HH
#define XFC_SOURCE_BUFFER_CLASS_HH

#include <xfc/gtk/private/textbufferclass.hh>

namespace Xfc {

namespace Gtk {

class SourceBufferClass
{
public:
	static void init(GtkSourceBufferClass *g_class);

	static GType get_type();

	static void* create(GtkSourceTagTable *table);

    static GtkSourceBufferClass* get_parent_class(void *instance);

	static void can_undo_proxy(GtkSourceBuffer *buffer, gboolean can_undo);

	static void can_redo_proxy(GtkSourceBuffer *buffer, gboolean can_redo);

	static void highlight_updated_proxy(GtkSourceBuffer *buffer, GtkTextIter *start, GtkTextIter *end);

	static void marker_updated_proxy(GtkSourceBuffer *buffer, GtkTextIter *where);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_BUFFER_CLASS_H

