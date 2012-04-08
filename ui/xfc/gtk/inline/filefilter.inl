/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  filefilter.inl - Gtk::FileFilter inline functions
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

inline GtkFileFilter*
Xfc::Gtk::FileFilter::gtk_file_filter() const
{
	return reinterpret_cast<GtkFileFilter*>(instance_);
}

inline Xfc::Gtk::FileFilter::operator GtkFileFilter* () const
{
	return this ? gtk_file_filter() : 0;
}

inline void 
Xfc::Gtk::FileFilter::set_name(const char *name)
{
	gtk_file_filter_set_name(gtk_file_filter(), name);
}

inline void 
Xfc::Gtk::FileFilter::add_mime_type(const char *mime_type)
{
	gtk_file_filter_add_mime_type(gtk_file_filter(), mime_type);
}

inline void 
Xfc::Gtk::FileFilter::add_pattern(const char *pattern)
{
	gtk_file_filter_add_pattern(gtk_file_filter(), pattern);
}

inline void 
Xfc::Gtk::FileFilter::add_pixbuf_formats()
{
	gtk_file_filter_add_pixbuf_formats(gtk_file_filter());
}

