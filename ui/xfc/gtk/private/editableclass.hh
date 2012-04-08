/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  editableclass.hh - Private interface
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

#ifndef XFC_GTK_EDITABLE_CLASS_HH
#define XFC_GTK_EDITABLE_CLASS_HH

namespace Xfc {

namespace Gtk {

class EditableClass
{
public:
	static void init(GtkEditableClass *g_iface);

	static GtkEditableClass* get_parent_iface(void *instance);

	static void insert_text_proxy(GtkEditable *editable, const gchar *text, gint length, gint *position);

	static void delete_text_proxy(GtkEditable *editable, gint start_pos, gint end_pos);

	static void changed_proxy(GtkEditable *editable);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_EDITABLE_CLASS_HH

