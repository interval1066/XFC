/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2005 The XFC Development Team.
 *
 *  pixbuf-io.cc - GdkPixbufFormat C++ wrapper implementation
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
 
#include "pixbuf-io.hh"

using namespace Xfc;

/*  Gdk::PixbufFormat
 */

Gdk::PixbufFormat::PixbufFormat(GdkPixbufFormat *format)
: format_(format)
{
}

Gdk::PixbufFormat::~PixbufFormat()
{
}

String
Gdk::PixbufFormat::get_name() const
{
	char *name = gdk_pixbuf_format_get_name(format_);
	String s(name);
	g_free(name);
	return s;
}

String 
Gdk::PixbufFormat::get_description() const
{
	char *description = gdk_pixbuf_format_get_description(format_);
	String s(description);
	g_free(description);
	return s;
}

std::vector<String> 
Gdk::PixbufFormat::get_mime_types() const
{
	std::vector<String> mime_types;

	int i = 0;
	char **tmp_mime_types = gdk_pixbuf_format_get_mime_types(format_);

	while (tmp_mime_types[i] && *tmp_mime_types[i])
	{
		String s(tmp_mime_types[i]);
		mime_types.push_back(s);
		++i;
	}

	g_strfreev(tmp_mime_types);
	return mime_types;
}

std::vector<String> 
Gdk::PixbufFormat::get_extensions() const
{
	std::vector<String> extensions;

	int i = 0;
	char **tmp_extensions = gdk_pixbuf_format_get_mime_types(format_);

	while (tmp_extensions[i] && *tmp_extensions[i])
	{
		String s(tmp_extensions[i]);
		extensions.push_back(s);
		++i;
	}

	g_strfreev(tmp_extensions);
	return extensions;
}

bool
Gdk::PixbufFormat::get_formats(std::vector<Pointer<PixbufFormat> >& formats)
{
	g_return_val_if_fail(formats.empty(), false);

	GSList *first = gdk_pixbuf_get_formats();
	GSList *next = first;

	while (next)
	{
		Pointer<PixbufFormat> format(new PixbufFormat((GdkPixbufFormat*)next->data));
		formats.push_back(format);
		next = g_slist_next(next);
	}

	g_slist_free(first);
	return !formats.empty();
}

Gdk::PixbufFormat* 
Gdk::PixbufFormat::get_file_info(const char *filename, int *width, int *height)
{
	GdkPixbufFormat *format = gdk_pixbuf_get_file_info(filename, width, height);
	return format ? new PixbufFormat(format) : 0;
}

Gdk::PixbufFormat* 
Gdk::PixbufFormat::get_file_info(const String& filename, int *width, int *height)
{
	return get_file_info(filename.c_str(), width, height);
}

String 
Gdk::PixbufFormat::get_license() const
{
	char *license = gdk_pixbuf_format_get_license(gdk_pixbuf_format());
	String s(license);
	g_free(license);
	return s;
}

