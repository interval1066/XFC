/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  iconfactory.cc - GtkIconSet C++ wrapper implementation
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
 
#include "iconset.hh"
#include "style.hh"
#include "widget.hh"
#include "../gdk-pixbuf/pixbuf.hh"

using namespace Xfc;

/*  Gtk::IconSet
 */

Gtk::IconSet::IconSet()
: G::Boxed(GTK_TYPE_ICON_SET, gtk_icon_set_new(), false)
{
}

Gtk::IconSet::IconSet(Gdk::Pixbuf& pixbuf)
: G::Boxed(GTK_TYPE_ICON_SET, gtk_icon_set_new_from_pixbuf(pixbuf.gdk_pixbuf()), false)
{
}

Gtk::IconSet::IconSet(GtkIconSet *icon_set)
: G::Boxed(GTK_TYPE_ICON_SET, icon_set)
{
}

Gtk::IconSet::IconSet(GtkIconSet *icon_set, bool copy)
: G::Boxed(GTK_TYPE_ICON_SET, icon_set, copy)
{
}

Gtk::IconSet::IconSet(const IconSet& src)
: G::Boxed(GTK_TYPE_ICON_SET, src.g_boxed(), true)
{
}

Gtk::IconSet::~IconSet()
{
}

Gtk::IconSet&
Gtk::IconSet::operator=(const IconSet& src)
{
	if (src.boxed_ == boxed_)
		return *this;

	copy(src);
	return *this;
}

bool
Gtk::IconSet::get_sizes(std::vector<IconSize>& sizes) const
{
	g_return_val_if_fail(sizes.empty(), false);
	GtkIconSize *tmp_sizes = 0;
	int n_sizes = 0;

	gtk_icon_set_get_sizes(gtk_icon_set(), &tmp_sizes, &n_sizes);

	int i = 0;
	while (i < n_sizes)
	{
		sizes.push_back((IconSize)tmp_sizes[i]);
		++i;
	}

	g_free(tmp_sizes);
	return !sizes.empty();
}

Pointer<Gdk::Pixbuf>
Gtk::IconSet::render_icon(Style& style, StateType state, IconSize size, Widget *widget, 
                          const char *detail, TextDirection direction)
{
	GdkPixbuf *pixbuf = gtk_icon_set_render_icon(gtk_icon_set(), style.gtk_style(), (GtkTextDirection)direction,
	                                             (GtkStateType)state, (GtkIconSize)size, *widget, detail);
	return G::Object::wrap<Gdk::Pixbuf>(pixbuf, true);
}

void
Gtk::IconSet::add_source(const IconSource& source)
{
	gtk_icon_set_add_source(gtk_icon_set(), source.gtk_icon_source());
}

