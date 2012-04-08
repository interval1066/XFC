/*  XFC: Xfce Foundation Classes (User Interface Library)
 *  Copyright (C) 2004-2005 The XFC Development Team.
 *
 *  filefilter.cc - GtkFileFilter C++ wrapper implementation
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

#include "filefilter.hh"
#include "private/filefilterclass.hh"

using namespace Xfc;

/*  Gtk::FileFilter
 */

Gtk::FileFilter::FileFilter(GtkFileFilter *filter, bool owns_reference)
: Object((GtkObject*)filter, owns_reference)
{
}

Gtk::FileFilter::FileFilter()
: Object((GtkObject*)FileFilterClass::create())
{
}

Gtk::FileFilter::~FileFilter()
{
}

String 
Gtk::FileFilter::get_name() const
{
	return gtk_file_filter_get_name(gtk_file_filter());
}

void 
Gtk::FileFilter::set_name(const String& name)
{
	set_name(name.c_str());
}

void 
Gtk::FileFilter::add_mime_type(const String& mime_type)
{
	add_mime_type(mime_type.c_str());
}

void 
Gtk::FileFilter::add_pattern(const String& pattern)
{
	add_pattern(pattern.c_str());
}

namespace { // FileFilterCallback

struct FileFilterCallback
{
	typedef Gtk::FileFilter::CustomSlot CustomSlot;
	CustomSlot slot_;

	FileFilterCallback(const CustomSlot& slot)
	: slot_(slot)
	{
	}
	
	static gboolean notify(const GtkFileFilterInfo *filter_info, void *data)
	{
		FileFilterCallback *cb = static_cast<FileFilterCallback*>(data);
		Gtk::FileFilterInfo info;
		info.contains = (Gtk::FileFilterFlagsField)filter_info->contains;
		info.filename = filter_info->filename;
		info.uri = filter_info->uri;
		info.display_name = filter_info->display_name;
		info.mime_type = filter_info->mime_type;
		return cb->slot_(info);
	}

	static void destroy(void *data)
	{
		FileFilterCallback *cb = static_cast<FileFilterCallback*>(data);
		delete cb;
	}
};

} // namespace

void 
Gtk::FileFilter::add_custom(FileFilterFlagsField needed, const CustomSlot& slot)
{
	FileFilterCallback *cb = new FileFilterCallback(slot);
	gtk_file_filter_add_custom(gtk_file_filter(), (GtkFileFilterFlags)needed,
	                           &FileFilterCallback::notify, cb, 
				   &FileFilterCallback::destroy);
}

/*  Gtk::FileFilterClass
 */

void
Gtk::FileFilterClass::init(GtkFileFilterClass *g_class)
{
	ObjectClass::init((GtkObjectClass*)g_class);
}

GType
Gtk::FileFilterClass::get_type()
{
	static GType type = 0;
	if (!type)
	{
		type = G::TypeInstance::register_type(GTK_TYPE_FILE_FILTER, (GClassInitFunc)&init);
	}
	return type;
}

void*
Gtk::FileFilterClass::create()
{
	return g_object_new(get_type(), 0);
}

