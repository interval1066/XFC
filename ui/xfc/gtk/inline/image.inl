/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  image.inl - Gtk::Image inline functions
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

inline GtkImage*
Xfc::Gtk::Image::gtk_image() const
{
	return reinterpret_cast<GtkImage*>(instance_);
}

inline Xfc::Gtk::Image::operator GtkImage* () const
{
	return this ? gtk_image() : 0;
}

inline Xfc::Gtk::ImageType
Xfc::Gtk::Image::get_storage_type() const
{
	return (ImageType)gtk_image_get_storage_type(gtk_image());
}

inline int 
Xfc::Gtk::Image::get_pixel_size() const
{
	return gtk_image_get_pixel_size(gtk_image());
}

inline void
Xfc::Gtk::Image::set(const char *filename)
{
	gtk_image_set_from_file(gtk_image(), filename);
}

inline void
Xfc::Gtk::Image::reset()
{
	gtk_image_set_from_pixbuf(gtk_image(), 0);
}

