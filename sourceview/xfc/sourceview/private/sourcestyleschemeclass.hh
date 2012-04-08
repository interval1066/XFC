/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  sourcestyleschemeclass.hh - Private interface
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

#ifndef XFC_GTK_SOURCE_STYLE_SCHEME_CLASS_H
#define XFC_GTK_SOURCE_STYLE_SCHEME_CLASS_H

namespace Xfc {

namespace Gtk {

class SourceStyleSchemeClass
{
public:
	static void init(GtkSourceStyleSchemeClass *g_iface);

    static GtkSourceStyleSchemeClass* get_parent_class(void *instance);

	static const gchar* get_name_proxy(GtkSourceStyleScheme *scheme);

	static void style_changed_proxy(GtkSourceStyleScheme *scheme, const gchar *tag_id);

	static GtkSourceTagStyle* get_tag_style_proxy(GtkSourceStyleScheme *scheme, const gchar *style_name);

	static GSList* get_style_names_proxy(GtkSourceStyleScheme *scheme);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_SOURCE_STYLE_SCHEME_CLASS_H

