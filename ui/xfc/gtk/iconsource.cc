/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  iconfactory.cc - GtkIconSource C++ wrapper implementation
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
 
#include "iconsource.hh"
#include "../gdk-pixbuf/pixbuf.hh"

using namespace Xfc;

/*  Gtk::IconSource
 */

Gtk::IconSource::IconSource()
: G::Boxed(GTK_TYPE_ICON_SOURCE, gtk_icon_source_new(), false)
{
}

Gtk::IconSource::IconSource(GtkIconSource *source)
: G::Boxed(GTK_TYPE_ICON_SOURCE, source)
{
}

Gtk::IconSource::IconSource(GtkIconSource *source, bool copy)
: G::Boxed(GTK_TYPE_ICON_SOURCE, source, copy)
{
}

Gtk::IconSource::IconSource(const IconSource& src)
: G::Boxed(GTK_TYPE_ICON_SOURCE, src.g_boxed(), true)
{
}

Gtk::IconSource::~IconSource()
{
}

Gtk::IconSource&
Gtk::IconSource::operator=(const IconSource& src)
{
	if (src.boxed_ != boxed_)
		copy(src);
	return *this;
}

String
Gtk::IconSource::get_filename() const
{
	return gtk_icon_source_get_filename(gtk_icon_source());
}

String
Gtk::IconSource::get_icon_name() const
{
	return gtk_icon_source_get_icon_name(gtk_icon_source());
}

Gdk::Pixbuf*
Gtk::IconSource::get_pixbuf() const
{
	return G::Object::wrap<Gdk::Pixbuf>(gtk_icon_source_get_pixbuf(gtk_icon_source()));
}

void
Gtk::IconSource::set_filename(const String& filename)
{
	gtk_icon_source_set_filename(gtk_icon_source(), filename.c_str());
}

void
Gtk::IconSource::set_icon_name(const String& icon_name)
{
	gtk_icon_source_set_icon_name(gtk_icon_source(), icon_name.c_str());
}

void
Gtk::IconSource::set_pixbuf(Gdk::Pixbuf *pixbuf)
{
	gtk_icon_source_set_pixbuf(gtk_icon_source(), *pixbuf);
}

