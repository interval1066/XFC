/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  texttag_p.h - Private interface
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

#ifndef XFC_GTK_TEXT_TAG_CLASS_HH
#define XFC_GTK_TEXT_TAG_CLASS_HH

#include <xfc/glib/private/objectclass.hh>

namespace Xfc {

namespace Gtk {

/*  Gtk::TextTagClass
 */

class TextTagClass
{
public:
	static void init(GtkTextTagClass *g_class);

	static GtkTextTagClass* get_parent_class(void *instance);

	static GType get_type();

	static void* create(const char *name);

	static gboolean event_proxy(GtkTextTag *tag, GObject *event_object, GdkEvent *event, const GtkTextIter *iter);
};

/*  Gtk::TextTagTableClass
 */

class TextTagTableClass
{
public:
	static void init(GtkTextTagTableClass *g_class);

	static GtkTextTagTableClass* get_parent_class(void *instance);

	static GType get_type();

	static void* create();

	static void tag_changed_proxy(GtkTextTagTable *table, GtkTextTag *tag, gboolean size_changed);

	static void tag_added_proxy(GtkTextTagTable *table, GtkTextTag *tag);

	static void tag_removed_proxy(GtkTextTagTable *table, GtkTextTag *tag);
};

} // namespace Gtk

} // namespace Xfc

#endif // XFC_GTK_TEXT_TAG_CLASS_HH

