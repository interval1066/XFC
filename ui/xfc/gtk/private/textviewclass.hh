/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  textviewclass.hh - Private interface
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

#ifndef XFC_GTK_TEXT_VIEW_CLASS_HH
#define XFC_GTK_TEXT_VIEW_CLASS_HH

#include <xfc/gtk/private/containerclass.hh>

namespace Xfc {

namespace Gtk {

class TextViewClass
{
public:
	static void init(GtkTextViewClass *g_class);

	static GtkTextViewClass* get_parent_class(void *instance);

	static GType get_type();

	static void* create();

	static void set_scroll_adjustments_proxy(GtkTextView *text_view, GtkAdjustment *hadjustment, GtkAdjustment *vadjustment);

	static void populate_popup_proxy(GtkTextView *text_view, GtkMenu *menu);

	static void set_anchor_proxy(GtkTextView *text_view);

	static void insert_at_cursor_proxy(GtkTextView *text_view, const gchar *str);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TEXT_VIEW_CLASS_HH

